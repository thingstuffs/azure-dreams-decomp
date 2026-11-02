#!/usr/bin/env python3
"""Address-named calls -> the real function's name (owner ruling 11-02: "call the real one").

    address_names.py plan  --scope src/dungeon/effect ... [--codemap build/codemap.db] --out DIR
    address_names.py apply --plan DIR/plan.tsv [--hold DIR/holds.tsv]

A TU that declares a raw address name (`extern void func_8002421C(...)`, or a per-address alias such as
`func_80069EF8` for the library's `rand`) and calls it gets the callee's own name, when the retail bytes
prove which function every one of its calls reaches and that the new spelling links to the same address:

  * the declared name lowers (config/names.tsv) to func_<X>; every retail call the TU's recipes make to X
    (build/codemap.db call_bind, image by image) is bound to ONE C function R (its readable name from the
    object, retail_fn.name), or X is a Psy-Q library entry point whose canonical name the SDK table knows
    (tools/headers/extra.py);
  * R's own symbol links to X from every caller unit: R lowers to func_<X> itself (`same_symbol`), or R is
    a library symbol at X (`library_alias`).  The image link resolves an undefined func_<A> by the address
    in its name (tools/gate/overlay_local_gate.symbol_addr) and rebinds only placement units
    (tools/gate/linklist.binding), so a placed copy of R at another address is NOT reachable by R's name:
    such names are reported (`placed_copy`, `home_self`) and never edited here (see
    docs/SIGNATURE_SOLVER.md, "Address names").

Placed copies (owner ruling 11-02, same-image copy rule; docs/LINK_LISTS.md "Same-image copy links"): when R's
symbol func_<H> names a TU whose copy at X is placed in the caller's load image, the call is `placed_copy` and
qualifies when, for every unit of the caller's recipes, the link reaches X under R's name: each home unit's image
holds exactly one instance of R's TU, the copy at X (linklist.copy_link_target), and each placement unit of the
caller binds func_<H> where it bound func_<X> (rules 1-6).  apply then also writes the caller rows' opt-in record
(config/link/copy_links.json: {row: {func_<H>: func_<X>}}) and projects it onto the link graph through its
producer (tools/link/graph.py sync-copy-links).  Native module callers are held (their import inventory names the symbol).

`home_self` (R is the callee unit's own home, called at its TRUE address, while R lowers to the synthetic row key)
is planned too: `truenames` maps R to the row's true symbol in config/names.tsv (rowbase policy: a TU in a proven
region defines its true name), after which the call is `same_symbol`.

apply renames every code token of the address name in the TU (comments and strings untouched) to R.  The
TU's own declaration is respelled to R (same types, so the object is identical: R lowers back to the same
symbol) unless the TU already sees a declaration of R, in which case the local one is deleted.  The
follow-up `extern_bulk.py` run moves the respelled declaration into R's owning header (or holds it with
the planner's reason).  Idempotent: a TU with no remaining address name is unchanged.
"""
from __future__ import annotations

import argparse
import collections
import os
import csv
import json
import re
import sqlite3
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent / 'gate')]

ADDR = re.compile(r'^(?:func|D)_([0-9A-Fa-f]{8})$')
FIELDS = ['file', 'old', 'new', 'kind', 'symbol', 'calls', 'images', 'new_header', 'evidence', 'link']


def names_table(root):
    name2sym = {}
    for line in (root / 'config/names.tsv').read_text().splitlines():
        cols = line.split('#', 1)[0].split('\t')
        if len(cols) >= 3 and cols[1].strip() and cols[2].strip():
            name2sym[cols[2].strip()] = cols[1].strip()
    return name2sym


def in_scope(path, scope):
    return any(path == s or path.startswith(s.rstrip('/') + '/') for s in scope)


