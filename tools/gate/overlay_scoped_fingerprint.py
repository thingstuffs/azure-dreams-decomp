"""Experimental certificate dependency projection; opt-in, fail closed.

config/overlay_fingerprint_schema selects this schema; legacy is default. Validation is never
memoized. File reads may use the identity-sensitive gate_read_cache.
Full symbol/as-flags/sibcall and executable tool identities stay conservative
(configure.py: its AS_FLAGS table only, the one part gate code reads).
"""
from __future__ import annotations
import ast, hashlib, json, os, re, shutil, subprocess, sys
from pathlib import Path
from functools import lru_cache
from gate_read_cache import read_json, read_jsonl, read_text, read_records
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
    value = read_text(p).strip() if p.exists() else 'legacy'
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
    if not path.exists(): return []
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

def validate(root, G):
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
    for p in sorted((root/'config/overlays').glob('*.rodata_owners.jsonl')):
        fam = p.name.split('.')[0]; owners[fam] = records(p)
        unique(owners[fam],lambda r:num(r['foff']),'rodata owner ' + fam)
        no_overlap([(num(r['foff']),num(r['foff'])+num(r['rodata_size']),str(r.get('id',r['foff']))) for r in owners[fam]],'rodata ownership ' + fam)
        for r in owners[fam]:
            off = num(r['foff']); size = num(r['rodata_size'])
            if size % 4 or r.get('schema')!='azure-clean.rodata_owner.v1':raise ValueError('invalid rodata owner')
            competitors = [x for x in reg.values() if family(x['container'])==fam and x['foff']<off+size and off<x['foff']+x['size']]
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
            if p.exists() and read_json(p)!=splits[fam]:raise ValueError('exported split roster differs: '+grp['results'])
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
            target=next((Path(os.path.abspath(x)) for x in [p.parent/hit[1],root/'include'/hit[1],root/hit[1]] if x.is_file()),None)
            if target is None or not target.is_relative_to(root):raise ValueError('literal include missing/escapes root: '+line)
            pending.append(str(target.relative_to(root)))
    gcc=root/'toolchain/compilers'/('gcc-'+version)
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
        observed.update(p for p in gcc.rglob('*') if p.is_file())
        signature={str(p):stamp(p) for p in observed}
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
    if not path.is_file():
        parts = Path(group['source_dir']).parts
        if len(parts) != 3 or parts[0] != 'overlays' or parts[2] != 'first_pass_matched':
            raise ValueError('unknown missing matched source facade: ' + group['source_dir'])
        unit = {'dungeon_engine':'dungeon', 'dungeon_engine_pilot_only':'dungeon_engine'}.get(parts[1], parts[1])
        path = root / 'src' / unit / filename
        if not path.is_file():
            raise ValueError('canonical matched source missing: ' + str(path))
    return str(path.resolve().relative_to((root / 'src').resolve().parent))

def identities(root, versions, G):
    # Conservative tool universe: additions/removals participate too. Both
    # layouts give gate tools the same identity; view copies are real files.
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
            if p.is_file():paths['compiler/'+v+'/'+str(p.relative_to(root/'toolchain/compilers'/('gcc-'+v)))]=p
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
    out={n:G.sha(p) if p.exists() else None for n,p in sorted(paths.items()) if n!=CONFIGURE}
    if CONFIGURE in paths:out[CONFIGURE]=configure_identity(paths[CONFIGURE])
    return out

# configure.py is the SLUS build graph. Gate code reads only its AS_FLAGS
# literal (match._default_func_as_flags, live_truth.main_exe_as_flags), so bind
# that table's value: a SLUS CC_VER/partition edit must not void overlay certs.
CONFIGURE='gate/configure.py'
def configure_identity(path):
    if not path.exists():return None
    nodes=[n for n in ast.parse(read_text(path)).body if isinstance(n,ast.Assign)
           and any(isinstance(t,ast.Name) and t.id=='AS_FLAGS' for t in n.targets)]
    if len(nodes)!=1:raise ValueError('configure.py: expected one AS_FLAGS assignment, found %d'%len(nodes))
    try:table=ast.literal_eval(nodes[0].value)
    except ValueError as exc:raise ValueError('configure.py: AS_FLAGS is not a literal') from exc
    if not isinstance(table,dict):raise ValueError('configure.py: AS_FLAGS is not a dict')
    # Insertion order matters: match maps src/w_X.c and src/func_X.c to one key, last wins.
    return 'AS_FLAGS:'+hashlib.sha256(json.dumps(list(table.items())).encode()).hexdigest()

