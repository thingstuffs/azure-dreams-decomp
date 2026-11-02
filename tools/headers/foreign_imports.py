#!/usr/bin/env python3
"""Foreign-program import headers: code linked against ANOTHER build declares each import once.

    foreign_imports.py --classes CLASSES.tsv --out DIR [--decide] [--apply] [--scope src/...]
                       [--identities IDS.tsv] [--workers 4] [--dry-run]

Owner ruling 2026-11-02: code linked against another executable / engine build (target_census.py classes
FOREIGN_SLUS, FOREIGN_IMAGE and NOWHERE: the call targets are mid-function, data or nothing in the retail
images, so no C body can ever own those names) gets ONE import header per foreign program, declaring each
import once with its address spelling; the local declarations are replaced by an include of that header.

Programs.  A header names its program with a marker line in its leading comment:

    * foreign-program: town 0x78B800-0x796000; town 0x7F4000-0x804000

(container and file-offset ranges).  A .c file belongs to a program when every linked unit of its
recipes (build/codemap.db image_unit: container + container offset) lies inside the program's ranges.

--decide  For every program, the names its files declare locally and the header does not declare yet:
          the candidate prototypes are the sites' own spellings rendered with header-visible types
          (common.h scalars; struct / union pointers become `void *`), widest-first variants for
          disagreeing returns (the signature solver's width rule: one ABI-wide prototype when the sites
          need different return widths), prototyped before K&R.  Every candidate is probed at every
          site at its production recipe (tools/typing/sig_probe.py: header declarations hidden, the
          TU's own declarations removed, the candidate inserted; compared with the control object).
          The first candidate neutral at every site is appended to the header's generated block; a name
          with no neutral candidate gets the candidate neutral at most sites (sites that refuse it keep
          their local declaration: a prototype floor, recorded in DIR/floors.jsonl in the
          ledger/prototype_floors.jsonl form); a name no candidate fits stays local everywhere.
--apply   For every .c file under --scope with local declarations of names its program header declares:
          the declarations whose spelling is not a recorded floor of that file are removed and the header
          is included after the last #include that precedes the first removed declaration.  The final
          text is compiled at every production recipe of the file and must equal the production object;
          a file that does not is retried with the names that are neutral one at a time, else held whole.
          Idempotent: a file that already includes its header and declares nothing it declares is untouched.

Outputs: DIR/sites.tsv (every local declaration site with its program), DIR/decisions.json, DIR/floors.jsonl,
DIR/apply.tsv (file, header, removed, held, reason), DIR/foreign_imports.patch.  Prove the result with
tools/lanes/prove_batch.sh (byte-exact over the build graph) before committing.
"""
from __future__ import annotations

import argparse
import collections
import csv
import difflib
import json
import re
import sqlite3
import sys
from pathlib import Path

HERE = Path(__file__).resolve()
ROOT = HERE.parents[2]
for p in (str(HERE.parent), str(HERE.parents[1] / 'typing'), str(HERE.parents[1] / 'codemap')):
    if p not in sys.path:
        sys.path.insert(0, p)

import cscan  # noqa: E402

FOREIGN = ('FOREIGN_SLUS', 'FOREIGN_IMAGE', 'NOWHERE')
MARK = re.compile(r'foreign-program:\s*([^\n]+)')
RANGE = re.compile(r'(main|town|dungeon|ovmovie|movie)\s+(0x[0-9A-Fa-f]+)\s*-\s*(0x[0-9A-Fa-f]+)')
BEGIN = '/* --- imports (tools/headers/foreign_imports.py): one declaration per address --- */'
END = '/* --- end of imports --- */'
SCALAR = {'int': 's32', 'unsigned int': 'u32', 'short': 's16', 'unsigned short': 'u16', 'signed char': 's8',
          'unsigned char': 'u8', 'char': 'char', 'void': 'void', 'long': 'long', 'unsigned long': 'unsigned long',
          'long long': 'long long', 'unsigned long long': 'unsigned long long', 'float': 'float',
          'double': 'double'}
WIDTH = {'void': 0, 's8': 1, 'u8': 1, 'char': 1, 's16': 2, 'u16': 2, 's32': 4, 'u32': 4, 'long': 4,
         'unsigned long': 4}


# ------------------------------------------------------------------------------------------- programs

def programs(root):
    """[{header, ranges: [(container, lo, hi)]}] from the foreign-program markers of include/**/*.h."""
    out = []
    for h in sorted((root / 'include').rglob('*.h')):
        text = h.read_text(errors='surrogateescape')
        m = MARK.search(text)
        if not m:
            continue
        ranges = [(c, int(a, 16), int(b, 16)) for c, a, b in RANGE.findall(m[1])]
        if ranges:
            out.append(dict(header=str(h.relative_to(root)), include=str(h.relative_to(root / 'include')),
                            ranges=ranges))
    return out