def plan(root, codemap, scope, exclude=()):
    import extra
    import linklist as L
    images, by_place, by_row, local = L.load(str(root))
    lib_names, lib_addr, _ = extra.library_symbols(root)
    c = sqlite3.connect(f'file:{codemap}?mode=ro', uri=True)
    q = lambda s, *p: c.execute(s, p).fetchall()  # noqa: E731
    name2sym = names_table(root)
    lower = lambda n: name2sym.get(n, n)  # noqa: E731
    recipes = collections.defaultdict(set)
    module_tus = set()
    for rid, src, kind in q('select id, source, kind from recipe'):
        recipes[src].add(rid)
        if kind == 'module':
            module_tus.add(src)
    phys_of = {rid: (src, phys) for rid, src, phys in q('select id, source, physical from recipe')}
    deps_c = collections.defaultdict(set)
    for rid, dp in q("select recipe, path from tu_dep where path like '%.c'"):
        deps_c[rid].add(dp)

    def files_of(rid):
        """Source files whose definitions a recipe compiles (its own/physical source and included .c members)."""
        src, phys = phys_of.get(rid, (None, None))
        return {x for x in (src, phys) if x} | deps_c.get(rid, set())
    defs_in = collections.defaultdict(set)
    for nm, df in q('select name, file from defn'):
        defs_in[df].add(nm)
    defined = {n for n, in q('select distinct name from defn')}
    units = collections.defaultdict(list)
    for img, rec, rows in q('select image, recipe, rows from image_unit'):
        units[(img, rec)].extend(json.loads(rows or '[]'))
    # TUs that declare the address name at file scope, or call it through a header's declaration
    headers_of = collections.defaultdict(set)
    for nm, hf in q("select distinct name, file from decl where kind = 'proto' and file like 'include/%'"):
        headers_of[nm].add(hf)
    import plan as P
    def_files = collections.defaultdict(set)
    for nm, df in q('select name, file from defn'):
        def_files[nm].add(df)

    def one_header(nm, lib=None):
        """The header a TU should see R from: the SDK stand-in, else the definition's folder header, else the
        only header declaring it."""
        hs = headers_of.get(nm, set())
        if lib:
            h = 'include/sdk/%s.h' % lib
            return h if h in hs else ''
        owners = {P.header_for(df) for df in def_files.get(nm, ())}
        if len(owners) == 1 and owners <= hs:
            return owners.pop()
        return sorted(hs)[0] if len(hs) == 1 else ''
    registry = {}
    for line in (root / 'ledger/rows.jsonl').read_text().splitlines():
        rec = json.loads(line)
        registry[rec['id']] = rec
    unit_info = collections.defaultdict(list)     # recipe -> [(image, rows, rebind, vma)]
    for img, rec, rows, reb, vma in q('select image, recipe, rows, rebind, vma from image_unit'):
        unit_info[rec].append((img, json.loads(rows or '[]'), reb, vma))
    tables = (images, by_place, by_row, local)

    def home_self(r, rm, binds, x):
        """R is the home unit every call reaches, at the row's TRUE address, while R lowers to the row key."""
        rows = set()
        crecs = sorted({b[1] for b in binds})
        for img, rr in q(f'select callee_image, callee_recipe from call_bind where target = ? and caller_recipe in '
                         f'({",".join("?" * len(crecs))})', x, *crecs):
            us = [u for u in unit_info.get(rr, []) if u[0] == img and u[3] == x and not u[2]]
            if len(us) != 1:
                return None
            rows.update(us[0][1])
        if len(rows) != 1:
            return None
        row = registry.get(rows.pop())
        if (not row or row['id'].split('/', 1)[1] != rm[0] or row.get('true_name') != 'func_%08X' % x
                or row.get('source_row')):
            return None
        home = by_row.get(row['id'])
        if home is not None and home['vma'] != x:
            return None
        return 'home %s runs at %s (registry true_name)' % (row['id'], row['true_name'])

    def copy_link(f, recs, h, x):
        """Rows to record when every unit of the caller's recipes reaches X under func_<H>; else a hold reason."""
        rows = []
        calling = {crec for _, crec, *_ in q(f'select image, caller_recipe from call_bind where target = ? and caller_recipe in '
                                             f'({",".join("?" * len(recs))})', x, *recs)}
        for rec in sorted(recs):
            if rec in module_recipes:
                return 'module_caller'
            for img, urows, reb, vma in unit_info.get(rec, []):
                if reb:
                    es = [by_row[rid] for rid in urows if rid in by_row and by_row[rid]['row'] != by_row[rid]['home']]
                    if len(es) != 1:
                        return 'caller_placement_unknown'
                    try:
                        if L._binding(tables, es[0], h) != L._binding(tables, es[0], x):
                            return 'caller_placement_binds_elsewhere'
                    except ValueError:
                        return 'caller_placement_ambiguous'
                    continue
                if rec not in calling:
                    continue
                try:
                    got = L.copy_link_target(tables, img, h)
                except ValueError as e:
                    msg = str(e)
                    return ('ambiguous' if 'instances' in msg else 'home_in_image' if 'home of' in msg
                            else 'not_load_image' if 'load image' in msg else 'callee_home_unknown')
                if got != x:
                    return 'copy_elsewhere'
                rows.extend(urows)
        return sorted(set(rows)) or 'no_home_caller'
    module_recipes = {rid for rid, kind in q('select id, kind from recipe') if kind == 'module'}
    sites = sorted(set(q("select distinct file, name from decl where local = 0 and kind = 'proto' and file like 'src/%'"))
                   | set(q("select distinct file, callee from call_site where file like 'src/%.c'")))
    out, report = [], collections.Counter()
    for f, n in sites:
        if not f.endswith('.c') or not in_scope(f, scope) or in_scope(f, exclude):
            continue
        sym = lower(n)
        m = ADDR.match(sym)
        if not m or not sym.startswith('func_'):
            continue
        x = int(m[1], 16)
        recs = recipes.get(f, set())
        if not recs:
            continue
        ph = ','.join('?' * len(recs))
        binds = q(f'select image, caller_recipe, callee_recipe, callee, how from call_bind '
                  f'where target = ? and caller_recipe in ({ph})', x, *recs)
        if not binds:
            report['no_retail_call'] += 1
            continue
        # library entry point at X with a canonical SDK name
        libs = sorted({nm for lb, nm, ev in lib_addr.get(x, []) if nm in extra.SDK})
        if libs and n not in extra.SDK and f in module_tus:
            # a native module recipe records its import inventory by symbol (config/overlays/modules.json
            # `imports`, checked by tools/gate/overlay_module_gate.py): the library spelling is another import
            report['library_alias_in_module'] += 1
            continue
        if libs and n not in extra.SDK:
            if len(libs) == 1 and all(how in ('resident', 'slus_symbol') for *_, how in binds):
                out.append(dict(file=f, old=n, new=libs[0], kind='library_alias', symbol=sym,
                                calls=len(binds), images=len({b[0] for b in binds}),
                                new_header=one_header(libs[0], lib=lib_addr[x][0][0]),
                                evidence='config/slus_006.14.symbols.txt: %s = 0x%08X' % (libs[0], x)))
                report['library_alias'] += 1
            else:
                report['library_ambiguous'] += 1
            continue
        # the callee's name is the function its TU DEFINES with that symbol (retail_fn.name picks one of
        # several names.tsv aliases of a shared address, so it is not an identity)
        targets = set()
        for _, _, rr, sy, _ in binds:
            if not rr:
                continue
            here = {d for src in files_of(rr) for d in defs_in.get(src, ()) if lower(d) == sy}
            targets |= here if len(here) == 1 else {('?', sy)}
        if n in defs_in.get(f, ()):
            report['defined_in_tu'] += 1
            continue
        if any(isinstance(t, tuple) for t in targets):
            report['callee_name_unknown'] += 1
            continue
        if len(targets) != 1 or any(rr is None for _, _, rr, _, _ in binds):
            report['multi_or_unresolved_target'] += 1
            continue
        r = targets.pop()
        if r == n or r not in defined:
            report['no_c_name'] += 1
            continue
        if lower(r) != sym:
            rm = ADDR.match(lower(r))
            hs = home_self(r, rm, binds, x) if rm else None
            if hs:
                out.append(dict(file=f, old=n, new=r, kind='home_self', symbol=sym, calls=len(binds),
                                images=len({b[0] for b in binds}), new_header=one_header(r),
                                evidence=hs, link='%s>%s' % (lower(r), sym)))
                report['home_self'] += 1
                continue
            verdict = copy_link(f, recs, int(rm[1], 16), x) if rm else 'callee_symbol_not_an_address'
            if isinstance(verdict, list):
                out.append(dict(file=f, old=n, new=r, kind='placed_copy', symbol=sym, calls=len(binds),
                                images=len({b[0] for b in binds}), new_header=one_header(r),
                                evidence='same-image copy of %s at 0x%08X; rows %s' % (lower(r), x, ' '.join(verdict)),
                                link='%s>%s' % (lower(r), sym)))
                report['placed_copy'] += 1
                continue
            # R's symbol is another address: only a placement caller could reach X through rebinding
            ok = True
            for img, crec, *_ in binds:
                entry = next((by_row[rid] for rid in units.get((img, crec), []) if rid in by_row
                              and by_row[rid]['image'] == img), None)
                rm = ADDR.match(lower(r))
                if entry is None or entry['row'] == by_row[entry['home']]['row'] or not rm:
                    ok = False
                    break
                if L.binding(str(root), entry, int(rm[1], 16)) != x:
                    ok = False
                    break
            if not ok:
                report['held_copy:' + verdict] += 1
                continue
            kind = 'placement_binding'
        else:
            kind = 'same_symbol'
        out.append(dict(file=f, old=n, new=r, kind=kind, symbol=sym, calls=len(binds),
                        images=len({b[0] for b in binds}), new_header=one_header(r),
                        evidence='call_bind: %d retail calls -> %s' % (len(binds), r)))
        report[kind] += 1
    # A callee whose name this run maps to its true symbol (home_self) lowers differently after the run: its
    # placed-copy callers are planned on the next run, against the new symbol.
    renamed = {r['new'] for r in out if r['kind'] == 'home_self'}
    later = [r for r in out if r['kind'] == 'placed_copy' and r['new'] in renamed]
    for r in later:
        out.remove(r)
        report['placed_copy'] -= 1
        report['held_copy:callee_home_self_this_run'] += 1
    return out, report


