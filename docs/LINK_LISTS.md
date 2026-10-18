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

## Relink text ratchet (LL2)

`tools/relink_lint.py` (run by `tools/row_db.py check`) refuses new `#define <ident> func_/D_<addr>` relocation lines
and new `/* Relink of matched` copy files: a copy is a link-list placement. The files that still carry such text
(copies not yet convertible: cross-container homes, solved rowbase regions, homes outside proven regions, objects
that differ) are frozen in `config/lint/relink_text.allow`. The list only shrinks; a stale entry is an error too, so
a conversion removes it in the same change (`tools/relink_lint.py shrink`).

## Whole-image byte maps (decision 60b)

`azure-clean.linklist.v1` upgrades a selected image from a sparse code list to an ordered partition of
`[foff, foff + size)`. Every entry has a positive size. Adjacent entries meet exactly; a leading gap,
trailing gap, overlap, or out-of-order entry is an error in the **production loader**, including when the
image contains no code. `v0` remains accepted for images awaiting conversion; it does not claim complete
coverage. Mixed v0/v1 trees retain the existing placement and rebinding semantics.

The image keeps its existing fields and gains required `census` byte totals and optional `provenance`.
Code entries keep precisely the v0 fields above, without a new `kind` or renamed functions. They account
as `proven_code`. A census export contradicting a code entry is refused as a snapshot/evidence conflict.
The v1 loader validates all metadata, but only unchanged TU entries enter `load()[1:3]`, `placement`,
`is_placement`, the row database, and the rebinding tables. It never compiles a metadata entry.

| `kind` | extra required fields | census class | meaning |
|---|---|---|---|
| absent | existing `row`, `tu`, `home`, `foff`, `vma`, `size` | `proven_code` | buildable TU placement; unchanged |
| `data` | `type` | `proven_data` or `noncode_typing_pending` | concrete evidenced type, or literal `typing pending` |
| `padding` | none | `padding_leftover` | padding established by the cited evidence |
| `asset` | `format`, `sha256`, `extractor`, `census_label` | `proven_data` or `noncode_typing_pending` | physical blob or data-object slice extracted from the user's disc |
| `leftover` | `reason` | `padding_leftover` | independently proved leftover; a duplicate alone is insufficient |
| `unresolved` | none | `unknown` | explicit evidence hold; no code/data/leftover inference |
| `code_region` | `census_label` | `proven_code`, `library_code`, or `strongly_code` | census code not represented by a TU placement yet |
| `image` | `ref` | recursively derived | reference to one complete v1 load image |

Every metadata entry also requires `foff`, `size`, and nonempty `evidence`. An optional metadata `vma` must
agree with the load image's delta. Unknown keys, missing fields, invalid SHA-256 values, and unsupported
extractors fail closed. A `code_region` is an accounting interval, not a newly registered function or a
build substitute; its existing ledger-driven compilation continues as before.

For example, a 48-byte evidenced jump-table object can be stored without its bytes:

```json
{"kind":"asset","foff":"0x1001008","size":48,
 "format":"psx-mips32-jump-table-le","extractor":"container-slice-v1",
 "sha256":"4257cbfde8a7ada455006f20e99287e2cef0c72da0c77bf3ffbbbec967606a6d",
 "census_label":"proven_data","evidence":"ledger/splits/dungeon.jsonl:D_80FE1008 MATCH data object"}
```

The schema does not store fill patterns or retail payloads. A padding claim does not by itself prescribe
a fill value. `format: opaque` and `census_label: noncode_typing_pending` describe a physical blob whose
type remains unproved; such an asset requires independent non-code evidence. Do not create it from an
unknown span merely to extract it. Concrete object types and placement remain separate claims.

A file container with several load bases can use `vma: null`. It has no direct TU entries and can refer
to complete load images with `kind: image`, `ref`, `foff`, `size`, and `evidence`. Each reference must name
an existing v1 image in the same container with exactly that extent; cycles and sparse v0 children fail.
This lets `main/main_bin.json` cover all MAIN.BIN without moving its existing `main/image_25c800` code
placements or inventing a single load address for the whole file. Recursive census walks count the
child once. Legacy overlapping placement-list views are not automatically container roots: choose
nonoverlapping physical owners before the complete-container rollout.

## Census export, generation, and checking

`tools/byte_map.py` consumes UTF-8 JSONL, with one `azure-clean.census-map.v1` header per image and one
record per disjoint labelled span. Multiple images can appear in one export. Headers require `image`,
`container`, `foff`, `size`, `vma`, `evidence`, and `census`; optional `children` lists load-image IDs
included in the same export. Numeric offsets/sizes accept integers or `0x` strings. The seven census
keys are `proven_code`, `library_code`, `strongly_code`, `proven_data`, `noncode_typing_pending`,
`padding_leftover`, and `unknown`; omitted zero counts normalize to zero. Totals must be nonnegative
integer byte counts, and both input and output must reproduce the complete image size.

