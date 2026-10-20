# Experimental declarative link graph

Production continues to read `config/link/` and `link/`. Neither the gate nor the
census imports this package. `config/link_graph/graph.json` is a proposal snapshot
of base `27ecdc47fe1fe15406e148c16605efea8f17cb80`.

The graph uses sorted-key JSONL records in shards smaller than 1,900,000 bytes.
One record per line makes entry/identity changes reviewable; JSON preserves
numeric spellings, empty maps and absent optional fields without a bespoke TSV
escape format. The manifest binds every shard's hash and record count.

The tables are separate identities:

* `files`: five physical disc files, sizes and SHA-1 witnesses.
* `views`: list attributes, physical-file reference and a view/phase identity.
  A phase ID identifies a view; it does not establish runtime exclusivity.
* `tus`: current ledger home identities, current LL7 source locations, source
  hashes and recipe witnesses. Native module identities are `module/<key>`.
  Inlined rows may share a physical source. This is not historical TU recovery.
* `entries`: ordered placements referencing TU homes, or accounting intervals.
  Metadata and TU fields retain their original schema and numeric spellings.
* `owners`: explicit image address witnesses and emitting linker-word owners.
  An address witness is never promoted to a definition merely by its address.

Source paths occur once per home rather than once per placement. Symbol maps are
reconstructed from owner edges. Original evidence, bindings, census, load evidence,
layout and provenance are retained. Of the current lists, 1,147 are sparse v0 and
144 are complete v1; the projection deliberately retains those schemas.

The census snapshot hashes 140 word lists as raw JSON, and its public-map
provenance binds raw hashes of every list. Views therefore record JSON object-key
traversal, indentation and original SHA-256. This metadata contains no duplicate
values. Projection preserves every list's exact serialization, in addition to the
requested canonical JSON comparison.

From the repository root (choose new, empty output directories):

```sh
python3 tools/link/graph.py validate
python3 tools/link/graph.py generate --output work/graph-replay/config/link
python3 tools/link/graph.py compare --report work/graph-replay/roundtrip.json \
    --holds work/graph-replay/holds.tsv
python3 -m unittest tools.tests.test_link_graph -v
```

`capture` is an explicit migration/import operation, requires an empty destination,
and reads the current lists plus ledger and source layout. `generate`, `compare`
and `validate` read the committed graph, without consulting the original lists to
restore entry fields. `compare` reads the original lists only as the expected side.
The generator refuses to write into this checkout's production `config/link/`.

For the combined link, prepare the ordinary SLUS build and gate the windows in
`build.slice` once. `combined.py --plan` writes the scoped gate command without
running it. Pass `--extend-ovmovie` to include the additional movie window. Outputs
must be private subdirectories of the root; binary inputs/outputs stay in the
explicit scratch directory, which is marked ignored.

```sh
python3 tools/link/combined.py --output work/graph-proof/out \
    --scratch work/graph-proof/scratch --extend-ovmovie --plan
# Run the scoped gate command in out/gate_plan.json once, with its GATE_JOURNAL.
python3 tools/link/combined.py --output work/graph-proof/out \
    --scratch work/graph-proof/scratch --extend-ovmovie
```

The adapter consumes the original ET_REL objects from the ordinary window builds,
not prelinked row binaries. It qualifies overlay symbols by stable image, TU
home and placement row (or assembly row), independently of object paths. The row
qualifier distinguishes multiple instances of one home in the same image: the
current graph has 304 such image/home pairs. It retains complete native
TU function-section order, the SLUS recipe and NOLOAD table witnesses. Actual
resident/image owners must agree with the window's linked-address witness.
Remaining imports receive explicit witnessed absolute assignments. Non-source
spans are imported from the verified user containers, with extent and SHA-256
receipts. Imports do not establish source ownership or independent reconstruction.

`emit_global` groups every selected RAM image by its declared shared VMA using
GNU `OVERLAY ... NOCROSSREFS`, assigns artificial disjoint LMAs, and asserts each
output's declared size. File-only MAIN/OVMOVIE spans use diagnostic VMAs and source
spans use the per-window link address. The retained `--no-check-sections` policy
is not proof of runtime phase separation. The negative test proves that GNU ld
rejects a relocation between distinct members of one overlay group.

