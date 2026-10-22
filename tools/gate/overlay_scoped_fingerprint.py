"""Experimental certificate dependency projection; opt-in, fail closed.

config/overlay_fingerprint_schema selects this schema; legacy is default. File reads may use the
identity-sensitive gate_read_cache. validate(), each window digest and each module fingerprint are
memoized per process (memo() below) and reused only while every input identity they probed is
unchanged; every validation rule still runs on any change. AZ_FP_MEMO=0 disables reuse.
Full symbol/as-flags/sibcall and executable tool identities stay conservative
(configure.py: its AS_FLAGS table only, the one part gate code reads).
"""
from __future__ import annotations
import ast, bisect, hashlib, json, os, pickle, re, shutil, subprocess, sys, threading
from pathlib import Path
from functools import lru_cache
import asm_paths
from gate_read_cache import read_json, read_jsonl, read_text, read_records, observe, observing, merge_observed, stamp_of, volatile, VOLATILE

# Per-process memo. An entry holds {path: identity} for every input probed while it was computed
# (gate_read_cache.observing: reads, cache hits, exists/is_file probes below, parent directories,
# and an audit-hook net for open()/listings elsewhere), captured at first probe, i.e. before the
# value was derived from it. Reuse requires every identity to be unchanged now, the same
# (dev, ino, mtime_ns, ctime_ns, size) identity gate_read_cache and _M_CACHE already trust.
# -M subprocess inputs are covered by _M_CACHE's observed-set signature, which is recorded too.
_MEMO = {}
_MEMO_LOCK = threading.Lock()

def memo(key, compute):
    if os.environ.get('AZ_FP_MEMO', '1') == '0':
        return compute()
    with _MEMO_LOCK:
        entry = _MEMO.get(key)
    if entry is not None and all(stamp_of(p) == v for p, v in entry[0].items()):
        merge_observed(entry[0])
        return pickle.loads(entry[1])
    from gate_read_cache import observers
    outer = observers()
    # A nested value (one window digest) may derive from records the caller already read.
    with observing(outer[-1] if outer else None) as seen:
        value = compute()
    if VOLATILE in seen:
        return value
    with _MEMO_LOCK:
        _MEMO[key] = (seen, pickle.dumps(value, protocol=5))
        if len(_MEMO) > 512: _MEMO.pop(next(iter(_MEMO)))
    return value

def _exists(p):
    observe(p); return Path(p).exists()

def _is_file(p):
    observe(p); return Path(p).is_file()
SCHEMA = 'overlay-module-scoped-v2'
FLAG = 'AZ_OVERLAY_SCOPED_FINGERPRINT'  # retired; never selects certificate semantics
SWITCH = 'config/overlay_fingerprint_schema'
ENV_POLICY = {'reject_exact': ['GCC_EXEC_PREFIX', 'COMPILER_PATH', 'LIBRARY_PATH',
    'C_INCLUDE_PATH', 'CPLUS_INCLUDE_PATH', 'OBJC_INCLUDE_PATH', 'CPATH'],
    'reject_prefix': ['AZURE_MASPSX', 'MASPSX_'], 'external_exceptions': []}

def switch_path(root):
    # Production views share config/overlays with their authority but copy
    # selected config files. Resolve the authority for this tracked switch.
    root = Path(root).absolute()
    return (root/'config/overlays').resolve().parent/'overlay_fingerprint_schema'

def enabled(root=None):
    if FLAG in os.environ:
        raise ValueError('environment schema flag retired; use ' + SWITCH)
    if root is None:
        root = Path(__file__).resolve().parents[1]
        if root.name == 'tools': root = root.parent
    p = switch_path(root)
    value = read_text(p).strip() if _exists(p) else 'legacy'
    if value not in ('legacy', SCHEMA):
        raise ValueError('unsupported tracked fingerprint schema: ' + value)
    return value == SCHEMA

def reject_environment(environ=None):
    # Called at public certify/build/window-gate entry, before tool-generated
    # NORETURN/SIBCALL dictionaries are passed to compiler subprocesses.
    environ = os.environ if environ is None else environ
    for key in sorted(environ):
        if key in ENV_POLICY['reject_exact'] or any(key.startswith(p) for p in ENV_POLICY['reject_prefix']):
            raise ValueError('unmodelled compiler environment: ' + key)

def reader_environment():
    # Fingerprints describe the tracked recipe, not a reader's shell. In
    # particular, -M must ignore ambient compiler search overrides too.
    return {key:value for key,value in os.environ.items()
            if key not in ENV_POLICY['reject_exact']
            and not any(key.startswith(p) for p in ENV_POLICY['reject_prefix'])}

