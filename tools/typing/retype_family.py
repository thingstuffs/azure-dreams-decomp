#!/usr/bin/env python3
"""Rewrite one census family's raw-offset sites into typed member accesses, proven per physical TU.

    retype_family.py --sites out/field_census/sites.jsonl.gz --family tools/typing/families/sprite_frame_state.json
                     --out results.jsonl --deps-cache deps.json [--only FILE...] [--skip FILE...]

family.json:
    {"type": "SpriteFrameState", "header": "shared/sprite_frame_state.h",
     "labels": ["ObjectNodeHeader->[0xc]", "SpriteFrameState"],
     "fields": {"0x14:2": "flags:u", "0xc:4": "color.word:s", "0xc:1": "color.c.r:u", ...},
     "constants": {"scale_x": {"0x1000": "ONE"}}}

With --all-spellings, fold_family supplies exact Clang source ranges for member views,
accessor macros and constant indexes as well. --queue-file restricts owned C paths;
registered SLUS consumers are explicit holds requiring a separate full-image proof.
Parameters with external prototypes retain explicit shared-type casts.

Default parser scope: raw_cast / F_macro sites whose base is a plain *local* `void *` or `u8 *` variable declared
on its own line.  A variable is retyped only when every raw site through it in that function belongs to the
family and maps to a declared field, and it is not otherwise used as a byte pointer (`V + k`, `V[i]`, `*V`,
`V++`).  Loads whose signedness differs from the field use `*(s16 *)&V->f` (same load instruction); stores
need no cast.  Each physical TU is compiled before and after (tu_identity / capture_one); a TU whose object
changes is retried variable by variable and the failing variables are reverted and recorded as refusals.
"""
from __future__ import annotations

import argparse
import os
import collections
from concurrent.futures import ProcessPoolExecutor
import gzip
import json
from pathlib import Path
import re
import subprocess
import sys

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE.parent), str(HERE)]

SIGNED = {'s8': 's1', 's16': 's2', 's32': 's4', 'u8': 'u1', 'u16': 'u2', 'u32': 'u4'}
CTYPE = {('s', 1): 's8', ('u', 1): 'u8', ('s', 2): 's16', ('u', 2): 'u16', ('s', 4): 's32', ('u', 4): 'u32'}
BYTEPTR = r'(?:u8|s8|char|unsigned char|signed char)'


def norm(text):
    return re.sub(r'\s+', '', text)


def strip_parens(t):
    while t.startswith('(') and t.endswith(')') and balanced(t[1:-1]):
        t = t[1:-1]
    return t


def balanced(t):
    d = 0
    for ch in t:
        d += ch == '('
        d -= ch == ')'
        if d < 0:
            return False
    return d == 0


def match_close(text, i):
    """index of the ')' matching text[i] == '('"""
    d = 0
    for j in range(i, len(text)):
        if text[j] == '(':
            d += 1
        elif text[j] == ')':
            d -= 1
            if d == 0:
                return j
    return -1


def access_spelling(expr, following=''):
    """Member accesses need no wrapper; unary loads need one before postfixes."""
    tail = re.sub(r'^(?:\s|/\*.*?\*/|//[^\n]*(?:\n|$))*', '', following, flags=re.S)
    if expr.startswith('*') and re.match(r'(?:\[|\.|->|\+\+|--|\()', tail):
        return '(' + expr + ')'
    return expr


F_HEAD = re.compile(r'\bF\s*\(')
CAST_TYPE = re.compile(r'^[A-Za-z_][A-Za-z0-9_]*\*+$')
EXPR = re.compile(r'\(?\((?:u8|s8|char|unsignedchar|signedchar)\*\)\(?(?P<v>[A-Za-z_]\w*)\)?\)?'
                  r'(?:(?P<op>[+-])\(?(?P<off>0x[0-9A-Fa-f]+|\d+|\(-?(?:0x[0-9A-Fa-f]+|\d+)\)|-(?:0x[0-9A-Fa-f]+|\d+))\)?)?$')


def skip_ws(text, i):
    while i < len(text) and text[i] in ' \t':
        i += 1
    return i


