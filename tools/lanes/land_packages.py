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
bookkeeping paths may be declared; their initial bytes must remain a prefix.
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
import uuid

sys.path.insert(0,str(Path(__file__).resolve().parent))
from window_dependencies import window_recipes, dependency_closure
from certify_batch import uncertified

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

def remove_except(p, protected):
    if p in protected:return
    if any(q.is_relative_to(p) for q in protected) and p.is_dir() and not p.is_symlink():
        for child in p.iterdir():remove_except(child,protected)
    else:remove(p)

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

def bookkeeping_paths(plan, root):
    declared=plan.get('bookkeeping',[])
    if not isinstance(declared,list) or any(not isinstance(p,str) for p in declared):
        raise Stop('bookkeeping must be a list of exact paths')
    paths=set(BOOKKEEPING)|set(declared)
    for rel in paths:
        safe(root,rel)
        if any(rel==g or rel.startswith(g+'/') for g in GENERATED):
            raise Stop('generated bookkeeping path: '+rel)
    return paths

def tree_dirt(root, plan):
    """The same source-tree admission check for preflight and live execution."""
    known=bookkeeping_paths(plan,root)
    status=git(root,'status','--porcelain=v1','-z').split(b'\0')
    refused=[];allowed=[];i=0
    while i<len(status):
        entry=status[i];i+=1
        if not entry:continue
        code,path=entry[:2].decode(),os.fsdecode(entry[3:])
        if code==' M' and path in known:allowed.append(os.fsdecode(entry))
        else:refused.append(os.fsdecode(entry))
        if 'R' in code or 'C' in code:
            if i<len(status):i+=1
    return {'refused':refused,'bookkeeping':allowed}

def bookkeeping_bytes(root, paths):
    return {rel:safe(root,rel).read_bytes() if (root/rel).exists() else None for rel in paths}

def check_bookkeeping(root, initial):
    for rel,prefix in initial.items():
        p=safe(root,rel)
        if not p.exists():
            if prefix is not None:raise Stop('bookkeeping removed: '+rel)
            continue
        if not p.is_file() or not p.read_bytes().startswith(prefix or b''):
            raise Stop('bookkeeping changed (original bytes are not a prefix): '+rel)