@lru_cache(maxsize=32)
def config_parser(text):
    # Execute ONLY match's pure canonical label parser, never match's
    # import-time ROOT/configure lookups (which are view-layout dependent).
    try:
        tree = ast.parse(text)
        nodes = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name == 'parse_config_label']
        if len(nodes) != 1: raise ValueError('missing unique canonical config parser')
        scope = {}
        exec(compile(ast.Module(body=nodes, type_ignores=[]), '<config-label-parser>', 'exec'), scope)
    except (NameError, SyntaxError) as exc:
        raise ValueError('invalid canonical config parser: ' + type(exc).__name__ + ': ' + str(exc)) from exc
    return scope['parse_config_label']

def parse_config_label(root, label, G):
    try:
        return config_parser(read_text(G.gate_tool(root, 'match.py')))(label)
    except NameError as exc:
        raise ValueError('invalid canonical config parser: NameError: ' + str(exc)) from exc


def records(path):
    if not _exists(path): return []
    return list(read_records(path))

def num(v): return int(str(v), 0) if isinstance(v, str) else int(v)
def intersects(r, start, end):
    off = r.get('foff')
    return isinstance(off, int) and start <= off < end if not r.get('size') else (
        isinstance(off, int) and off < end and start < off + num(r['size']))

def unique(items, key, label):
    seen = set()
    for item in items:
        k = key(item)
        if k in seen: raise ValueError('duplicate ' + label + ': ' + str(k))
        seen.add(k)

def no_overlap(items, label):
    last = None
    for start, end, name in sorted(items):
        if not 0 <= start < end: raise ValueError('invalid ' + label + ': ' + name)
        if last and start < last[1]: raise ValueError('overlapping ' + label + ': ' + last[2] + '/' + name)
        last = start, end, name

@lru_cache(maxsize=8192)
def yaml_input(text):
    import yaml
    return yaml.load(text, Loader=getattr(yaml,'CSafeLoader',yaml.SafeLoader))

def windows(root):
    out = {}
    for p in sorted((root/'config/overlays').glob('*.overlay.yaml')):
        import yaml
        try: cfg = yaml_input(read_text(p))
        except yaml.YAMLError as exc:
            raise ValueError('invalid production window YAML: ' + p.name + ': ' + str(exc)) from exc
        sb = cfg.get('standalone_build')
        if not sb: continue
        w = sb['window']; start, end = num(w['file_start']), num(w['file_end'])
        if not 0 <= start < end: raise ValueError('invalid production window: ' + p.name)
        out[str(p.relative_to(root))] = cfg
    unique(out.values(), lambda c:c['name'], 'production window name')
    return out

def family(name): return 'dungeon' if name == 'dungeon_engine' else name

def evidence_suffix(fam):
    # MAIN shares the base evidence files with its co-resident SLUS runtime.
    return '' if fam == 'main' else '.' + fam

def window_modules(mods, fam, fs, fe, G):
    # Same container family only: file offsets of different containers overlap numerically (r120 fix:
    # OVMOVIE's libpress at 0x0-0x1b88 was counted inside TOWN's town_scene window 0x0-0x52000).
    return [v for v in mods if family(v['container'])==fam and any(fs<end and start<fe for start,end in G.module_extents(v))]

def family_spans(reg):
    """Per family: registry rows sorted by start, with start and end keys (spans proven disjoint)."""
    spans = {}
    for i, x in enumerate(reg.values()): spans.setdefault(family(x['container']), []).append((x['foff'], i, x))
    out = {}
    for fam, rows in spans.items():
        rows.sort(key=lambda t: t[0])
        out[fam] = (rows, [t[0] for t in rows], [t[2]['foff']+t[2]['size'] for t in rows])
    return out

def overlapping(spans, fam, off, size):
    """Registry rows of fam overlapping [off, off+size), in registry order (== the former full scan)."""
    rows, starts, ends = spans.get(fam, ([], [], []))
    return [t[2] for t in sorted(rows[bisect.bisect_right(ends, off):bisect.bisect_left(starts, off+size)], key=lambda t: t[1])]

def validate(root, G):
    return memo(('validate', str(Path(root).absolute()), G.__name__), lambda: _validate(root, G))

