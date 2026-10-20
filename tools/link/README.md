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
