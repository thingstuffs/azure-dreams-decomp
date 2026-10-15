"""Portable lane proofs: independently rediscovered inputs, never a trusted file list.

Receipts are reviewed package evidence, not signatures or review authority. Only
canonical producers issue reusable window/module receipts. Diagnostic row/TU
receipts cannot discharge a window or a complete module certificate.
"""
from __future__ import annotations

import argparse
from contextlib import contextmanager
from contextvars import ContextVar
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT/'tools'), str(ROOT/'tools/gate')]
SCHEMA = 'azure-proof-receipt.v1'
KINDS = {'overlay-window', 'overlay-module', 'native-candidate', 'row-score'}
_SNAPSHOT = ContextVar('portable_proof_hashes', default=None)


def encoded(value):
    return json.dumps(value, sort_keys=True, separators=(',', ':')).encode()


def hashed(value):
    return hashlib.sha256(encoded(value)).hexdigest()


def sha(path):
    # Only process-local content-read sharing, scoped to a single verification
    # sweep. No persisted stat identity ever grants proof validity.
    path = Path(path)
    cache = _SNAPSHOT.get()
    st = path.stat()
    key = (str(path), st.st_dev, st.st_ino, st.st_size, st.st_mtime_ns, st.st_ctime_ns)
    if cache is not None and key in cache:
        return cache[key]
    h = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024*1024), b''):
            h.update(block)
    value = h.hexdigest()
    if cache is not None:
        cache[key] = value
    return value


@contextmanager
def input_snapshot():
    token = _SNAPSHOT.set({})
    try:
        import gen_noreturn_syms as C
        with C.scoped_input_snapshot():yield
    finally:
        _SNAPSHOT.reset(token)


def local(root, name):
    p = Path(name)
    if not p.parts or p.is_absolute() or '..' in p.parts:
        raise ValueError('unsafe proof path: ' + str(name))
    return Path(root)/p


def private(root, name):
    p = local(root, name)
    if any(q.is_symlink() for q in [p,*p.parents] if q.is_relative_to(Path(root))) or not p.parent.resolve().is_relative_to(Path(root).resolve()):
        raise ValueError('proof output escapes root: ' + str(name))
    return p


def _authorities():
    from gate import overlay_module_gate as G
    import overlay_scoped_fingerprint as S
    return G, S


def environment():
    _, S = _authorities()
    S.reject_environment()
    # These additional entry points can replace extraction/scoring tools.
    for key in ('OVERLAY_EXTRACT_BINS', 'PYTHONPATH', 'PYTHONHOME', 'LD_PRELOAD',
                'LD_LIBRARY_PATH', 'GATE_EXTRA_FLAGS'):
        if os.environ.get(key):
            raise ValueError('unmodelled proof environment: ' + key)
    return dict(policy=1)


def records(path):
    cache=_SNAPSHOT.get();key=('records',str(path))
    if cache is not None and key in cache:return cache[key]
    if not path.exists():
        return []
    value=[json.loads(s) for s in path.read_text().splitlines()
           if s.strip() and not s.lstrip().startswith('#')]
    if cache is not None:cache[key]=value
    return value


def optional(root, names):
    return {name:sha(local(root, name)) if local(root, name).is_file() else None
            for name in sorted(n for n in set(names) if n)}


def tree_files(path):
    # Narrow, explicit input trees only. Never walk work/ or the repository.
    if not path.exists():
        return []
    return sorted(p for p in path.rglob('*') if p.is_file() and '__pycache__' not in p.parts
                  and p.suffix not in ('.pyc', '.pyo'))


