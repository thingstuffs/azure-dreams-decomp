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
import ast
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
        doc=json.loads(manifest.read_text());aliases={**doc.get('protected_links',{}),**doc.get('protected_aliases',{})}
        for rel,target in aliases.items():
            p=root/rel
            if not p.is_symlink() or not p.resolve().is_relative_to(root):raise G.Stop('protected proof-tool alias differs: '+rel)
            expected=p.parent/target if rel in doc.get('protected_links',{}) else root/target
            if p.resolve()!=expected.resolve() or (rel in doc.get('protected_links',{}) and os.readlink(p)!=target):raise G.Stop('protected proof-tool alias differs: '+rel)
        for rel,expected in doc.get('protected_inputs',{}).items():
            p=root/rel
            if rel in aliases:p=p.resolve()
            else:p=G.safe(root,rel)
            if G.digest(p)!=expected:raise G.Stop('protected guard != HEAD: '+rel)
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



def possible_package_writes(entry):
    """Advisory only: bounded Python path assignments and explicit write calls.

    Record appliers can write rowbase/configure without a whole-file inventory
    guard. This explains their dependencies; it never authorizes a mutation or
    substitutes for a package's actual guards and dry run.
    """
    entry=Path(entry)
    if entry.suffix!='.py':entry=entry.parent/'apply.py'
    if not entry.is_file() or entry.stat().st_size>4*1024*1024:return set()
    try:tree=ast.parse(entry.read_text())
    except (SyntaxError,UnicodeError):return set()
    variables={};paths=set()
    def value(node):
        if isinstance(node,ast.Constant) and isinstance(node.value,str):return node.value
        if isinstance(node,ast.Name):return variables.get(node.id)
        if isinstance(node,ast.BinOp) and isinstance(node.op,ast.Div):
            right=value(node.right);left=value(node.left)
            return str(Path(left)/right) if left and right else right
        if isinstance(node,ast.Call):
            for arg in node.args:
                candidate=value(arg)
                if candidate and Path(candidate).parts and Path(candidate).parts[0] in G.MANAGED:return candidate
        return None
    for node in ast.walk(tree):
        if isinstance(node,ast.Assign):
            for target in node.targets:
                if isinstance(target,ast.Name):variables[target.id]=value(node.value)
        if isinstance(node,ast.Call) and isinstance(node.func,ast.Attribute):
            writing=node.func.attr in ('write_text','write_bytes') or (node.func.attr=='open' and node.args and isinstance(node.args[0],ast.Constant) and any(c in str(node.args[0].value) for c in 'wax+'))
            if writing:
                rel=value(node.func.value)
                if rel and not Path(rel).is_absolute() and '..' not in Path(rel).parts and Path(rel).parts[0] in G.MANAGED:paths.add(rel)
    return paths

def package_dependencies(package, root=None):
    base=Path(package['entry']).parent
    inventory=base/'files.json';manifest=base/'manifest.json'
    writes={r['path']:{**r,'guarded':True} for r in json.loads(inventory.read_text())} if inventory.is_file() else {}
    doc=json.loads(manifest.read_text()) if manifest.is_file() else {}
    reads=dict(doc.get('protected_inputs',{}))
    for rel in doc.get('mutates',[]):writes.setdefault(rel,{'guarded':False})
    for rel in possible_package_writes(package['entry']):writes.setdefault(rel,{'guarded':False,'inferred':True})
    aliases={**doc.get('protected_links',{}),**doc.get('protected_aliases',{})}
    for alias,target in aliases.items():
        if not isinstance(target,str):raise G.Stop('invalid protected alias: '+alias)
        # protected_links stores readlink text; protected_aliases stores a
        # repository-relative target. Neither may resolve outside the tree.
        rel=os.path.normpath(str(Path(alias).parent/target)) if alias in doc.get('protected_links',{}) else os.path.normpath(target)
        if Path(rel).is_absolute() or '..' in Path(rel).parts:raise G.Stop('unsafe protected alias: '+alias)
        reads.setdefault(rel,None);reads.setdefault(alias,None)
    if root is not None:
        for rel,expected in list(reads.items()):
            p=root/rel
            if p.is_symlink():
                target=p.resolve()
                if not target.is_relative_to(root):raise G.Stop('protected alias escapes tree: '+rel)
                reads.setdefault(target.relative_to(root).as_posix(),expected)
    return writes,reads

def ordering_hints(packages, root=None):
    deps=[package_dependencies(p,root) for p in packages];edges=set();conflicts=[]
    for a,(aw,ar) in enumerate(deps):
        for b,(bw,br) in enumerate(deps):
            if a>=b:continue
            for rel in sorted(aw.keys()&bw.keys()):
                if aw[rel].get('guarded') and bw[rel].get('guarded'):
                    conflicts.append({'path':rel,'packages':[a,b],'kind':'two writers','action':'combine and re-prove; ordering cannot reconcile two full-file write guards'})
            for writer,reader,writes,reads in ((a,b,aw,br),(b,a,bw,ar)):
                for rel in sorted(writes.keys()&reads.keys()):
                    expected=reads[rel];rec=writes[rel]
                    if expected is not None and expected==rec.get('after') and expected!=rec.get('before'):
                        first,last=writer,reader
                    else:first,last=reader,writer
                    edges.add((first,last))
                    inferred=rec.get('inferred',False)
                    conflicts.append({'path':rel,'packages':[reader,writer],'kind':('possible write to ' if inferred else '')+'protected input / proof-tool alias','suggest_before':first,'suggest_after':last,'inferred':inferred,'action':'review this order and replay guards; renew certificates after final inputs'})
    remaining=set(range(len(packages)));order=[]
    while remaining:
        ready=sorted(n for n in remaining if not any(b==n and a in remaining for a,b in edges))
        if not ready:break
        order+=ready;remaining.difference_update(ready)
    return {'conflicts':conflicts,'suggested_order':order if not remaining else None,'cycle':sorted(remaining),
            'entries':[p['entry'] for p in packages]}

