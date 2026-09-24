# Round 77: the split-address "toolchain gap" - DISPROVED (Fable sceptic, owner request 2026-09-24)

Owner: "Extremely sceptical of a 'toolchain' gap. 1 fable agent to prove or disprove."  Lane `r77_fable_splitaddr`
(claude-fable-5-1, 355k tokens); full report and every probe in `work/native_lane/r77_fable_splitaddr/REPORT.md`, `cands/`.

**Claim tested** (r77_opus_m1/m2/m3 and the ADDR_ALIAS comment in `src/slus/w_8003D92C.c`): retail's
`lui %hi / other insn / addiu %lo` pairs cannot come from C because `la` is atomic in the assembler and cse folds
integer pages to `lui/ori`; page-constant `ASM_KEEP`/`ASM_REG` pins are therefore a toolchain gap.

**Verdict: false.** The pairs are the output of an address-SPLITTING compiler: the tree's own `2.7.2-cdk` cell (-mgas,
PsyQ 4.1 CC1PSX). The pinned rows are registered at cells that cannot split (2.6.3, 2.7.2, or cdk with `-mmips-as`),
and their page-constant pins imitate that cell.
- `slus/w_8003D92C` natural C (`input_state = &D_80083160;` ..., 0 pins, 0 page constants) at `2.7.2-cdk` through the
  project pipeline: 136/136 words, same 2-word `jal` floor as the retail-exact pinned control (`cands/pipe.py`;
  **reproduced by the orchestrator 2026-09-24**). Through the GENUINE toolchain (cdk cc1 -> genuine ASPSX 2.67/2.77 `-0`,
  no maspsx): 136/136, 0 mismatches.
- Genuine ASPSX 2.56/2.67/2.77 never splits an `la`; maspsx agrees on that. 2.6.3/2.7.2 `mips.c` have no
  `split_addresses` path (grep 0; 5 in 2.8.1).
- Tree (slus retail, 556 rows): 185 of 317 pin-free cdk rows show the split fingerprint from natural C; 6 of 364 pin-free
  2.7.2 rows do, and those come from maspsx passes, not cc1.
- Class size: 150 rows / 332 pin sites on a local assigned `0x8XXX0000` (10% of live pins); ~50 rows / ~125 sites at
  non-splitting cells are this class. The other four rows of the pack: partial evidence (split pair exact at cdk, residue
  left).

**Owner decisions this raises (charter-reserved: they change what "exact" means or move recipes):**
1. **maspsx fidelity.** `_sink_call_separated_la` and `_split_funcaddr_la` (tools/maspsx) assert ASPSX behaviour that
   genuine ASPSX does not have, and make 2.7.2-registered rows exact by imitating the cdk compiler in the assembler stage.
2. **ASPSX version for slus.** The slus pipeline passes `--aspsx-version=2.56`; ASPSX 2.56 cannot parse cdk `%hi/%lo`
   output (7 syntax errors), so a cdk-registered slus TU implies ASPSX >= 2.67. The SLUS mixes cells.
3. **Small externs.** Genuine ASPSX addresses every `.extern` absolutely and `$gp`-relativises only TU-defined small
   `.comm`/`.sbss`; maspsx `$gp`-relativises small externs. The w_8003D92C candidate needed its seven `.extern` lines
   withheld from maspsx.
4. **Recipe route for the ~50-row class.** Moving these rows to `2.7.2-cdk` fails rule 2 (the pinned text is not exact
   at cdk), so it is a coherence-style trade (clause 4b applies only toward the module census recipe) - per-row check
   of the module census needed before any landing.
Nothing was staged or landed from this lane.