def _validate(root, G):
    """Validate complete inputs before reducing them, on EVERY fingerprint.

    Preserve the existing load_modules cohort/type/recipe/eligibility screens,
    compare the complete generated graph, and reject duplicates/overlaps even
    outside the selected module's bank. Never manufacture a filtered graph.
    """
    allrows = list(read_jsonl(root/'ledger/rows.jsonl'))
    unique(allrows, lambda r:r['id'], 'registry id')
    assignments = list(read_jsonl(root/'ledger/modules.jsonl'))
    unique(assignments, lambda r:r['id'], 'assignment id')
    reg = {r['id']:r for r in allrows if r['kind']=='overlay'}
    for container in {family(r['container']) for r in reg.values()}:
        no_overlap([(r['foff'],r['foff']+r['size'],r['id']) for r in reg.values()
                    if family(r['container'])==container], 'registry spans ' + container)
    splits = {}
    for p in sorted((root/'ledger/splits').glob('*.jsonl')):
        splits[p.stem] = records(p)
        live = [r for r in splits[p.stem] if not r.get('rerun') and isinstance(r.get('foff'),int) and r.get('size',0)>0]
        no_overlap([(r['foff'],r['foff']+r['size'],str(r.get('func_vram',r['foff']))) for r in live], 'split spans ' + p.stem)
    regions = {}; owners = {}
    for p in sorted((root/'config/overlays').glob('*.rowbase.jsonl')):
        fam = p.name.split('.')[0]; regions[fam] = records(p)
        unique(regions[fam],lambda r:r['region'],'load region ' + fam)
        no_overlap([(num(r['foff_start']),num(r['foff_end']),r['region']) for r in regions[fam]],'load regions ' + fam)
        if any(not r.get('proof') or r.get('schema')!='azure-clean.rowbase.v1' for r in regions[fam]):
            raise ValueError('invalid load region evidence: '+fam)
    # Registry spans were proven non-overlapping above, so per family starts and ends are both
    # sorted and the overlap query is two bisections (it was a scan of every registry row per
    # owner: 24.8 M family() calls). Same competitor set, in registry order.
    spans = family_spans(reg)
    for p in sorted((root/'config/overlays').glob('*.rodata_owners.jsonl')):
        fam = p.name.split('.')[0]; owners[fam] = records(p)
        unique(owners[fam],lambda r:num(r['foff']),'rodata owner ' + fam)
        no_overlap([(num(r['foff']),num(r['foff'])+num(r['rodata_size']),str(r.get('id',r['foff']))) for r in owners[fam]],'rodata ownership ' + fam)
        for r in owners[fam]:
            off = num(r['foff']); size = num(r['rodata_size'])
            if size % 4 or r.get('schema')!='azure-clean.rodata_owner.v1':raise ValueError('invalid rodata owner')
            competitors = overlapping(spans, fam, off, size)
            if len(competitors)!=1 or competitors[0]['foff']!=off or size>competitors[0]['size'] or r.get('id')!=competitors[0]['id']:
                raise ValueError('competing/missing rodata registry owner: '+str(r.get('id')))
    mods = G.load_modules(root)  # ALL cohorts/regions/import evidence, never just this module
    physical = G.graph(root, modules=mods, registry=reg)
    if read_json(root/'ledger/splits/overlay_modules.build.json') != physical:
        raise ValueError('physical graph stale or incomplete')
    wins = windows(root)
    for r in reg.values():
        wn = r.get('gate_config')
        if wn not in wins: raise ValueError('row missing production window: ' + r['id'])
        cfg = wins[wn]; w = cfg['standalone_build']['window']; fam=cfg['name'].split('_')[0]
        if family(r['container'])!=fam or not num(w['file_start'])<=r['foff']<r['foff']+r['size']<=num(w['file_end']):
            raise ValueError('row outside production window: ' + r['id'])
    # Validate ALL exported rosters even when their records lie outside scope.
    exported=set()
    for cfg in wins.values():
        sb=cfg['standalone_build']
        for grp in [{'results':sb['split_results']},*sb.get('matched_sources',[])]:
            if grp['results'] in exported:continue
            exported.add(grp['results'])
            p=G.local(root,grp['results']); fam=Path(grp['results']).parts[1]
            if _exists(p) and read_json(p)!=splits[fam]:raise ValueError('exported split roster differs: '+grp['results'])
    return reg, assignments, splits, regions, owners, mods, physical, wins

_M_CACHE = {}
_NS_CACHE = {}
def namespace(path):
    cached=_NS_CACHE.get(path)
    if cached and all(stamp(p)==v for p,v in cached.items()):return set(cached)
    dirs={Path(base) for base,_,_ in os.walk(path)}
    _NS_CACHE[path]={p:stamp(p) for p in dirs}
    if len(_NS_CACHE)>1024:_NS_CACHE.pop(next(iter(_NS_CACHE)))
    return dirs

def stamp(p):
    try:
        s=p.stat();return (s.st_dev,s.st_ino,s.st_mtime_ns,s.st_ctime_ns,s.st_size)
    except FileNotFoundError:return None

