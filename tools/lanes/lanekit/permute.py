#!/usr/bin/env python3
"""Bounded statement-order sweeps through Lab's screen, scorer and staging.

Examples (run from a lane):
  permute.py ROW --base erased.c --plan movable.json --limit 1000 --workers 4
  permute.py ROW --base erased.c --auto --compound --limit 2000

Plan: {"groups": [{"lines": [[10,10],[11,12],[13,13]],
                    "depends": [[0,2]]}], "subs": [["old","new"]]}.
Instead of lines, use "statements": ["x = 1;", "y = 2;"]. Lines are 1-based,
inclusive, after substitutions/compound rewrites. Items must be adjacent whole
statements in one block. Dependencies augment inferred RAW, WAR and WAW edges.
Declarations, calls, unknown side effects and control flow are fixed barriers.
The parser handles a conservative C subset; this is not a general C optimizer.
"""
from __future__ import annotations

import argparse
import hashlib
import itertools
import json
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kitlib
import lab


def code_mask(text):
    """Preserve offsets/newlines while hiding comments, strings and directives."""
    rx = r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|^[ \t]*#[^\n]*(?:\\\n[^\n]*)*'
    return re.sub(rx, lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), text, flags=re.S | re.M)


def gap_safe(text):
    return not code_mask(text).strip() and not re.search(r'^\s*#', text, flags=re.M)


@dataclass(frozen=True)
class Statement:
    start: int
    end: int
    block: int
    text: str


def parse_statements(text):
    """Semicolon statements grouped by physical brace block (for headers stay fixed)."""
    masked = code_mask(text)
    stack = []
    statements = []
    paren = bracket = serial = 0
    for i, c in enumerate(masked):
        if c == '(':
            paren += 1
        elif c == ')':
            paren -= 1
        elif c == '[':
            bracket += 1
        elif c == ']':
            bracket -= 1
        elif c == '{' and paren == bracket == 0:
            serial += 1
            stack.append([serial, i + 1])
        elif c == '}' and paren == bracket == 0:
            if not stack:
                raise ValueError('unbalanced braces')
            stack.pop()
            if stack:
                stack[-1][1] = i + 1
        elif c == ';' and paren == bracket == 0 and stack:
            block, start = stack[-1]
            # Keep comments attached to their statement, but trim whitespace.
            while start < i and text[start].isspace():
                start += 1
            statements.append(Statement(start, i + 1, block, text[start:i + 1]))
            stack[-1][1] = i + 1
    if stack or paren or bracket:
        raise ValueError('unbalanced C delimiters')
    return statements


IDENT = re.compile(r'\b[A-Za-z_]\w*\b')
ASSIGN = re.compile(r'(?<![=!<>])([+\-*/%&|^]?=)(?!=)')
FIELD = re.compile(r'(?:->|\.)\s*([A-Za-z_]\w*)')


def reads(expr):
    fields = set(FIELD.findall(expr))
    ids = set(IDENT.findall(expr)) - fields - {'sizeof'}
    return ids | {'@field:' + f for f in fields}


