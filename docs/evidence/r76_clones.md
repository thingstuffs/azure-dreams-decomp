# Round 76: clone transfer made to pay (2026-09-23)

## Tools

- `tools/lanes/clone_families.py` (new): clone families over the CURRENT pinned rows (identifier-normalised
  line signatures, difflib ratio >= 0.9, union-find; 902 pinned rows -> 194 pairs in ~8 s on 12 processes).
  Per member: pins, macros, served lanes (`served.py`), every lane `out/` file for the row (one glob per row id),
  its pin count, whether its `.base_sha` is current, and with `--verify` whether it is byte-exact now; per
  family: exemplar lane pairs whose base is a clone (proof: landed / superseded / unproven), a representative
  (best byte-exact partial, else fewest pins, unserved first, shortest), and the representative's residue
  (macros + the "removing it ..." reasons). Writes `ledger/clone_families.jsonl`
  (schema `azure-clean.clone-families.v1`). `--stage-partials LANE` stages verified partials whose
  `.base_sha` went stale.
- `tools/lanes/clone_transfer.py`: aligner v2 (`--aligner v1|v2|both`, default both), composition (the remaining
  exemplars re-run on each exact text), `--transplant LEDGER` (every family member's current text, rewritten to
  the sibling's names, is an exemplar for its siblings), `--lanes-glob`, proof-ranked exemplars (deduplicated
  by (row, base, out)), parallel sibling finder, `--no-stage` for control runs. The JUDGE is unchanged
  (listing screen, then byte-exact verify; unscored-arm guard; unmapped address symbol refuses).
- Tests: `tools/tests/test_clone_transfer.py` (+8 v2/transplant cases), `tools/tests/test_clone_families.py`.

## Why v1 refused

Triage of the 55 non-exact records of `r73_h3_clones` (pin key = macro + pin line + neighbouring code lines):
only 15 targeted the same pin site as the exemplar's removed pin; 32 hit a site whose neighbourhood differs,
8 a different site altogether. Several "context does not align" refusals were hunks ALREADY APPLIED by an
earlier landing (`func_80AC5958`/`func_8102F674`: `result = object; result = (u8 *)result + 0x20`), which v1
could not recognise; the five `*054` rows (F17) are the other kind - their one pin, `ASM_KEEP(call_obj)`, is a
different site from the exemplar's, and no aligner reaches it. v2 therefore: works in code-line space (blank and comment-only
lines invisible); cuts the edit twice (3-line groups + bare changed runs, so two nearby pins can go alone);
locates a hunk through the code-line alignment or as an exact occurrence of its 2/1/0-line window nearest the
predicted position; reads numbers from the hunk's own lines and never refuses on a globally ambiguous number.

## A/B (same inputs: 618 exemplar pairs from 273 r5*/r6*/r7* lanes, 902 pinned rows, 56 siblings, no composition)

| aligner | exact rows | pins removed | on r73_h3_clones' siblings (those still pinned) |
|---|---|---|---|
| v1 (rounds 65-75) | 6 | 6 | 2 rows / 2 pins |
| v2 | 12 | 20 | 8 rows / 16 pins |

