# Round 76: cascade list repair, generator catch-up, depth-2 composition (2026-09-23)

Pin sites before (STATUS.md at the start): **3,701 in 902 rows**.  After: see "Landing" below.

## 1. Cascade list repair

**The bug.**  `tools/lanes/cascade_extra.txt` was extended three times (72cbc693 t96/t97, 1ff6caea t98/t99,
49669ba5 t101/t102) with `sed 's/$/ tNN .../'`, which appends to EVERY line, comments included.  land_gap.sh read the
file with `grep -v '^#' | tr '\n' ' '`, so the six generators t96 t97 t98 t99 t101 t102 were passed ~17 times in
EXTRA_T and each swept ~17x per cascade pass (the comment copies were harmless; the 17 generator lines were not).
Generators t100 and t103-t117 were in neither list, although several have landed rows.

**Changes** (commits ecb2123d, f2ae066f, dd0dfb83):

| file | change |
|---|---|
| `tools/lanes/cascade_extra.txt` | header restored (plus a FORMAT rule: one per line, never `sed 's/$/...'`); one generator per line; t78-t87 removed (already in land_lanes.sh's built-in list, they swept twice); **added t100_rmwfold, t103-t117** |
| `tools/lanes/cascade_list.py` (new) | the ONE parser: strips `#` comments anywhere, drops duplicates (one warning per token with its count), drops tokens that are not `tools/xform/<tok>.py` and tokens already in land_lanes.sh's built-in `for T in ...` list, each with a stderr warning.  `builtin()` parses land_lanes.sh; `full()` = built-in + extras + t2_pins |
| `tools/lanes/land_gap.sh` | EXTRA_T from `python3 $HERE/cascade_list.py` (the grep is the fallback); installed by atomic `mv` (land_finished2 was running) |
| `tools/lanes/coherence_sweep.py` | default `--transforms` = `cascade_list.full()` (68 generators) instead of its hand-kept literal, which stopped at t87 (the literal is the fallback) |
| `tools/lanes/gen_drive.py` | `--catchup`: count as done every (id, in_sha) this generator already scored in its other lanes (`work/native_lane/*<gen>*`, not `_check`/`probe`, journals newer than the module file) and in `ledger/sweeps/<gen>.jsonl` (records whose `at` is newer than the module file) - a tree-wide catch-up then scores only rows whose text changed since |
| tests | `tools/tests/test_cascade_list.py` (repo file clean, sed corruption harmless, stray/built-in tokens dropped, built-in parse); `test_land_gap.py` (EXTRA_T deduplicated, corrupted list end to end); `test_gen_drive_flags.py` (`--catchup`); `test_compose2.py` |

Not edited: `land_lanes.sh` (the running lander re-reads it each landing; nothing needed changing), `land_finished2.sh`.

**Which generators joined, and why.**  Criterion: landed a row or reproduced an exemplar in the round-73 harvests
(`docs/evidence/pin_research_round73_move_table.md`): t103 1/2, t104 1/1, t105 2/2, t106 1/1, t107 2/2, t108 2/3,
t109 4/4, t110 4/7, t111 3/3, t112 1/4, t113 1/3, t114 1/1, t115 3/7, t117 3/7; t100 (round 72) 2/2.
**t116_ptaglink** (0/3 exemplars, never swept) was first left out; its catch-up sweep below found **2 exact rows in 21
eligible (12 s)**, both landed and gated, so it joined too (f2ae066f).  Cost note: the cascade now runs 30 extra
generators per pass; the expensive ones on a tree-wide sweep are t101 (0.6-1.1 CPU-h / 1,000 rows), t112, t115, t117,
t109 (0.6-0.9 CPU-h / 1,000 rows) - on a landing's few dozen changed rows this is minutes, not hours.

## 2. Catch-up sweeps (`gen_drive.py <gen> r76_cascade_<gen> --catchup --workers 8`, two chains)

"eligible" = the rows the last tree-wide sweep counted eligible; "scored" = rows scored now (changed text since the
generator last saw them, or never seen).  t101's old lane journal predates its last module edit, so it re-scored
everything eligible.  Wall time 18 min (t101 alone 11 min).

| generator | last sweep eligible | scored now | exact | pins | rows |
|---|---|---|---|---|---|
| t96_absplace | 94 | 5 | 0 | 0 | |
| t97_pagesym | 109 | 5 | 0 | 0 | |
| t98_paramcell | 131 | 7 | 0 | 0 | |
| t99_absmem | 267 | 12 | 2 | 2 | town/func_800BBD9C 8->7, dungeon/func_80084340 11->10 |
| t100_rmwfold | 52 | 21 | 0 | 0 | |
| t101_crossmerge | 289 | 546 | 2 | 2 | dungeon/func_81850800 12->11, dungeon/func_8195AB84 6->5 |
| t102_gotojoin | 788 | 45 | 0 | 0 | |
| t103_dropsink | 341 | 52 | 0 | 0 | |
| t104_pagejoint | 36 | 7 | 0 | 0 | |
| t105_headhoist | 190 | 30 | 0 | 0 | |
| t106_nmpromote | 57 | 7 | 0 | 0 | |
| t107_incstore | 34 | 8 | 0 | 0 | |
| t108_globalreg | 13 | 2 | 0 | 0 | |
| t109_voidret | 526 | 63 | 0 | 0 | |
| t110_paramfold | 208 | 28 | 1 | 2 | dungeon/func_813236DC 4->2 |
| t111_selfadd | 44 | 5 | 0 | 0 | |
| t112_deadhost | 790 | 103 | 0 | 0 | |
| t113_sibarity | 316 | 42 | 0 | 0 | |
| t114_zeroreg | 8 | 0 | 0 | 0 | |
| t115_carrierfold | 778 | 38 | 0 | 0 | |
| t116_ptaglink | - (never swept) | 21 | 2 | 3 | dungeon/func_81874F58 2->0, dungeon/func_818F30EC 4->3 |
| t117_stagehost | 683 | 39 | 3 | 3 | town/func_800CF814 2->1, dungeon/func_800AAF90 2->1, dungeon/func_80AC55DC 7->6 |
| t91_absfresh | 59 | 0 | 0 | 0 | (in the cascade since r66) |
| **total** | | | **10** | **12** | |

## 3. Depth-2 composition: `tools/lanes/compose2.py`

    python3 tools/lanes/compose2.py <lane> (--rows id@A+A,... | --near D) [--B cascade|a,b] [--k 3] [--base-from auto]
                                    [--min-pins N] [--skip-A gen,..] [--max-rows N] [--workers N]

Generic, no generator edited.  (1) Generator A runs with a verifier that always says "not exact" while every text it
hands to `screen.compile_s` is CAPTURED; the captured texts are ranked by listing distance to the ORIGINAL pinned
text's listing, and the k nearest that keep the unscored text, add no pin and **keep at least one pin** are the stage-1
candidates.  (2) Every generator B whose `eligible()` accepts a candidate runs on it with the real verifier - and with
`compile_s(row, candidate)` answered by the original text's listing, so B ranks by distance to the retail listing (every
generator computes its target from its INPUT text; without the substitution B would steer back towards A's inexact
output).  (3) An exact B result with fewer pins than the original is a win; the best per row is staged as an ordinary
lane (`out/` + `.base_sha` + journal), resumable on (id, in_sha).

