"""Prototype table: function definitions, declaration sites, type canonicalisation and classification.

Pure and deterministic (no compiler): everything is keyed by function NAME plus the definition's
canonical prototype, never by line numbers or opaque ids, so the table rebuilds unchanged on a newer
HEAD where files were merged, moved or renamed.

Containers come from the src/ top directory (dungeon, town, main = frontend+main, slus = engine+slus,
ovmovie = ovmovie+movie).  An overlay site binds to a definition in its own container first, then to
the resident SLUS image; anything else is a cross-container site and is never unified.
"""
from __future__ import annotations

import os
import re
from collections import defaultdict
from dataclasses import dataclass, field
from pathlib import Path

try:
    from . import cscan
except ImportError:  # run as a script from tools/headers
    import cscan

CONTAINER_OF_TOP = {'dungeon': 'dungeon', 'town': 'town', 'frontend': 'main', 'main': 'main',
                    'engine': 'slus', 'slus': 'slus', 'ovmovie': 'ovmovie', 'movie': 'ovmovie'}
RESIDENT = 'slus'

# canonical spellings of builtin integer/float types
_BUILTIN = {
    ('void',): 'void', ('char',): 'char', ('signed', 'char'): 's8', ('unsigned', 'char'): 'u8',
    ('short',): 's16', ('short', 'int'): 's16', ('signed', 'short'): 's16', ('signed', 'short', 'int'): 's16',
    ('unsigned', 'short'): 'u16', ('unsigned', 'short', 'int'): 'u16',
    ('int',): 's32', ('signed',): 's32', ('signed', 'int'): 's32', ('long',): 's32', ('long', 'int'): 's32',
    ('signed', 'long'): 's32',
    ('unsigned',): 'u32', ('unsigned', 'int'): 'u32', ('unsigned', 'long'): 'u32', ('unsigned', 'long', 'int'): 'u32',
    ('long', 'long'): 's64', ('unsigned', 'long', 'long'): 'u64', ('float',): 'f32', ('double',): 'f64',
}
_QUAL = {'const', 'volatile', '__volatile__', '__const__'}
NARROW = {'char', 's8', 'u8', 's16', 'u16', 'f32', 'f64', 's64', 'u64'}

SAFE_CLASSES = ('identical', 'spelling', 'const_qual', 'abi_equal', 'void_ptr', 'pointer_view', 'int_pointer',
                'unprototyped', 'return_dropped')
HAZARD_CLASSES = ('unprototyped_hazard', 'param_width', 'return_width', 'return_kind', 'return_void_used')
NEVER_CLASSES = ('arity', 'varargs', 'def_varargs', 'complex', 'struct_by_value')


def container_of(rel: str) -> str:
    parts = rel.split('/')
    if parts[0] == 'src' and len(parts) > 1:
        return CONTAINER_OF_TOP.get(parts[1], parts[1])
    return 'include'


@dataclass
class TypedefInfo:
    name: str
    path: str
    spec: tuple
    ptr: int
    suffix: str
    fnptr: bool


@dataclass
class FuncDef:
    name: str
    path: str
    line: int
    static: bool
    ret_spec: tuple
    ret_ptr: int
    params: list          # token lists
    proto: str            # declaration text: 'ret name(params)'
    container: str
    knr: bool = False
    varargs: bool = False
    complex: bool = False


@dataclass
class Site:
    name: str
    path: str
    line: int
    start: int
    end: int
    storage: str          # 'extern' | '' | 'static'
    ret_spec: tuple
    ret_ptr: int
    params: list | None   # None = unprototyped '()'
    text: str
    ndecl: int            # declarators in the statement
    in_header: bool
    cond: int
    complex: bool = False


@dataclass
class DataDecl:
    name: str
    path: str
    line: int
    start: int
    end: int
    spec: tuple
    ptr: int
    suffix: str
    storage: str
    ndecl: int
    is_def: bool