def include_inputs(root, starts, version, flags, G):
    """Union literal closure and actual preprocessor -M at the compile recipe.

    Literal closure deliberately overbinds inactive quoted includes. Actual
    preprocessing captures macro-expanded and system/conditional includes.
    This is fail-closed when a dependency escapes the lexical build root.
    """
    pending=list(starts);found=set()
    while pending:
        name=pending.pop()
        if name in found:continue
        p=G.local(root,name);text=read_text(p);found.add(name)
        for line in text.splitlines():
            hit=re.match(r'\s*(?:#\s*include|\.include)\s+"([^"]+)"',line)
            if not hit:continue
            target=next((Path(os.path.abspath(x)) for x in [p.parent/hit[1],root/'include'/hit[1],root/hit[1]] if _is_file(x)),None)
            if target is None or not target.is_relative_to(root):raise ValueError('literal include missing/escapes root: '+line)
            pending.append(str(target.relative_to(root)))
    gcc=root/'toolchain/compilers'/('gcc-'+version);gcc_files=None
    for name in sorted(set(starts)):
        if not name.endswith(('.c','.h')):continue
        import shlex
        argv_flags=shlex.split(flags)
        for flag in argv_flags:
            if flag.startswith(('-B','-specs','--specs','--sysroot','-wrapper')):
                raise ValueError('unmodelled compiler recipe override: '+flag)
        # Nonstandard include search recipes get a fresh -M scan. This also
        # observes previously absent custom search directories and shadows.
        reusable=not any(flag.startswith(('-I','-i','-nostdinc')) for flag in argv_flags)
        if not reusable:volatile()  # custom search dirs are rescanned every time; never memoize over them
        key=(root,name,version,flags)
        # Include namespace additions (shadowing/macro includes) invalidate,
        # as do every previous dependency, literal dependency and compiler.
        dirs=namespace(root/'include') | namespace((root/name).parent) | namespace(gcc)
        cached=_M_CACHE.get(key)
        deps=set(cached[0]) if cached else set()
        # The -M command depends on this translation unit, its previous
        # actual dependencies and search namespaces. Other starts in the
        # caller's batch affect the final literal-closure hash, not this
        # command; including them here made every repeated call a miss.
        observed={root/name,*(root/n for n in deps)}
        observed.update(p.parent for p in observed.copy())
        observed.update(dirs)
        # One compiler walk per call (it was repeated for every start).
        if gcc_files is None:gcc_files=[p for p in gcc.rglob('*') if p.is_file()]
        observed.update(gcc_files)
        signature={str(p):stamp(p) for p in observed}
        for n,v in signature.items():observe(n,v)
        if reusable and cached and cached[1]==signature:
            found.update(deps);continue
        p=subprocess.run([str(gcc/'gcc'),'-B'+str(gcc)+'/', '-M','-x','c','-O2',*argv_flags,'-I'+str(root/'include'),'-w',str(G.local(root,name))],cwd=root,env=reader_environment(),capture_output=True,text=True,check=True,timeout=300)
        deps=p.stdout.replace('\\\n',' ').split(':',1)
        if len(deps)!=2:raise ValueError('preprocessor dependency output malformed')
        actual=set()
        for dep in deps[1].split():
            path=Path(os.path.abspath(root/dep))
            if not path.is_relative_to(root):raise ValueError('preprocessor dependency escapes root: '+dep)
            actual.add(str(path.relative_to(root)))
        found.update(actual)
        added={root/n for n in actual}
        observed.update(added)
        observed.update(p.parent for p in added)
        _M_CACHE[key]=(actual,{str(p):stamp(p) for p in observed})
        for n,v in _M_CACHE[key][1].items():observe(n,v)
        if len(_M_CACHE)>4096:_M_CACHE.pop(next(iter(_M_CACHE)))
    return {n:G.sha(G.local(root,n)) for n in sorted(found)}

def matched_source(root, group, row):
    """Map the production first_pass_matched facade to canonical src.

    A canonical checkout has no overlays/ facade. Exported views do. The
    mk_ovl_root maps dungeon_engine to dungeon and the pilot-only facade
    to dungeon_engine. Unknown missing facades fail closed.
    """
    filename = row['func_vram'] + '.c'
    path = root / group['source_dir'] / filename
    if not _is_file(path):
        parts = Path(group['source_dir']).parts
        if len(parts) != 3 or parts[0] != 'overlays' or parts[2] != 'first_pass_matched':
            raise ValueError('unknown missing matched source facade: ' + group['source_dir'])
        unit = {'dungeon_engine':'dungeon', 'dungeon_engine_pilot_only':'dungeon_engine'}.get(parts[1], parts[1])
        from source_layout import row_path
        path = row_path({'container': unit, 'c_path': filename}, root)
        if not _is_file(path):
            raise ValueError('canonical matched source missing: ' + str(path))
    return (Path('src') / path.resolve().relative_to((root / 'src').resolve())).as_posix()