**A structural limit, measured.**  A stage-1 candidate with NO pin left cannot be composed: every generator's `eligible()`
wants a pin site.  t110_paramfold's menu is whole-function plans only - all pin-free - so t110's three "needs a second
move" rows (80E0D090 d18, 80B9D094 d16, 818F33BC d6) have no stage-1 candidate from t110; the second move they need
(a cast / typed interface on already pin-free text) is not a pin-removal generator at all.  The same holds for every
`A-empty` row below (`pinfree_best` = A's best pin-free distance).

### 3a. The named rows (exemplar texts, `--base-from auto`, B = whole cascade + t66..t117 = 73 generators, k = 3)

42 rows, 118 stage-1 candidates, 2,397 (candidate, B) runs, 54 min at 6 workers.  **4 wins, all on pre-landing
exemplar texts that model lanes have since landed** (measurement only - their `base_sha` is not today's src/ text, so
the staged copies can never land):

| row | exemplar lane | pins | composition | the doc's diagnosis |
|---|---|---|---|---|
| dungeon/func_80BEE4EC | r73_opus_a6 | 3 -> 0 | t113_sibarity (d13) -> t77_symplace | "80BEE4EC d13 needs the symbol store" - reproduced |
| town/func_8032CE94 | r73_astra_a2 | 4 -> 0 | t108_globalreg (d4) -> t86_symaddr | t108 exemplar miss d4 |
| dungeon/func_80977E0C | r71_kit_astra9 | 7 -> 0 | t102_gotojoin (d2) -> t86_symaddr | t102 exemplar miss d2 |
| dungeon/func_8199AAD4 | r73_opus_p3 | 6 -> 4 | t86_symaddr (d5) -> t86_symaddr | H3-2 row "also needs a symbol move" |

Every win's second move is a **symbol spelling** (t77 / t86): the first generator's move is right but leaves an address
spelled as a constant, and the symbol generator refused or missed on the original text because the move had not been
made.  Distance table of the 38 misses (dA = A's nearest pinned stage-1 candidate; best B = the nearest retail distance
any B reached on any stage-1 candidate; `A-empty`/`A-refused` = no stage-1 candidate):

| row | pins (base -> src today) | dA | best B (distance, A, B) | no stage-1 from |
|---|---|---|---|---|
| dungeon/func_80E0D090 | 2 -> 0 | - | - | t110 A-empty (pin-free best 18), t36 empty, t84/t98 refused |
| dungeon/func_80B9D094 | 3 -> 1 | 16 | 16 t110 -> t102 | t84 refused |
| dungeon/func_818F33BC | 6 -> 0 | 28 | 6 t84 -> t63 | t110 A-empty (pin-free 6), t98 refused |
| dungeon/func_81886800 | 5 -> 0 | 11 | 11 t115 -> t107 | t110/t84 refused |
| dungeon/func_800C30E4 | 2 -> 0 | 14 | 18 t108 -> t37 | |
| town/func_800BF718 | 6 -> 1 | 3 | 5 t115 -> t63 | t107 refused |
| dungeon/func_80DE6884 | 3 -> 0 | 23 | 3 t78 -> t112 | t113 A-empty (pin-free 40) |
| dungeon/func_809F7320 | 3 -> 0 | 4 | 5 t86 -> t89 | |
| dungeon/func_800900F4 | 6 -> 0 | 9 | 3 t113 -> t89 | t86 refused |
| dungeon/func_8009F8EC | 4 -> 2 | 15 | 15 t113 -> t117 | t86 A-empty (170) |
| dungeon/func_80FB1000 | 4 -> 1 | 4 | 8 t117 -> t67 | t112 A-empty (16) |
| dungeon/func_80FF3000 | 4 -> 0 | 6 | 6 t117 -> t105 | t112 A-empty (19) |
| dungeon/func_81059F68 | 3 -> 1 | 12 | 10 t117 -> t89 | t112 A-empty (18) |
| dungeon/func_80094C70 | 4 -> 3 | 4 | 6 t117 -> t37 | t112 A-empty (56) |
| dungeon/func_8009DB44 | 2 -> 0 | 2 | 4 t117 -> t117 | |
| town/func_80813368 | 3 -> 2 | 16 | 2 t112 -> t37 | t117 A-empty |
| dungeon/func_800ACC98 | 3 -> 2 | 14 | **0** t111 -> t105 (listing-exact, byte-inexact) | |
| dungeon/func_80BC1528 | 13 -> 5 | 14 | 6 t103 -> t89 | |
| dungeon/func_81910EC0 | 2 -> 0 | 4 | 7 t116 -> t109 | |
| dungeon/func_818D4800 | 1 -> 0 | - | - | t116 A-empty (30) |
| dungeon/func_8182121C | 2 -> 1 | 24 | 29 t116 -> t37 | |
| dungeon/func_809A1D60 | 5 -> 0 | 24 | 26 t91 -> t63 | t16 A-empty |
| dungeon/func_809CB224 | 3 -> 0 | 0 | 2 t91 -> t37 | t16 A-empty |
| town/func_80091F04 | 5 -> 2 | 8 | 10 t91 -> t89 | t16 A-empty |
| dungeon/func_818761D8 | 7 -> 1 | - | - | t91 refused, t16 A-empty |
| dungeon/func_818D4A94 | 5 -> 0 | - | - | t91 refused, t16 A-empty |
| dungeon/func_80FB176C | 2 -> 0 | 7 | 15 t102 -> t90_far | t69 A-empty, t107 refused |
| dungeon/func_81031F30 | 2 -> 0 | 34 | 10 t69 -> t102 | t107 refused |
| dungeon/func_80CEBD74 | 4 -> 3 | 12 | 14 t102 -> t117 | |
| dungeon/func_800B8F90 | 7 -> 6 | 0 | 1 t101 -> t54 | |
| dungeon/func_80A1FBBC | 8 -> 7 | 0 | 2 t101 -> t63 | |
| dungeon/func_800C68F8 | 4 -> 0 | 8 | 3 t37 -> t37 | |
| dungeon/func_800C85AC | 4 -> 0 | 3 | 3 t37 -> t115 | |
| dungeon/func_80AC7A30 | 4 -> 2 | 2 | 2 t37 -> t93 | |
| dungeon/func_800BD0C4 | 3 -> 0 | 7 | 10 t89 -> t115 | t86 A-empty (48), t91 refused |
| dungeon/func_8197192C | 5 -> 3 | 4 | 12 t89 -> t101 | t91 refused |
| dungeon/func_8191740C | 1 -> 0 | - | - | t89/t86/t37 A-empty (12), t91 refused |
| dungeon/func_80E8F178 | 1 -> 0 | - | - | t89/t37 A-empty (22/18), t86/t91 refused |

The H3-3 compound abs rows (p2/p4/p5/p7: 818761D8, 80091F04, 818D4A94, 809A1D60) and the H3/H4 "t69 composed with
t102/t107" rows (80FB176C, 81031F30) are **bounded negatives at depth 2** with this generator set.

### 3b. The same named rows on TODAY's src/ text (11 rows still with >= 2 pins, full B set)

`r76_compose_named_src`: 0 wins in 11 rows (17 min).  The model lanes' landed partials moved these rows away from the
exemplar shapes (e.g. 800B8F90 / 80A1FBBC: t101 stage-1 at d2, best B t54_pagebase d2 / t115 d6; 80813368 t112 d16 ->
t37 d37).

### 3c. Near-miss rows on today's src/ (the journals of r73_h_t* / r73_h2_t* / r73_h3_t* / r76_cascade_t*)

`--near D` takes every journalled MISS whose in_sha is still the row's src/ text and whose nearest distance is <= D
(D <= 2: 356 rows, D <= 6: 623); `--min-pins 2` (a depth-2 win needs a pin for each move); A = that journal's generator.
t101_crossmerge is excluded as A (`--skip-A`): its menu costs ~200 listings a row and it was 85% of the first attempt's
wall time.

| run | rows | B set | stage-1 candidates | (cand, B) runs | wins | wall |
|---|---|---|---|---|---|---|
| `r76_compose_near` (D <= 6 first, stopped at 68 rows; then D <= 2) | 303 | the 9 symbol/page generators (t54 t59 t77 t86 t92 t96 t97 t99 t104) - the B of every 3a win | 1,324 | 2,100 | **0** | 45 + 13 min |
| `r76_compose_near_fullB` (D <= 1, first 40 rows) | 40 | whole cascade + t66..t117 (73) | 81 | 1,800 | **4 rows / 6 pins** | 34 min at 8 workers |
| `r76_compose_near_fullB2` (D <= 2, the rest) | 211 | 75 | - | - | RUNNING at hand-back (~3 h; lands itself via land_finished2) | |

The symbol-B negative on 303 rows says the 3a mechanism (a move that leaves an address to respell) is spent on today's
text: the landed tree has already taken those.  Best-B distance over the 303 rows: d0 8 rows (listing-exact,
byte-inexact), d1 30, d2 22, d3-9 49, >= 10 69 (the rest had no eligible B).

**fullB wins (staged in `work/native_lane/r76_compose_near_fullB`, landed below):**

| row | pins | composition | the move |
|---|---|---|---|
| dungeon/func_800C434C | 10 -> 8 | t103_dropsink (d1) -> t74_multiset | the `$17` copy of a parameter dropped (parameter renamed and used directly) + `x = (...) >> 9; x &= 7;` split |
| dungeon/func_80C42B74 | 2 -> 0 | t105_headhoist (d0) -> t85_allocorder | `wrapped_angle = angle` hoisted to the head, `angle` declared `s16` (signature change of a local static callee) |
| dungeon/func_80DF5054 | 3 -> 2 | t105_headhoist (d0) -> t37_localwidth | `final_arg0 = flags` hoisted, local narrowed to `s16` |
| dungeon/func_80DFB054 | 2 -> 1 | t105_headhoist (d0) -> t74_multiset | twin of 80DF5054 |

The t105 rows are the "listing-exact but byte-inexact" class: t105's head hoist is d0 on the cc1 listing and the byte
difference is a width / multiset move that no single generator makes on the original text.  Cost: the expensive Bs
are t51_sched_order (2,011 s over the 81 candidates), t72 (1,600), t67 (1,269), t101 (731).

## 4. Landing

All landings isolated (build_ovl_gate), GATE_RC=0, SLUS SHA-1 MATCH.  STATUS.md pin line: **3,701 in 902 rows** at the
start -> **3,585 in 879 rows** after `r76cmp` (the difference includes other sessions' lanes landed in the same window:
r76_partials, r76_clones*, r76_gemf_*, r76_opus_*/astra/sol6, t118/t119).

| landing | lanes of this round | rows / pins | STATUS after |
|---|---|---|---|
| fin0938 (land_finished2) | r76_cascade_t116, _t117, _t99 | 7 / 8 | 3,690 in 901 |
| fin1020 (land_finished2) | r76_cascade_t101, _t110 | 3 / 4 | 3,644 in 891 |
| r76cmp (`LAND_ISOLATED=1 land_gap.sh`) | r76_compose_near_fullB | 3 / 5 (80DFB054 skipped: stale base - another lane took it to 1 pin in fin1059) | 3,585 in 879 |
| **this round** | | **13 rows / 17 pins** (catch-up 10 / 12, composition 3 / 5) | |

Cascade cost of the new list, measured on fin1020's 23 changed rows (`ledger/sweeps/<T>.jsonl` timestamps): pass 1 of
t100-t117 took 3.3 min together, pass 2 seconds (journal-cached); the whole cascade was ~20 min, dominated as before by
the built-in t51 / t66.

## 5. Still running at hand-back

`r76_compose_near_fullB2`: compose2 with the full B set over the other 211 near rows (D <= 2, >= 2 pins, t101 not as A),
8 workers, est. 3 h+ (the first 40 rows took 34 min; these are larger).  It lands itself (land_finished2 globs r7[0-9]_*
and lands a generator lane when no process names it).  Journal: `work/native_lane/r76_compose_near_fullB2/journal.jsonl`
(resumable: rerun the same command to continue).  Expected from the fullB hit rate (4/40): ~15-20 rows.

## 6. Negatives and leads

* **Depth-2 needs a pin in the intermediate text.**  Generators whose menus are whole-function plans (t110, t113's
  arity rewrite, t112 / t117 on 1-2-pin rows, t116) hand no composable candidate; the second move those rows need is a
  NON-pin rewrite (typed interface, cast, symbol spelling on pin-free text).  A "pin-free polish" stage - the
  width / symbol / multiset generators allowed to run on pin-free text of a row that is NOT yet exact - is the
  natural depth-2 extension; it needs an `eligible()` that does not demand a pin site, i.e. a generator-side change.
* **The symbol-spelling second move is spent on today's text** (303 near rows, 0 wins with the 9 symbol/page B's),
  though it is the move behind all four exemplar wins.