class Corpus:
    """Scans src/**/*.c and include/**/*.h of a root."""

    def __init__(self, root, src_dirs=('src',), files=None):
        self.root = Path(root).resolve()
        if files is None:
            files = []
            for top in src_dirs:
                for d, dn, fn in os.walk(self.root / top):
                    dn.sort()
                    for f in sorted(fn):
                        if f.endswith('.c'):
                            files.append((Path(d) / f).relative_to(self.root).as_posix())
        self.c_files = sorted(files)
        self.h_files = sorted((Path(d) / f).relative_to(self.root).as_posix()
                              for d, _, fn in os.walk(self.root / 'include') for f in fn if f.endswith('.h'))
        self._scan = {}
        self._text = {}
        self._includes = {}
        self._closure = {}

    def text(self, rel):
        if rel not in self._text:
            self._text[rel] = (self.root / rel).read_bytes().decode('utf-8', 'surrogateescape')
        return self._text[rel]

    def scan(self, rel):
        s = self._scan.get(rel)
        if s is None:
            s = self._scan[rel] = cscan.scan(self.text(rel))
        return s

    # ----- includes -----------------------------------------------------------------------------
    def resolve_include(self, from_rel, target):
        here = (self.root / from_rel).parent / target
        if here.is_file():
            return os.path.normpath(here.relative_to(self.root).as_posix()) if here.resolve().is_relative_to(self.root) else None
        inc = self.root / 'include' / target
        if inc.is_file():
            return os.path.normpath(('include/' + target))
        return None

    def includes(self, rel):
        if rel in self._includes:
            return self._includes[rel]
        out = []
        for d in self.scan(rel).directives:
            if d.kind == 'include' and d.arg.startswith('"'):
                tgt = d.arg.split('"')[1]
                r = self.resolve_include(rel, tgt)
                if r:
                    out.append(r)
        self._includes[rel] = out
        return out

    def closure(self, rel):
        if rel in self._closure:
            return self._closure[rel]
        seen, stack = [], [rel]
        while stack:
            f = stack.pop()
            if f in seen:
                continue
            seen.append(f)
            stack.extend(reversed(self.includes(f)))
        self._closure[rel] = seen
        return seen


# ----- typedef index ------------------------------------------------------------------------------
def file_typedefs(corpus, rel):
    out = {}
    for it in corpus.scan(rel).items:
        if it.kind != 'decl' or 'typedef' not in it.storage:
            continue
        for d in it.decls:
            if not d.name:
                continue
            fnptr = d.is_function or ('(' in d.text)
            out[d.name] = TypedefInfo(d.name, rel, tuple(it.spec), d.ptr, d.suffix, fnptr)
    return out


_TAGS = {}


def file_tags(corpus, rel):
    """struct/union/enum tags DEFINED (with a body) in a file."""
    if not hasattr(corpus, '_tags'):
        corpus._tags = {}
    if rel in corpus._tags:
        return corpus._tags[rel]
    tags = corpus._tags[rel] = set()
    toks = cscan.tokens(corpus.scan(rel).masked)
    for i in range(len(toks) - 2):
        if toks[i] in ('struct', 'union', 'enum') and cscan.IDENT.fullmatch(toks[i + 1]) and toks[i + 2] == '{':
            tags.add(toks[i] + ' ' + toks[i + 1])
    return tags


class TypeIndex:
    def __init__(self, corpus):
        self.corpus = corpus
        self.by_file = {}
        self._visible = {}
        self.global_defs = defaultdict(list)    # typedef name -> [header paths]
        self.tag_defs = defaultdict(list)       # 'struct X' -> [header paths]
        for h in corpus.h_files:
            tds = file_typedefs(corpus, h)
            self.by_file[h] = tds
            for n in tds:
                self.global_defs[n].append(h)
            for t in file_tags(corpus, h):
                self.tag_defs[t].append(h)

    def typedefs(self, rel):
        if rel not in self.by_file:
            self.by_file[rel] = file_typedefs(self.corpus, rel)
        return self.by_file[rel]

    def visible(self, rel):
        """typedef name -> TypedefInfo visible in a TU (its own + include closure; first wins)."""
        if rel in self._visible:
            return self._visible[rel]
        vis = {}
        for f in self.corpus.closure(rel):
            for n, ti in self.typedefs(f).items():
                vis.setdefault(n, ti)
        self._visible[rel] = vis
        return vis


