# Lost-compiler hunt B: gcc2 trunk snapshots from 1997-04 to 1997-08, built and bisected

This is a measurement (brief `work/fidelity/LOSTCC_B_BRIEF.md`). The owner approved the downloads and builds on
2026-09-24. Nothing under src/, include/, ledger/, config/, tools/maspsx, tools/gate, tools/build or toolchain/ was
touched, and no gate, landing or git command was run. Every compiler was built under `work/fidelity/lostcc/B/`.
It follows `fidelity_step1b_epilogue.md`, `fidelity_step1c_compiler_inventory.md`,
`fidelity_websearch_1997_compiler.md` and `fidelity_lostcc_A_sn_binaries.md`.

- **Tools.**
  - `tools/fidelity/trunk_bisect_report.py` produces every table below, with 7 tests in
    `tools/tests/test_trunk_bisect_report.py`.
  - `tools/fidelity/epilogue_model.py` gained additive fields: `psyq_s_sha` (a hash of the candidate's `.ent`..`.end`
    bodies), `psyq_s_equal_t272` / `psyq_s_diff_t272` (the candidate against our cell's output after the t272 rule)
    and `src_sha` (the row text). Its 7 tests still pass.
- **Data** (`work/fidelity/lostcc/B/`, git-ignored).
  - Build and run records:
    - `builds.json`: every build, with its SHA, SVN revision, tarball sha256, cc1 sha256, setup notes and donor-file
      hashes.
    - `run_labels.tsv`: which cc1 file each run label used.
    - `runs/<label>.jsonl`: one journal per cc1.
    - `report.txt`: the full report.
    - `matrix.tsv`: per-row results for every cc1.
  - Scripts:
    - `build_one.sh`, `setup_tree.py`: the build recipe.
    - `run2.sh`: the runner. It records git HEAD and a dirty-tree hash before and after every run.
    - `residue_diff.py`, `restore_order.py`: the residue classifiers.
  - Patches: `patches/r14412_law_epilogue.diff` (Law's change, extracted) and `patches/exp_blockage_after_sp.diff`.
  - Inputs: the downloaded tarballs (`tar/`) and the 39 built cc1s (`bin/`). The extracted source trees were
    deleted after the runs; `build_one.sh` recreates any of them in about 20 s.
- **Re-run.**
  - Build: `work/fidelity/lostcc/B/build_one.sh <sha> <label>`, about 15-20 s each at `-j8`.
  - Run: `work/fidelity/lostcc/B/run2.sh work/fidelity/lostcc/B/rows603.txt <label>=<cc1>`, about 2.5-4 min per cc1.
  - Tables: `python3 tools/fidelity/trunk_bisect_report.py`.

**"Retail-exact"** has the same meaning as in steps 1b and 1c and hunt A:
- The candidate cc1 is driven through the row's registered gcc driver, cpp and flags.
- Its output is assembled by **genuine ASPSX 2.79**.
- The result equals the row's maspsx object at its **registered** recipe. The gate proves that object retail-exact,
  and every one of the 603 journal rows records `maspsx_exact = True`.

This is not `aspsx_diff`'s trial-cell `exact_versions`. "t272" is step 1b's model of gcc 2.7.2's epilogue decision,
applied to text: it re-prints the filled `j $31 / addu $sp` block in reorder mode. "Twin" means the `.ent`..`.end`
bodies are identical (comments dropped).

**Row set.** The same 603 rows as step 1c: every row that was registered at a 2.8-era cell then. At run time (HEAD
`b250da6d`, then `9b762227`, a docs-only commit; no row text or cfg drifted in any journal) they split as follows:

| group | rows | what it is |
|---|---|---|
| cdk-exact | 440 | retail-exact at genuine-equivalent cygnus-970404. Step 1c's 424 are all still included |
| **H28** | **115** | step 1c's 131 epilogue-helper rows that are still at a 2.8-era cell. **37 are pin-free**; 78 carry `ASM_KEEP*` / `ASM_REG` / `asm` scaffolding |
| Hcdk | 16 | the other 16 of the 131, moved since step 1c to cdk with new natural C (`b250da6d`) |
| C20 | 20 | step 1c's controls: genuine-exact at their 2.8-era cell, not at cdk |
| nosplit | 6 | rows whose flags carry `-mno-split-addresses`, which cdk rejects |

## Headline

1. **Calibration: FSF trunk from April 1997 is an exact stand-in for the Cygnus tree.** r13838 (04-03) and r13861
   (04-11) were compiled with Cygnus's local default `-fno-exceptions`: cygnus-970404's `toplev.c` sets
   `flag_exceptions = 0` under "CYGNUS LOCAL EH off", while trunk sets it to 1. With that default:
   - both produce **bodies identical to cygnus-970404 on 593 of 593** compiled rows;
   - both are retail-exact on **440 of 440** cdk-exact rows, which includes step 1c's 424 of 424.

   As built, with trunk's own EH default, they are exact on 0 rows, because trunk emits exception regions for C.
   It stops doing so between 04-20 and 04-27. Among the files checked (`except.c`, `toplev.c`, `stmt.c`,
   `c-decl.c`, `c-lang.c`), the only exception-handling commits in that range are the 04-23 sjlj rework.
2. **No snapshot inside the window reproduces the target rows, and on natural C it adds nothing over cdk.**
   - The best in-window snapshots are r14288 through r14410 (06-22 .. 07-10), which are identical to each other on
     every row.
   - They reach **28 of 115** H28 rows, **16 of 16** Hcdk, **2 of 20** C20, **3 of 6** nosplit and **439 of 440**
     cdk-exact: 472 of 603 in all.
   - **All 28 of those H28 rows are pinned.** 22 of them come from one commit, r14287 (Kenner, 06-22,
     `combine.c` `force_to_mode`: "Don't do anything for a ASM_OPERANDS insn"). Every one of the 41 rows whose code
     changes there contains inline-asm scaffolding.
   - **On the 37 pin-free H28 rows, no snapshot from 04-03 to 07-10 is exact (0 of 37).**
3. **The first pin-independent change that retail needs came after the epilogue was deleted.**
   - It is r14536 (Kenner, 1997-07-27, gcc-2.8.0 `ChangeLog` "Sun Jul 27 12:09:02 1997": "expr.c
     (get_inner_unaligned_p): Deleted. (expand_assignment): Remove special-case of constant array. (expand_expr, case
     ARRAY_REF): Likewise").
   - Before r14536, and in cygnus-970404 (whose `expr.c` still has `get_inner_unaligned_p`), a constant index folds
     into the symbol: `%hi(D+16)` then `lbu 0($2)`. Retail has `%hi(D)` then `lbu 16($2)`.
   - That one commit turns **36 more H28 rows t272-exact (22 of them pin-free)**.
   - So retail has `expr.c` code from 07-27 or later, together with a return epilogue that FSF deleted on 07-11
     (r14412). **No FSF trunk snapshot has both.**
   - Hunt A showed that SN's released 3.7-line compilers stayed on 970404 through November 1997.
   - Together these say that the production compiler existed and has not been published: a post-July-1997 gcc2
     snapshot in which the return slot is not filled.
4. **A literal revert of Law's epilogue change is not rock solid.** Law's r14412 was reverse-applied to FSF 2.8.0 and
   2.8.1. Without the revert, our builds of both are body-identical to the production cells: 42 of 42 and 152 of
   152 rows.
   - The reverted compilers reproduce **163 of the 174** rows at those cells that the t272 model reproduces, and none
     that the model misses.
   - They also break **6 of the 13** C20 controls that plain 2.8.1 reproduces.
   - The losses come from reorg: branch delay-slot fills near the function end, and the `$31`-only epilogue-delay
     form. With the text epilogue, reorg decides these differently.
   - Retail keeps 2.8's RTL-epilogue decisions everywhere except the final return slot.
   - One experiment built 2.8.x plus a single `blockage` after the stack restore. Two measures:
     - retail-exact on **172 of the 174** t272-exact rows at 2.8.0 / 2.8.1 cells;
     - bodies equal to the t272 model on **190 of 194** rows at those cells.

     It keeps all 13 of the 2.8-era C20 controls. It misses the two `$31`-only-frame rows (`town/func_8047EA14`,
     `slus/code7`) that the t272 rule treats specially. It also misses one pin-free cdk-cell control,
     `slus/w_80059BC4`, where reorg fills the unblocked return slot with `move $2,$0`. So the slot must take no delay
     instruction at all, not only lose the teardown.
5. **The residue after the best builds.**
   - 2.8.1 with the revert leaves 34 of 115 H28 rows (9 pin-free), and 2.8.1 with the blockage leaves 30 (7
     pin-free).
   - **17 H28 rows are at 2.91.66 / 2.95.2 cells, and no text-epilogue build we have reproduces any of them.**
     These are egcs-era proxies.
   - Most of the rest are pinned rows whose C was tuned against a 2.8.x cell.

## Builds

The recipe is the old project's `build97` recipe, with the same configure line, CFLAGS and PSX target header as the
held 970802 build. It adds only host-side and era adaptations. None of them touches an RTL pass, `mips.c`, `mips.md`
or any other code-generation file:

- **Parser and hash tables.** The mirror's early history tracks no generated files, so they are regenerated.
  - `c-parse.c` comes from **bison 1.35**, built locally. Bison 3.8 rejects the 1997 grammar's untyped mid-rule `$$`.
  - `c-gperf.h` comes from gperf 3.1.
- **configure.** It is generated with **autoconf 2.13** from the tree's `configure.in` (from 1997-05-18), plus
  **autoheader 2.13** from 07-19.
  - Before 05-18 gcc's `configure` was hand-written and not tracked, so these trees use the one from the
    cygnus-970404 source tree we hold, with its SN `mips-sony-psx` case removed.
  - The mid-conversion `configure.in` of 05-18 to 06 needs `cross_overrides` and `build_overrides` preset to
    `/dev/null`.
- **Untracked host files.** `version.c` (a label only), `obstack.[ch]`, `getopt.c`, `stab.def`, `gstab.h` and
  `move-if-change` are copied from the cygnus-970404 tree. The `xm-linux.h` host headers are copied from the held
  1997-08-02 trunk tree.
- **Target header.** `TARGET_DEFAULT` keeps `MASK_SPLIT_ADDR` only where the tree defines it, which is from 05-01.
  Before that, `mips_split_addresses` is set unconditionally under `TARGET_GAS && optimize`, as in cygnus-970404.
  `ASM_OUTPUT_SECTION_NAME` takes the arity the tree's `varasm.c` calls.
- **Host link flag.** `-fcommon` is added for trees with tentative definitions in headers.
- **Proof that the adaptations are neutral.**
  - `r14412rev` was built with `-fcommon`. `r14410` was built without it and with different donor sources. The two
    are body-identical on 599 of 599 rows.
  - Our r14639 build is body-identical to the held 970802 trunk cc1 on 599 of 599 rows.
  - Our FSF 2.8.0 and 2.8.1 builds equal the production cells, as stated in headline 4.

Downloads: the gcc-mirror `codeload` tarballs listed below; bison 1.35 (`ftp.gnu.org`, sha256 `710d4fd9…`); Ubuntu
.debs for autoconf2.13, m4, bison and gperf (sha256 in `builds.json`).

| cc1 (label) | date | SVN | gcc-mirror SHA | tarball sha256 | cc1 sha256 |
|---|---|---|---|---|---|
| r13838 | 1997-04-03 | r13838 | 8bb196585a66 | f44dd8e6e13a9f6a | 6c76019a943ba88e |
| r13861 | 1997-04-11 | r13861 | 51a96571d69e | a46ef9191dd4b8c4 | 284415dd33096721 |
| r13947 | 1997-04-20 | r13947 | 388320a5709b | ea11c3ed8f6d3ed0 | 77d572716c53c225 |
| r13986 | 1997-04-27 | r13986 | b835c5b30e5e | 45cf5714d7aa3877 | feae7df97fe2fc25 |
| r14014 | 1997-05-03 | r14014 | 3f76745e0104 | 55ad08e722fd694e | f05a6528fbc03b96 |
| r14058 | 1997-05-09 | r14058 | 6f54921d6967 | eca1c4570c7c7c03 | 81fad0fc18f05ab3 |
| r14097 | 1997-05-18 | r14097 | eaf95893f87d | 7d811512a250da56 | f8e472dde7c92bdb |
| r14114 | 1997-05-24 | r14114 | 8efc7e64cfc2 | 195853d47e02e3e5 | b6c9dce9f3dc1cf9 |
| r14140 | 1997-05-30 | r14140 | b1f21e0aef20 | 03c1d1b143d61c1d | e8e5508faf74ec44 |
| r14173 | 1997-06-08 | r14173 | d75292760db1 | 839c591cef810e81 | 4108ffd695730c10 |
| r14247 | 1997-06-14 | r14247 | babae559e20a | c9efe68d7aa41f0e | 96498c9829ccf16f |
| r14249 / r14257 / r14267 / r14268 | 06-16 .. 06-21 | (bisect) | 119f2738a65c / c13210e90292 / a8136932ccc4 / 9d1cf1d98c0d | see `builds.json` | bd424e785c567793 / 34777c5adbabe671 / 5cecbebbf24b19d7 / eb2ba056564118d1 |
| r14286 / r14287 | 1997-06-22 | (bisect) | 1997cb46f733 / 132d20400815 | see `builds.json` | e3bccdfdcdda5b9f / c13dc451e1c28cdc |
| r14288 | 1997-06-22 | r14288 | 5a0609628119 | 75ec7dbe36caf5b6 | e618c5424b8204ff |
| r14361 | 1997-06-29 | r14361 | 38c1f2d7e6de | aa45c4dccd63271e | 12a07a04646c312c |
| r14393 | 1997-07-06 | r14393 | 114d6a82f062 | 94ff41547a3ca847 | 570fd358786a481b |
| **r14410** | 1997-07-10 | r14410 | 7a49a4fd7b45 | be55ba15b1a93746 | 64a587067966aa78 |
| r14412 (Law's epilogue change) | 1997-07-11 | r14412 | 1f2d8f510f4e | c641d8efe52a1663 | 9461af7e86e6d1f5 |
| r14427 / r14477 / r14479 / r14512 | 07-14 .. 07-21 | r14427 / r14477 / r14479 / r14512 | 9ddca353b96f / 4f286636c9e8 / cbfc3ad3450b / 866aa3b64b91 | see `builds.json` | 070b94e2ae395c27 / 577a165e782478a7 / 326cedbdf6e304db / 29a45cee1ac4fda4 |
| r14535 / **r14536** / r14541 | 1997-07-27 | r14535 / r14536 / r14541 | 95a086b10a85 / 08293addce3c / f0eebf28c40e | see `builds.json` | b0347f9d6c1c5c84 / efea46513d570ed8 / b28f8efbf26a1cab |
| r14639 | 1997-08-02 | r14639 | 50eb43cabc93 | c671fca7a071acd4 | 32dd2a1a3214b02f |
| r14412rev / r14536rev / r14639rev | | + reverse of `r14412_law_epilogue.diff` | | | 8a54264133263125 / fdcdb21f77209864 / e0f2fbd93d9f6d68 |
| rel280 / rel280rev / rel280blk | FSF 2.8.0 release (held tarball) | + revert / + blockage | | | 80fba6581d64998f / cf6a49e6ee3cc8d6 / ce49246a554745f1 |
| rel281 / rel281rev / rel281blk | FSF 2.8.1 release (held tarball) | + revert / + blockage | | | 2c4edb0eff6e206c / 26980626ed226503 / f611230324304a66 |

The April snapshots also ran through a wrapper that adds `-fno-exceptions` (`bin_wrap/`, labels `r13838noeh`,
`r13861noeh` and `r13947noeh`).

## Calibration (brief step 2): FSF trunk against cygnus-970404

| cc1 | compiled | bodies = cdk (all compiled) | cdk-exact: exact | step 1c's 424: exact |
|---|---|---|---|---|
| cygnus-970404 (our `2.7.2-cdk`, = PsyQ 4.1 per step 1c) | 593 / 603 | 593 | 440 / 440 | 424 |
| r13838 as built / with `-fno-exceptions` | 593 | 0 / **593** | 0 / **440** | 0 / **424** |
| r13861 as built / with `-fno-exceptions` | 593 | 0 / **593** | 0 / **440** | 0 / **424** |
| r13947 with `-fno-exceptions` | 593 | 591 | 440 | 424 |
| r13986 as built (EH regions for C gone) | 593 | 591 | 440 | 424 |

- **What the differences are.**
  - The only difference between April trunk and cygnus-970404 on this corpus is the exception-handling default.
  - cygnus-970404's CYGNUS LOCAL additions (regmove, which is off: `ENABLE_REGMOVE_PASS` is undefined; conditional
    execution; branch prediction; haifa) are inert for MIPS at our flags.
  - The source differences (`srcdiff_vs_cdk.txt`, for example `loop.c` 762 lines and `jump.c` 470) are mostly
    CYGNUS LOCAL blocks. The 593-of-593 body identity shows that none of them changes code on these rows.
- **Where the EH default stops mattering.** It stops between r13947 and r13986. Among the files checked (`except.c`,
  `toplev.c`, `stmt.c`, `c-decl.c`, `c-lang.c`), the only exception-handling commits in that range are Stump's 04-23
  sjlj exception-handling rework (r13968/r13969).
- **Errors, the same 10 rows for cdk and April trunk:**
  - `-mno-split-addresses` (6 rows);
  - `-fstrict-aliasing` / `-fno-gcse` (2 rows);
  - two front-end parse errors, from `__attribute__` and `asm "+"` (2 rows).

  From 05-03 the 6 `-mno-split-addresses` rows compile.

## In-window test and bisect (brief steps 3-4)

The snapshots fall into four groups with identical results inside each group. The full table is `report.txt`. The
entries are retail-exact counts, as emitted.

| snapshots | cdk-exact (440) | H28 (115) | H28 pin-free (37) | Hcdk (16) | C20 (20) | nosplit (6) | all (603) |
|---|---|---|---|---|---|---|---|
| r13838noeh, r13861noeh | 440 | 0 | 0 | 16 | 0 | 0 | 440 |
| r13947noeh, r13986 | 440 | 1 | 0 | 16 | 0 | 0 | 441 |
| r14014 .. r14247 (05-03 .. 06-14) | 440 | 6 | 0 | 16 | 0 | 3 | 449 |
| **r14288 .. r14410 (06-22 .. 07-10)** | 439 | **28** | **0** | 16 | 2 | 3 | **472** |

The step-3 answer for r14410 (07-10), the last text-epilogue trunk:
- **28 of 115** H28 rows (all pinned), 16 of 16 Hcdk, 2 of 20 C20 and 3 of 6 nosplit;
- on the controls, 439 of 440 cdk-exact rows. The one lost is `slus/w_80041CBC`, pinned, and it is lost at r14287.

Every multi-register return is the text epilogue (470 `text`, 0 `filled`).

Change points inside the window, each bisected to one commit or to the narrowest range:

| between | rows whose code changes | H28 gained | pin-free gained | cause |
|---|---|---|---|---|
| r13861 → r13947 (04-11 .. 04-20) | 2 (`dungeon/func_800969CC`, `func_800A172C`) | 1 | 0 | a commit in 04-12 .. 04-20, not bisected further; both rows are pinned |
| r13986 → r14014 (04-27 .. 05-03) | 0 bodies | 5 | 0 | the composite bank rows (`func_80E91000`, `_80E9D000`, `_80EA3000`, `_80EAF000`, `_80FA5000`, all pinned) lose one stray `.text` directive outside the bodies. The cause is section output (varasm / the section macro in the target header), not code generation |
| r13986 → r14014 | nosplit 3 rows compile and are exact | | 2 (`dungeon/func_800A4DDC`, `town/func_80813E14`) | Wilson's 05-01 `MASK_SPLIT_ADDR` / `-mno-split-addresses`. At cdk without the flag these rows miss retail by 2 and 76 words (`cell_retail_check.py --cfg`), so the flag is real |
| r14268 → r14287 (06-21 .. 06-22) | 41 (all contain asm scaffolding) | 22 (+2 C20) | 0 | **r14287** Kenner, `combine.c` `force_to_mode` returns early for `ASM_OPERANDS`. r14249, r14257, r14267, r14268 and r14286 were built and are all unchanged. This is a pin artefact: retail's original C had no asm operands |

No other week changes any of the 603 rows' bodies. Wilson's 06-16 and 06-21 `mips_expand_prologue` changes and his
06-20 `output_block_move` change are inert here.

**Decisive for the brief's step 4: no in-window snapshot reproduces any pin-free H28 row.** The best in-window
snapshot is r14288, and r14288 = r14361 = r14393 = r14410 on every row. Its gains over cygnus-970404 are, in turn:
- pinned rows (23: the 22 of r14287 and `func_800969CC`);
- section-directive rows (5, pinned);
- the 3 `-mno-split-addresses` rows, of which 2 are pin-free.

The last are the one natural-C sign that the source compiler is later than 05-01.

**Step 5's question, for the best in-window snapshot.** Does r14410 differ from the rows' registered 2.8-era cells
only in the epilogue?
- **On 28 of 115 H28 rows, yes.** Its bodies equal the cell's output after the t272 rule (`psyq_s_equal_t272`), and
  exactly those 28 are retail-exact. All 28 are pinned.
- **On the other 87 (all 37 pin-free rows among them), no.** The code itself differs; see the residue section for
  the classes.

## Past the window: what retail's code needs after 1997-07-11

The same 603 rows were run on snapshots from after Law's change, scored with the t272 rule. Their returns are filled
(470 `filled`).

| cc1 | H28 t272-exact | pin-free | C20 | all (t272) |
|---|---|---|---|---|
| r14412 (07-11), r14427 | 33 | 3 | 8 | 483 |
| r14479 (07-18) .. r14535 | 34 | 4 | 8 | 484 |
| **r14536 (07-27)**, r14541, r14639 (08-02) = held trunk 970802 | **70** | **26** | 13 | 524 |
| FSF 2.8.0 release (= production cell, 42/42 bodies) | 75 | 29 | 13 | 524 |
| FSF 2.8.1 release (= production cell, 152/152 bodies) | 86 | 31 | 13 | 541 |
| our registered cells (2.8.0 / 2.8.1 / 2.91.66 / 2.95.2) | 115 (by selection) | 37 | 20 | 582 |

Change points:

- **r14410 → r14412 (Law's own change): +5 H28 rows under t272, 3 of them pin-free** (`dungeon/func_80A49908`,
  `dungeon/func_81881F60`, `slus/code7`). These rows need the RTL epilogue's effect on reorg. All 5 are among the
  rows the literal revert loses (next section).
- **r14477 → r14479 (07-18): +1 pin-free** (`town/func_8047E1C0`). This is Kenner's r14478/r14479: `reload_cse_regs`
  is now called from `rest_of_compilation`, not from `reload`. r14477 was built to split the range.
- **r14535 → r14536 (07-27): 43 rows change, +36 H28 rows t272-exact (22 pin-free).** This is the `ARRAY_REF` change
  in headline 3.
  - `residue_diff.py` puts 35 of r14410's 87 H28 misses in the "constant offset folded into the symbol" class; 22 of
    them are pin-free. After r14536, 34 of the 35 are body-identical to the cell under t272.
  - cygnus-970404's `expr.c` has the removed code (`get_inner_unaligned_p` at line 4202). So the class is
    2.7.2-lineage behaviour that retail does not have.
- Nothing else in 07-11 .. 08-02 changes these rows.
- **After 08-02 we have only the 2.8.0 / 2.8.1 releases.** They add 5 and 16 H28 rows.

## The epilogue: would a single revert be rock solid? (brief step 5)

Law's r14412 touches only `mips.c`, `mips.h` and `mips.md`: 372 diff lines, `patches/r14412_law_epilogue.diff`.
Reverse-applying it:
- to r14412 gives a tree whose sources equal r14410, and a cc1 body-identical to r14410 on 599 of 599 rows;
- to r14536, r14639, FSF 2.8.0 and FSF 2.8.1 applies cleanly, with offsets only and no fuzz.

| at cell | rows | production cell, as emitted | t272 model (step 1b) | **2.8.x + revert (native)** | **2.8.x + blockage after sp restore (native)** |
|---|---|---|---|---|---|
| 2.8.0 | 42 | 12 | 37 | **34** (bodies = t272 model on 37) | **36** (40) |
| 2.8.1 | 152 | 58 | 137 | **129** (125) | **136** (150) |
| H28, all cells | 115 | 0 | 115 | 2.8.0: 71 / 2.8.1: 81 | 74 / 85 |
| C20 | 20 | 20 | 20 | 7 | 13 |
| all 603 | | 459 | 582 | 514 / 530 | 521 / 538 |

- **The revert never beats the t272 model, and loses 11 of its 174 exact rows at 2.8.0 and 2.8.1.**
  - The 11 are `dungeon/func_80A49908`, `main/func_800219C4`, `town/func_800B7CEC`, `dungeon/func_8009AE44`,
    `dungeon/func_800D1A48`, `dungeon/func_81881F60`, `slus/code7`, `slus/w_8004F330`, `slus/w_800557C8`,
    `slus/w_80059D1C` and `town/func_800AC54C`. 6 of them are pin-free.
  - Among C20 controls that plain 2.8.1 reproduces, it also loses `main/func_800219C4`, `slus/w_8004F330`,
    `slus/w_800557C8`, `slus/w_80059D1C`, `town/func_800AC54C` and `town/func_800C4508`.
  - The differences are all reorg decisions. The first kind is a branch delay slot that is filled in retail but not
    under the text epilogue (`beq … / move` in `slus/w_80059D1C`, `dungeon/func_80A49908`). The second is a branch
    to the return that becomes `j $L` (`town/func_800AC54C`). The third is the 2.7.2 `$31`-only epilogue-delay form,
    which puts a body instruction between `lw $31` and `j $31`; retail does not (`slus/code7`).

  The text epilogue removes the RTL return and the restores that reorg's liveness and fill logic see, and retail
  shows 2.8's decisions there.
- **The return slot itself is the only difference in 172 of 174 rows.** Adding one `emit_insn (gen_blockage ())`
  after the stack restore in 2.8.x's `mips_expand_epilogue` (an experiment, never a production compiler) does two
  things. It leaves 2.8's RTL epilogue and all reorg decisions in place, and it stops reorg from moving the `addu $sp`
  into the `j $31` slot.
  - This reproduces the t272 model's bodies on 40 of 42 and 150 of 152 rows, and all 13 of the 2.8-era C20 controls.
    It is retail-exact on 36 of 37 and 136 of 137 of the t272-exact rows.
  - It misses the two `$31`-only-frame rows, `town/func_8047EA14` (step 1b's control) and `slus/code7`. There retail
    keeps the slot filled when an instruction separates `lw $31` from `j $31`, which is the t272 rule's one
    exception.
  - Among the 440 cdk-exact controls:
    - `rel281blk` loses 3: `slus/code3`, which every 2.8.x build loses; `town/func_8047EA14`; and `slus/w_80059BC4`,
      which is pin-free and registered at cdk.
    - `rel281rev` loses only `slus/code3`.

    In `slus/w_80059BC4` the blockage stops the teardown, and reorg then fills the `j $31` slot with the return-value
    `move $2,$0` from before the restores. Retail (cdk's text epilogue) leaves that slot empty. So in frames that
    save more than `$31`, retail's return takes no delay instruction at all. That is gcc 2.7.2's
    `mips_epilogue_delay_slots` rule, and it is stronger than "do not move the teardown".
  - A compiler that reproduced the t272 model exactly would therefore need two things: no delay filler for the return
    in frames that save more than `$31`, and 2.7.2's epilogue-delay behaviour for `$31`-only frames, applied to 2.8's
    RTL epilogue. The maspsx helpers already model this.
- **Restore order agrees.** In all 126 rows at 2.8-era cells that have multi-register frames, the cell's RTL
  epilogue prints the restores as one contiguous block in 2.7.2's text order: `$31`, then the other saved registers
  from high to low (`restore_order_2x.json`). On a synthetic example, sched2 can interleave these under 2.8, but that
  never happens in these rows. So the restore order does not tell the two epilogue forms apart.

## Residue (brief step 5)

These are the H28 rows (115) not reproduced natively by each build, split by the row's registered cell. The
pin-free count is in brackets.

| build | residue | 2.8.0 | 2.8.1 | 2.91.66 | 2.95.2 |
|---|---|---|---|---|---|
| r14410 (in-window best) | 87 (37) | 13 (3) | 57 (28) | 5 (1) | 12 (5) |
| r14639 + revert | 50 (14) | 11 (1) | 22 (7) | 5 (1) | 12 (5) |
| FSF 2.8.0 + revert | 44 (11) | 2 (1) | 25 (4) | 5 (1) | 12 (5) |
| FSF 2.8.1 + revert | 34 (9) | 13 (1) | 4 (2) | 5 (1) | 12 (5) |
| FSF 2.8.1 + blockage | 30 (7) | 12 (0) | 1 (1) | 5 (1) | 12 (5) |

- **Across every text-epilogue build we made, 92 of 115 H28 rows (28 of 37 pin-free) are reproduced by at least
  one.**
  - The 17 rows at 2.91.66 / 2.95.2 (6 pin-free) are reproduced by none. They need egcs-era passes (for example
    code behind `-fno-gcse` / `-fstrict-aliasing`) that no 1997 gcc2 snapshot has. They are proxy-cell
    rows, not bisect residue.
- **r14410's 87 misses, classified** against the cell output with the t272 rule applied (`residue_r14410/`):

  | class | rows | first fixed at |
  |---|---|---|
  | constant offset folded into the symbol | 35 | r14536 fixes 34 |
  | different code (instruction count differs; 3 of them also differ in delay-slot fills) | 21 | 2 fixed by 08-02; the rest need 2.8.0 / 2.8.1 / egcs code |
  | register choice only | 8 | none by 08-02 |
  | order and registers | 8 | 2 fixed by 08-02 |
  | delay-slot fill count | 5 | 2 fixed by 08-02 |
  | order only | 5 | 1 fixed by 08-02 |
  | other same-opcode | 5 | 1 fixed by 08-02 |

  The 45 rows left after 08-02 are at these cells:
  - 2.8.0: 10. SN's genuine JP-4.3 2.8.0 plus t272 reproduces 9 of them (step 1c journal). That is gcc2 code from
    after 08-02, up to the 2.8.0 release.
  - 2.8.1: 18.
  - 2.91.66 / 2.95.2: 17.

  **34 of the 45 are pinned.**
- **Cell dependence.** Rows registered at 2.8.1 are best served by 2.8.1 plus a revert, and rows at 2.8.0 by 2.8.0
  plus a revert. No single reverted release covers both: 2.8.1 + revert misses 13 rows at 2.8.0, and 2.8.0 + revert
  misses 25 at 2.8.1. Each row's C was fitted against its own cell, and 70% of H28 is pinned. So much of this split
  reflects that fitting, not two historical compilers.

## Negative results and caveats

- **Pre-July FSF trunk does not supply the post-970404 code, at any date.** No snapshot from 04-03 to 07-10 makes
  any pin-free H28 row exact. The only natural-C gain is the 2 pin-free `-mno-split-addresses` rows from 05-01. This
  closes lead 1 of the web search, "a trunk snapshot close to 07-10 is the best stand-in", negatively.
- **As built, trunk's EH default makes every April snapshot miss every row (0 of 603).** The calibration therefore
  uses cygnus-970404's own local default. This is a documented difference between the two trees, not a tuning
  choice.
- The 5 composite-bank gains at 05-03 lie outside the function bodies (a `.text` directive). Whether trunk's
  `varasm.c` or our 4-argument section macro causes them was not separated. They are not code-generation evidence.
- **Runs that were superseded.**
  - The first batch (HEAD `b250da6d`, before the `src_sha` field existed) was re-run in full.
  - One docs-only commit (`9b762227`, hunt A) landed during the second batch. Every run records HEAD and a hash of
    `git status` for src/include/config/ledger (`logs/run_batch*.log`, all STABLE), and the report's drift check
    (row cfg and text against the reference journal) is empty.
- **A June bisect run.** The June bisect (r14249 .. r14287) ran on the 41 changed rows only (`runs_june/`).
- **Not done.**
  - The 04-12 .. 04-20 change behind the 2 pinned rows was not bisected further.
  - The gcc2 line between 08-02 and the 2.8.0 release (1998-01-07) is not in the mirror's default history, which
    becomes egcs after 08-11, so it was not bisected.
  - No egcs snapshot was tried for the 2.91.66 / 2.95.2 rows.

## Decisions for the owner

1. **Where the lost compiler comes from, and how strong the evidence is.** Retail needs gcc2 code from 1997-07-27 or
   later (r14536, 22 pin-free rows), from 07-18 (r14479, 1 row) and from the gcc2 line up to 2.8.0 / 2.8.1 (step 1c:
   SN 2.8.0 reproduces 9 of the 10 rows left at 2.8.0). It also needs a return epilogue that FSF deleted on 07-11.
   SN's released compilers show neither (hunt A).
   - **Recommendation:** record it as "a post-July-1997 gcc2 snapshot with an unfilled return slot, not held,
     probably SN or Cygnus-internal".
2. **A patched compiler: not the literal revert.**
   - Reverting r14412 on 2.8.x loses 11 of 174 exact rows (6 pin-free) and 6 of 13 controls. Its evidence is weaker
     than the t272 model's.
   - The one-`blockage` patch is retail-exact on 172 of 174 and keeps all 13 C20 controls at 2.8.x cells. It loses
     `town/func_8047EA14` and `slus/w_80059BC4` among the cdk-exact controls. The misses show what an exact patch
     needs:
     - the return in multi-register frames takes no delay instruction at all;
     - 2.7.2's `$31`-only epilogue-delay rule.

     If the owner wants a compiler rather than the maspsx model, that is the candidate: 2.8.x plus a two-condition
     epilogue patch, not the revert. It would then need a full tree measurement and sign-off.
   - **Recommendation:** keep the two maspsx epilogue helpers as the model of record, and label them as modelling
     this compiler's return slot. A patched cell buys nothing the helpers do not already give, unless the owner
     wants the model inside cc1.
3. **The remaining work is pinned rows, not compilers.**
   - 78 of 115 H28 rows carry asm scaffolding. The in-window "gains" were entirely pin interactions (r14287).
   - The 16 rows re-derived in natural C at cdk (`b250da6d`) show that some H28 rows are cdk rows written for the
     wrong cell.
   - **Recommendation:** re-derive the pinned H28 rows in natural C at cdk, as that lane did, before any compiler
     work. The pin-free residue (9 after 2.8.1 + revert, 6 of them at egcs cells) is what is actually unexplained.
4. **The 17 H28 rows at 2.91.66 / 2.95.2 cells (6 pin-free).** No 1997 compiler reproduces them. They are
   egcs-cell proxies (step 1b decision 4). Treat them as a separate question: natural C at 2.8.x, or an egcs
   snapshot. Do not count them as bisect residue.
5. **Housekeeping.**
   - `tools/fidelity/epilogue_model.py` gained four additive fields in this lane. Hunt A noted that its runs
     overlapped the edit.
   - The build recipe can now rebuild any 1997 gcc-mirror snapshot in about 20 s. It is kept under
     `work/fidelity/lostcc/B/`: `build_one.sh`, `setup_tree.py`, bison 1.35, autoconf 2.13 and the donors.