def effects(statement):
    """(reads, writes), or None for a fixed/ambiguous statement.

    Field identity conservatively aliases the same field on different bases.
    Unknown pointer dereferences and arrays stay fixed. Different fields can
    move; union/overlap knowledge must be expressed with declared dependencies.
    """
    if re.search(r'^\s*#', statement, flags=re.M):
        return None
    t = code_mask(statement).strip()
    if not t.endswith(';') or re.search(r'\b(?:if|else|for|while|do|switch|case|return|goto|break|continue|asm|__asm__|volatile)\b|[{}?:]', t):
        return None
    if re.search(r'\b[A-Za-z_]\w*\s*\(', t) or '++' in t or '--' in t or ',' in t:
        return None
    matches = list(ASSIGN.finditer(t))
    if len(matches) != 1:
        return None
    m = matches[0]; lhs, rhs = t[:m.start()].strip(), t[m.end():-1]
    if not lhs or '[' in lhs or '[' in rhs:
        return None
    fields = FIELD.findall(lhs)
    if fields:
        # Casted struct-member lvalues are common in decompiler text.
        if not re.search(r'(?:->|\.)\s*\w+\s*$', lhs):
            return None
        writes_set = {'@field:' + fields[-1]}
        read_set = reads(lhs) - writes_set
    elif re.fullmatch(r'[A-Za-z_]\w*', lhs):
        writes_set = {lhs}; read_set = set()
    else:
        return None  # declaration, raw dereference or unsupported lvalue
    # A raw dereference in the RHS may alias any field. Multiplication is also
    # held conservatively, rather than guessing from token spelling.
    if '*' in rhs or ASSIGN.search(rhs):
        return None
    read_set |= reads(rhs)
    if m[1] != '=':
        read_set |= writes_set
    return read_set, writes_set


def dependency_edges(items, declared=()):
    ef = [effects(s.text) for s in items]
    edges = set()
    for i, a in enumerate(ef):
        for j in range(i + 1, len(ef)):
            b = ef[j]
            if a is None or b is None or a[1] & (b[0] | b[1]) or a[0] & b[1]:
                edges.add((i, j))
    for pair in declared:
        if len(pair) != 2 or any(type(k) is not int or not 0 <= k < len(items) for k in pair) or pair[0] == pair[1]:
            raise ValueError('invalid declared dependency')
        edges.add(tuple(pair))
    # Verify acyclicity without enumerating the permutation space.
    remaining = set(range(len(items)))
    while remaining:
        ready = {i for i in remaining if not any(b == i and a in remaining for a, b in edges)}
        if not ready:
            raise ValueError('cyclic dependencies')
        remaining -= ready
    return edges


def orders(n, edges):
    """Lazy topological permutations, original order first where admissible."""
    def visit(prefix, remaining):
        if not remaining:
            yield tuple(prefix)
        for i in sorted(remaining):
            if not any(b == i and a in remaining for a, b in edges):
                yield from visit(prefix + [i], remaining - {i})
    yield from visit([], set(range(n)))


