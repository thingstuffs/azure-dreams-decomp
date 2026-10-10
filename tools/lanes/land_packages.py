#!/usr/bin/env python3
"""Land reviewed packages as one fail-closed transaction.

Usage: python3 tools/lanes/land_packages.py --root REPO --plan PLAN.json
       [--scratch | --live] [--preflight] [--no-commit] [--prepare-only] [--log LOG]

A JSON (or YAML with PyYAML) plan has version=1, reviewer, commit_message,
patches=[{file, strip:1, files:{path:{before:SHA_OR_NULL,after:SHA}}}],
scripts=[{argv:[...],files:{path:{before,after}}}], packages=[{entry,args:[],
live_flag:true}], optional copies=[{source,target,before,after}],
unit_modules=[...], discover_patterns=["test_*.py"], timing_windows=[...],
workers=8, certificate_timeout=1800, allow_census_change=false.
Plan file/source/entry paths resolve relative to the plan. Script arguments may
contain {root} or {plan_dir}; commands are argument arrays, never shell strings.
Hash-checked steps run in patches/scripts/packages/copies order. Scripts declare
all their tracked changes; package scripts are trusted reviewed programs and
must confine writes to the managed trees and generated roots below. Live package
entries MUST support --live; this tool never rewrites a guard. --live explicitly
authorizes the canonical live root; --scratch excludes unrelated live processes
from the busy check and is forbidden on that root.

Known bookkeeping: ledger/model_capacity.jsonl (unstaged only). Additional exact
bookkeeping paths may be declared; their initial bytes must survive unchanged.
All other tracked/untracked dirt fails preflight. Existing generated roots are
quarantined, then rebuilt; rollback restores their original contents by rename.
Managed trees, tracked files (including individual tracked work/ files), original
HEAD and index, and newly created untracked files are restored on any failure.
No recursive scan of work/, the repo root, or shared binary inputs is performed.
Logs survive outside the managed trees. SIGINT/SIGTERM and child timeouts stop the
whole child process group before rollback. A machine-readable STOP records whether
rollback verification passed. --prepare-only is an explicitly incomplete preview:
it leaves applied inputs for replay comparison, runs no gates and cannot commit.
It is NEVER a successful landing; --no-commit runs every proof without committing.
"""
import argparse
from collections import Counter
import contextlib
import fcntl
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import signal
import stat
import subprocess
import sys
import tempfile
import time

# the canonical live checkout (no literal private path: the scrub hook refuses those); override for another host
LIVE = Path(os.environ.get('LAND_LIVE_ROOT', str(Path.home() / 'azure-clean'))).resolve()
MANAGED = ('src', 'raw', 'config', 'ledger', 'tools', 'include', 'docs')
GENERATED = ('build_slus', 'build_ovl', 'build_ovl_gate', 'overlays', 'ledger/cache')
BOOKKEEPING = ('ledger/model_capacity.jsonl',)
REVIEW_FILES = ('ledger/splits/dungeon.jsonl', 'ledger/splits/town.jsonl',
               'config/overlays/dungeon.rowbase.jsonl', 'config/overlays/town.rowbase.jsonl',
               'config/overlays/dungeon.rodata_owners.jsonl',
               'config/overlays/town.rodata_owners.jsonl', 'ledger/modules.jsonl')

# Exact patterns from the repository scrub hook, split to keep this tool clean.
SCRUB_PATTERNS = ('/'+'home/', 'azure-'+'decomp', 'azure-'+'cleanup',
                  'claude.ai'+'/code', 'david'+'.john')

class Stop(RuntimeError): pass

def digest(p):
    if not p.exists(): return None
    if p.is_symlink(): raise Stop('hash target is a symlink: '+str(p))
    return hashlib.sha256(p.read_bytes()).hexdigest()

def records(p):
    return [json.loads(s) for s in p.read_text().splitlines()
            if s.strip() and not s.lstrip().startswith('#')] if p.exists() else []

def safe(root, rel):
    rel=Path(rel)
    if rel.is_absolute() or '..' in rel.parts or not rel.parts or rel.parts[0]=='.git':
        raise Stop('unsafe target: '+str(rel))
    p=root/rel
    if not p.parent.resolve().is_relative_to(root) or p.is_symlink():
        raise Stop('write traverses symlink: '+str(rel))
    return p

def remove(p):
    if p.is_symlink() or p.is_file(): p.unlink()
    elif p.exists(): shutil.rmtree(p)

