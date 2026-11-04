"""Definition-inclusive prototype disagreement census with container binding."""
from __future__ import annotations

from collections import Counter
import hashlib
import json
from pathlib import Path
import sys

TOOLS = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(TOOLS), str(TOOLS / 'headers'), str(TOOLS / 'typing')]
import model as M
from sig_census import Census, site_key


def mismatch(definition_key, declaration_key):
    """Only return type and explicit parameter count are policy candidates."""
    ret = definition_key[0] != declaration_key[0]
    a, b = definition_key[1], declaration_key[1]
    arity = a is not None and b is not None and len(a) != len(b)
    return ('return_type' if ret else '') + ('+arity' if ret and arity else 'arity' if arity else '')


def census(root: Path):
    c = Census(root)
    floors = {json.loads(line)['name'] for line in
              (root / 'ledger/prototype_floors.jsonl').read_text().splitlines() if line.strip()}
    candidates = {}
    duplicates = []
    bodies = {}
    for name, definitions in sorted(c.plan.defs.items()):
        defs = [d for d in definitions if not d.static and not getattr(d, 'kind', '')]
        if len(defs) > 1:
            entries = []
            for d in defs:
                if d.path not in bodies:
                    scan = c.corpus.scan(d.path)
                    bodies[d.path] = {(it.decls[0].name, it.line): hashlib.sha256(
                        ' '.join(scan.masked[it.body[0]:it.body[1]].split()).encode()).hexdigest()[:16]
                        for it in scan.items if it.kind == 'def' and it.body}
                entries.append(dict(file=d.path, container=d.container, prototype=d.proto,
                                    signature=repr(site_key(d.params, d.ret_spec, d.ret_ptr,
                                                            c.tindex.visible(d.path))),
                                    body_hash=bodies[d.path].get((d.name, d.line))))
            signatures = {e['signature'] for e in entries}
            hashes = {e['body_hash'] for e in entries}
            kind = ('different_contracts' if len(signatures) > 1 else
                    'same_body_copies' if len(hashes) == 1 and None not in hashes else 'identity_review')
            # These two collisions were independently identified by creator/updater review.
            if name in {'apply_random_actor_value_adjustment', 'update_actor_effect_sequence'}:
                kind = 'different_functions'
            duplicates.append(dict(name=name, classification=kind, definitions=entries))
        if len(defs) != 1 or name in floors:
            continue
        definition = defs[0]
        defkey = site_key(definition.params, definition.ret_spec, definition.ret_ptr,
                          c.tindex.visible(definition.path))
        for row in c.plan.sites_by_name.get(name, []):
            site = row.site
            if (row.definition is None or row.definition.path != definition.path
                    or site.storage == 'static' or site.path.startswith(('include/modules/', 'include/sdk/'))):
                continue
            sitekey = site_key(site.params, site.ret_spec, site.ret_ptr,
                               c.tindex.visible(site.path))
            kind = mismatch(defkey, sitekey)
            if not kind:
                continue
            key = f'{name}::{definition.path}::{site.path}::{kind}'
            candidates[key] = dict(site_id=key, name=name, definition=definition.path,
                                   declaration=site.path, line=site.line, kind=kind,
                                   definition_signature=repr(defkey), declaration_signature=repr(sitekey),
                                   declaration_text=' '.join(site.text.split()))
    return dict(candidates=sorted(candidates.values(), key=lambda row: row['site_id']),
                duplicates=duplicates, count=len({row['name'] for row in candidates.values()}),
                candidate_sites=len(candidates), duplicate_names=len(duplicates),
                duplicate_classes=dict(Counter(row['classification'] for row in duplicates)))


def check(report, baseline):
    known = set(baseline['candidate_sites'])
    return [row['site_id'] for row in report['candidates'] if row['site_id'] not in known]


def main(argv=None):
    import argparse
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--root', type=Path, default=TOOLS.parent)
    p.add_argument('--out', type=Path, required=True)
    p.add_argument('--baseline', type=Path, default=Path(__file__).with_name('proto_baseline.json'))
    p.add_argument('--check', action='store_true')
    p.add_argument('--write-baseline', action='store_true')
    args = p.parse_args(argv)
    if args.check and args.write_baseline:
        p.error('choose check or write-baseline')
    report = census(args.root.resolve())
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(json.dumps(report, indent=2) + '\n')
    if args.write_baseline:
        args.baseline.write_text(json.dumps(dict(candidate_sites=[row['site_id'] for row in report['candidates']]),
                                            indent=2) + '\n')
    problems = check(report, json.loads(args.baseline.read_text())) if args.check else []
    print(f'prototype candidates: {report["count"]} names, {report["candidate_sites"]} sites; '
          f'multi-definition names: {report["duplicate_names"]}')
    for problem in problems:
        print('new prototype disagreement: ' + problem, file=sys.stderr)
    return int(bool(problems))


if __name__ == '__main__':
    sys.exit(main())
