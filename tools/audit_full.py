#!/usr/bin/env python3
"""Quiet-time full audits in immutable disposable commit snapshots.

Landings only enqueue commit IDs (default every ten landings). Run --drain from
cron/systemd in quiet time. No worker is launched or awaited by the lander.
The worker never checks out or resets the live tree and never creates commits.
"""
from __future__ import annotations
import argparse
import fcntl
import io
import json
import os
from pathlib import Path
import shutil
import signal
import subprocess
import sys
import tarfile
import tempfile
import time


def git(root,*args):
    return subprocess.check_output(['git',*args],cwd=root,text=True).strip()


def atomic(path,doc):
    path=Path(path);path.parent.mkdir(parents=True,exist_ok=True)
    temp=path.with_suffix('.tmp');temp.write_text(json.dumps(doc,indent=2,sort_keys=True)+'\n');temp.replace(path)


def record_landing(root,commit,every=10,queue=None):
    if not isinstance(every,int) or isinstance(every,bool) or every<1:raise ValueError('audit cadence must be a positive integer')
    root=Path(root).resolve()
    commit=git(root,'rev-parse','--verify',commit+'^{commit}')
    queue=Path(queue) if queue else Path(git(root,'rev-parse','--absolute-git-dir'))/'full_audits'
    queue.mkdir(parents=True,exist_ok=True)
    with (queue/'queue.lock').open('a') as lock:
        fcntl.flock(lock,fcntl.LOCK_EX)
        path=queue/'state.json'
        state=json.loads(path.read_text()) if path.exists() else dict(version=1,count=0,landings=[])
        if commit in state['landings']:return None
        state['count']+=1;state['landings'].append(commit)
        # Keep a bounded deduplication window; the monotone count is durable.
        state['landings']=state['landings'][-1000:]
        due=state['count']%every==0
        if due:
            atomic(queue/'requests'/(commit+'.json'),dict(commit=commit,landing=state['count'],at=time.time()))
        atomic(path,state)
    return dict(commit=commit,count=state['count'],queued=due,queue=str(queue))


def stages(root,workers):
    py=sys.executable
    return [('slus',['bash','tools/build/build_slus.sh','--fresh','-j',str(workers)]),
            ('view',['bash','tools/build/mk_ovl_root.sh']),
            ('row-db',[py,'tools/row_db.py','check']),
            ('gate-all',[py,'tools/build/gate_all.py','--all','--workers',str(workers)]),
            # Rebuild durable artifacts from the audited commit. Historical
            # ephemeral proof directories are not evidence of a bad commit.
            ('certify-all',[py,'tools/lanes/certify_batch.py','--root',str(root),'--workers',str(workers),
                            '--worker-mode','process','--log-dir',str(root/'work/audit_certificates')]),
            ('certificate-validation',[py,'tools/lanes/certify_batch.py','--root',str(root),'--workers',str(workers),
                                       '--log-dir',str(root/'work/audit_validation'),'--validate-only']),
            ('cold-levels',[py,'tools/levels.py']),('cold-status',[py,'tools/status.py']),
            ('row-db-final',[py,'tools/row_db.py','check'])]


def snapshot(source,commit,dest):
    """Extract tracked inputs without writing the source index or worktree."""
    archive=subprocess.check_output(['git','archive','--format=tar',commit],cwd=source)
    with tarfile.open(fileobj=io.BytesIO(archive),mode='r:') as tar:
        for m in tar.getmembers():
            p=Path(m.name)
            if p.is_absolute() or '..' in p.parts or m.islnk():
                raise ValueError('audit archive contains an unsafe tracked input: '+m.name)
            if m.issym():
                target=Path(m.linkname)
                resolved=(dest/p.parent/target).resolve()
                if target.is_absolute() or not resolved.is_relative_to(dest.resolve()):
                    raise ValueError('audit archive link escapes snapshot: '+m.name)
        # The data filter also checks links against already extracted parents;
        # internal tool shims remain internal to the immutable snapshot.
        tar.extractall(dest,filter='data')
    for name in ('.venv','bin','baserom'):
        p=source/name
        if p.exists() and not (dest/name).exists():(dest/name).symlink_to(p.resolve(),target_is_directory=p.is_dir())
    # Share immutable binaries, but use the audited assembler Python source.
    toolchain=source/'toolchain'
    if toolchain.exists():
        target=dest/'toolchain'
        if target.is_symlink():raise ValueError('tracked toolchain alias is unsupported')
        target.mkdir(exist_ok=True)
        for p in toolchain.iterdir():
            q=target/p.name
            if q.exists():continue
            actual=dest/'tools/maspsx' if p.name=='maspsx' and (dest/'tools/maspsx').is_dir() else p.resolve()
            q.symlink_to(actual,target_is_directory=actual.is_dir())
    for name in ('containers','extract'):
        p=source/'work/disc'/name
        if not p.exists():raise ValueError('audit retail resource missing: '+name)
        q=dest/'work/disc'/name;q.parent.mkdir(parents=True,exist_ok=True);q.symlink_to(p.resolve(),target_is_directory=True)