def file_units(db):
    """{source path: [(recipe, container, off)]} for the linked units of every C recipe."""
    out = collections.defaultdict(list)
    for rid, src, phys, img, off in db.execute(
            'SELECT r.id, r.source, r.physical, u.image, u.off FROM recipe r JOIN image_unit u ON u.recipe = r.id'):
        cont = img.split('/')[0]
        out[src].append((rid, cont, off, phys))
    return out


def program_of(units, progs):
    """The program every unit of a file lies in (None when none / several / no units)."""
    hit = set()
    for _rid, cont, off, _phys in units:
        if off is None:
            return None
        owner = [i for i, p in enumerate(progs) if any(c == cont and lo <= off < hi for c, lo, hi in p['ranges'])]
        if len(owner) != 1:
            return None
        hit.add(owner[0])
    return hit.pop() if len(hit) == 1 else None


# ------------------------------------------------------------------------------------------- rendering

def split_fn(canon):
    """'ret(params)' -> (ret, [params], variadic) for a canonical function type, None when complex."""
    i = canon.find('(')
    if i < 0 or not canon.endswith(')') or '(' in canon[:i]:
        return None
    ret, inner = canon[:i].strip(), canon[i + 1:-1]
    parts, depth, cur = [], 0, ''
    for ch in inner:
        if ch == ',' and depth == 0:
            parts.append(cur.strip())
            cur = ''
            continue
        depth += ch == '('
        depth -= ch == ')'
        cur += ch
    if cur.strip():
        parts.append(cur.strip())
    variadic = bool(parts) and parts[-1] == '...'
    if variadic:
        parts = parts[:-1]
    return ret, parts, variadic


def render_type(t):
    """Header-visible spelling of one canonical type (None when it needs a type the header cannot see)."""
    t = re.sub(r'\bconst\b|\bvolatile\b', '', t).strip()
    t = re.sub(r'\s+', ' ', t)
    if '(*)' in t:                                   # function pointer: render its own signature
        m = re.fullmatch(r'(.+?)\(\*\)\((.*)\)', t)
        if not m:
            return None
        ret = render_type(m[1])
        sub = split_fn('x(' + m[2] + ')')
        if ret is None or sub is None:
            return None
        ps = [render_type(p) for p in sub[1]]
        if any(p is None for p in ps):
            return None
        return '%s (*)(%s)' % (ret, ', '.join(ps + (['...'] if sub[2] else [])) or 'void')
    stars = len(t) - len(t.rstrip('*'))
    base = t.rstrip('*').strip()
    if base in SCALAR:
        return SCALAR[base] + (' ' + '*' * stars if stars else '')
    if stars and re.fullmatch(r'(struct|union|enum) \w+', base):
        return 'void *'
    if not stars and base.startswith('enum '):
        return 's32'
    return None


def render(name, canon, has_proto):
    """Prototype text (no ';') for a declaration's canonical type, None when not header-visible."""
    sp = split_fn(canon)
    if sp is None:
        return None
    ret, params, variadic = sp
    r = render_type(ret)
    if r is None:
        return None
    if not has_proto:
        return '%s%s%s()' % (r, '' if r.endswith('*') else ' ', name)
    ps = []
    for p in params:
        q = render_type(p)
        if q is None:
            return None
        ps.append(q)
    if ps == ['void']:
        ps = []
    plist = ', '.join(ps + (['...'] if variadic else [])) or 'void'
    return '%s%s%s(%s)' % (r, '' if r.endswith('*') else ' ', name, plist)


ATTR = ' __attribute__((noreturn))'


def proto_parts(text, name):
    """(ret, params text, prototyped, variadic) of a rendered prototype."""
    body = text[:-len(ATTR)] if text.endswith(ATTR) else text
    i = body.index(name + '(')
    params = body[i + len(name) + 1:-1]
    return body[:i].strip(), params, not body.endswith(name + '()'), params.endswith('...')


def candidates(name, spellings):
    """Ordered candidate prototypes from the rendered site spellings (Counter text -> sites).

    Prototyped, fixed-arity spellings first (most sites first, narrow return first), then the width rule's
    ABI-wide return over each of their parameter lists.  An unprototyped `T f()` or variadic spelling is a
    candidate only when every site already spells it that way (it would hide an arity disagreement that the
    floors record instead)."""
    def loose(t):
        return not proto_parts(t, name)[2] or proto_parts(t, name)[3]
    fixed = [t for t in spellings if not loose(t)]
    out = sorted(fixed, key=lambda t: (-spellings[t], WIDTH.get(proto_parts(t, name)[0], 4), t))
    rets = {proto_parts(t, name)[0] for t in spellings}
    if len(rets) > 1 and fixed:
        # width rule: one ABI-wide return for sites that need different widths (value users first)
        wide = 'void *' if any(r.endswith('*') for r in rets) else 's32'
        for t in list(out):
            _r, params, _p, _v = proto_parts(t, name)
            w = '%s%s%s(%s)%s' % (wide, '' if wide.endswith('*') else ' ', name, params,
                                  ATTR if t.endswith(ATTR) else '')
            if w not in out:
                out.append(w)
    if not fixed:
        out += sorted(spellings, key=lambda t: (-spellings[t], t))
    return out