def noreturn(root, fam, offsets, splits, regions, G):
    if fam=='ovmovie':
        p=root/'config/noreturn_syms.ovmovie.txt'
        return {'family_file':G.sha(p) if p.exists() else None}
    if fam not in {'town','dungeon'}:return {}
    # Resolve frozen evidence at the authority; both module and row compiles
    # use this resolver when their view omits raw/.
    if (root/'tools/gate/gen_noreturn_syms.py').exists():
        sys.path.insert(0,str(root/'tools'))
        from gate.gen_noreturn_syms import _find_root, scoped_inputs
    else:
        from gen_noreturn_syms import _find_root, scoped_inputs
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
                p=evidence/name;selected[name]=G.sha(p) if p.exists() else None
    return {'semantic':scoped_inputs(fam,offsets,root=evidence),'regions':scope_records,'frozen_sources':dict(sorted(selected.items())), 'false_member_records':[r for r in records(evidence/'config/noreturn_false_members.jsonl') if r.get('family',r.get('container'))==fam]}

def retail(root, container, start, size, G):
    p=root/'work/disc/containers'/G.CONTAINERS[container]
    with p.open('rb') as f:f.seek(start);data=f.read(size)
    if len(data)!=size:raise ValueError('truncated retail dependency')
    return hashlib.sha256(data).hexdigest()

def required_windows(m, wins, G):
    if m.get('allocation_model')=='separated-literal-allocations-v1':
        extents=[(a['foff'],a['foff']+a['size']) for a in m['allocations']]
    else:
        start=G.module_first(m)['foff'];extents=[(start,start+G.module_size(m))]
    out = [name for name,cfg in sorted(wins.items())
           if cfg['name'].split('_')[0] == family(m['container'])
           and any(num(cfg['standalone_build']['window']['file_start'])<end and start<num(cfg['standalone_build']['window']['file_end']) for start,end in extents)]
    if not out: raise ValueError('module has no production window')
    return out

def screening(m, levels, baseline, G):
    out = {}
    for a in G.all_members(m):
        level = levels[a['id']]
        data = a in m.get('data_members', [])
        out[a['id']] = {('l2' if data else 'l3'): level['level'] >= (2 if data else 3),
            'pins': level['pins_left'], 'tail_jumps': level['tail_jumps'],
            'residue': sorted(set(level['l4_residue']) - {'not_in_module'})}
        if data: out[a['id']]['baseline_exact'] = baseline[a['id']].get('exact') is True
    return out

def row_eligibility(row, level):
    if level is None: return None
    data = row.get('row_kind') == 'data'
    return {('l2' if data else 'l3'): level['level'] >= (2 if data else 3),
        'pins': level['pins_left'], 'tail_jumps': level['tail_jumps'],
        'residue': sorted(set(level['l4_residue']) - {'not_in_module'})}


def fingerprint(m, root, G, windows=True):
    root=Path(root).absolute()
    if m.get('container') not in {'town','dungeon','ovmovie'}:
        raise ValueError('scoped fingerprint does not model this container evidence')
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
        'sibcall':G.sha(root/f'config/sibcall_syms.{fam}.txt') if (root/f'config/sibcall_syms.{fam}.txt').exists() else None,
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
            cfg=wins[wn];sb=cfg['standalone_build'];w=sb['window'];fs,fe=num(w['file_start']),num(w['file_end'])
            units={Path(g['results']).parts[1] for g in [{'results':sb['split_results']},*sb.get('matched_sources',[])]}
            roster={unit:[r for r in splits[unit] if intersects(r,fs,fe)] for unit in sorted(units)}
            wr=[r for r in reg.values() if family(r['container'])==fam and intersects(r,fs,fe)]
            wid={r['id'] for r in wr}
            edges=[e for e in physical['edges'] if wid.intersection(e['rows'])]
            wm=[v for v in mods if any(fs<end and start<fe for start,end in G.module_extents(v))]
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
                        sources.update({n:G.sha(root/n) for n in G.closure(root,[r['asm_path']])})
            for name in ['config/names.tsv','config/slus_006.14.symbols.txt','config/overlays/abs_syms.txt',cfg.get('options',{}).get('symbol_addrs_path'),f'config/overlays/{fam}.as_flags.jsonl',f'config/sibcall_syms.{fam}.txt']:
                if name:symbol_inputs[name]=G.sha(root/name) if (root/name).exists() else None
            window={'config':cfg,'registry':wr,'splits':roster,'edges':edges,'modules':wm,'sources':sources,'symbols':symbol_inputs,
                    'assignments':[r for r in assign if r['id'] in wid],
                    'rowbase':[r for r in regions.get(fam,[]) if num(r['foff_start'])<fe and fs<num(r['foff_end'])],
                    'owned_data':[r for r in owners.get(fam,[]) if num(r['foff'])<fe and fs<num(r['foff'])+num(r['rodata_size'])],
                    'noreturn':noreturn(root,fam,off,splits,regions,G),'retail':retail(root,fam,fs,fe-fs,G),'tools':identities(root,versions,G)}
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
            receipts[wn]={'sha256':G.hashed(window)}
    module_hash=G.hashed(module)
    return {'schema':SCHEMA,'sha256':G.hashed({'schema':SCHEMA,'module':module_hash,'windows':{n:r['sha256'] for n,r in receipts.items()},'required_windows':required}),
            'module':{'sha256':module_hash},'windows':receipts,'required_windows':required}
