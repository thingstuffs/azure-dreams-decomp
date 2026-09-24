# Toolchain fidelity plan (owner-approved direction, 2026-09-24)

Status: **STEPS 1-2 RUNNING (2026-09-24 ~03:30Z; Opus agents, briefs docs/evidence/fidelity_step{1,2}_brief.md).** Was: planned - starts when the round-77 lanes still running at 2026-09-24 ~03:00Z (r77_opus_p5, p6, b1, b2, m8)
have finished and landed. No new pin lanes until step 2 reports.**

Goal (owner): byte accuracy AND cleanliness for every row. Principle: a row's recipe is the toolchain the original
was built with (compiler cell + flags + assembler version), and its C is what that toolchain needs to reproduce
retail. Pins or page constants that imitate a different toolchain are not clean, even when byte-exact.

Trigger: the round-77 Fable sceptic disproved the split-address "toolchain gap"
(`docs/evidence/r77_splitaddr_verdict.md`, lane `work/native_lane/r77_fable_splitaddr`): retail's split
`lui %hi / ... / addiu %lo` pairs come from the `2.7.2-cdk` cell, rows registered at non-splitting cells carry
page-constant pins imitating it, and maspsx has passes that imitate it in the assembler stage.

## Steps (in order)

### 1. Genuine-ASPSX differential over the whole tree (CPU, measurement only)
For every landed TU: the cc1 output of its registered recipe, assembled by maspsx (as the pipeline does) AND by
genuine ASPSX 2.56 / 2.67 / 2.77 (sibling repo `toolchain/psyq/psyq4.x/ASPSX.EXE` under `toolchain/bin/wibo`,
`-q -o OUT.OBJ IN.S`, CRLF, `.include`/`#APP` stripped; 2.56 cannot parse %hi/%lo). Relocation-resolved word
comparison (start from `work/native_lane/r77_fable_splitaddr/cands/pipe.py`, `aspsx_run.py`).
Output: per TU, which assembler version(s) reproduce retail, and every maspsx-vs-genuine difference attributed to the
maspsx pass that made it. Answers decisions 1-3 below with data instead of one row.

### 2. Split-fingerprint census in every container (CPU, measurement only)
Retail words showing cc1-level address splitting (HIGH and LO_SUM separated by other insns, LO_SUM into a register
other than its HIGH, a `lui` half in a delay slot, one `lui` shared by several accesses) cannot come from 2.6.3/2.7.2
non-split cells (their mips.c has no split_addresses path) nor from genuine ASPSX (never splits `la`). Scan slus AND
the overlays (the sceptic scanned slus only: 185/317 pin-free cdk rows show it, 6/364 pin-free 2.7.2 rows, all
maspsx-made). Add the fingerprint as an evidence column of `ledger/module_recipe_census.jsonl`.

### 3. Decisions (owner signs; recommendations as agreed 2026-09-24)
1. **maspsx cdk-imitating passes** (`_sink_call_separated_la`, `_split_funcaddr_la`, plus whatever step 1 finds):
   keep for now (removing them breaks exact rows); list dependents per pass; re-recipe the dependents (step 4);
   delete a pass once it fires on zero landed rows (byte-neutral, as the casesi patch was).
2. **ASPSX version per TU**: record the assembler version in each TU's recipe, as the compiler cell is, set to the
   version step 1 shows reproduces it (cdk output implies >= 2.67, the PsyQ 4.1 pairing). One global
   `--aspsx-version=2.56` cannot be right for a binary that mixes cells.
3. **Small-extern `$gp` model**: fix maspsx to genuine ASPSX behaviour (every `.extern` absolute; only TU-defined small
   `.comm`/`.sbss` `$gp`-relative); gate on the TUs step 1 shows affected; rows that shift go to step 4.