# ------------------------------------------------------------------------------------------- headers

def header_decls(text):
    """{name: prototype text without ';'} of the function declarations in a header."""
    out = {}
    sc = cscan.scan(text)
    for it in sc.items:
        if it.kind != 'decl' or 'typedef' in it.storage:
            continue
        for d in it.decls:
            if d.is_function:
                stmt = re.sub(r'\s+', ' ', cscan.mask(it.text)).strip().rstrip(';').strip()
                stmt = re.sub(r'^extern\s+', '', stmt)
                out[d.name] = stmt
    return out


def append_block(text, lines):
    """Header text with `lines` added to the generated block (created before the include guard's #endif)."""
    if not lines:
        return text
    add = ''.join(l + '\n' for l in lines)
    if END in text:
        i = text.index(END)
        return text[:i] + add + text[i:]
    j = text.rstrip().rfind('#endif')
    block = '\n' + BEGIN + '\n' + add + END + '\n\n'
    return text[:j].rstrip('\n') + '\n' + block + text[j:]


TYPE_WORDS = {'void', 'char', 'short', 'int', 'long', 'unsigned', 'signed', 'float', 'double', 'const', 'volatile',
              's8', 'u8', 's16', 'u16', 's32', 'u32', 'struct', 'union', 'enum'}
SPELL = {'int': 's32', 'unsigned int': 'u32', 'unsigned': 'u32', 'short': 's16', 'unsigned short': 'u16',
         'unsigned char': 'u8', 'signed char': 's8'}


def sig_key(stmt, name):
    """A declaration's type with parameter names, `extern` and spacing removed (None when not one function)."""
    t = re.sub(r'/\*.*?\*/', ' ', stmt, flags=re.S)
    t = re.sub(r'\bextern\b', ' ', t).strip().rstrip(';').strip()
    m = re.match(r'^(.*?)\b%s\s*\((.*?)\)\s*(__attribute__\s*\(\(.*\)\))?$' % re.escape(name), t, re.S)
    if not m:
        return None

    def norm(x):
        x = re.sub(r'\s+', ' ', x).strip()
        x = re.sub(r'\s*\*\s*', '*', x)
        return SPELL.get(x, x)
    params = []
    for p in [x for x in m[2].split(',') if x.strip()]:
        toks = re.findall(r'\w+|\S', p)
        if len(toks) > 1 and re.fullmatch(r'[A-Za-z_]\w*', toks[-1]) and toks[-1] not in TYPE_WORDS \
                and (toks[-2] == '*' or re.fullmatch(r'\w+', toks[-2])):
            p = p[:p.rfind(toks[-1])]
        params.append(norm(p))
    if params == ['void']:
        params = []
    attr = 'noreturn' if m[3] and 'noreturn' in m[3] else ''
    return '%s(%s)%s' % (norm(m[1]), ','.join(params), attr)


# ------------------------------------------------------------------------------------------- sites

def local_sites(text, names):
    """{name: [(start, end, ndecl)]} of the file-scope function declarations of `names` in a .c text."""
    out = collections.defaultdict(list)
    sc = cscan.scan(text)
    for it in sc.items:
        if it.kind != 'decl' or 'typedef' in it.storage or 'static' in it.storage:
            continue
        for d in it.decls:
            if d.is_function and d.name in names:
                out[d.name].append((it.start, it.end, len(it.decls), it.cond_depth))
    return out, sc


def line_span(text, s, e):
    ls = text.rfind('\n', 0, s) + 1
    le = text.find('\n', e)
    le = len(text) if le < 0 else le + 1
    if text[ls:s].strip() == '' and re.fullmatch(r'[ \t]*(/\*[^\n]*?\*/[ \t]*)*\n?', text[e:le]):
        return ls, le
    return s, e


COMMON_TYPEDEF = re.compile(r'^typedef[ \t]+(unsigned char|signed char|unsigned short|short|unsigned int|int)[ \t]+'
                            r'(u8|s8|u16|s16|u32|s32)[ \t]*;[ \t]*\n', re.M)