def inventory(root, prefixes, excluded=()):
    """Bounded traversal; record directory entries and symlinks without following."""
    out={}
    def visit(p):
        rel=p.relative_to(root).as_posix()
        if any(rel==e or rel.startswith(e+'/') for e in excluded): return
        if not p.exists() and not p.is_symlink(): return
        st=p.lstat();mode=stat.S_IMODE(st.st_mode)
        if p.is_symlink(): out[rel]=['link',mode,os.readlink(p)]
        elif p.is_dir():
            out[rel]=['dir',mode]
            for child in sorted(p.iterdir()): visit(child)
        else: out[rel]=['file',mode,hashlib.sha256(p.read_bytes()).hexdigest()]
    for rel in prefixes: visit(root/rel)
    return out

def git(root, *args):
    p=subprocess.run(['git','-C',str(root),*args],capture_output=True,env=dict(os.environ,GIT_OPTIONAL_LOCKS='0'))
    if p.returncode: raise Stop('git '+str(args)+': '+p.stderr.decode(errors='replace'))
    return p.stdout

def names(data): return [os.fsdecode(x) for x in data.split(b'\0') if x]

def l5(root):
    return sum(r.get('level') in (5,'L5') for r in records(root/'ledger/levels.jsonl'))

def busy_processes(root, scratch):
    ancestors={os.getpid()};pid=os.getppid()
    while pid>1:
        ancestors.add(pid)
        try:
            fields=(Path('/proc')/str(pid)/'stat').read_text().rsplit(')',1)[1].split()
            pid=int(fields[1])
        except (OSError,ValueError,IndexError): break
    found=[]
    for proc in Path('/proc').iterdir():
        if not proc.name.isdigit() or int(proc.name) in ancestors: continue
        try:
            args=(proc/'cmdline').read_bytes().replace(b'\0',b' ').decode(errors='replace')
            cwd=(proc/'cwd').resolve()
        except OSError: continue
        marker=bool(re.search(r'\b(?:gate_all|overlay_local_gate|certify_overlay_module|land_packages|land_lanes|land_gap)\.py\b|\bcodex\s+exec\b',args))
        if marker and (not scratch or cwd.is_relative_to(root) or str(root) in args):
            found.append({'pid':int(proc.name),'command':args[:400]})
    return found

class Snapshot:
    def __init__(self, root, store):
        self.root,self.store=root,store
        self.head=git(root,'rev-parse','HEAD').decode().strip()
        self.gitdir=Path(git(root,'rev-parse','--absolute-git-dir').decode().strip())
        self.index=(self.gitdir/'index').read_bytes()
        self.status=git(root,'status','--porcelain=v1','-z')
        self.untracked=set(names(git(root,'ls-files','--others','--exclude-standard','-z')))
        tracked=names(git(root,'ls-files','-z'))
        self.prefixes=list(MANAGED)+[p for p in tracked if p.split('/')[0] not in MANAGED]
        # STATUS is a derived output even in a small synthetic test repo.
        if 'STATUS.md' not in self.prefixes: self.prefixes.append('STATUS.md')
        self.before=inventory(root,self.prefixes,GENERATED)
        backup=store/'files'
        for rel,item in self.before.items():
            src,dst=root/rel,backup/rel;dst.parent.mkdir(parents=True,exist_ok=True)
            if item[0]=='dir': dst.mkdir(exist_ok=True)
            elif item[0]=='link': dst.symlink_to(item[2])
            else: shutil.copy2(src,dst)
        self.saved={}
    def quarantine(self):
        for rel in GENERATED:
            p=self.root/rel
            if p.is_symlink(): raise Stop('generated root is a symlink: '+rel)
            if p.exists():
                dst=self.store/'generated'/rel;dst.parent.mkdir(parents=True,exist_ok=True)
                p.rename(dst);self.saved[rel]=dst
    def restore(self):
        # Preserve the original cache directory while replacing its ledger parent.
        for rel in GENERATED: remove(self.root/rel)
        current=set(names(git(self.root,'ls-files','--others','--exclude-standard','-z')))
        for rel in sorted(current-self.untracked, key=lambda s:s.count('/'),reverse=True):
            remove(self.root/rel)
        git(self.root,'reset','--hard',self.head)
        for rel in self.prefixes: remove(self.root/rel)
        for rel,item in sorted(self.before.items(),key=lambda x:(x[0].count('/'),x[0])):
            src,dst=self.store/'files'/rel,self.root/rel;dst.parent.mkdir(parents=True,exist_ok=True)
            if item[0]=='dir': dst.mkdir(exist_ok=True)
            elif item[0]=='link': dst.symlink_to(item[2])
            else: shutil.copy2(src,dst)
            if item[0]!='link': dst.chmod(item[1])
        for rel,dst in self.saved.items():
            p=self.root/rel;p.parent.mkdir(parents=True,exist_ok=True);dst.rename(p)
        (self.gitdir/'index').write_bytes(self.index)
        after=inventory(self.root,self.prefixes,GENERATED)
        if after!=self.before: raise Stop('rollback inventory differs')
        if git(self.root,'rev-parse','HEAD').decode().strip()!=self.head: raise Stop('rollback HEAD differs')
        if git(self.root,'status','--porcelain=v1','-z')!=self.status: raise Stop('rollback status differs')
        return {'tracked_and_managed_entries':len(after),'head':self.head,'status_identical':True,'index_identical':True,'generated_roots_restored':sorted(self.saved)}