4. **Recipe route for the page-constant class** (~50 rows / ~125 sites at non-splitting cells; 150 rows / 332 sites
   on `0x8XXX0000` locals overall): charter amendment needed - a coherence repair toward the recipe the RETAIL BYTES
   prove (step 2's fingerprint), not only toward the module census recipe.

### 4. Re-recipe with natural C
After the step-3 decisions: CPU sweep `t86_symaddr`-style natural symbol spellings, cellscored at the evidenced recipe,
over the class; exact rows land as coherence trades (ledger/recipe_trades.jsonl); the rest go to Opus port-style
lanes (cheap: ~150k tokens a lane in round 77). Fix the wrong ADDR_ALIAS comment in `src/slus/w_8003D92C.c` when
that row lands.

### 5. Retire maspsx passes
Delete each imitation pass once step 4 leaves it firing on zero landed rows; re-gate the tree.

## Owner sign-off needed
- Charter amendment for decision 4 (coherence toward the retail-proven recipe).
- Any change to what "exact" means: the ASPSX version in the recipe (decision 2), the maspsx `$gp` fix (decision 3),
  deleting a maspsx pass (step 5).
Steps 1 and 2 are measurements and need no sign-off.

## Log
- 2026-09-24: plan recorded (round 77, after the sceptic's verdict). Pins at the time: 3,316 in 817 rows.
- 2026-09-24 ~03:30Z: round-77 lanes all landed (3,512 -> 3,207, incl. the NON_MATCHING arm-retirement ruling). Steps 1 and 2 launched in parallel as Opus agents; outputs tools/fidelity/, work/fidelity/, docs/evidence/fidelity_step{1,2}_*.md.
- 2026-09-24: STEP 2 done (docs/evidence/fidelity_step2_split_fingerprint.md). Pin-free rows at splitting cells 81% fingerprint vs 4.4% at non-splitting cells; 345/365 modules agree with the census (1 contradiction: dungeon/ovl_10a30bc.c); step-4 candidates 70 strict + 2 weak (docs/evidence/fidelity_step4_candidates.tsv): 48 toward an already-splitting census recipe (existing clause 4b), 22 need the amendment (17 slus, 5 dungeon).
- 2026-09-24: owner decisions after step 2: (1) amendment granted (charter 'Rulings 2026-09-24 (later)'); (2) hidden scaffolding goes on the ladder - whole-function asm = L0 (done, w_8005A1D0), `cell_imitation`/`maspsx_dependent` L4 residue after step 1; (3) weak tier waits for step 1; (4) fingerprint to be built into the module census TOOL as a constraint (module summary in ledger/, per-row data regenerable in work/).
- 2026-09-24 04:10Z: slus/w_8005A1D0 (the only whole-function asm row, a 39-word .word paste) written in C by lane r77_opus_asmfn and landed at 2.7.2-cdk (retail-proven splitting cell, neighbours' cell); SLUS SHA-1 MATCH. First slus recipe change: slus recipes live in tools/build/configure.py CC_VER + ledger/splits/slus.build.ninja (pinned), not in set_row_cfg (no slus split records) - step 4 needs a slus path in the lander. verify.py's cached reference for this row (ledger cache slus_obj.json/slus_dis, built from the raw .word text) no longer matches compiled C; the SLUS gate is the proof of record - re-baseline the slus cache when step 4 touches slus rows.
- 2026-09-24: STEP 1 done (docs/evidence/fidelity_step1_aspsx_diff.md; tool tools/fidelity/aspsx_diff.py, 13 min full run, genuine toolchain via the local link toolchain/genuine). All 6,767 rows exact through maspsx; 6,157 (91.0%) exact under a genuine ASPSX; 610 maspsx-dependent (836 pins; 439 pin-free), every one attributed by ablation: _maybe_unfill_return_delay 459 + _unfill_via_load_delay 37 (both faithful ASPSX-filler models applied to cc1 output with a pre-filled noreorder return - a reorder-mode epilogue lets genuine 2.79 reproduce 496/511: a CC1 question, not maspsx), $gp small externs 59 (slus), per-row --aspsx-version 2.40/2.34 22 (town), cdk-imitating passes ~30. One global ASPSX (2.77/2.79/2.81) covers all 6,157; 2.56 cannot assemble 4,690 rows; the per-TU switch that matters is -0 (div checks).
- 2026-09-24: owner: "go down this rabbit hole ... even if it takes us backwards in terms of numbers". Launched in parallel (Opus agents, briefs docs/evidence/fidelity_{step1b,step_asv,step4}_brief.md): STEP 1b (which compiler/options emitted the 2.8-era reorder-mode epilogues - 511 rows), the ASPSX version trial (maspsx 2.56 -> 2.79/2.77, whole tree), STEP 4 preparation (recipe-move lander for overlay AND slus rows, slus verify-cache re-baseline, natural-C measurement of the 72 candidates at their evidenced recipe). Ladder refinement proposed: cell_imitation -> L4 residue (source/recipe), maspsx_dependent (filler/$gp model) -> L5 residue (toolchain model, not the row's C).
- 2026-09-24: STEP 1b done (docs/evidence/fidelity_step1b_epilogue.md, tools/fidelity/epilogue_model.py). The 2.8-era rows' epilogues are gcc 2.7.2's text-epilogue decision (function_epilogue + mips_epilogue_delay_slots) on 2.8-era codegen; gcc deleted it on 1997-07-11 (2.8.0 ChangeLog, Jeffrey A Law; verified by the orchestrator in the 2.8.0 tarball). No compiler we hold (our 2.8.0/2.8.1/2.91.66/2.95.2, genuine SN psyq 4.3-4.6 CC1PSX incl. an SN egcs-2.91.66 PSX cc1, CCPSX driver) emits it with any option. Model t272 + genuine ASPSX 2.79 alone: 580/601 rows at 2.8-era cells (496/496 epilogue-dependent, 84/84 controls; the 21 others carry a second maspsx behaviour). The original compiler is a pre-July-1997 gcc2 snapshot with 2.8-era codegen; the four 2.8-era cells are stand-ins for it. Incident: the job deleted the shared work/fidelity/tmp during the ASPSX trial (10 rows errored; re-run requested).
- 2026-09-24: check of the 30 rows registered at 2.91.66/2.95.2 (current text scored at the same flags on 2.8.1/2.8.0): 1/30 exact (town/func_800C4508); distances 3-111 elsewhere (5 not scorable). They do not collapse into the 2.8.x cells as written; one row needs -fno-gcse (gcse is egcs-lineage). Open: whether the lost pre-July-1997 compiler had egcs-era passes, or retail mixes compilers here - a natural-C re-derivation at 2.8.x would be the test, not a relabel.