def parse_deref(line, i):
    """At line[i] == '*': parse `*((T *) E)` or `*(T *) (E)`; return (end, var, off) or None."""
    j = skip_ws(line, i + 1)
    if j >= len(line) or line[j] != '(':
        return None
    close = match_close(line, j)
    if close < 0:
        return None
    inner = line[j + 1:close]
    k = skip_ws(inner, 0)
    if k < len(inner) and inner[k] == '(':
        c2 = match_close(inner, k)
        cast = norm(inner[k + 1:c2]) if c2 > 0 else ''
        if c2 > 0 and CAST_TYPE.match(cast):
            expr, end = inner[c2 + 1:], close + 1          # form A
        else:
            expr = None
    else:
        expr = None
    if expr is None:
        cast = norm(inner)
        if not CAST_TYPE.match(cast):
            return None
        k = skip_ws(line, close + 1)
        if k >= len(line) or line[k] != '(':
            return None
        c3 = match_close(line, k)
        if c3 < 0:
            return None
        expr, end = line[k:c3 + 1], c3 + 1                    # form B
    parsed = parse_byte_address(expr)
    if parsed is not None:
        return end, parsed[0], parsed[1]
    return None


def parse_byte_address(expr):
    """A variable plus a constant byte offset, allowing redundant casts/parens.

    Only byte-pointer and void-pointer casts are erased. Typed-pointer arithmetic
    is deliberately rejected because its stride is not one byte.
    """
    e = strip_parens(norm(expr))
    depth = 0
    split = None
    for i, ch in enumerate(e):
        if ch == '(':
            depth += 1
        elif ch == ')':
            depth -= 1
        elif depth == 0 and ch in '+-' and i:
            split = (i, ch)
    if split:
        i, op = split
        left = parse_byte_address(e[:i])
        try:
            right = int(strip_parens(e[i + 1:]), 0)
        except ValueError:
            return None
        if left:
            return left[0], left[1] + (right if op == '+' else -right)
        return None
    if e.startswith('('):
        close = match_close(e, 0)
        cast = e[1:close]
        if cast in ('u8*', 's8*', 'char*', 'unsignedchar*', 'signedchar*', 'void*'):
            return parse_byte_address(e[close + 1:])
    if re.fullmatch(r'[A-Za-z_]\w*', e):
        return e, 0
    return None


def find_raw(line, var):
    """Yield (start, end, ctype, off, spell) for raw derefs through var, and F(var, T, off)."""
    out = []
    for i, ch in enumerate(line):
        if ch != '*':
            continue
        prev = line[:i].rstrip()
        if prev and (prev[-1].isalnum() or prev[-1] in '_)]'):
            continue          # multiplication or a declarator
        got = parse_deref(line, i)
        if not got or got[1] != var:
            continue
        end, _, off = got
        start = i
        # swallow one redundant pair of parentheses around the whole access
        p0 = len(line[:start].rstrip()) - 1
        p1 = skip_ws(line, end)
        if p0 >= 0 and line[p0] == '(' and p1 < len(line) and line[p1] == ')' and match_close(line, p0) == p1:
            before = line[:p0].rstrip()
            if not (before and (before[-1].isalnum() or before[-1] == '_')):   # not a call's parentheses
                start, end = p0, p1 + 1
        out.append((start, end, None, off, 'raw_cast'))
    for m in F_HEAD.finditer(line):
        open_i = m.end() - 1
        close = match_close(line, open_i)
        if close < 0:
            continue
        args = [a.strip() for a in line[open_i + 1:close].split(',')]
        if len(args) == 3 and strip_parens(norm(args[0])) == var:
            try:
                off = int(strip_parens(norm(args[2])), 0)
            except ValueError:
                continue
            out.append((m.start(), close + 1, args[1], off, 'F_macro'))
    # drop nested duplicates (inner matches of an outer access through the same var)
    out.sort()
    kept = []
    for o in out:
        if kept and o[0] < kept[-1][1]:
            continue
        kept.append(o)
    return kept


def func_span(text, name):
    m = re.search(r'^[^\n;]*\b%s\s*\([^;{]*\)\s*\{' % re.escape(name), text, re.M)
    if not m:
        return None
    open_i = text.index('{', m.end() - 1)
    d = 0
    for j in range(open_i, len(text)):
        if text[j] == '{':
            d += 1
        elif text[j] == '}':
            d -= 1
            if d == 0:
                return open_i, j + 1
    return None


