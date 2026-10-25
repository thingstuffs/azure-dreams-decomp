"""Decision 74(b,c): evidence-based SDK routing and conservative data ownership.

No SDK headers are read or copied. Signatures below are independently written call
contracts using the game's scalar aliases and opaque pointers for SDK records.
Unknown library signatures and ambiguous data views remain local. The ordinary
TU/header byte decision also applies to every declaration introduced here.
"""
from __future__ import annotations

import re
from collections import Counter, defaultdict
from dataclasses import replace

import cscan
import model as M

# Return spelling, parameter spellings. Only entries actually referenced are emitted.
SDK = {}
def _sig(names, ret, args):
    for name in names.split():
        SDK[name] = (ret, args)

_sig('rsin rcos SquareRoot0 SquareRoot12', 's32', 's32')
_sig('ratan2', 's32', 's32, s32')
_sig('PushMatrix PopMatrix InitGeom', 'void', 'void')
_sig('SetRotMatrix SetTransMatrix SetLightMatrix SetColorMatrix', 'void', 'void *')
_sig('SetGeomOffset SetFogFar', 'void', 's32, s32')
_sig('SetGeomScreen', 'void', 's32')
_sig('SetBackColor SetFarColor', 'void', 's32, s32, s32')
_sig('CompMatrix ApplyMatrixSV', 'void *', 'void *, void *, void *')
_sig('ScaleMatrix TransMatrix RotMatrix TransposeMatrix', 'void *', 'void *, void *')
_sig('RotMatrixX RotMatrixY RotMatrixZ', 'void *', 's32, void *')
_sig('ReadRotMatrix', 'void *', 'void *')
_sig('RotTransPers', 's32', 'void *, s32 *, s32 *, s32 *')
_sig('RotTrans', 'void', 'void *, void *, s32 *')
_sig('NormalClip', 's32', 's32, s32, s32')
_sig('RotTransPers4', 's32', 'void *, void *, void *, void *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *')
_sig('RotAverage4', 's32', 'void *, void *, void *, void *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *')
_sig('GetTPage', 'u16', 's32, s32, s32, s32')
_sig('GetClut', 'u16', 's32, s32')
_sig('LoadTPage', 'u16', 'u32 *, s32, s32, s32, s32, s32, s32')
_sig('LoadClut', 'u16', 'u32 *, s32, s32')
_sig('AddPrim CatPrim', 'void', 'void *, void *')
_sig('AddPrims', 'void', 'void *, void *, void *')
_sig('TermPrim DrawPrim DrawOTag', 'void', 'void *')
_sig('SetSemiTrans SetShadeTex', 'void', 'void *, s32')
_sig('SetPolyF3 SetPolyFT3 SetPolyG3 SetPolyGT3 SetPolyF4 SetPolyFT4 SetPolyG4 SetPolyGT4 SetSprt SetSprt8 SetSprt16 SetTile SetTile1 SetTile8 SetTile16 SetLineF2 SetLineG2 SetLineF3 SetLineG3 SetLineF4 SetLineG4', 'void', 'void *')
_sig('SetDrawMode', 'void', 'void *, s32, s32, s32, void *')
_sig('SetDrawTPage', 'void', 'void *, s32, s32, s32')
_sig('SetDefDrawEnv SetDefDispEnv', 'void *', 'void *, s32, s32, s32, s32')
_sig('PutDrawEnv PutDispEnv GetDrawEnv GetDispEnv', 'void *', 'void *')
_sig('SetDrawArea SetDrawOffset', 'void', 'void *, void *')
_sig('LoadImage StoreImage', 's32', 'void *, u32 *')
_sig('MoveImage', 's32', 'void *, s32, s32')
_sig('ClearImage', 's32', 'void *, u8, u8, u8')
_sig('ClearOTag ClearOTagR', 'u32 *', 'u32 *, s32')
_sig('DrawSync ResetGraph SetGraphDebug SetGraphReverse SetDispMask', 's32', 's32')
_sig('VSync SetVideoMode', 's32', 's32')
_sig('GetVideoMode ResetCallback StopCallback RestartCallback CheckCallback', 's32', 'void')
_sig('CdInit', 's32', 'void')
_sig('CdSync CdReady CdReadSync', 's32', 's32, u8 *')
_sig('CdControl CdControlB', 's32', 'u8, u8 *, u8 *')
_sig('CdControlF', 's32', 'u8, u8 *')
_sig('CdRead', 's32', 's32, u32 *, s32')
_sig('CdRead2 CdReset', 's32', 's32')
_sig('CdGetSector', 's32', 'void *, s32')
_sig('CdIntToPos', 'void *', 's32, void *')
_sig('CdPosToInt', 's32', 'void *')
_sig('StUnSetRing StClearRing', 'void', 'void')
_sig('StSetRing', 'void', 'u32 *, s32')
_sig('rand', 's32', 'void')
_sig('abs', 's32', 's32')
_sig('srand', 'void', 'u32')
_sig('bzero', 'void', 'void *, s32')
_sig('memcpy memmove', 'void *', 'void *, const void *, s32')
_sig('memset', 'void *', 'void *, s32, s32')
_sig('strlen', 's32', 'const char *')
_sig('strcmp', 's32', 'const char *, const char *')
_sig('strncmp', 's32', 'const char *, const char *, s32')
_sig('strcpy strcat', 'char *', 'char *, const char *')
_sig('strncpy strncat', 'char *', 'char *, const char *, s32')
_sig('printf', 's32', 'const char *, ...')
_sig('puts', 's32', 'const char *')
_sig('FlushCache', 'void', 'void')
_sig('InitHeap', 'void', 'void *, u32')


