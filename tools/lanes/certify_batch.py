#!/usr/bin/env python3
"""Validate recorded certificates and renew selected ones in a cancellable group."""
import argparse
from concurrent.futures import ThreadPoolExecutor,as_completed
import json
import os
from pathlib import Path
import signal
import subprocess
import sys
import time
import threading

def jobs(root):
    result={}
    for p in sorted((root/'ledger/modules').glob('overlay_*.json')):
        rec=json.loads(p.read_text());key=rec.get('module');reviewer=rec.get('reviewer')
        if not key or p.name!='overlay_'+key+'.json' or not reviewer or reviewer=='pending':
            raise ValueError('invalid live certificate: '+str(p))
        result[key]=reviewer
    return result

def invalid_certificates(root, roster):
    # Both legacy and scoped readers expose this interface. Import this root's
    # reader in the helper process, never interpret fingerprints here.
    sys.path[:0]=[str(root/'tools'),str(root/'tools/gate')]
    from overlay_module_evidence import module_status
    statuses=module_status(root);seen=set();invalid={}
    for entry in statuses:
        key=entry['module']['key']
        if key in seen:raise ValueError('duplicate module status: '+key)
        seen.add(key)
        if key=='manifest' and not entry['valid']:raise ValueError(entry['reason'])
        if key in roster and not entry['valid']:invalid[key]=entry['reason'] or 'certificate invalid'
    if not set(roster).issubset(seen):raise ValueError('recorded certificate absent from module status: '+str(sorted(set(roster)-seen)))
    return invalid

def renew(root,workers,window_workers,log_dir,receipts=None,transaction=None,timeout=7200,invalid_only=False,validate_only=False,force_renew=()):
    roster=jobs(root);log_dir.mkdir(parents=True,exist_ok=True);start=time.monotonic()
    forced=set(force_renew)
    if forced-set(roster):raise ValueError('forced renewal absent from certificate roster: '+str(sorted(forced-set(roster))))
    if validate_only and forced:raise ValueError('forced renewal conflicts with validate-only')
    invalid=invalid_certificates(root,roster) if invalid_only or validate_only else {}
    if validate_only and invalid:raise ValueError('invalid final certificates: '+json.dumps(invalid,sort_keys=True))
    selected={} if validate_only else {key:reviewer for key,reviewer in roster.items() if not invalid_only or key in invalid or key in forced}
    print(json.dumps({'step':'certificate-selection','validated':len(roster),'renew':sorted(selected),
                      'retain':sorted(set(roster)-set(selected)),'invalid':invalid,'forced':sorted(forced)}),flush=True)
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
    with ThreadPoolExecutor(max_workers=workers) as pool:
        futures=[pool.submit(run,item) for item in selected.items()];results=[]
        try:
            for f in as_completed(futures):results.append(f.result())
        except BaseException:
            for f in futures:f.cancel()
            # main establishes a private group even when used standalone.
            with launching:
                stopping.set();signal.signal(signal.SIGTERM,signal.SIG_DFL)
                os.killpg(os.getpgrp(),signal.SIGTERM)
            raise
    if jobs(root)!=roster:raise ValueError('certificate identities/reviewers changed during renewal')
    if invalid_only:
        final_invalid=invalid_certificates(root,roster)
        if final_invalid:raise ValueError('invalid certificates after renewal: '+json.dumps(final_invalid,sort_keys=True))
    summary={'result':'PASS','workers':workers,'window_workers':window_workers,'seconds':round(time.monotonic()-start,3),
             'certificates':sorted(results,key=lambda r:r['module']),'validated':len(roster),
             'retained':sorted(set(roster)-set(selected)),'invalid_before':invalid,'forced':sorted(forced)}
    (log_dir/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print(json.dumps(summary),flush=True)
    return summary

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--root',required=True,type=Path)
    ap.add_argument('--workers',required=True,type=int);ap.add_argument('--window-workers',type=int,default=1)
    ap.add_argument('--log-dir',required=True,type=Path);ap.add_argument('--gate-receipts',type=Path);ap.add_argument('--transaction')
    ap.add_argument('--timeout',type=int,default=7200)
    mode=ap.add_mutually_exclusive_group();mode.add_argument('--invalid-only',action='store_true');mode.add_argument('--validate-only',action='store_true')
    ap.add_argument('--renew',action='append',default=[],help='force renewal of a new or transaction-changed certificate (repeatable)')
    a=ap.parse_args()
    if min(a.workers,a.window_workers,a.timeout)<1 or bool(a.gate_receipts)!=bool(a.transaction):ap.error('positive worker counts/timeouts and a receipt directory/token pair are required')
    if os.getpgrp()!=os.getpid():os.setsid()
    def interrupted(signum,frame):raise RuntimeError('certification interrupted by signal '+str(signum))
    signal.signal(signal.SIGTERM,interrupted)
    try:renew(a.root.resolve(),a.workers,a.window_workers,a.log_dir.resolve(),a.gate_receipts,a.transaction,a.timeout,a.invalid_only,a.validate_only,a.renew)
    except Exception as e:
        print(str(e),file=sys.stderr,flush=True);signal.signal(signal.SIGTERM,signal.SIG_DFL);os.killpg(os.getpgrp(),signal.SIGTERM)
        return 1
    return 0

if __name__=='__main__':raise SystemExit(main())