* **Listing-exact, byte-inexact after composition**: 8 near rows reach d0 with a B candidate (town/func_800B50D4,
  800BB6A8, 8033077C, 8046F730; dungeon/func_8008F814, 80098378, 800B8C00, 8194D354) and dungeon/func_800ACC98 (t111 ->
  t105 d0 on its exemplar) - an assembler-level residue class, not a C-shape one.
* H3-3 compound abs rows and the "t69 composed with t102/t107" rows: bounded negatives (3a table).

## 7. Pin-free intermediates (`compose2.py --pinfree`, owner-approved 2026-09-23)

**The mode.**  §3's structural limit - a stage-1 candidate with no pin left cannot be composed, because every B's
`eligible()` / detector anchors on a pin site - is lifted by a shared hook, no generator edited
(`tools/lanes/residue_anchor.py`, commit d6a445ce):

* **Localiser = the -g listing diff.**  Both texts (the row's pinned text = retail, and A's pin-free candidate) are
  compiled by cc1 with `-g` (a localiser only; never the verifier).  Every cell's cc1 emits `.loc FILE LINE` (checked on
  2.6.3 / 2.7.2 / 2.7.2-cdk / 2.8.0 / 2.8.1 / 2.91.66 / 2.95.2); with the debug directives dropped the -g instruction
  stream equals `screen.compile_s`'s plain listing on **40/40** sampled rows.  `difflib` opcodes between the two
  instruction streams give the candidate's differing instructions and, through the `.loc` of the row's own file, their C
  lines (weight = instructions charged to the line; a retail-only block is charged to the lines flanking the gap).
  A residue on the function's `{` line (the parameter loads) falls back to the signature line.  When the listings are
  equal (d0 - the residue is past cc1) the anchor is A's own move (the C lines the text diff touches).  Cost: two cc1
  runs per stage-1 candidate.  Chosen over sched_map's `-da` RTL dumps (one compile per pass dump) and residue.py
  (fingerprints a diff but does not localise it to C).