def identities(root, versions, G):
    # Conservative tool universe: additions/removals participate too. Both
    # layouts give gate tools the same identity; view copies are real files.
    observe(root/'tools/gate')
    gd=root/'tools/gate' if (root/'tools/gate').is_dir() else root/'tools'
    paths={ 'gate/'+p.name:p for p in gd.iterdir() if p.is_file() and p.suffix in ('.py','.sh')}
    # A flat view contains fidelity/evidence extras: don't count twice.
    if gd==root/'tools':paths.pop('gate/overlay_module_evidence.py',None)
    for sub in ['fidelity']:
        # Only files copied to production views are runtime dependencies here.
        for n in ['aspsx_diff.py','objread.py','certify_overlay_module.py']:
            paths['tools/'+sub+'/'+n]=root/'tools'/sub/n
    for n in ['tools/overlay_module_evidence.py','tools/build/slus_rodata_trim.py']:
        paths[n]=root/n
    for v in sorted(versions):
        for p in sorted((root/'toolchain/compilers'/('gcc-'+v)).rglob('*')):
            if _is_file(p):paths['compiler/'+v+'/'+str(p.relative_to(root/'toolchain/compilers'/('gcc-'+v)))]=p
    for n in ['toolchain/genuine/bin/wibo','toolchain/genuine/psyq/psyq4.4/ASPSX.EXE','.venv/bin/python']:
        paths[n]=root/n
    for p in sorted((root/'toolchain/maspsx').rglob('*.py')):paths[str(p.relative_to(root))]=p
    for name in ['python3','bash','mipsel-linux-gnu-as','mipsel-linux-gnu-ld','mipsel-linux-gnu-objcopy','mipsel-linux-gnu-nm']:
        p=shutil.which(name)
        if not p:raise ValueError('missing tool: '+name)
        paths['host/'+name]=Path(p)
    paths[SWITCH]=switch_path(root)
    # The inline-ASM macro branch names this through a C string, so -M does
    # not see it. Bind presence/absence even while that branch is unused.
    paths['include/macro.inc']=root/'include/macro.inc'
    out={n:G.sha(p) if _exists(p) else None for n,p in sorted(paths.items()) if n!=CONFIGURE}
    if CONFIGURE in paths:out[CONFIGURE]=configure_identity(paths[CONFIGURE])
    return out

# configure.py is the SLUS build graph. Gate code reads only its AS_FLAGS
# literal (match._default_func_as_flags, live_truth.main_exe_as_flags), so bind
# that table's value: a SLUS CC_VER/partition edit must not void overlay certs.
CONFIGURE='gate/configure.py'
def configure_identity(path):
    if not _exists(path):return None
    nodes=[n for n in ast.parse(read_text(path)).body if isinstance(n,ast.Assign)
           and any(isinstance(t,ast.Name) and t.id=='AS_FLAGS' for t in n.targets)]
    if len(nodes)!=1:raise ValueError('configure.py: expected one AS_FLAGS assignment, found %d'%len(nodes))
    try:table=ast.literal_eval(nodes[0].value)
    except ValueError as exc:raise ValueError('configure.py: AS_FLAGS is not a literal') from exc
    if not isinstance(table,dict):raise ValueError('configure.py: AS_FLAGS is not a dict')
    # Insertion order matters: match maps src/w_X.c and src/func_X.c to one key, last wins.
    return 'AS_FLAGS:'+hashlib.sha256(json.dumps(list(table.items())).encode()).hexdigest()

