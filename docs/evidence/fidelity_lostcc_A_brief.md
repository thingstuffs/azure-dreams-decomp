# Lost-compiler hunt A: genuine SN binaries from the 1997-04..07 window (downloads approved by the owner)

Owner (2026-09-24): "I'm starting to lean towards it existed but no one has it. So build the evidence and cite it, let's explore
whatever avenues we can first ... if we need a patched compiler for this one epilogue fix then we move with that, but it needs to
be rock solid and I'd like to exhaust any avenues we can." Downloads are approved.

Read first: docs/TOOLCHAIN_FIDELITY_PLAN.md, docs/evidence/fidelity_step1b_epilogue.md, fidelity_step1c_compiler_inventory.md,
fidelity_websearch_1997_compiler.md (URLs, SHAs). Tools: tools/fidelity/epilogue_model.py (substitute-cc1 env overrides, return-form
census), tools/fidelity/aspsx_diff.py; genuine toolchain at toolchain/genuine (wibo, ASPSX); dosemu2 is installed.

## Tasks
1. Download SN N64 `n64_sn272_build0006cygnus.tar.gz` (decompme/compilers `compilers` release; ~1.67 MB) and, for comparison,
   SN N64 build 0004 if available there. Record URL + sha256. Read every version string (`strings`); establish its Cygnus date and
   SN build number. Then TEST it on our problem: can it emit MIPS I little-endian R3000 code usable for PSX (-mips1 -mcpu=3000 -mel
   or whatever its specs allow; compare its output on a sample of our 2.8-era rows' C (the ~131 rows in
   work/fidelity/step1c/cdk_not_exact_epilogue_rows.tsv plus controls) against cdk (PSX build 0004) and retail via genuine
   ASPSX 2.79). Does it have post-970404 codegen? Does it emit the text epilogue? Does any row become retail-exact that cdk misses?
2. Download the US Run-time Library 4.0 "Release 2.0" disc (redump 71991, mastered 1997-06-20, archive.org `ps1_sdks`, ~392 MB)
   into work/fidelity/lostcc/ (never into the repo tree proper), extract, inventory every CC1PSX/CCPSX/ASPSX with version strings
   and sha256, and test any cc1 not already held (as in task 1). Delete the image after extraction; keep only the tool binaries
   (work/fidelity/lostcc/ is git-ignored work).
3. Any other genuine binary lead from the websearch report you judge worth one cheap check - note each with outcome.

## Evidence standard
Every claim cites a file + sha256 or a URL + date. Negative results are results: record exactly what was tested.

## Deliverables
docs/evidence/fidelity_lostcc_A_sn_binaries.md; data/binaries under work/fidelity/lostcc/A/. Rules: never edit src/, include/,
ledger/, config/, tools/maspsx, tools/gate, tools/build, toolchain/; no gates/landings/git; own scratch dir; no recursive grep over
work/, repo root or home; <= 8 workers; no private absolute paths or the sibling repo's name in the doc. Report: headline,
version strings, test results, decisions.