v2 is a superset of v1 (no v1-only row). v2-only wins: the F5 family (`func_80B1B010`, `80F0B2A8`, `80B6F204`,
`80B452F8`, `809CB224`, each 2 -> 0 from `r74_astra_a2`'s `func_80D91070`) and `func_80BCDBA8` 3 -> 2.
Journals: `work/native_lane/ab76_v1/`, `work/native_lane/ab76_v2/` (control runs, nothing staged).

## Staged (production run: both aligners + composition + transplant)

| lane | rows | pins | note |
|---|---|---|---|
| `r76_partials` | 2 | 4 | r70_kit_astra8's byte-exact outs for `func_80A170DC`/`func_80C1509C` (14 -> 12) had a stale `.base_sha`; re-based, LANDED |
| `r76_clones` | 15 | 26 | 26 exact steps over 19 rows: 15 lane exemplars (v2), 11 transplants (9 v2, 2 v1); 4 rows withdrawn (below) |
| `r76_clones3` | 4 | 6 | `func_809F90DC`/`80A0B0DC` 11 -> 10, `func_80A170DC`/`80C1509C` 12 -> 10, re-run with the scaffolding guard |

The first production run staged 6 candidates (4 rows in `r76_clones`, 2 in a `r76_clones2` re-base) on which
`while (0)` grew (a transplanted donor's barrier): the landing rule would have refused them. They were withdrawn
and the JUDGE now refuses any candidate on which a scaffolding kind of `land_lanes.sh` grows
(`scaffold_grew`), as does `clone_families.py --stage-partials` (plus the unscored-arm guard). Total staged:
36 pins (4 landed with `r76_partials`, 32 queued).

F0 (`func_80C1B09C` + 9) goes down by 1-2 pins on 9 of its 10 members (the r70_kit_sol6 move now transfers;
`func_80A050DC` gained nothing), F4 `func_80BC7BA8`
7 -> 2, F7 `func_80EE5000` 4 -> 1 (transplant of `func_80EDF000`), `func_80AD7000` 8 -> 7, `func_80BD3BA8` 7 -> 6.
Landing is automatic (`land_finished2.sh`).

## Model-lane targets (no transfer left; do not launch from here)

Projected pins after the staged lanes land; representative = fewest projected pins, shortest.

| family | rows | pins | representative (pins) | residue |
|---|---|---|---|---|
| F0 | 10 | 92 | dungeon/func_80C1B09C (9) | 6 ASM_REG, 3 ASM_KEEP, 1 KEEP_NV; reorders / register colouring (`$20 outer`, `$23 part`, `$8` constant) |
| F1 | 11 | 66 | dungeon/func_800D0360 (6) | 5 ASM_REG, 1 ASM_KEEP; reorders, statement across a call (the `func_80BD9084`/`80BC1084`/`80C8D084` group); no exemplar anywhere |
| F2 | 2 | 26 | dungeon/func_81888258 (13) | REG 4, KEEP_NV 4, MEM_BARRIER 4, SCHED_BARRIER 1; colouring, address form, copy count |
| F3 | 6 | 24 | dungeon/func_8097B5A8 (4) | REG 3, KEEP 1; address form, delay slot (the `func_809815A8` group) |
| F6 | 2 | 11 | dungeon/func_81334230 (5) | REG 4, KEEP 1; address form, constant rematerialised |
| F8 | 2 | 9 | dungeon/func_80FC3000 (2) | REG 1, KEEP 1; address form |
| F4 | 4 | 8 | dungeon/func_80BD9BA8 (2) | REG 1, KEEP4 1 |
| F10 | 2 | 8 | dungeon/func_818CEB58 (4) | REG 2, KEEP 2; address form, whole shape |
| F9 | 2 | 8 | dungeon/func_818690C8 (4) | REG 4; constant rematerialised, whole shape |
| F7 | 4 | 7 | dungeon/func_80EDF000 (1) | REG 1; delay-slot fill |

Every member of every family has been served at least once (`served.py`), so each target is a deliberate
`--repack` retry of ONE representative, with transfer (`--transplant`) to carry the result across the family.
All 26 families: 92 rows, 358 pins -> 324 projected (`ledger/clone_families.jsonl`).

## Landing (land_finished2.sh cycle after the runs)

`r76_partials` 2 rows / 4 pins landed; `r76_clones` 13 rows / 24 pins landed (`func_80AD7000`, `func_80BD3BA8`
were superseded by other lanes that landed more first: now 5 and 2 pins); `r76_clones3` 2 rows / 2 pins landed
(`func_809F90DC`, `func_80A0B0DC`), `func_80A170DC`/`func_80C1509C` reached the staged 10 pins through a
different text in the same cycle. Net from this round's clone work: 30 pins landed, 4 more reached elsewhere.