def strip_quals(spec):
    return tuple(t for t in spec if t not in _QUAL and t != '__attribute__')


def canon(spec, ptr, vis, depth=0):
    """Canonical (base, ptr, kind) for a spec + pointer level under a typedef visibility map."""
    spec = tuple(spec)
    quals = tuple(t for t in spec if t in _QUAL)
    core = strip_quals(spec)
    if depth > 12:
        return ('?loop', ptr, '?')
    if core and core[0] in ('struct', 'union', 'enum'):
        if core[0] == 'enum':
            return ('s32', ptr, 'int') if ptr == 0 else ('enum', ptr, 'ptr')
        if len(core) >= 2 and cscan.IDENT.fullmatch(core[1]):
            return (core[0] + ' ' + core[1], ptr, 'ptr' if ptr else 'struct')
        return (core[0] + ' <anon>', ptr, 'ptr' if ptr else 'struct')
    b = _BUILTIN.get(tuple(sorted(core, key=lambda t: ('signed', 'unsigned', 'long', 'short', 'char', 'int',
                                                        'float', 'double', 'void').index(t)
                                          if t in ('signed', 'unsigned', 'long', 'short', 'char', 'int', 'float',
                                                   'double', 'void') else 99)))
    if b is None:
        b = _BUILTIN.get(core)
    if b is not None:
        if ptr:
            return (b, ptr, 'ptr')
        kind = 'void' if b == 'void' else ('float' if b in ('f32', 'f64') else 'int')
        return (b, 0, kind)
    if len(core) == 1:
        ti = vis.get(core[0])
        if ti is None:
            return (core[0], ptr, 'ptr' if ptr else 'unknown')
        if ti.fnptr:
            return ('fnptr', ptr + 1, 'ptr')
        extra = 1 if ti.suffix.startswith('[') else 0
        if extra and ptr == 0:
            return canon(ti.spec, ti.ptr + extra, vis, depth + 1)[:2] + ('array',)
        return canon(ti.spec, ti.ptr + ptr + extra, vis, depth + 1)
    return (' '.join(core), ptr, 'unknown')


def abi(c):
    base, ptr, kind = c
    if ptr:
        return 'p'
    if kind == 'int':
        return base if base in NARROW else 'w'
    if kind == 'float':
        return base
    if kind == 'void':
        return 'v'
    if kind == 'struct':
        return 'S:' + base
    if kind == 'array':
        return 'p'
    return '?' + base


def param_parts(ptoks):
    """One parameter's tokens -> (spec, ptr, name, complex, is_ellipsis)."""
    if ptoks == ['...']:
        return ((), 0, '', False, True)
    # A declaration's lone typedef token is an unnamed type, not a parameter
    # name. K&R definitions are identified separately by collect_files().
    if len(ptoks) == 1 and cscan.IDENT.fullmatch(ptoks[0]):
        return (tuple(ptoks), 0, '', False, False)
    storage, spec, dparts = cscan.split_specifiers(ptoks)
    if not dparts or not dparts[0]:
        return (tuple(spec), 0, '', False, False)
    d = cscan.parse_declarator(dparts[0])
    if d is None:
        # abstract declarator: only stars / array
        stars = dparts[0].count('*')
        arr = 1 if '[' in dparts[0] else 0
        if '(' in dparts[0]:
            return (('fnptr',), 1, '', True, False)
        return (tuple(spec), stars + arr, '', False, False)
    if d.is_function or '(' in dparts[0]:
        return (('fnptr',), 1, d.name, True, False)
    arr = 1 if d.suffix.startswith('[') else 0
    return (tuple(spec), d.ptr + arr, d.name, False, False)