def extra_tools(root):
    # Bind producer/verifier, entry points and Python dependency implementations
    # in addition to S.identities' compiler, assembler and genuine tool hashes.
    paths = {n:root/n for n in ('tools/lanes/proof_receipts.py', 'tools/build/gate_all.py',
             'tools/verify.py', 'tools/common.py', 'tools/lanes/lanekit/native_member.py',
             'tools/lanes/lanekit/kitlib.py', 'tools/build/mk_ovl_root.sh')}
    import yaml
    paths['python/yaml'] = Path(yaml.__file__)
    try:
        import _yaml
        paths['python/_yaml'] = Path(_yaml.__file__)
    except ImportError:
        pass
    for name in ('mipsel-linux-gnu-objdump', 'mipsel-linux-gnu-readelf'):
        p = shutil.which(name)
        if not p:
            raise ValueError('missing proof tool: ' + name)
        paths['host/'+name] = Path(p)
    return {name:sha(p) if p.is_file() else None for name, p in sorted(paths.items())}


def assembly_inputs(root, name):
    """Literal GNU assembly include/incbin closure, including lookup shadows."""
    found = {}
    pending = [name]
    while pending:
        item = pending.pop()
        if item in found:
            continue
        p = local(root, item)
        if not p.is_file() and item.startswith('asm/'):
            p = local(root, 'build_slus/'+item)
        if not p.is_file():
            raise ValueError('assembly input missing: ' + item)
        found[item] = sha(p)
        # incbin data is opaque, rather than necessarily UTF-8 assembly.
        if p.suffix.lower() not in ('.s', '.inc', '.h'):
            continue
        for line in p.read_text().splitlines():
            if not re.match(r'\s*(?:\.(?:include|incbin)|#\s*include)\b', line):
                continue
            hit = re.fullmatch(r'\s*(?:\.(?:include|incbin)|#\s*include)\s+"([^"]+)"\s*(?:,.*)?', line)
            if not hit:
                raise ValueError('unmodelled assembly dependency: ' + line)
            candidates = [p.parent/hit[1], root/'include'/hit[1], root/hit[1],
                          root/'build_ovl_gate'/hit[1]]
            matches = [q for q in candidates if q.is_file()]
            if not matches:
                raise ValueError('missing assembly dependency: ' + line)
            for q in matches:
                lexical = Path(os.path.abspath(q))
                if not lexical.is_relative_to(root):
                    raise ValueError('assembly dependency escapes root')
                pending.append(str(lexical.relative_to(root)))
    return found


def module_fingerprint(root,m):
    cache=_SNAPSHOT.get();key=('module_fingerprint',str(root),m['key'])
    if cache is not None and key in cache:return cache[key]
    G,_=_authorities();value=G.fingerprint(m,root)
    if cache is not None:cache[key]=value
    return value


def window_modules(root):
    cache = _SNAPSHOT.get()
    key = ('window_modules',str(root))
    if cache is not None and key in cache:return cache[key]
    G,S = _authorities();out = {}
    if (root/'config/overlays/modules.json').exists() and not (root/'config/overlay_modules_disabled').exists():
        parsed=S.windows(root)
        for m in G.load_modules(root):
            for wn in G.affected_windows(m,root,parsed_windows=parsed):out.setdefault(wn,[]).append(m)
    if cache is not None:cache[key]=out
    return out


def modules_for_window(root,cfg,target=None):
    """Independent geometric selection; selected TUs still validate canonically.

    Avoid parsing every other YAML and validating every unrelated module for
    each worker window. Global registry/graph checks stay on the landing path.
    The complete fingerprint validates any selected supplied module anew.
    """
    G,S=_authorities();cache=_SNAPSHOT.get();key=('module_roster',str(root))
    if not (root/'config/overlays/modules.json').exists() or (root/'config/overlay_modules_disabled').exists():return []
    if cache is not None and key in cache:modules=cache[key]
    else:
        modules=G.read_json(root/'config/overlays/modules.json')['modules']
        if cache is not None:cache[key]=modules
    w=cfg['standalone_build']['window'];lo,hi=S.num(w['file_start']),S.num(w['file_end'])
    scoped=S.enabled(root);out=[]
    for m in modules:
        if scoped:
            family='dungeon' if m['container']=='dungeon_engine' else m['container']
            if cfg['name'].partition('_')[0]!=family:continue
            spans=G.module_extents(m)
        else:
            name=Path(target).name if target else cfg['name']
            if not name.startswith(m['container']):continue
            spans=[G.module_span(m)]
        if any(lo<end and start<hi for start,end in spans):out.append(m)
    return out