Example export for a synthetic, file-only 32-byte image:

```jsonl
{"schema":"azure-clean.census-map.v1","image":"main/example","container":"main","foff":0,"size":32,"vma":null,"evidence":"reviewed census snapshot","census":{"noncode_typing_pending":16,"unknown":16}}
{"image":"main/example","foff":0,"size":16,"label":"noncode_typing_pending","evidence":"validated non-code detector"}
{"image":"main/example","foff":16,"size":16,"label":"unknown","evidence":"no bounded reader or code entry"}
```

Span records require `image`, `foff`, `size`, `label`, and `evidence`. Typed proven data also needs `type`,
or explicit `kind: asset` with the asset fields above. `padding_leftover` needs explicit `kind: padding`
or `kind: leftover` plus its reason; the exporter must preserve this evidence distinction. Evidence kinds
in census2's large span files need a small export adapter into this documented interface, not a fresh
round of inference. Do not assume a missing type is a concrete type or an unknown is leftover.

```sh
python3 tools/byte_map.py generate --labels <export.jsonl> --verify-retail
python3 tools/byte_map.py generate --labels <export.jsonl> --verify-retail --write
python3 tools/byte_map.py check --labels <export.jsonl>
# Rollout completion claim requires all five physical containers:
python3 tools/byte_map.py check --labels <export.jsonl> --complete-containers
```

`--root <checkout>` precedes the subcommand. `generate` validates everything before writing; without
`--write` it only prints the proposed sizes, census and coverage receipts. It preserves all code entry
objects and image geometry, fits the census spans around those objects and the selected child images,
and emits the remaining accounting entries. A physical asset may not be cut by a TU or child boundary.
`--verify-retail` verifies all directly emitted asset hashes against the user's extracted containers.
The only supported extractor ID is `container-slice-v1`.

The default `--coverage-regions` is `ledger/coverage_regions.jsonl`. Categories are overlapping witnesses:
the generator clips/unions them per image and reports their byte counts separately. A `window` is not
all code, `data_excluded` is not independent data proof, and `estimated_code` is not automatically an
admitted census tier. Neither the coverage ledger nor the generator changes census labels. Generated
image provenance binds the SHA-256 of both the labels export and coverage ledger.

`check` loads the production maps, recursively derives the seven totals, and, with `--labels`, compares
labels at **every interval boundary**, permitting equivalent coalescing. A label swap with unchanged
aggregate totals still fails. Its summary distinguishes referenced children from root images and refuses
overlapping selected roots. `--image` can scope the summary; all v1 maps are still validated by the loader.
`--complete-containers` additionally proves exact coverage of all five containers against their recorded
sizes (SLUS is 524,288 bytes), and fails on a partial rollout.

## User-disc asset extraction

```sh
python3 tools/extract_assets.py --disc 'bin/Azure Dreams.bin'
python3 tools/extract_assets.py --disc <user.iso> --image dungeon/bank_1001000
```

The extractor reads ISO9660 directory records from ISO/2048, raw MODE2/2352, or raw MODE1/2352. It reads
only the declared slices of MAIN/MAIN.BIN, TOWN/TOWN.BIN, DUNGEON/DUNGEON.BIN, OVMOVIE.BIN, or SLUS_006.14;
no committed sector placement or retail content is required. Unsupported multi-extent/interleaved files,
missing files, truncated reads and out-of-file slices are refused. Container-image references are walked
without extracting their children twice. Each blob is streamed to a temporary file, hashed, and published
only after its SHA-256 matches; a mismatch removes the temporary file and preserves any existing output.

Outputs live under `work/assets/<container>/`, protected by both `.gitignore` and `.ignore`. An optional
`--out` must resolve under that directory; symlink escapes fail. Names use offset, size, and a digest
prefix, with full hashes retained in the maps/receipt. Never add extracted blobs or containers to a patch.

## Prototype and rollout limit

`work/native_lane/r121w_bytemap/prototype.py` reproduces a conservative three-image demonstration from
staged MATCH code/data records and the census method's zero-run rule. It tiles a dungeon bank, a town
module and the complete MAIN.BIN, preserving all 53 existing sample TU entries. It includes pending
object types and two verified jump-table assets. The supplied census2 reports contain totals but no
span export or detector implementation; therefore this prototype deliberately retains other bytes as
`unknown`. Its figures are **not** the census2 classification totals or a claim of full five-container
coverage. `REPORT.md` in that lane records the measured results and the remaining evidence dependency.
