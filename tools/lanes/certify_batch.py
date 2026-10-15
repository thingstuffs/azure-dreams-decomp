#!/usr/bin/env python3
"""Validate recorded certificates and renew selected ones in a cancellable group."""
import argparse
from concurrent.futures import ThreadPoolExecutor,ProcessPoolExecutor,as_completed
import contextlib
from contextvars import ContextVar
import importlib.util
import multiprocessing
import json
import os
from pathlib import Path
import signal
import subprocess
import sys
import time
import threading
import traceback

def jobs(root):
    result={}
    for p in sorted((root/'ledger/modules').glob('overlay_*.json')):
        rec=json.loads(p.read_text());key=rec.get('module');reviewer=rec.get('reviewer')
        if not key or p.name!='overlay_'+key+'.json' or not reviewer or reviewer=='pending':
            raise ValueError('invalid live certificate: '+str(p))
        result[key]=reviewer
    return result

def review_complete(module):
    """True when a manifest module carries a finished review by a named reviewer."""
    review=module.get('review')
    if not isinstance(review,dict):return False
    reviewer=review.get('reviewer')
    if not isinstance(reviewer,str) or not reviewer or reviewer=='pending':return False
    fields=[v for k,v in review.items() if k!='reviewer']
    return bool(fields) and all(v=='reviewed' for v in fields)


def uncertified(root):
    """Return ({key: recorded review.reviewer} for reviewed modules lacking a certificate, [unreviewed keys])."""
    modules=json.loads((root/'config/overlays/modules.json').read_text())['modules']
    ready={};waiting=[]
    for m in modules:
        if (root/'ledger/modules'/('overlay_'+m['key']+'.json')).exists():continue
        if review_complete(m):ready[m['key']]=m['review']['reviewer']
        else:waiting.append(m['key'])
    return ready,sorted(waiting)


def _reader(root):
    # A worker imports ONLY this root's authority. Pools use spawn so caches,
    # signal handlers and imports from another validation cannot leak in.
    sys.path[:0]=[str(root/'tools'),str(root/'tools/gate')]
    import overlay_module_evidence
    return overlay_module_evidence


def _validate_certificate(item):
    root,m,*options=item;reader=_reader(root)
    details=bool(options and options[0])
    # The same per-module body and exception policy as module_status. Every
    # certificate_reason call still performs the full manifest/fingerprint,
    # object, genuine proof, artifact, placement and retail checks.
    import yaml
    cert=None
    try:
        cert=json.loads((root/'ledger/modules'/('overlay_'+m['key']+'.json')).read_text())
        reason=reader.certificate_reason(m,cert,root)
    except (OSError,ValueError,KeyError,TypeError,AttributeError,IndexError,NameError,yaml.YAMLError,subprocess.SubprocessError) as e:
        reason='certificate missing/invalid: '+type(e).__name__+': '+str(e)
    if details:return {'module':m,'certificate':cert,'valid':reason is None,'reason':reason}
    return {'module':{'key':m['key']},'valid':reason is None,'reason':reason}


def _statuses(root,workers,details=False):
    reader=_reader(root)
    if workers==1 or not all(hasattr(reader,n) for n in ('load_modules','certificate_reason')):
        return reader.module_status(root)
    import yaml
    try:modules=reader.load_modules(root)
    except (OSError,ValueError,KeyError,TypeError,NameError,yaml.YAMLError) as e:
        return [{'module':{'key':'manifest','members':[]},'valid':False,
                 'reason':'manifest invalid: '+type(e).__name__+': '+str(e)}]
    with ProcessPoolExecutor(max_workers=workers,mp_context=multiprocessing.get_context('spawn')) as pool:
        try:return list(pool.map(_validate_certificate,((root,m,details) for m in modules)))
        except BaseException:
            # Do not enter Executor.__exit__'s wait while a descendant is
            # still compiling/preprocessing after a cancellation.
            signal.signal(signal.SIGTERM,signal.SIG_DFL)
            os.killpg(os.getpgrp(),signal.SIGTERM)
            raise