def execute(argv,root,env,stream,timeout=14400):
    child=subprocess.Popen(argv,cwd=root,env=env,stdout=stream,stderr=subprocess.STDOUT,start_new_session=True)
    try:return child.wait(timeout=timeout)
    except BaseException:
        try:os.killpg(child.pid,signal.SIGTERM)
        except ProcessLookupError:pass
        try:child.wait(timeout=5)
        except subprocess.TimeoutExpired:
            try:os.killpg(child.pid,signal.SIGKILL)
            except ProcessLookupError:pass
            child.wait()
        raise


def run_commit(source,commit,out,workers=8):
    source=Path(source);out=Path(out);out.mkdir(parents=True,exist_ok=False)
    result=dict(commit=commit,result='ERROR',stages=[])
    try:
        with tempfile.TemporaryDirectory(prefix='azure-audit-') as td:
            root=Path(td).resolve()
            if root.is_relative_to(source.resolve()):raise ValueError('audit scratch must be outside source; set TMPDIR to an external private directory')
            snapshot(source,commit,root)
            tmp=root/'work/audit_tmp';tmp.mkdir(parents=True)
            env=dict(os.environ,PYTHONDONTWRITEBYTECODE='1',TMPDIR=str(tmp),
                     AZURE_ROW_CACHE='0',GATE_BUILD_ROOT='build_ovl_gate',EXP='gate',SRCROOT=str(root/'src'))
            for key in ('LAND_SKIP_PACKAGE_PROOF','LAND_PACKAGE_PROOF_CONTEXT','GATE_JOURNAL'):
                env.pop(key,None)
            for label,argv in stages(root,workers):
                start=time.monotonic();log=root/'work/audit_stage_logs'/(label+'.log');log.parent.mkdir(parents=True,exist_ok=True)
                try:
                    with log.open('w') as f:rc=execute(argv,root,env,f)
                finally:
                    if log.is_file():shutil.copy2(log,out/(label+'.log'))
                result['stages'].append(dict(stage=label,rc=rc,seconds=round(time.monotonic()-start,3)))
                if rc:
                    result.update(result='FAIL',failed_stage=label);break
            else:result['result']='PASS'
            # Preserve the cold reports before deleting the snapshot.
            for name in ('STATUS.md','ledger/levels.jsonl','ledger/gate.jsonl'):
                p=root/name
                if p.is_file():shutil.copy2(p,out/p.name)
    except (OSError,ValueError,subprocess.SubprocessError,tarfile.TarError) as e:
        result.update(result='ERROR',error=type(e).__name__+': '+str(e))
    atomic(out/'result.json',result)
    return result


def bisect_first(commits,check):
    """First-parent prefix bisection; ERROR never becomes a byte-failure verdict.

    Caller supplies known-good first and known-bad last. Verify the entire
    earlier first-parent prefix after binary narrowing, including nonmonotone
    histories (a bad commit can be temporarily repaired and later broken).
    """
    if len(commits)<2:raise ValueError('bisection needs good and bad endpoints')
    lo,hi=0,len(commits)-1;tested={commits[0]:'PASS',commits[-1]:'FAIL'}
    while hi-lo>1:
        mid=(lo+hi)//2;value=check(commits[mid]);tested[commits[mid]]=value
        if value=='ERROR':return dict(result='HOLD',error_commit=commits[mid],tested=tested)
        if value=='PASS':lo=mid
        elif value=='FAIL':hi=mid
        else:raise ValueError('unknown audit verdict')
    # Reverts/repairs can make history nonmonotone. Scan the untested prefix
    # before claiming FIRST bad; this is quiet-time work, not landing latency.
    for i in range(1,hi):
        value=tested.get(commits[i])
        if value is None:value=check(commits[i]);tested[commits[i]]=value
        if value=='ERROR':return dict(result='HOLD',error_commit=commits[i],tested=tested)
        if value=='FAIL':hi=i;break
    return dict(result='BISECTED',last_good=commits[hi-1],first_bad=commits[hi],tested=tested,
                first_parent_prefix_verified=True)


