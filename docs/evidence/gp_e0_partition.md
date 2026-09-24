# E0 list cursor: exact physical partition, pending provenance support

Status: **private architecture prototype, not a landable module**. The three
adjacent functions at 410FC, 41110 and 41134 form a small zero-terminated list
unit. Their current physical sources are `code2.c`, `code.c` and `w_80041134.c`,
respectively. Combining their existing operations with one real
`s32 *D_800814E0 = 0` definition gives all **44 retail words** through stock,
private generic and genuine ASPSX 2.79 at the existing 2.8.1 recipe. All three
comparisons are unmasked. This establishes a useful smaller physical unit
without merging the entire 20-row graph.

The [candidate](gp_e0_partition/candidate.c) normalizes the cursor's pointer
declaration across those functions; it adds no pins or padded data. It retains
the existing eight-word external array view at 83C68, without claiming the
original array's complete extent. The functions initialize its first word and
cursor, append a value and terminator, and remove the first matching value while
backing up the cursor. The cursor is observed through word loads/stores, and
its four retail zero bytes are at offset `0xaa0` of `assets/54240.bin`.

The [standalone receipt](gp_e0_partition/receipt.json) measures 5 + 9 + 30 words.
The [full-link receipt](gp_e0_partition/link_receipt.json) removes the two exact
function bodies from private copies of the collectors, puts the candidate at
41134's physical source, and carves actual four-byte `.sdata` storage. The full
524288-byte image matches retail SHA-256
`ae19d8d4bdd2db9a933b1e44d70dd61be670781e441d7cb37da85250a7aed31f`.
The cursor links non-absolutely at `800814E0` and all three function addresses
remain exact. A separate linked-context check confirms fresh stock, generic
and genuine objects equal the actual linked object and retail, zero masks.
All 19 production modules are preserved; production itself is unchanged.

## Why this cannot be silently integrated

The existing manifest/row model assigns each complete logical source to at most
one physical module. Its validation compares the member's declared functions
with the frozen raw row symbols. This prototype deliberately redistributes
functions from two collector IDs into 41134's physical source. The generated
link works, but the current whole-row membership check correctly refuses the
three-function claim for the original one-function 41134 row. The receipt
records that mismatch and `registry_compatible: false`. No certificate or
production dependency removal is justified by this experiment.

A current collector row is a recipe bucket, not evidence that all its functions
belong in one historical translation unit. The E0 example bridges `code` and
`code2` through only one function in each. Removing that artificial grouping
requires an explicit function-provenance model rather than relaxing membership
validation or silently discarding the parent IDs.

## Next implementation boundary

Design and test a partition record that maps each moved function to its original
logical row, canonical source fragment, physical owner and effective recipe.
Retain the frozen row provenance and account for each original emitted function
exactly once, including the collector remainder. Verification and fingerprints
must cover every physical unit contributing to an edited logical row, and
status must not count moved functions twice or award placement to an entire
collector from a partial proof. Reject missing functions, duplicate ownership,
unknown functions, recipe drift, and stale cross-file evidence.

Use this three-function unit as the bounded implementation pilot. Its only
per-function recipe change is 41110 from the collector's plain 2.7.2 to 2.8.1,
already byte-exact in the prototype; 410FC and 41134 remain 2.8.1. Once provenance
and negative checks work, rerun full retail/genuine/data gates before production
integration. Preserve the independent remaining dependencies in both collectors.
Do not merge all 20 rows solely because their collector IDs connect the graph.

Reproduction scripts remain in `work/native_lane/gp_e0_function_group/`:
`probe.py`, `link_probe.py`, then `confirm.py`. The final confirmation checks the
actual staged linked object and explicitly demonstrates the current membership
rejection. Source and extraction hashes are retained in the receipts.