COMMON_TYPES = {'u8': 'unsigned char', 's8': 'signed char', 'u16': 'unsigned short', 's16': 'short',
                'u32': 'unsigned int', 's32': 'int'}


def edit_text(text, header_inc, spans, sc):
    """Text with the declaration spans removed and `#include "header_inc"` added (when not yet included).

    A file that spells its own base typedefs instead of including common.h (which the import header includes)
    loses the ones common.h defines identically (gcc 2.7 rejects a repeated typedef), as the signature
    solver's include_common_h repair does; the include goes before the first of them."""
    first = min(s for s, _e in spans)
    includes = [d for d in sc.directives if d.kind == 'include']
    have = any(header_inc in text[d.start:d.end] for d in includes)
    edits = [(s, e, '') for s, e in sorted({line_span(text, s, e) for s, e in spans})]
    if not have and not any('"common.h"' in text[d.start:d.end] for d in includes):
        tds = [m for m in COMMON_TYPEDEF.finditer(text) if COMMON_TYPES[m[2]] == m[1]]
        if tds:
            first = min(first, tds[0].start())
            edits += [(m.start(), m.end(), '') for m in tds]
    if not have:
        before = [d for d in includes if d.start < first and d.depth == 0]
        at = before[-1].end if before else 0
        if at and text[at - 1] != '\n':
            edits.append((at, at, '\n#include "%s"\n' % header_inc))
        else:
            edits.append((at, at, '#include "%s"\n' % header_inc))
    out = text
    for s, e, rep in sorted(edits, key=lambda x: (x[0], x[1]), reverse=True):
        out = out[:s] + rep + out[e:]
    return out


# ------------------------------------------------------------------------------------------- main

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--classes', type=Path, required=True)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--scope', nargs='*', default=['src'])
    ap.add_argument('--also-classes', nargs='*', default=[],
                    help='further census classes to import (DEV_LIB: library stubs inside the program)')
    ap.add_argument('--decide', action='store_true')
    ap.add_argument('--prototype-knr', action='store_true',
                    help='replace unprototyped `T f()` imports by a prototype from the calls when every caller is neutral')
    ap.add_argument('--apply', action='store_true')
    ap.add_argument('--identities', type=Path, nargs='*', default=[],
                    help='TSV address-or-name<TAB>comment for the declarations the tool appends (foreign_twins.py)')
    ap.add_argument('--floors', type=Path, help='floors.jsonl of an earlier --decide (default: DIR/floors.jsonl)')
    ap.add_argument('--respell', type=Path, nargs='*', default=[],
                    help='address_respell classes TSVs whose new names count as probed imports (devkit library)')
    ap.add_argument('--workers', type=int, default=4)
    ap.add_argument('--dry-run', action='store_true')
    a = ap.parse_args(argv)
    root = a.root.resolve()
    a.out.mkdir(parents=True, exist_ok=True)
    db = sqlite3.connect('file:%s?mode=ro' % (root / 'build/codemap.db'), uri=True)
    foreign = set()
    with a.classes.open() as fh:
        for row in csv.DictReader(fh, delimiter='\t'):
            if row['class'] in FOREIGN or row['class'] in a.also_classes:
                foreign.add(row['name'])
    # never an import: an address where a C unit of a live image starts (its readable name reaches it)
    live = {v for (v,) in db.execute("SELECT u.vma FROM image_unit u JOIN image i ON i.name = u.image "
                                     "WHERE i.kind = 'image' AND u.kind = 'c' AND u.vma IS NOT NULL")}
    foreign = {n for n in foreign if int(address_key(n), 16) not in live} if foreign else foreign
    progs = programs(root)
    units = file_units(db)
    canon = {}
    for name, f, cn, hp in db.execute("SELECT name, file, canon_norm, has_proto FROM decl WHERE kind = 'proto' "
                                      "AND file LIKE 'src/%'"):
        if name in foreign:
            canon[(f, name)] = (cn, hp)
    files = sorted({f for f, _n in canon})
    # ---- sites: every local declaration of a foreign name in a file of a program
    sites = []            # dict(file, name, prog, spelling, rendered, recipes)
    by_file = collections.defaultdict(list)
    for f in files:
        p = program_of(units.get(f, ()), progs)
        if p is None or not (root / f).is_file():
            continue
        if any(phys and phys != f for _r, _c, _o, phys in units[f]):
            continue                                   # a member of another physical TU: proven with it
        recipes = sorted({r for r, _c, _o, _p in units[f]})
        for (ff, name), (cn, hp) in canon.items():
            if ff == f:
                s = dict(file=f, name=name, prog=p, canon=cn, rendered=render(name, cn, hp), recipes=recipes)
                sites.append(s)
                by_file[f].append(s)
    with (a.out / 'sites.tsv').open('w') as fh:
        fh.write('file\tname\theader\tcanonical\trendered\n')
        for s in sites:
            fh.write('%s\t%s\t%s\t%s\t%s\n' % (s['file'], s['name'], progs[s['prog']]['header'], s['canon'],
                                              s['rendered'] or ''))
    print('foreign_imports: %d programs, %d sites in %d files' % (len(progs), len(sites), len(by_file)))
    floors_path = a.floors or (a.out / 'floors.jsonl')
    floors = collections.defaultdict(dict)          # file -> {name: reason}
    pool = None

    def workers():
        nonlocal pool
        if pool is None:
            import sig_probe
            pool = sig_probe.Workers(root, max(1, min(8, a.workers)))
        return pool

    try:
        if a.decide:
            decide(a, root, progs, sites, workers, floors_path)
        if a.prototype_knr:
            prototype_knr(a, root, progs, units, db, workers)
        if floors_path.is_file():
            for line in floors_path.read_text().splitlines():
                if line.strip():
                    r = json.loads(line)
                    for b in r.get('blocking', []):
                        floors[b['path']][r['name']] = b['reason']
        if a.apply:
            probed = set()
            for path in a.respell:
                with path.open() as fh:
                    probed |= {r['detail'].split(' -> ')[-1].split()[0] for r in csv.DictReader(fh, delimiter='\t')}
            apply(a, root, progs, by_file, floors, workers, probed)
    finally:
        if pool is not None:
            pool.close()
    return 0