def noreturn(root, fam, offsets, splits, regions, G):
    if fam in {'main','ovmovie'}:
        p=root/('config/noreturn_syms'+evidence_suffix(fam)+'.txt')
        return {'family_file':G.sha(p) if _exists(p) else None}
    if fam not in {'town','dungeon'}:return {}
    # Resolve frozen evidence at the authority; both module and row compiles
    # use this resolver when their view omits raw/.
    if _exists(root/'tools/gate/gen_noreturn_syms.py'):
        sys.path.insert(0,str(root/'tools'))
        from gate.gen_noreturn_syms import _find_root, scoped_inputs, frozen_sha
    else:
        from gen_noreturn_syms import _find_root, scoped_inputs, frozen_sha
    evidence=_find_root(root/'tools/_')
    # Bind content and ABSENCE for every selected frozen source, not just the
    # extracted names. Region sources are selected exactly as _scope_index.
    rr=records(evidence/f'config/overlays/{fam}.rowbase.jsonl')
    units=(fam,'dungeon_engine') if fam=='dungeon' else (fam,)
    allsplits=[r for unit in units for r in records(evidence/f'ledger/splits/{unit}.jsonl')]
    selected={};scope_records=[];byoff={};regional={}
    for r in allsplits:
        if isinstance(r.get('foff'),int):byoff.setdefault(r['foff'],[]).append(r)
    for off in sorted(set(offsets)):
        scope=next((r for r in rr if num(r['foff_start'])<=off<num(r['foff_end'])),None)
        candidates=list(byoff.get(off,[]))
        if scope and scope['region'] not in regional:
            regional[scope['region']]=True;scope_records.append(scope)
            candidates += [r for r in allsplits if isinstance(r.get('foff'),int) and num(scope['foff_start'])<=r['foff'] and r['foff']+(r.get('size') or 0)<=num(scope['foff_end'])]
        for r in candidates:
            source=r.get('c_path') or (r.get('func_vram','')+'.c' if r.get('func_vram') else None)
            if source:
                name=f'raw/{fam}/'+Path(source).name
                if name in selected:continue
                selected[name]=frozen_sha(evidence,name)
    return {'semantic':scoped_inputs(fam,offsets,root=evidence),'regions':scope_records,'frozen_sources':dict(sorted(selected.items())), 'false_member_records':[r for r in records(evidence/'config/noreturn_false_members.jsonl') if r.get('family',r.get('container'))==fam]}

def retail(root, container, start, size, G):
    p=root/'work/disc/containers'/G.CONTAINERS[container]
    with p.open('rb') as f:f.seek(start);data=f.read(size)
    if len(data)!=size:raise ValueError('truncated retail dependency')
    return hashlib.sha256(data).hexdigest()

def required_windows(m, wins, G):
    extents=G.module_extents(m)
    out = [name for name,cfg in sorted(wins.items())
           if cfg['name'].split('_')[0] == family(m['container'])
           and any(num(cfg['standalone_build']['window']['file_start'])<end and start<num(cfg['standalone_build']['window']['file_end']) for start,end in extents)]
    if not out: raise ValueError('module has no production window')
    return out

def eligibility(level, data):
    """Eligibility inputs of one ledger/levels.jsonl record.

    A seed record {"id": ..., "level": -1} (new rows, until a full gate computes
    levels) has no pins/tail/residue fields. It is bound as an explicit unleveled
    state that never passes the L2/L3 screen, instead of raising KeyError. Any
    other incomplete record still raises (fail closed).
    """
    key = 'l2' if data else 'l3'
    if level['level'] < 0:
        return {key: False, 'pins': None, 'tail_jumps': None, 'residue': ['unleveled'], 'level': level['level']}
    return {key: level['level'] >= (2 if data else 3),
        'pins': level['pins_left'], 'tail_jumps': level['tail_jumps'],
        'residue': sorted(set(level['l4_residue']) - {'not_in_module'})}

def screening(m, levels, baseline, G):
    out = {}
    for a in G.all_members(m):
        level = levels[a['id']]
        data = a in m.get('data_members', [])
        out[a['id']] = eligibility(level, data)
        if data: out[a['id']]['baseline_exact'] = baseline[a['id']].get('exact') is True
    return out

def row_eligibility(row, level):
    if level is None: return None
    return eligibility(level, row.get('row_kind') == 'data')


def fingerprint(m, root, G, windows=True):
    root=Path(root).absolute()
    return memo(('fingerprint',str(root),json.dumps(m,sort_keys=True),bool(windows),G.__name__),lambda:_fingerprint(m,root,G,windows))

