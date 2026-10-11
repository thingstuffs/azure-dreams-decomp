#!/usr/bin/env python3
"""Renew all recorded certificates concurrently in one cancellable process group."""
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

def renew(root,workers,window_workers,log_dir,receipts=None,transaction=None,timeout=7200):
    roster=jobs(root);log_dir.mkdir(parents=True,exist_ok=True);start=time.monotonic()
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
        futures=[pool.submit(run,item) for item in roster.items()];results=[]
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
    summary={'result':'PASS','workers':workers,'window_workers':window_workers,'seconds':round(time.monotonic()-start,3),
             'certificates':sorted(results,key=lambda r:r['module'])}
    (log_dir/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print(json.dumps(summary),flush=True)
    return summary

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--root',required=True,type=Path)
    ap.add_argument('--workers',required=True,type=int);ap.add_argument('--window-workers',type=int,default=1)
    ap.add_argument('--log-dir',required=True,type=Path);ap.add_argument('--gate-receipts',type=Path);ap.add_argument('--transaction')
    ap.add_argument('--timeout',type=int,default=7200)
    a=ap.parse_args()
    if min(a.workers,a.window_workers,a.timeout)<1 or bool(a.gate_receipts)!=bool(a.transaction):ap.error('positive worker counts/timeouts and a receipt directory/token pair are required')
    if os.getpgrp()!=os.getpid():os.setsid()
    def interrupted(signum,frame):raise RuntimeError('certification interrupted by signal '+str(signum))
    signal.signal(signal.SIGTERM,interrupted)
    try:renew(a.root.resolve(),a.workers,a.window_workers,a.log_dir.resolve(),a.gate_receipts,a.transaction,a.timeout)
    except Exception as e:
        print(str(e),file=sys.stderr,flush=True);signal.signal(signal.SIGTERM,signal.SIG_DFL);os.killpg(os.getpgrp(),signal.SIGTERM)
        return 1
    return 0

if __name__=='__main__':raise SystemExit(main())
