# Finding the editable source

Source is organized by subsystem under `src/engine/`, `src/frontend/`,
`src/town/`, `src/dungeon/` and `src/movie/`. Stable row IDs still use physical
container names such as `slus`, `main` and `ovmovie`. An ID is not a source path.

Run these commands from the repository root; no disc or compiler is needed:

```sh
python3 tools/source_layout.py check
python3 tools/source_layout.py path town/func_8008D54C
python3 tools/source_layout.py path dungeon/func_8188C800
python3 tools/source_layout.py ids src/town/scene/copy_words_backward_from_offset.c
```

The first example resolves to
`src/town/scene/copy_words_backward_from_offset.c`; the second resolves to
`src/dungeon/effect/travel/follow_brighten.c`. Resolve again when working on a
later revision. The `ids` command returns the logical rows affected by a
physical source path, including shared ownership as applicable.

## One source, several identities

`ledger/layout.jsonl` maps registered IDs to current source locations.
`ledger/layout_inline.jsonl` records members inlined into a physical TU.
[Link lists](LINK_LISTS.md) identify fileless placements that use a home's
source. Several row IDs can therefore resolve to the same C file. Keep the
complete physical TU when editing; do not recreate an old per-member file.

`c_path` and historical basenames remain lineage identifiers in records and
build adapters. An old `src/<container>/<address>.c` token in a manifest may
describe a generated build view rather than a file in the public source tree.
The resolver, not a textual prefix substitution, determines the editable path.
The source reorganization did not rename the registry's stable IDs.

## Tool interfaces

`tools/gate/source_layout.py` validates the layout and provides `row_path`,
`row_relative`, `source_items`, `source_files`, `row_ids_for_paths` and
`physical_owner`. `tools/source_layout.py` is the public facade and also
provides `own_source` and `source_segments` for per-row analysis of inlined
members. Scanning a complete shared TU as though every sibling belongs to one
row would miscount pins, calls and source-quality facts.

Build adapters materialize a managed flat projection for consumers that still
require historical names. That generated view is not the editable source tree.
Source moves must update layout records, inline extents, manifest paths,
includes and affected proofs together. Ordinary source changes should retain
the existing layout. Source symlinks escaping the tree, ambiguous ownership and
invalid inline spans are rejected by the resolver.

The layout and naming rules are recorded in
[decisions 61, 65 and 68](evidence/r97_decisions.md).
