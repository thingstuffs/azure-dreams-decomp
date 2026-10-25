"""Header plan: which prototype lives in which header, and what each .c includes instead of its externs.

Layout (decision 61(f) subsystem interfaces, mirroring src/):
    src/<a>/<b>/<x>.c        ->  include/<a>/<b>.h       ("dungeon/actor.h")
    src/<a>/<x>.c            ->  include/<a>.h           ("town.h")
One header per src directory that defines global functions.  A header holds only prototypes (and the
type includes / struct-tag forward declarations its prototypes need); it never includes another
interface header, so the include graph is acyclic by construction.

Function-level holds (prototype not published): no C definition, static only, conflicting multiple
definitions, cross-container binding, K&R/complex/varargs definition, a prototype type that only the
defining .c file declares, an unknown type, or a name that is also a macro.
TU-level holds (the TU keeps its local declarations for that header and does not include it): a
'never' class site (arity, varargs, struct by value, complex), a conditional or multi-declarator site,
an annotated declaration, a name clash with the TU's own statics/typedefs/macros, a typedef clash
between the header's type closure and the TU's, or an existing-header declaration of incompatible arity.
Hazard-class sites (promotion/return width) are attempted and decided by object bytes (prove.py).
"""
from __future__ import annotations

import re
from collections import defaultdict
from dataclasses import dataclass, field

try:
    from . import cscan, model as M
except ImportError:
    import cscan
    import model as M

TRIVIAL_TRAILING = re.compile(r'^\s*/\*\s*extern\s*\*/\s*$')
TYPE_ALWAYS = {'include/common.h'}
# Interface headers may include only shared-concept type headers (decision 61(f)); these are pure
# (typedefs, struct definitions, extern declarations, macros -- no code, data or asm).
TYPE_HEADER_DIRS = ('include/shared/', 'include/records/')
TYPE_HEADER_FILES = {'include/common.h', 'include/m2c_compat.h', 'include/game.h', 'include/globals.h'}


def type_header_ok(path):
    return path in TYPE_HEADER_FILES or path.startswith(TYPE_HEADER_DIRS)


def header_for(def_path: str) -> str:
    parts = def_path.split('/')[1:-1]          # strip 'src' and file name
    return 'include/' + '/'.join(parts) + '.h'


def guard_for(header: str) -> str:
    return re.sub(r'[^A-Za-z0-9]', '_', header[len('include/'):]).upper()


def include_token(header: str) -> str:
    return header[len('include/'):]


@dataclass
class FnRow:
    name: str
    definition: object        # FuncDef or None
    header: str = ''
    status: str = 'header'    # header | hold
    reason: str = ''
    type_headers: tuple = ()
    tags: tuple = ()
    subst: dict = field(default_factory=dict)
    proto: str = ''


@dataclass
class SiteRow:
    site: object
    fn: str
    definition: object
    cls: str
    detail: str
    risk: str
    action: str = ''          # remove | keep
    reason: str = ''


@dataclass
class TuPlan:
    path: str
    add: list = field(default_factory=list)          # headers to include
    remove: list = field(default_factory=list)       # SiteRow to delete
    holds: dict = field(default_factory=dict)        # header -> reason
    implicit: list = field(default_factory=list)     # (fn, header) implicit callers that gain a prototype
    stale: list = field(default_factory=list)        # generated headers included but no longer needed


@dataclass
class Plan:
    functions: dict
    headers: dict             # header -> list of FnRow (published)
    header_types: dict        # header -> (type headers, tags)
    sites: list               # SiteRow (all, tree-wide)
    tus: dict                 # path -> TuPlan (scope only)
    data: list
    corpus: object
    tindex: object


KEYWORDS = set('''if while for switch return sizeof do else case goto break continue default typedef struct union
enum static extern register auto volatile const signed unsigned void char short int long float double
__attribute__ __asm__ asm __volatile__ inline __inline__'''.split())


def _macros(corpus, rel):
    names = set()
    for f in corpus.closure(rel):
        for d in corpus.scan(f).directives:
            if d.kind == 'define':
                m = re.match(r'([A-Za-z_]\w*)', d.arg)
                if m:
                    names.add(m.group(1))
    return names