def plan_function(text, span, func, sites, fam):
    """Return ([(var, decl_old, decl_new)], {line_no: [(start,end,replacement)]}, refusals)."""
    body = text[span[0]:span[1]]
    body_line0 = text.count('\n', 0, span[0]) + 1
    lines = text.split('\n')
    by_var = collections.defaultdict(list)
    for s in sites:
        by_var[s['base']].append(s)
    plans, refusals = [], []
    for var, vsites in by_var.items():
        if not re.fullmatch(r'[A-Za-z_]\w*', var):
            refusals.append((var, 'base_not_a_variable'))
            continue
        decl = re.search(r'^(\s*)(void|u8)\s*\*\s*%s\s*;' % re.escape(var), body, re.M)
        if not decl:
            head = text[:span[0]]
            head = head[head.rfind(func):]
            other = re.search(r'^\s*([A-Za-z_][\w ]*?\**)\s*\b%s\s*;' % re.escape(var), body, re.M)
            if re.search(r'\b%s\b' % re.escape(var), head):
                refusals.append((var, 'parameter'))
            elif other:
                refusals.append((var, 'typed_local:' + other.group(1).strip()))
            else:
                refusals.append((var, 'not_a_simple_local'))
            continue
        # every raw site through var in this function must be a family site
        edits = collections.defaultdict(list)
        ok = True
        found = 0
        for ln in range(body_line0, body_line0 + body.count('\n') + 1):
            line = lines[ln - 1]
            for start, end, ctype, off, spell in find_raw(line, var):
                found += 1
                site = next((s for s in vsites if s['line'] == ln and s['off'] == off), None)
                if site is None:
                    refusals.append((var, 'non_family_site:%d:+%#x' % (ln, off)))
                    ok = False
                    break
                key = '%#x:%d' % (off, site['width'])
                field = fam['fields'].get(key)
                if field is None:
                    refusals.append((var, 'unmapped_field:%s' % key))
                    ok = False
                    break
                path, fsign = field.split(':')
                rep = '%s->%s' % (var, path)
                if site['rw'] in ('r', 'rw') and site['sign'] in 'su' and site['sign'] != fsign:
                    rep = '*(%s *)&%s' % (CTYPE[(site['sign'], site['width'])], rep)
                if site['rw'] == 'addr':
                    refusals.append((var, 'address_taken:%d' % ln))
                    ok = False
                    break
                edits[ln].append((start, end, access_spelling(rep, line[end:]), site))
            if not ok:
                break
        if not ok:
            continue
        if found == 0:
            refusals.append((var, 'no_rewritable_site'))
            continue
        # other byte-pointer uses of var
        scrub = body
        for ln, es in edits.items():
            for start, end, rep, _ in es:
                pass
        masked = []
        for ln in range(body_line0, body_line0 + body.count('\n') + 1):
            line = lines[ln - 1]
            for start, end, _, _ in sorted(edits.get(ln, []), reverse=True):
                line = line[:start] + 'SITE' + line[end:]
            masked.append(line)
        masked = '\n'.join(masked)
        masked = re.sub(r'^\s*(?:void|u8)\s*\*\s*%s\s*;' % re.escape(var), '', masked, flags=re.M)
        if re.search(r'(?<![\w>.])%s\s*(\+\+|--|\[|[+-](?!>))|(\+\+|--|\*)\s*%s\b|\(\s*(?:u8|s8|char|s16|u16|s32|u32|int|short)\s*\*?\s*\)\s*%s\b' % ((re.escape(var),) * 3), masked):
            refusals.append((var, 'byte_pointer_use'))
            continue
        plans.append((var, decl, edits))
    return plans, refusals