def library_symbols(root):
    """SLUS address -> (library, canonical name, evidence), based on pinned layout."""
    yaml = root / 'config/slus_006.14.yaml'
    sym = root / 'config/slus_006.14.symbols.txt'
    if not yaml.exists() or not sym.exists():
        return {}, {}, []
    entries = []
    for line in yaml.read_text().splitlines():
        m = re.match(r'\s*- \[(0x[0-9a-fA-F]+),\s*(\w+)(?:,\s*([^\]]+))?\]', line)
        if m:
            off, kind, path = m.groups()
            entries.append((int(off, 16), kind, (path or '').strip()))
    entries.sort()
    spans = [(a + 0x8002C800, b + 0x8002C800, p.split('/')[1], p)
             for (a, k, p), (b, _, _) in zip(entries, entries[1:])
             if k == 'asm' and p.startswith('psyq/')]
    names, addresses = {}, defaultdict(list)
    for no, line in enumerate(sym.read_text().splitlines(), 1):
        m = re.match(r'(\w+)\s*=\s*(0x[0-9a-fA-F]+);', line)
        if not m:
            continue
        name, address = m[1], int(m[2], 16)
        names[name] = address
        for a, b, lib, p in spans:
            if a <= address < b:
                addresses[address].append((lib, name, f'config/slus_006.14.symbols.txt:{no};config/slus_006.14.yaml:{p}'))
                break
    return names, addresses, spans


def _fd(name, proto, path, kind, container, line=1):
    it = cscan.scan(proto + ';').items[0]
    d = it.decls[0]
    fd = M.FuncDef(name, path, line, False, tuple(it.spec), d.ptr,
                   M.proto_params(d.params) or [], proto, container,
                   varargs=any(p == ['...'] for p in d.params or []), complex=d.complex)
    fd.kind = kind
    return fd


def _aliases(root):
    out = {}
    p = root / 'config/names.tsv'
    if p.exists():
        for line in p.read_text().splitlines():
            cols = line.split('\t')
            if len(cols) >= 3 and not line.startswith('#'):
                out[cols[1]] = cols[2]
    return out