def drain(root,queue,workers=8):
    root=Path(root);queue=Path(queue);queue.mkdir(parents=True,exist_ok=True)
    with (queue/'worker.lock').open('a') as lock:
        try:fcntl.flock(lock,fcntl.LOCK_EX|fcntl.LOCK_NB)
        except BlockingIOError:return []
        results=[]
        for request in sorted((queue/'requests').glob('*.json'),key=lambda p:p.stat().st_mtime_ns):
            req=json.loads(request.read_text());commit=req['commit']
            # Validate a full commit identity; JSON must not inject git flags.
            if git(root,'rev-parse','--verify',commit+'^{commit}')!=commit:raise ValueError('audit commit changed')
            stamp=str(time.time_ns());directory=queue/'reports'/(commit+'-'+stamp)
            result=run_commit(root,commit,directory,workers)
            prior=queue/'last-good.json'
            if result['result']=='PASS':atomic(prior,dict(commit=commit))
            elif result['result']=='FAIL' and prior.exists():
                good=json.loads(prior.read_text())['commit']
                chain=git(root,'rev-list','--first-parent','--reverse',good+'..'+commit).splitlines()
                ancestry=git(root,'rev-list','--first-parent',commit).splitlines()
                if good in ancestry and chain and chain[-1]==commit:
                    def check(c):return run_commit(root,c,directory/'bisect'/c,workers)['result']
                    endpoint=run_commit(root,good,directory/'last-good-recheck',workers)
                    if endpoint['result']!='PASS':
                        result['bisect']=dict(result='HOLD',reason='known-good commit fails in current environment',endpoint=endpoint)
                    else:result['bisect']=bisect_first([good,*chain],check)
                else:result['bisect']=dict(result='HOLD',reason='no known-good first-parent ancestor')
            elif result['result']=='FAIL':result['bisect']=dict(result='HOLD',reason='no previous successful audit endpoint')
            atomic(directory/'result.json',result)
            report=['# Full audit '+commit,'', 'Result: '+result['result'], '']
            if 'failed_stage' in result:report.append('Failed stage: '+result['failed_stage'])
            if 'error' in result:report.append('Infrastructure error: '+result['error'])
            if 'bisect' in result:report.extend(['','Bisection:','```json',json.dumps(result['bisect'],indent=2),'```'])
            (directory/'REPORT.md').write_text('\n'.join(report)+'\n')
            results.append(result)
            done=queue/'done';done.mkdir(exist_ok=True);request.replace(done/request.name)
        return results


def main(argv=None):
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--root',type=Path,required=True)
    ap.add_argument('--queue',type=Path);ap.add_argument('--every',type=int,default=10)
    ap.add_argument('--workers',type=int,default=8);ap.add_argument('--record',metavar='COMMIT')
    ap.add_argument('--once',metavar='COMMIT');ap.add_argument('--output',type=Path);ap.add_argument('--drain',action='store_true')
    a=ap.parse_args(argv);root=a.root.resolve()
    if a.workers<1 or a.every<1:ap.error('workers and cadence must be positive')
    if sum(bool(x) for x in (a.record,a.once,a.drain))!=1:ap.error('choose --record, --once or --drain')
    if a.record:result=record_landing(root,a.record,a.every,a.queue)
    elif a.once:
        if a.output is None:ap.error('--once requires a new --output directory')
        commit=git(root,'rev-parse','--verify',a.once+'^{commit}');result=run_commit(root,commit,a.output,a.workers)
    else:
        queue=a.queue or Path(git(root,'rev-parse','--absolute-git-dir'))/'full_audits'
        result=drain(root,queue,a.workers)
    print(json.dumps(result,indent=2))
    if isinstance(result,list):return 0 if all(r.get('result')=='PASS' for r in result) else 1
    return 0 if not isinstance(result,dict) or result.get('result','PASS')=='PASS' else 1

if __name__=='__main__':raise SystemExit(main())