def probe_tasks(root, site, name, cands, sig_probe):
    """sig_probe tasks: control + one variant per candidate, for every recipe of the site's file."""
    text = (root / site['file']).read_text(encoding='utf-8', errors='surrogateescape')
    spans = [(s, e) for s, e, _n, _t in sig_probe.local_decls(text, name)]
    tasks = []
    for rid in site['recipes']:
        tasks.append(dict(key='%s|%s|control' % (site['file'], rid), recipe=rid,
                          text=sig_probe.hide_variant(text, name)))
        for i, c in enumerate(cands):
            tasks.append(dict(key='%s|%s|%d' % (site['file'], rid, i), recipe=rid,
                              text=sig_probe.hide_variant(text, name, remove=spans, decl=c)))
    return tasks


def prototype_knr(a, root, progs, units, db, workers):
    """An import every site spelled `T f()` gets the prototype its calls imply: every call in the program's files
    (code map call_site) passes the same number of arguments; a pointer argument everywhere gives `void *`,
    otherwise `s32`.  The prototype replaces the header line only when it is byte-neutral in every file of the
    program that calls the name (sig_probe at each production recipe)."""
    import sig_probe
    out = []
    for pi, prog in enumerate(progs):
        hpath = root / prog['header']
        htext = hpath.read_text(errors='surrogateescape')
        knr = {n: t for n, t in header_decls(htext).items() if t.endswith(n + '()')}
        if not knr:
            continue
        files = {f for f, us in units.items() if us and program_of(us, progs) == pi
                 and not any(phys and phys != f for _r, _c, _o, phys in us)}
        for name, decl in sorted(knr.items()):
            calls = [(f, n, json.loads(t or '[]')) for f, n, t in db.execute(
                'SELECT file, nargs, arg_types FROM call_site WHERE callee = ?', (name,)) if f in files]
            if not calls or len({n for _f, n, _t in calls}) != 1:
                out.append(dict(name=name, header=prog['header'], status='kept_knr',
                                reason='no calls' if not calls else 'varying argument count'))
                continue
            nargs = calls[0][1]
            params = []
            for i in range(nargs):
                ts = [t[i] if i < len(t) else '' for _f, _n, t in calls]
                params.append('void *' if all('*' in x or '[' in x for x in ts) else 's32')
            ret = decl[:decl.index(name)].strip()
            cand = '%s%s%s(%s)' % (ret, '' if ret.endswith('*') else ' ', name, ', '.join(params) or 'void')
            tasks = []
            callers = sorted({f for f, _n, _t in calls})
            for f in callers:
                text = (root / f).read_text(encoding='utf-8', errors='surrogateescape')
                spans = [(s, e) for s, e, _n, _t in sig_probe.local_decls(text, name)]
                for rid in sorted({r for r, _c, _o, _p in units[f]}):
                    tasks.append(dict(key='%s|%s|c' % (f, rid), recipe=rid, text=sig_probe.hide_variant(text, name)))
                    tasks.append(dict(key='%s|%s|v' % (f, rid), recipe=rid,
                                      text=sig_probe.hide_variant(text, name, remove=spans, decl=cand)))
            res = dict(zip([t['key'] for t in tasks], workers().map(tasks)))
            bad = [k[:-2] for k in res if k.endswith('|v') and sig_probe.compare(res[k[:-2] + '|c'], res[k])]
            if bad:
                out.append(dict(name=name, header=prog['header'], status='kept_knr', candidate=cand,
                                reason='not neutral at ' + ', '.join(sorted(bad))[:300]))
                continue
            htext = re.sub(r'^%s;' % re.escape(decl), cand + ';', htext, count=1, flags=re.M)
            out.append(dict(name=name, header=prog['header'], status='prototyped', candidate=cand, callers=callers))
        if not a.dry_run:
            hpath.write_text(htext, errors='surrogateescape')
    (a.out / 'knr.json').write_text(json.dumps(out, indent=1))
    print('prototype_knr: %d prototyped, %d kept' % (sum(1 for x in out if x['status'] == 'prototyped'),
                                                     sum(1 for x in out if x['status'] != 'prototyped')))


