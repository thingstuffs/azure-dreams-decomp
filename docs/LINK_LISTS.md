# Link lists: one TU, many placements

Decision 59 (r121). This note describes the link-list tooling and the public byte-map catalogue.

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
  homes (not modelled yet; a module-member HOME is allowed, its member file compiles standalone or the gate fails), and refuses a placement that still has a copy file in `src/`. Archived first-pass facts are
  indexed by `config/frozen_raw.jsonl`; placements have no current raw text.

## Not yet modelled

Module placements (certified-module members and their bank copies) and cross-container homes. Text-reading reporting tools
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
This lets `link/main/main_bin.tsv` cover all MAIN.BIN without moving its existing `main/image_25c800` code
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
python3 tools/byte_map.py generate --labels <export.jsonl> --verify-retail --catalogue link --write
python3 tools/byte_map.py check --catalogue link --labels <export.jsonl>
# Rollout completion claim requires all five physical containers:
python3 tools/byte_map.py check --catalogue link --labels <export.jsonl> --complete-containers
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

`check` loads the selected catalogue (`config/link/` by default), recursively derives the seven totals, and, with `--labels`, compares
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

## Public byte-map catalogue and reproduction

`config/link/` remains the compilation catalogue. `link/<container>/<image>.tsv`
is the complete public catalogue: 1,317 logical images, including five physical
container roots, 443 exported load views and 37 leftover slices. Large images use
`<image>.000.tsv`, `.001.tsv`, etc.; these are storage parts of one logical image.
No part exceeds 2,000,000 bytes. The compact representation expands to the v1
semantic schema above, including the original TU objects, geometry and bindings.

Regenerate every public byte map from a fresh B13 clone plus this patch and a
user-owned US disc image (raw BIN or ISO). Python 3 and its standard library suffice:

```sh
python3 tools/census/regenerate.py --disc /path/to/Azure_Dreams.bin \
  --output /tmp/azure-census --check
```

The command extracts its temporary containers from ISO9660 directory records,
checks their B13 identity hashes, recomputes all detectors and precision gates,
validates bounded source/read and strict-prefix evidence, and writes regenerated
maps under `/tmp/azure-census/link/`. `--check` compares the complete generated file
set and every byte with committed `link/`; success reports `diff empty`. It needs
no existing `work/`, lane files, compiler, receipt or analysis cache. Temporary
retail containers are deleted at completion. Raw spans and detailed reports remain
in the output directory, which carries `.ignore`; none are committed.

The census and its masked-prefix helper are in `tools/census/`. All small inputs
are in `config/census/`: snapshot/source hashes, SLUS section layout, conditional
loader bank map, 69 accepted matched-read records, three strict replay prefixes,
and the rule registry. The 541 stale historical proposals remain excluded; their
hashes were not refreshed. Read instruction identities are SHA-256 hashes rather
than copied instruction words. The inputs contain extents, addresses, types,
relocation metadata and hashes, with no retail payloads.

Each metadata interval cites a stable rule ID from `config/census/rules.json`,
for example `census:zero_fill>=16`, `census:format:vab`, or
`census:noncode:decode`. The registry links each ID to its exact census evidence
kind and label. `tools/census/README.md` identifies the implementing functions and
precedence. Generated-path references are never evidence. Source and generated
census hashes are checked before rollout. Registered TU records are retained
verbatim; their storage tag `census:registered_tu` denotes the existing committed
`config/link/` object, without inferring additional compiled C.

The TSV format (`azure-clean.bytemap.tsv.v1`) has a `#` JSON header followed by:

```text
o	n	k	r	h	x
```

| field | meaning |
|---|---|
| `o`, `n` | JSON scalars for file offset and size; original TU spelling retained |
| `k` | `c` TU, `r` code region, `d` data, `a` asset, `p` padding, `l` leftover, `u` unresolved, `i` image reference |
| `r` | committed census rule ID; TU rows use `census:registered_tu` |
| `h` | asset SHA-256, otherwise empty |
| `x` | metadata profile index, or JSON `[row,home,vma,profile]` for a TU |

The header uses `s` format ID, `d` image metadata, `p` attribute profiles, `a`
zero-based part number and `z` total parts. Image metadata uses `i/c/o/n/v/l/e/y`
for image/container/offset/size/VMA/layout/evidence/symbols, `t` for the seven
census totals in the table's order and `p` for label hash, coverage hash and source.
TU identities omit the current container prefix; a null home means its own row.
The default TU path is `src/<home>.c`; any exception, optional bindings and original
evidence live in the TU profile. A legacy TU evidence note that mentions ignored
files is represented by `{"from":"config/link/<image>.json"}` and restored from
that committed original entry; no ignored path enters the public map. Absent optional fields stay absent. Profiles also
hold repeated format, census-label, type, extractor
or leftover-reason attributes. Readers reject unknown columns/keys, missing or
duplicate parts, inconsistent headers, conflicting geometry and label totals.
Adjacent metadata with equal kind, rule, label and attributes is merged, and any
combined asset gets a fresh hash over its exact new extent. TU and image-reference
boundaries survive unchanged.

```sh
python3 tools/byte_map.py check --catalogue link \
  --physical-roots link/physical_roots.json --complete-containers
python3 tools/extract_assets.py --catalogue link --disc /path/to/Azure_Dreams.bin
PYTHONPATH=tools/tests python3 -m unittest tools.tests.test_byte_map \
  tools.tests.test_byte_map_format tools.tests.test_byte_map_rollout \
  tools.tests.test_linklist tools.tests.test_source_layout -q
python3 -m unittest discover -s tools/census/tests -q
```

The byte-map reader decodes storage and uses the production geometry and census
validators; its placement indices and rule-3 tables must equal `config/link/`.
Without `--catalogue`, existing build callers continue to read `config/link/`.
Only `physical_root=1` rows in generated `coverage.tsv` may be summed: historical
views overlap and must agree with physical-root labels at every boundary.
`strongly_code` remains separate from registered C. The decision-57 terminal
non-code class is data awaiting typing, and is excluded from unknown/holds.

`link/leftovers/` keeps the reviewed group notes, slice hashes and structure audits.
The symbol dump contains two arrays of 678 and 2909 records plus a 168-byte opaque
separator. Descriptor checks bound the optional NPC and shop loads to 2048 bytes;
whole-container searches find two exact occurrences each. Slice identity does not
prove shared compiled TUs, full twin allocations, four shop placements or runtime
non-loading. The existing bounded holds remain valid. Any future compilation
input change needs its own scoped gate; this catalogue does not change authority.

## Load evidence outside rowbase regions (LL3c)

A fileless placement outside every rowbase region may obtain its link VMA from
its image. The image must carry `load_evidence` with exactly `path` (the tracked
`ledger/instance_load_regions.jsonl`) and `record_sha256` (SHA-256 of the selected
record serialized as sorted-key compact JSON). The gate checks the current record,
container, image containment, base/delta consistency, exact placement size and
split true name. Free-form `evidence` text alone cannot authorize the base.
A solved rowbase region still requires normal promotion; this path cannot bypass it.
When a proven rowbase delta exists, the placement must agree with it.

The load-record file participates in the affected window's inputs alongside its
image and home-image lists. A linked-base witness retains its stated scope: it
does not establish that retail executes a documented devkit-linked image.
Placement assembler flags resolve by the logical row key, retaining their identity
when several no-region images share a true-name label.