_PRODUCER=None

class _RetryLockedReceipt(Exception):pass


@contextlib.contextmanager
def _receipt_parallelism(producer,receipts):
    """Immutable receipt reads need no mutable-window build lock.

    The canonical fresh_window_source still validates context, inputs and
    every artifact. If it cannot reuse the snapshot, unwind BEFORE any gate
    build and retry the entire certificate with the original locking path.
    No certificate or proof check is skipped or cached here.
    """
    if receipts is None or not all(hasattr(producer,n) for n in ('certification_window_lock','fresh_window_source')):
        yield;return
    lock=producer.certification_window_lock;fresh=producer.fresh_window_source
    covered=json.loads((receipts/'index.json').read_text()).get('windows',{})
    unlocked=ContextVar('batch_immutable_receipt',default=False)
    @contextlib.contextmanager
    def window_lock(root,name):
        receipt=receipts/name/'receipt.json'
        # This is only a scheduling hint. The canonical reader independently
        # verifies the index/hash/path/config/transaction and inventory below.
        candidate=False
        if receipt.is_file() and not receipt.is_symlink():
            candidate=json.loads(receipt.read_text()).get('config') in covered
        if candidate:
            token=unlocked.set(True)
            try:yield
            finally:unlocked.reset(token)
        else:
            with lock(root,name):yield
    def checked_fresh(*args,**kw):
        result=fresh(*args,**kw)
        if result is None and unlocked.get():raise _RetryLockedReceipt()
        return result
    producer.certification_window_lock=window_lock;producer.fresh_window_source=checked_fresh
    try:yield
    finally:
        producer.certification_window_lock=lock;producer.fresh_window_source=fresh


def _certify_process(item):
    root,key,reviewer,window_workers,receipts,transaction,output,timeout=item
    global _PRODUCER
    start=time.monotonic()
    # Deadlines and descendants remain inside certify_batch's private group.
    # The main process cancels that entire group on failure or timeout.
    def expired(signum,frame):
        print('certification timed out: '+key,file=sys.stderr,flush=True)
        # A producer may be inside a window ThreadPoolExecutor whose cleanup
        # waits for compiler threads. Wake the parent first so its group
        # cancellation stops descendants without waiting for that cleanup.
        os.kill(os.getppid(),signal.SIGTERM)
        raise TimeoutError('certification timed out: '+key)
    previous=signal.signal(signal.SIGALRM,expired)
    signal.alarm(timeout)
    try:
        with output.open('w') as f,contextlib.redirect_stdout(f),contextlib.redirect_stderr(f):
            try:
                if _PRODUCER is None:
                    os.chdir(root)
                    sys.path[:0]=[str(root/'tools'),str(root/'tools/gate')]
                    spec=importlib.util.spec_from_file_location('batch_certificate_producer',root/'tools/fidelity/certify_overlay_module.py')
                    _PRODUCER=importlib.util.module_from_spec(spec);spec.loader.exec_module(_PRODUCER)
                try:
                    with _receipt_parallelism(_PRODUCER,receipts):
                        cert,path=_PRODUCER.certify(key,root/'build_ovl_gate',reviewer,receipts,transaction,window_workers)
                except _RetryLockedReceipt:
                    print('fresh receipt unavailable; retrying with canonical window locks',flush=True)
                    cert,path=_PRODUCER.certify(key,root/'build_ovl_gate',reviewer,receipts,transaction,window_workers)
                print(json.dumps({'module':cert['module'],'members':cert['members'],'certificate':str(path),
                                  'windows':[w['config'] for w in cert['windows']],'result':'CERTIFIED'},indent=2),flush=True)
            except BaseException as e:
                traceback.print_exc()
                raise RuntimeError('certification failed: '+key+'; see '+str(output)) from e
        return {'module':key,'reviewer':reviewer,'seconds':round(time.monotonic()-start,3),'rc':0,'log':str(output)}
    finally:
        signal.alarm(0);signal.signal(signal.SIGALRM,previous)


