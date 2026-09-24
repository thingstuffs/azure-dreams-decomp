# H28 interrupted-wave recovery (2026-09-24)

The owner's request was to pick up Claude's interrupted 67-function cleanup after
the compiler investigation. This is the H28 batch in `r77_h28_lanes.json`: dungeon,
town and main rows, not 67 SLUS rows. No compiler, assembler, scorer or gate was
changed. The existing recipe-fidelity preference remains natural C at the genuine
970404 CDK compiler first, fewer pins at the registered proxy second.

## Recovered work

Lanes h1-h8 had stopped without completion markers. Only h1 had a partial report;
h9-h16 had been prepared but had no measurements. Ten exact candidates were
recoverable from the first eight lanes. In particular, h1's report stopped before
its later `C98cdk_p27` exact result, and h7's actor candidate was staged only for
the registered cell even though the same text is also exact at CDK.

| Row | Original pins | Candidate pins | Source |
|---|---:|---:|---|
| dungeon/func_800C9858 | 28 | 27 | h1 `cells/`, exact `C98cdk_p27` in lab log |
| dungeon/func_81912154 | 16 | 15 | h2 `cells/` |
| dungeon/func_8009AE44 | 13 | 0 | h3 `cells/` |
| dungeon/func_800B5B84 | 10 | 0 | h4 `cells/` |
| dungeon/func_819611CC | 9 | 0 | h5 `cells/` |
| dungeon/func_8196B2F8 | 9 | 0 | h5 `cells/` |
| dungeon/func_80285A70 | 8 | 0 | h6 `cells/` |
| dungeon/func_80FD5000 | 7 | 0 | h7 `out/`, independently re-scored at CDK |
| dungeon/func_80CE83EC | 6 | 0 | h7 `cells/` |
| dungeon/func_8009F190 | 5 | 0 | h8 `cells/` |
| town/func_800B7CEC | 5 | 0 | new continuation, below |

The nine recipe candidates from h1-h8 landed through `land_recipe_move.py`, tag
`r77_h28_recovery`: **62 pins removed**, seven newly pin-free rows. All seven
affected windows matched (2,168 other windows were current). Staging and logs:
`work/native_lane/r77_codex_h28_recovery/`.

The actor and new town candidate landed under tag `r77_h28_final`, with both
affected windows matching (2,173 other windows current). The town-scene rebuild
took 245 seconds. Staging and logs: `work/native_lane/r77_codex_h28_final/`.
Together the eleven landings remove **74 pins**, with nine pin-free rows and two
partial reductions. Pin-free does not imply that
every other fidelity residue or module-placement requirement is resolved.

## New source fix: town/func_800B7CEC

The five-byte prefix already has a packed `Text5` declaration and the symbol
`D_800892DC`. Replace the pinned page calculation and separately pinned word/tail
loads and stores with `*(Text5 *)output = D_800892DC`. At `2.7.2-cdk-G0` this emits
retail's unaligned word copy plus signed tail-byte load without any copy pins.

That alone leaves aligned distance 3 (1 substitution, 2 indels). Initialize the
real loop counter before its entry test. CDK's final delay-slot scheduling then
uses `move $16,$0` in the `blez` slot, exactly as retail, instead of pulling
`andi $2,$20,1` from the later odd-remainder test. This reaches exact bytes with
zero pins. The declaration is not given a dead initializer: the assignment is
the loop's actual initialization. Stale pin commentary was removed.

Scoped evidence: `work/native_lane/r77_codex_h28_followup/prefix_cdk_dumps/`
contains both CDK assembly listings and jump2/dbr dumps. The earlier
`prefix_why.txt` used the registered 2.8.0 recipe and is **not** the evidence for
this CDK mechanism. The exact candidate is `prefix_clean_min.c`.

Measured alternatives: replacing the existing loop's marker-page expression with
the symbol directly leaves 2 aligned indels; holding a typed marker pointer
leaves distance 5; a compact `for` loop leaves distance 3. Those were not staged.
The landed candidate retains that existing unpinned marker-page expression.

## Verification and genuine assembler evidence

Every staged recipe candidate was independently scored against retail and checked
by `tools/fidelity/cell_retail_check.py` at its proposed recipe. All eleven are
retail-exact through maspsx, and their genuine ASPSX 2.67/2.77/2.79/2.81/2.86
objects agree with the scorer-exact maspsx object. Some direct relocation-resolved
comparisons contain masked relocations; these are covered by object equivalence
and the linked covering-window gate, not claimed as independently resolved.

`exact_versions` alone was never treated as trial-cell retail exactness. The
compact receipt `r77_h28_recovery_receipt.jsonl` preserves source hashes, recipes,
pin counts and both checks. Recipe changes and source hashes are also retained
in `ledger/recipe_trades.jsonl` and the two recipe-move sweep journals.

A fresh `aspsx_diff.py` run on all eleven registered rows confirmed their exact
source hashes, retail-exact maspsx output, genuine object equivalence and **zero
fired compatibility passes**. Their obsolete `maspsx_dependence.jsonl` entries
were removed: 237 -> 226. Row database and SLUS SHA-1 checks passed; the assembler
version, gate definitions and module-census recipes were not changed.

The regenerated workspace census is **3,110 pins / 770 rows**. Its drop from
3,185 includes this batch's 74 pins and a separate one-pin automatic landing on
dungeon/func_80AF1A80 (`r76_gemf_w_25`); that background result is not credited to
the H28 recovery. The background job's source and sweep-journal changes remain
separate from this batch.

## Queued-row measurement and next work

All 40 rows assigned to h9-h16 received an exact registered-text control, an
all-pins-erased listing comparison at the registered cell, and a retail byte
score of the erased text at CDK with the same flags. **0/40** became exact by
erasure plus compiler replacement alone. This is a bounded negative for those
texts, not a compiler limitation or a reason to park them. The hash-keyed results
are in `r77_h28_queued_screen.tsv`; detailed trials remain in
`work/native_lane/r77_codex_h28_followup/lab_log.jsonl`.

Continue h1-h8's unsolved rows from their existing dumps/candidates; their old
reports are incomplete. In the queued set, town/func_800B7CEC is now solved.
The other 39 queued rows still need source work. Useful measured entry points:

- `dungeon/func_80AC5F28`: erased CDK text, aligned distance 9 (5 subs, 4 indels).
- `dungeon/func_80D3D3B0`: erased CDK text, distance 10 (9 subs, 1 indel).
  The missing instruction is the call's separate `li v0,1`: CDK reuses the
  already-known `result == 1` in s3 for the fifth argument. Narrowing the local
  call constant to s16/u16/s8/u8 does not change that; narrowing `result` to
  s16/u16 leaves distance 12. Inspect constant equivalence at cse/reload next.
- `main/func_80013128`: replacing the pinned source page with `&D_80028064`
  leaves distance 11 with the one-trip block removed, or 10 with it retained;
  CDK rematerializes the address for the call and changes copy-register allocation.
  Inspect the address lifetime and call arguments before trying further spellings.
- `dungeon/func_81983138`: replacing the sprite page with `&D_800269EC` at either
  its definition or use leaves distance 14 (12 subs, 2 indels), compared with 18
  for erasure alone. The remaining register/copy differences need attribution.

Do not mark h9-h16 as completed model lanes: the broad check was a CPU screen,
and only the town prefix function received a completed source reconstruction.
The original 67-row cohort still contains 58 pinned rows after these eleven
landings; two of those have moved to CDK with fewer pins, and 56 remain at their
original proxy recipes.