def apply_plans(text, span, plans, fam):
    lines = text.split('\n')
    for var, decl, edits in plans:
        for ln, es in edits.items():
            line = lines[ln - 1]
            for start, end, rep, site in sorted(es, key=lambda e: -e[0]):
                line = line[:start] + rep + line[end:]
            # named constants on whole-statement stores: `V->scale_x = 0x1000;`
            for path, consts in fam.get('constants', {}).items():
                for value, name in consts.items():
                    line = re.sub(r'(%s->%s\s*=\s*)%s\s*;' % (re.escape(var), re.escape(path), re.escape(value)),
                                  r'\g<1>%s;' % name, line)
            lines[ln - 1] = line
    text = '\n'.join(lines)
    body = text[span[0]:]
    for var, decl, edits in plans:
        pat = re.compile(r'^(\s*)(?:void|u8)\s*\*\s*%s\s*;' % re.escape(var), re.M)
        body = pat.sub(r'\g<1>%s *%s;' % (fam['type'], var), body, count=1)
    return text[:span[0]] + body


def ensure_include(text, header):
    inc = '#include "%s"' % header
    if inc in text:
        return text
    m = re.search(r'^#include "[^"]+"\n', text, re.M)
    if not m:
        return inc + '\n' + text
    return text[:m.end()] + inc + '\n' + text[m.end():]


# ----------------------------------------------------------------------------------------- proof

def deps_map(root, cache):
    if cache.exists():
        return json.loads(cache.read_text())
    import layout_compile_identity as L
    from tu_identity import _mm
    physical, _ = L.recipes(root)
    out = {}
    with ProcessPoolExecutor(max_workers=6) as ex:
        for rel, deps in ex.map(_mm, [(str(root), p) for p in sorted(physical)], chunksize=32):
            out[rel] = sorted({os.path.normpath(d) for d in deps})
    cache.write_text(json.dumps(out))
    return out


def tus_for(file, deps):
    return sorted(tu for tu, ds in deps.items() if tu == file or file in ds)


def capture(root, tus, physical):
    import layout_compile_identity as L
    res = {}
    for tu in tus:
        try:
            r = L.capture_one(root, tu, physical[tu])
            res[tu] = (r['raw_sha256'], r['canonical_object_sha256'], r['canonical_assembly_sha256'])
        except Exception as exc:
            res[tu] = ('error', str(exc)[-200:])
    return res


def work(args):
    root, file, funcs, fam, deps_tus, physical = args
    root = Path(root)
    path = root / file
    orig = path.read_text()
    if re.search(r'(?i)relink(?:ed)? (?:of|copy)|r121_nodonor relink|LL4', orig[:1500]) or 'NON_MATCHING' in orig:
        # LL4-marked relink copies follow their home; never edited here
        return {'file': file, 'tus': deps_tus, 'applied': [], 'sites_rewritten': 0,
                'refused': [(f + ':' + v, 'relink_copy') for f, ss in funcs.items() for v in {s['base'] for s in ss}]}
    cached = fam.get('_baseline')
    before = {t: tuple(cached[t]) for t in deps_tus} if cached and all(t in cached for t in deps_tus) else capture(root, deps_tus, physical)
    result = {'file': file, 'tus': deps_tus, 'applied': [], 'refused': [], 'sites_rewritten': 0}
    if any(v[0] == 'error' for v in before.values()):
        result['refused'].append(('*', 'baseline_compile_error'))
        return result
    candidates = []   # (func, var, plan)
    text = orig
    for func, sites in funcs.items():
        span = func_span(text, func)
        if not span:
            result['refused'].extend((v, 'function_not_found') for v in {s['base'] for s in sites})
            continue
        plans, refusals = plan_function(text, span, func, sites, fam)
        result['refused'].extend((func + ':' + v, r) for v, r in refusals)
        candidates.extend((func, p) for p in plans)

    def build(chosen):
        t = orig
        for func, plan in chosen:
            span = func_span(t, func)
            t = apply_plans(t, span, [plan], fam)
        return ensure_include(t, fam['header']) if chosen else t

    def proves(chosen):
        path.write_text(build(chosen))
        after = capture(root, deps_tus, physical)
        return all(after[t] == before[t] for t in deps_tus), after

    keep = []
    if candidates:
        ok, after = proves(candidates)
        if ok:
            keep = candidates
        else:
            failed = []
            for cand in candidates:
                ok1, after1 = proves(keep + [cand])
                if ok1:
                    keep.append(cand)
                else:
                    failed.append((cand, after1))
            # a second pass: a variable may only pass together with an alias kept later
            for cand, after1 in failed:
                ok2, after2 = proves(keep + [cand])
                if ok2:
                    keep.append(cand)
                    continue
                bad = [t for t in deps_tus if after2[t] != before[t]]
                reason = 'object_changed' if all(after2[t][0] != 'error' for t in bad) else 'compile_error'
                result['refused'].append(('%s:%s' % (cand[0], cand[1][0]), reason + ':' + ','.join(bad)))
                result.setdefault('refused_sites', 0)
                result['refused_sites'] += sum(len(v) for v in cand[1][2].values())
    final = build(keep)
    path.write_text(final)
    if keep:
        ok, _ = proves(keep)
        if not ok:      # never leave an unproven edit
            path.write_text(orig)
            result['refused'].append(('*', 'final_recheck_failed'))
            keep = []
    result['applied'] = ['%s:%s' % (f, p[0]) for f, p in keep]
    result['sites_rewritten'] = sum(len(v) for _, p in keep for v in p[2].values())
    result['receipt'] = {t: {'raw_sha256': before[t][0], 'canonical_object_sha256': before[t][1]} for t in deps_tus}
    return result