TOKEN = r'(?<![A-Za-z0-9_]){}(?![A-Za-z0-9_])'


_CORPUS = {}


def visible_declares(root, rel, name, text):
    """Does a header the TU includes (transitively) declare `name`?"""
    import model as M
    corpus = _CORPUS.get(root) or _CORPUS.setdefault(root, M.Corpus(root))
    for h in corpus.closure(rel):
        if h == rel:
            continue
        try:
            body = (root / h).read_text(errors='replace')
        except OSError:
            continue
        import cscan
        if re.search(TOKEN.format(re.escape(name)) + r'\s*\(', cscan.mask(body)):
            return h
    return None


def depth_at(masked, pos):
    """Brace depth at pos (file scope = 0)."""
    return masked.count('{', 0, pos) - masked.count('}', 0, pos)


def apply_one(root, rel, pairs, log, corpus_root=None):
    import cscan
    path = root / rel
    text = path.read_text()
    masked = cscan.mask(text)
    edits, includes = [], []
    for old, new, header in pairs:
        if not re.search(TOKEN.format(re.escape(old)), masked):
            continue
        seen = visible_declares(corpus_root or root, rel, new, text)
        if not seen and re.search(r'^[^#\n]*' + TOKEN.format(re.escape(new)) + r'\s*\([^;{}]*\)\s*;', masked, re.M):
            seen = rel     # the TU declares the new name itself
        # the TU's file-scope declarations of `old` (one declarator each)
        decls = [m for m in re.finditer(r'^[ \t]*(?:extern[ \t]+)?[^;{}()#=\n]*?' + TOKEN.format(re.escape(old)) +
                                        r'\s*\([^;{}=]*\)\s*;[^\n]*\n', masked, re.M)
                 if depth_at(masked, m.start()) == 0]
        if not decls and not seen:
            # no declaration to respell and none of R visible: adding R's header here conflicts too often with
            # the TU's other header views (screened); the extern wave decides includes, so hold the name
            log.append((rel, old, new, 0, 'hold:no_visible_prototype'))
            continue
        for m in decls:
            if seen:
                edits.append((m.start(), m.end(), ''))
            else:
                seg = text[m.start():m.end()]
                edits.append((m.start(), m.end(), re.sub(TOKEN.format(re.escape(old)), new, seg, count=1)))
        covered = [(m.start(), m.end()) for m in decls]
        for m in re.finditer(TOKEN.format(re.escape(old)), masked):
            if any(a <= m.start() < b for a, b in covered):
                continue
            edits.append((m.start(), m.end(), new))
        how = ('deleted_declaration (sees %s)' % seen) if decls and seen else (
            'respelled' if decls else ('include ' + includes[-1] if not seen else 'uses only'))
        log.append((rel, old, new, len(decls), how))
    if not edits:
        return False
    for a, b, s in sorted(edits, reverse=True):
        text = text[:a] + s + text[b:]
    for inc in sorted(set(includes)):
        line = '#include "%s"\n' % inc
        if line in text:
            continue
        last = [m for m in re.finditer(r'^#include[^\n]*\n', text, re.M)]
        at = last[-1].end() if last else 0
        text = text[:at] + line + text[at:]
    path.write_text(text)
    return True