def _file_level_names(corpus, rel):
    """Names a TU itself declares at file scope other than extern function sites: statics, data,
    typedefs, enum constants (approximate)."""
    sc = corpus.scan(rel)
    names = set()
    for it in sc.items:
        if it.kind == 'def':
            if 'static' in it.storage:
                names.add(it.decls[0].name)
            continue
        if it.kind != 'decl':
            continue
        for d in it.decls:
            if not d.is_function and d.name:
                names.add(d.name)
            elif d.is_function and 'static' in it.storage:
                names.add(d.name)
    return names


def _called(corpus, rel):
    sc = corpus.scan(rel)
    out = set()
    for it in sc.items:
        if it.kind != 'def':
            continue
        body = sc.masked[it.body[0]:it.body[1]]
        for m in re.finditer(r'\b([A-Za-z_]\w*)\s*\(', body):
            if m.group(1) not in KEYWORDS:
                out.add(m.group(1))
        # address-taken function names (no call) also bind to a declaration
    return out


def type_needs(fd, tindex):
    """(type headers, struct tags, substitutions, problem) for a definition's prototype outside its TU.

    A typedef the defining .c declares itself is replaced, where that is a compatible spelling, by
      * the same-named header typedef when it has the same canonical type (duplicate local copy),
      * 'struct Tag' (+ a forward declaration) when it names a tagged struct/union used through a pointer,
      * the builtin spelling when it is a scalar alias (typedef s16 Angle;).
    Anything else (anonymous struct, by-value local struct, unknown type) is a function-level hold."""
    vis = tindex.visible(fd.path)
    headers, tags, subst = set(), set(), {}
    parts = [(fd.ret_spec, fd.ret_ptr, False, [])] + \
        [(pp[0], pp[1], pp[3], p) for p in fd.params for pp in [M.param_parts(p)]]
    for spec, ptr, cx, raw in parts:
        toks = list(spec) if not cx else list(raw)
        i = 0
        while i < len(toks):
            t = toks[i]
            if t in ('struct', 'union', 'enum') and i + 1 < len(toks) and cscan.IDENT.fullmatch(toks[i + 1]):
                if t == 'enum':
                    return headers, tags, subst, 'enum_tag'
                tags.add(t + ' ' + toks[i + 1])
                i += 2
                continue
            if cscan.IDENT.fullmatch(t) and t not in cscan.BASE_TYPES and t not in cscan.QUALIFIERS \
                    and t not in cscan.STORAGE and t != '__attribute__':
                ti = vis.get(t)
                if ti is None:
                    if cx:          # parameter names inside function-pointer parameters
                        i += 1
                        continue
                    return headers, tags, subst, 'unknown_type:' + t
                if type_header_ok(ti.path):
                    if ti.path not in TYPE_ALWAYS:
                        headers.add(ti.path)
                    i += 1
                    continue
                # typedef local to the .c, or in a private (collector/module) header
                local_c = M.canon((t,), 0, vis)
                hdrs = [h for h in tindex.global_defs.get(t, [])
                        if M.canon(tindex.typedefs(h)[t].spec, tindex.typedefs(h)[t].ptr, tindex.visible(h))
                        == M.canon(ti.spec, ti.ptr, vis)]
                if t in ('s8', 'u8', 's16', 'u16', 's32', 'u32') and local_c[2] == 'int':
                    i += 1
                    continue
                hdrs = [h for h in hdrs if type_header_ok(h)]
                if len(hdrs) == 1 and not ti.fnptr:
                    if hdrs[0] not in TYPE_ALWAYS:
                        headers.add(hdrs[0])
                    i += 1
                    continue
                core = M.strip_quals(ti.spec)
                if not ti.fnptr and ti.ptr == 0 and not ti.suffix and len(core) >= 2 and \
                        core[0] in ('struct', 'union') and cscan.IDENT.fullmatch(core[1]) and \
                        (len(core) == 2 or core[2] == '{') and (ptr or cx):
                    subst[t] = core[0] + ' ' + core[1]
                    tags.add(subst[t])
                    i += 1
                    continue
                if not ti.fnptr and ti.ptr == 0 and not ti.suffix and local_c[2] in ('int', 'float') \
                        and local_c[1] == 0:
                    subst[t] = local_c[0]
                    i += 1
                    continue
                kind = 'local_type_anonymous' if core and core[0] in ('struct', 'union') and \
                    (len(core) < 2 or core[1] == '{') else 'local_type'
                if ti.path.startswith('include/'):
                    kind = 'private_header_type'
                return headers, tags, subst, f'{kind}:{t}@{ti.path}'
            i += 1
    return tuple(sorted(headers)), tuple(sorted(tags)), subst, ''