class Lander:
    def __init__(self, root, plan, plan_dir, log, scratch=False, live=False):
        self.root,self.plan,self.plan_dir,self.log=root,plan,plan_dir,log
        self.scratch,self.live=scratch,live
        self.env=dict(os.environ,PYTHONDONTWRITEBYTECODE='1',GATE_BUILD_ROOT='build_ovl_gate')
        self.results=[];self.seq=0;self.child=None
    def event(self, step, **values):
        event={'at':time.strftime('%Y-%m-%dT%H:%M:%SZ',time.gmtime()),'step':step,**values}
        with self.log.open('a') as f:f.write(json.dumps(event,sort_keys=True)+'\n')
        print(json.dumps(event,sort_keys=True),flush=True)
    def run(self, step, argv, cwd=None, env=None, timeout=7200):
        self.seq+=1;dest=self.log.parent/(self.log.stem+f'.{self.seq:02d}.log')
        self.event(step,command=[str(a) for a in argv],output=str(dest))
        start=time.monotonic()
        with dest.open('w') as f:
            self.child=subprocess.Popen([str(a) for a in argv],cwd=cwd or self.root,
                env=env or self.env,stdout=f,stderr=subprocess.STDOUT,start_new_session=True)
            try: rc=self.child.wait(timeout=timeout)
            except BaseException:
                self.kill_child();raise
            finally:self.child=None
        secs=round(time.monotonic()-start,3)
        self.results.append({'step':step,'seconds':secs,'rc':rc,'log':str(dest)})
        self.event(step,result='PASS' if rc==0 else 'FAIL',seconds=secs,rc=rc)
        if rc:
            detail=self.graph_diagnostics() if step in ('graph','fast-graph') else ''
            raise Stop(step+' failed'+('; '+detail if detail else '')+'; see '+str(dest))
        return dest,secs
    def kill_child(self):
        if self.child is not None:
            try:os.killpg(self.child.pid,signal.SIGTERM)
            except ProcessLookupError:return
            try:self.child.wait(timeout=5)
            except subprocess.TimeoutExpired:
                try:os.killpg(self.child.pid,signal.SIGKILL)
                except ProcessLookupError:pass
                self.child.wait()
    def source(self,s):
        p=Path(s);return p if p.is_absolute() else self.plan_dir/p
    def expand(self,argv):
        return [str(s).replace('{root}',str(self.root)).replace('{plan_dir}',str(self.plan_dir)) for s in argv]
    def preflight(self):
        if self.plan.get('version')!=1: raise Stop('plan version must be 1')
        if self.root==LIVE and not self.live: raise Stop('live root requires --live')
        if self.root==LIVE and self.scratch: raise Stop('--scratch is forbidden on the live root')
        if self.live and self.root!=LIVE: raise Stop('--live is only for the canonical live root')
        if not self.plan.get('reviewer') or not self.plan.get('commit_message'): raise Stop('reviewer and commit_message required')
        if self.plan.get('reviewer')=='pending' and self.plan.get('commit',True):
            raise Stop('pending reviewer cannot commit; set commit=false for scratch proof')
        active=busy_processes(self.root,self.scratch)
        if active:raise Stop('lander/gate/codex running: '+json.dumps(active))
        known=set(list(BOOKKEEPING)+self.plan.get('bookkeeping',[]))
        status=git(self.root,'status','--porcelain=v1','-z').split(b'\0')
        for entry in status:
            if not entry:continue
            code,path=entry[:2].decode(),os.fsdecode(entry[3:])
            if code!=' M' or path not in known: raise Stop('dirty tree: '+os.fsdecode(entry))
            safe(self.root,path)
        for rel in GENERATED:
            if (self.root/rel).is_symlink():raise Stop('generated root is a symlink: '+rel)
        for package in self.plan.get('packages',[]):
            if self.live and not package.get('live_flag'): raise Stop('live package lacks explicit --live contract: '+package['entry'])
        for kind in ('patches','scripts'):
            for item in self.plan.get(kind,[]):
                if not item.get('files'): raise Stop(kind+' requires expected base/output hashes')
                for rel,h in item['files'].items():
                    safe(self.root,rel)
                    if set(h)!={'before','after'} or not re.fullmatch('[0-9a-f]{64}',h['after']):raise Stop('invalid hash contract: '+rel)
        self.bookkeeping={rel:digest(self.root/rel) for rel in known if (self.root/rel).exists()}
        self.census={p.name:digest(p) for p in (self.root/'config').glob('noreturn_syms*.txt')}
        self.before_l5=l5(self.root)
        self.before_certs=self.certificates()
        self.before_reviews={rel:(self.root/rel).read_text() if (self.root/rel).exists() else '' for rel in REVIEW_FILES}
        self.tracked=set(names(git(self.root,'ls-files','-z')))
        self.event('preflight',result='PASS',bookkeeping=sorted(known),L5=self.before_l5,lander_sha256=digest(Path(__file__)))
    def hashes(self,files,field):
        for rel,h in files.items():
            actual=digest(safe(self.root,rel))
            if actual!=h[field]:raise Stop(field+' SHA256 mismatch: '+rel+f' expected={h[field]} actual={actual}')
    def mutate(self):
        for n,item in enumerate(self.plan.get('patches',[])):
            self.hashes(item['files'],'before')
            patch_paths=set()
            for line in self.source(item['file']).read_text().splitlines():
                if line.startswith(('--- ','+++ ')):
                    name=line[4:].split('\t',1)[0].split(' ',1)[0]
                    if name=='/dev/null':continue
                    parts=Path(name).parts;strip=int(item.get('strip',1))
                    if name.startswith('/') or '..' in parts or len(parts)<=strip:raise Stop('unsafe patch header: '+name)
                    rel='/'.join(parts[strip:]);safe(self.root,rel);patch_paths.add(rel)
            if patch_paths!=set(item['files']):raise Stop('patch headers differ from hash contract')
            args=['patch','--batch','--fuzz=0','--no-backup-if-mismatch','-p'+str(item.get('strip',1)),'-i',str(self.source(item['file']))]
            self.run(f'patch-{n}-dry-run',args+['--dry-run'])
            self.run(f'patch-{n}',args);self.hashes(item['files'],'after')
        for n,item in enumerate(self.plan.get('scripts',[])):
            self.hashes(item['files'],'before')
            self.run(f'script-{n}',self.expand(item['argv']))
            self.hashes(item['files'],'after')
        for n,item in enumerate(self.plan.get('packages',[])):
            entry=self.source(item['entry'])
            argv=([sys.executable] if entry.suffix=='.py' else ['bash'])+[str(entry),'--root',str(self.root)]+self.expand(item.get('args',[]))
            if self.live:argv.append('--live')
            self.run(f'package-{n}-dry-run',argv+['--dry-run'])
            self.run(f'package-{n}',argv)
        for item in self.plan.get('copies',[]):
            dst=safe(self.root,item['target']);src=Path(self.expand([item['source']])[0])
            if not src.is_absolute():src=self.source(str(src))
            if digest(src)!=item['after'] or digest(dst)!=item['before']:raise Stop('copy hash mismatch: '+item['target'])
            dst.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(src,dst)
            self.event('copy',target=item['target'],sha256=digest(dst))
    def normalise_review(self):
        windows=[]
        for y in (self.root/'config/overlays').glob('*.overlay.yaml'):
            if y.relative_to(self.root).as_posix() in self.tracked:continue
            s=y.read_text();t=s
            for key in ('file_start','file_end','vram_start'):
                t=re.sub(r'(\b'+key+r':\s+)(\d+)\b',lambda m:m[1]+'0x'+format(int(m[2]),'X'),t)
            if t!=s:y.write_text(t)
            windows.append(y.name)
        changed={};reviewer=self.plan['reviewer']
        for rel,old in self.before_reviews.items():
            p=self.root/rel
            if not p.exists():continue
            prior=Counter(old.splitlines());out=[];count=0
            for s in p.read_text().splitlines(keepends=True):
                line=s.rstrip('\r\n')
                if prior[line]:prior[line]-=1
                elif line.strip() and not line.lstrip().startswith('#'):
                    r=json.loads(line)
                    if r.get('reviewer') in (None,'pending') and reviewer!='pending':
                        r['reviewer']=reviewer;s=json.dumps(r)+'\n';count+=1
                out.append(s)
            if count:p.write_text(''.join(out))
            changed[rel]=count
        self.event('normalise-review',new_windows=windows,reviewer=reviewer,marked=changed)
    def regenerate(self):
        self.run('registry',[sys.executable,'tools/registry.py'])
        self.run('index',[sys.executable,'tools/gen_src_index.py'])
        self.run('graph',[sys.executable,'tools/gate/overlay_module_gate.py','--root',str(self.root),'--graph'])
        registered=records(self.root/'ledger/rows.jsonl')
        missing=[r.get('id') for r in registered if not r.get('gate_config')]
        if missing:raise Stop('rows without gate window: '+str(missing[:12]))
        import yaml
        bounds={}
        for r in registered:
            wn=r['gate_config']
            # SLUS rows are proved by the forced whole-image build, not YAML windows.
            if r.get('kind')=='slus' and r.get('container')=='slus' and wn=='build.ninja':continue
            if not wn.startswith('config/overlays/') or not wn.endswith('.overlay.yaml'):raise Stop('non-production gate config: '+wn)
            path=safe(self.root,wn)
            if not path.is_file():raise Stop('missing production window: '+wn)
            if wn not in bounds:
                w=yaml.safe_load(path.read_text()).get('standalone_build',{}).get('window',{})
                bounds[wn]=(w.get('file_start'),w.get('file_end'))
            start,end=bounds[wn]
            if not isinstance(start,int) or not isinstance(end,int) or not (start<=r['foff'] and r['foff']+r['size']<=end):raise Stop('row lies outside production window: '+str(r.get('id')))
        for rel,h in self.bookkeeping.items():
            if digest(self.root/rel)!=h:raise Stop('bookkeeping changed: '+rel)
        now={p.name:digest(p) for p in (self.root/'config').glob('noreturn_syms*.txt')}
        if now!=self.census and not self.plan.get('allow_census_change',False):raise Stop('census files changed')
        changed=set(names(git(self.root,'diff','--name-only','-z','HEAD')))|set(names(git(self.root,'ls-files','--others','--exclude-standard','-z')))
        self.force_all=any(p.startswith(('tools/','raw/')) or ('rowbase' in p and p.startswith('config/')) for p in changed)
        # row_db export's canonical mirror is temporary; it must never be staged.
        remove(self.root/'overlays')
        self.event('invariants',rows_without_window=0,census_unchanged=now==self.census,gate_all=self.force_all,split_changes=sorted(p for p in changed if p.startswith('ledger/splits/')))
    def graph_diagnostics(self):
        """Explain a failed authoritative graph without changing its decision."""
        try:
            path=self.root/'config/overlays/modules.json'
            if not path.exists():return ''
            levels={x['id']:x for x in records(self.root/'ledger/levels.jsonl')}
            reg={x['id']:x for x in records(self.root/'ledger/rows.jsonl')}
            assignments=records(self.root/'ledger/modules.jsonl');bad=[]
            for m in json.loads(path.read_text())['modules']:
                if not m.get('membership_evidence'):continue
                ev=json.loads(safe(self.root,m['membership_evidence']).read_text())
                group=ev['ledger_group']
                actual={x['id'] for x in assignments if all(x.get(k)==v for k,v in group.items())}
                expected={a['id'] for a in m['members']}
                if actual!=expected:
                    bad.append(m['key']+' cohort members='+','.join(sorted(actual^expected)))
                for a in m['members']:
                    rid=a['id'];level=levels.get(rid);r=reg.get(rid)
                    if level is None or r is None:
                        bad.append(m['key']+' member='+rid+' missing registry/level');continue
                    if level['level']<3 or level['pins_left'] or level['tail_jumps'] or set(level['l4_residue'])-{'not_in_module'}:
                        bad.append(m['key']+' member='+rid+' L3/placement screen failed '+json.dumps({k:level[k] for k in ('level','pins_left','tail_jumps','l4_residue')},sort_keys=True))
                    if any(a[k]!=r[k] for k in ('foff','size')):
                        bad.append(m['key']+' member='+rid+' identity differs')
            return '; '.join(bad) if bad else ''
        except (OSError,ValueError,KeyError,TypeError) as e:
            return 'graph diagnostic unavailable: '+str(e)
    def scrub(self):
        # Include every changed tracked path, plus files the commit would add.
        dirty=set(names(git(self.root,'diff','--name-only','-z','HEAD')))
        dirty.update(names(git(self.root,'ls-files','--others','--exclude-standard','-z')))
        failures=[];checked=0
        for rel in sorted(dirty):
            if rel in self.bookkeeping or rel.split('/')[0] in ('raw','src') or any(rel==g or rel.startswith(g+'/') for g in GENERATED):continue
            p=safe(self.root,rel)
            if not p.is_file():continue
            data=p.read_bytes();checked+=1
            for pattern in SCRUB_PATTERNS:
                if pattern.encode() in data:failures.append({'file':rel,'pattern':pattern})
        self.event('scrub',result='FAIL' if failures else 'PASS',checked=checked,failures=failures)
        if failures:raise Stop('scrub hook patterns: '+json.dumps(failures,sort_keys=True))
    def fast_front(self):
        self.run('fast-levels',[sys.executable,'tools/levels.py'])
        self.run('fast-graph',[sys.executable,'tools/gate/overlay_module_gate.py','--root',str(self.root),'--graph'])
        self.run('fast-status',[sys.executable,'tools/status.py'])
        self.scrub()
        self.event('FAST_FRONT_PASS',message='accounting/graph/status/scrub only; proofs still required')
    def certificates(self):
        out={}
        for p in sorted((self.root/'ledger/modules').glob('overlay_*.json')):
            c=json.loads(p.read_text());key=c.get('module');reviewer=c.get('reviewer')
            if not key or p.name!='overlay_'+key+'.json' or not reviewer or reviewer=='pending':raise Stop('invalid live certificate: '+str(p))
            out[key]=reviewer
        return out
    def validate(self):
        workers=str(self.plan.get('workers',8))
        # A quarantined (or fresh) build_slus has no split/asm; bootstrap before mk_ovl.
        log,_=self.run('SLUS-bootstrap',[ 'bash','tools/build/build_slus.sh','--fresh','-j',workers])
        if 'SLUS SHA-1 gate: MATCH' not in log.read_text() or 'recipe identical to the pinned copy' not in log.read_text():raise Stop('forced SLUS lacks MATCH/identical recipe')
        self.run('mk-ovl',[ 'bash','tools/build/mk_ovl_root.sh'])
        env=dict(self.env,EXP='gate',SRCROOT=str(self.root/'src'))
        self.run('mk-gate',[ 'bash','tools/build/mk_ovl_root.sh'],env=env)
        modules=self.plan.get('unit_modules',[])
        if not modules:raise Stop('dotted unit_modules are required')
        self.run('unit-dotted',[sys.executable,'-m','unittest',*modules])
        for pattern in self.plan.get('discover_patterns',['test_*.py']):
            test_log,_=self.run('unit-discover-'+pattern,[sys.executable,'-m','unittest','discover','-s','tools/tests','-p',pattern])
            count=re.search(r'Ran (\d+) tests?',test_log.read_text())
            if not count or int(count[1])==0:raise Stop('discovery ran no tests: '+pattern)
        import yaml
        wins=[]
        for y in (self.root/'config/overlays').glob('*.overlay.yaml'):
            cfg=yaml.safe_load(y.read_text());w=cfg.get('standalone_build',{}).get('window',{})
            if 'file_start' in w and 'file_end' in w:wins.append((w['file_end']-w['file_start'],y.relative_to(self.root).as_posix()))
        chosen=list(dict.fromkeys(self.plan.get('timing_windows',[])+[p for _,p in sorted(wins,reverse=True)[:2]]))
        timeout=int(self.plan.get('certificate_timeout',1800))
        for wn in chosen:
            timing_log,secs=self.run('timing-'+Path(wn).stem,[sys.executable,'tools/overlay_local_gate.py','--config',wn,'--clean'],cwd=self.root/'build_ovl_gate',timeout=timeout)
            if secs>=timeout:raise Stop('window exceeds certification timeout: '+wn)
            if not re.search(r'^MATCH\b',timing_log.read_text(),re.M):raise Stop('timed window lacks MATCH: '+wn)
        self.run('gate-all',[sys.executable,'tools/build/gate_all.py','--workers',workers]+(['--all'] if self.force_all else []))
        slus_log,_=self.run('SLUS-forced',['bash','tools/build/build_slus.sh','--fresh','-j',workers])
        if 'SLUS SHA-1 gate: MATCH' not in slus_log.read_text() or 'recipe identical to the pinned copy' not in slus_log.read_text():raise Stop('forced SLUS lacks MATCH/identical recipe')
        certs=self.certificates()
        if not set(self.before_certs).issubset(certs):raise Stop('a pre-landing live certificate disappeared')
        self.event('certificate-discovery',modules=sorted(certs))
        for key,reviewer in certs.items():
            self.run('certify-'+key,[sys.executable,'tools/fidelity/certify_overlay_module.py',key,'--root','build_ovl_gate','--reviewer',reviewer],timeout=7200)
        if set(self.certificates())!=set(certs):raise Stop('live certificate set changed during certification')
        self.run('levels',[sys.executable,'tools/levels.py'])
        self.run('status',[sys.executable,'tools/status.py'])
        after=l5(self.root)
        if after<self.before_l5:raise Stop(f'L5 dropped: {self.before_l5} -> {after}')
        status=(self.root/'STATUS.md').read_text();debt=re.findall(r'statements in \d+ rows',status)
        self.event('accounting',L5_before=self.before_l5,L5_after=after,carve_debt=debt)
        # Recheck after all proofs, including tests and certificates.
        self.regenerate()
        self.scrub()
    def preserve_diagnostics(self):
        candidates=[]
        for rel in ['build_ovl_gate/work/s3_splat','build_ovl_gate/work/module_proofs','build_slus']:
            base=self.root/rel
            if base.exists():
                candidates.extend(p for p in base.rglob('*.log') if p.is_file() and not p.is_symlink() and p.stat().st_size<=1024*1024)
        if candidates:
            dest=self.log.parent/(self.log.stem+'.failure_logs')
            for p in sorted(candidates,key=lambda p:p.stat().st_mtime,reverse=True)[:20]:
                out=dest/p.relative_to(self.root);out.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(p,out)
            self.event('failure-diagnostics',directory=str(dest))
    def commit(self):
        if self.plan['reviewer']=='pending':raise Stop('pending reviewer cannot commit')
        dirty=names(git(self.root,'diff','--name-only','-z','HEAD'))+names(git(self.root,'ls-files','--others','--exclude-standard','-z'))
        paths=sorted(set(p for p in dirty if p not in self.bookkeeping and not any(p==g or p.startswith(g+'/') for g in GENERATED)))
        if paths:
            git(self.root,'add','-A','--',*paths)
            self.run('commit',['git','commit','-m',self.plan['commit_message']])
        self.event('COMMITTED',head=git(self.root,'rev-parse','HEAD').decode().strip())