def invalid_certificates(root, roster, workers=1):
    # Both legacy and scoped readers expose this interface. Import this root's
    # reader in the helper process, never interpret fingerprints here.
    statuses=_statuses(root,workers);seen=set();invalid={}
    for entry in statuses:
        key=entry['module']['key']
        if key in seen:raise ValueError('duplicate module status: '+key)
        seen.add(key)
        if key=='manifest' and not entry['valid']:raise ValueError(entry['reason'])
        if key in roster and not entry['valid']:invalid[key]=entry['reason'] or 'certificate invalid'
    if not set(roster).issubset(seen):raise ValueError('recorded certificate absent from module status: '+str(sorted(set(roster)-seen)))
    return invalid

def _renewal_cost(root,key):
    # Scheduling hint only: every proof is rebuilt/checked canonically. Start
    # many-window certificates first rather than leaving the 20-window TU as
    # a serial tail after the pool's other workers become idle.
    try:
        windows=json.loads((root/'ledger/modules'/('overlay_'+key+'.json')).read_text()).get('windows',[])
        return len(windows),sum(max(0,w['file_end']-w['file_start']) for w in windows)
    except (OSError,ValueError,KeyError,TypeError,AttributeError):return 0,0


def renew(root,workers,window_workers,log_dir,receipts=None,transaction=None,timeout=7200,invalid_only=False,validate_only=False,force_renew=(),worker_mode='subprocess',issue=()):
    roster=jobs(root);log_dir.mkdir(parents=True,exist_ok=True);start=time.monotonic()
    forced=set(force_renew)
    # First certificates: modules absent from the roster whose manifest review
    # is complete. The recorded review.reviewer is the certificate reviewer.
    new={}
    if issue:
        ready,waiting=uncertified(root)
        for key in issue:
            if key in roster:raise ValueError('issue key already has a certificate: '+key)
            if key not in ready:raise ValueError('issue key lacks a complete review or is not a module without a certificate: '+key)
            new[key]=ready[key]
        if validate_only:raise ValueError('issue conflicts with validate-only')
    if forced-set(roster):raise ValueError('forced renewal absent from certificate roster: '+str(sorted(forced-set(roster))))
    if validate_only and forced:raise ValueError('forced renewal conflicts with validate-only')
    invalid=invalid_certificates(root,roster,workers) if invalid_only or validate_only else {}
    if validate_only and invalid:raise ValueError('invalid final certificates: '+json.dumps(invalid,sort_keys=True))
    selected={} if validate_only else {key:reviewer for key,reviewer in roster.items() if not invalid_only or key in invalid or key in forced}
    selected.update(new)
    expected={**roster,**new}
    print(json.dumps({'step':'certificate-selection','validated':len(roster),'renew':sorted(selected),
                      'retain':sorted(set(roster)-set(selected)),'invalid':invalid,'forced':sorted(forced),'issue':sorted(new)}),flush=True)
    launching=threading.Lock();stopping=threading.Event()
    def run(item):
        key,reviewer=item;output=log_dir/(key+'.log');t=time.monotonic()
        argv=[sys.executable,'tools/fidelity/certify_overlay_module.py',key,'--root','build_ovl_gate',
              '--reviewer',reviewer,'--window-workers',str(window_workers)]
        if receipts:argv+=['--gate-receipts',str(receipts),'--transaction',transaction]
        print(json.dumps({'step':'certify-'+key,'command':argv,'output':str(output)}),flush=True)
        with output.open('w') as f:
            # All descendants inherit the helper's group; the lander can stop
            # every compiler before restoring its Snapshot.
            with launching:
                if stopping.is_set():raise RuntimeError('certification cancelled before launch')
                p=subprocess.Popen(argv,cwd=root,stdout=f,stderr=subprocess.STDOUT)
            rc=p.wait(timeout=timeout)
        result={'module':key,'reviewer':reviewer,'seconds':round(time.monotonic()-t,3),'rc':rc,'log':str(output)}
        print(json.dumps(result),flush=True)
        if rc:raise RuntimeError('certification failed: '+key+'; see '+str(output))
        return result
    pool_type=ProcessPoolExecutor if worker_mode=='process' else ThreadPoolExecutor
    options={'mp_context':multiprocessing.get_context('spawn')} if worker_mode=='process' else {}
    with pool_type(max_workers=workers,**options) as pool:
        futures=[];results=[]
        try:
            if worker_mode=='process':
                for key,reviewer in sorted(selected.items(),key=lambda item:_renewal_cost(root,item[0]),reverse=True):
                    output=log_dir/(key+'.log')
                    print(json.dumps({'step':'certify-'+key,'worker_mode':'process','output':str(output)}),flush=True)
                    futures.append(pool.submit(_certify_process,(root,key,reviewer,window_workers,receipts,transaction,output,timeout)))
            else:
                for item in selected.items():futures.append(pool.submit(run,item))
            for f in as_completed(futures):
                result=f.result();results.append(result)
                if worker_mode=='process':print(json.dumps(result),flush=True)
        except BaseException:
            for f in futures:f.cancel()
            # main establishes a private group even when used standalone.
            with launching:
                stopping.set();signal.signal(signal.SIGTERM,signal.SIG_DFL)
                os.killpg(os.getpgrp(),signal.SIGTERM)
            raise
    if jobs(root)!=expected:raise ValueError('certificate identities/reviewers changed during renewal')
    if invalid_only:
        final_invalid=invalid_certificates(root,expected,workers)
        if final_invalid:raise ValueError('invalid certificates after renewal: '+json.dumps(final_invalid,sort_keys=True))
    summary={'result':'PASS','workers':workers,'window_workers':window_workers,'worker_mode':worker_mode,'seconds':round(time.monotonic()-start,3),
             'certificates':sorted(results,key=lambda r:r['module']),'validated':len(roster),'issued':sorted(new),
             'retained':sorted(set(roster)-set(selected)),'invalid_before':invalid,'forced':sorted(forced)}
    (log_dir/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print(json.dumps(summary),flush=True)
    return summary

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--root',required=True,type=Path)
    ap.add_argument('--workers',required=True,type=int);ap.add_argument('--window-workers',type=int,default=1)
    ap.add_argument('--log-dir',required=True,type=Path);ap.add_argument('--gate-receipts',type=Path);ap.add_argument('--transaction')
    ap.add_argument('--timeout',type=int,default=7200)
    ap.add_argument('--worker-mode',choices=('subprocess','process'),default='subprocess',
                    help='persistent certificate interpreters or legacy one subprocess per module')
    mode=ap.add_mutually_exclusive_group();mode.add_argument('--invalid-only',action='store_true');mode.add_argument('--validate-only',action='store_true')
    ap.add_argument('--renew',action='append',default=[],help='force renewal of a new or transaction-changed certificate (repeatable)')
    ap.add_argument('--issue',action='append',default=[],help='issue a FIRST certificate for a reviewed module that has none (repeatable; reviewer = its manifest review.reviewer)')
    a=ap.parse_args()
    if min(a.workers,a.window_workers,a.timeout)<1 or bool(a.gate_receipts)!=bool(a.transaction):ap.error('positive worker counts/timeouts and a receipt directory/token pair are required')
    if os.getpgrp()!=os.getpid():os.setsid()
    def interrupted(signum,frame):raise RuntimeError('certification interrupted by signal '+str(signum))
    signal.signal(signal.SIGTERM,interrupted)
    try:renew(a.root.resolve(),a.workers,a.window_workers,a.log_dir.resolve(),a.gate_receipts,a.transaction,a.timeout,a.invalid_only,a.validate_only,a.renew,a.worker_mode,a.issue)
    except Exception as e:
        print(str(e),file=sys.stderr,flush=True);signal.signal(signal.SIGTERM,signal.SIG_DFL);os.killpg(os.getpgrp(),signal.SIGTERM)
        return 1
    return 0

if __name__=='__main__':raise SystemExit(main())