def compound_rewrite(text):
    """Simple self-RMW and single-use split load/store pairs, without new uses.

    The split form t = p->f; ... p->f = t | K becomes p->f |= K at
    the original store. Calls/control flow, another t use or a p/f write block
    the rewrite. Declaration cleanup handles only one-variable declarations.
    """
    stmts = parse_statements(text); edits = []; temps = set(); consumed = set()
    simple_lv = r'[A-Za-z_]\w*(?:\s*->\s*[A-Za-z_]\w*)?'
    for i, s in enumerate(stmts):
        masked = code_mask(s.text).strip()
        direct = re.fullmatch(r'(' + simple_lv + r')\s*=\s*(' + simple_lv + r')\s*([|&^+\-])\s*([^;]+);', masked)
        if direct and re.sub(r'\s', '', direct[1]) == re.sub(r'\s', '', direct[2]):
            if effects(s.text) is not None:
                edits.append((s.start, s.end, direct[1] + ' ' + direct[3] + '= ' + direct[4] + ';'))
            continue
        load = re.fullmatch(r'([A-Za-z_]\w*)\s*=\s*(' + simple_lv + r');', masked)
        if not load or '->' not in load[2] or effects(s.text) is None:
            continue
        temp, lv = load[1], load[2]; key = re.sub(r'\s', '', lv)
        # A narrower/differently signed temporary can change the value. Only
        # rewrite a known identical scalar field/temporary type, no guessing.
        field = re.search(r'->\s*(\w+)\s*$', lv)[1]
        def decl(name, source):
            return re.findall(r'\b((?:u|s)(?:8|16|32|64)|(?:unsigned\s+|signed\s+)?(?:char|short|int|long))\s+' + re.escape(name) + r'\s*;', code_mask(source))
        temp_types, field_types = decl(temp, text), decl(field, text)
        base = re.match(r'\s*(\w+)\s*->', lv)[1]
        pointer_types = set(re.findall(r'\b([A-Za-z_]\w*)\s*\*\s*' + re.escape(base) + r'\s*;', code_mask(text)))
        if len(pointer_types) == 1:
            typename = next(iter(pointer_types))
            definitions = re.findall(r'\btypedef\s+struct(?:\s+\w+)?\s*\{([^{}]*)\}\s*' + re.escape(typename) + r'\s*;', code_mask(text))
            if len(definitions) == 1:
                field_types = decl(field, definitions[0])
        if len(temp_types) != 1 or not field_types or set(field_types) != set(temp_types):
            continue
        for j in range(i + 1, len(stmts)):
            dst = stmts[j]
            # The physical substring must contain only these same-block statements.
            between = text[s.end:dst.start]
            if dst.block != s.block or '{' in code_mask(between) or '}' in code_mask(between) or re.search(r'^\s*#', between, flags=re.M):
                break
            store = re.fullmatch(r'(' + simple_lv + r')\s*=\s*' + re.escape(temp) + r'\s*([|&^+\-])\s*([^;]+);', code_mask(dst.text).strip())
            if store and re.sub(r'\s', '', store[1]) == key and effects(dst.text) is not None:
                # Exactly declaration + load + store occurrences: no surviving use.
                if len(re.findall(r'\b' + re.escape(temp) + r'\b', code_mask(text))) == 3 and i not in consumed and j not in consumed:
                    edits += [(s.start, s.end, ''), (dst.start, dst.end, lv + ' ' + store[2] + '= ' + store[3] + ';')]
                    temps.add(temp); consumed.update((i, j))
                break
            ef = effects(dst.text)
            if ef is None or temp in ef[0] | ef[1] or reads(lv) & ef[1]:
                break
    for start, end, new in sorted(edits, reverse=True):
        text = text[:start] + new + text[end:]
    for temp in temps:
        text = re.sub(r'^[ \t]*(?:unsigned\s+|signed\s+)?[A-Za-z_]\w*\s+' + re.escape(temp) + r'\s*;[ \t]*\n', '', text, flags=re.M)
    return text


def select_groups(text, specs=None):
    statements = parse_statements(text)
    if specs is None:
        runs = []; run = []
        for s in statements:
            adjacent = run and s.block == run[-1].block and gap_safe(text[run[-1].end:s.start])
            if effects(s.text) is None or not adjacent:
                if len(run) > 1:
                    runs.append((run, []))
                run = []
            if effects(s.text) is not None:
                run.append(s)
        if len(run) > 1:
            runs.append((run, []))
        # Large automatic runs are split into bounded adjacent windows.
        return [(items[i:i + 8], dep) for items, dep in runs for i in range(0, len(items), 8) if len(items[i:i + 8]) > 1]
    groups = []; used = set()
    for spec in specs:
        items = []
        if ('lines' in spec) == ('statements' in spec):
            raise ValueError('each group needs lines OR statements')
        if 'lines' in spec:
            lines = text.splitlines(keepends=True); starts = [0]
            for line in lines:
                starts.append(starts[-1] + len(line))
            for lo, hi in spec['lines']:
                if not 1 <= lo <= hi <= len(lines):
                    raise ValueError('line range outside source')
                found = [s for s in statements if starts[lo - 1] <= s.start and s.end <= starts[hi]]
                if len(found) != 1 or code_mask(text[starts[lo - 1]:found[0].start] + text[found[0].end:starts[hi]]).strip():
                    raise ValueError('range must contain exactly one whole statement')
                items.append(found[0])
        else:
            for literal in spec['statements']:
                hits = [s for s in statements if code_mask(s.text).strip() == code_mask(literal).strip()]
                if len(hits) != 1:
                    raise ValueError('statement missing or ambiguous: ' + literal)
                items.append(hits[0])
        if len(items) < 2 or items != sorted(items, key=lambda s: s.start):
            raise ValueError('group needs at least two statements in source order')
        if any(re.search(r'^\s*#', s.text, flags=re.M) for s in items):
            raise ValueError('preprocessor boundaries cannot move')
        for a, b in zip(items, items[1:]):
            if a.block != b.block or not gap_safe(text[a.end:b.start]):
                raise ValueError('movable statements must be adjacent in one block')
        if used & {s.start for s in items}:
            raise ValueError('overlapping groups')
        used |= {s.start for s in items}
        groups.append((items, spec.get('depends', [])))
    return groups