def alias_groups(root, defs=None):
    """All spellings ccproc maps to a label, plus explicit resident link aliases.

    Keep alternatives instead of selecting the last semantic rename: live
    alternatives in one image require an ownership hold.
    """
    groups = defaultdict(set)
    by_address = defaultdict(set)
    p = root / 'config/names.tsv'
    rows = []
    if p.exists():
        for line in p.read_text().splitlines():
            cols = line.split('\t')
            if len(cols) >= 3 and not line.startswith('#'):
                old, new = cols[1].strip(), cols[2].strip()
                groups[old].update((old, new))
                m = re.fullmatch(r'func_([0-9A-Fa-f]{8})', old)
                if m:
                    by_address[int(m[1], 16)].update((old, new))
    aliases = defaultdict(set)
    for old, names in groups.items():
        for spelling in names:
            aliases[spelling].update(names)
    symbols = root / 'config/slus_006.14.symbols.txt'
    linked = {}
    if symbols.exists():
        for line in symbols.read_text().splitlines():
            m = re.match(r'(\w+)\s*=\s*(0x[0-9A-Fa-f]+);', line)
            if m:
                linked[m[1]] = int(m[2], 16)
    # C subsegment bounds are authoritative; do not infer an overlay alias from
    # a coincident numeric address in another image.
    layout = root / 'config/slus_006.14.yaml'
    entries = []
    if layout.exists():
        for line in layout.read_text().splitlines():
            m = re.match(r'\s*- \[(0x[0-9A-Fa-f]+),\s*(\w+)', line)
            if m:
                entries.append((int(m[1], 16), m[2]))
    entries.sort()
    ranges = [(a + 0x8002C800, b + 0x8002C800) for (a,k),(b,_) in zip(entries,entries[1:]) if k == 'c']
    if defs:
        for name, ds in defs.items():
            if not any(not d.static and d.container == M.RESIDENT for d in ds):
                continue
            m = re.fullmatch(r'func_([0-9A-Fa-f]{8})', name)
            address = linked.get(name, int(m[1],16) if m else None)
            if address is not None and any(a <= address < b for a,b in ranges):
                by_address[address].add(name)
    resident = set()
    for name, address in linked.items():
        if any(a <= address < b for a,b in ranges) and address in by_address:
            aliases[name].update(by_address[address])
            resident.add(name)
    return dict(aliases), resident


def augment_functions(corpus, tindex, defs, sites, functions):
    """Return synthetic definitions + rows and one classification for every no-C site."""
    import plan as P
    names, addresses, spans = library_symbols(corpus.root)
    aliases, resident_aliases = alias_groups(corpus.root, defs)
    asm = defaultdict(list)
    for rel in corpus.c_files:
        # Only real macro invocations, never mentions in comments.
        text = cscan.mask(corpus.text(rel))
        for m in re.finditer(r'\bINCLUDE_ASM\s*\([^,]+,\s*(\w+)\s*\)', text):
            asm[m[1]].append(rel)
    result, census = {}, []
    no_c = [s for s in sites if M.bind(s.path, s.name, defs)[1] == 'no_c_definition']
    by_name = defaultdict(list)
    for s in no_c:
        by_name[s.name].append(s)
    for name, ss in sorted(by_name.items()):
        address = names.get(name)
        numeric = re.fullmatch(r'func_([0-9a-fA-F]{8})', name)
        if address is None and numeric:
            address = int(numeric[1], 16)
        lib = canonical = evidence = owner = problem = ''
        category = 'unknown'
        linked = addresses.get(address, [])
        if linked:
            lib = linked[0][0]
            known = sorted({n for l, n, e in linked if n in SDK})
            canonical = name if name in SDK else (known[0] if len(known) == 1 else '')
            evidence = linked[0][2]
            category = 'psyq_library'
        elif address is not None and any(a <= address < b for a, b, l, p in spans):
            a, b, lib, segment = next(s for s in spans if s[0] <= address < s[1])
            category = 'psyq_library'
            evidence = 'config/slus_006.14.yaml:' + segment + '; unnamed library address'
        elif name == 'abs':
            # Compiler/libc integer helper; no out-of-line SLUS segment is needed.
            category, lib, canonical = 'psyq_library', 'libc', name
            evidence = 'game call sites: integer absolute-value builtin'
        row = None
        if category == 'psyq_library':
            if canonical:
                ret, args = SDK[canonical]
                proto = f'{ret} {name}({args})'
                fd = _fd(name, proto, 'include/common.h', 'sdk', M.RESIDENT)
                # SDK signatures here contain only common scalars/opaque pointers.
                row = P.FnRow(name, fd, header='include/sdk/' + lib + '.h', proto=proto)
                row.kind = 'sdk'
                owner = row.header
            else:
                problem = 'sdk_signature_unresolved'
        elif name in aliases:
            targets = aliases[name]
            ds = [d for target in sorted(targets) for d in defs.get(target, []) if not d.static and
                  (name not in resident_aliases or d.container == M.RESIDENT)]
            if ds:
                category = 'game_c_alias'
                evidence = ('config/slus_006.14.symbols.txt;config/slus_006.14.yaml:' if name in resident_aliases
                            else 'config/names.tsv:') + name + '->' + ','.join(sorted(targets))
                problem = 'alias_multiple_definitions' if len(ds) > 1 else ''
            if len(ds) == 1:
                d = ds[0]
                target = d.name
                fr = functions.get(target) or functions.get(target + '@' + d.container)
                if fr and fr.status == 'header':
                    proto = re.sub(r'\b' + re.escape(target) + r'(?=\s*\()', name, fr.proto)
                    fd = replace(d, name=name, proto=proto)
                    fd.kind = 'alias'
                    row = P.FnRow(name, fd, fr.header, type_headers=fr.type_headers, tags=fr.tags, proto=proto)
                    row.kind = 'alias'
                    owner = fr.header
                else:
                    problem = 'alias_definition_held'
        elif name in asm:
            paths = sorted(set(asm[name]))
            category, evidence = 'game_asm', ';'.join(paths)
            # No guessed K&R contract: all explicit declaration types must agree.
            typed = [s for s in ss if s.params is not None and not s.complex]
            keys = {(M.canon(s.ret_spec, s.ret_ptr, tindex.visible(s.path)),
                     tuple(M.canon(*M.param_parts(p)[:2], tindex.visible(s.path)) for p in s.params))
                    for s in typed}
            if len(paths) == 1 and len(keys) == 1:
                s = sorted(typed, key=lambda x: (x.path, x.line))[0]
                proto = re.sub(r'^\s*extern\s+', '', M.proto_text_from(cscan.mask(s.text))).rstrip(';')
                fd = _fd(name, proto, s.path, 'asm', M.container_of(paths[0]), s.line)
                th, tg, sub, problem = P.type_needs(fd, tindex)
                if not problem:
                    fd.path = paths[0]
                    row = P.FnRow(name, fd, P.header_for(paths[0]), type_headers=th, tags=tg,
                                  proto=P.substituted_proto(fd, sub))
                    row.kind = 'asm'
                    owner = row.header
            else:
                problem = 'asm_contract_ambiguous'
        if row:
            result[name] = row
        elif not problem:
            problem = 'no_link_or_definition_evidence'
        for s in ss:
            if not s.in_header:
                census.append((s.path, s.line, name, category, lib, canonical, owner,
                               'candidate' if row else 'hold', problem, evidence))
    return result, census