def c_input_policy(root,names):
    # -M cannot describe files pulled in by inline assembler, or a compiler's
    # wall clock. The current production C corpus has neither; refuse new
    # unsupported forms rather than pretend their dependencies are complete.
    G,_=_authorities()
    for name in names:
        if Path(name).suffix not in ('.c','.h'):continue
        text=G.read_text(local(root,name))
        if re.search(r'\b__(?:DATE|TIME|TIMESTAMP)__\b',text):
            raise ValueError('volatile compiler input requires a proof adapter: '+name)
        text=re.sub(r'/\*.*?\*/|//[^\n]*','',text,flags=re.S)
        text=text.replace('\\\n','')
        for line in text.splitlines():
            if re.match(r'\s*#\s*define\s+INCLUDE_(?:ASM|RODATA)(?:\s|\()',line):continue
            if re.match(r'\s*#\s*(?:ifn?def|endif|else)\b',line):continue
            if re.fullmatch(r'\s*__asm__\(\s*"\.include \\"include/(?:macro|labels)\.inc\\"\\n"\s*\);\s*',line):continue
            if re.search(r'\bINCLUDE_(?:ASM|RODATA)\b|\.(?:include|incbin)\b',line):
                raise ValueError('inline assembler file input requires a proof adapter: '+name)


def source_inputs(root,names,version,flags,G):
    cache=_SNAPSHOT.get();key=('source_inputs',str(root),tuple(names),version,flags)
    if cache is not None and key in cache:return cache[key]
    _,S=_authorities();value=S.include_inputs(root,names,version,flags,G)
    c_input_policy(root,value)
    if cache is not None:cache[key]=value
    return value


def bank_inputs(root,family,offsets,rosters,G):
    cache=_SNAPSHOT.get();_,S=_authorities()
    if cache is None or family not in ('town','dungeon'):
        return S.noreturn(root,family,offsets,rosters,{},G)
    import gen_noreturn_syms as C
    stamp_key=('bank_stamps',str(root),family)
    if stamp_key not in cache:cache[stamp_key]=C._scope_stamps(root,family)
    stamps=cache[stamp_key]
    selected=set();regions=[];seen=set();scopes=set()
    rr=records(root/f'config/overlays/{family}.rowbase.jsonl')
    for off in sorted(set(offsets)):
        scope,sources=C._scope_sources(root,family,stamps,off)
        scopes.add((scope if scope is not None else (off,off,'isolated:'+format(off,'X')),sources))
        selected.update(sources)
        if scope is not None and scope[2] not in seen:
            seen.add(scope[2]);regions.append(next(r for r in rr if r['region']==scope[2]))
    key=('bank_inputs',str(root),family,tuple(sorted(scopes,key=repr)))
    if key not in cache:
        # Same frozen-source selector as compile evidence, without repeatedly
        # decoding/indexing an entire split table at every isolated offset.
        paths={str(p.relative_to(root)):sha(p) if p.is_file() else None for p in selected}
        cache[key]=dict(semantic=C.scoped_inputs(family,offsets,root=root),regions=regions,
                        frozen_sources=dict(sorted(paths.items())),
                        false_member_records=[r for r in records(root/'config/noreturn_false_members.jsonl')
                                              if r.get('family',r.get('container'))==family])
    return cache[key]


