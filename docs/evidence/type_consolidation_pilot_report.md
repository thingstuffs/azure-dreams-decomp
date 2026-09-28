# r78 type-consolidation pilot - report

Model: claude-opus-5-5[1m] (provider anthropic; codex.log). No edits to src/, include/, config/ or tools/, no git,
no landers. BUSY_ROWS untouched.

## Deliverables (this directory)
- `DESIGN.md`: the mechanism, the header layout, the naming rule, the two recovered types with per-field
  evidence, the measured hazards, and the scaling recommendation.
- `apply.sh` (+ `payload/`): `payload/include/shared/{dir_step,dungeon_status}.h` and `payload/names_add.tsv`
  (3 data alias rows).
  - Dry run: `preflight: 243 rows to land, 0 skipped`. The dry run takes no lock.
  - The real run takes `build_ovl/work/land.lock` and checks each row's src sha256 (stale or busy rows are
    skipped). It refuses any pin or scaffolding growth and any name or type collision.
  - It then writes the headers, names.tsv and the rows, runs `verify.py` on all touched rows,
    `mk_ovl_root.sh` + `gate_all.py --workers 8`, and `build_slus.sh -j 8` with `gate_slus` MATCH. Any failure
    restores everything (REVERTED).
- The gate runs in `build_ovl_gate` by default (LAND_ISOLATED=1, as land_lanes.sh does), so build_ovl, which the
  pin lanes score in, is never rebuilt. `--rows blk_sample_rows.txt` lands the 20-row block sample first when a
  smaller first gate is wanted. names.tsv is appended newline-safely.
- `cand/<container>/<file>.c` + `.base_sha`, and `cand/MANIFEST.tsv`: 243 verified rows (row, candidate, verified
  src sha, how).
- `results/final.jsonl`: the final verification of each candidate (cc1 listing through ccproc with the lane
  names table vs the pinned listing, plus the `verify.py` byte score).
- Evidence and tools:
  - `census/*.jsonl`: every access to the targets in the pinned listings, via `tools/census.py` + `tools/flow.py`.
  - `results/*.jsonl`: every measured pass.
  - `tools/{rewrite,check,drive,finalize}.py`.
  - `hand/blk/`: the hand-written natural spellings.
  - `hand/pin/`: the pin tests, not in the apply set.

## Target 1: direction step tables -> `dirStepX` / `dirStepY` (231 rows: dungeon 224, town 7)
| outcome | rows | spelling / reason |
|---|---|---|
| exact, natural `short` array (`dirStepX[i]`) | 215 | includes rows that had declared `u16[]` |
| exact, view spelling | 10 | `((u16 *)dirStepX)[i]`: these rows' `lhu` feeds a compare or shift, so `short` gives `lh` |
| refused | 1 | dungeon/func_800B0770 (2.7.2-cdk, -G8): it declared `s8` (1 B, a small-data extern), so cc1 emits a `la` macro and retail matches that. With `short[8]` the row misses by 3. It keeps its local declaration |
| refused | 1 | dungeon/func_80D3CBF8 (2.8.1-G0): a `u8[16]` byte view; the cast view changes a register choice (9 differences) |
| not attempted (rewriter limit) | 2 | town/func_800C0D74 declares `s16 D_8006CCD8[][2]` (a pair view); dungeon/func_800C6C10 declares both tables on one line. Both are trivial hand edits and are not in the apply set |
| busy (not touched) | 2 | BUSY_ROWS |

## Target 2: the 0x80083460 block -> `DungeonGlobalStatus dungeonStatus` (size 0x20)
The rows that access 0x80083460..0x8008347F are all dungeon rows plus slus/w_80042BDC. Town touches only
0x80083498 / 0x800834B8, which are separate objects, so the "mixed containers" sample is dungeon + SLUS.

**Sample migrated (20 rows, all exact via verify.py; in the apply set)**