def _nominal(spec, vis, seen=()):
    """C distinctions that the function ABI classifier intentionally erases."""
    core = M.strip_quals(spec)
    quals = tuple(sorted(t for t in spec if t in M._QUAL))
    if len(core) == 1 and core[0] in vis and core[0] not in seen:
        inner, iq = _nominal(vis[core[0]].spec, vis, seen + (core[0],))
        return inner, tuple(sorted(set(quals + iq)))
    return core.count('long'), quals


def data_key(x, ti):
    # Keep array extents, qualifiers and function-pointer shapes: -G8 decisions
    # can depend on these even where C permits compatible declarations.
    vis = ti.visible(x.path)
    return (M.canon(x.spec, x.ptr, vis), _nominal(x.spec, vis),
            re.sub(r'\s+', '', x.suffix), _typedef_bounds(x.spec, vis),
            _typedef_callback(x.spec, vis))


def _typedef_bounds(spec, vis, seen=()):
    core = M.strip_quals(spec)
    if len(core) == 1 and core[0] in vis and core[0] not in seen:
        td = vis[core[0]]
        return re.sub(r'\s+', '', td.suffix) + _typedef_bounds(td.spec, vis, seen + (core[0],))
    return ''


def _typedef_callback(spec, vis, seen=()):
    core = M.strip_quals(spec)
    if len(core) == 1 and core[0] in vis and core[0] not in seen:
        td = vis[core[0]]
        if td.fnptr:
            return (td.spec, td.ptr, re.sub(r'\s+', '', td.suffix))
        return _typedef_callback(td.spec, vis, seen + (core[0],))
    return None


