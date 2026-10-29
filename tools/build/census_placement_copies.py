#!/usr/bin/env python3
"""Census: which linked production recipes the typing tools' proof map never compiles.

    census_placement_copies.py [--root R] [--json OUT]

The proof map every typing/header tool uses is `layout_compile_identity.recipes(root)` (one recipe per
physical source).  The build graph is `build/.state/recipes` + registered images.  This joins the two
on the recipe's own source and classifies every overlay recipe:

  src_proven_linked     source in the proof map, linked into a registered image
  src_unproven_linked   src/ source not in the proof map, linked
  placement_linked      placement copy (build/.state/enumerate/*.member/*.c), linked
  unlinked              in no registered image (facades, check-only recipes)

For placement copies it also reports how many owners are themselves in the proof map (the owner's
compile covers the text but not the copy: other bank, other noreturn/sibcall evidence, other
bindings), and how many distinct objects the copies of one home produce (`build/obj` hashes; no
compile).  Read-only; ~20 s.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import hashlib
import json
from pathlib import Path
import sys

HERE = Path(__file__).resolve()
sys.path.insert(0, str(HERE.parent))
import affected as A    # noqa: E402


def census(root):
    root = Path(root).resolve()
    sys.path[:0] = [str(root / 'tools'), str(root / 'tools/gate')]
    import layout_compile_identity as L
    physical, members = L.recipes(root)
    graph = A.Graph(root)
    linked = Counter()
    for spec in graph.images.values():
        for rid in set(spec['recipes']):
            linked[rid] += 1
    classes = Counter()
    by_class = defaultdict(list)
    for rid, spec in graph.recipes.items():
        if spec['_family'] != 'overlay':
            continue
        if spec.get('projection'):
            cls = 'placement_linked' if linked[rid] else 'placement_unlinked'
        elif not linked[rid]:
            cls = 'unlinked'
        elif spec['source'] in physical:
            cls = 'src_proven_linked'
        else:
            cls = 'src_unproven_linked'
        classes[cls] += 1
        by_class[cls].append(rid)
    copies = by_class['placement_linked']
    owners_proven = sum(graph.recipes[r]['projection']['owner'] in physical for r in copies)
    in_map = sum(graph.recipes[r]['source'] in physical for r in copies)
    per_home = defaultdict(set)
    missing = 0
    for rid in copies + by_class['placement_unlinked']:
        spec = graph.recipes[rid]
        path = root / spec['output']
        if not path.is_file():
            missing += 1
            continue
        per_home[spec['projection']['home']].add(hashlib.sha256(path.read_bytes()).hexdigest())
    distinct = Counter(len(v) for v in per_home.values())
    multi_image = sum(1 for r in copies if linked[r] > 1)
    sources_in_map_recipes = Counter()
    for rid, spec in graph.recipes.items():
        if spec['_family'] == 'overlay' and not spec.get('projection') and spec['source'] in physical \
                and linked[rid]:
            sources_in_map_recipes[spec['source']] += 1
    return dict(
        proof_map_sources=len(physical), proof_map_member_paths=len(members),
        overlay_recipes=sum(1 for s in graph.recipes.values() if s['_family'] == 'overlay'),
        slus_recipes=sum(1 for s in graph.recipes.values() if s['_family'] == 'slus'),
        registered_images=len(graph.images) + (1 if graph.slus_image else 0),
        linked_overlay_recipes=sum(1 for r, s in graph.recipes.items() if s['_family'] == 'overlay' and linked[r]),
        classes=dict(classes),
        placement_copies_total=len(copies) + len(by_class['placement_unlinked']),
        placement_linked_source_in_proof_map=in_map,
        placement_linked_owner_in_proof_map=owners_proven,
        placement_linked_in_more_than_one_image=multi_image,
        placement_homes=len(per_home), placement_objects_missing=missing,
        distinct_objects_per_home=dict(sorted(distinct.items())),
        proof_map_sources_with_more_than_one_src_recipe=sum(1 for n in sources_in_map_recipes.values() if n > 1),
        extra_src_recipes_beyond_one_per_source=sum(n - 1 for n in sources_in_map_recipes.values() if n > 1),
        extra_src_recipe_args=dict(Counter(' '.join(s['args'][1:]) for r, s in graph.recipes.items()
                                           if s['_family'] == 'overlay' and not s.get('projection')
                                           and linked[r] and sources_in_map_recipes.get(s['source'], 0) > 1)
                                   .most_common(6)),
        src_unproven_linked=sorted(graph.recipes[r]['source'] for r in by_class['src_unproven_linked'])[:40],
        stale_recipe_files=dict(Counter(s['_family'] for s in graph.stale.values())),
        stale_placement_copy_files=sum(1 for s in graph.stale.values() if s.get('projection')),
    )


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=A.DEFAULT_ROOT)
    ap.add_argument('--json', type=Path)
    args = ap.parse_args(argv)
    result = census(args.root)
    text = json.dumps(result, indent=1, sort_keys=True)
    if args.json:
        args.json.write_text(text + '\n')
    print(text)
    return 0


if __name__ == '__main__':
    sys.exit(main())