def variants(text, groups, limit):
    """Bounded lazy Cartesian traversal, without materialising factorial lists."""
    def walk(i, edits, signatures):
        if i == len(groups):
            out = text
            for start, end, new in sorted(edits, reverse=True):
                out = out[:start] + new + out[end:]
            yield out, signatures
            return
        items, dep = groups[i]; edges = dependency_edges(items, dep)
        # Leave each slot's original inter-statement whitespace intact.
        gaps = [text[a.end:b.start] for a, b in zip(items, items[1:])]
        for order in orders(len(items), edges):
            new = ''.join(items[k].text + (gaps[j] if j < len(gaps) else '') for j, k in enumerate(order))
            yield from walk(i + 1, edits + [(items[0].start, items[-1].end, new)], signatures + [list(order)])
    yield from itertools.islice(walk(0, [], []), limit)


def cleanliness(text):
    return (len(kitlib.sites(text)), kitlib.goto_count(text), text.count('volatile'),
            kitlib.m2c_count(text), len(parse_statements(text)), len(text))


def bounded_map(pool, fn, source, width):
    """Keep at most width jobs queued; yield in generation order for repeatability."""
    pending = []
    for item in source:
        pending.append(pool.submit(fn, item))
        if len(pending) >= width:
            yield pending.pop(0).result()
    for future in pending:
        yield future.result()