def augment_data(corpus, ti, data, enabled, definitions=None):
    import plan as P
    from handler_addresses import AddressIndex
    function_addresses = AddressIndex(corpus, definitions or {})
    grouped = defaultdict(list)
    for x in data:
        grouped[x.name].append(x)
    rows, entities = [], {}
    for name, xs in sorted(grouped.items()):
        ext = [x for x in xs if not x.is_def and x.storage == 'extern']
        if not ext:
            continue
        ds = [x for x in xs if x.is_def and x.storage != 'static' and x.path.endswith('.c')]
        keys = {data_key(x, ti) for x in ext}
        targets = [d for x in ext for d, evidence in function_addresses.targets(x.path, name)]
        reason = 'data_is_function_address' if targets else ''
        views = Counter(' '.join(x.spec) + ' ' + '*' * x.ptr + x.suffix for x in ext)
        if len(keys) != 1:
            reason = reason or 'data_views_differ'
        if len(ds) > 1:
            reason = reason or 'data_multiple_definitions'
        if len(ds) == 1 and any(data_key(x, ti) != data_key(ds[0], ti) for x in ext):
            reason = reason or 'data_definition_view_differs'
        source = ds[0] if ds else sorted(ext, key=lambda x: (x.path, x.line))[0]
        if '(' in source.suffix or '{' in source.spec or any('(' in t for t in source.spec):
            reason = reason or 'data_complex_declarator'
        if source.ndecl != 1:
            reason = reason or 'data_multi_declarator'
        proto = 'extern ' + ' '.join(source.spec) + ' ' + '*' * source.ptr + name + source.suffix
        fd = M.FuncDef(name, source.path, source.line, False, source.spec, source.ptr, [], proto,
                       M.container_of(source.path))
        fd.kind = 'data'
        th, tg, sub, prob = P.type_needs(fd, ti)
        reason = reason or ('data_' + prob if prob else '')
        # Tagged forward declarations are insufficient for array elements/by-value
        # data. Keep local layouts and unknown array-bound macros out of headers.
        for tag in tg:
            if not source.ptr:
                candidates = [h for h in ti.tag_defs.get(tag, []) if P.type_header_ok(h)]
                if len(candidates) == 1:
                    th = tuple(sorted(set(th) | set(candidates)))
                else:
                    reason = reason or 'data_incomplete_tag'
        bounds = set(cscan.IDENT.findall(source.suffix))
        if bounds:
            reason = reason or 'data_named_extent'
        owner = P.header_for(ds[0].path) if len(ds) == 1 else ''
        containers = sorted({M.container_of(x.path) for x in ext if x.path.endswith('.c')})
        containers = sorted(set(containers) | {x.path.split('/')[1] for x in ext
                            if re.fullmatch(r'include/[^/]+/data.h', x.path)})
        # A no-definition symbol is one global name with one exact view, declared
        # per image that imports it (the ABI is checked for every physical TU).
        owners = [owner] if owner else ['include/' + c + '/data.h' for c in containers]
        for h in owners:
            cont = M.container_of(ds[0].path) if len(ds) == 1 else h.split('/')[1]
            row = P.FnRow(name, fd, h, type_headers=th, tags=tg,
                          proto=P.substituted_proto(fd, sub))
            row.kind = 'data'
            row.data_defined = len(ds) == 1
            row.status = 'hold' if reason else 'header'
            row.reason = reason
            if enabled and not reason:
                entities[(name, cont)] = row
        rows.append((name, 'hold' if reason else 'candidate', reason, len(ext), len(keys),
                     ';'.join(owners), ';'.join(f'{x.path}:{x.line}' for x in ds),
                     ' | '.join(f'{v} x{n}' for v, n in views.most_common()), proto + ';'))
    return entities, rows


def legacy_data_census(plan):
    """Inventory declarations outside generated owners; do not rewrite headers."""
    census = {r[0]: r for r in plan.data_census}
    generated = defaultdict(set)
    for x in plan.data:
        if x.storage == 'extern' and not x.is_def and x.path in plan.generated:
            generated[x.name].add(x.path)
    rows = []
    for x in plan.data:
        if x.storage != 'extern' or x.is_def or not x.path.endswith('.h') or x.path in plan.generated:
            continue
        r = census.get(x.name)
        if r is None:
            continue
        proto = 'extern ' + ' '.join(x.spec) + ' ' + '*' * x.ptr + x.name + x.suffix + ';'
        rows.append((x.name, x.path, x.line, r[1], r[2], ';'.join(sorted(generated[x.name])),
                     r[5], proto, 'Fold the handwritten declaration only with before snapshots and '
                     'identity proof for every consumer; tree-wide data changes wait for data naming.'))
    return sorted(rows)
