# Toolchain fidelity STEP 1c: every compiler we hold, tested on the 2.8-era epilogue question

Measurement only (brief `work/fidelity/STEP1C_BRIEF.md`; follows `docs/evidence/fidelity_step1b_epilogue.md`).
Nothing under src/, include/, ledger/, config/, recipes, tools/maspsx, tools/build or toolchain/ was touched; no gate,
landing, sweep or git command was run; nothing was downloaded. Archives were unpacked into `work/fidelity/step1c/`
only and the unpacked images deleted after listing.

- Tools: `tools/fidelity/epilogue_model.py` (additive: `EPILOGUE_MODEL_OUT` / `EPILOGUE_MODEL_CC1` environment
  overrides so the `psyq` leg can run ANY cc1 - Windows PE under wibo, a host ELF natively, or a DOS/go32 cc1 under
  dosemu2 - plus `epi_forms()`, the return-form census of a cc1 listing, and a fix for a worker race when the cc1
  wrapper root is first built; step 1b's defaults and outputs are unchanged, its 7 tests pass);
  `tools/fidelity/step1c_report.py` (the tables below).
- Data: `work/fidelity/step1c/` (git-ignored): one journal per compiler (`<label>.jsonl`), `report.txt` (full
  tables), `cdk_exact_rows.tsv` (362 rows), `cdk_not_exact_epilogue_rows.tsv` (151 rows), `patched_builds_probe.txt`,
  the row samples (`sample_2x.txt`, `sample_272.txt`), the disc listings (`extract/en41_list.txt`,
  `extract/en43_list.txt`), copies of the tested binaries (`genuine_cc1/`), runners `run_all.sh` / `run2.sh` and
  their logs. Re-run: `bash work/fidelity/step1c/run2.sh` (about 6 min) then `python3 tools/fidelity/step1c_report.py`.

## Headline

**Have we tested every compiler we hold? Now yes.** Step 1b tested 10 of the 21 distinct historical or
reconstructed C compilers we hold. This step tests the other 11 and re-runs our cdk cell on every 2.8-era row: genuine SN 2.8.0 from the Japanese
4.3 disc, the three 1997 gcc2/egcs trunk cc1s the old project rebuilt, genuine PsyQ 4.0 and 4.1, and the five DOS/go32
compilers (SN16.3.7.0003, SN.1, GCC 2.5.7, GCC 2.6.0, and the non-SN 2.7.2 from DTL-S3040). It also probes the 13
patched research builds. No binary we hold emits both 2.8-era code generation and the unfilled (reorder-mode) return.

- **Every 2.8-era binary we hold post-dates 11 July 1997 and fills the return slot.** JP-4.3 `2.8.0 SN32 Build
  4.0.0007` (PE-linked 1998-02-17) and the trunk cc1s `testgcc-2.7.90 970802`, `egcs-2.90.01 970821` and
  `egcs-2.90.14 971023` fill **470 of 470** multi-register returns across 599 rows, with 0 text epilogues. All
  four trunk source trees (including the unbuilt 971101) contain Law's 1997-07-11 change: `define_expand
  "epilogue"` is enabled and `mips_epilogue_delay_slots` is gone.
- **The pre-July binaries print the text epilogue but mostly lack the 2.8-era code.** The one exception is the
  most important finding of this step. On **424 of 593** rows at 2.8-era cells, **the April-1997 Cygnus snapshot
  reproduces retail exactly** with genuine ASPSX 2.79 and no maspsx helper. That snapshot is genuine PsyQ 4.1
  `cygnus-2.7.2-970404 SN32.3.7.0004`, and it equals our decompals `2.7.2-cdk` cc1 on all 593 rows. The 424 include
  **360 of the 491 rows that carry the epilogue helpers** (328 of 454 `_maybe_unfill_return_delay`, 32 of 37
  `_unfill_via_load_delay`). So most of the "2.8-era codegen" these rows were assigned already exists in
  cygnus-970404. 151 rows are not exact at cdk. Of these, only **131 epilogue-helper rows need both** code
  generation later than 970404 and the pre-July text epilogue, which points to the unheld window 1997-04-12 ..
  1997-07-11. The other 20 are already exact as registered with the filled return. They date their code after
  970404 but do not need the text epilogue.
- **Rebuild fidelity closures:**
  - Our decompals gcc 2.8.0 equals genuine SN 2.8.0 Build 4.0.0007 on **193 of 193** 2.8.0-cell rows (identical
    `.ent`..`.end` bodies).
  - The genuine 4.1 cc1 equals our cdk on all 593 2.8-era rows (same exact set, same diff sizes and forms). This
    extends the old 5-TU proof.
  - Genuine 4.0, DOS SN16.3.7.0003 and the non-SN DTL-S3040 2.7.2 each equal our 2.7.2 cell on the 10 sampled
    2.7.2 rows.
  - `testgcc-2.7.90 970802` is **not** normalised-identical to 2.8.0 or 2.8.1 on the corpus: its bodies equal 2.8.0
    on 181 of 193 rows and 2.8.1 on 359 of 379. It sits between them. This refines the old project's 6-probe
    "970802 = 2.8.x" result.
- **No gcc source from the window is held offline** (item 3, below). "2.7.90" exists only as the label of the
  970802 snapshot. "2.7.91" occurs nowhere we hold.

## Method

The same harness and comparison as step 1b. For every row, the row's current source goes through the row's cell
driver and cpp, with the candidate binary substituted as cc1 (`epilogue_model.py --psyq` with
`EPILOGUE_MODEL_CC1`). The output is assembled by genuine ASPSX 2.79 in every mode aspsx_diff tries, and compared
with the row's retail-exact maspsx object, both as emitted (`psyq`) and after gcc 2.7.2's epilogue rule (`psyq_t272`).
Our own cell's cc1 runs alongside (`base`, `t272`). Two extra fields per row:

- `psyq_s_equal`: are the candidate's `.ent`..`.end` bodies identical to our cell's (comments dropped)? This is
  the codegen-twin test. It only means something for RTL-epilogue compilers: a text-epilogue compiler differs at
  every return by construction, so for those the exact counts are the measure.
- `psyq_epi`: the candidate's return forms. In functions that save a register besides `$31`, it counts `filled`
  (reorg's noreorder `j $31 / addu $sp`), `text` (2.7.2's reorder `addu $sp / j $31`) and `text_filled` (the
  teardown in the slot under a bare `.set noreorder`). `text_filled` is GCC 2.5.7's text epilogue, and in
  `$31`-only frames it is also gcc 2.7.2's epilogue-delay form `lw $31 / X / j $31 / addu`. The same three are
  counted for `$31`-only frames.

Scope:

- The 2.8-era binaries, genuine 4.1 and our cdk ran on **all 603 rows** at 2.8.0 / 2.8.1 / 2.91.66 / 2.95.2 cells.
  That is 2 more than step 1b's 601, because the registry grew.
- Genuine 4.0 and the five DOS compilers ran on a **68-row stratified sample**:
  - 44 rows at 2.8-era cells: 22 `_maybe_unfill_return_delay`, 8 `_unfill_via_load_delay`, 10 genuine-exact, 4 other;
  - 24 rows from step 1b's 2.6.3 / 2.7.2 / 2.7.2-cdk control sample.

  Their 2.7.2-or-older code generation fails the codegen leg on 2.8-era rows by construction, so the sample reports
  their epilogue form and codegen era separately.
- dosemu2 is available (`/usr/bin/dosemu`, 2.0pre9). Each DOS cc1 runs in its own directory with 8.3 names, about
  3 s per compile.

## Inventory: every C compiler binary held (both repos, every archive)

sha256 prefixes (16 hex). "Sibling" = the sibling decomp repo. C++ front ends (`CC1PLPSX.EXE`, `cc1plus`) are not
listed.

### Historical binaries

| # | binary / where held | sha256 | version string | runs via | lineage | tested on the epilogue question |
|---|---|---|---|---|---|---|
| 1 | `toolchain/compilers/gcc-2.6.3/cc1` (decompals; same in sibling) | f4391c56fe7c602a | 2.6.3 [AL 1.1, MM 40] Sony Playstation | native | FSF 2.6.3 + psx patch | 1b control (text epilogue) |
| 2 | `toolchain/compilers/gcc-2.7.2/cc1` | 0359379289db8e39 | 2.7.2 [AL 1.1, MM 40] Sony Playstation | native | FSF 2.7.2 | 1b control (text) |
| 3 | `toolchain/compilers/gcc-2.7.2-cdk/cc1` | 90db2db7bcfe3722 | cygnus-2.7.2-970404 SN32.3.7.0004 (SonyPSX) | native | Cygnus 970404 (= PsyQ 4.1) | 1b control; **1c all 603 2.8-era rows** |
| 4 | `toolchain/compilers/gcc-2.8.0/cc1` | f752a0865ae4b9e7 | 2.8.0 (mips-sony-psx) | native | FSF 2.8.0 | 1b (filled) |
| 5 | `toolchain/compilers/gcc-2.8.1/cc1` | 1a48ec5ac87a146a | 2.8.1 (mips-sony-psx) | native | FSF 2.8.1 | 1b (filled) |
| 6 | `toolchain/compilers/gcc-2.91.66/cc1` | ab7bacfde8c88dd7 | egcs-2.91.66 19990314 (egcs-1.1.2) | native | egcs | 1b (filled) |
| 7 | `toolchain/compilers/gcc-2.95.2/cc1` | 2aa85925dfa10855 | 2.95.2 19991024 (release) | native | FSF 2.95.2 | 1b (filled) |
| 8 | genuine psyq4.0 `CC1PSX.EXE` (sibling `toolchain/psyq/psyq4.0/`) | ddaa03030d1b0127 | 2.7.2.SN32.3.7.0002 | wibo | SN 2.7.2 | T5 sweep, old signature sweep; **1c sample: text epilogue, = our 2.7.2 on 10/10** |
| 9 | genuine psyq4.1 `CC1PSX.EXE` (psyq4.1; 4.1 CD `GNU/`) | 17b0d9dc6a80b2aa | cygnus-2.7.2-970404 SN32.3.7.0004 | wibo | Cygnus 970404 + SN | old 4.1 sweep (5 TUs); **1c all 603 rows** |
| 10 | **genuine JP-4.3 `CC1PSX.EXE`** (sibling `work/fable_endgame_20260811/hunt_280/jp43_bin/`, from DTL-S2340 `COMPILER/`) | 17081b8e39a92078 | 2.8.0 SN32 Build 4.0.0007 (PE 1998-02-17) | wibo | FSF 2.8.0 + SN | old signature sweep (4 probes); **1c all 603 rows** |
| 11 | genuine psyq4.3 (EN) / 4.4 / 4.5 `CC1PSX.EXE`; 4.3 ISO `GNU/`; 4.5 MFD `BIN/` | 26eb8259fa3e077d | 2.8.1 SN32 BUILD 4.0.0010 (PE 1998-06-09) | wibo | FSF 2.8.1 + SN | 1b all rows (filled) |
| 12 | 4.5 MFD archive (`_archives/rar45` = the MFD zip's `mfdpsx0N.zip`) `BIN/WIN/CC1PSX.EXE` | a24ed21b8d371ca5 | SN egcs-2.91.66 (PSX) | wibo | egcs + SN | 1b 2.91.66 rows (filled) |
| 13 | psyq4.6; `PSYQ_SDK.zip` `psyq/bin/`; `Psy-Q_46.zip` | 0755e509f148b601 | 2.95.2 19991024 BUILD 4.0.0030 | wibo | FSF 2.95.2 + SN | 1b 2.95.2 rows (filled) |
| 14 | DOS `CC1PSX.EXE`: 4.1 / 4.3 CD `GNU/DOS/`, JP-4.3 `COMPILER/DOS/`, 4.5 MFD `BIN/DOS/` | 6801fea8e7618f75 | 2.7.2.SN16.3.7.0003 | dosemu2 | SN 2.7.2 (16-bit host line) | old signature sweep; **1c sample: text, = our 2.7.2 on 10/10** |
| 15 | DOS `CC1PSX.EXE`: `PSYQ_SDK.zip` `psyq/psyq/` (RTL 3.5 / 3.6 discs) | d383902b6ed1a326 | 2.7.2.SN.1 | dosemu2 | SN 2.7.2 (first bundled, ASPSX 2.34) | old signature sweep; **1c sample: text** |
| 16 | DOS `CC1PSX.EXE`, Sony Programmer Tool ISO `Ps/Compile2/DISK1/` (sibling `toolchain/downloads/hunt_pre40/`) | eee20f31e5cf76b0 | 2.5.7 [AL 1.1, MM 40] (Apr 1994) | dosemu2 | FSF 2.5.7 + psx | old pre-4.0 hunt (1 probe); **1c sample: noreorder text epilogue, teardown in the slot** |
| 17 | DOS `cc1psx.exe` (gzip `CC1PSX.EXZ`), GNU C Compiler 2.60 floppy; same in ISO `Compile1` | 6587ed37f9f8795f | 2.6.0 [AL 1.1, MM 40] (Oct 1994) | dosemu2 | FSF 2.6.0 + psx | old pre-4.0 hunt; **1c sample: text** |
| 18 | DOS `CC1.EXE` (+ `GO32.EXE`), DTL-S3040 GNU disc | db0de4bb725dccc6 | 2.7.2 [AL 1.1, MM 40] (non-SN) | dosemu2 | FSF 2.7.2 + psx | old pre-4.0 hunt; **1c sample: text, = our 2.7.2 on 10/10** |

### Reconstructed from 1997 trunk source

Built by the old project for diagnostics, never used in production: `build_one.sh`, five host-only patches, psx
target registration.

| # | binary (sibling `work/fable_endgame_20260811/build97/bin/`) | sha256 | version string | runs via | tested |
|---|---|---|---|---|---|
| 19 | `cc1-970802-testgcc290` | 4559246f95c057cf | testgcc-2.7.90 970802 experimental | native (i386 static) | old 6-probe sweep; **1c all 603 rows** |
| 20 | `cc1-970821-egcs29001` | ff19514d0e09f480 | egcs-2.90.01 970821 (gcc2-970802 experimental) | native | old sweep; **1c all 603 rows** |
| 21 | `cc1-971023-egcs29014` | 28623f28e583207c | egcs-2.90.14 971023 (gcc2-970802 experimental) | native | old sweep; **1c all 603 rows** |

### Patched research builds

These are not historical. Each was probed on one TU (`work/fidelity/step1c/patched_builds_probe.txt`). The
2.8.1-based ones fill the return. The 2.7.2- and cdk-based ones print the text epilogue. None changes the epilogue
decision.

| sha256 (12) | banner | where (sibling repo or its worktrees) | return |
|---|---|---|---|
| d314f43f85b2 | 2.8.1 (mips-sony-psx) | `toolchain/i3_hold/gcc-2.8.1-i3hold/cc1` (i3 hold heuristic) | filled |
| 41f1b3f77276 | 2.8.1 (mips-sony-psx) | retired `gcc-2.8.1-sn0` (local-alloc noreturn patch), a worktree | filled |
| 5fe876a35305 | 2.7.2 [AL 1.1, MM 40] | retired `gcc-2.7.2-sn0`, a worktree | text |
| ed17e43c48f5, b3e7a91dcf8e | cygnus-2.7.2-970404 SN32.3.7.0004 | `toolchain/compiler-src/` cdk source build, `patches/cc1-oracle-all-blocks` (allocator trace) | text |
| 775d3f2fcd19, e47b40ac4f9e, 86884a0d5f07, 7b1421c95d31, 51570e5de69f, 40989b7e633f, 2929f458b233, c6fc9677d8b8 | 2.8.1 (mips-sony-psx) | `work/i3_81083694_20260821/`, `work/i3_allocator_pair_20260821/` allocator, tie, tail and address patches | filled |

### Checked and found to hold no additional cc1

- **Archives:** `Psy-Q_47.zip` and `psyq-4.7-converted-full.7z` hold libraries only. `PSYQ_SDK.zip` holds #13 and
  #15. Its Metrowerks `3RDPARTY/METROWER` directory has CodeWarrior libraries only; the CodeWarrior compiler is not
  held.
- **Discs:**
  - English 4.1 (DTL-S2002) and SCEE 4.3 (Nov 1998) discs, listed in full after unpacking: `GNU/` holds only #9 or
    #11 and #14.
  - JP-4.3 disc: `COMPILER/` holds only #10 and #14. Its `PSSN43.LZH` and `PSX43.LZH` hold tools and libraries, no
    cc1.
  - The pre-4.0 LZH sets (PSX/PSYQ 0125, 0314, 1020, 36jp) hold no cc1.
- **Other copies:**
  - The decompals tarballs in other worktrees are byte-identical to #2 and #3.
  - Sibling `work/compiler_repros` (one C file) and `work/i3_compiler_patch_lane` (README only) hold no binaries.
  - A sotn-decomp `cc1-psx-26.tar.gz.sha256` exists, but not the tarball.

## Results

`base` and `t272` = our cell's cc1. `psyq` and `psyq_t272` = the tested binary. All four are exact counts with
genuine ASPSX 2.79. "twin" = bodies identical to our cell's cc1.

| compiler | rows ok | twin with our cell | multi-reg returns filled / text / text-filled | $31-only returns filled / text / text-filled | base / t272 | psyq / psyq_t272 |
|---|---|---|---|---|---|---|
| JP-4.3 SN 2.8.0 (#10) | 599/603 | 2.8.0 **193/193**, 2.8.1 349/379, 2.91.66 0/8, 2.95.2 0/19 | **470** / 0 / 0 | 49 / 1 / 0 | 82 / 578 | 74 / 518 |
| trunk 970802 (#19) | 599/603 | 2.8.0 181/193, 2.8.1 359/379, 0/8, 0/19 | **470** / 0 / 0 | 49 / 1 / 0 | 82 / 578 | 74 / 524 |
| trunk 970821 (#20) | 599/603 | 2.8.0 120/193, 2.8.1 287/379, 0/8, 0/19 | **470** / 0 / 0 | 49 / 1 / 0 | 82 / 578 | 68 / 394 |
| trunk 971023 (#21) | 599/603 | 2.8.0 119/193, 2.8.1 284/379, 0/8, 0/19 | **470** / 0 / 0 | 49 / 1 / 0 | 82 / 578 | 68 / 391 |
| genuine psyq 4.1 (#9) | 593/603 | (text epilogue: see note) | 0 / **467** / 0 | 0 / 48 / 2 | 82 / 575 | **424 / 424** |
| our cdk (#3) | 593/603 | same as #9 in every measured field (593/593) | 0 / **467** / 0 | 0 / 48 / 2 | 82 / 575 | **424 / 424** |
| genuine psyq 4.0 (#8), sample | 63/68 | 2.7.2 10/10, cdk 1/10, 2.8.x 0/30 | 0 / 31 / 0 | 0 / 15 / 0 | 33 / 60 | 16 / 16 |
| DOS SN16.3.7.0003 (#14), sample | 68/68 | 2.7.2 10/10, 2.8.x 0/33 | 0 / 32 / 0 | 0 / 16 / 0 | 33 / 63 | 16 / 16 |
| DOS 2.7.2.SN.1 (#15), sample | 68/68 | 2.7.2 6/10, 2.8.x 0/33 | 0 / 32 / 0 | 0 / 16 / 0 | 33 / 63 | 11 / 11 |
| DOS GCC 2.5.7 (#16), sample | 68/68 | 2.7.2 1/10, 2.8.x 0/33 | 0 / 0 / **31** | 0 / 0 / 17 | 33 / 63 | 4 / 4 |
| DOS GCC 2.6.0 (#17), sample | 68/68 | 2.6.3 4/4, 2.7.2 8/10, 2.8.x 0/33 | 0 / 31 / 0 | 0 / 17 / 0 | 33 / 63 | 13 / 13 |
| DOS DTL-S3040 2.7.2 (#18), sample | 68/68 | 2.7.2 10/10, 2.8.x 0/33 | 0 / 32 / 0 | 0 / 16 / 0 | 33 / 63 | 15 / 15 |

Notes on the table:

- **psyq 4.1 and cdk are identical.** On all 593 rows they have the same ok set, the same exact set (424) and the
  same word-diff sizes and return forms. Their "twin" counts against our 2.8.x cells (44 of 593) are not a codegen
  measure, because every return differs by construction.
- **No tested binary beats our cells on any row.** In every journal there is no row where `psyq` is exact and
  `base` is not, or where `psyq_t272` is exact and `t272` is not. The one exception is cdk as emitted (below).
- **Why JP-4.3 scores 518 rather than 578 under `t272`:**
  - 55 of the missing rows are cross-generation rows at 2.8.1, 2.91.66 or 2.95.2 cells, where its code differs.
  - The other 5 are at 2.8.0 and have **identical bodies**. Four are step 1b's composite bank rows
    (`func_80E91000`, `_80E9D000`, `_80EA3000`, `_80EAF000`), where the genuine cc1 adds one `.text`. The fifth is
    `func_818E6800`, whose bodies are also identical, so its difference lies outside `.ent`..`.end`. None of the
    five is a code difference.
- **Errors, all recorded:** each run has 4 to 10 compile errors.
  - `-fno-gcse` and `-fstrict-aliasing`, which exist only from 2.91 / 2.95, on 2.8.0-era binaries.
  - `-mno-split-addresses`, which cdk and 4.0 / 4.1 reject: 6 rows.
  - `__attribute__` and `asm "+"` constraints that pre-2.8 front ends do not parse: `town/func_800B6A28`,
    `town/func_800B9B58`, `dungeon/func_8008EE88`, `dungeon/func_81071000`.
- **One reorder return from a 2.8-era compiler.** The single `$31`-only reorder return every 2.8-era binary emits
  is in `slus/code3`. It is a native gcc return, not a lead.
- **The two option lists match.** Option-name strings of JP-4.3 `CC1PSX.EXE` against psyq 4.4 and our 2.8.0 show no
  SN-added option; the only differences are binary noise. Step 1b's claim that no held compiler has an option giving
  the text epilogue on 2.8-era code therefore covers SN 2.8.0 too.

## The new finding: cygnus-970404 already is the compiler for most of these rows

This covers the 593 rows that compiled under cdk; the extra `-mno-split-addresses` and attribute rows are excluded.

| container | cell | rows | base | t272 | cdk / psyq 4.1 as emitted | t272-exact, not cdk-exact |
|---|---|---|---|---|---|---|
| dungeon | 2.8.0 | 174 | 5 | 172 | 138 | 34 |
| dungeon | 2.8.1 | 205 | 10 | 203 | 131 | 72 |
| dungeon | 2.91.66 / 2.95.2 | 2 / 7 | 0 / 0 | 2 / 7 | 0 / 0 | 2 / 7 |
| main | 2.8.0 / 2.8.1 / 2.95.2 | 3 / 9 / 1 | 2 / 2 / 0 | 3 / 9 / 1 | 2 / 5 / 0 | 1 / 4 / 1 |
| ovmovie | 2.8.1 | 5 | 2 | 4 | 4 | 0 |
| slus | 2.8.1 | 119 | 31 | 108 | 104 | 4 |
| slus | 2.91.66 / 2.95.2 | 1 / 3 | 1 / 2 | 1 / 2 | 0 / 1 | 1 / 1 |
| town | 2.8.0 / 2.8.1 | 13 / 38 | 8 / 13 | 12 / 38 | 10 / 29 | 2 / 9 |
| town | 2.91.66 / 2.95.2 | 5 / 8 | 2 / 4 | 5 / 8 | 0 / 0 | 5 / 8 |
| **all** | | **593** | 82 | 575 | **424** | **151** |

- **What is exact at cdk.** 362 rows are exact at cdk but not with our registered cc1 as emitted: 328
  `_maybe_unfill_return_delay`, 32 `_unfill_via_load_delay` and 2 others (`cdk_exact_rows.tsv`). For those rows the
  helpers are not needed at all: genuine 970404 cc1 plus genuine ASPSX gives retail as it stands.
- **What needs the unheld compiler.** 151 rows (`cdk_not_exact_epilogue_rows.tsv`) are exact with our 2.8-era code
  and the 2.7.2 epilogue rule, but not at cdk: 126 `_maybe_unfill_return_delay`, 5 `_unfill_via_load_delay` and 20
  already-exact rows. The **131 helper rows** are the only ones that need code generation newer than 970404
  together with the text epilogue. They are the target for the unheld snapshot and the bisect set. The 20 already
  exact rows need only the newer code, which any held 2.8-era compiler supplies. By cell the 151 are 89 at 2.8.1,
  37 at 2.8.0, 17 at 2.95.2 and 8 at 2.91.66. Their cdk distance is small, with a median
  of about 5 words.
- **The 2.91.66 / 2.95.2 rows are almost never cdk-exact** (1 of 27). Step 1b already marked them as the suspect
  cells.
- **Caveats.** The measurement drives cdk through the row's 2.8.x gcc driver and cpp, with the row's 2.8.x flag
  string. It uses genuine ASPSX 2.79, while PsyQ 4.1 shipped ASPSX 2.67; the old project showed 2.67 equals 2.77 on
  its 5 TUs. It is not the pipeline's `2.7.2-cdk` recipe run through maspsx and verify. A recipe move needs step 4's
  lander, which already moved 9 rows to the retail-proven splitting cell.
- **Why are 362 cdk-exact rows registered at 2.8.x at all?** There are two possible causes, and the lander tells
  them apart. Either (a) the rows were never tried at the cdk cell, because cell assignment stopped at the first
  2.8.x + maspsx match; or (b) the pipeline's cdk recipe gives different bytes from cdk + genuine ASPSX. The recipe
  differs in maspsx at its `--aspsx-version`, the cdk defaults (`-mgpopt`, `-fverbose-asm`) and the TU-level gate.
  If the cause is (b), that is a maspsx-vs-ASPSX fidelity gap on cdk output and a finding in its own right.

**Timeline.** The dates are consistent with PsyQ's own history:

- PsyQ 4.1 (Dec 1997) shipped exactly this snapshot.
- The old JP-vs-US study dated the relevant objects to November 1997 or earlier.
- The remaining 131 helper rows fit a Cygnus snapshot between 1997-04-12 and 1997-07-11. (The cdk source tree's newest
  ChangeLog entry is 1997-04-12; its version string is `cygnus-2.7.2-970404`.)

## Item 3: 1997 gcc sources held offline

| source | where | date / identity | epilogue by source | use |
|---|---|---|---|---|
| cygnus-2.7.2-970404 SN32.3.7.0004 | sibling `toolchain/compiler-src/gcc-2.7.2-cdk-SN32.3.7.0004/` | newest ChangeLog entry 1997-04-12 | text (2.7.2 `function_epilogue`) | the lower bound of the window; genuine Cygnus/SN source |
| FSF gcc-2.7.2.3 | sibling `toolchain/downloads/hunt_cygnus97/gcc-2.7.2.3.tar.bz2` | 1997-08-20, 2.7.2 branch | text (`mips_epilogue_delay_slots` present, epilogue expander commented out) | 2.7.2 codegen, not a 2.8 snapshot |
| trunk `testgcc-2.7.90 970802` | `hunt_cygnus97/gcc2-egcs_970802_testgcc290_861bb6c1b095.tar.gz` | git 861bb6c1, 1997-08-11 | RTL (Law's 1997-07-11 entry at `gcc/ChangeLog:631`) | built (#19) |
| trunk `egcs-2.90.01 970821` | `..._970821_e29001_f1e182826e4c.tar.gz` | 1997-08-21 | RTL | built (#20) |
| trunk `egcs-2.90.14 971023` | `..._971023_66724f0abd68.tar.gz` | 1997-10-23 | RTL | built (#21) |
| trunk `egcs-2.91.00 971101` | `..._971101_e29100_e9a25f70a0a7.tar.gz` | 1997-11-01 | RTL (`mips.md:6480` expander enabled) | not built: the old build stopped at `rtl.o` (host headers); post-July anyway |
| FSF 2.6.3 / 2.7.2 / 2.8.0 / 2.8.1, egcs-1.1.2, 2.95.2 | `toolchain/gcc-src/` | releases | 2.6.3 / 2.7.2 text, rest RTL | step 1b |

**Nothing between 1997-04-12 and 1997-07-11 is held in any form.** The only material inside the window is commit
metadata, not source: `hunt_cygnus97/_mail/c_1997-06-06.json` lists 16 gcc-mirror commits from 1997-06-06 to
06-08, for example `d75292760db1`. The old hunt notes that every day of that trunk can be fetched from the
gcc-mirror git history. Before 1997-08-11 there is no `version.c`, so the version marker is `toplev.c`
`version_string`.

## Verdict

- **Tested:** every historical C compiler binary held, 18 distinct; the three rebuilt 1997 trunk cc1s; and a probe
  of every patched research build. None emits 2.8-era code together with the unfilled return.
- **Tested on a sample only:** the six pre-4.1 binaries (4.0, SN16, SN.1, 2.5.7, 2.6.0, S3040). A full run is cheap
  (`run2.sh` with scope `all`) but cannot change the answer: they have 2.7.2-or-older code on every sampled 2.8-era
  row (0 of 30 to 33 twin, 0 exact).
- **Not tested, because not held as a binary:**
  - the 971101 trunk (source only, post-July);
  - gcc-2.7.2.3 (source only, 2.7.2 branch);
  - any PsyQ 4.2-era SN cc1 (no archive has one);
  - CodeWarrior for PlayStation (libraries only);
  - the 1997-04-12 .. 07-11 Cygnus trunk (not held at all).
- **What is left of the question** is narrower than step 1b stated. On 424 of 593 rows the historical compiler is
  plausibly cygnus-970404 itself, a binary we hold and have validated. Only 131 epilogue-helper rows need the
  unheld window snapshot. Another 20 rows need only code newer than 970404.

## Decisions for the owner / orchestrator

1. **Accept the inventory closure.** Every held compiler has now been tested. Optionally, catalogue the JP-4.3
   binary (#10) under the genuine toolchain as `psyq4.3jp`, which toolchain/ edits in this step could not do. The old
   project's follow-up also still asks for it to be recorded in its compiler notes.
2. **Recipe-move candidates (new, supersedes part of step 1b's route choice).** `cdk_exact_rows.tsv` lists 362
   rows (137 at 2.8.0 and 225 at 2.8.1 cells) that are retail-exact at cygnus-970404 with genuine ASPSX
   and no epilogue helper. Before any landing, run them through step 4's lander, which applies the cdk cell recipe
   with maspsx and verify. If they hold, the helpers' dependents drop from 496 to about 131 to 136, and route 1 (rebuilt
   reverted-epilogue cells) shrinks to those rows.
3. **Authorise a fetch of the missing snapshot, or not.** The prize compiler is a Cygnus trunk snapshot from
   1997-04-12 .. 1997-07-11. It can only be obtained by downloading gcc-mirror commits in that window and building
   them with the old `build_one.sh` recipe. Bisecting against the 131 helper rows would show whether a vanilla snapshot
   reproduces them natively. This needs internet access, which this step did not use. If declined, route 1 or
   route 2 of step 1b stands for those 131 rows only.
4. **The 2.91.66 / 2.95.2 cells (27 rows):** 26 are exact under t272, only 1 of them at cdk. As step 1b decision 4
   says, they are proxies. Their true compiler is most likely the same unheld window snapshot.