def window_inputs(root, target):
    """Production window's semantic records + actual -M closure + byte identities.

    All matched-source groups are overbound even if only_if_missing suppresses
    an earlier group. Global header namespaces are bound too: addition of a
    previously absent include must not preserve an old -M dependency result.
    """
    import yaml
    G, S = _authorities()
    root = Path(root).absolute()
    if not target.startswith('config/overlays/') or not target.endswith('.overlay.yaml'):
        raise ValueError('not a production window')
    cfg = yaml.safe_load(local(root, target).read_text())
    sb = cfg['standalone_build'];w = sb['window']
    start, end = S.num(w['file_start']), S.num(w['file_end'])
    if not 0 <= start < end:
        raise ValueError('empty production window')
    family = S.family(cfg['name'].split('_')[0])
    sources = {};rosters = {};versions = set();offsets = set()
    groups = [{'results':sb['split_results']}, *sb.get('matched_sources', [])]
    for group in groups:
        name = group['results'];parts = Path(name).parts
        if len(parts) != 3 or parts[0] != 'overlays' or parts[2] != 'overlay_first_pass_results.json':
            raise ValueError('unknown split authority: ' + name)
        unit = parts[1]
        table = records(root/'ledger/splits'/f'{unit}.jsonl')
        selected = [r for r in table if S.intersects(r, start, end)]
        rosters[unit] = selected
        if 'source_dir' not in group:
            continue
        for row in selected:
            if row.get('result') != 'MATCH' or (group.get('skip_rerun', True) and row.get('rerun')):
                continue
            # Production load_matches admits only completely contained rows.
            if not start <= row['foff'] < row['foff']+row['size'] <= end:
                continue
            kind = row.get('source_kind', 'c')
            if kind == 'c':
                version, flags = S.parse_config_label(root, row.get('config') or '2.7.2', G)
                versions.add(version);offsets.add(row['foff'])
                name = S.matched_source(root, group, row)
                sources.update(source_inputs(root, [name], version, flags, G))
            elif kind in ('platform_asm', 'game_asm'):
                sources.update(assembly_inputs(root, row['asm_path']))
            else:
                raise ValueError('unknown window source kind: ' + kind)
    modules = []
    selected_modules=modules_for_window(root,cfg,target)
    if selected_modules:
        for m in selected_modules:
            version = G.module_compiler(m);versions.add(version)
            starts = [m['source'],*m['headers'],*(a['source'] for a in G.all_members(m)),
                      *(p for p in m['review_inputs'] if p.endswith(('.c','.h'))),
                      *(d['declaration'] for d in m['imports'] if d['kind']=='runtime_data')]
            sources.update(source_inputs(root, starts, version, '-G0', G))
            offsets.update(a['foff'] for a in G.all_members(m))
            modules.append(dict(entry=m, fingerprint=module_fingerprint(root,m)))
    registry = [r for r in records(root/'ledger/rows.jsonl')
                if S.family(r.get('container','')) == family and S.intersects(r, start, end)]
    ids = {r['id'] for r in registry}
    symbols = ['config/names.tsv','config/slus_006.14.symbols.txt','config/slus_006.14.yaml',
               'config/overlays/abs_syms.txt', cfg.get('options',{}).get('symbol_addrs_path'),
               f'config/overlays/{family}.as_flags.jsonl',f'config/overlays/{family}.rodata_owners.jsonl',
               f'config/overlays/{family}.rowbase.jsonl','config/overlay_modules_disabled']
    suffix = '' if family == 'main' else '.'+family
    symbols.extend(f'config/{kind}_syms{suffix}.txt' for kind in ('noreturn','sibcall'))
    # Capture all include namespace bytes conservatively; source-local header
    # additions and transitive/macro includes are independently rediscovered -M.
    headers = {str(p.relative_to(root)):sha(p) for p in tree_files(root/'include')}
    # Full container identity is intentionally conservative: extraction/gate
    # validates the configured sha1 of the entire container, then compares slice.
    container = root/'work/disc/containers'/G.CONTAINERS[family]
    with container.open('rb') as stream:
        stream.seek(start);retail = stream.read(end-start)
    if len(retail) != end-start:
        raise ValueError('truncated retail window')
    return dict(schema=SCHEMA, kind='overlay-window', target=target, config=cfg,
                config_sha256=sha(root/target), registry=registry, splits=rosters, sources=sources,
                assignments=[r for r in records(root/'ledger/modules.jsonl') if r['id'] in ids],
                modules=modules, headers=headers, symbols=optional(root,symbols),
                noreturn=bank_inputs(root,family,offsets,rosters,G),
                retail=dict(container_sha256=sha(container),slice_sha256=hashlib.sha256(retail).hexdigest(),
                            start=start,end=end),
                tools=dict(canonical=S.identities(root,versions,G),extra=extra_tools(root)),
                environment=environment())


