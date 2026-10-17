# Link lists: one TU, many placements

Decision 59 (r121). Design and census: `work/native_lane/_r120/linklist/REPORT.md`. This note describes the
tooling (LL0); the conversions (LL1+) are separate batches.

## Model

- A **TU** is the only text of a function family. It is written in its **home** placement's address space:
  the object spells every symbol `func_/D_<home address>` (tools/build/ccproc.py turns names.tsv aliases back
  into those).
- A **load image** (a dungeon bank, a town scene module, the engine) has one link list,
  `config/link/<container>/<image>.json` (schema `azure-clean.linklist.v0`, see `tools/gate/linklist.py`).
- A **placement** is a link-list entry: (row, TU, home row, foff, vma, size, optional `bindings`). It is still a
  registered row (split record + rows.jsonl), so windows, coverage, levels and certificates keep their unit. It
  has no `src/` file. `tools/registry.py` derives `source_row` (the home row id) from the link lists; never add it
  by hand. `tools/source_layout.py` resolves a placement row to its home's source.
- With no `config/link/` directory every tool behaves exactly as before.

## Address rules (linklist.binding; first rule that applies)

1. the TU's own entry point -> the placement vma;
2. the entry's `bindings` (per placement, with evidence);
3. a symbol whose home row is also placed in this image -> that placement (local definition wins);
4. same `layout` tag on both images and the symbol lies in the home image -> shifted by the image delta;
5. the image's `symbols` map;
6. unchanged (resident).

Names never enter a link list: a rename in names.tsv or the TU cannot change what a placement links to.
No `#define <old> func_<new>` relocation lines and no `-D` symbols: rebinding happens on the object, by address.

## Proof

- The window gate compiles the shared TU for a placement segment with the **home's** frozen bank evidence
  (linklist.evidence_foff), rewrites the object's symbols with objcopy (log: `obj/<row>.rebind.txt`), and the
  unchanged mini-link + window compare proves the bytes at the placement's address. A placement exists only if
  that window gate matches retail.
- `proof_receipts.window_inputs` binds the TU and its `-M` closure (through the resolver), the home's bank
  evidence, and the link-list files that decide the window's placements (`linklist.window_files`: the
  placement's image, its home's image, and the home images of the other placements in that image). A TU edit or
  a link-list edit re-keys exactly the windows holding affected placements; windows without placements bind no
  link-list file.
- `proof_receipts.validate_view` requires the gate view's `config/link` to be the canonical one and, when the
  source_layout projection is in use, that the projection is exactly the planned set of symlinks.
- `tools/row_db.py check` checks every entry against its split record (MATCH C row, extent, link vma), the
  registry (`source_row`), the home's resolved source (`tu`), refuses a placement row that is a module member and cross-container
  homes (not modelled yet; a module-member HOME is allowed, its member file compiles standalone or the gate fails), and refuses a placement that still has a copy file in `src/`. A placement's `raw/` file is
  optional.

## Not yet modelled

Module placements (certified-module members and their bank copies), cross-container homes, placements whose
image has no proven rowbase region (the gate links at a true base only inside one). Text-reading reporting tools
(status shape census, decl/struct census, levels record facts, dashboard) still read the home text once per
placement; LL1 must make them count each TU once (`source_layout.source_items` already does).
