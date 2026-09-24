# Toolchain fidelity plan, STEP 1c: test EVERY compiler we hold on the 2.8-era epilogue question (measurement only)

Owner question: "In the old project we did a massive sweep to try to find every compiler - have we tested everything we have?"
Answer so far: NO. Step 1b (docs/evidence/fidelity_step1b_epilogue.md, tools/fidelity/epilogue_model.py) tested our stock
2.8.0/2.8.1/2.91.66/2.95.2, genuine SN psyq 4.3/4.4/4.5 (one identical `2.8.1 SN32 4.0.0010` binary), 4.6, an SN
`egcs-2.91.66 (PSX)` cc1 from the 4.5 MFD archive, and the CCPSX driver defaults. Every one fills the return slot; retail
does not (gcc 2.7.2's text epilogue, deleted 1997-07-11). The old project (sibling decomp repo: see
toolchain/genuine -> its toolchain/, and its tools/compiler_notes.md, work/psyq_hunt/, work/town_100_20260811/,
work/i4c_cc1_archaeology/, work/psyq41_validation/, work/psyq45_extract/) concluded in Aug 2026 that the production compiler
is "a mid-97 Cygnus snapshot between 970404 and 2.8.0" and launched a hunt for GCC 2.7.90/2.7.91 betas.

## Task
1. INVENTORY every C compiler binary we hold, in both repos and inside every archive (toolchain/genuine/psyq/_archives/:
   PSYQ 4.5 MFD zip, PSYQ_SDK.zip (legacy 3.5/3.6 pair), Psy-Q_46.zip, Psy-Q_47.zip, psyq-4.7-converted-full.7z, the
   RuntimeLibrary 4.1 (Dec 1997) and 4.3 (Nov 1998) rars, rar45), the sibling repo's work/psyq_hunt/ (DOS
   `2.7.2.SN16.3.7.0003`, psyq_sdk_probe cc1s), any compiler builds under its work/ (e.g. compiler_repros,
   i3_compiler_patch_lane - note which are PATCHED research builds, not historical), and specifically FIND the
   "JP-4.3 genuine 2.8.0 SN32 4.0.0007" cc1 the old project recorded as recovered (Aug 2026; memory says "recovered!")
   and the outcome of the 2.7.90/2.7.91 beta hunt. Table: path (repo-relative or archive member), sha256, version string,
   runnable how (native / wibo / dosemu2 - dosemu2 availability?), lineage, already-tested-where.
2. TEST each historical compiler not yet tested on the epilogue question with step 1b's method (epilogue form on a sample
   of the 511 rows + controls; genuine ASPSX 2.79 leg; compare to retail). A compiler with 2.7.2-era codegen will fail on
   codegen - report that separately from the epilogue form. The prize: any binary that emits BOTH 2.8-era codegen AND the
   unfilled (reorder-mode) return.
3. If a gcc 2.7.90/2.7.91 or a 1997 gcc2/Cygnus snapshot SOURCE is obtainable offline (the sibling repo, archives), say so;
   do not download anything from the internet without noting it in the report (it is allowed to look for local copies).

## Deliverables
docs/evidence/fidelity_step1c_compiler_inventory.md (inventory table + test results + verdict: tested everything / what
remains and why); tools under tools/fidelity/ if any; data under work/fidelity/step1c/ (its own scratch dir - never delete
a shared directory).

## Rules
Measurement only: never edit src/, include/, ledger/, config/, recipes, tools/maspsx, tools/build, toolchain/ (extract
archives into work/fidelity/step1c/ only; clean large extractions afterwards); no gates, landings, sweeps or git. IO rule: no
recursive grep over work/ trees, repo roots or the home dir - use find with -maxdepth / rg --max-filesize 4M on named dirs.
<= 8 workers. Never write private absolute paths or the sibling repo's name into committed files (say "the sibling decomp
repo"). Report: headline, doc path, decisions.