def _fingerprint(m, root, G, windows):
    if m.get('container') not in {'main','town','dungeon','ovmovie'}:
        raise ValueError('scoped fingerprint does not model this container evidence')
    # tu7 MAIN owner model: a MAIN module may import retail views of its own proven load region
    # (owner retail_asset:main:<region>, bound below by retail bytes) and SLUS runtime objects;
    # owned payload and allocation models stay text-only.
    if m.get('container') == 'main' and (m.get('owned_data') or m.get('data_members') or m.get('allocations')
            or any(d.get('kind') not in ('function', 'data', 'runtime_data') or 'asset' in d
                   or (d.get('kind') == 'data' and d.get('owner') != 'retail_asset:main:' + m['region'])
                   for d in m.get('imports', []))):
        raise ValueError('MAIN scoped modules currently require text-only payload and function-only imports')
    reg,assign,splits,regions,owners,mods,physical,wins=validate(root,G)
    current=next((v for v in mods if v['key']==m['key']),None)
    if current!=m:raise ValueError('stale supplied manifest entry')
    required=required_windows(m,wins,G)
    if required!=G.affected_windows(m,root,parsed_windows=wins):raise ValueError('parsed required windows differ from affected_windows')
    levels={r['id']:r for r in read_jsonl(root/'ledger/levels.jsonl')}
    baseline={r['id']:r for r in read_jsonl(root/'ledger/baseline.jsonl')} if any(v.get('data_members') for v in mods) else {}
    ids={a['id'] for a in G.all_members(m)};fam=m['container'];offsets={a['foff'] for a in G.all_members(m)}
    span_start,span_end=G.module_span(m)
    inputs={p:G.sha(G.local(root,p)) for p in [*m['review_inputs'],'config/names.tsv']}
    starts=[m['source'],*m['headers'],*(a['source'] for a in G.all_members(m)),'include/labels.inc',*(p for p in m['review_inputs'] if p.endswith(('.c','.h'))),*(d['declaration'] for d in m['imports'] if d['kind']=='runtime_data')]
    module={'manifest_schema':read_json(root/'config/overlays/modules.json')['schema'],'entry':m,
        'registry':[reg[a['id']] for a in G.all_members(m)], 'assignments':[r for r in assign if r['id'] in ids],
        'splits':{unit:[r for r in rs if intersects(r,span_start,span_end)] for unit,rs in splits.items() if family(unit)==fam},
        'rowbase':[r for r in regions.get(fam,[]) if num(r['foff_start'])<span_end and span_start<num(r['foff_end'])],
        'owned_data':[r for r in owners.get(fam,[]) if num(r['foff'])<span_end and span_start<num(r['foff'])+num(r['rodata_size'])],
        'review_inputs':inputs,'closure':include_inputs(root,starts,G.module_compiler(m),'-G0',G),
        'screening':screening(m,levels,baseline,G) if m.get('membership_evidence') else {},
        'retail':{'module':retail(root,fam,span_start,span_end-span_start,G)},
        'sibcall':G.sha(root/f'config/sibcall_syms{evidence_suffix(fam)}.txt') if _exists(root/f'config/sibcall_syms{evidence_suffix(fam)}.txt') else None,
        'environment_policy':ENV_POLICY,'noreturn':noreturn(root,fam,offsets,splits,regions,G),'tools':identities(root,{G.module_compiler(m)},G)}
    for d in m['imports']:
        if d['kind']=='data':
            if 'asset' in d:
                with G.local(root,d['asset']).open('rb') as f:f.seek(d['foff']);b=f.read(d['view_bytes'])
                if len(b)!=d['view_bytes']:raise ValueError('truncated external storage')
                module['retail'][d['symbol']]=hashlib.sha256(b).hexdigest()
            else:module['retail'][d['symbol']]=retail(root,fam,d['foff'],d['view_bytes'],G)
    receipts={}
    if windows:
        # Window digests contain no module/window fingerprints: no cycles.
        for wn in required:
            receipts[wn]=memo(('window',str(root),wn,fam,G.__name__),
                              lambda wn=wn:_window_digest(root,wn,wins,splits,reg,physical,assign,regions,owners,mods,levels,baseline,fam,G))
    module_hash=G.hashed(module)
    return {'schema':SCHEMA,'sha256':G.hashed({'schema':SCHEMA,'module':module_hash,'windows':{n:r['sha256'] for n,r in receipts.items()},'required_windows':required}),
            'module':{'sha256':module_hash},'windows':receipts,'required_windows':required}