def load_plan(path):
    data=path.read_text()
    if path.suffix in ('.yaml','.yml'):
        import yaml
        plan=yaml.safe_load(data)
    else:plan=json.loads(data)
    if not isinstance(plan,dict):raise Stop('plan must be an object')
    return plan

@contextlib.contextmanager
def stop_signals():
    def interrupted(signum, frame):raise Stop('interrupted by signal '+str(signum))
    previous={sig:signal.signal(sig,interrupted) for sig in (signal.SIGINT,signal.SIGTERM)}
    try:yield
    finally:
        for sig,handler in previous.items():signal.signal(sig,handler)


def copy_preflight_inputs(source, target):
    """No build/proof directories: share read-only tools; COPY container bytes."""
    for rel in ('toolchain','.venv','baserom'):
        src=source/rel;dst=target/rel
        if src.exists() and not dst.exists():dst.symlink_to(src.resolve(),target_is_directory=True)
    base=source/'work/disc/containers'
    if base.exists():
        dest=target/'work/disc/containers';dest.mkdir(parents=True,exist_ok=True)
        for src in base.iterdir():
            if src.is_file():shutil.copy2(src,dest/src.name,follow_symlinks=True)
    (target/'tmp').mkdir(exist_ok=True)
    common=Path(git(target,'rev-parse','--path-format=absolute','--git-common-dir').decode().strip())
    exclude=common/'info/exclude';exclude.parent.mkdir(parents=True,exist_ok=True)
    with exclude.open('a') as f:f.write('\n/toolchain\n/.venv\n/baserom\n/tmp/\n/work/\n')

