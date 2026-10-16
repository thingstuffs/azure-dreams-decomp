# r121 remnants continuation 2

This incremental package adds 277 complete ordinary C rows / 5,948 bytes:
225 TOWN / 4,884 B, 46 dungeon / 368 B, six MAIN / 696 B.
All 349 previous rows / 17,216 B and both earlier packages are preserved.
The cumulative lane delivery is 626 rows / 23,164 B. Review is pending.

Strict-kit measurements use the unchanged stock recipes: 2.7.2-cdk-G0 for the
common game/helper cohort and 2.6.3-G0 for the linked MAIN devkit cohort.
These were fixed before scoring; no per-row flag or toolchain fitting occurred.
Retail signatures of short leaf bodies do not independently distinguish compiler
versions. The recipe is cohort-compatible, not a compiler-attribution claim.

Every new source is compiled from ordinary C. Literal-address first passes
are preserved separately; admitted pointer accessors use symbolic objects,
counter helpers use bounded structs, and other leaf operations use normal
field dereferences. M2C_FIELD expands only to a typed C dereference. There are
no pins, volatile accesses, inline/whole-function asm, no-op dependencies,
masked words, assembler edits, byte patches, or runtime retail substitution
inside any new C body. Full compiler binaries and ELF function extents are
checked independently; window comparison sums are not unique coverage.

TOWN scene placement is derived independently of C equality from the existing
module header/loader receipt, with raw header and disc-descriptor words re-read
and checked against destination 0x80016000, sector count and disc LBA. New row
extents are inside the loaded sectors or already documented proven extent;
no previous bank is extended merely by adjacency. Dungeon empty callback
slots use existing static per-floor maps, promoting only exact sub-extents.
MAIN uses the independently j-solved linked devkit delta 0x80197000. Runtime
capture, native TU/storage closure and a new native certificate are not claimed.

The wrapper cohort admits only complete, independently delimited local leaf
callees whose control flow and delay slots establish live input registers and
return definitions, with no child calls or stack parameters. Sparse incoming
register sets and unresolved contracts are rejected. The 77 bounded callee
contexts and CFG audit are retained; 67 wrappers passed. MAIN imports were
cross-checked against existing definitions, with explicit 32-bit representation
casts where those definitions use integer address parameters. The initial five MAIN
sources were rescored after this audit. Import definitions are package guards.

Coverage residue is append-only. Old active unported events in processed queue
spans are deactivated, preserving history, then split into complete matched rows
and explicit remaining physical pieces. All 388 input items have a status:
261 resolved, nine partial, 109 open and nine delegated spans. The queue byte
partition is 5,384 matched C / 4,024 remaining here / 1,004 delegated bytes.
The difference between 5,384 queued bytes and 5,948 full C bytes is recovered
function context: 264 bytes beyond the queued MAIN tail, plus 300 bytes
of context from the other complete bodies, largely return/delay-slot words. MAIN’s final
64-byte remnant was recovered as a complete 328-byte function, using an
existing exact TOWN twin. Its five-byte constant is declared as an aligned
word-plus-byte object, avoiding the original scalar-overrun declaration.
The lineage fingerprint is neutral/insufficient for version attribution;
2.6.3-G0 remains the independently established cohort recipe. Main_boot was
freshly regated; all 223 other windows had complete fresh C projections
checked against their unchanged prior compiler manifests before retaining
the proofs. All 277 full ELF symbol extents were then reverified.

No new SDK assembly or data relabel is asserted. SDK-looking entries without
proven source/placement remain unported. Dungeon 0x8D1658 is a mixed packed-table
and 12-byte epilogue candidate; invalid disassembly alone does not prove its
accessor or justify relabelling the entire 72-byte span as data. Other tails
must be recovered with their full containing functions. Failure of the earlier
instance search is not evidence that a span is unique code or data.

func_800B7914 and all 28 ABI/placement holds are delegated to r121_hardholds
and excluded from this package's C work. This includes the seven 108-byte
callback groups, the 32-byte dungeon wrapper and the 216-byte TOWN counter
group present in the input queue. Their prior records/artifacts are unchanged.

Apply after delivery/ and delivery_continue/ using apply.py --root R --live.
--live --dry-run is read-only; dry-run wins. Guard drift must be reviewed and
rebased deliberately. Run row_db.py check, registry/export and the receipt's
production windows after installation. No git commits are created. Existing
dungeon_cd_control_d79c4 renewal and missing external-copy .git preflight
remain as previously documented. See the receipt for all per-row source,
recipe, placement, first-pass, strict-score and production-binary proofs.
