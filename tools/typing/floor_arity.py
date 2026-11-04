#!/usr/bin/env python3
"""Arity prototype floors: per-call binary evidence and the cheapest unifying route.

    floor_arity.py --floors DIR/floors.tsv --out DIR [--root R] [--abi-cache build/abi_facts.json.gz]

Input is tools/typing/floor_triage.py output (rows with blocker `arity`).  For every floor name the tool
lists each direct C call (file, caller, argument count, line) and joins it to the call sites that
tools/typing/abi_facts.py decoded from the byte-exact objects (caller symbol through config/names.tsv).
Per argument position the decoded reaching definition decides what the caller's bytes really do:

  set       the register (or outgoing stack slot) is written in the call's own block: the argument is
            in the bytes (conservative: the block may write it for another purpose)
  stale     left over from an earlier call or computed in an earlier block: not set up for this call
  entry     the caller's own incoming argument at that position, unchanged

Each call admits an interval of byte-compatible arities, but an interval alone does not establish
source intent.  The output classifies each position as explicit setup, entry forwarding, stale,
none, or unknown.  Entry forwarding without a callback contract is held.  Aggregate
`abi.args_set_up` counts from the floor ledger are reported as leads, never substituted for a
call-site proof.  Routes (column `route`):

  extend_definition   added positions are explicitly set at every call, with consistent callers or a
                      callback contract; still requires a byte proof
  drop_phantom_args   every dropped position is stale or none at every decoded site; requires byte proof
  extend_and_drop     both conditions hold for the added and dropped positions
  add_passthrough_args  entry forwarding has a documented callback contract; requires byte proof
  hold_entry_forwarding  entry provenance lacks a callback contract
  hold_unproven_arity   missing, mixed, or otherwise insufficient position evidence
  trim_definition     only a smaller arity is feasible: unread trailing parameters leave the definition
  declarations_only   every call already agrees; only declaration spellings disagree in arity
  no_direct_calls     no direct C call (address-taken / dispatcher family): one callback typedef route
  mixed_real_arity    no single arity keeps every caller's bytes: callers really pass different counts
                      (original K&R / unprototyped calls).  Owner decision: an unprototyped `T f();`
                      declaration in the owner header, or the counted floor stays
  unmatched           some call has no decoded site (copies, partitions): needs a probe before routing

Prediction only: every route is proven by compiling (tools/lanes/prove_batch.sh) before it is kept.
Outputs: DIR/floor_arity.tsv (one row per name), DIR/floor_calls.tsv (one row per call), DIR/summary.json.
"""
from __future__ import annotations

import argparse
import collections
import csv
import json
from pathlib import Path
import re
import sys

HERE = Path(__file__).resolve()
TOOLS = HERE.parents[1]
for p in (str(HERE.parent), str(TOOLS), str(TOOLS / 'headers'), str(TOOLS / 'readability')):
    if p not in sys.path:
        sys.path.insert(0, p)

ARG_REGS = ('a0', 'a1', 'a2', 'a3')
NOT_SET = ('stale', 'none')
DECL_PREV = ('extern', 'void', 's32', 'u32', 's16', 'u16', 's8', 'u8', 'int', 'char', 'short', 'long')
NAME_FIELDS = ['name', 'route', 'def_path', 'def_arity', 'callee_reads', 'body_uses', 'ledger_args_set_up', 'feasible', 'target_arity',
               'calls', 'call_arities', 'drop_calls', 'add_calls', 'extend_by', 'mixed_reason', 'unmatched_calls',
               'decl_arities', 'def_proto']
CALL_FIELDS = ['name', 'file', 'line', 'caller', 'nargs', 'sites', 'positions', 'evidence_classes',
               'callback_contract', 'lo', 'hi', 'passthrough', 'args']