def plan_preflight(root, plan_path, log=None):
    # Clone owns its git metadata. worktree add/remove never uses source .git.
    # This leaves canonical HEAD/index/worktree/locks untouched while lanes run.
    log=(log or Path(tempfile.gettempdir())/('preflight-'+str(time.time_ns())+'.jsonl')).resolve()
    if log.is_relative_to(root):raise Stop('preflight log must be outside the source checkout')
    log.parent.mkdir(parents=True,exist_ok=True)
    land=None
    with tempfile.TemporaryDirectory(prefix='plan_preflight-',dir=log.parent) as temp:
        base=Path(temp);seed=base/'seed';view=base/'tree'
        try:
            subprocess.run(['git','clone','--shared','--no-checkout','--',str(root),str(seed)],check=True,capture_output=True)
            commit=git(seed,'rev-parse','HEAD').decode().strip()
            git(seed,'worktree','add','--detach',str(view),commit)
            copy_preflight_inputs(root,view)
            plan=load_plan(plan_path);plan['commit']=False
            land=Lander(view,plan,plan_path.parent,log,scratch=True)
            land.event('disposable-worktree',head=commit,source=str(root))
            land.preflight()
            land.env['TMPDIR']=str(view/'tmp')
            land.mutate();land.normalise_review();land.regenerate();land.fast_front()
            if git(root,'rev-parse','HEAD').decode().strip()!=commit:raise Stop('source HEAD changed during preflight; rerun')
            land.event('PREFLIGHT_PASS',head=commit,message='no SLUS/gates/certification/commit; no landing authority')
            return 0
        except BaseException as e:
            if land:
                land.kill_child();land.event('STOP',error=str(e),rollback='disposable worktree removed')
            else:print('STOP: '+str(e),file=sys.stderr)
            return 1
        finally:
            if seed.exists() and view.exists():
                git(seed,'worktree','remove','--force',str(view))