| row | cfg | retail pattern | spelling | notes |
|---|---|---|---|---|
| dungeon/func_80087A70 | 2.7.2-cdk-G0 | base | plain fields (hand) | local view `S80083460` removed; 0x0C compared with an entity pointer, which is why it is typed `void *` |
| dungeon/func_800881EC | 2.7.2-cdk-G0 -fno-schedule-insns | base | plain field (hand) | `D_80083460[2] = D_80083460[2]*2` becomes `unk_04 = unk_04 * 2`; the automatic view cast missed by 3 |
| dungeon/func_8009612C | 2.7.2-cdk-G0 -fno-rerun-cse-after-loop | direct | plain field (auto) | also migrated for target 1 (both rewrites in one text) |
| dungeon/func_8009D47C | 2.7.2-cdk-G0 | base | plain fields (hand) + one `*(s32 *)&dungeonStatus.unk_08` | the one 32-bit read over 0x08..0x0B (the union site) |
| dungeon/func_800A05E4 | 2.7.2-G0 (macro) | direct | plain field (auto) | |
| dungeon/func_800A07D8 | 2.7.2-cdk-G0 | base | plain field (hand) | `D_80083460[5]--` becomes `dungeonStatus.unk_0A--`; the view cast missed by 3 |
| dungeon/func_800A1094 | 2.7.2-cdk-G0 | base | plain field (hand) | as above; the view missed by 6 |
| dungeon/func_800A42AC | 2.7.2-G0 (macro) | direct | plain field (auto) | |
| dungeon/func_800BC764 | 2.7.2-cdk-G0 | base | plain field (hand) | as above; the view missed by 6 |
| dungeon/func_800C23D8 | 2.8.1-G0 | base | plain field (hand) | the view missed by 6 |
| dungeon/func_800CED34 | 2.7.2-cdk-G0 | two direct symbols in one function | plain fields (hand) | separate luis are kept: the accesses are in different blocks |
| dungeon/func_80976E28 | 2.6.3-G0 (macro) | direct | plain field (auto) | |
| dungeon/func_80A71654 | 2.8.1-G0 | direct | plain field (auto) | |
| dungeon/func_80CC266C | 2.8.1-G0 | direct + base | plain fields (hand) | the local `u8 *global_state` alias and its view typedef are removed; `unk_0A` load+store forms the base itself |
| dungeon/func_80CE8CBC | 2.8.1 -G0 | direct | plain field (auto) | |
| dungeon/func_80F0C3B8 | 2.7.2-cdk-G0 | base | plain field (hand) | the view missed by 5 |
| dungeon/func_8125192C | 2.7.2-cdk-G0 | two direct | plain fields (hand) | needs `unk_0A` to be `short`: declared `unsigned short`, it misses by 1 (`lh`) |
| dungeon/func_81332EC0 | 2.7.2-cdk-G0 | two direct | plain fields (hand) | same |
| dungeon/func_818AAE60 | 2.8.0-G0 | direct | plain field (auto) | also migrated for target 1 |
| slus/w_80042BDC | 2.7.2-cdk -G16 | base | plain fields (hand) | local `S_80042BDC_83460` removed; the listing is identical, so no SLUS rebaseline is needed |

**Whole-population measurement (automatic, not landed; `results/blk_*_scored.jsonl`)**

| pass | exact |
|---|---|
| view mode (type-preserving casts) | 795 / 857 |
| plain-when-compatible, `unk_0A` unsigned | 786 |
| plain-when-compatible, `unk_0A` short (adopted) | 797 |

- Every row whose declarations map onto a field was exact (234/234).
- The 60 misses are all array/pointer-cast views: `u16[]` 27, `s32[]` 21, `s16[]` 4, `u8[]` 3, and a few
  others.
- 5 rows use a block symbol with no local declaration, and 1 view needs a hand edit.
- Hand natural spelling fixed 8 of 8 tried.

## Pins
Not a pin lane, so nothing was removed. Two rows show the type change can remove a pin:
- dungeon/func_800A065C (`ASM_KEEP(base)`, registered 2.7.2-G0 with -fno-schedule-insns*): the one-line
  `dungeonStatus.unk_0A += 1;` is exact at 2.7.2-cdk-G0 (with and without the -fno-schedule flags). The pinned
  text is not exact there (total 6).
- dungeon/func_800A4DA8 (`do {} while (0)` scaffold, pointer arithmetic, 2.7.2-G0): the natural spelling is exact
  at 2.7.2-cdk-G0; the pinned text misses by 7.

Both are rule-4b / 09-24 coherence repairs: the retail `la g` + `off($r)` form is the split-address fingerprint.
Land them with `land_coherence.sh`, with the struct in place. The texts are in `hand/pin/dungeon/`.

## Tool calls
About 155 tool calls, within the ~200 budget.