def lexical_calls(root, files, name, cache):
    """[(file, line, caller, nargs, argtext)] for direct calls to `name` inside function bodies."""
    import score as S
    out = []
    for rel in files:
        if not rel.endswith('.c'):
            continue
        if rel not in cache:
            text = (root / rel).read_text(errors='replace')
            tokens = S.lex(text)
            pairs, _ = S.pairs_of(tokens)
            defs = [(b, e, tokens[n].value) for a, n, b, e, s in S.definitions(tokens, pairs)]
            cache[rel] = (text, tokens, pairs, defs)
        text, tokens, pairs, defs = cache[rel]
        for i, t in enumerate(tokens[:-1]):
            if t.value != name or tokens[i + 1].value != '(' or (i + 1) not in pairs:
                continue
            if i and tokens[i - 1].value in ('.', '->'):
                continue
            caller = next((fn for b, e, fn in defs if b < i < e), None)
            if caller is None:
                continue
            prev = tokens[i - 1].value if i else ''
            if prev in DECL_PREV or (prev == '*' and i > 2 and tokens[i - 2].kind == 'id'
                                     and tokens[i - 2].value != 'return'
                                     and tokens[i - 3].value in (';', '{', '}', 'extern')):
                continue
            close = pairs[i + 1]
            args, depth, start = [], 0, i + 2
            for j in range(i + 2, close):
                v = tokens[j].value
                if v in '([{':
                    depth += 1
                elif v in ')]}':
                    depth -= 1
                elif v == ',' and depth == 0:
                    args.append((start, j))
                    start = j + 1
            if close > i + 2:
                args.append((start, close))
            argtext = [' '.join(text[tokens[a].pos:tokens[b - 1].pos + len(tokens[b - 1].value)].split())
                       for a, b in args]
            out.append((rel, text.count('\n', 0, t.pos) + 1, caller, len(args), argtext))
    return out


def definition_use(root, rel, name, cache):
    """(param names, highest used index + 1) for the C definition of `name` in `rel` (lexical)."""
    import score as S
    if rel not in cache:
        text = (root / rel).read_text(errors='replace')
        tokens = S.lex(text)
        pairs, _ = S.pairs_of(tokens)
        defs = [(b, e, tokens[n].value) for a, n, b, e, s in S.definitions(tokens, pairs)]
        cache[rel] = (text, tokens, pairs, defs)
    text, tokens, pairs, defs = cache[rel]
    for a, n, b, e, style in S.definitions(tokens, pairs):
        if tokens[n].value != name or tokens[n + 1].value != '(':
            continue
        close = pairs[n + 1]
        groups, cur, depth = [], [], 0
        for j in range(n + 2, close):
            v = tokens[j].value
            if v in '([':
                depth += 1
            elif v in ')]':
                depth -= 1
            if v == ',' and depth == 0:
                groups.append(cur)
                cur = []
            else:
                cur.append(tokens[j])
        if cur:
            groups.append(cur)
        names = []
        for g in groups:
            ids = [t.value for t in g if t.kind == 'id']
            names.append(ids[-1] if ids and [t.value for t in g] != ['void'] else None)
        names = [x for x in names if x is not None and x != 'void']
        body = {tokens[j].value for j in range(b, e) if tokens[j].kind == 'id'}
        used = max([k + 1 for k, x in enumerate(names) if x in body] + [0])
        return names, used
    return [], 0


def position_kind(site, k):
    """'set' / 'stale' / 'entry' / 'none' for argument position k at one decoded call site."""
    if k < 4:
        reg = ARG_REGS[k]
        kind = site.get('args', {}).get(reg, 'none')
        if kind in NOT_SET:
            return kind
        # A value computed in an earlier block has unknown provenance here; absence of a write in
        # this block alone does not prove that the source argument was phantom.
        if reg in (site.get('set_in_block') or ()):
            return 'set'
        return 'entry' if kind == 'entry' else 'unknown'
    return 'set' if (k - 4) in (site.get('stack_args') or ()) else 'none'


def call_interval(nargs, sites):
    """(lo, hi, positions) the arities that keep this call's bytes, over every decoded site of it."""
    width = max([nargs, 4] + [4 + max(s.get('stack_args') or [-1]) + 1 for s in sites])
    kinds = [sorted({position_kind(s, k) for s in sites}) for k in range(width)]
    # only positions the C passes are attributable to this call: the C is byte-exact, so a register written
    # beyond its arguments belongs to other code of the caller (a temporary), not to a missing argument
    lo = 0
    for k, ks in enumerate(kinds[:nargs]):
        if 'set' in ks:
            lo = k + 1
    # an argument the C passes is never dropped below its own set-up position; beyond the C arguments only
    # registers that hold the caller's own incoming value may be added (pass-through compiles to nothing)
    hi = nargs
    while hi < 4 and kinds[hi] == ['entry']:
        hi += 1
    return lo, hi, ['/'.join(ks) for ks in kinds[:max(nargs, lo, hi)]]


def position_evidence(call, k):
    """Classify one position without turning byte compatibility into source intent."""
    raw = call.get('positions', '')
    parts = raw.split(',') if isinstance(raw, str) else raw
    if k >= len(parts) or not parts[k]:
        return 'unknown'
    kinds = set(parts[k].split('/'))
    if kinds == {'set'}:
        return 'explicit_setup'
    if kinds == {'entry'}:
        return 'callback_contract' if call.get('callback_contract') else 'entry_forwarding'
    if kinds == {'stale'}:
        return 'stale'
    if kinds == {'none'}:
        return 'none'
    return 'unknown'


