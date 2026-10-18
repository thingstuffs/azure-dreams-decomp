# Disc leftovers

These are metadata link lists: offsets, lengths, hashes, placement image IDs,
positive reasons and evidence references. The payload remains on the user's disc.
No source or directory moves are part of LL6. Each group's `placements.json` lists
bounded slices; the referenced whole-image v1 map lives under `link/town/`.

- `town/scene_drafts/`: 25 scene-table records and three bounded zero-base prefixes.
- `town/debug_npc/`: two independently hashed, identical 2048-byte slices.
- `town/test_shop/`: two independently hashed, identical 2048-byte slices; the
  report's broader four-copy family is held pending exact extents and TU proof.
- `devkit/`: symbol dump, debug type tables, scenario paths, assembler source
  fragment and link-line text, with format and extent limits recorded.
- `stale_images/`: only the exact census ledger stale/prior intervals, with hashes;
  no enclosing stale image is inferred.

Evidence is preserved at `docs/evidence/r121w_ll6/LEFTOVERS_REPORT.md`. Its static
reachability findings are not emulator observations. Hash identity establishes
slice identity only, not a shared compiled TU or runtime deadness proof.

These groups overlap each other and some scene records overlap: use interval
unions, never sum slice lengths. Existing code, data and unknown census classes
are retained inside leftover footprints. Only exported padding/leftover bytes
receive `kind: leftover` there. Public
coverage shows both the disjoint census class and the full leftover footprint.
Physical roots count each byte once, and game-code totals exclude code in that
footprint. Bytes elsewhere remain unresolved unless existing evidence classifies
them. Shipped-module Japanese text, shifted resident images and uncertain stale
images are not admitted here merely because they look old.