def fold_work(args):
    """AST fallback for raw/index/accessor and member-view family spellings."""
    from fold_family import plan_file, apply
    root, file, funcs, fam, deps_tus, physical = args
    root = Path(root)
    path = root / file
    orig = path.read_text()
    planned = plan_file(root, file, [s for ss in funcs.values() for s in ss], fam)
    result = {'file': file, 'tus': deps_tus, 'applied': [], 'sites_rewritten': 0,
              'refused': [(p.get('func', '*') + ':' + p['var'], p['reason']) for p in planned['refused']],
              'refusal_details': planned['refused']}
    candidates = planned['plans']
    if not candidates:
        return result
    cached = fam.get('_baseline')
    before = {t: tuple(cached[t]) for t in deps_tus} if cached and all(t in cached for t in deps_tus) else capture(root, deps_tus, physical)
    if not deps_tus or any(v[0] == 'error' for v in before.values()):
        result['refused'].append(('*', 'baseline_compile_error_or_no_recipe'))
        return result

    def proves(chosen):
        path.write_text(apply(orig, chosen, fam['header']))
        after = capture(root, deps_tus, physical)
        return after == before, after

    keep = []
    try:
        ok, after = proves(candidates)
        if ok:
            keep = candidates
        else:
            failed = []
            for cand in candidates:
                ok, after = proves(keep + [cand])
                if ok:
                    keep.append(cand)
                else:
                    failed.append(cand)
            for cand in failed:
                ok, after = proves(keep + [cand])
                if ok:
                    keep.append(cand)
                else:
                    bad = [t for t in deps_tus if after[t] != before[t]]
                    reason = 'object_changed' if all(after[t][0] != 'error' for t in bad) else 'compile_error'
                    result['refused'].append((cand['func'] + ':' + cand['var'], reason + ':' + ','.join(bad)))
                    result['refusal_details'].append({'func': cand['func'], 'var': cand['var'],
                        'reason': reason, 'sites': sum(cand['sites'].values()), 'tus': bad})
        # A successful whole-file attempt already is the final proof. A split
        # attempt must restore and recheck its retained variable subset.
        if keep != candidates:
            ok, after = proves(keep)
        if not ok:
            raise RuntimeError('final identity recheck failed: ' + file)
    except BaseException:
        path.write_text(orig)
        raise
    result['applied'] = [p['func'] + ':' + p['var'] for p in keep]
    result['sites_by_stage'] = dict(sum((collections.Counter(p['sites']) for p in keep), collections.Counter()))
    result['sites_rewritten'] = sum(result['sites_by_stage'].values())
    result['locals_retyped'] = sum(p['local_typed'] for p in keep)
    result['cast_parameters'] = [p['func'] + ':' + p['var'] for p in keep if p['parameter']]
    result['receipt'] = {t: {'raw_sha256': before[t][0], 'canonical_object_sha256': before[t][1],
                            'canonical_assembly_sha256': before[t][2]} for t in deps_tus}
    return result


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parent.parent)
    ap.add_argument('--sites', type=Path, required=True)
    ap.add_argument('--family', type=Path, required=True)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--deps-cache', type=Path, required=True)
    ap.add_argument('--workers', type=int, default=6)
    ap.add_argument('--only', nargs='*')
    ap.add_argument('--skip', nargs='*', default=[])
    ap.add_argument('--queue-file', type=Path, help='newline-delimited owned C paths')
    ap.add_argument('--all-spellings', action='store_true', help='AST fallback, including member views and accessor/index sites')
    ap.add_argument('--baseline-receipt', type=Path, help='immutable earlier complete-TU snapshot; avoids duplicate baseline builds')
    args = ap.parse_args(argv)
    root = args.root.resolve()
    fam = json.loads(args.family.read_text())
    if args.baseline_receipt:
        records = [json.loads(l) for l in args.baseline_receipt.read_text().splitlines()]
        fam['_baseline'] = {r['source']: [r['raw_sha256'], r['canonical_object_sha256'], r['canonical_assembly_sha256']] for r in records if 'error' not in r}
    by_file = collections.defaultdict(lambda: collections.defaultdict(list))
    with gzip.open(args.sites, 'rt') as fh:
        for line in fh:
            s = json.loads(line)
            if s.get('label') in fam['labels'] and (args.all_spellings or s['spell'] in ('raw_cast', 'F_macro', 'raw_index')):
                by_file[os.path.normpath(s['file'])][s['func']].append(s)
    import layout_compile_identity as L
    physical, _ = L.recipes(root)
    deps = deps_map(root, args.deps_cache)
    jobs = []
    held = []
    owned = {os.path.normpath(p) for p in args.queue_file.read_text().splitlines()} if args.queue_file else None
    for file, funcs in sorted(by_file.items(), key=lambda kv: -sum(len(ss) for ss in kv[1].values())):
        if args.only and file not in args.only or file in args.skip:
            continue
        if owned is not None and file not in owned:
            continue
        tus = tus_for(file, deps)
        if not tus:
            held.append({'file': file, 'tus': [], 'applied': [], 'sites_rewritten': 0,
                         'refused': [('*', 'no_physical_recipe')]})
            continue
        if any(physical[t]['container'] == 'slus' for t in tus):
            held.append({'file': file, 'tus': tus, 'applied': [], 'sites_rewritten': 0,
                         'refused': [('*', 'slus_full_image_proof_required')]})
            continue
        job_family = dict(fam)
        if '_baseline' in fam:
            job_family['_baseline'] = {t: fam['_baseline'][t] for t in tus if t in fam['_baseline']}
        jobs.append((str(root), file, dict(funcs), job_family, tus, {t: physical[t] for t in tus}))
    # files sharing any physical TU must not be edited concurrently: connected components over TUs
    parent = list(range(len(jobs)))

    def find(i):
        while parent[i] != i:
            parent[i] = parent[parent[i]]
            i = parent[i]
        return i
    owner = {}
    for i, j in enumerate(jobs):
        for tu in j[4]:
            if tu in owner:
                parent[find(i)] = find(owner[tu])
            else:
                owner[tu] = i
    groups = collections.defaultdict(list)
    for i, j in enumerate(jobs):
        groups[find(i)].append(j)
    results = list(held)
    with args.out.open('w') as fh:
        for r in held:
            fh.write(json.dumps(r, sort_keys=True) + '\n')
        with ProcessPoolExecutor(max_workers=args.workers) as ex:
            for res in ex.map(_run_group, [(list(g), args.all_spellings) for g in groups.values()]):
                results.extend(res)
                for r in res:
                    fh.write(json.dumps(r, sort_keys=True) + '\n')
                fh.flush()
                print(json.dumps({'files_done': len(results), 'sites_rewritten': sum(r['sites_rewritten'] for r in results)}), flush=True)
    total = sum(sum(len(v) for v in by_file[r['file']].values()) for r in results)
    print(json.dumps({'files': len(results), 'family_raw_sites': total,
                      'sites_rewritten': sum(r['sites_rewritten'] for r in results),
                      'vars_applied': sum(len(r['applied']) for r in results),
                      'refusals': collections.Counter(x[1].split(':')[0] for r in results for x in r['refused'])}, default=str))


def _run_group(g):
    jobs, all_spellings = g
    return [(fold_work if all_spellings else work)(j) for j in jobs]


if __name__ == '__main__':
    main()