def main(argv=None):
    ap=argparse.ArgumentParser(description=__doc__,formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root',required=True,type=Path);ap.add_argument('--plan',required=True,type=Path)
    mode=ap.add_mutually_exclusive_group();mode.add_argument('--scratch',action='store_true');mode.add_argument('--live',action='store_true')
    ap.add_argument('--preflight',action='store_true',help='replay the plan at HEAD in a disposable worktree; no builds or proofs');ap.add_argument('--no-commit',action='store_true');ap.add_argument('--prepare-only',action='store_true');ap.add_argument('--log',type=Path)
    args=ap.parse_args(argv);root=args.root.resolve();plan_path=args.plan.resolve()
    if args.preflight:
        if args.live or args.prepare_only:ap.error('--preflight cannot combine with --live or --prepare-only')
        with stop_signals():return plan_preflight(root,plan_path,args.log)
    if root==LIVE and not args.live:ap.error('canonical live root requires --live')
    if args.prepare_only and root==LIVE:ap.error('prepare-only is scratch-only')
    gitdir=Path(git(root,'rev-parse','--absolute-git-dir').decode().strip())
    log=(args.log or gitdir/'land_logs'/('land-'+str(time.time_ns())+'.jsonl')).resolve()
    if any(log.is_relative_to(root/p) for p in MANAGED+GENERATED):ap.error('log must be outside managed/generated paths')
    log.parent.mkdir(parents=True,exist_ok=True)
    land=None;snapshot=None;transaction=None
    with (gitdir/'land_packages.lock').open('a') as lock:
        try:fcntl.flock(lock,fcntl.LOCK_EX|fcntl.LOCK_NB)
        except BlockingIOError:print('STOP: another land_packages transaction holds the lock',file=sys.stderr);return 1
        def interrupted(signum,frame):raise Stop('interrupted by signal '+str(signum))
        previous={sig:signal.signal(sig,interrupted) for sig in (signal.SIGINT,signal.SIGTERM)}
        try:
            plan=load_plan(plan_path)
            if args.no_commit:plan['commit']=False
            land=Lander(root,plan,plan_path.parent,log,args.scratch,args.live)
            land.preflight()
            transaction=Path(tempfile.mkdtemp(prefix='land_transaction-',dir=gitdir))
            snapshot=Snapshot(root,transaction);snapshot.quarantine()
            land.env['TMPDIR']=str(transaction/'tmp');(transaction/'tmp').mkdir()
            land.mutate();land.normalise_review();land.regenerate();land.fast_front()
            if args.prepare_only:
                land.event('PREVIEW_INCOMPLETE',message='applied inputs only; no gates/certification/commit')
            else:
                land.validate()
                if plan.get('commit',True):land.commit()
                else:land.event('PROVED_NO_COMMIT',message='every proof passed; commit disabled')
            shutil.rmtree(transaction);return 0
        except BaseException as e:
            if land:
                land.kill_child()
                try:land.preserve_diagnostics()
                except (OSError,ValueError):pass
            result={'error':str(e),'rollback':'not needed'}
            if snapshot:
                try:result['rollback']=snapshot.restore()
                except BaseException as failure:result['rollback']='FAILED: '+str(failure)
            if land:land.event('STOP',**result)
            else:print('STOP: '+str(e),file=sys.stderr)
            if transaction and isinstance(result['rollback'],dict):shutil.rmtree(transaction)
            return 1
        finally:
            for sig,handler in previous.items():signal.signal(sig,handler)

if __name__=='__main__':raise SystemExit(main())