def norm_params(params):
    """Parameter list without names, as text (for 'identical')."""
    if params is None:
        return None
    out = []
    for p in params:
        if p == ['void'] and len(params) == 1:
            return []
        spec, ptr, name, cx, ell = param_parts(p)
        if ell:
            out.append('...')
        elif cx:
            out.append(' '.join(t for t in p if t != name))
        else:
            out.append(' '.join(spec) + ' ' + '*' * ptr)
    return [x.strip() for x in out]


def proto_params(params):
    if params is None:
        return None
    if params == [['void']]:
        return []
    return params


# ----- definitions and sites -------------------------------------------------------------------
def collect(corpus, tindex):
    return collect_files(corpus, tindex, corpus.c_files + corpus.h_files)


def collect_files(corpus, tindex, files):
    defs = defaultdict(list)
    sites = []
    data = []
    for rel in files:
        sc = corpus.scan(rel)
        in_header = rel.endswith('.h')
        for it in sc.items:
            if it.kind == 'def':
                d = it.decls[0]
                params = proto_params(d.params)
                knr = bool(params) and all(len(p) == 1 and cscan.IDENT.fullmatch(p[0]) and p[0] not in
                                           ('void',) and p[0] not in tindex.visible(rel) for p in params) \
                    and not any(p[0] in ('int', 'char', 'short', 'long', 'float', 'double') for p in params)
                head = sc.masked[it.start:it.body[0]]
                defs[d.name].append(FuncDef(
                    d.name, rel, it.line, 'static' in it.storage, tuple(it.spec), d.ptr, params or [],
                    proto_text_from(head), container_of(rel), knr=knr,
                    varargs=any(p == ['...'] for p in (params or [])), complex=d.complex))
                continue
            if it.kind != 'decl' or 'typedef' in it.storage:
                continue
            fdecls = [d for d in it.decls if d.is_function]
            storage = 'extern' if 'extern' in it.storage else ('static' if 'static' in it.storage else '')
            for d in it.decls:
                if d.is_function:
                    sites.append(Site(d.name, rel, it.line, it.start, it.end, storage, tuple(it.spec), d.ptr,
                                      proto_params(d.params), it.text, len(it.decls), in_header, it.cond_depth,
                                      complex=d.complex))
                elif d.name and not d.is_function:
                    data.append(DataDecl(d.name, rel, it.line, it.start, it.end, tuple(it.spec), d.ptr, d.suffix,
                                         storage, len(it.decls), 'extern' not in it.storage))
            del fdecls
    return defs, sites, data


def proto_text_from(masked_head):
    """The definition's own spelling, whitespace-normalised (comments already masked)."""
    t = ' '.join(masked_head.split())
    t = re.sub(r'\(\s+', '(', t)
    t = re.sub(r'\s+\)', ')', t)
    t = re.sub(r'\s+,', ',', t)
    return t


# ----- binding -------------------------------------------------------------------------------
def bind(site_path, name, defs):
    """Choose the definition a site refers to.  Returns (FuncDef|None, reason)."""
    cands = [d for d in defs.get(name, []) if not d.static]
    statics = [d for d in defs.get(name, []) if d.static]
    if site_path.endswith('.h'):
        if not cands:
            return None, 'static_only' if statics else 'no_c_definition'
        return pick_multi(cands)
    if any(d.path == site_path for d in statics):
        return None, 'same_file_static'
    cont = container_of(site_path)
    same = [d for d in cands if d.container == cont]
    if same:
        return pick_multi(same)
    res = [d for d in cands if d.container == RESIDENT]
    if res:
        return pick_multi(res)
    if cands:
        return None, 'cross_container'
    if statics:
        return None, 'static_only'
    return None, 'no_c_definition'


def def_key(d, tindex):
    vis = tindex.visible(d.path)
    ret = canon(d.ret_spec, d.ret_ptr, vis)
    ps = tuple(canon(*param_parts(p)[:2], vis) for p in d.params)
    return (ret, ps, d.varargs)


_TINDEX = [None]