def inputs(root, kind, target):
    root = Path(root).absolute()
    if kind == 'overlay-window':
        return window_inputs(root, target)
    G, S = _authorities()
    if kind in ('overlay-module', 'native-candidate'):
        m = next(m for m in G.load_modules(root) if m['key']==target)
        version = G.module_compiler(m)
        starts = [m['source'],*m['headers'],*(a['source'] for a in G.all_members(m))]
        return dict(schema=SCHEMA, kind=kind, target=target, fingerprint=G.fingerprint(m,root),
                    actual_includes=source_inputs(root, starts, version, '-G0', G),
                    tools=extra_tools(root), environment=environment(),
                    windows={wn:window_inputs(root,wn) for wn in G.affected_windows(m,root)})
    if kind == 'row-score':
        row = next(r for r in records(root/'ledger/rows.jsonl') if r['id']==target)
        if row.get('kind')!='overlay':
            raise ValueError('SLUS row receipts require a separate proof adapter')
        return dict(schema=SCHEMA,kind=kind,target=target,row=row,
                    window=window_inputs(root,row['gate_config']),
                    raw=optional(root,[f"raw/{row['container']}/{Path(row['c_path']).name}"]))
    raise ValueError('unsupported portable proof kind: '+str(kind))


def inventory(directory):
    result = {}
    for p in sorted(Path(directory).rglob('*')):
        if p.is_symlink():
            raise ValueError('linked portable evidence')
        if p.is_file() and p != Path(directory)/'proof-receipt.json':
            result[str(p.relative_to(directory))] = sha(p)
    return result


def publish(directory, kind, target, before, after, result, *, metadata=None):
    if kind not in KINDS or before != after:
        raise ValueError('proof inputs changed during production')
    if result != 'MATCH':
        raise ValueError('only successful exact proofs may be published')
    directory = Path(directory)
    doc = dict(schema=SCHEMA,kind=kind,target=target,result='MATCH',inputs=before,
               inputs_sha256=hashed(before),artifacts=inventory(directory),metadata=metadata or {})
    path = directory/'proof-receipt.json'
    path.write_bytes(encoded(doc)+b'\n')
    return path


def verify(root, directory, *, expected_kind=None, expected_target=None):
    """Re-discover inputs on this tree; stale/invalid is a miss, never authority."""
    directory = Path(directory)
    doc = json.loads((directory/'proof-receipt.json').read_text())
    if (doc.get('schema')!=SCHEMA or doc.get('result')!='MATCH' or doc.get('kind') not in KINDS
            or expected_kind is not None and doc.get('kind')!=expected_kind
            or expected_target is not None and doc.get('target')!=expected_target):
        raise ValueError('portable proof identity differs')
    if doc.get('inputs_sha256')!=hashed(doc.get('inputs')):
        raise ValueError('portable proof input record corrupt')
    if inventory(directory)!=doc.get('artifacts') or not doc.get('artifacts'):
        raise ValueError('portable proof artifacts changed or missing')
    current = inputs(root,doc['kind'],doc['target'])
    if current != doc['inputs']:
        raise ValueError('portable proof inputs changed')
    if doc['kind']=='overlay-window':
        blob = directory/'window.bin'
        if sha(blob)!=current['retail']['slice_sha256'] or blob.stat().st_size!=current['retail']['end']-current['retail']['start']:
            raise ValueError('portable window differs from retail')
    return doc