def worker_counts(plan):
    available=len(os.sched_getaffinity(0)) if hasattr(os,'sched_getaffinity') else (os.cpu_count() or 1)
    workers=plan.get('workers',max(1,min(16,available-available//3)))
    if type(workers) is not int or workers<1:raise Stop('workers must be a positive integer')
    # Receipt renewal is mostly Python validation: use independent
    # certificate interpreters before adding window threads to one GIL.
    # The 24-CPU/64-GB sweep favors twelve; explicit overrides still win.
    certificates=plan.get('certificate_workers',max(1,min(12,workers)))
    for name,value in (('workers',workers),('certificate_workers',certificates)):
        if type(value) is not int or value<1:raise Stop(name+' must be a positive integer')
    return workers,certificates,max(1,workers//certificates)

def l5(root):
    return sum(r.get('level') in (5,'L5') for r in records(root/'ledger/levels.jsonl'))

def busy_processes(root, scratch, isolated=False, proc_root=Path("/proc")):
    ancestors={os.getpid()};pid=os.getppid()
    while pid>1:
        ancestors.add(pid)
        try:
            fields=(Path('/proc')/str(pid)/'stat').read_text().rsplit(')',1)[1].split()
            pid=int(fields[1])
        except (OSError,ValueError,IndexError): break
    found=[]
    snapshot=process_snapshot(proc_root)
    for pid,info in snapshot.items():
        if pid in ancestors:continue
        args,cwd=info['args'],info['cwd']
        marker=bool(re.search(r'\b(?:gate_all|overlay_local_gate|certify_overlay_module|land_packages|land_lanes|land_gap|verify|sweep|promote)\.py\b|\b(?:land_lanes|land_gap|land_coherence|land_finished)\.sh\b|\bcodex\s+exec\b',args))
        if isolated:
            jobs={'gate_all','overlay_local_gate','certify_overlay_module','certify_batch',
                  'land_packages','land_lanes','land_gap','verify','sweep','promote'}
            # Module lookup/inline commands never establish isolation. Recognize
            # the module form so it cannot disappear from the busy candidate set.
            marker=marker or bool(re.search(r'\b(?:'+ '|'.join(sorted(jobs))+r')\b',args)) or any(
                a.startswith('-m') and a[2:].rsplit('.',1)[-1] in jobs
                for a in info['argv'])
        if not marker:continue
        if cwd is None:
            # A vanished process cannot conflict. A still-present process with
            # unreadable cwd/stat is ambiguous, never an isolation exemption.
            if isolated and info['proc'].exists():found.append({'pid':pid,'command':args[:400]})
            continue
        if scratch and not cwd.is_relative_to(root) and str(root) not in args:continue
        if isolated and isolated_lane(info['proc'],root,proc_root,snapshot):continue
        found.append({'pid':pid,'command':args[:400]})
    return found


def process_snapshot(proc_root):
    """Read structured argv/cwd/parents once; no recursive filesystem scan."""
    out={}
    for proc in proc_root.iterdir():
        if not proc.name.isdigit():continue
        try:
            data=(proc/'cmdline').read_bytes()
            argv=[os.fsdecode(a) for a in data.rstrip(b'\0').split(b'\0')] if data else []
        except OSError:continue
        try:
            cwd=(proc/'cwd').resolve()
            fields=(proc/'stat').read_text().rsplit(')',1)[1].split()
            parent=int(fields[1])
        except (OSError,ValueError,IndexError):cwd,parent=None,None
        out[int(proc.name)]={'proc':proc,'argv':argv,'args':' '.join(argv),'cwd':cwd,'parent':parent}
    return out


def process_lane(info, root):
    """One lane containing cwd and every script/path argument, or None.

    argv[0] may be a system interpreter/launcher; it is not a source or output
    path. Python/shell script paths, absolute arguments, option=path values and
    relative path arguments must all resolve into the same physical lane.
    Opaque inline commands and module lookup cannot establish that containment.
    """
    root=root.resolve();cwd=info['cwd'];argv=info['argv']
    if cwd is None or not cwd.is_dir() or not argv or info['parent'] is None:return None
    if any(c.isspace() for c in argv[0]):return None
    base=root/'work/native_lane'
    if not cwd.is_relative_to(base):return None
    parts=cwd.relative_to(base).parts
    if not parts:return None
    lane=base/parts[0]
    # Resolving a symlink into canonical src/build is not lane ownership.
    if lane.resolve()!=lane or not lane.is_dir():return None
    protected=tuple(root/n for n in ('build_ovl','build_ovl_gate','build_slus','src'))
    physical=tuple(p.resolve() for p in protected)
    if Path(argv[0]).is_absolute():
        program=Path(argv[0])
        if any(program.is_relative_to(p) for p in protected):return None
        if any(program.resolve().is_relative_to(p) for p in physical):return None
    executable=Path(argv[0]).name
    direct_script=argv[0].endswith(('.py','.sh'))
    start=0 if direct_script else 1
    python=bool(re.fullmatch(r'python(?:\d+(?:\.\d+)*)?',executable))
    shell=executable in ('bash','sh','dash')
    script_found=not (python or shell)
    for index,arg in enumerate(argv[start:],start):
        if ((python and (arg in ('-m','-c') or arg.startswith(('-c','-m')))) or
                (shell and re.fullmatch(r'-[A-Za-z]*c[A-Za-z]*',arg))):return None
        if arg in ('--command','--eval'):return None
        value=arg
        if arg.startswith('-') and '=' in arg:value=arg.split('=',1)[1]
        elif re.match(r'^-(?:I|L|B|o|C|isystem|iquote)/',arg):
            value=arg[arg.index('/'):]
        elif arg.startswith('-') and '/' in arg:return None
        is_script=(direct_script and index==0) or ((python or shell) and not script_found and not arg.startswith('-'))
        if is_script:script_found=True
        path_like=(is_script or Path(value).is_absolute() or '/' in value or
                   value in ('.','..') or value.endswith(('.py','.sh')))
        if not path_like:continue
        # This is a single argv path, not shell text, JSON, a glob or a prompt
        # containing embedded paths. Preserve actual spaces in real file paths.
        if any(c in value for c in '\n\r;|&<>$`*?') or value.startswith(('"',"'",'{','[')):return None
        if re.search(r'\s/',value) or (not arg.startswith('-') and '=' in value):return None
        if ':' in value.split('/',1)[0]:return None
        path=Path(value)
        if not path.is_absolute():path=cwd/path
        try:target=path.resolve(strict=False)
        except (OSError,RuntimeError,ValueError):return None
        lexical=Path(os.path.abspath(path))
        if any(lexical.is_relative_to(p) for p in protected):return None
        if any(target.is_relative_to(p) for p in physical):return None
        # r118: the scratch-root symlinks toolchain/.venv/baserom resolve into the canonical root; no lander writes them.
        if not target.is_relative_to(lane) and not shared_readonly(target,root):return None
        if is_script and not target.is_file():return None
    return lane if script_found else None


SHARED_READONLY=('toolchain','.venv','baserom')


def shared_readonly(path, root):
    """A canonical path no lander writes: the compilers, the venv and the base ROM (scratch roots symlink them)."""
    return any(path.is_relative_to(root/n) or path.is_relative_to((root/n).resolve()) for n in SHARED_READONLY)


def inline_lane_command(info, root, lane):
    """A lane DESCENDANT running inline shell/Python text whose every visible path stays out of the canonical tree.

    codex runs every command as `bash -lc '<text>'` and feeds Python heredocs on stdin, so a lane is mid-command almost
    always. A shell wrapper's real work runs in children, which are checked one by one. Its own text must not name a
    path that resolves into the root outside work/native_lane or the read-only shared inputs. Inline or stdin Python
    runs in-process, so it also needs a lane-owned kit root (the nearest parent with tools/common.py, which kitlib
    takes as ROOT) and no PYTHONPATH entry into the canonical tree.
    """
    root=root.resolve();cwd=info['cwd'];argv=info['argv']
    if cwd is None or info['parent'] is None or not argv or not cwd.is_relative_to(lane):return False
    name=Path(argv[0]).name
    shell=name in ('bash','sh','dash');python=bool(re.fullmatch(r'python(?:\d+(?:\.\d+)*)?',name))
    if not (shell or python):return False
    text=None
    for i,arg in enumerate(argv[1:],1):
        if (shell and re.fullmatch(r'-[A-Za-z]*c[A-Za-z]*',arg)) or (python and arg=='-c'):
            text=argv[i+1] if i+1<len(argv) else '';break
        if python and arg.startswith('-c'):text=arg[2:];break
        if python and (arg=='-m' or arg.startswith('-m')):return False
        if not arg.startswith('-'):
            if python and arg!='-':return False   # a script path: process_lane decides
            if shell:return False
    if shell and text is None:return False
    allowed=(root/'work/native_lane',)
    def admissible(path):
        if not path.is_absolute():path=cwd/path
        for q in (Path(os.path.abspath(path)),path.resolve(strict=False)):
            if q.is_relative_to(root) and not any(q.is_relative_to(a) for a in allowed) and not shared_readonly(q,root):
                return False
        return True
    try:
        for token in re.split(r'[\s\'"`;|&<>(),=]+',text or ''):
            if '$' in token or not ('/' in token or token in ('.','..')):continue
            token=re.split(r'[*?\[]',token,1)[0]
            if token and not admissible(Path(token)):return False
        if python:
            kit=next((p for p in (cwd,*cwd.parents) if (p/'tools/common.py').is_file()),None)
            if kit is None or not kit.resolve().is_relative_to(lane):return False
            for setting in (info['proc']/'environ').read_bytes().split(b'\0'):
                key,sep,value=setting.partition(b'=')
                if sep and key==b'PYTHONPATH':
                    for entry in os.fsdecode(value).split(':'):
                        if entry and not admissible(Path(entry)):return False
    except (OSError,RuntimeError,ValueError):return False
    return True


CANONICAL_MUTABLE=('src','include','config','ledger','raw','docs','asm','build_ovl','build_ovl_gate','build_slus')


def workspace_command(info, root, lane):
    """A lane DESCENDANT working inside a lane-owned scratch tree, with no path into what a landing mutates.

    Lanes build private trees (work/native_lane/<lane>/.../tools/common.py, with toolchain/.venv/tools symlinked in)
    and run their own gates, builds and gdb oracles there; kitlib and the build scripts take that tree as ROOT. Such a
    process is isolated when its cwd's nearest workspace root is inside the lane and no argv token (inline text
    included), fd or gate override resolves into the canonical src/include/config/ledger/raw/docs/asm/build outputs,
    nor to the root itself or above it (a `cd` out of the lane).
    """
    root=root.resolve();cwd=info['cwd'];argv=info['argv']
    if cwd is None or info['parent'] is None or not argv or not cwd.is_relative_to(lane):return False
    ws=next((p for p in (cwd,*cwd.parents) if (p/'tools/common.py').exists()),None)
    if ws is None or not ws.is_relative_to(lane):return False
    # kitlib/common take ROOT from their own resolved __file__: Python reaching the canonical tools/ scores live.
    python=bool(re.fullmatch(r'python(?:\d+(?:\.\d+)*)?',Path(argv[0]).name))
    mutable=tuple(root/n for n in CANONICAL_MUTABLE+(('tools',) if python else ()))
    def bad(path):
        if not path.is_absolute():path=cwd/path
        for q in (Path(os.path.abspath(path)),path.resolve(strict=False)):
            if root.is_relative_to(q) or any(q.is_relative_to(m) or q.is_relative_to(m.resolve()) for m in mutable):return True
        return False
    try:
        for arg in argv[1:]:
            for token in re.split(r'[\s\'"`;|&<>(),=:]+',arg):
                if '$' in token or not ('/' in token or token in ('.','..')):continue
                token=re.sub(r'^-(?:I|L|B|o|C|isystem|iquote)(?=/)','',token)
                token=re.split(r'[*?\[]',token,1)[0]
                if token and bad(Path(token)):return False
        if bad(Path(argv[0])) and '/' in argv[0]:return False
        for fd in (info['proc']/'fd').iterdir():
            try:name=os.readlink(fd)
            except FileNotFoundError:continue
            if name.startswith('/') and bad(Path(name.removesuffix(' (deleted)'))):return False
        for setting in (info['proc']/'environ').read_bytes().split(b'\0'):
            key,sep,value=setting.partition(b'=')
            if sep and key in (b'GATE_BUILD_ROOT',b'GATE_JOURNAL',b'SRCROOT',b'PYTHONPATH'):
                for entry in os.fsdecode(value).split(':'):
                    if entry and (bad(Path(entry)) or (key==b'PYTHONPATH' and Path(entry).resolve().is_relative_to(root/'tools'))):return False
    except (OSError,RuntimeError,ValueError):return False
    return True


def foreign_helper(info, root, lane):
    """True for an external program a lane's codex runs that has no path into the root.

    codex spawns global helpers (the ghidra-mcp bridge: an interpreter and a
    script in a sibling checkout, cwd inherited from the lane) under a lane's
    codex process. The program and every path-like argv token, fd and gate
    override must resolve outside the root or inside this lane; the cwd too.
    Inline code (-c/-e/-m/--command/--eval) is opaque and never qualifies.
    """
    root=root.resolve();cwd=info['cwd'];argv=info['argv']
    if cwd is None or info['parent'] is None or not argv:return False
    def shared(path):
        if not path.is_absolute():path=cwd/path
        for p in (Path(os.path.abspath(path)),path.resolve(strict=False)):
            if p.is_relative_to(root) and not p.is_relative_to(lane):return True
        return False
    try:
        program=Path(argv[0])
        if not program.is_absolute() or shared(cwd):return False
        if Path(os.path.abspath(program)).is_relative_to(root) or program.resolve().is_relative_to(root):return False
        for m in re.finditer(re.escape(str(root)),info['args']):
            rest=info['args'][m.start():]
            if not (rest.startswith(str(lane)) and rest[len(str(lane)):][:1] in ('','/',' ')):return False
        for arg in argv[1:]:
            if arg in ('-c','-e','-m','--command','--eval') or re.fullmatch(r'-[A-Za-z]*[cm]\S*',arg) and not arg.startswith('--'):return False
            value=arg.split('=',1)[1] if arg.startswith('-') and '=' in arg else arg
            if ('/' in value or value in ('.','..')) and shared(Path(value)):return False
        for fd in (info['proc']/'fd').iterdir():
            try:name=os.readlink(fd)
            except FileNotFoundError:continue
            if name.startswith('/') and shared(Path(name.removesuffix(' (deleted)'))):return False
        for setting in (info['proc']/'environ').read_bytes().split(b'\0'):
            key,sep,value=setting.partition(b'=')
            if sep and key in (b'GATE_BUILD_ROOT',b'GATE_JOURNAL',b'SRCROOT') and shared(Path(os.fsdecode(value))):return False
    except (OSError,RuntimeError,ValueError):return False
    return True


def isolated_lane(proc, root, proc_root=Path("/proc"), snapshot=None):
    """Prove one lane from live process paths, independent of launcher receipts.

    Every descendant must satisfy the same containment and fd checks; no busy
    process inherits an exemption from its parent. A canonical-root cwd stays
    ambiguous even when visible arguments only name its lane. This is enabled
    only by busy_processes(..., isolated=True); default admission is unchanged.
    """
    try:
        root=root.resolve()
        snapshot=process_snapshot(proc_root) if snapshot is None else snapshot
        info=snapshot.get(int(proc.name))
        lane=process_lane(info,root) if info else None
        if lane is None:return False
        children={}
        for pid,item in snapshot.items():children.setdefault(item['parent'],[]).append(pid)
        todo=[int(proc.name)];seen=set()
        protected=tuple((root/n).resolve() for n in ('build_ovl','build_ovl_gate','build_slus','src'))
        while todo:
            pid=todo.pop()
            if pid in seen:return False
            seen.add(pid);item=snapshot[pid];q=item['proc']
            todo.extend(children.get(pid,[]))
            # An external helper with no path into the root outside this lane
            # (codex's MCP bridge) cannot reach the transaction; its own
            # children are still checked one by one.
            if pid!=int(proc.name) and foreign_helper(item,root,lane):continue
            if pid!=int(proc.name) and workspace_command(item,root,lane):continue
            if process_lane(item,root)!=lane and not (pid!=int(proc.name) and inline_lane_command(item,root,lane)):
                # r118: codex/oracle children (cc1 under gdb) live for milliseconds; one that exited during the
                # check cannot conflict with the transaction.
                if pid!=int(proc.name) and not q.exists():continue
                return False
            try:
                fds=list((q/'fd').iterdir());environment=(q/'environ').read_bytes().split(b'\0')
            except FileNotFoundError:
                if pid!=int(proc.name) and not q.exists():continue
                raise
            for fd in fds:
                try:
                    name=os.readlink(fd)
                except FileNotFoundError:continue  # fd closed during the snapshot
                if not name.startswith('/'):continue  # pipe/socket/anon_inode
                target=Path(name.removesuffix(' (deleted)')).resolve()
                if any(target.is_relative_to(p) for p in protected):return False
                # Hidden ledger/config/temp descriptors can couple a private
                # job to a canonical transaction too. No out-of-lane project
                # fd is presumed read-only merely because argv looks private.
                if target.is_relative_to(root) and not target.is_relative_to(lane) and not shared_readonly(target,root):return False
            # These overrides can redirect a scratch gate into canonical output
            # without naming that output in argv. Never print process secrets.
            for setting in environment:
                key,sep,value=setting.partition(b'=')
                if sep and key in (b'GATE_BUILD_ROOT',b'GATE_JOURNAL',b'SRCROOT'):
                    path=Path(os.fsdecode(value))
                    if not path.is_absolute():path=item['cwd']/path
                    lexical=Path(os.path.abspath(path));target=path.resolve()
                    canonical=tuple(root/n for n in ('build_ovl','build_ovl_gate','build_slus','src'))
                    if any(lexical.is_relative_to(p) for p in canonical):return False
                    if any(target.is_relative_to(p) for p in protected):return False
                    if not target.is_relative_to(lane):return False
        return True
    except (OSError,RuntimeError,ValueError,KeyError,IndexError,TypeError,Stop):return False


def resolve_source(base, name):
    p=Path(name)
    return p if p.is_absolute() else base/p


def validate_plan(plan, base, root=None):
    """Validate structural contracts before snapshot, packages, or builds."""
    if not isinstance(plan,dict) or plan.get('version')!=1:raise Stop('plan version must be 1')
    if not isinstance(plan.get('reviewer'),str) or not plan['reviewer'].strip():raise Stop('reviewer required')
    if not isinstance(plan.get('commit_message'),str) or not plan['commit_message'].strip():raise Stop('commit_message required')
    modules=plan.get('unit_modules')
    if not isinstance(modules,list) or not modules:raise Stop('non-empty dotted unit_modules are required')
    if any(not isinstance(m,str) or not re.fullmatch(r'[A-Za-z_]\w*(?:\.[A-Za-z_]\w*)+',m) for m in modules):raise Stop('invalid dotted unit_modules')
    for field in ('packages','patches','scripts','copies','reviews','coherence','promotions'):
        items=plan.get(field,[])
        if not isinstance(items,list) or any(not isinstance(i,dict) for i in items):raise Stop(field+' must be a list of objects')
    for item in plan.get('packages',[])+plan.get('reviews',[]):
        if not isinstance(item.get('entry'),str) or not resolve_source(base,item['entry']).is_file():raise Stop('entry missing: '+str(item.get('entry')))
        if not isinstance(item.get('args',[]),list) or any(not isinstance(a,str) for a in item.get('args',[])):raise Stop('entry args must be strings')
        if item in plan.get('reviews',[]) or Path(item['entry']).name=='review_modules.py':
            keys=item.get('keys',item.get('args',[]))
            if not isinstance(keys,list) or not keys or any(not isinstance(k,str) or not re.fullmatch(r'[A-Za-z_]\w*',k) for k in keys):raise Stop('review keys required')
    if root is not None:
        keys=set()
        roster=root/'config/overlays/modules.json'
        if roster.is_file():keys.update(m['key'] for m in json.loads(roster.read_text())['modules'])
        for item in plan.get('packages',[]):
            doc=resolve_source(base,item['entry']).parent/'modules.entries.json'
            if doc.is_file():keys.update(m['key'] for m in json.loads(doc.read_text()).get('modules',[]))
        for item in plan.get('reviews',[])+[p for p in plan.get('packages',[]) if Path(p['entry']).name=='review_modules.py']:
            missing=set(item.get('keys',item.get('args',[])))-keys
            if missing:raise Stop('review keys missing from roster/package entries: '+','.join(sorted(missing)))
    for item in plan.get('patches',[]):
        if not item.get('file') or not resolve_source(base,item['file']).is_file():raise Stop('patch entry missing')
    for item in plan.get('scripts',[]):
        if not isinstance(item.get('argv'),list) or not item['argv'] or any(not isinstance(a,str) for a in item['argv']):raise Stop('script argv required')
    patterns=plan.get('discover_patterns',['test_*.py'])
    if not isinstance(patterns,list) or not patterns or any(not isinstance(p,str) or '/' in p or not p.endswith('.py') for p in patterns):raise Stop('discover_patterns must name tests')
    if 'isolated' in plan and not isinstance(plan['isolated'],bool):raise Stop('isolated must be boolean')
    if not isinstance(plan.get('unit_timeout',60),int) or plan.get('unit_timeout',60)<=0:raise Stop('unit_timeout must be positive seconds')
    if plan.get('gate_all','incremental') not in ('incremental','full'):raise Stop('gate_all must be incremental or full')
    worker_counts(plan)
    if root is not None:bookkeeping_paths(plan,root)
    for item in plan.get('coherence',[]):
        if not isinstance(item.get('tag'),str) or not re.fullmatch(r'[A-Za-z0-9_-]+',item['tag']) or not item.get('lane') or not resolve_source(base,item['lane']).is_dir():raise Stop('coherence requires tag and lane directory')
        if not (resolve_source(base,item['lane'])/'cells.jsonl').is_file():raise Stop('coherence cells missing')
    for item in plan.get('promotions',[]):
        if not all(isinstance(item.get(k),str) and item[k] for k in ('id','body','before')):raise Stop('promotion requires id/body/before')
        if not re.fullmatch(r'[0-9a-f]{64}',item['before']):raise Stop('promotion before must be SHA256')
        if not resolve_source(base,item['body']).is_file():raise Stop('promotion body missing')
    return plan


def full_gate_reasons(paths, plan, root=None, before_includes=None, baseline=None):
    # raw/ and rowbase are hashed by inputs_sha since r103. Unrelated tools do
    # not force all windows, but compiler/gate/fingerprint/build inputs do.
    prefixes=('tools/gate/','tools/maspsx/','tools/fidelity/','toolchain/')
    exact={'tools/build/gate_all.py','tools/build/mk_ovl_root.sh','tools/row_db.py',
           'tools/common.py','tools/overlay_module_evidence.py','tools/build/slus_rodata_trim.py'}
    reasons=sorted(p for p in paths if p.startswith(prefixes) or p in exact)
    includes={p for p in paths if p.startswith('include/')}
    if before_includes is None or root is None or baseline is None:
        reasons.extend(sorted(includes))  # Missing context must never narrow a gate.
    else:
        reasons.extend(sorted(includes & before_includes))
        new=includes-before_includes
        if new and not reasons and plan.get('gate_all')!='full':
            try:
                dependencies=dependency_closure(root,baseline)
                reasons.extend(sorted(new & dependencies))
            except Exception as e:
                reasons.append('include dependency closure unavailable: '+type(e).__name__+': '+str(e))
    if plan.get('gate_all')=='full':reasons.insert(0,'plan gate_all=full')
    return reasons

def certificate_evidence(root):
    """Bind certificate bytes and durable generated proofs before quarantine.

    Reader acceptance alone cannot authorize package-supplied proof records.
    Inventory never follows links; identical quarantine copies compare equal.
    """
    out={}
    for p in sorted((root/'ledger/modules').glob('overlay_*.json')):
        rec=json.loads(p.read_text());key=rec.get('module')
        if not key or p.name!='overlay_'+key+'.json':raise Stop('invalid live certificate: '+str(p))
        refs=[rec.get('proof_dir')]
        if isinstance(rec.get('windows'),list):refs.extend(w.get('proof_dir') for w in rec['windows'] if isinstance(w,dict))
        proofs={}
        for rel in sorted(set(r for r in refs if isinstance(r,str))):
            safe(root,rel)
            if any(Path(rel).is_relative_to(g) for g in GENERATED):
                proofs.update(inventory(root,[rel]))
        out[key]={'certificate':digest(p),'proofs':proofs}
    return out

class Snapshot:
    def __init__(self, root, store, isolated=False, bookkeeping=()):
        self.root,self.store=root,store
        self.generated=tuple(p for p in GENERATED if not (isolated and p=='build_ovl'))
        self.head=git(root,'rev-parse','HEAD').decode().strip()
        self.gitdir=Path(git(root,'rev-parse','--absolute-git-dir').decode().strip())
        self.index=(self.gitdir/'index').read_bytes()
        self.status=git(root,'status','--porcelain=v1','-z')
        self.untracked=set(names(git(root,'ls-files','--others','--exclude-standard','-z')))
        tracked=names(git(root,'ls-files','-z'))
        self.prefixes=list(MANAGED)+[p for p in tracked if p.split('/')[0] not in MANAGED]
        self.prefixes+=list(bookkeeping)
        # STATUS is a derived output even in a small synthetic test repo.
        if 'STATUS.md' not in self.prefixes: self.prefixes.append('STATUS.md')
        self.before=inventory(root,self.prefixes,GENERATED)
        self.certificate_evidence=certificate_evidence(root)
        self.bookkeeping=bookkeeping_bytes(root,bookkeeping)
        backup=store/'files'
        for rel,item in self.before.items():
            src,dst=root/rel,backup/rel;dst.parent.mkdir(parents=True,exist_ok=True)
            if item[0]=='dir': dst.mkdir(exist_ok=True)
            elif item[0]=='link': dst.symlink_to(item[2])
            else: shutil.copy2(src,dst)
        self.saved={}
    def quarantine(self):
        for rel in self.generated:
            p=self.root/rel
            if p.is_symlink(): raise Stop('generated root is a symlink: '+rel)
            if p.exists():
                dst=self.store/'generated'/rel;dst.parent.mkdir(parents=True,exist_ok=True)
                p.rename(dst);self.saved[rel]=dst
        # Certificates bind durable artifacts inside generated roots. Moving
        # those away would invalidate every otherwise-current certificate.
        # Copy only their proof directories; the quarantined originals remain
        # untouched for rollback. Build caches and exported tools stay fresh.
        self.proofs_copied=[];proofs=set()
        for cert in sorted((self.root/'ledger/modules').glob('overlay_*.json')):
            rec=json.loads(cert.read_text())
            refs=[rec.get('proof_dir')]
            if isinstance(rec.get('windows'),list):refs.extend(w.get('proof_dir') for w in rec['windows'] if isinstance(w,dict))
            proofs.update(p for p in refs if isinstance(p,str))
        for rel in sorted(proofs):
            target=safe(self.root,rel)
            generated=next((g for g in self.saved if Path(rel).is_relative_to(g)),None)
            if generated is None:continue
            base=self.store/'generated';source=base/rel
            parents=[source,*source.parents]
            if any(p.is_symlink() for p in parents if p.is_relative_to(base)):continue
            if not source.is_dir():continue  # Missing evidence must be renewed.
            entries=inventory(base,[rel])
            if any(v[0]=='link' for v in entries.values()):continue
            target.parent.mkdir(parents=True,exist_ok=True)
            shutil.copytree(source,target,dirs_exist_ok=True)
            self.proofs_copied.append(rel)
    def restore(self):
        # Keep concurrent append-only writer output across rollback. Rewrites
        # are not authorized and are restored from the original snapshot.
        preserved=set()
        for rel,prefix in self.bookkeeping.items():
            p=self.root/rel
            if not p.is_symlink() and p.parent.resolve().is_relative_to(self.root) and p.is_file():
                data=p.read_bytes()
                if data.startswith(prefix or b''):preserved.add(rel)
        protected={self.root/rel for rel in preserved}
        # Preserve the original cache directory while replacing its ledger parent.
        for rel in self.generated: remove(self.root/rel)
        current=set(names(git(self.root,'ls-files','--others','--exclude-standard','-z')))
        for rel in sorted(current-self.untracked, key=lambda s:s.count('/'),reverse=True):
            remove_except(self.root/rel,protected)
        # Reset only HEAD/index: --hard would overwrite concurrent appenders.
        git(self.root,'reset','--mixed',self.head)
        for rel in self.prefixes:remove_except(self.root/rel,protected)
        for rel,item in sorted(self.before.items(),key=lambda x:(x[0].count('/'),x[0])):
            src,dst=self.store/'files'/rel,self.root/rel;dst.parent.mkdir(parents=True,exist_ok=True)
            if rel in preserved:continue
            if item[0]=='dir': dst.mkdir(exist_ok=True)
            elif item[0]=='link': dst.symlink_to(item[2])
            else: shutil.copy2(src,dst)
            if item[0]!='link': dst.chmod(item[1])
        for rel,dst in self.saved.items():
            p=self.root/rel;p.parent.mkdir(parents=True,exist_ok=True);dst.rename(p)
        (self.gitdir/'index').write_bytes(self.index)
        after=inventory(self.root,self.prefixes,GENERATED)
        def other_inventory(entries):
            return {rel:item for rel,item in entries.items() if rel not in preserved and not
                    (item[0]=='dir' and any(Path(p).is_relative_to(rel) for p in preserved))}
        if other_inventory(after)!=other_inventory(self.before):raise Stop('rollback inventory differs')
        check_bookkeeping(self.root,self.bookkeeping)
        growth=[rel for rel in preserved if safe(self.root,rel).read_bytes()!=self.bookkeeping[rel]]
        if git(self.root,'rev-parse','HEAD').decode().strip()!=self.head: raise Stop('rollback HEAD differs')
        current_status=git(self.root,'status','--porcelain=v1','-z')
        def other_status(data):
            return [e for e in data.split(b'\0') if e and os.fsdecode(e[3:]) not in preserved]
        if other_status(current_status)!=other_status(self.status): raise Stop('rollback status differs')
        return {'tracked_and_managed_entries':len(after),'head':self.head,'status_identical':current_status==self.status,'index_identical':True,'bookkeeping_appends_preserved':sorted(growth),'generated_roots_restored':sorted(self.saved)}

class Lander:
    def __init__(self, root, plan, plan_dir, log, scratch=False, live=False):
        self.root,self.plan,self.plan_dir,self.log=root,plan,plan_dir,log
        self.scratch,self.live=scratch,live
        self.tests_passed=False
        # Callers without a transaction snapshot must reprove every certificate.
        self.before_certificate_evidence={}
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
        validate_plan(self.plan,self.plan_dir,self.root)
        if self.root==LIVE and not self.live: raise Stop('live root requires --live')
        if self.root==LIVE and self.scratch: raise Stop('--scratch is forbidden on the live root')
        if self.live and self.root!=LIVE: raise Stop('--live is only for the canonical live root')
        if not self.plan.get('reviewer') or not self.plan.get('commit_message'): raise Stop('reviewer and commit_message required')
        if self.plan.get('reviewer')=='pending' and self.plan.get('commit',True):
            raise Stop('pending reviewer cannot commit; set commit=false for scratch proof')
        active=busy_processes(self.root,self.scratch,isolated=self.plan.get('isolated',False))
        # r118: an isolated landing waits for a clean sample (codex lanes are mid-command most of the time and a
        # transient child can be ambiguous); it never proceeds while any sample is busy.
        for _ in range(int(os.environ.get('LAND_BUSY_RETRIES','30')) if self.plan.get('isolated',False) else 0):
            if not active:break
            time.sleep(float(os.environ.get('LAND_BUSY_POLL','2')))
            active=busy_processes(self.root,self.scratch,isolated=True)
        if active:raise Stop('lander/gate/codex running: '+json.dumps(active))
        known=bookkeeping_paths(self.plan,self.root)
        dirt=tree_dirt(self.root,self.plan)
        if dirt['refused']:raise Stop('dirty tree: '+json.dumps(dirt['refused']))
        for rel in GENERATED:
            if (self.root/rel).is_symlink():raise Stop('generated root is a symlink: '+rel)
        for package in self.plan.get('packages',[])+self.plan.get('reviews',[]):
            if self.live and not package.get('live_flag'): raise Stop('live package lacks explicit --live contract: '+package['entry'])
        for kind in ('patches','scripts'):
            for item in self.plan.get(kind,[]):
                if not item.get('files'): raise Stop(kind+' requires expected base/output hashes')
                for rel,h in item['files'].items():
                    safe(self.root,rel)
                    if set(h)!={'before','after'} or not re.fullmatch('[0-9a-f]{64}',h['after']):raise Stop('invalid hash contract: '+rel)
        self.bookkeeping=bookkeeping_bytes(self.root,known)
        self.census={p.name:digest(p) for p in (self.root/'config').glob('noreturn_syms*.txt')}
        self.before_l5=l5(self.root)
        self.before_certs=self.certificates()
        self.before_reviews={rel:(self.root/rel).read_text() if (self.root/rel).exists() else '' for rel in REVIEW_FILES}
        self.tracked=set(names(git(self.root,'ls-files','-z')))
        self.before_includes={p for p,v in inventory(self.root,['include']).items() if v[0]!='dir'}
        try:self.before_window_recipes=window_recipes(self.root)
        except Exception as e:self.before_window_recipes={'error':type(e).__name__+': '+str(e)}
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
            if Path(item['entry']).name=='review_modules.py':continue
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
    def batch_inputs(self):
        if not self.plan.get('coherence') and not self.plan.get('promotions'):return
        # Byte checks use a PRIVATE canonical-layout clone so verify.py's
        # legacy build_ovl and common.set_row_cfg cannot touch live scorer roots.
        self.run('batch-inputs',[sys.executable,'tools/lanes/batch_inputs.py','--root',str(self.root),
                 '--plan-dir',str(self.plan_dir),'--spec',json.dumps({k:self.plan.get(k,[]) for k in ('coherence','promotions')})])

    def review_steps(self):
        items=self.plan.get('reviews',[])+[p for p in self.plan.get('packages',[]) if Path(p['entry']).name=='review_modules.py']
        for n,item in enumerate(items):
            keys=item.get('keys',item.get('args',[]))
            roster=json.loads((self.root/'config/overlays/modules.json').read_text())['modules']
            available={m['key'] for m in roster}
            missing=set(keys)-available
            if missing:raise Stop('review keys missing from installed roster: '+','.join(sorted(missing)))
            entry=self.source(item['entry'])
            argv=([sys.executable] if entry.suffix=='.py' else ['bash'])+[str(entry),'--root',str(self.root)]
            argv+=self.expand(keys if 'keys' in item else item.get('args',[]))
            if self.live:argv.append('--live')
            self.run(f'review-{n}-dry-run',argv+['--dry-run'],timeout=60)
            self.run(f'review-{n}',argv,timeout=60)
            # A hardcoded reviewer mismatch must fail before certification.
            roster=json.loads((self.root/'config/overlays/modules.json').read_text())['modules']
            for m in roster:
                if m['key'] in keys and m.get('review',{}).get('reviewer')!=self.plan['reviewer']:
                    raise Stop('review-script reviewer mismatch: '+m['key'])

    def unit_checks(self):
        if self.tests_passed:return
        modules=self.plan['unit_modules']
        for module in modules:
            path=self.root/(module.replace('.','/')+'.py')
            if not path.is_file():raise Stop('unit module missing from canonical layout: '+module)
        # Use the same test-path setup for dotted and discovery entry points.
        # The guard is inherited by Python descendants; denied attempts are
        # recorded even when a unittest catches PermissionError.
        guard_dir=self.log.parent/(self.log.stem+'.guard');guard_dir.mkdir(exist_ok=True)
        source=self.root/'tools/lanes/test_root_guard.py'
        if not source.is_file():raise Stop('missing test_root_guard.py')
        shutil.copy2(source,guard_dir/'sitecustomize.py')
        attempts=guard_dir/'attempts.jsonl'
        outer=Path(self.env.get('LAND_TEST_ROOT',str(self.root)))
        env=dict(self.env,LAND_TEST_ROOT=str(outer),LAND_TEST_FORBIDDEN=str(LIVE),LAND_TEST_AUDIT=str(attempts),
                 PYTHONPATH=os.pathsep.join(dict.fromkeys([str(guard_dir),str(self.root),str(self.root/'tools/tests'),str(outer),str(outer/'tools/tests')])))
        def check(step,argv):
            log,_=self.run(step,argv,env=env,timeout=self.plan.get('unit_timeout',60))
            if attempts.exists():
                self.event('test-confinement',result='FAIL',attempts=records(attempts)[:12])
                raise Stop('test touched canonical root; see '+str(attempts))
            count=re.search(r'Ran (\d+) tests?',log.read_text())
            if not count or int(count[1])==0:raise Stop('tests ran no cases: '+step)
        check('unit-dotted',[sys.executable,'-m','unittest',*modules])
        for pattern in self.plan.get('discover_patterns',['test_*.py']):
            check('unit-discover-'+pattern,[sys.executable,'-m','unittest','discover','-s','tools/tests','-p',pattern])
        self.tests_passed=True

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
        check_bookkeeping(self.root,self.bookkeeping)
        now={p.name:digest(p) for p in (self.root/'config').glob('noreturn_syms*.txt')}
        if now!=self.census and not self.plan.get('allow_census_change',False):raise Stop('census files changed')
        changed=set(names(git(self.root,'diff','--name-only','-z','HEAD')))|set(names(git(self.root,'ls-files','--others','--exclude-standard','-z')))
        self.changed_inputs=changed
        self.gate_reasons=full_gate_reasons(changed,self.plan,self.root,self.before_includes,self.before_window_recipes)
        self.force_all=bool(self.gate_reasons)
        # row_db export's canonical mirror is temporary; it must never be staged.
        remove(self.root/'overlays')
        self.event('invariants',rows_without_window=0,census_unchanged=now==self.census,gate_all='full' if self.force_all else 'incremental',gate_reasons=self.gate_reasons,split_changes=sorted(p for p in changed if p.startswith('ledger/splits/')))
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
    def row_db_check(self):
        # Runs on the tree AFTER the plan's packages/registry/index/graph.
        try:self.run('row-db-check',[sys.executable,'tools/row_db.py','check'])
        except Stop as e:
            detail=''
            if self.results and self.results[-1]['step']=='row-db-check':
                try:detail=Path(self.results[-1]['log']).read_text().strip()
                except OSError:pass
            raise Stop('row_db check failed: '+detail[-4000:]+'\n'+str(e)) from e
        self.event('ROW_DB_CHECK_PASS',message='split tables, windows and MATCH raw/src files verified')
    def fast_front(self):
        self.row_db_check()
        self.unit_checks()
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
        gate_workers,certificate_workers,window_workers=worker_counts(self.plan);workers=str(gate_workers)
        self.event('workers',gate=gate_workers,certificates=certificate_workers,windows_per_certificate=window_workers)
        # A quarantined (or fresh) build_slus has no split/asm; bootstrap before mk_ovl.
        log,_=self.run('SLUS-bootstrap',[ 'bash','tools/build/build_slus.sh','--fresh','-j',workers])
        if 'SLUS SHA-1 gate: MATCH' not in log.read_text() or 'recipe identical to the pinned copy' not in log.read_text():raise Stop('forced SLUS lacks MATCH/identical recipe')
        if not self.plan.get('isolated',False):
            self.run('mk-ovl',[ 'bash','tools/build/mk_ovl_root.sh'])
        env=dict(self.env,EXP='gate',SRCROOT=str(self.root/'src'))
        self.run('mk-gate',[ 'bash','tools/build/mk_ovl_root.sh'],env=env)
        # Regenerated assembly inputs are now available. An early missing
        # closure remains full in preflight, but can be proved here before
        # choosing gate_all's actual mode.
        if getattr(self,'changed_inputs',set()):
            self.gate_reasons=full_gate_reasons(self.changed_inputs,self.plan,self.root,self.before_includes,self.before_window_recipes)
            self.force_all=bool(self.gate_reasons)
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
        transaction=uuid.uuid4().hex
        receipts=Path(self.env['TMPDIR'])/'fresh-window-gates'
        _,seconds=self.run('gate-all',[sys.executable,'tools/build/gate_all.py','--workers',workers,'--receipts',str(receipts),'--transaction',transaction]+(['--all'] if self.force_all else []))
        self.event('gate-timing',mode='full' if self.force_all else 'incremental',seconds=seconds,reasons=self.gate_reasons)
        slus_log,_=self.run('SLUS-forced',['bash','tools/build/build_slus.sh','--fresh','-j',workers])
        if 'SLUS SHA-1 gate: MATCH' not in slus_log.read_text() or 'recipe identical to the pinned copy' not in slus_log.read_text():raise Stop('forced SLUS lacks MATCH/identical recipe')
        certs=self.certificates()
        if not set(self.before_certs).issubset(certs):raise Stop('a pre-landing live certificate disappeared')
        # First certificates for reviewed modules that have none; each is
        # certified by its manifest review.reviewer in the same worker pool.
        try:issue,unreviewed=uncertified(self.root)
        except (OSError,ValueError,KeyError,TypeError) as e:raise Stop('cannot determine uncertified modules: '+str(e))
        self.event('certificate-first-issue',issue=issue,unreviewed_uncertified=unreviewed)
        expected={**certs,**issue}
        self.event('certificate-discovery',modules=sorted(certs))
        current_evidence=certificate_evidence(self.root)
        forced=sorted(key for key in certs if self.before_certificate_evidence.get(key)!=current_evidence[key])
        # Headers keep selective renewal even when they force a full gate.
        # Tool/build/explicit-plan reasons may be outside either fingerprint.
        selective=all(r.startswith(('include/','include dependency closure unavailable:')) for r in self.gate_reasons)
        selection=(['--invalid-only'] if selective else [])+[arg for key in forced for arg in ('--renew',key)]
        self.event('certificate-renewal-policy',mode='invalid-or-changed' if selective else 'all',forced=forced,reasons=self.gate_reasons)
        cert_logs=self.log.parent/(self.log.stem+'.certificates')
        self.run('certify-all',[sys.executable,'tools/lanes/certify_batch.py','--root',str(self.root),
                 '--workers',str(certificate_workers),'--worker-mode','process','--window-workers',str(window_workers),'--log-dir',str(cert_logs),
                 '--gate-receipts',str(receipts),'--transaction',transaction]+selection+[arg for key in sorted(issue) for arg in ('--issue',key)],timeout=7200*max(1,(len(expected)+certificate_workers-1)//certificate_workers))
        if self.certificates()!=expected:raise Stop('live certificate identities/reviewers changed during certification')
        self.run('levels',[sys.executable,'tools/levels.py'])
        self.run('status',[sys.executable,'tools/status.py'])
        after=l5(self.root)
        if after<self.before_l5:raise Stop(f'L5 dropped: {self.before_l5} -> {after}')
        status=(self.root/'STATUS.md').read_text();debt=re.findall(r'statements in \d+ rows',status)
        self.event('accounting',L5_before=self.before_l5,L5_after=after,carve_debt=debt)
        # Recheck after all proofs, including tests and certificates.
        self.regenerate()
        self.scrub()
        # Regeneration may change bound registry, graph or eligibility inputs.
        # Validate every recorded certificate again; never hide a final drop.
        self.run('certificate-final-validation',[sys.executable,'tools/lanes/certify_batch.py','--root',str(self.root),
                 '--workers',str(certificate_workers),'--log-dir',str(cert_logs/'final'),'--validate-only'],timeout=7200)
        if self.certificates()!=expected:raise Stop('live certificate identities/reviewers changed during final validation')
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


def load_plan(path, root=None):
    data=path.read_text()
    if path.suffix in ('.yaml','.yml'):
        import yaml
        plan=yaml.safe_load(data)
    else:plan=json.loads(data)
    return validate_plan(plan,path.parent,root)

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
    extract=source/'work/disc/extract';out=target/'work/disc/extract'
    if extract.exists():
        out.mkdir(parents=True,exist_ok=True)
        for name in ('SLUS_006.14','SYSTEM.CNF'):
            if (extract/name).is_file():shutil.copy2(extract/name,out/name,follow_symlinks=True)
        main=extract/'MAIN/MAIN.BIN'
        if main.is_file():
            (out/'MAIN').mkdir(exist_ok=True);shutil.copy2(main,out/'MAIN/MAIN.BIN',follow_symlinks=True)
    src=source/'bin'
    if src.exists() and not (target/'bin').exists():(target/'bin').symlink_to(src.resolve(),target_is_directory=True)
    (target/'tmp').mkdir(exist_ok=True)
    common=Path(git(target,'rev-parse','--path-format=absolute','--git-common-dir').decode().strip())
    exclude=common/'info/exclude';exclude.parent.mkdir(parents=True,exist_ok=True)
    with exclude.open('a') as f:f.write('\n/toolchain\n/.venv\n/bin\n/baserom\n/tmp/\n/work/\n')

def plan_preflight(root, plan_path, log=None):
    # Clone owns its git metadata. worktree add/remove never uses source .git.
    # This leaves canonical HEAD/index/worktree/locks untouched while lanes run.
    log=(log or Path(tempfile.gettempdir())/('preflight-'+str(time.time_ns())+'.jsonl')).resolve()
    if log.is_relative_to(root):raise Stop('preflight log must be outside the source checkout')
    log.parent.mkdir(parents=True,exist_ok=True)
    try:
        checked_plan=load_plan(plan_path,root)
        dirt=tree_dirt(root,checked_plan)
        with log.open('a') as f:f.write(json.dumps({'step':'source-tree-dirt',**dirt})+'\n')
        if dirt['refused']:raise Stop('dirty tree: '+json.dumps(dirt['refused']))
    except (Stop,ValueError,OSError) as e:
        with log.open('a') as f:f.write(json.dumps({'step':'STOP','error':str(e),'phase':'source admission','rollback':'not needed'})+'\n')
        print('STOP: '+str(e),file=sys.stderr);return 1
    land=None
    with tempfile.TemporaryDirectory(prefix='plan_preflight-',dir=log.parent) as temp:
        base=Path(temp);seed=base/'seed';view=base/'tree'
        try:
            subprocess.run(['git','clone','--shared','--no-checkout','--',str(root),str(seed)],check=True,capture_output=True)
            commit=git(seed,'rev-parse','HEAD').decode().strip()
            git(seed,'worktree','add','--detach',str(view),commit)
            copy_preflight_inputs(root,view)
            plan=dict(checked_plan);plan['commit']=False
            land=Lander(view,plan,plan_path.parent,log,scratch=True)
            land.event('disposable-worktree',head=commit,source=str(root))
            land.preflight()
            land.env['TMPDIR']=str(view/'tmp')
            land.mutate();land.batch_inputs();land.review_steps();land.normalise_review();land.unit_checks();land.regenerate();land.fast_front()
            if git(root,'rev-parse','HEAD').decode().strip()!=commit:raise Stop('source HEAD changed during preflight; rerun')
            dirt=tree_dirt(root,checked_plan)
            if dirt['refused']:raise Stop('source tree became dirty during preflight: '+json.dumps(dirt['refused']))
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
    ap.add_argument('--isolated',action='store_true',help='allow only receipt-verified scratch lanes; never rebuild build_ovl');ap.add_argument('--preflight',action='store_true',help='replay the plan at HEAD in a disposable worktree; no builds or proofs');ap.add_argument('--no-commit',action='store_true');ap.add_argument('--prepare-only',action='store_true');ap.add_argument('--log',type=Path)
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
            plan=load_plan(plan_path,root)
            if args.no_commit:plan['commit']=False
            if args.isolated:plan['isolated']=True
            land=Lander(root,plan,plan_path.parent,log,args.scratch,args.live)
            land.preflight()
            transaction=Path(tempfile.mkdtemp(prefix='land_transaction-',dir=gitdir))
            snapshot=Snapshot(root,transaction,isolated=plan.get('isolated',False),bookkeeping=land.bookkeeping);snapshot.quarantine()
            land.before_certificate_evidence=snapshot.certificate_evidence
            land.event('certificate-proof-preservation',directories=snapshot.proofs_copied)
            land.env['TMPDIR']=str(transaction/'tmp');(transaction/'tmp').mkdir()
            land.mutate();land.batch_inputs();land.review_steps();land.normalise_review();land.unit_checks();land.regenerate();land.fast_front()
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