def lib_symbol_names(root):
    """Library symbol -> its address name (config/slus_006.14.symbols.txt), for object comparison."""
    out = {}
    for line in (root / 'config/slus_006.14.symbols.txt').read_text().splitlines():
        m = re.match(r'(\w+)\s*=\s*(0x[0-9a-fA-F]+);', line)
        if m:
            out[m[1]] = 'func_%08X' % int(m[2], 16)
    return out


def screen(root, codemap, plan_path, out_dir, workers=3):
    """Compile every edited TU before/after at each of its production recipes' compiler arguments (the
    root's tools/build/cc.sh pipeline) and compare the objects (tools/rename_proof.compare_objects: allocated
    sections, relocations, symbols) with library symbols renamed to their address names.  Pairs whose TU
    differs are retried alone; a pair that still differs is written to DIR/holds.tsv.  Screening is
    attribution only: acceptance is the build-graph proof (tools/lanes/prove_batch.sh).  Each trial compiles a
    sibling dot file `.addrnames_<pid>_*.c` next to the TU (removed after the compile; a killed run can leave one,
    which the corpus scan and the build ignore)."""
    import subprocess, tempfile, shutil, concurrent.futures as cf
    sys.path.insert(0, str(root / 'tools'))
    import rename_proof
    c = sqlite3.connect(f'file:{codemap}?mode=ro', uri=True)
    args_of = collections.defaultdict(set)
    for src, args in c.execute("select source, args from recipe where source like 'src/%'"):
        a = (json.loads(args or '[]') + ['', '', ''])[:3]
        args_of[src].add(tuple(a))
    libmap = lib_symbol_names(root)
    by_file = collections.defaultdict(list)
    links = collections.defaultdict(dict)
    for r in csv.DictReader(open(plan_path), delimiter='\t'):
        by_file[r['file']].append((r['old'], r['new'], r.get('new_header', '')))
        if r.get('link'):
            # placed_copy / home_self: the respelled call lowers to A where the old spelling lowered to B; the
            # link (copy-link record / true-name remap) maps A back to B, so compare the after-object with A -> B
            a, b = r['link'].split('>')
            links[(r['file'], r['old'])] = (a, b)
    out_dir = Path(out_dir); out_dir.mkdir(parents=True, exist_ok=True)
    tmp = Path(tempfile.mkdtemp(prefix='addrnames_', dir=out_dir))

    def compile_text(rel, text, args, tag):
        src = (root / rel).parent / ('.addrnames_%d_%s_%s' % (os.getpid(), tag, Path(rel).name))
        obj = tmp / ('%s_%s.o' % (rel.replace('/', '_'), tag))
        src.write_text(text)
        try:
            res = subprocess.run(['nice', '-n', '10', 'bash', 'build_slus/tools/cc.sh', str(src), str(obj), *args],
                                 cwd=root, capture_output=True, text=True)
        finally:
            src.unlink()
        if res.returncode:
            # checkout-relative diagnostics (receipts carry no absolute paths)
            err = res.stderr.replace(str(root) + '/', '').replace(str(src.parent) + '/', '')
            return None, err[-400:]
        used = subprocess.run(['mipsel-linux-gnu-nm', str(obj)], capture_output=True, text=True).stdout.split()
        ren = [x for x in used if x in libmap]
        if ren:
            subprocess.run(['mipsel-linux-gnu-objcopy'] + ['--redefine-sym=%s=%s' % (x, libmap[x]) for x in ren] +
                           [str(obj)], check=True)
        return obj, ''

    def nm_set(obj):
        return set(subprocess.run(['mipsel-linux-gnu-nm', str(obj)], capture_output=True, text=True).stdout.splitlines())

    def check(rel, pairs, tag):
        base = (root / rel).read_text()
        trial = tmp / 'trial'
        work = tmp / ('w_' + tag)
        work.mkdir(exist_ok=True)
        # apply the pairs to a scratch copy of the TU text
        shadow = work / 'root'
        if not shadow.exists():
            shadow.mkdir()
        dst = shadow / rel
        dst.parent.mkdir(parents=True, exist_ok=True)
        dst.write_text(base)
        apply_one(shadow, rel, pairs, [], corpus_root=root)
        after = dst.read_text()
        if after == base:
            return True, 'unchanged'
        relink = dict(links[(rel, o)] for o, n, h in pairs if (rel, o) in links)
        for args in sorted(args_of.get(rel) or {('2.7.2', '', '')}):
            a, ea = compile_text(rel, base, args, tag + 'a')
            b, eb = compile_text(rel, after, args, tag + 'b')
            if a is None:
                return False, 'baseline_compile:' + ea
            if b is None:
                return False, 'compile:' + eb.replace('\n', ' ')
            if relink:
                used = set(subprocess.run(['mipsel-linux-gnu-nm', str(b)], capture_output=True, text=True).stdout.split())
                ren = [(x, y) for x, y in relink.items() if x in used]
                if ren:
                    subprocess.run(['mipsel-linux-gnu-objcopy'] + ['--redefine-sym=%s=%s' % xy for xy in ren] + [str(b)],
                                   check=True)
            res = rename_proof.compare_objects(a.read_bytes(), b.read_bytes())
            if not res['equal']:
                if res['differences'] == ['symbols'] and nm_set(a) == nm_set(b):
                    continue    # one import merged with an equal one (two spellings of one library address)
                return False, 'object:' + ','.join(res['differences'])[:200]
        return True, 'identical'

    results, holds = [], []
    jobs = sorted(by_file.items())

    def run(item):
        rel, pairs = item
        tag = '%x' % (abs(hash(rel)) % (1 << 32))
        ok, why = check(rel, pairs, tag)
        if ok:
            return [(rel, o, n, 'pass', why) for o, n, h in pairs]
        rows = []
        good = []
        for i, pr in enumerate(pairs):
            ok1, why1 = check(rel, [pr], tag + str(i))
            rows.append((rel, pr[0], pr[1], 'pass' if ok1 else 'hold', why1))
            if ok1:
                good.append(pr)
        if len(good) > 1:
            okg, whyg = check(rel, good, tag + 'g')
            if not okg:
                rows = [(r[0], r[1], r[2], 'hold' if r[3] == 'pass' else r[3], r[4] if r[3] != 'pass' else 'combination:' + whyg)
                        for r in rows]
        return rows

    with cf.ThreadPoolExecutor(workers) as ex:
        for rows in ex.map(run, jobs):
            results += rows
    shutil.rmtree(tmp, ignore_errors=True)
    with open(out_dir / 'screen.tsv', 'w') as fh:
        fh.write('file\told\tnew\tverdict\twhy\n')
        for r in results:
            fh.write('\t'.join(r) + '\n')
    with open(out_dir / 'holds.tsv', 'w') as fh:
        for r in results:
            if r[3] == 'hold':
                fh.write('%s\t%s\t%s\n' % (r[0], r[1], r[4]))
    print(collections.Counter(r[3] for r in results))


