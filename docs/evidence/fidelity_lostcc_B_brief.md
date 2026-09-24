# Lost-compiler hunt B: build gcc2 trunk snapshots from 1997-04..07 and bisect (downloads + builds approved by the owner)

Owner (2026-09-24): build the evidence that the production compiler existed and cite it; exhaust avenues; a patched compiler (the
one epilogue revert) only if rock solid. Downloads approved.

Read first: docs/TOOLCHAIN_FIDELITY_PLAN.md, docs/evidence/fidelity_step1b_epilogue.md, fidelity_step1c_compiler_inventory.md,
fidelity_websearch_1997_compiler.md (the gcc-mirror SHAs: window 1997-04-04..07-11 = SVN r13838..r14412; Law's epilogue deletion
1f2d8f510f4e516803427373e1625991756d4d91 (r14412, 07-11); its parent 7a49a4fd7b45ce1c15859f6bd4ee46418310d8f1 (r14410, 07-10); weekly
anchors listed there; 1997-05-01 Wilson's -m[no-]split-addresses). The previously built trunk rebuilds 970802/970821/971023 and
their build recipe (`build_one.sh` and host fixes) live in the sibling decomp repo (see the step 1c doc for paths; reachable via
toolchain/genuine/.. is NOT guaranteed - find them with `find` under its work/ with -maxdepth, not recursive grep).

## Method
1. Fetch tarballs with `https://codeload.github.com/gcc-mirror/gcc/tar.gz/<sha>` (~8 MB each; do NOT clone the 4.2 GB repo) into
   work/fidelity/lostcc/B/src/. Build a MIPS-target cc1 per snapshot with the old recipe (same configure target/flags as the held
   970802 build). Record sha256 of each cc1.
2. CALIBRATE: build r13838 (04-03) and r13861 (04-11). On the 424 rows cdk (970404) already reproduces (step 1c lists) - do these
   trunk snapshots reproduce them too (compare .s to cdk's and retail via genuine ASPSX 2.79 with the epilogue as emitted)? This
   establishes how good FSF trunk is as a stand-in for the Cygnus/SN tree. Report agreement numbers.
3. TEST r14410 (07-10, last text epilogue): on the ~131 rows that need post-970404 codegen + text epilogue
   (work/fidelity/step1c/cdk_not_exact_epilogue_rows.tsv) and on controls (rows already genuine-exact at their cells). Retail-exact
   count with genuine ASPSX (no maspsx epilogue helper).
4. BISECT through the weekly anchors (and finer if it pays) for the snapshot that reproduces the most rows (ideally all 131 + all
   controls). Watch the -m[no-]split-addresses introduction (05-01) - 6 rows use that flag.
5. If no snapshot reproduces everything: characterise the residue (which rows, which pass). If the best snapshot + the 2.8-era
   cells differ only in the epilogue, say so precisely: that is the evidence a single epilogue revert would rest on.

## Evidence standard
Every claim cites snapshot SHA/SVN rev, cc1 sha256, row lists and counts. Negative results recorded.

## Deliverables
docs/evidence/fidelity_lostcc_B_trunk_bisect.md; tools under tools/fidelity/ if reusable (+ test); builds/data under
work/fidelity/lostcc/B/. Rules: never edit src/, include/, ledger/, config/, tools/maspsx, tools/gate, tools/build, toolchain/ (build
compilers ONLY under work/fidelity/lostcc/B/); no gates/landings/git; own scratch dir; no recursive grep over work/, repo root or
home; builds with -j <= 8 (another job runs alongside). No private absolute paths or the sibling repo's name in the doc. Report:
headline, calibration, best snapshot and its counts, residue, decisions.