def _window_digest(root,wn,wins,splits,reg,physical,assign,regions,owners,mods,levels,baseline,fam,G):
    # Window digests contain no module/window fingerprints: no cycles.
    cfg=wins[wn];sb=cfg['standalone_build'];w=sb['window'];fs,fe=num(w['file_start']),num(w['file_end'])
    units={Path(g['results']).parts[1] for g in [{'results':sb['split_results']},*sb.get('matched_sources',[])]}
    roster={unit:[r for r in splits[unit] if intersects(r,fs,fe)] for unit in sorted(units)}
    wr=[r for r in reg.values() if family(r['container'])==fam and intersects(r,fs,fe)]
    wid={r['id'] for r in wr}
    edges=[e for e in physical['edges'] if wid.intersection(e['rows'])]
    wm=window_modules(mods,fam,fs,fe,G)
    sources={};versions={'2.7.2-cdk'};off=set();symbol_inputs={}
    for v in wm:
        ss=[v['source'],*v['headers'],*(a['source'] for a in G.all_members(v)),*(p for p in v['review_inputs'] if p.endswith(('.c','.h'))),*(d['declaration'] for d in v['imports'] if d['kind']=='runtime_data')]
        version=G.module_compiler(v);versions.add(version)
        sources.update(include_inputs(root,ss,version,'-G0',G))
        off.update(a['foff'] for a in G.all_members(v))
    for grp in sb.get('matched_sources',[]):
        unit=Path(grp['results']).parts[1]
        for r in roster[unit]:
            if r.get('result')!='MATCH' or (grp.get('skip_rerun',True) and r.get('rerun')):continue
            version,flags=parse_config_label(root,r.get('config') or '2.7.2',G);versions.add(version)
            if r.get('source_kind','c')=='c':
                off.add(r['foff'])
                name=matched_source(root,grp,r)
                sources.update(include_inputs(root,[name],version,flags,G))
            else:
                sources.update({n:G.sha(asm_paths.resolve(root,n)) for n in G.closure(root,[r['asm_path']])})
    import linklist
    observe(linklist.link_dir(root))  # memo invalidation: the directory, each container directory, each list
    if linklist.link_dir(root).is_dir():
        for d in linklist.link_dir(root).iterdir():observe(d)
    for f in linklist.files(root):observe(f)
    cross=linklist.cross_evidence(root,fam,off)  # decision 75 (A): homes in another container
    off|=linklist.evidence_offsets(root,fam,off)  # placements compile with their home's bank evidence
    for name in ['config/names.tsv','config/slus_006.14.symbols.txt','config/overlays/abs_syms.txt',cfg.get('options',{}).get('symbol_addrs_path'),f'config/overlays/{fam}.as_flags.jsonl',f'config/sibcall_syms{evidence_suffix(fam)}.txt']:
        if name:symbol_inputs[name]=G.sha(root/name) if _exists(root/name) else None
    window={'config':cfg,'registry':wr,'splits':roster,'edges':edges,'modules':wm,'sources':sources,'symbols':symbol_inputs,
            'assignments':[r for r in assign if r['id'] in wid],
            'rowbase':[r for r in regions.get(fam,[]) if num(r['foff_start'])<fe and fs<num(r['foff_end'])],
            'owned_data':[r for r in owners.get(fam,[]) if num(r['foff'])<fe and fs<num(r['foff'])+num(r['rodata_size'])],
            'noreturn':noreturn(root,fam,off,splits,regions,G),'retail':retail(root,fam,fs,fe-fs,G),'tools':identities(root,versions,G)}
    # Link-list files deciding this window's placement rows (docs/LINK_LISTS.md); the key is absent while the
    # window holds none, so a tree without config/link/ keeps every existing digest.
    links=linklist.window_files(root,sorted(wid))
    if links:window['link_lists']={n:G.sha(root/n) for n in links}
    # Cross-container placements compile with their HOME family's evidence; absent key = unchanged digest.
    if cross:
        window['cross_noreturn']={f:dict(noreturn(root,f,sorted(o),splits,regions,G),
                                         sibcall=G.sha(root/f'config/sibcall_syms{evidence_suffix(f)}.txt')
                                         if _exists(root/f'config/sibcall_syms{evidence_suffix(f)}.txt') else None)
                                  for f,o in sorted(cross.items())}
    # Every neighbor TU can consume own review/storage evidence too.
    window['module_inputs']={v['key']:{p:G.sha(root/p) for p in v['review_inputs']} for v in wm}
    window['module_registry']={v['key']:[reg[a['id']] for a in G.all_members(v)] for v in wm}
    window['module_screening']={v['key']:screening(v,levels,baseline,G) for v in wm if v.get('membership_evidence')}
    window['neighbor_eligibility']={rid:row_eligibility(reg[rid],levels.get(rid)) for rid in sorted(wid)}
    storage={}
    for v in wm:
        first,last=G.module_span(v)
        storage[v['key']]={'text':retail(root,v['container'],first,last-first,G)}
        for d in v['imports']:
            if d['kind']!='data':continue
            if 'asset' in d:
                with G.local(root,d['asset']).open('rb') as f:f.seek(d['foff']);b=f.read(d['view_bytes'])
                if len(b)!=d['view_bytes']:raise ValueError('truncated neighboring storage')
                h=hashlib.sha256(b).hexdigest()
            else:h=retail(root,v['container'],d['foff'],d['view_bytes'],G)
            storage[v['key']][d['symbol']]=h
    window['module_storage']=storage
    import overlay_module_placements as P
    observe(root/P.MANIFEST)
    placed=[p for p in P.load(root,mods) if p['container']==fam and P.intersects(p,fs,fe)]
    if placed:
        window['module_placements']=[dict(P.inputs(p,root),artifact=G.fingerprint(next(m for m in mods if m['key']==p['module']),root,windows=False)) for p in placed]
    return {'sha256':G.hashed(window)}