def validate_view(root,view,target):
    """A current source hash cannot authorize a stale exported tool/row facade."""
    import yaml
    root=Path(root).absolute();view=Path(view).absolute();G,_=_authorities()
    for name in ('src','include','ledger','config/overlays','toolchain','.venv'):
        if (view/name).resolve()!=(root/name).resolve():
            raise ValueError('proof view differs from canonical inputs: '+name)
    expected_tools={p.name for p in (root/'tools/gate').iterdir() if p.is_file() and p.suffix in ('.py','.sh')}|{'overlay_module_evidence.py'}
    actual_tools={p.name for p in (view/'tools').iterdir() if p.is_file() and p.suffix in ('.py','.sh')}
    if actual_tools!=expected_tools:raise ValueError('exported gate tool namespace differs')
    if (view/'asm').resolve()!=(root/'build_slus/asm').resolve():raise ValueError('exported assembly facade differs')
    for p in (root/'tools/gate').iterdir():
        if p.is_file() and p.suffix in ('.py','.sh'):
            q=view/'tools'/p.name
            if not q.is_file() or sha(q)!=sha(p):raise ValueError('stale exported gate tool: '+p.name)
    for name in ('tools/overlay_module_evidence.py','tools/build/slus_rodata_trim.py',
                 'tools/fidelity/aspsx_diff.py','tools/fidelity/objread.py','tools/fidelity/certify_overlay_module.py'):
        if sha(view/name)!=sha(root/name):raise ValueError('stale exported proof tool: '+name)
    for p in (root/'config').glob('*'):
        # mk_ovl exports these shared build/evidence inputs at identical paths.
        if p.is_file() and (p.name in ('names.tsv','slus_006.14.yaml','slus_006.14.symbols.txt',
                          'overlay_fingerprint_schema','noreturn_false_members.jsonl')
                          or p.name.startswith(('noreturn_syms','sibcall_syms'))):
            if sha(view/'config'/p.name)!=sha(p):raise ValueError('stale exported config: '+p.name)
    cfg=yaml.safe_load((root/target).read_text());sb=cfg['standalone_build']
    family=cfg['name'].partition('_')[0]
    family='dungeon' if family=='dungeon_engine' else family
    container=local(view,sb.get('extract',{}).get('container_path') or cfg['options']['target_path'])
    canonical=root/'work/disc/containers'/G.CONTAINERS[family]
    if sha(container)!=sha(canonical):raise ValueError('exported retail container differs')
    for group in [{'results':sb['split_results']},*sb.get('matched_sources',[])]:
        name=group['results'];unit=Path(name).parts[1]
        if G.read_json(view/name)!=records(root/'ledger/splits'/f'{unit}.jsonl'):
            raise ValueError('exported split roster differs: '+name)
        if 'source_dir' in group:
            parts=Path(group['source_dir']).parts
            if len(parts)!=3 or parts[0]!='overlays' or parts[2]!='first_pass_matched':
                raise ValueError('unmodelled source facade')
            family={'dungeon_engine':'dungeon','dungeon_engine_pilot_only':'dungeon_engine'}.get(parts[1],parts[1])
            if (view/group['source_dir']).resolve()!=(root/'src'/family).resolve():
                raise ValueError('exported source facade differs: '+group['source_dir'])
    return True