def substituted_proto(fd, subst):
    text = fd.proto
    if not subst:
        return text
    # never touch the function name itself
    head, sep, rest = text.partition(fd.name + '(')
    def rep(part):
        return re.sub(r'\b(' + '|'.join(map(re.escape, sorted(subst))) + r')\b', lambda m: subst[m.group(1)], part)
    return rep(head) + sep + rep(rest)


def build(root, scope=(), corpus=None, scope_files=None, include_data=False):
    corpus = corpus or M.Corpus(root)
    gen = generated_headers(corpus)
    corpus.h_files = [h for h in corpus.h_files if h not in gen]
    tindex = M.TypeIndex(corpus)
    M._TINDEX[0] = tindex
    defs, sites, data = M.collect(corpus, tindex)
    if gen:  # their declarations are only used to keep owners on a rerun
        corpus.h_files_generated = sorted(gen)
        _, gsites, gdata = M.collect_files(corpus, tindex, sorted(gen))
        sites = sites + gsites
        data = data + gdata

    # ---- function-level status --------------------------------------------------------------
    functions = {}
    macro_names = set()
    for h in corpus.h_files:
        for d in corpus.scan(h).directives:
            if d.kind == 'define':
                m = re.match(r'([A-Za-z_]\w*)', d.arg)
                if m:
                    macro_names.add(m.group(1))
    for name, dl in sorted(defs.items()):
        glob = [d for d in dl if not d.static]
        if not glob:
            continue
        # one row per (name, container group): bind from a site in the definition's own container
        by_cont = defaultdict(list)
        for d in glob:
            by_cont[d.container].append(d)
        for cont, ds in sorted(by_cont.items()):
            d, why = M.pick_multi(ds)
            key = name if len(by_cont) == 1 else f'{name}@{cont}'
            row = FnRow(name, d)
            if d is None:
                row.status, row.reason = 'hold', why
            else:
                row.header = header_for(d.path)
                if why == 'multi_definition':
                    row.reason = 'multi_definition'
                if d.knr:
                    row.status, row.reason = 'hold', 'knr_definition'
                elif d.complex:
                    row.status, row.reason = 'hold', 'complex_definition'
                elif d.varargs:
                    row.status, row.reason = 'hold', 'varargs_definition'
                elif name in macro_names:
                    row.status, row.reason = 'hold', 'name_is_macro'
                else:
                    th, tg, sub, prob = type_needs(d, tindex)
                    if prob:
                        row.status, row.reason = 'hold', prob
                    row.type_headers, row.tags, row.subst = th, tg, sub
                    row.proto = substituted_proto(d, sub)
                if len(by_cont) > 1 and row.status == 'header' and M.RESIDENT in by_cont:
                    # an overlay definition shadowing a resident one: an overlay TU may see both headers,
                    # so publish only when the prototypes agree (two overlays never share a TU)
                    keys = {M.def_key(x, tindex) for x in glob if x.container in (cont, M.RESIDENT)}
                    if len(keys) > 1:
                        row.status, row.reason = 'hold', 'multi_container_conflict'
            functions[key] = row

    import extra
    extra_functions, sdk_census = extra.augment_functions(corpus, tindex, defs, sites, functions)
    extra_rows = {}
    for n, fr in extra_functions.items():
        defs[n].append(fr.definition)
        extra_rows[(fr.definition.kind, n, fr.definition.container)] = fr
    data_entities, data_census = extra.augment_data(corpus, tindex, data, include_data, defs)
    for (n, cont), fr in data_entities.items():
        from dataclasses import replace
        fr.definition = replace(fr.definition, container=cont)
        fr.definition.kind = 'data'
        extra_rows[('data', n, cont)] = fr

    def fn_for_def(d):
        if d is None:
            return None
        kind = getattr(d, 'kind', '')
        if kind:
            return extra_rows.get((kind, d.name, d.container))
        key = d.name if d.name in functions else f'{d.name}@{d.container}'
        return functions.get(key)

    headers = defaultdict(list)
    for row in list(functions.values()) + list(extra_rows.values()):
        if row.status == 'header':
            headers[row.header].append(row)
    # --data controls NEW data moves. A functions-only rerun must retain data
    # already published by a prior --data pass, including its type scaffolding.
    # These rows never enter data_entities or the C site table below.
    preserved_data_headers = set()
    if not include_data:
        function_data = {r[0] for r in data_census if r[2] == 'data_is_function_address'}
        for x in data:
            if x.path not in gen or x.is_def or x.storage != 'extern' or x.name in function_data:
                continue
            text = corpus.text(x.path)
            th = tuple(h for h in corpus.includes(x.path)
                       if type_header_ok(h) and h not in TYPE_ALWAYS)
            tags = tuple(re.findall(r'^((?:struct|union)\s+\w+);\s*$', text, re.M))
            proto = 'extern ' + ' '.join(x.spec) + ' ' + '*' * x.ptr + x.name + x.suffix
            fd = M.FuncDef(x.name, x.path, x.line, False, x.spec, x.ptr, [], proto,
                           M.container_of(x.path))
            fd.kind = 'data'
            row = FnRow(x.name, fd, x.path, type_headers=th, tags=tags, proto=proto)
            row.kind = 'data'
            headers[x.path].append(row)
            preserved_data_headers.add(x.path)
    header_types = {}
    for h, rows in headers.items():
        rows.sort(key=lambda r: (r.definition.path, r.definition.line, r.name))
        th = sorted({x for r in rows for x in r.type_headers})
        tg = sorted({x for r in rows for x in r.tags})
        header_types[h] = (th, tg)

    # ---- site table ----------------------------------------------------------------------------
    rows = []
    for s in sites:
        if s.storage == 'static':
            continue
        d, why = M.bind(s.path, s.name, defs)
        if d is None:
            rows.append(SiteRow(s, s.name, None, why, '', 'never'))
            continue
        cls, det = M.classify(s, d, tindex)
        risk = M.risk(cls)
        if getattr(d, 'kind', '') == 'sdk' and cls in ('varargs', 'def_varargs'):
            risk = 'hazard'
        rows.append(SiteRow(s, s.name, d, cls, det, risk))

    data_reason = {r[0]: r[2] for r in data_census}
    for x in data if include_data else []:
        if x.is_def or x.storage != 'extern':
            continue
        cont = M.container_of(x.path)
        fr = data_entities.get((x.name, cont)) or data_entities.get((x.name, M.RESIDENT))
        if fr is None:
            # C-owned data can be imported by another image.
            matches = [r for (n, c), r in data_entities.items() if n == x.name and r.data_defined]
            fr = matches[0] if len(matches) == 1 else None
        it = next(i for i in corpus.scan(x.path).items if i.start == x.start)
        s = M.Site(x.name, x.path, x.line, x.start, x.end, x.storage, x.spec, x.ptr,
                   None, it.text, x.ndecl, x.path.endswith('.h'), it.cond_depth)
        s.kind = 'data'
        if fr is None:
            rows.append(SiteRow(s, x.name, None, 'data_hold', data_reason.get(x.name) or
                                'data_owner_unresolved', 'never'))
        else:
            rows.append(SiteRow(s, x.name, fr.definition, 'data_exact', '', 'safe'))

    plan = Plan(functions, dict(headers), header_types, rows, {}, data, corpus, tindex)
    plan.fn_for_def = fn_for_def
    plan.defs = defs
    plan.sites_by_path = defaultdict(list)
    for r in rows:
        plan.sites_by_path[r.site.path].append(r)
    plan.generated = gen
    plan.extra_rows = extra_rows
    plan.sdk_census = sdk_census
    plan.data_census = data_census
    plan.include_data = include_data
    plan.preserved_data_headers = preserved_data_headers
    plan.generated_names = {h: {r.site.name for r in plan.sites_by_path.get(h, [])} |
                           {x.name for x in data if x.path == h} for h in gen}
    if scope or scope_files:
        files = scope_files or [f for f in corpus.c_files if any(f == p or f.startswith(p.rstrip('/') + '/')
                                                               for p in scope)]
        for f in sorted(files):
            plan.tus[f] = plan_tu(plan, f)
    return plan


