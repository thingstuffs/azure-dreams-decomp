# Round 42: mechanize the copy repair and identify the remaining causes

Baseline: commit `cfbab7cd`, **6,071 pins in 1,279 rows**. The previous round
removed 27 pins through whole-object reconstruction and an actual return
contract. The user asked which parts can be mechanical. This round develops a
conservative fixed-copy generator and probe workflow, and audits its eligible
population before spending compiles on it.

## Reuse an existing source reconstruction

`town/func_800B0994` was a bounded negative at 2.8.1-G0: all four ordinary
68-byte aggregate spellings produced the same register mismatch. Reusing the
first spelling at stock CDK gives 21/21 exact words and zero pins. The pinned
source is also exact at CDK, so the established automatic cell transition
applies. The definite `open_shop` caller allocates a fresh node with enough
storage; an adjacent initializer independently types the exact 68-byte field.
Independent linked-strict verification and semantic/caller reviews pass. See
the [review](evidence/pin_research_copy68_review_20260917.md) and
[gate receipt](evidence/pin_research_copy68_20260917.json).
The standard `apply_candidates --cells` path has applied the one-pin repair;
the full 335,872-byte town scene window is byte-identical. SLUS SHA-1 also
matches and the row database passes. The gated census is **6,070 pins in 1,278
rows**, 33 removals since restarting the zero-pin objective.

The allocator dumps expose a transferable cause. Both compilers see identical
pointer lifetimes and global allocation order. CDK has already assigned the
block move's four scratch registers during local allocation, forcing source,
destination and end into a2, a3 and t0. GCC 2.8.1 leaves the scratch operands
unassigned until reload, after global pointers have occupied a1, a2 and v0.
A trusted debugger run rules out failed constraints and exhausted scratch
capacity. Compiler source identifies the change: CDK mutates instruction scratch
nodes in place; 2.8.1 records replacement registers in a side table and leaves
the instruction operands unresolved. See [the causal trace](evidence/pin_research_copy68_causal_20260917.md).
Plain 2.7.2 recovers the copy registers but rematerializes the preceding scalar
load address; CDK reuses the existing base. No further C spelling or compiler
patch was needed. Exact output does not establish a unique historical release.

## Population and automation boundary

Allocator kind 0x136 does not define the copy family. Most nearby routines
initialize fields in place or implement update callbacks. The only new named
copy, `8080E59C`, has a volatile source word requiring semantic review. The
bounded TOWN source audit finds no additional simple copy loop with an attached
keep or barrier beyond the earlier cohort. A DUNGEON inventory is a separate
extension, not evidence that the whole population has been exhausted.

Automatic recognition must establish a fixed contiguous extent, aligned
four-word transfers, matching pointer increments and a contiguous tail. It must
refuse calls, volatile accesses, uncertain residual pointer uses, runtime
alignment branches and disjoint source tails. Exact output still needs actual
source/destination review, source-hash binding and full affected gates.

The implemented tools are `tools/aggregate_copy.py` and
`tools/aggregate_copy_probe.py`; usage and promotion boundaries are documented
in [the workflow](PIN_RESEARCH_WORKFLOW.md#mechanical-fixed-copy-probes).
The CLI accepts at most five explicit rows and four explicit stock recipes per
row, including the recorded recipe. It preserves source hashes and unchanged
source controls, reports whether the input is live or historical, and leaves
all generated candidates unreviewed. It never changes source or recipes.

The five-row compiler pilot produced:

| Input | Mechanical result |
|---|---|
| Historical `800B0994` | One 68-byte candidate: exact at CDK, distance 17 at 2.8.1. Unchanged historical source exact at both. |
| Historical `800A23CC` | One 84-byte candidate: exact at CDK. This reproduces the earlier copy repair, not its later return repair. |
| Historical `8080E838` | Refused: copy scratch values are declared outside the recognized region. |
| Historical `8081DD70` | Same conservative refusal; its complete reconstruction remains a manual research result. |
| Current pin-free `808834DC` | One 52-byte candidate: exact at its recorded 2.7.2 recipe. Zero new pins removed. |

The [compact pilot receipt](evidence/pin_research_mechanical_copy_20260917.json)
retains source hashes and scores. The focused generator, probe and case-ledger
suite passes **45 tests**. This is a reproduction/control pilot, not another
removal batch. The two
historical initializer baselines are exact at their original recipes and miss
at their current reconstructed recipes; both old/current controls are retained.
The recognizer also refuses the actual alignment/disjoint-tail and volatile
cohort controls. Its lexical checks do not prove arbitrary C semantics or
header/preprocessor behavior; candidate review remains necessary.

## Hard cases provide discriminating evidence

Pair24 now has a recovered, symbol-bounded template and three more bounded
negative const/object probes. Direct address-use scanning did not find another
recognized use in the same image; indirect uses and original translation-unit
linkage remain open. More extern spelling has no demonstrated value.

The [small field initializer](evidence/pin_research_field_init_20260917.md)
`800BEA7C` loses its standalone payload pointer in
GCC 2.8.1's combine pass. A genuine owner-recovery expression restores all
registers and the 45-word length, leaving one base/offset substitution. The next
action concerns that combine decision, rather than a separate register-coloring
search.

The [group initializer](evidence/pin_research_group_init_20260917.md)
`8080E59C` reaches distance 19 with a six-word aggregate, but still retains three
loop keeps. Its unlocated helper and real alias relationship need evidence.
A dump of the pinned baseline is not retail RTL; it cannot prove that the
original compiler started from scalar operations rather than a block copy.

The [larger DUNGEON snapshot](evidence/pin_research_snapshot140_20260917.md)
`8008EE88` contains two 140-byte copies and 24 pins.
Ordinary aggregates plus stock CDK reduce a distance-158 probe to 40, but the
frame and second-loop address lifetimes remain wrong. A one-pin diagnostic
restores the frame and identifies the retained buffer page as the next question.
This source remains unlanded; no minimum or impossibility is claimed.
