#!/usr/bin/env python3
"""Lint one lane package, then replay pending packages and FAST FRONT at HEAD.

Usage: package_preflight.py --root REPO --package APPLY [--arg ARG ...]
       [--pending QUEUE.json] [--log LOG.jsonl]
Queue schema: {"version":1,"packages":[{"entry":"repo-relative/apply.py",
"args":[],"live_flag":true}]}. Missing default queue means an empty queue.
Explicit missing queues fail. Writes occur only in disposable lane/temp storage.
This is an early screen, never a substitute for landing proofs or review.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import time

sys.path.insert(0,str(Path(__file__).resolve().parent))
import land_packages as G

def package_path(base, name):
    return G.safe(base, name)

def lint_inventory(entry, root):
    """Conventional package inventories and HEAD source/protected guards."""
    base=entry.parent
    files=base/'files.json'
    if not files.is_file():raise G.Stop('missing files.json inventory')
    entries=json.loads(files.read_text())
    if not isinstance(entries,list):raise G.Stop('files.json must be a list')
    bound={};inventories=[]
    for name in ('package.sha256.json','records.sha256.json'):
        p=base/name
        if not p.exists():continue
        inventories.append(name)
        data=json.loads(p.read_text())
        if not isinstance(data,dict):raise G.Stop('invalid integrity inventory: '+name)
        for rel,expected in data.items():
            actual=G.digest(package_path(base,rel))
            if actual!=expected:raise G.Stop('stale '+name+': '+rel)
            if rel in bound and bound[rel]!=expected:raise G.Stop('inconsistent integrity inventories: '+rel)
            bound[rel]=expected
    if not inventories:raise G.Stop('missing integrity inventory')
    # files.json itself controls guards and must be fresh when the outer package
    # inventory exists. Older record-only inventories still bind sources below.
    if 'package.sha256.json' in inventories and 'files.json' not in bound:
        raise G.Stop('package.sha256.json does not bind files.json')
    for rec in entries:
        src=package_path(base,rec['file']);dst=G.safe(root,rec['path'])
        if G.digest(src)!=rec['after']:raise G.Stop('packaged source hash differs: '+rec['path'])
        if G.digest(dst)!=rec['before']:
            raise G.Stop('guard != HEAD: '+rec['path']+'; rebase before delivery')
    manifest=base/'manifest.json'
    if manifest.exists():
        for rel,expected in json.loads(manifest.read_text()).get('protected_inputs',{}).items():
            if G.digest(G.safe(root,rel))!=expected:raise G.Stop('protected guard != HEAD: '+rel)
    # Bounded package inputs only; diagnostic logs are not installation inputs.
    candidates={entry,*(package_path(base,r['file']) for r in entries),*(package_path(base,r) for r in bound if not r.startswith('diagnostics/'))}
    candidates.update(p for p in base.iterdir() if p.is_file() and p.suffix in ('.py','.sh','.json','.jsonl','.md'))
    records_dir=base/'records'
    if records_dir.exists():candidates.update(p for p in records_dir.iterdir() if p.is_file())
    flattened={'tools/'+p.name for p in (root/'tools/gate').glob('*.py')}
    installed_sources={package_path(base,r['file']) for r in entries}
    for p in sorted(candidates):
        data=p.read_bytes()
        if ('/'+'home/').encode() in data:raise G.Stop('home-directory absolute path: '+str(p.relative_to(base)))
        if p.suffix in ('.py','.sh') and p not in installed_sources:
            for path in sorted(flattened):
                if path.encode() in data:raise G.Stop('scratch-flattened repository tool path: '+path)
            for tool in ('tools/build/gate_all.py','tools/fidelity/certify_overlay_module.py','tools/build/build_slus.sh','tools/build/mk_ovl_root.sh'):
                if tool.encode() in data:raise G.Stop('package apply invokes proof/build tool: '+tool)
    return {'sources':len(entries),'inventories':inventories,'lint_files':len(candidates)}

def lint_contract(land, entry, args):
    # Relocate into a fake canonical checkout to exercise refusal/--live safely.
    # No call uses the real canonical --root, even if --dry-run is broken.
    facade=land.root/'work/native_lane/contract/package'
    shutil.copytree(entry.parent,facade,ignore=shutil.ignore_patterns('__pycache__'))
    target=facade/entry.name
    argv=([sys.executable] if target.suffix=='.py' else ['bash'])+[str(target)]
    help_log,_=land.run('contract-help',argv+['--help'])
    help_text=help_log.read_text()
    for flag in ('--root','--dry-run','--live'):
        if flag not in help_text:raise G.Stop('missing contract flag: '+flag)
    # Both dry runs must leave tracked/managed inputs byte-identical.
    prefixes=list(G.MANAGED)+list(G.GENERATED)+['STATUS.md']
    before=G.inventory(land.root,prefixes)
    no_live=land.log.parent/(land.log.stem+'.refusal.log')
    env=dict(land.env,LAND_LIVE_ROOT=str(land.root))
    start=time.monotonic()
    with no_live.open('w') as f:
        land.child=subprocess.Popen(argv+['--root',str(land.root),*args,'--dry-run'],cwd=land.root,env=env,stdout=f,stderr=subprocess.STDOUT,start_new_session=True)
        try:rc=land.child.wait(timeout=120)
        except BaseException:land.kill_child();raise
        finally:land.child=None
    message=no_live.read_text()
    if G.inventory(land.root,prefixes)!=before:raise G.Stop('contract dry-run mutated inputs without --live')
    if rc==0 or not any(s in message.lower() for s in ('refus','requires --live','without --live','require --live')):
        raise G.Stop('canonical refusal without --live not demonstrated; see '+str(no_live))
    land.event('contract-refusal',result='PASS',seconds=round(time.monotonic()-start,3))
    try:
        land.run('contract-live-dry-run',argv+['--root',str(land.root),*args,'--live','--dry-run'],env=env,timeout=120)
    finally:
        if G.inventory(land.root,prefixes)!=before:raise G.Stop('contract --live --dry-run mutated inputs')


def pending_packages(root, path=None):
    explicit=path is not None
    path=(path or root/'work/native_lane/_pending_packages.json').resolve()
    if not path.exists():
        if explicit:raise G.Stop('missing pending queue: '+str(path))
        return [],None
    doc=json.loads(path.read_text())
    if not isinstance(doc,dict) or doc.get('version')!=1 or not isinstance(doc.get('packages'),list):
        raise G.Stop('pending queue requires version=1 and packages list')
    out=[]
    for item in doc['packages']:
        if not isinstance(item,dict) or not item.get('entry') or item.get('live_flag') is not True or not isinstance(item.get('args',[]),list):
            raise G.Stop('invalid pending package contract')
        p=G.safe(root,item['entry'])
        if not p.is_file():raise G.Stop('pending entry missing: '+item['entry'])
        out.append({**item,'entry':str(p)})
    return out,hashlib.sha256(path.read_bytes()).hexdigest()


def preflight(root, entry, args, pending, log):
    root=root.resolve();entry=entry.resolve();log=log.resolve();log.parent.mkdir(parents=True,exist_ok=True)
    land=None
    with tempfile.TemporaryDirectory(prefix='package_preflight-',dir=log.parent) as temp:
        base=Path(temp);seed=base/'seed';view=base/'tree'
        try:
            queue,queue_sha=pending_packages(root,pending)
            subprocess.run(['git','clone','--shared','--no-checkout','--',str(root),str(seed)],check=True,capture_output=True)
            head=G.git(seed,'rev-parse','HEAD').decode().strip()
            G.git(seed,'worktree','add','--detach',str(view),head)
            G.copy_preflight_inputs(root,view)
            plan={'version':1,'reviewer':'pending','commit':False,'commit_message':'package preflight','packages':[]}
            land=G.Lander(view,plan,entry.parent,log,scratch=True)
            land.env['TMPDIR']=str(view/'tmp')
            land.preflight()
            result=lint_inventory(entry,view)
            land.event('inventory-head-lint',head=head,queue_sha256=queue_sha,**result)
            lint_contract(land,entry,args)
            # Record guards are exercised at untouched HEAD by the contract dry run.
            # Then replay ALL pending inputs in order before the candidate.
            plan['packages']=queue+[{'entry':str(entry),'args':args,'live_flag':True}]
            if any(Path(p['entry']).resolve()==entry for p in queue):
                raise G.Stop('candidate already queued; remove duplicate candidate for this check')
            land.mutate();land.normalise_review();land.regenerate();land.fast_front()
            # Detect a queue changed by another lane during the screen.
            _,after=pending_packages(root,pending)
            if after!=queue_sha:raise G.Stop('pending queue changed during preflight; rerun against the new queue')
            if G.git(root,'rev-parse','HEAD').decode().strip()!=head:raise G.Stop('source HEAD changed during preflight; rerun')
            land.event('PACKAGE_PREFLIGHT_PASS',head=head,pending=len(queue),reviewer='pending',message='append candidate to pending queue; landing proofs required')
            return 0
        except BaseException as e:
            if land:
                land.kill_child();land.event('STOP',error=str(e),rollback='disposable worktree removed')
            else:print('STOP: '+str(e),file=sys.stderr)
            return 1
        finally:
            if seed.exists() and view.exists():G.git(seed,'worktree','remove','--force',str(view))


def main(argv=None):
    ap=argparse.ArgumentParser(description=__doc__,formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root',required=True,type=Path);ap.add_argument('--package',required=True,type=Path)
    ap.add_argument('--arg',action='append',default=[]);ap.add_argument('--pending',type=Path)
    ap.add_argument('--log',type=Path,default=Path(tempfile.gettempdir())/('package-preflight-'+str(time.time_ns())+'.jsonl'))
    a=ap.parse_args(argv)
    if a.log.resolve().is_relative_to(a.root.resolve()):ap.error('--log must be outside the source checkout')
    with G.stop_signals():return preflight(a.root,a.package,a.arg,a.pending,a.log)

if __name__=='__main__':raise SystemExit(main())