The graph does not yet replace compiler configuration, the SLUS recipe generator,
window dependency projection or the production gate. Those are still independent
witnesses. No authority switch is implemented.

The OVMOVIE extension also consumes the existing separated-allocation module:
its graph TU records the rodata/text/data section extents from the current module
descriptor, and the adapter requires exact agreement with the fresh module gate
receipt. All allocations use one qualified ET_REL object. The final map receipt
summarizes source/import byte origins and hashes the private map; it contains no
retail payloads.

The expanded adapter selects all 60 town views at `0x80016000`, every
`dungeon/bank_*` view, and the two resident engine views. Diagnostic per-row
views are not extra load images. Prepare the existing SLUS and overlay build
views first, as above. Then:

```sh
python3 tools/link/combined.py --output work/one-link/out \
    --scratch work/one-link/scratch --all-images --extend-ovmovie --plan
# Run the command in out/gate_plan.json with its environment (at most 60 windows).
python3 tools/link/combined.py --output work/one-link/out \
    --scratch work/one-link/scratch --all-images --extend-ovmovie --prepare
```

`prepare.py` calls the existing production home-recipe APIs for source selection,
compiler and assembler flags, frozen home evidence, placement rebinding and
complete native-module preparation. Repeated home compiles are reused only
inside one invocation, before placement rebinding, with source/recipe/evidence
keys. Link-list and module tables are validated once and held constant during
preparation, with input hashes checked afterward. No gate implementation is
edited. A private hash-bound preparation index supports rerunning the combined
link without `--prepare`; changed inputs or objects invalidate it.

The bounded production gate is a representative window proof. Every linked
image also receives its own full retail byte comparison. An image whose objects
were only prepared is marked `NOT_GATED` in the window-comparison column; this
never claims a fresh production window verdict. `images.tsv` distinguishes linked
images from preparation holds. Source-row holds remain explicit even if retail
imports fill the corresponding gaps. `provenance.tsv` counts imported bytes
separately from original-object spans, so byte identity does not imply complete
source reconstruction.

Resident resolution requires both a witnessed address and a real definition in
an original input object. Absolute catalogues and local symbols cannot become
resident owners. Same-family engine definitions may satisfy bank references;
other bank definitions are never selected as resident owners. `binding_changes.tsv`
records each removed absolute binding and its defining object. Counts compare
the same expanded image scope with those recorded owner substitutions withheld
and applied. A separately reproduced baseline supplies the original-scope count.
Receipts larger than 2 MB stay in ignored scratch storage; output contains their
size, record count and SHA-256 summary. The global script and map likewise stay
private, with hash summaries in the output directory.

`--image <view>` may be repeated with `--all-images` for incremental global-link
proofs; the original baseline outputs remain included. Ordinary ELF32 metadata
is read directly to avoid spawning three binutils processes per original input.
Unexpected ELF bindings use binutils; neither object bytes nor relocations are
changed by this metadata reader.

Interior resident references use a real original-input definition plus an offset
strictly inside its explicit ELF symbol size. Extents are never inferred from
the next symbol. `LD_FEATURE("SANE_EXPR")` keeps those expressions attached to
the defining section; tests prove they retain NOCROSSREFS protection. Absolute
catalogue aliases and zero-size labels do not grant interior ownership.

For a large window whose repeated catalogue lookups dominate the production
gate, the same checks can run with validated immutable recipe tables:

```sh
python3 tools/link/gate_snapshot.py --window dungeon_deep_t8_0d07 \
    --output work/one-link/scratch/window-proof
```

This calls the unchanged `GateAll.run_window` and `worker_output`, compiles the
complete window, retains the ordinary pre/post input digest checks and catalogue
stamp checks, and additionally brackets the run with full preparation-input
hashes. The receipt records its wrapper hash and method. It edits no gate source
or authority files; each selected window still counts toward the 60-window cap.

A mismatched recipe VMA normally holds the source row. A loader-bound view may
instead accept a strict invariant-placement witness: independently link the
unchanged original object at both the recipe and selected VMAs, require both
complete code slices to equal retail, and reject NOLOAD/table/allocation moves.
`placement_bridges.json` records both hashes and the bound loader record. Tests
reject self-address relocations and missing loader evidence. No registry or
source correction is implied by this experimental placement.