def decide(a, root, progs, sites, workers, floors_path):
    import sig_probe
    idents = {}
    for path in a.identities:
        for line in path.read_text().splitlines():
            if line.strip() and not line.startswith('#'):
                n, c = line.split('\t', 1)
                idents[address_key(n)] = c.strip()
    decisions, floor_rows = [], []
    for pi, prog in enumerate(progs):
        hpath = root / prog['header']
        htext = hpath.read_text(errors='surrogateescape')
        have = header_decls(htext)
        per = collections.defaultdict(list)
        for s in sites:
            if s['prog'] == pi and s['name'] not in have:
                per[s['name']].append(s)
        lines = []
        for name in sorted(per, key=lambda n: (int(n[-8:], 16), n)):
            ss = per[name]
            for s in ss:
                if s['rendered'] and noreturn(root, s['file'], name, sig_probe):
                    s['rendered'] += ' __attribute__((noreturn))'
            rendered = collections.Counter(s['rendered'] for s in ss if s['rendered'])
            if not rendered:
                decisions.append(dict(name=name, header=prog['header'], status='unrenderable',
                                      sites=[s['file'] for s in ss]))
                continue
            cands = candidates(name, rendered)
            # trivial: one spelling, rendered without a type substitution at every site
            trivial = len(cands) == 1 and all(s['rendered'] and canon_equal(s, cands[0], name) for s in ss)
            if trivial:
                choice, results = cands[0], {}
            else:
                tasks = []
                for s in ss:
                    tasks += probe_tasks(root, s, name, cands, sig_probe)
                res = dict(zip([t['key'] for t in tasks], workers().map(tasks)))
                results = {}
                for s in ss:
                    for i, c in enumerate(cands):
                        ok = True
                        for rid in s['recipes']:
                            ctrl = res['%s|%s|control' % (s['file'], rid)]
                            var = res['%s|%s|%d' % (s['file'], rid, i)]
                            if 'error' in ctrl:
                                ok = 'uncalibrated'
                                break
                            d = sig_probe.compare(ctrl, var)
                            if d:
                                ok = 'error' if d.get('kind') == 'error' else 'changed'
                                detail = str(d.get('detail', d))[:200]
                                results.setdefault(s['file'], {})['%d_detail' % i] = detail
                                break
                        results.setdefault(s['file'], {})[i] = 'neutral' if ok is True else ok
                full = [i for i in range(len(cands)) if all(results[s['file']].get(i) == 'neutral' for s in ss)]
                if full:
                    choice = cands[full[0]]
                else:
                    counts = [sum(1 for s in ss if results[s['file']].get(i) == 'neutral') for i in range(len(cands))]
                    best = max(range(len(cands)), key=lambda i: (counts[i], -i))
                    if counts[best] == 0:
                        decisions.append(dict(name=name, header=prog['header'], status='floor_all', candidates=cands,
                                              results=results, sites=[s['file'] for s in ss]))
                        floor_rows.append(floor_record(name, prog['header'], ss, results, cands, None))
                        continue
                    choice = cands[best]
                    floor_rows.append(floor_record(name, prog['header'], ss, results, cands, best))
            decisions.append(dict(name=name, header=prog['header'], status='published', choice=choice,
                                  candidates=cands, results=results, sites=[s['file'] for s in ss]))
            comment = idents.get(address_key(name))
            lines.append(choice + ';' + ('   /* %s */' % comment if comment else ''))
        if lines and not a.dry_run:
            hpath.write_text(append_block(htext, lines), errors='surrogateescape')
        print('decide %s: %d names appended' % (prog['header'], len(lines)))
    (a.out / 'decisions.json').write_text(json.dumps(decisions, indent=1, default=str))
    with floors_path.open('w') as fh:
        for r in floor_rows:
            fh.write(json.dumps(r, sort_keys=True) + '\n')