def export_window(root, view, target, directory, before, lines):
    """Called under the canonical window lock after an actual successful gate."""
    import yaml
    validate_view(root,view,target)
    directory = Path(directory)
    if directory.exists():
        raise ValueError('portable proof output already exists')
    directory.mkdir(parents=True)
    try:
        cfg = yaml.safe_load((Path(root)/target).read_text())
        name = cfg['name'];bd=Path(view)/cfg['standalone_build']['work_dir']/name/'build'
        shutil.copy2(bd/(name+'.window.bin'),directory/'window.bin')
        shutil.copy2(bd.parent/(name+'_manifest.json'),directory/'manifest.json')
        (directory/'gate.log').write_text('\n'.join(lines)+'\n')
        if (bd/'modules.json').is_file():
            shutil.copy2(bd/'modules.json',directory/'modules.json')
            if (bd/'modules').is_dir():shutil.copytree(bd/'modules',directory/'modules')
        after=inputs(root,'overlay-window',target)
        if sha(directory/'window.bin')!=after['retail']['slice_sha256']:
            raise ValueError('exported gate bytes differ from retail')
        return publish(directory,'overlay-window',target,before,after,'MATCH')
    except BaseException:
        shutil.rmtree(directory)
        raise


def import_window(root, view, target, source, fresh, transaction, record):
    """Rebind verified lane artifacts to the existing transaction-local format."""
    import yaml
    doc=verify(root,source,expected_kind='overlay-window',expected_target=target)
    cfg=yaml.safe_load((Path(root)/target).read_text());name=cfg['name']
    source=Path(source);fresh=Path(fresh);dest=fresh/name
    # Windows without modules need only their exact retail bytes + current
    # journal record. Native projections additionally serve certify's reader.
    if (source/'modules.json').exists() and json.loads((source/'modules.json').read_text()):
        if dest.exists():raise ValueError('duplicate portable window')
        dest.mkdir(parents=True)
        for p in source.iterdir():
            if p.name=='proof-receipt.json':continue
            if p.is_dir():shutil.copytree(p,dest/p.name)
            else:shutil.copy2(p,dest/p.name)
        rec=dict(schema=1,transaction=transaction,config=target,gate=record,
                 artifacts=inventory(dest))
        (dest/'receipt.json').write_bytes(encoded(rec)+b'\n')
    return doc


def export_module(root, key, directory):
    """Freeze an already valid complete certificate; diagnostic scores cannot enter."""
    from overlay_module_evidence import certificate_reason
    G,_=_authorities();root=Path(root);directory=Path(directory)
    m=next(m for m in G.load_modules(root) if m['key']==key)
    certificate_bytes=(root/'ledger/modules'/('overlay_'+key+'.json')).read_bytes()
    cert=json.loads(certificate_bytes)
    before=inputs(root,'overlay-module',key)
    reason=certificate_reason(m,cert,root)
    if reason:raise ValueError('cannot carry invalid certificate: '+reason)
    directory.mkdir(parents=True,exist_ok=False)
    try:
        (directory/'certificate.json').write_bytes(certificate_bytes)
        refs=[cert['proof_dir'],*(w['proof_dir'] for w in cert['windows'])]
        for i,name in enumerate(refs):
            path=local(root,name)
            if not path.resolve().is_relative_to(root.resolve()):raise ValueError('certificate proof escapes root')
            if any(p.is_symlink() for p in path.rglob('*')):raise ValueError('linked certificate artifact')
            shutil.copytree(path,directory/'proofs'/str(i))
        return publish(directory,'overlay-module',key,before,inputs(root,'overlay-module',key),'MATCH',
                       metadata=dict(proof_dirs=refs))
    except BaseException:
        shutil.rmtree(directory)
        raise