def drop_supported(calls, target):
    return all(position_evidence(c, k) in {'stale', 'none'}
               for c in calls for k in range(target, c['nargs']))


def extension_supported(calls, old, target):
    if not all(c['nargs'] >= target and all(position_evidence(c, k) == 'explicit_setup'
                                             for k in range(old, target)) for c in calls):
        return False
    return len({c['nargs'] for c in calls}) == 1 or all(c.get('callback_contract') for c in calls)


def evidence_hold(calls, target):
    if any(position_evidence(c, k) == 'entry_forwarding'
           for c in calls for k in range(min(c['nargs'], target), max(c['nargs'], target))):
        return 'hold_entry_forwarding', 'entry-forwarded argument has no callback contract'
    return 'hold_unproven_arity', 'position evidence does not support the proposed arity'


def route(name, darity, reads, calls, decl_arities, used=0):
    """(route, feasible, target, reason) from per-call intervals and the callee's read arity."""
    if darity is None:
        return 'unmatched', '', '', 'no C definition arity'
    if not calls:
        return 'no_direct_calls', '', '', ''
    if any(c['sites'] == 0 for c in calls):
        return 'unmatched', '', '', '%d calls without decoded sites' % sum(c['sites'] == 0 for c in calls)
    # a byte-exact definition with `darity` parameters cannot read a register beyond them: a larger decoded
    # read count is decoder over-approximation (an argument register live across a call, a delay slot)
    reads = min(reads, darity)
    # a parameter the body names may be forwarded unchanged (an `entry` pass-through no instruction reads):
    # the decoded read count misses it, the C body does not
    reads = max(reads, used)
    nargs = {c['nargs'] for c in calls}
    if len(nargs) == 1:
        m = next(iter(nargs))
        if m == darity:
            return 'declarations_only', '%d..%d' % (m, m), darity, ''
        if m > darity:
            if extension_supported(calls, darity, m):
                return 'extend_definition', '%d..%d' % (m, m), m, ''
            hold, why = evidence_hold(calls, darity)
            return hold, '%d..%d' % (m, m), '', why
        if reads <= m:
            return 'trim_definition', '%d..%d' % (m, m), m, ''
        return 'mixed_real_arity', '', '', 'callee reads %d args, every call passes %d' % (reads, m)
    lo = max([reads] + [c['lo'] for c in calls])
    hi = min(c['hi'] for c in calls)
    if lo > hi:
        worst = min(calls, key=lambda c: (c['hi'], -c['lo']))
        need = max(calls, key=lambda c: c['lo'])
        why = 'call %s:%d keeps <= %d args, call %s:%d needs >= %d' % (
            worst['file'].rsplit('/', 1)[-1], worst['line'], worst['hi'],
            need['file'].rsplit('/', 1)[-1], need['line'], lo)
        if reads > hi:
            why = 'callee reads %d args, a call keeps <= %d' % (reads, hi)
        return 'mixed_real_arity', '', '', why
    feasible = '%d..%d' % (lo, hi)
    if lo <= darity <= hi:
        if all(c['nargs'] >= darity for c in calls) and drop_supported(calls, darity):
            return 'drop_phantom_args', feasible, darity, ''
        if (all(c['nargs'] <= darity and c.get('callback_contract') for c in calls)
                and all(position_evidence(c, k) == 'callback_contract'
                        for c in calls for k in range(c['nargs'], darity))):
            return 'add_passthrough_args', feasible, darity, ''
        hold, why = evidence_hold(calls, darity)
        return hold, feasible, '', why
    for target in range(max(lo, darity + 1), hi + 1):
        if extension_supported(calls, darity, target) and drop_supported(calls, target):
            return 'extend_and_drop', feasible, target, ''
    hold, why = evidence_hold(calls, min(hi, darity))
    return hold, feasible, '', why


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=TOOLS.parent)
    ap.add_argument('--floors', type=Path, required=True, help='floor_triage.py floors.tsv')
    ap.add_argument('--abi-cache', type=Path, help='abi_facts cache (default build/abi_facts.json.gz)')
    ap.add_argument('--ledger', type=Path, default=Path('ledger/prototype_floors.jsonl'),
                    help='floor rows supplying aggregate abi.args_set_up leads')
    ap.add_argument('--workers', type=int, default=4)
    ap.add_argument('--out', type=Path, required=True)
    args = ap.parse_args(argv)
    root = args.root.resolve()
    import abi_facts as AF
    import sig_census as SC
    rows = [r for r in csv.DictReader(args.floors.open(), delimiter='\t') if r['blocker'] == 'arity']
    ledger = {row['name']: row for row in (json.loads(line) for line in (root / args.ledger).read_text().splitlines())}
    facts = AF.Facts(root, AF.scan(root, args.abi_cache or root / 'build/abi_facts.json.gz',
                                   min(args.workers, 6), log=lambda m: print(m, file=sys.stderr)))
    census = SC.Census(root, log=lambda m: print(m, file=sys.stderr))
    cache, out_rows, out_calls = {}, [], []
    for r in rows:
        name = r['name']
        darity = int(r['def_arity']) if r['def_arity'] != '' else None
        info = census.info(name)
        decl_arities = collections.Counter(s.arity for s in info.sites)
        defs = facts.callee(name)
        reads = max([d['facts']['arity'] for d in defs] or [0])
        sites = facts.sites(name)
        by_caller = collections.defaultdict(list)
        for s in sites:
            for cname in facts.rev.get(s['caller'], ()) or (s['caller'],):
                by_caller[cname].append(s)
        calls = []
        for rel, line, caller, nargs, argtext in lexical_calls(root, info.users, name, cache):
            matched = by_caller.get(caller, [])
            same = [s for s in matched if s['source'] == rel]
            use = same or matched
            lo, hi, pos = call_interval(nargs, use) if use else (nargs, nargs, [])
            if hi > nargs:
                # an omitted pass-through can only be spelled with the caller's own parameter name
                cnames = definition_use(root, rel, caller, cache)[0]   # the caller is defined in this file
                hi = max(nargs, min(hi, len(cnames)))
            c = dict(name=name, file=rel, line=line, caller=caller, nargs=nargs, sites=len(use),
                     positions=','.join(pos), callback_contract=0, lo=lo, hi=hi,
                     passthrough='', args=' | '.join(argtext)[:200])
            c['evidence_classes'] = ','.join(position_evidence(c, k) for k in range(max(nargs, hi)))
            calls.append(c)
        pnames, used = definition_use(root, r['def_path'], name, cache) if r['def_path'] else ([], 0)
        rt, feasible, target, why = route(name, darity, reads, calls, decl_arities, used)
        drop = sum(1 for c in calls if target != '' and c['nargs'] > int(target))
        add = sum(1 for c in calls if target != '' and c['nargs'] < int(target))
        for c in calls:
            if target != '' and c['nargs'] < int(target):
                # the omitted arguments are the caller's own incoming parameters at the same positions
                cnames = definition_use(root, c['file'], c['caller'], cache)[0]
                c['passthrough'] = ','.join(cnames[k] if k < len(cnames) else '?'
                                            for k in range(c['nargs'], int(target)))
        out_rows.append(dict(name=name, route=rt, def_path=r['def_path'], def_arity=r['def_arity'],
                             callee_reads=reads, body_uses=used,
                             ledger_args_set_up=json.dumps(ledger.get(name, {}).get('abi', {}).get('args_set_up', {}), sort_keys=True),
                             feasible=feasible, target_arity=target, calls=len(calls),
                             call_arities=','.join('%d:%d' % kv for kv in sorted(
                                 collections.Counter(c['nargs'] for c in calls).items())),
                             drop_calls=drop, add_calls=add,
                             extend_by=(int(target) - darity) if target != '' and darity is not None else '',
                             mixed_reason=why,
                             unmatched_calls=sum(c['sites'] == 0 for c in calls),
                             decl_arities=','.join('%s:%d' % ('()' if k is None else k, n)
                                                   for k, n in sorted(decl_arities.items(), key=repr)),
                             def_proto=r['def_proto']))
        out_calls.extend(calls)
    args.out.mkdir(parents=True, exist_ok=True)
    (args.out / '.ignore').write_text('*\n')
    for fname, fields, data in (('floor_arity.tsv', NAME_FIELDS, out_rows), ('floor_calls.tsv', CALL_FIELDS, out_calls)):
        with (args.out / fname).open('w', newline='') as fh:
            w = csv.DictWriter(fh, fields, delimiter='\t', lineterminator='\n')
            w.writeheader()
            w.writerows(out_rows if fname == 'floor_arity.tsv' else out_calls)
    summary = dict(arity_floors=len(out_rows), calls_to_extend=sum(r['add_calls'] for r in out_rows), by_route=dict(collections.Counter(r['route'] for r in out_rows).most_common()),
                   calls=len(out_calls), calls_to_edit=sum(r['drop_calls'] for r in out_rows))
    (args.out / 'summary.json').write_text(json.dumps(summary, indent=1) + '\n')
    print(json.dumps(summary, indent=1))
    return 0


if __name__ == '__main__':
    sys.exit(main())