def address_key(name):
    """0x8XXXXXXX of an address name or hex string (a placeholder nibble corrected to 8), else the name."""
    m = re.search(r'([0-9A-Fa-f]{8})$', name.strip())
    return '0x%08X' % ((int(m[1], 16) & 0x0FFFFFFF) | 0x80000000) if m else name.strip()


def noreturn(root, path, name, sig_probe):
    """The site's own declaration carries __attribute__((noreturn)) (the canonical type drops it)."""
    text = (root / path).read_text(encoding='utf-8', errors='surrogateescape')
    return any('noreturn' in t for _s, _e, _n, t in sig_probe.local_decls(text, name))


def canon_equal(site, cand, name):
    """The rendered candidate spells the site's own canonical type (no type substitution)."""
    return site['rendered'] == cand and 'struct ' not in site['canon'] and 'union ' not in site['canon']


FLOOR_TEXT = {'compile_error': "this site's argument count or types differ from the foreign program's import prototype",
              'changed_bytes': "the foreign program's import prototype changes this site's bytes",
              'unprobeable': 'not probed against the foreign program\'s import prototype'}
REASON = {'error': 'compile_error', 'changed': 'changed_bytes', 'uncalibrated': 'unprobeable'}


def floor_record(name, header, ss, results, cands, best):
    blocking = []
    for s in ss:
        r = results.get(s['file'], {})
        if best is not None and r.get(best) == 'neutral':
            continue
        why = r.get(best if best is not None else 0, 'changed')
        blocking.append(dict(path=s['file'], declaration=s['file'], is_def=False,
                             reason=REASON.get(why, why), spelling=s['rendered'] or s['canon'],
                             detail=r.get('%d_detail' % (best if best is not None else 0))))
    status = 'partial' if best is not None else 'refused'
    return dict(schema='azure-clean.prototype-floor.v1', name=name, owner=header, status=status,
                floor_class='foreign_import_spelling', reason='no single import prototype is byte-neutral at every '
                'declaration site of this foreign program', definition=dict(path=None, proto=None),
                candidates=cands, chosen=None if best is None else cands[best], blocking=blocking,
                evidence=dict(tool='tools/headers/foreign_imports.py', header=header))