def guard_collisions(packages, root=None):
    """A guard is a read dependency too: protected inputs also conflict.

    Idempotent append records have separate contracts and do not conflict merely
    because they append to the same shared ledger. files.json/protected_inputs
    bind complete files. Two writers require a combined package; read dependencies
    must execute in the order their guards require, without any guard override.
    """
    hints=ordering_hints(packages,root)
    blocked=[c for c in hints['conflicts'] if c['kind']=='two writers' or (not c.get('inferred') and c['suggest_before']>c['suggest_after'])]
    if blocked:
        rel=blocked[0]['path']
        raise G.Stop('queued packages guard the same file: '+rel+'; package-order hints: '+json.dumps(hints,sort_keys=True))
    seen={}
    for package in packages:
        writes,reads=package_dependencies(package,root)
        for rel in writes.keys()|reads.keys():seen[rel]=package['entry']
    return seen


def package_tests(packages,view):
    """Use installed canonical test paths, never run from delivery/sources.

    files.json test sources are included automatically. tests.json may add
    unit_modules/discover_patterns for tests already present in the checkout.
    """
    modules=[];patterns=[]
    for package in packages:
        base=Path(package['entry']).parent
        inventory=base/'files.json'
        if inventory.is_file():
            for rec in json.loads(inventory.read_text()):
                rel=rec['path']
                if rel.startswith('tools/tests/test_') and rel.endswith('.py'):
                    patterns.append(Path(rel).name)
        test_spec=base/'tests.json'
        if test_spec.is_file():
            doc=json.loads(test_spec.read_text())
            modules+=doc.get('unit_modules',[]);patterns+=doc.get('discover_patterns',[])
    # Existing lander tests verify the transaction; new lane tests run under
    # discovery so tests which import siblings see the canonical tests path.
    modules=modules or ['tools.tests.test_land_packages']
    patterns=patterns or ['test_land_packages.py']
    return {'unit_modules':list(dict.fromkeys(modules)), 'discover_patterns':list(dict.fromkeys(patterns))}

def package_state(packages):
    """Bind the exact submitted bytes across a long accounting screen."""
    state={}
    for item in packages:
        entry=Path(item['entry']);base=entry.parent
        paths={entry,base/'files.json',base/'tests.json',base/'manifest.json'}
        for name in ('package.sha256.json','records.sha256.json'):
            inventory=base/name;paths.add(inventory)
            if inventory.is_file():paths.update(package_path(base,p) for p in json.loads(inventory.read_text()))
        if (base/'files.json').is_file():paths.update(package_path(base,r['file']) for r in json.loads((base/'files.json').read_text()))
        state[str(entry)]={str(p.relative_to(base)):G.digest(p) for p in sorted(paths)}
    return state

def preflight(root, entry, args, pending, log):
    root=root.resolve();entry=entry.resolve();log=log.resolve();log.parent.mkdir(parents=True,exist_ok=True)
    land=None
    with tempfile.TemporaryDirectory(prefix='package_preflight-',dir=log.parent) as temp:
        base=Path(temp);seed=base/'seed';view=base/'tree'
        try:
            dirt=G.tree_dirt(root,{})
            with log.open('a') as f:f.write(json.dumps({'step':'source-tree-dirt',**dirt})+'\n')
            if dirt['refused']:raise G.Stop('dirty tree: '+json.dumps(dirt['refused']))
            queue,queue_sha=pending_packages(root,pending)
            subprocess.run(['git','clone','--shared','--no-checkout','--',str(root),str(seed)],check=True,capture_output=True)
            head=G.git(seed,'rev-parse','HEAD').decode().strip()
            G.git(seed,'worktree','add','--detach',str(view),head)
            G.copy_preflight_inputs(root,view)
            all_packages=queue+[{'entry':str(entry),'args':args,'live_flag':True}]
            hints=ordering_hints(all_packages,view)
            with log.open('a') as f:f.write(json.dumps({'step':'package-order-hints',**hints})+'\n')
            guard_collisions(all_packages,view)
            submitted=package_state(all_packages)
            plan={'version':1,'reviewer':'pending','commit':False,'commit_message':'package preflight','packages':[],
                  **package_tests(all_packages,view)}
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
            land.mutate();land.review_steps();land.normalise_review();land.unit_checks();land.regenerate();land.fast_front()
            if package_state(all_packages)!=submitted:raise G.Stop('package bytes changed during preflight; rerun')
            # Detect a queue changed by another lane during the screen.
            _,after=pending_packages(root,pending)
            if after!=queue_sha:raise G.Stop('pending queue changed during preflight; rerun against the new queue')
            if G.git(root,'rev-parse','HEAD').decode().strip()!=head:raise G.Stop('source HEAD changed during preflight; rerun')
            dirt=G.tree_dirt(root,{})
            if dirt['refused']:raise G.Stop('source tree became dirty during preflight: '+json.dumps(dirt['refused']))
            land.event('PACKAGE_PREFLIGHT_PASS',head=head,pending=len(queue),reviewer='pending',message='append candidate to pending queue; landing proofs required')
            return 0
        except BaseException as e:
            if land:
                land.kill_child();land.event('STOP',error=str(e),rollback='disposable worktree removed')
            else:
                with log.open('a') as f:f.write(json.dumps({'step':'STOP','error':str(e),'rollback':'disposable worktree removed'})+'\n')
                print('STOP: '+str(e),file=sys.stderr)
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
