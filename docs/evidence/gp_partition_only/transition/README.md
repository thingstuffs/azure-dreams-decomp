# Private ready29 global GP transition proposal

`transition.patch` is a reviewable proposal against the production code baseline
`b4130ec4`. It has **not** been applied to production. The current HEAD during
preparation was a docs-only successor; every proposed target was diffed against
its current production bytes. `prepare.py` reproduces the patch, `inventory.json`
records before/after SHA-256 and byte counts for every file, and `payload/`
holds exact proposed contents. A private `patch -p1` replay into
`patch_checkroot/` reproduced all 57 payload files byte for byte.

The 57 files are 29 canonical SLUS C sources, two shared headers, two module
plans, the canonical workflow document, nine build/ownership adapters, two portable tests, two guarded generic
assembler files, seven assembler regression tests, and three complete ledger
outputs. The C sources come from the full-retail ready29 stage, with four
source-hygiene refinements proven to emit byte-identical raw CDK assembly and
two canonical-body repairs described below; changed
collector bodies remain in their canonical parent sources and are routed by
the two-parent partition plan. The new aggregators supply declarations and
storage, then include generated partition fragments. Generated fragments are
not proposed as canonical production files. The inventory lists each changed
source's module role, functions, and owned symbols. There are 70 unique owned
data records, no overlapping owner intervals, no new keyed assembler flags,
and no new config pin file. The guarded assembler delta has no named function,
symbol, or absolute-address special case.

The final `tools/build/configure.py` payload is the frozen nine-tool core
(SHA-256 `5728f7979b573c189c05817aa48b94b98bbf45566a3e6d982dc658861279f4fd`)
plus ready29's exact 15 CDK recipe overrides (final SHA-256
`ae9639ee865fc821df79f2f9bc9697aa705beac21b6c026c1cf8be5e2668ca2c`).
A fresh private configure run in `configure_fixture/` generated
`build.ninja` byte-identical to the retail-exact ready29 stage and proposed
pinned Ninja (SHA-256 `968784a7addd9c20cca57e34f3f28d73a101dcc88c91e5046adbe55d0a7cdc44`).
Its complete 860 physical edges project to all 884 original logical SLUS rows.

The proposed `ledger/splits/slus.jsonl` is the full candidate projection, not
a hand-edited subset. Its 869 semantically unchanged rows retain their baseline
line bytes; only the 15 changed recipe rows are reserialized in baseline field
order. The proposed `ledger/rows.jsonl` is the complete
6,767-row registry from the private census fixture, preserving existing
`cfg_corrected` annotations and the town `--aspsx-version=2.60` override.
Exactly 15 SLUS recipe rows differ from the current registry; all other row
records and all logical source identities remain the same. The ledger source
receipt is `work/native_lane/gp_partition_only_tools/census_fixture/census_setup_receipt.json`.

The workflow appendix in `docs/SLUS_MODULES.md` is the existing production
document byte for byte, followed only by the partition-only section from the
reviewed private candidate. It explains the original collector row identity,
physical closure, data ownership, and the absence of collector placement credit.

The assembler CLI and package bytes are the guarded generic candidate at
SHA-256 `d3e6ec7d...` and `28e45bbc...`. The seven regression-test updates are
the independently proven set in
`docs/evidence/gp_partition_only/assembler_tests/receipt.json`; its
`golden_delta.patch` documents the six removed stale extern metadata lines
and no other golden change. The new two portable tests and the other nine tool
files passed a single-interpreter **187/187** candidate regression. The
guarded assembler plus revised tests passed **418/418**. The ready29 generated
full-SLUS rehearsal built all 860 C objects with the guarded assembler and
matched the retail image/SHA1, 29 selected functions/1,949 genuine words with
zero masks, and 70 linked data records. These proofs remain private evidence;
the patch itself grants no production ownership certificate or placement.

The four source-hygiene items are completed in this payload:
`w_80041AB0.c` and `w_8004AB7C.c` have corrected comments;
`gp_d92c_owned.c` drops unused `FLAGS_PAGE`/`BASE_PAGE` macros; and
`w_8003FAD4.c` drops unused `pool_page`. Each intermediate revised source was
compared against the frozen ready29 source using the same CDK compiler at
`-S -O2 -w`; the raw assembly files are byte-identical, with no normalization. The private
`inputs/source_hygiene/` package retains the original probe and receipt,
before/after sources, and both assembly streams. The independent `reproduce.py`
compiles the saved before/after sources into separate output directories and
verifies them against the original receipt; its `reproduction_receipt.json`
pins the GCC driver, `cc1`, all private include-header bytes, and both assembly
streams. Use this reproducer for a fresh check: the original probe referred to
the transition payload as its before source, which is now refined. `inventory.json`
records ready29 and refined source hashes, the shared assembly hash, and both
receipt locations. The D92C intermediate owner body is then moved to its
canonical row source, so its final aggregator source is the wrapper described
next.

The final `gp_d92c_owned.c` and `gp_order_bytes_owner.c` aggregators each
include their one declared canonical member body exactly once. The natural
candidate bodies now reside in `w_8003D92C.c` and `w_80049F68.c`. The
`inputs/canonical_sources/` package retains the frozen before sources, four
final sources, compiler assembly streams, probe, and receipt. At each owner's
exact CDK recipe, before/after whole-TU assembly differs only by one added
`.file 2` source metadata directive; all other instructions and directives are
byte-identical. `inventory.json` records both overlay stages and source hashes.
This establishes compiler-output continuity with ready29 but does not replace
the pending full 33-owner proof, census, and generated-build gates.

Before activation, review and apply the patch in an isolated worktree; run a
normal generated configure/build against the proposed complete pinned ledger;
refresh remaining derived views and caches; and run the production-bound SLUS,
overlay, ownership, and dependency census gates. Those follow-on gates are
explicitly pending here. No production files or commits were changed by this
preparation.