def run(a):
    lane = kitlib.bootstrap()
    # All descendants inherit nice/ionice, including screen's compiler children.
    try:
        os.nice(10)
    except OSError:
        pass
    subprocess.run(['ionice', '-c2', '-n7', '-p', str(os.getpid())], check=True, capture_output=True)
    harness = lab.Lab(a.row, stage=False, more=True)
    harness.raw_only = True
    control = harness.baseline(score=True)
    if not control['score']['exact']:
        raise ValueError('permutation calibration failed')
    text = Path(a.base).read_text() if a.base else harness.erased
    plan = json.loads(Path(a.plan).read_text()) if a.plan else {}
    text = kitlib.apply_subs(text, plan.get('subs', []), label='permutation preparation')
    if a.compound:
        text = compound_rewrite(text)
    groups = select_groups(text, None if a.auto else plan.get('groups', []))
    if not groups:
        raise ValueError('no movable groups; provide --plan or --auto')
    out = Path(a.out).resolve() if a.out else harness.dir / ('permute_' + hashlib.sha256(text.encode()).hexdigest()[:12])
    if not out.is_relative_to(lane):
        raise ValueError('--out must be lane-owned')
    out.mkdir(parents=True, exist_ok=False)
    (out / '.ignore').write_text('*\n')
    (out / 'prepared.c').write_text(text)
    records = []; seen = set()
    def candidates():
        for index, (cand, order) in enumerate(variants(text, groups, a.limit)):
            sha = hashlib.sha256(cand.encode()).hexdigest()
            if sha in seen:
                continue
            seen.add(sha)
            yield index, cand, order, sha
    def measure(item):
        index, cand, order, sha = item
        name = 'perm_' + out.name + '_' + str(index)
        path = out / (str(index) + '.c'); path.write_text(cand)
        # Pure parallel screen; only the coordinator writes the lab journal/stages.
        bad = harness.guards(cand)
        rec = dict(variant=name, path=str(path), order=order, sha256=sha, pins=len(kitlib.sites(cand)),
                   clean=list(cleanliness(cand)), score=None, note='permute.py', status='measured')
        try:
            rec['distance'] = None if bad else harness.screen.distance(cand)
            if bad:
                rec.update(status='refused', why='; '.join(bad))
            elif rec['distance'] is None:
                rec.update(status='no-build', stderr=lab.compile_stderr(harness.row, cand)[0])
        except Exception as e:
            rec.update(distance=None, status='screen-failed', why=str(e))
        return rec
    with ThreadPoolExecutor(max_workers=a.workers) as pool:
        for rec in bounded_map(pool, measure, candidates(), 2 * a.workers):
            harness.log(dict(rec, kind='permutation-screen'))
            records.append(rec)
            if len(records) % 100 == 0:
                print(f'screened {len(records)}/{a.limit}', flush=True)
        ranked = sorted([r for r in records if r['distance'] is not None],
                        key=lambda r: (r['distance'], r['clean'], r['variant']))
        score_set = [r for r in ranked if r['distance'] <= a.score_near]
        score_set += [r for r in ranked[:a.score_top] if r not in score_set]
        def score_one(rec):
            cand = Path(rec['path']).read_text()
            try:
                sc = kitlib.score_fields(harness.score_text(cand))
                return rec, sc
            except Exception as e:
                return rec, {'exact': False, 'status': 'score-failed', 'err': str(e)}
        for rec, sc in bounded_map(pool, score_one, score_set, 2 * a.workers):
            rec['score'] = sc; rec['status'] = 'exact' if sc.get('exact') else sc.get('status') or 'scored'
            harness.log(dict(rec, kind='permutation-score'))
    exact = sorted([r for r in records if (r['score'] or {}).get('exact')],
                   key=lambda r: (r['clean'], r['variant']))
    staged = None
    if not a.no_stage:
        for rec in exact:
            cand = Path(rec['path']).read_text()
            if not kitlib.admissible(harness.base, cand):
                # Re-score the chosen text immediately before existing staging.
                final = harness.score_text(cand)
                if final.get('exact'):
                    staged = harness.publish(rec['variant'], cand)
                    harness.log(dict(rec, kind='permutation-stage', staged=staged))
                break
    result = {'row': harness.id, 'limit': a.limit, 'workers': a.workers,
              'generated': len(records), 'scored': len(score_set), 'exact': len(exact),
              'staged': staged, 'calibration': control, 'ranking': sorted(records,
              key=lambda r: (not (r['score'] or {}).get('exact', False), r['distance'] is None,
                             r['distance'] or 0, r['clean'], r['variant']))}
    (out / 'results.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps({k: v for k, v in result.items() if k not in ('ranking', 'calibration')}, indent=2))
    return result


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('row'); ap.add_argument('--base'); ap.add_argument('--plan')
    ap.add_argument('--auto', action='store_true'); ap.add_argument('--compound', action='store_true')
    ap.add_argument('--limit', type=int, default=1000); ap.add_argument('--workers', type=int, default=4)
    ap.add_argument('--score-near', type=int, default=0); ap.add_argument('--score-top', type=int, default=3)
    ap.add_argument('--out'); ap.add_argument('--no-stage', action='store_true')
    a = ap.parse_args(argv)
    if not 1 <= a.limit <= 10000 or not 1 <= a.workers <= 8 or a.score_top < 0 or a.score_near < 0:
        ap.error('limit 1..10000, workers 1..8 and nonnegative scorer bounds required')
    if a.auto == bool(a.plan):
        ap.error('choose --auto OR --plan')
    try:
        run(a)
    except (OSError, ValueError, RuntimeError) as e:
        ap.exit(1, str(e) + '\n')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
