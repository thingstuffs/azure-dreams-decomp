# Link lists and disc byte maps

A translation unit (TU) is one compiler input. Its home supplies the canonical
source; a placement reuses its object in another load image with evidenced
address bindings. Stable row IDs remain distinct even when they resolve to the
same physical source. See [SOURCE_LAYOUT.md](SOURCE_LAYOUT.md).

`config/link/<container>/<image>.json` is the compilation catalogue.
`link/<container>/` is the complete public byte-map catalogue, including views
that overlap. Sum only the nonoverlapping physical roots listed in
`link/physical_roots.json`; summing every load view would count bytes repeatedly.
The [link catalogue overview](../link/README.md) explains its directory layout.

## Source placement and rebinding

A code entry records the row, TU, home, file offset, VMA, size and optional
bindings. The registry derives `source_row`; do not add it by hand. A fileless
placement must not retain a duplicate source file. The home source and recipe,
load evidence, relocation targets and complete destination window are all
part of verification. [Complete module placements](LL5_MODULE_PLACEMENTS.md)
extend this model to supported whole TUs; cross-container homes remain outside
that backend's supported scope.

A home entry may carry `body_offset` when its registered extent starts with a
data prefix that its module keeps owning (a module member with `body_offset`;
the split record's `native_prefix_bytes` and the module member must agree, and
`tools/row_db.py check` enforces this). Its placements then copy only the
function body: each placement's size must equal the home size minus the prefix,
and rule 1 below maps the body entry, not the prefix start.

Address binding uses this priority:

1. The TU entry point maps to the placement VMA.
2. Explicit per-placement bindings apply.
3. Definitions placed in the same image win.
4. A matching layout tag permits the evidenced image displacement.
5. The image symbol map applies.
6. Otherwise the symbol remains unchanged, such as a resident reference.

Readable names do not choose bindings. Alias lowering retains canonical
address symbols; object rebinding replaces source-level relocation macros.
`tools/relink_lint.py`, run by `tools/row_db.py check`, rejects new relink-copy
text and checks the shrinking legacy allowlist.

The window gate compiles against the home's assembler evidence, rebinds the
object and checks the destination's linked retail bytes. Input fingerprints
cover the source/include closure and relevant image/home lists. A textual
declaration or an address shift alone proves neither storage ownership nor
runtime reachability.

## Complete byte maps

The `azure-clean.linklist.v1` semantic schema partitions an image's entire file
extent into positive-sized ordered entries, with no gaps or overlap. Sparse
legacy `v0` lists retain their narrower placement scope. Metadata entries are
accounting claims, not compiler inputs.

| Entry kind | Meaning |
|---|---|
| Code TU (no `kind`) | Registered code placement with its original row identity |
| `code_region` | Code evidence not represented by an additional registered TU |
| `data` | Evidenced type, or explicitly data awaiting typing |
| `asset` | Hashed slice derived from the contributor's disc |
| `padding` | Evidenced padding; the label alone prescribes no fill bytes |
| `leftover` | Independently evidenced leftover, not merely duplicate content |
| `unresolved` | Explicit unknown extent |
| `image` | Reference to a complete child image with matching geometry |

The seven census classes stay separate: `proven_code`, `library_code`,
`strongly_code`, `proven_data`, `noncode_typing_pending`, `padding_leftover`
and `unknown`. Strongly-code evidence is not decompiled C, and data awaiting
typing is not unknown code. A census label does not create a compiled function.

The compact `azure-clean.bytemap.tsv.v1` storage has a JSON header and columns
`o`, `n`, `k`, `r`, `h`, `x`: offset, size, kind, rule ID, asset hash and profile
reference. Headers retain image geometry, census totals and repeated profiles.
Large maps use numbered TSV parts; those parts form one logical image. The
reader validates part completeness, metadata, geometry and census totals.
`tools/byte_map_format.py` implements the encoding; `config/census/rules.json`
defines evidence rule IDs. No retail payload is stored in these maps.

Validate the committed maps from the repository root, without a disc:

```sh
python3 tools/byte_map.py check --catalogue link --physical-roots link/physical_roots.json --complete-containers
```

The result checks all five physical containers. Individual load views may
overlap but must agree with their physical-root labels at interval boundaries.
This catalogue check validates the committed accounting; it does not recompile C.

## Reproducing the census

**Requires a user-owned US disc, Python 3 and the committed census inputs.**
With the disc at the setup path, run from the repository root:

```sh
python3 tools/census/regenerate.py --disc 'bin/Azure Dreams.bin' --output work/docs_census --check
```

The command verifies `config/census/snapshot.json`, extracts temporary
containers using ISO9660 records, checks their hashes, recomputes detectors and
precision gates, and compares the complete regenerated map file set with
`link/`. Success reports `diff empty`. The ignored output contains reports and
hash receipts; temporary retail containers are removed on exit. No compiler,
Psy-Q installation, private workflow directory or analysis cache is required.
Read [the census implementation notes](../tools/census/README.md) for detector
precedence and the distinction between accepted and stale read evidence.

For extraction of catalogue assets, also requiring the disc:

```sh
python3 tools/extract_assets.py --catalogue link --disc 'bin/Azure Dreams.bin'
```

The extractor supports ISO/2048 and raw MODE1/MODE2 images, verifies slice hashes
before publishing, and writes under ignored `work/assets/`. An output override
must remain within that asset directory. Do not commit these extracted files.

## Load evidence and linker-owned words

Outside solved rowbase regions, an image may bind a tracked
`ledger/instance_load_regions.jsonl` record by hash. Its container, bounds,
base/delta and placement must agree. A solved region still requires its normal
promotion proof. Static linked-base evidence does not establish runtime execution.

One-word header, entry-point and padding records can be owned by the link list
rather than a C TU. They require the exact aligned four-byte extent, hash,
`container-slice-v1` extractor and canonical symbol bindings. The gate derives
the bytes from the user's container, rejects overlapping ownership, and includes
the resulting symbols in row and final links. `link_data.json` records each
window's contribution; `ledger/link_data_retired.jsonl` preserves retired IDs.
These words do not acquire synthetic function identities.

[Leftover reviews](../link/leftovers/README.md) distinguish slice identity from
unreachability and shared compiled ownership. Detailed layout/publication
rulings remain in [the decision record](evidence/r97_decisions.md).