_SOURCES = {}


def spelled_anywhere(root, name):
    """Does any source or header (src/, include/) spell `name` as a token?"""
    if root not in _SOURCES:
        _SOURCES[root] = [p.read_text(errors='replace') for d in ('src', 'include') for p in (root / d).rglob('*')
                          if p.suffix in ('.c', '.h', '.inc') and p.is_file()]
    pat = re.compile(TOKEN.format(re.escape(name)))
    return any(name in t and pat.search(t) for t in _SOURCES[root])


def link_records(root, rows):
    """The link side of applied placed_copy / home_self pairs.

    placed_copy: merge {caller row: {func_<H>: func_<X>}} into config/link/copy_links.json, then project it onto the
    link graph through its producer (tools/link/graph.py capture; never an edit of its shards).
    home_self: point R's config/names.tsv row at the row's true symbol, and drop other names of that symbol that no
    source or header spells any more (one name per function)."""
    import subprocess, tempfile, shutil
    import linklist as L
    units = {r: {'func_%08X' % h: 'func_%08X' % c for h, c in v.items()} for r, v in L.copy_links(root).items()}
    copies = [r for r in rows if r['kind'] == 'placed_copy']
    for r in copies:
        h, x = r['link'].split('>')
        for row in r['evidence'].split('; rows ', 1)[1].split():
            units.setdefault(row, {})[h] = x
    if copies:
        L.write_copy_links(root, units)
        # the link graph carries the record as a TU attribute: its producer projects it (no shard edits)
        subprocess.run([sys.executable, str(root / 'tools/link/graph.py'), '--root', str(root),
                        '--graph', str(root / 'config/link_graph'), 'sync-copy-links'],
                       check=True, capture_output=True, text=True)
    selfs = {r['new']: r['link'].split('>')[1] for r in rows if r['kind'] == 'home_self'}
    # a true symbol is a RAM-slot label other rows may share: retire only aliases whose evidence names the same
    # row (its synthetic symbol), never a name documented for another function at that slot
    rowkey = {}
    for r in rows:
        if r['kind'] == 'home_self':
            rowkey.setdefault(r['link'].split('>')[1], set()).add(r['link'].split('>')[0])
    if selfs:
        path = root / 'config/names.tsv'
        lines = path.read_text().splitlines(keepends=True)
        out, retired = [], []
        targets = set(selfs.values())
        for line in lines:
            cols = line.rstrip('\n').split('\t')
            if len(cols) >= 3 and cols[2] in selfs:
                sym = selfs[cols[2]]
                note = 'true symbol: the definition runs at %s (home_self, same-image copy lane)' % sym
                evidence = '\t'.join(cols[3:])
                out.append('\t'.join(['0x' + sym[5:], sym, cols[2], (evidence + ' | ' + note) if evidence else note]) + '\n')
                continue
            if len(cols) >= 3 and cols[1] in targets and cols[2] not in selfs:
                same_row = any(k in '\t'.join(cols[3:]) for k in rowkey.get(cols[1], ()))
                if same_row and not spelled_anywhere(root, cols[2]):
                    retired.append(cols[2])
                    continue
            out.append(line)
        path.write_text(''.join(out))
        print('names: %d mapped to true symbols, %d unused aliases retired (%s)'
              % (len(selfs), len(retired), ' '.join(retired)))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='cmd', required=True)
    p = sub.add_parser('plan')
    p.add_argument('--root', default='.')
    p.add_argument('--codemap')
    p.add_argument('--scope', nargs='+', default=['src'])
    p.add_argument('--exclude', nargs='*', default=[])
    p.add_argument('--out', required=True)
    a2 = sub.add_parser('apply')
    a2.add_argument('--root', default='.')
    a2.add_argument('--plan', required=True)
    a2.add_argument('--hold', help='TSV of file<TAB>old pairs to skip (proof back-offs)')
    a2.add_argument('--log')
    a2.add_argument('--kinds', help='comma list of plan kinds to apply (default: all)')
    s = sub.add_parser('screen')
    s.add_argument('--root', default='.')
    s.add_argument('--codemap')
    s.add_argument('--plan', required=True)
    s.add_argument('--out', required=True)
    s.add_argument('--workers', type=int, default=3)
    a = ap.parse_args()
    root = Path(a.root).resolve()
    if a.cmd == 'plan':
        out, report = plan(root, Path(a.codemap or root / 'build/codemap.db').resolve(), a.scope, a.exclude)
        d = Path(a.out)
        d.mkdir(parents=True, exist_ok=True)
        with open(d / 'plan.tsv', 'w') as fh:
            w = csv.DictWriter(fh, fieldnames=FIELDS, delimiter='\t', lineterminator='\n')
            w.writeheader()
            w.writerows(sorted(out, key=lambda r: (r['file'], r['old'])))
        (d / 'report.json').write_text(json.dumps(dict(report), indent=1, sort_keys=True) + '\n')
        print(dict(report))
        return
    if a.cmd == 'screen':
        screen(root, Path(a.codemap or root / 'build/codemap.db').resolve(), a.plan, a.out, a.workers)
        return
    held = set()
    if a.hold and Path(a.hold).is_file():
        held = {tuple(l.split('\t')[:2]) for l in Path(a.hold).read_text().splitlines() if l.strip()}
    by_file = collections.defaultdict(list)
    kinds = set(a.kinds.split(',')) if a.kinds else None
    for r in csv.DictReader(open(a.plan), delimiter='\t'):
        if kinds is not None and r['kind'] not in kinds:
            held.add((r['file'], r['old']))
        if (r['file'], r['old']) not in held:
            by_file[r['file']].append((r['old'], r['new'], r.get('new_header', '')))
    selfs = {r['new'] for r in csv.DictReader(open(a.plan), delimiter='\t') if r['kind'] == 'home_self'
             and (r['file'], r['old']) not in held}
    late = [r for r in csv.DictReader(open(a.plan), delimiter='\t') if r['kind'] == 'placed_copy'
            and r['new'] in selfs and (r['file'], r['old']) not in held]
    if late:
        raise SystemExit('plan applies home_self and placed_copy to one callee (%s): re-plan' % late[0]['new'])
    log, changed = [], 0
    for rel, pairs in sorted(by_file.items()):
        changed += apply_one(root, rel, pairs, log)
    applied = {(row[0], row[1]) for row in log if not str(row[4]).startswith('hold')}
    linked = [r for r in csv.DictReader(open(a.plan), delimiter='\t')
              if r['kind'] in ('placed_copy', 'home_self') and (r['file'], r['old']) in applied
              and (r['file'], r['old']) not in held]
    if linked:
        link_records(root, linked)
    if a.log:
        Path(a.log).write_text(''.join('\t'.join(map(str, row)) + '\n' for row in log))
    print('files changed: %d, names: %d' % (changed, len(log)))


if __name__ == '__main__':
    main()
