# Toolchain fidelity plan, STEP 1b: which compiler emitted the 2.8-era epilogues? (measurement only)

Read first: docs/TOOLCHAIN_FIDELITY_PLAN.md, docs/evidence/fidelity_step1_aspsx_diff.md (esp. "decision 1" and the
reorder-epilogue probe), work/tailslot_aspsx/CC1_DIFFERENTIAL.md.

## Question
511 rows (459 `_maybe_unfill_return_delay` + 37 `_unfill_via_load_delay` + overlaps; lists in
docs/evidence/fidelity_step1_maspsx_dependent.tsv and work/fidelity/reorder_epilogue_probe.txt), all at
2.8.0 / 2.8.1 / 2.91.66 / 2.95.2 cells, are retail-exact only through two maspsx rules that model ASPSX's own
delay-slot filler applied to cc1 output whose return slot cc1 ALREADY filled (`.set noreorder / j $31 / addu $sp`).
Rewriting only that epilogue into reorder mode lets GENUINE ASPSX 2.79 alone reproduce retail on 496/511. So the
original compiler emitted a reorder-mode return there. Which compiler, with which options, does that - and does it then
reproduce retail with genuine ASPSX on these rows WITHOUT the maspsx rules?

## Known
- Round 14 (CC1_DIFFERENTIAL.md): on 15 rows, genuine PsyQ CC1PSX.EXE output was byte-identical to our rebuilds:
  psyq4.0 = gcc-2.7.2, psyq4.1 = gcc-2.7.2-cdk, psyq4.3/4.4/4.5 = gcc-2.8.1, psyq4.6 = gcc-2.95.2. So the binary alone is
  probably not it - but those 15 rows were not these rows, and only one epilogue case was ever looked at.
- Genuine binaries: toolchain/genuine/psyq/psyq4.{0,1,3,4,5,6}/ (CC1PSX.EXE, ASPSX.EXE; 4.0/4.4 also CCPSX.EXE the
  driver, CPPPSX, PSYLINK, SN.INI/psyq.ini - the driver's DEFAULT options live there); run under toolchain/genuine/bin/wibo.
  Our compilers: toolchain/compilers/; gcc sources: toolchain/gcc-src/ (read gcc 2.8.x config/mips/mips.c function
  epilogue emission: when does it print `.set noreorder` + a filled `j $31`, when does it leave the return to the
  assembler or emit an RTL epilogue - flags such as -g/-gcoff, -O level, -fomit-frame-pointer, -mabicalls, -mgas/-mmips-as,
  -fno-delayed-branch, TARGET_* bits, frame size, `current_function_epilogue_delay_list`).
- Tools: tools/fidelity/aspsx_diff.py (--one, --cfg, --asflags, --cfile), tools/fidelity/probe_reorder_epilogue.py,
  work/tailslot_aspsx/ harness (genuine CC1PSX runner).

## Method (suggested, not prescribed)
1. From gcc 2.8 mips.c, list the conditions for each epilogue form; find the option(s) that give reorder-mode returns.
2. Test those options with our gcc 2.8.1 AND genuine CC1PSX 4.3/4.4/4.5 (and CCPSX's default option set) on a sample
   of the 511 rows across cells/containers; assemble with genuine ASPSX (2.77/2.79, -0 as the row needs); compare to
   retail (aspsx_diff's comparator). Then the full 511, and a control set of genuine-exact 2.8-era rows (the option must
   not break rows that are already genuine-exact).
3. If one compiler+option reproduces retail on (nearly) all of them with genuine ASPSX, that is the evidenced recipe.
   Report which rows still need maspsx and why.

## Deliverables
docs/evidence/fidelity_step1b_epilogue.md (question, gcc source citations, the option table, results by cell/
container, controls, the recommended recipe change and its blast radius); any tool under tools/fidelity/ (+ test);
data under work/fidelity/step1b/.

## Rules
Measurement only: never edit src/, include/, ledger/, config/, recipes, tools/maspsx, tools/build, toolchain/; no gates,
landings, sweeps or git. New files only under tools/fidelity/, tools/tests/, work/fidelity/step1b/, docs/evidence/.
IO rule: no recursive grep over work/, repo root or <home> (`rg --max-filesize 4M` on narrow dirs only). Heavy
jobs under `nice -n10 ionice -c2 -n7`, <= 10 workers (two other jobs run alongside). One background command per long
run, one completion. Never write private absolute paths (under the user home) or the sibling repo's name into committed files:
use repo-relative paths and toolchain/genuine. Report: headline, doc path, decisions for the orchestrator.
