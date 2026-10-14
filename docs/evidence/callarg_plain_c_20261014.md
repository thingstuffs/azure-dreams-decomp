# CALL-ARG plain-C reconstruction, 2026-10-14

## town/func_8096C508: pin removed

The function now uses ordinary early returns and direct calls with `object`.
The sole `ASM_REG("$4")` declaration and its pointer-copy assignments are gone.
The registered recipe remains `2.7.2-cdk-G0`.

The selection operation is expressed as four paths:

1. The active choice matches: write state 6 and its two timing fields, then return.
2. The alternate choice matches: store the alternate index, call the selection
   helper, write state 6 and its timing fields, then return.
3. Neither matches, but the active choice is occupied and the alternate is empty:
   store the alternate index, call the helper, write state 5 and clear field B,
   then return.
4. Otherwise: write state 5, clear field B, and return.

These are the original paths and effects. In particular, both selection-helper
calls still follow the index store and precede the state writes. The repeated
state writes belong to mutually exclusive paths; they add no executed work.

## Evidence and scope correction

The original pinned control matched; erasing its pin alone gave listing distance
8. Reconstructing the branches with explicit early returns reduced the distance
to 4. Duplicating the real final state writes into the second update arm gave
listing distance 0 and full byte-scorer `exact=true, total=0, subs=0, indels=0`.
The complete generated listing equals the pinned listing, avoiding ambiguity
from a scorer that truncates overlong output. Independent orchestration-lane
verification also reported MATCH for the 884-byte function.

After applying the candidate, the isolated TOWN gate completed successfully:
`town_deep_t8b_08ec` (1,108 bytes), `town_deep_t8b_044d9c` (144 bytes), and
`town_scene` (335,872 bytes) all MATCH; 708 other windows were up to date.
Receipts are in `ledger/gate.jsonl`, dated 2026-10-14 07:44–07:49 UTC.
The source and evidence are left uncommitted for the owner's landing.

The source does not preserve a disguised pointer copy through CSE. The argument
still comes from the ordinary object pseudo. The successful change instead
alters basic-block boundaries around the calls and their real continuations.
The duplicated tails survive through `.jump2` and `.sched2`; late `.dbr`
reorganization factors them back into the shared retail tail. Thus a final
assembly label does not imply that the same boundary existed during scheduling.
The lane's `EVIDENCE.md` records both call-site scheduler traces and the
intermediate/final tail shapes; `COMPILER_AUDIT.md` independently checks them.

This **supersedes the unconditional no-C claim** in the o14/o17 CALL-ARG analysis
for this row. Their argument-expansion and CSE observations explain the former
source shape. Their three-instruction-block scheduling premise does not cover
the reconstructed branches. Neither a hard register binding nor an opaque
value is necessary.

Scratch evidence:

- `work/native_lane/plain_callarg_c508_20261014/REPORT.md`
- `work/native_lane/plain_callarg_c508_20261014/cand/vK.c`
- `work/native_lane/plain_callarg_c508_20261014/lab_log.jsonl`
- `work/native_lane/plain_callarg_review_20261014/lab_log.jsonl`
- Landing journal: `ledger/sweeps/plain_callarg_c508_20261014.jsonl`.

## Other CALL-ARG row

`dungeon/func_800C7F80` remains a separate investigation. The C508 result does
not establish its solution, but it rules out treating local source-shape
negatives as a proof that all plain C is impossible.