* **Anchor = synthetic sites.**  The 6 heaviest residue statements become `("stmt", "RESIDUE", <statement>, start,
  end, line, "")` tuples.  `install()` patches the `sites_of` binding of every loaded tools/xform module (+ pin_sites,
  dead_init) to return them for exactly the registered text (the real census for any other text, so a B's
  "candidate has fewer pins" filter sees 0 < n), and `erase` / `erase_many` never erase a RESIDUE tuple.
  compose2's own win check and pin_census stay unpatched.
* **B = PF_B**: t36 t37 t94 (widths), t77 t86 t97 t104 (symbols / pages), t72 t74 (order / multiset), t118 t119
  (set-once / dead-init).  Win rule unchanged: B exact AND fewer real pin sites than the row's text (the landers keep
  the scaffolding-growth check).  Tests: `tools/tests/test_residue_anchor.py`, `test_compose2.py` (pin-free menu).

    python3 tools/lanes/compose2.py <lane> --pinfree (--rows id@A+A,.. | --near D) [--max-dA 20] [--anchors 6] ...

### 7a. Named rows (the 42 rows of 3a; t101 not as A: 800B8F90 / 80A1FBBC skipped)

`r76_compose_pf_named` (exemplar texts, `--base-from auto`, k = 3): 40 rows, **145 s** at 8 workers.  **3 wins, all on
exemplar texts that model lanes have since landed (measurement only, can never land):**