def _header_type_closure(plan, h):
    th, _ = plan.header_types[h]
    files = []
    for t in th:
        for f in plan.corpus.closure(t):
            if f not in files:
                files.append(f)
    return files


GENERATED_MARK = 'maintained by tools/headers'


def generated_headers(corpus):
    out = set()
    for h in corpus.h_files:
        if GENERATED_MARK in corpus.text(h)[:400]:
            out.add(h)
    return out


def _mentions(corpus, rel):
    """Identifiers used outside declarations (bodies and initialisers) -- calls and address-taking."""
    sc = corpus.scan(rel)
    out = set()
    for it in sc.items:
        if it.kind == 'def':
            seg = sc.masked[it.body[0]:it.body[1]]
        elif it.kind == 'decl' and '=' in sc.masked[it.start:it.end]:
            seg = sc.masked[it.start:it.end].split('=', 1)[1]
        else:
            continue
        out.update(m.group(0) for m in cscan.IDENT.finditer(seg))
    return out


def plan_tu(plan, rel):
    corpus, tindex = plan.corpus, plan.tindex
    tp = TuPlan(rel)
    sc = corpus.scan(rel)
    own = plan.sites_by_path.get(rel, [])
    by_header = defaultdict(list)
    for r in own:
        if r.definition is None:
            r.action, r.reason = 'keep', (r.detail if r.cls == 'data_hold' else r.cls)
            continue
        fr = plan.fn_for_def(r.definition)
        if fr is None or fr.status != 'header':
            r.action, r.reason = 'keep', 'function_held:' + (fr.reason if fr else 'unbound')
            continue
        by_header[fr.header].append(r)
    # headers the TU defines functions for
    defined_here = set()
    for it in sc.items:
        if it.kind == 'def' and 'static' not in it.storage:
            for key in (it.decls[0].name, f'{it.decls[0].name}@{M.container_of(rel)}'):
                fr = plan.functions.get(key)
                if fr and fr.status == 'header' and fr.definition.path == rel:
                    defined_here.add(fr.header)
    for (kind, n, cont), fr in plan.extra_rows.items():
        if kind == 'data' and fr.data_defined and fr.definition.path == rel:
            defined_here.add(fr.header)
    # rerun on a newer HEAD: prototypes this TU already gets from generated headers must keep an owner
    gen_included = [h for h in corpus.includes(rel) if h in plan.generated]
    from_generated = set(gen_included) & plan.preserved_data_headers
    if gen_included:
        declared = set()
        for h in gen_included:
            declared |= plan.generated_names.get(h, set())
        cont = M.container_of(rel)
        for n in sorted(declared & _mentions(corpus, rel)):
            fr = plan.functions.get(n) or plan.functions.get(f'{n}@{cont}')
            if fr and fr.status == 'header':
                from_generated.add(fr.header)
            for (kind, name, image), fr in plan.extra_rows.items():
                if name == n and image in (cont, M.RESIDENT):
                    from_generated.add(fr.header)
        # Removing an unused declaration still leaves an intentional include.
        # Preserve it on reruns while the header has an owner; moved, used names
        # continue to be repointed by the binding above.
        mentions = _mentions(corpus, rel)
        for h in gen_included:
            if h in plan.headers and not (plan.generated_names.get(h, set()) & mentions):
                from_generated.add(h)
    wanted = set(by_header) | defined_here | from_generated
    tp.stale = sorted(set(gen_included) - wanted)
    if not wanted:
        return tp
    own_names = _file_level_names(corpus, rel)
    # The local externs being moved are not competing definitions.
    own_names -= {r.site.name for r in own if getattr(r.site, 'kind', '') == 'data'}
    own_names -= {fr.name for (kind, n, cont), fr in plan.extra_rows.items()
                  if kind == 'data' and fr.data_defined and fr.definition.path == rel}
    macros = _macros(corpus, rel)
    closure = [f for f in corpus.closure(rel) if f not in plan.generated]
    vis_files = {}
    for f in closure:
        for n, ti in tindex.typedefs(f).items():
            vis_files.setdefault(n, f)
    called = _called(corpus, rel)
    declared_here = {r.site.name for f in closure for r in plan.sites_by_path.get(f, [])} | \
        {it.decls[0].name for it in sc.items if it.kind == 'def'}
    closure_header_sites = defaultdict(list)
    for f in closure:
        if f.endswith('.h'):
            for r in plan.sites_by_path.get(f, []):
                closure_header_sites[r.site.name].append(r)

    for h in sorted(wanted):
        reason = ''
        fnames = {fr.name for fr in plan.headers.get(h, [])}
        for r in by_header.get(h, []):
            s = r.site
            if r.risk == 'never':
                reason = f'site_{r.cls}:{s.name}'
            elif s.cond:
                reason = f'conditional_site:{s.name}'
            elif s.ndecl != 1:
                reason = f'multi_declarator:{s.name}'
            elif _annotated(sc, s):
                reason = f'annotated_declaration:{s.name}'
            if reason:
                break
        if not reason and 'include/common.h' not in closure:
            # common.h carries include_asm.h's top-level asm; a TU without it would change its stream
            reason = 'tu_without_common_h'
        if not reason:
            clash = sorted(fnames & (own_names | macros))
            if clash:
                reason = 'name_clash:' + clash[0]
        if not reason:
            for f in _header_type_closure(plan, h):
                for n in tindex.typedefs(f):
                    other = vis_files.get(n)
                    if other is not None and other != f:
                        reason = f'typedef_clash:{n}'
                        break
                if reason:
                    break
        if not reason:
            mine = set()
            for f in closure:
                mine |= {(t, f) for t in M.file_tags(corpus, f)}
            mine_tags = {}
            for t, f in sorted(mine):
                mine_tags.setdefault(t, f)
            for f in _header_type_closure(plan, h):
                for t in M.file_tags(corpus, f):
                    other = mine_tags.get(t)
                    if other is not None and other != f:
                        reason = f'tag_clash:{t}'
                        break
                if reason:
                    break
        if not reason:
            pub = {fr.name: fr for fr in plan.headers.get(h, [])}
            for n in sorted(fnames):
                for r in closure_header_sites.get(n, []):
                    if getattr(r.site, 'kind', '') == 'data' or getattr(pub[n], 'kind', '') == 'data':
                        # Data census already holds every differing view globally.
                        continue
                    cls, _ = M.classify(r.site, pub[n].definition, tindex)
                    # two declarations in one TU must be C-compatible types, not just ABI-equal
                    if cls not in ('identical', 'spelling', 'unprototyped'):
                        reason = f'existing_header_{cls}:{n}@{r.site.path}'
                        break
                if reason:
                    break
        if reason:
            tp.holds[h] = reason
            for r in by_header.get(h, []):
                r.action, r.reason = 'keep', 'tu_hold:' + reason
            continue
        tp.add.append(h)
        for r in by_header.get(h, []):
            r.action = 'remove'
            tp.remove.append(r)
        for n in sorted((fnames & called) - declared_here):
            tp.implicit.append((n, h))
    return tp


def _annotated(sc, s):
    """True when the declaration carries a comment other than a bare '/* extern */' marker."""
    text = sc.text
    line_start = text.rfind('\n', 0, s.start) + 1
    line_end = text.find('\n', s.end)
    line_end = len(text) if line_end < 0 else line_end
    before = text[line_start:s.start]
    after = text[s.end:line_end]
    inner = text[s.start:s.end]
    if before.strip():
        return True
    if '/*' in inner or '//' in inner:
        return True
    if after.strip() and not TRIVIAL_TRAILING.match(after):
        return True
    return False