def pick_multi(cands):
    if len(cands) == 1:
        return cands[0], ''
    cands = sorted(cands, key=lambda d: d.path)
    ti = _TINDEX[0]
    if ti is not None:
        keys = {def_key(d, ti) for d in cands}
        if len(keys) > 1:
            return None, 'multi_definition_conflict'
    return cands[0], 'multi_definition'


# ----- classification ------------------------------------------------------------------------
def classify(site, d, tindex):
    """Return (class, detail) comparing a declaration site with its bound definition."""
    if site.complex or d.complex:
        return 'complex', ''
    if d.knr:
        return 'knr_definition', ''
    svis = tindex.visible(site.path)
    dvis = tindex.visible(d.path)
    sret = canon(site.ret_spec, site.ret_ptr, svis)
    dret = canon(d.ret_spec, d.ret_ptr, dvis)
    dps = [param_parts(p) for p in d.params]
    dcan = [canon(p[0], p[1], dvis) for p in dps if not p[4]]
    rclass = None
    if sret != dret:
        sa, da = abi(sret), abi(dret)
        if sa == da:
            rclass = 'pointer_view' if sa == 'p' else 'abi_equal'
        elif da == 'v':
            rclass = 'return_dropped'       # site claims a value; definition returns nothing
        elif sa == 'v':
            rclass = 'return_dropped'       # site discards; definition returns a value
        elif {sa, da} <= {'w', 'p'}:
            rclass = 'return_kind'
        else:
            rclass = 'return_width'
    if site.params is None:
        if d.varargs:
            return 'def_varargs', 'unprototyped site, varargs definition'
        hz = [abi(c) for c in dcan if abi(c) in NARROW or abi(c).startswith('S:')]
        if hz:
            return 'unprototyped_hazard', 'definition params ' + ','.join(hz)
        if rclass in ('return_width', 'return_kind'):
            return rclass, f'{abi(sret)}->{abi(dret)}'
        return 'unprototyped', rclass or ''
    sps = [param_parts(p) for p in site.params]
    if any(p[4] for p in sps):
        return 'varargs', ''
    if d.varargs:
        return 'def_varargs', ''
    if len(sps) != len(dps):
        return 'arity', f'{len(sps)} vs {len(dps)}'
    if any(p[3] for p in sps) or any(p[3] for p in dps):
        cx = True
    else:
        cx = False
    scan_ = [canon(p[0], p[1], svis) for p in sps]
    worst = []
    for sc_, dc_ in zip(scan_, dcan):
        if sc_ == dc_:
            continue
        sa, da = abi(sc_), abi(dc_)
        if da.startswith('S:') or sa.startswith('S:'):
            worst.append('struct_by_value')
        elif sa == da == 'p':
            worst.append('void_ptr' if 'void' in (sc_[0], dc_[0]) else 'pointer_view')
        elif sa == da:
            worst.append('abi_equal')
        elif {sa, da} <= {'w', 'p'}:
            worst.append('int_pointer')
        else:
            worst.append('param_width')
    if rclass:
        worst.append(rclass)
    if not worst:
        if norm_params(site.params) == norm_params(d.params) and tuple(site.ret_spec) == tuple(d.ret_spec) \
                and site.ret_ptr == d.ret_ptr:
            return 'identical', ''
        quals = (tuple(t for t in site.ret_spec if t in _QUAL) != tuple(t for t in d.ret_spec if t in _QUAL) or
                 any(tuple(t for t in a[0] if t in _QUAL) != tuple(t for t in b[0] if t in _QUAL)
                     for a, b in zip(sps, dps)))
        return ('const_qual' if quals else 'spelling'), 'fnptr' if cx else ''
    order = ['struct_by_value', 'param_width', 'return_width', 'return_kind', 'int_pointer', 'return_dropped',
             'void_ptr', 'pointer_view', 'abi_equal']
    worst.sort(key=order.index)
    return worst[0], ','.join(sorted(set(worst)))


def risk(cls):
    if cls in SAFE_CLASSES:
        return 'safe'
    if cls in HAZARD_CLASSES:
        return 'hazard'
    return 'never'