| row | pins | composition | the second move |
|---|---|---|---|
| dungeon/func_800900F4 | 6 -> 0 | t113_sibarity (pin-free d3) -> t37_localwidth | `var_s1` (an `ASM_REG` local) -> `u16`; 3a's best was t113 -> t89 d3 |
| dungeon/func_8191740C | 1 -> 0 | t89_lifetimesplit (d12) -> t118_setonce | `v = f(); v = (v >> 4) * g()` folded to one expression (x3); 3a: A-empty on every A |
| town/func_8032CE94 | 4 -> 0 | t108_globalreg (d4) -> t97_pagesym | page constant respelled `D_8001F8A5 + 0x10` (3a reached it with the pin kept, via t86) |

`r76_compose_pf_named_src` (today's src/, rows with >= 1 pin): **0 wins in 14 rows** (28 s).

Distance table of the named rows that have a pin-free stage-1 candidate (dA = A's nearest pin-free distance; best B =
nearest retail distance any PF_B reached; the other 23 rows have no pin-free candidate: A-empty / A-refused, as in 3a):

| row | pins | dA (A) | anchors | best B | PF_B eligible |
|---|---|---|---|---|---|
| dungeon/func_80E0D090 | 2 | 18 (t110) | 6 | 16 t37 | 5 |
| dungeon/func_80B9D094 | 3 | 16 (t110) | 6 | 16 | 4 |
| dungeon/func_818F33BC | 6 | 6 (t110) | 3 | 6 | 6 |
| dungeon/func_80BEE4EC | 3 | 15 (t113) | 5 | 11 t37 | 6 |
| dungeon/func_809F7320 | 3 | 15 (t113) | 5 | 9 t37 | 6 |
| dungeon/func_80FB1000 | 4 | 16 (t112) | 6 | 16 | 4 |
| dungeon/func_80FF3000 | 4 | 19 (t112) | 6 | 19 | 5 |
| dungeon/func_81059F68 | 3 | 18 (t112) | 6 | 13 t37 | 4 |
| dungeon/func_8009DB44 | 2 | 9 (t112) | 6 | 7 t118 | 7 |
| dungeon/func_81031F30 | 2 | 10 (t102) | 4 | 10 | 4 |
| dungeon/func_80977E0C | 7 | 16 (t102) | 6 | 15 t37 | 8 |
| dungeon/func_800C68F8 | 4 | 6 (t37) | 3 | 3 t37 | 2 |
| dungeon/func_800C85AC | 4 | 8 (t37) | 4 | 5 t37 | 2 |
| dungeon/func_80E8F178 | 1 | 18 (t37) | 6 | 18 | 4 |

**The three t110 rows are bounded negatives at depth 2 with PF_B.**  818F33BC shows why: its landed text (987d4397)
is t110's d6 candidate plus `held_*` retyped `s16` (t37 makes that move - it is in the menu) AND each
`bias = held - 0x10; pos += bias; dest = pos;` chain folded into `dest = (s16)pos + (s16)(held - 0x10);` - a
CROSS-VARIABLE statement merge with casts at the sum.  t74 only splits chains and t118 folds only a
SAME-variable `v = E; v op= F` chain (its 8191740C win); no PF_B menu holds this merge.  80E0D090 (t37 18 ->
16) and 80B9D094 (16, no B moved it) need moves of the same kind.

### 7b. Near rows (`--near 20`, nearest journalled miss first, t101 not as A)

`r76_compose_pf_near` (first 100 rows, 385 s) then `r76_compose_pf_near2` (the other 625, 1,983 s, resumed from the
first journal), then `r76_compose_pf_d0` (the 4 rows whose pin-free candidate was listing-exact, rerun with the
A-move anchor, 71 s).  **725 rows, 360 with a pin-free stage-1 candidate (dA <= 20), 3 wins / 3 pins, all on today's
src/ text:**

| row | pins | composition | the second move | lane | state |
|---|---|---|---|---|---|
| dungeon/func_80D3C944 | 1 -> 0 | t102_gotojoin (d1) -> t37_localwidth (also t112 d1 -> t37) | `old_x`, `old_x_early` `u8` -> `s16` | r76_compose_pf_near | landed: land_finished2 `fin1314` (with r76_astra_b8c_1), GATE_RC=0 |
| dungeon/func_81977FB8 | 1 -> 0 | t113_sibarity (d4) -> t37_localwidth | `height_or_shade` -> `s16` (t113: `func_8004491C` at its 2-argument arity) | r76_compose_pf_near2 | staged |
| dungeon/func_809DB054 | 1 -> 0 | t115_carrierfold (d0) -> t37_localwidth (A-move anchor) | `flag_bits` -> `u32` | r76_compose_pf_d0 | staged |

Distance table (per row: A's nearest pin-free dA; best B = nearest retail distance any PF_B candidate reached):

| band | rows by dA | rows by best B |
|---|---|---|
| 0 | 4 | 6 (3 wins + 80088964, 8008D69C, 80CC2828 listing-exact, byte-inexact) |
| 1-2 | 49 | 50 |
| 3-5 | 69 | 80 |
| 6-10 | 105 | 103 |
| 11-20 | 133 | 113 |
| no B eligible | | 8 |

A PF_B move got closer than A's own candidate on 73 of the 360 rows.  A generators that hand pin-free candidates
(stage-1 candidate runs): t112 548, t115 417, t109 211, t117 180, t102 177, t110 134, t113 56, t105 45, others < 35.
PF_B eligibility (candidate runs): t119 1,770, t37 1,523, t74 1,480, t94 1,022, t86 936, t77 474, t118 413, t36 168,
t97 71, t104 40, **t72 0** (its `runs()` wants an `ASM_` statement line by text - `PIN_LINE.match` - so a synthetic
anchor cannot reach it without a generator edit; t97's `t92.runs` and t118's pin-line tests are partly textual too,
which is why their counts are low).  Every exact B on a near row was **t37_localwidth** (7 exact runs on 3 rows; t119
once, on 809DB054, same text).

### 7c. Read

* **The hook works and is cheap** (40 min at 8 workers for 725 rows + 42 named), but the yield is thin: 3 landable
  pins in 725 near rows (0.4 %), all 1-pin rows, all a width second move (t37).  The width move is the only PF_B move
  that pays on today's tree; the symbol / page second moves that made every §3a win are spent (§3c), and paid here
  only on exemplar texts (8032CE94).
* **The named "needs a second move" rows need a statement merge**, not a width/symbol/order move: a "pin-free
  polish" of the PF_B kind does not reach them.  A generator that folds a CROSS-VARIABLE chain (`b = h - K; p += b;
  d = p;` -> `d = (s16)p + (s16)(h - K);`, narrowing casts at the sum) is the missing second move - the inverse of
  t74; t118 already folds the same-variable case (8191740C's win: `v = f(); v = (v >> 4) * g()`).
* Listing-exact, byte-inexact after composition: 80088964, 8008D69C, 80CC2828 join §6's assembler-level class.
* Not run: t101 as A (cost, as in §3c); rows whose pin-free candidates are beyond d20.