def apply(a, root, progs, by_file, floors, workers, probed_names=frozenset()):
    import sig_probe
    scope = [str(Path(s)) for s in a.scope]
    rows, diffs, edits = [], [], {}
    plans, why = [], {}
    for f, ss in sorted(by_file.items()):
        if not any(f == s or f.startswith(s.rstrip('/') + '/') for s in scope):
            continue
        prog = progs[ss[0]['prog']]
        have = header_decls((root / prog['header']).read_text(errors='surrogateescape'))
        text = (root / f).read_text(encoding='utf-8', errors='surrogateescape')
        # every local declaration of a name the program header declares (also names respelled since the census)
        found, sc = local_sites(text, set(have))
        fl = floors.get(f, {})
        names = {n for n in found if n not in fl}
        held = {n: 'floor' for n in found if n in fl}
        # a header name the census did not probe for this program (a readable alias, a respelled name) is
        # replaced only where the local declaration spells the header's very type
        probed = {s['name'] for s in ss} | probed_names
        for n in sorted(names - probed):
            hk = sig_key(have[n] + ';', n)
            if hk is None or any(sig_key(text[a:b], n) != hk for a, b, _nd, _cd in found[n]):
                names.discard(n)
                held[n] = 'spelling_differs_from_header'
        held.update({s['name']: 'not_in_header' for s in ss if s['name'] not in have and s['name'] not in found})
        spans = {}
        for n in sorted(names):
            got = found.get(n, [])
            if not got:
                continue
            if any(nd > 1 or cd for _s, _e, nd, cd in got):
                held[n] = 'multi_declarator_or_conditional'
                continue
            spans[n] = [(s, e) for s, e, _nd, _cd in got]
        if spans:
            plans.append((f, prog, text, sc, spans, held, ss[0]['recipes']))
        elif held:
            rows.append((f, prog['header'], '', ','.join('%s:%s' % kv for kv in sorted(held.items())), 'nothing_to_do'))

    def variant(text, sc, prog, spans, keep):
        sel = [sp for n in keep for sp in spans[n]]
        return edit_text(text, prog['include'], sel, sc)

    tasks = []
    for f, prog, text, sc, spans, held, recipes in plans:
        for rid in recipes:
            tasks.append(dict(key='%s|%s|prod' % (f, rid), recipe=rid, text=None))
            tasks.append(dict(key='%s|%s|all' % (f, rid), recipe=rid, text=variant(text, sc, prog, spans, spans)))
    res = dict(zip([t['key'] for t in tasks], workers().map(tasks))) if tasks else {}
    retry = []
    for f, prog, text, sc, spans, held, recipes in plans:
        bad = [(rid, sig_probe.compare(res['%s|%s|prod' % (f, rid)], res['%s|%s|all' % (f, rid)])) for rid in recipes]
        bad = [(rid, d) for rid, d in bad if d]
        if bad:
            why[f] = str(bad[0][1])[:300]
        if not bad:
            edits[f] = (variant(text, sc, prog, spans, spans), sorted(spans), held, prog)
        else:
            retry.append((f, prog, text, sc, spans, held, recipes))
    # one name at a time for the failing files, then the union of the neutral ones
    tasks = []
    for f, prog, text, sc, spans, held, recipes in retry:
        for n in spans:
            for rid in recipes:
                tasks.append(dict(key='%s|%s|%s' % (f, rid, n), recipe=rid, text=variant(text, sc, prog, spans, [n])))
    res2 = dict(zip([t['key'] for t in tasks], workers().map(tasks))) if tasks else {}
    tasks, keep = [], {}
    for f, prog, text, sc, spans, held, recipes in retry:
        ok = [n for n in spans if all(not sig_probe.compare(res['%s|%s|prod' % (f, rid)], res2['%s|%s|%s' % (f, rid, n)])
                                      for rid in recipes)]
        keep[f] = ok
        if ok and len(ok) < len(spans):
            for rid in recipes:
                tasks.append(dict(key='%s|%s|some' % (f, rid), recipe=rid, text=variant(text, sc, prog, spans, ok)))
    res3 = dict(zip([t['key'] for t in tasks], workers().map(tasks))) if tasks else {}
    for f, prog, text, sc, spans, held, recipes in retry:
        ok = keep[f]
        if ok and len(ok) < len(spans) and all(
                not sig_probe.compare(res['%s|%s|prod' % (f, rid)], res3['%s|%s|some' % (f, rid)]) for rid in recipes):
            h = dict(held)
            h.update({n: 'not_neutral' for n in spans if n not in ok})
            edits[f] = (variant(text, sc, prog, spans, ok), sorted(ok), h, prog)
        else:
            h = dict(held)
            h.update({n: 'file_not_neutral' for n in spans})
            rows.append((f, prog['header'], '', ','.join('%s:%s' % kv for kv in sorted(h.items())),
                         'held: ' + why.get(f, '').replace('\t', ' ').replace('\n', ' ')))
    # floor sites keep their declaration, marked for tools/proto/prototypes.py (comment only: no line moves)
    for f, ss in sorted(by_file.items()):
        if not any(f == s or f.startswith(s.rstrip('/') + '/') for s in scope) or not floors.get(f):
            continue
        old = edits[f][0] if f in edits else (root / f).read_text(encoding='utf-8', errors='surrogateescape')
        new = old
        for name, reason in sorted(floors[f].items()):
            for m in reversed(list(re.finditer(r'^[^\n]*\b%s\b[^\n;]*;[^\n]*$' % re.escape(name), new, re.M))):
                line = m[0]
                if 'Unprototyped:' in line or not re.match(r'^(extern\s+)?[A-Za-z_]', line) or '(' not in line:
                    continue
                new = new[:m.end()] + ' /* Unprototyped: %s */' % FLOOR_TEXT.get(reason, reason) + new[m.end():]
        if new != old:
            if f in edits:
                edits[f] = (new,) + edits[f][1:]
            else:
                prog = progs[ss[0]['prog']]
                edits[f] = (new, [], {n: 'floor' for n in floors[f]}, prog)
    for f, (new, removed, held, prog) in sorted(edits.items()):
        old = (root / f).read_text(encoding='utf-8', errors='surrogateescape')
        rows.append((f, prog['header'], ','.join(removed), ','.join('%s:%s' % kv for kv in sorted(held.items())),
                     'applied' if removed else 'floor_marked'))
        diffs.extend(difflib.unified_diff(old.splitlines(True), new.splitlines(True), 'a/' + f, 'b/' + f))
        if not a.dry_run:
            (root / f).write_text(new, encoding='utf-8', errors='surrogateescape')
    with (a.out / 'apply.tsv').open('w') as fh:
        fh.write('file\theader\tremoved\theld\tstatus\n')
        fh.writelines('\t'.join(r) + '\n' for r in sorted(rows))
    (a.out / 'foreign_imports.patch').write_text(''.join(diffs), errors='surrogateescape')
    removed = sum(len(r[2].split(',')) for r in rows if r[2])
    print('apply: %d files edited, %d declarations removed, %d files held' % (
        sum(1 for r in rows if r[4] == 'applied'), removed, sum(1 for r in rows if r[4].startswith('held'))))


if __name__ == '__main__':
    sys.exit(main())