def import_module(root, source):
    """Validate the original certificate at its original relative paths; no re-signing."""
    from overlay_module_evidence import certificate_reason
    doc=verify(root,source,expected_kind='overlay-module')
    root=Path(root);source=Path(source);key=doc['target']
    cert=json.loads((source/'certificate.json').read_text())
    refs=[cert['proof_dir'],*(w['proof_dir'] for w in cert['windows'])]
    if doc['metadata'].get('proof_dirs')!=refs:raise ValueError('certificate proof directories differ')
    # Limit package-directed writes to durable module proof directories. Every
    # imported artifact is guarded by the reviewed package inventory and above
    # receipt. Existing evidence is atomically replaced file by file.
    staged=[]
    for i,name in enumerate(refs):
        if not name.startswith(('build_ovl_gate/work/module_proofs/','build_ovl/work/module_proofs/')):
            raise ValueError('unsupported module proof destination')
        dest=private(root,name)
        for p in (source/'proofs'/str(i)).rglob('*'):
            if p.is_file():
                q=private(root,str((dest/p.relative_to(source/'proofs'/str(i))).relative_to(root)))
                staged.append((p,q))
    for p,q in staged:
        q.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(p,q)
    G,_=_authorities();m=next(m for m in G.load_modules(root) if m['key']==key)
    reason=certificate_reason(m,cert,root)
    if reason:raise ValueError('carried certificate failed canonical validation: '+reason)
    target=private(root,'ledger/modules/overlay_'+key+'.json')
    target.parent.mkdir(parents=True,exist_ok=True)
    target.write_bytes((source/'certificate.json').read_bytes())
    return doc


def main(argv=None):
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root',type=Path,required=True)
    commands=ap.add_subparsers(dest='command',required=True)
    p=commands.add_parser('verify');p.add_argument('directory',type=Path)
    p=commands.add_parser('export-module');p.add_argument('key');p.add_argument('directory',type=Path)
    a=ap.parse_args(argv)
    with input_snapshot():
        if a.command=='verify':doc=verify(a.root,a.directory);print(json.dumps(dict(kind=doc['kind'],target=doc['target'],result='CURRENT')))
        else:print(export_module(a.root,a.key,a.directory))

if __name__=='__main__':main()


def package_receipts(package):
    """Only inventoried, immutable package evidence can be a landing candidate."""
    package=Path(package).resolve();index=package/'proofs.json'
    if not index.exists():return []
    sealed=json.loads((package/'package.sha256.json').read_text())
    if sealed.get('proofs.json')!=sha(index):raise ValueError('unsealed portable proof index')
    entries=json.loads(index.read_text())
    if not isinstance(entries,list):raise ValueError('portable proof index must be a list')
    result=[];seen=set()
    for entry in entries:
        kind,target,name=entry['kind'],entry['target'],entry['directory']
        if kind not in KINDS or (kind,target) in seen:raise ValueError('duplicate/unknown portable proof')
        seen.add((kind,target));directory=private(package,name)
        for p in [directory/'proof-receipt.json',*directory.rglob('*')]:
            if p.is_symlink():raise ValueError('linked portable package evidence')
            if p.is_file():
                rel=str(p.relative_to(package))
                if sealed.get(rel)!=sha(p):raise ValueError('unsealed portable evidence: '+rel)
        doc=json.loads((directory/'proof-receipt.json').read_text())
        if doc.get('kind')!=kind or doc.get('target')!=target:raise ValueError('portable proof index identity differs')
        result.append(dict(kind=kind,target=target,directory=str(directory),package=str(package)))
    return result


def module_window_proofs(root, source, output):
    """A canonically validated module certificate already contains exact windows."""
    source=Path(source);output=Path(output)
    doc=verify(root,source,expected_kind='overlay-module')
    cert=json.loads((source/'certificate.json').read_text());result={}
    for i,window in enumerate(cert['windows'],1):
        target=window['config'];directory=output/Path(target).stem
        directory.mkdir(parents=True,exist_ok=False)
        for name in ('window.bin','manifest.json','gate.log'):
            shutil.copy2(source/'proofs'/str(i)/name,directory/name)
        before=doc['inputs']['windows'][target]
        after=window_inputs(root,target)
        publish(directory,'overlay-window',target,before,after,'MATCH',metadata=dict(derived_from_module=doc['target']))
        result[target]=str(directory)
    return result
