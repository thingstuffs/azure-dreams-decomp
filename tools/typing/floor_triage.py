#!/usr/bin/env python3
"""Prototype-floor triage: what blocks each ledger/prototype_floors.jsonl name in the CURRENT tree.

    floor_triage.py --out DIR [--root R] [--ledger ledger/prototype_floors.jsonl]

The floors were recorded by the signature solver (tools/typing/sig_solver.py, sig_consensus floor classes) at
the tree named in each record's evidence.  Later waves moved declarations into headers, retyped parameters
and removed casts, so a recorded blocker may be gone.  This re-reads the tree (no compiler, no build):

  * the declaration census of every floor name (tools/typing/sig_census.py: definitions, declaration
    sites with their canonical signature keys, users), built once;
  * whether each recorded blocking spelling is still present in its file;
  * the argument count of every direct call to the name (lexical: the score.py lexer over each user file,
    calls inside function bodies only).

Blocker (column `blocker`, first that applies):
  stale              no declaration site disagrees with the definition any more and every call passes the
                     definition's arity: nothing blocks one prototype (release: re-run sig_solver
                     --only-floors --retry-floors on a built tree to record it unified / drop the floor)
  foreign_build      no C definition in src/ (an import of another program or devkit build) or the
                     ledger's foreign_import_spelling class
  knr_definition     the definition is K&R / unprototyped (a prototype changes argument promotion)
  arity              calls or declarations disagree with the definition's parameter count
                     (phantom: more arguments than the definition reads; short: fewer)
  generated_type     the definition's prototype or a disagreeing declaration uses a generated layout
                     (S_<addr>, Rec_func_, Func<addr>Result, *View ...), so the owner header cannot publish it
  group_header_spelling  the only disagreeing headers are TU-group headers (*_gNNNNN.h): their extern
                     spelling differs from the definition (a probe decides whether the owner header can replace it)
  conflicting_header two header declarations disagree, or a header declaration disagrees with the definition
  local_spelling     only local (.c) declarations disagree, same arity, no generated type: a pointer-kind or
                     width difference the solver must re-probe (`floor_class` says which kind was recorded)

`releasable` = stale; `release` says how: drop_record (the owning header already publishes the definition's
prototype, so the floor record is obsolete) or publish_prototype (re-run the solver to write it).  `reprobe` = local_spelling floors whose recorded blocking spellings are all gone or
changed (the tree moved under them; a solver re-probe may unify).  Outputs: DIR/floors.tsv, DIR/floors.json.
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

GENERATED = re.compile(r'\b(?:S_(?:func_)?[0-9A-Fa-f]{6,8}\w*|Rec_\w+|Row_\w+|R\d+_\w+|Func[0-9A-Fa-f]{8}\w*|'
                       r'\w*[0-9A-Fa-f]{8}(?:State|Args?|Data|Ctx|Work|Result)\b|\w+View)\b')
GROUP_HEADER = re.compile(r'_g\d{5}\.h$')
FIELDS = ['name', 'owner', 'status', 'floor_class', 'blocker', 'releasable', 'release', 'owner_header_matches', 'reprobe', 'def_path', 'def_arity',
          'def_proto', 'sites', 'disagreeing', 'header_disagreeing', 'recorded_blocking', 'recorded_still_present',
          'call_arities', 'phantom_calls', 'short_calls', 'generated', 'evidence']


def squash(text):
    return re.sub(r'\s+', '', text or '')


def call_arities(root, files, name, cache):
    """Counter {nargs: calls} over direct calls to `name` inside function bodies of `files`."""
    import score as S
    out, where = collections.Counter(), collections.defaultdict(list)
    for rel in files:
        if not rel.endswith('.c'):
            continue
        if rel not in cache:
            text = (root / rel).read_text(errors='replace')
            tokens = S.lex(text)
            pairs, _ = S.pairs_of(tokens)
            bodies = [(b, e) for a, n, b, e, s in S.definitions(tokens, pairs)]
            cache[rel] = (text, tokens, pairs, bodies)
        text, tokens, pairs, bodies = cache[rel]
        for i, t in enumerate(tokens[:-1]):
            if t.value != name or tokens[i + 1].value != '(' or (i + 1) not in pairs:
                continue
            if i and tokens[i - 1].value in ('.', '->'):
                continue
            if not any(b < i < e for b, e in bodies):
                continue
            prev = tokens[i - 1].value if i else ''
            # a block-scope declaration `extern T name(...)` / `T *name(...)` is not a call
            if prev in ('extern', 'void', 's32', 'u32', 's16', 'u16', 's8', 'u8', 'int', 'char', 'short', 'long') or \
                    (prev == '*' and i > 1 and tokens[i - 2].kind == 'id' and tokens[i - 2].value not in ('return',)
                     and tokens[i - 3].value in (';', '{', '}', 'extern')):
                continue
            close = pairs[i + 1]
            if close == i + 2:
                n = 0
            else:
                n, depth = 1, 0
                for j in range(i + 2, close):
                    v = tokens[j].value
                    if v in '([{':
                        depth += 1
                    elif v in ')]}':
                        depth -= 1
                    elif v == ',' and depth == 0:
                        n += 1
            out[n] += 1
            where[n].append('%s:%d' % (rel, text.count('\n', 0, t.pos) + 1))
    return out, where


def knr(proto):
    """True for a K&R / unprototyped definition head: identifiers only between the parentheses."""
    m = re.search(r'\(([^()]*)\)\s*$', (proto or '').strip())
    if not m:
        return False
    inner = m.group(1).strip()
    if inner in ('', 'void'):
        return inner == ''
    return all(re.fullmatch(r'[A-Za-z_]\w*', p.strip()) for p in inner.split(','))


def triage(root, ledger, log=print):
    import sig_census as SC
    floors = [json.loads(line) for line in (root / ledger).read_text().splitlines() if line.strip()]
    log('%d floors; building the declaration census (about a minute)' % len(floors))
    census = SC.Census(root, log=log)
    cache, rows = {}, []
    for f in floors:
        name = f['name']
        info = census.info(name)
        defs = [d for d in info.definitions if not d.static]
        dkey = info.def_keys[0] if info.def_keys else None
        darity = None if dkey is None or dkey[1] is None else len(dkey[1])
        dproto = defs[0].proto if defs else (f.get('definition') or {}).get('proto')
        dpath = defs[0].path if defs else (f.get('definition') or {}).get('path')
        if dkey is None:
            # no C definition: the header's (or most common) spelling is the reference
            keys = collections.Counter(s.key for s in info.sites)
            hdr = [s.key for s in info.sites if s.in_header]
            dkey = hdr[0] if hdr else (keys.most_common(1)[0][0] if keys else None)
        disagree = [s for s in info.sites if dkey is not None and s.key != dkey]
        hdis = [s for s in disagree if s.in_header]
        hkeys = {s.key for s in info.sites if s.in_header}
        calls, where = call_arities(root, info.users, name, cache)
        decl_arity = collections.Counter(s.arity for s in disagree if s.arity is not None)
        phantom = sum(n for a, n in calls.items() if darity is not None and a > darity)
        short = sum(n for a, n in calls.items() if darity is not None and a < darity)
        decl_bad = sum(n for a, n in decl_arity.items() if darity is not None and a != darity)
        gen = sorted({m.group(0) for text in [dproto or ''] + [s.text for s in disagree]
                      for m in GENERATED.finditer(text)})
        recorded = f.get('blocking') or []
        present = 0
        for b in recorded:
            path = root / (b.get('path') or '')
            if not path.is_file():
                continue
            text = path.read_text(errors='replace')
            sp = b.get('spelling')
            if sp:
                present += squash(sp.rstrip(';')) in squash(text)
            else:
                present += any(s.path == b.get('path') for s in info.sites)
        foreign = (not defs) or f.get('floor_class') == 'foreign_import_spelling'
        if not disagree and not phantom and not short and not foreign:
            blocker = 'stale'
        elif foreign:
            blocker = 'foreign_build'
        elif dproto and knr(dproto):
            blocker = 'knr_definition'
        elif phantom or short or decl_bad:
            blocker = 'arity'
        elif gen:
            blocker = 'generated_type'
        elif hdis or len(hkeys) > 1:
            blocker = 'conflicting_header'
        else:
            blocker = 'local_spelling'
        reprobe = blocker == 'local_spelling' and recorded and present == 0
        owner_ok = any(s.in_header and s.key == dkey for s in info.sites)
        if blocker == 'stale':
            # the owning header already publishes the definition's prototype: the floor record is obsolete
            release = 'drop_record' if owner_ok else 'publish_prototype'
        else:
            release = ''
        group = [s for s in hdis if GROUP_HEADER.search(s.path)]
        if blocker == 'conflicting_header' and group and len(group) == len(hdis):
            blocker = 'group_header_spelling'
        ev = []
        if disagree:
            ev.append('disagree: ' + '; '.join('%s:%d %s' % (s.path, s.line, ' '.join(s.text.split())[:90])
                                               for s in disagree[:3]))
        if phantom or short:
            ev.append('calls: ' + '; '.join('%d args at %s' % (a, ','.join(where[a][:2]))
                                            for a in sorted(calls) if a != darity))
        rows.append(dict(name=name, owner=f.get('owner') or '', status=f.get('status'),
                         floor_class=f.get('floor_class'), blocker=blocker, releasable=int(blocker == 'stale'),
                         release=release, owner_header_matches=int(owner_ok),
                         reprobe=int(bool(reprobe)), def_path=dpath or '', def_arity='' if darity is None else darity,
                         def_proto=' '.join((dproto or '').split())[:140], sites=len(info.sites),
                         disagreeing=len(disagree), header_disagreeing=len(hdis),
                         recorded_blocking=len(recorded), recorded_still_present=present,
                         call_arities=','.join('%d:%d' % kv for kv in sorted(calls.items())),
                         phantom_calls=phantom, short_calls=short, generated=','.join(gen)[:120],
                         evidence=' | '.join(ev)[:400]))
    return rows


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=TOOLS.parent)
    ap.add_argument('--ledger', default='ledger/prototype_floors.jsonl')
    ap.add_argument('--out', type=Path, required=True)
    args = ap.parse_args(argv)
    root = args.root.resolve()
    rows = triage(root, args.ledger)
    args.out.mkdir(parents=True, exist_ok=True)
    (args.out / '.ignore').write_text('*\n')
    with (args.out / 'floors.tsv').open('w', newline='') as fh:
        w = csv.DictWriter(fh, FIELDS, delimiter='\t', lineterminator='\n')
        w.writeheader()
        w.writerows(rows)
    summary = dict(floors=len(rows), by_blocker=dict(collections.Counter(r['blocker'] for r in rows).most_common()),
                   by_blocker_and_recorded_class=dict(collections.Counter(
                       '%s<-%s' % (r['blocker'], r['floor_class']) for r in rows).most_common()),
                   releasable=sum(r['releasable'] for r in rows), reprobe=sum(r['reprobe'] for r in rows),
                   release=dict(collections.Counter(r['release'] for r in rows if r['release'])),
                   recorded_blocking=sum(r['recorded_blocking'] for r in rows),
                   recorded_still_present=sum(r['recorded_still_present'] for r in rows))
    (args.out / 'floors.json').write_text(json.dumps(summary, indent=1) + '\n')
    print(json.dumps(summary, indent=1))
    return 0


if __name__ == '__main__':
    sys.exit(main())
