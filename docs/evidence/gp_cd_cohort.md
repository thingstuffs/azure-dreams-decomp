# CD consumer group: one common compiler recipe

At production baseline `89b14658`, a private eight-function CD owner now matches
all **1,041 retail instructions**, with zero masked relocations, through both
the corrected generic assembler and genuine ASPSX 2.79. The compiler recipe is
`2.7.2-cdk -G32` at the normal `-O2`, with expensive optimizations enabled.
Production still has **189 dependency records, including 21 GP rows**. This
measurement has not activated the owner or changed the assembler default.

## The source repair

The [combined report](gp_cd_cohort/combined8/REPORT.md) and
[receipt](gp_cd_cohort/combined8/receipt.json) cover exactly E34C, E4FC,
E758, F240, F2A4, F368, F5AC, and F624, in retail order. Eleven initialized
small globals appear once in the owner. The proposed
[module](gp_cd_cohort/combined8/module.json) declares their exact scattered data
pieces; a single new `code2` partition moves only F240. The other seven members
retain their existing row identities.

- The driver and auxiliary state use observed prefix types with incomplete
  external arrays, replacing the old size-forcing padding. All prefix accesses
  select element zero; enclosing allocation sizes remain unknown.
- A shared 24-byte queue entry replaces competing private queue types. F2A4
  uses actual 32-bit payload accesses at byte offset four. This drops the old
  source's volatile pointer qualifier; all two payload loads and the store
  nevertheless match retail exactly. No historical volatile contract is claimed.
- F368's result aliases are bounded one-/two-byte access views instead of padded
  16-byte structs. Cross-symbol addresses use explicit 32-bit target-address
  arithmetic. The result object remains eight bytes; its save/restore remains
  four bytes. Existing E758 and F368 register pins are retained.
- D3 has one shared two-byte view. Existing E758 asm-named aliases remain;
  no new alias or pin was introduced to join the functions.

These are memory-access views, not claims that every declaration is an
independent historical allocation. Some overlapping views, external aliases,
and E758's computed dispatch scaffolding remain. The F624 source also retains a
stale size-related comment in the frozen candidate; it must be corrected before
production integration. This checkpoint grants no new ladder level.

## Why the common recipe works

Seven functions first matched together with `-fno-expensive-optimizations`.
F240's simple previous-entry expression produced 13 words instead of 12 at that
recipe. Explicit queue-base locals and a byte-address view did not fix it.

[RTL evidence](gp_cd_cohort/f240_rtl/REPORT.md) shows that constant-multiply
expansion reuses an accumulator pseudo without expensive optimization and creates
a fresh one with it. Instruction order first diverges at the first scheduler;
the live-range difference already exists in expansion. Available upstream GCC
2.7.2 source explains this through `preserve_subexpressions_p()` and
`expand_mult`; the precise CDK source is unavailable, so that source attribution
is limited to the upstream implementation plus observed CDK dumps.

Enabling expensive optimization makes F240's original expression exactly match
all 12 retail words through both assemblers. The same flag change initially
left only seven register-field differences in E758, all in the completion queue
lookup. A separate, locally scoped byte-offset accumulator for that lookup
restores the retail register roles. Reusing the earlier dispatch accumulator
instead changed the first dispatch block, so the final source keeps the two
lifetimes separate. The complete eight-function object then passes; no compiler
version sweep or assembler exception is involved.

## Placement and other prepared repairs

The [bounded E758 rehearsal](gp_cd_cohort/bounded_e758/receipt.json) independently
passes the generated full SLUS link and SHA-1 gate with the integrated data-piece
tools. All eight owned data symbols have their retail addresses and bytes, and
all 868 outside C objects are unchanged. That rehearsal uses the earlier bounded
E758 source, not this new eight-function owner.

The [ready18 refresh](gp_cd_cohort/ready18/REPORT.md) also passes on baseline
`89b14658`: 18 functions / 891 words are genuine- and retail-exact, 56 data records
match, 851 outside objects are unchanged, and the entire image is exact. It is a
selective private assembler rehearsal, not the global transition gate.

The [complete eight-function full-link trial](gp_cd_cohort/linked/REPORT.md)
now passes as well: 24 private owners, 863 physical outputs and 884 logical rows;
all eleven data pieces at their exact retail addresses; all 861 unaffected objects
unchanged; and all 22 remaining code2 functions / 224 words unchanged. Fresh
generic assembly, the actual linked owner, and genuine ASPSX each match all
1,041 words without masks. The full image and generated SHA-1 gate pass.
All 27 frozen input pins and the production snapshot agree before and after.

The [merged ready18+CD8 rehearsal](gp_cd_cohort/merged26/REPORT.md) also
passes: 31 modules, 858 physical outputs, 884 logical rows, and the full retail
image. All 26 selected functions / 1,932 words were freshly checked against
genuine ASPSX and retail, together with all 67 data records. Thirteen selected
translation units use the corrected generic assembler in this passing trial.

## Whole-SLUS generic audit and the final three functions

The [all-858 audit](gp_cd_cohort/all858/REPORT.md) rebuilt every active physical
SLUS C object with the proposed generic assembler. Only `code.o` and `code2.o`
changed measured instructions or relocations. Exactly three functions remain:

| Function | Remaining external small data | Instructions before / after |
| --- | --- | ---: |
| `func_8003F5D4` | `D_800814C8` | 3 / 4 |
| `func_8003F5E0` | `D_800814C8` | 3 / 4 |
| `func_80048DA0` | `D_80080B1B`, `D_80080B1C` | 11 / 13 |

No function set or allocated data payload changed. The other 856 objects have
equal canonical instructions, data, and relocations; 266 have raw ELF metadata
changes only. The generated link completes, but its image is 16 bytes longer
and fails SHA-1. This is an explicit failed global gate, not a completed transition.

[Direct probes](gp_cd_cohort/closure_archive.json) already recover all 17 retail
words in those three functions through both assemblers at their existing recipes:
2.7.2 for the C8 accessors and 2.8.1 for 48DA0. They define the three small data
symbols explicitly. The overlapping `D_80080B18` table stays an external address
view and gains no duplicate storage. These are isolated instruction proofs;
they do not yet prove the two proposed owners in the full linked build.

All three functions come from collector rows. The next tooling change will
support explicitly declared owners made entirely from collector fragments,
requiring incoming function coverage and full physical-owner genuine proof.
It must preserve collector identities and must not grant whole-row placement
from a fragment proof. After integration, repeat the global generic gate,
refresh dependency evidence, and complete the remaining transition gates before
the existing owner sign-off step. The overall goal remains active.

## Reproduction and archive

The current private workspace is `work/native_lane/gp_cd_contract/combined8/`.
Run its `probe.py` using the fidelity Python environment. Full-link work uses
`work/native_lane/gp_cd_cohort_link/`; the passing merged rehearsal is in
`work/native_lane/gp_ready26_cd/`, and the all-object audit is in
`work/native_lane/gp_all858_probe/`.

The [closure archive index](gp_cd_cohort/closure_archive.json),
[linked-proof archive index](gp_cd_cohort/linked_archive.json),
[cohort archive index](gp_cd_cohort/cohort_archive.json) and
[baseline rehearsal index](gp_cd_cohort/baseline_rehearsal_archive.json) bind each
archived file to its original path and SHA-256. Absolute home paths were scrubbed
in tracked text. Archived scripts preserve their original relative workspace
assumptions; restore them to those recorded paths before execution. Original
private helpers and sources are pinned by the retained receipts.
