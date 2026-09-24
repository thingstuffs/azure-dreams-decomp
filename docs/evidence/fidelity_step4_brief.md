# Toolchain fidelity plan, STEP 4 preparation: re-recipe tooling + candidate measurement (no landing)

Read: docs/TOOLCHAIN_FIDELITY_PLAN.md, docs/PIN_CAMPAIGN_CHARTER.md (clause 4b and "Rulings 2026-09-24 (later)" item 1),
docs/evidence/fidelity_step2_split_fingerprint.md, docs/evidence/fidelity_step4_candidates.tsv (70 strict + 2 weak rows
whose retail proves an address-splitting cell but which are registered at a non-splitting one), and the landing of
slus/w_8005A1D0 in the plan's log (commit ca253080: the first slus recipe change, done by hand).

## Part A - tooling (the orchestrator lands; you build and test)
1. A recipe-move lander that handles BOTH row kinds: overlay rows via common.set_row_cfg (ledger/splits, rows.jsonl,
   build roots); slus rows via tools/build/configure.py CC_VER + ledger/splits/slus.build.ninja (pinned copy; the
   regenerated recipe must differ from it ONLY on the moved TUs' lines) + ledger/rows.jsonl. Verify first, switch,
   apply the candidate text, gate (overlay windows + SLUS SHA-1), restore everything on failure, append the trade to
   ledger/recipe_trades.jsonl (kind coherence, evidence: fingerprint kinds + module census or "retail-proven"). Model
   it on tools/lanes/land_coherence.sh. Put it in tools/fidelity/ (e.g. land_recipe_move.sh / .py) with a dry-run mode
   and a test on a throwaway copy - DO NOT run it for real.
2. verify.py's slus reference cache (ledger cache slus_obj.json + slus_dis, built from raw/ text by baseline_slus)
   goes stale when a slus row's text or recipe changes on purpose (slus/w_8005A1D0 now fails verify although the SLUS
   gate matches). Design and implement a re-baseline for named rows from the LANDED src at the landed recipe, gated on
   the SLUS SHA-1 gate having matched; document it in verify.py's docstring. Test it.

## Part B - measurement: which candidates have a natural pin-free text at the evidenced recipe?
For each of the 72 rows: generate natural spellings (the page-constant pins become the symbol they encode -
tools/xform/t86_symaddr.py and the sceptic's examples in work/native_lane/r77_fable_splitaddr/cands/ show how; scaffold
removal per the charter) and score them at the evidenced recipe (the module census best_recipe when it splits;
otherwise 2.7.2-cdk vs 2.8.1 per the ruling: the cell where natural C is exact, tie -> TU neighbours' cell) with
verify.py / lab.py cellscore. Also score the CURRENT pinned text there (rule 2: if exact, a plain byte-neutral switch).
Output work/fidelity/step4/results.jsonl + docs/evidence/fidelity_step4_measure.md: per row - evidenced recipe, pinned
text exact there?, best natural candidate (path, pins before/after, exact?), residue if not exact. Stage exact
candidates under work/native_lane/r77_step4/out/<container>/<name>.c with .base_sha (the kit's convention) and
cells.jsonl lines ({"id","to","coherence"}) so the orchestrator can land them.

Rules: measurement + tooling only: never edit src/, include/, ledger/, config/, recipes, tools/maspsx, tools/build
(except: you may ADD a new function/section to tools/verify.py for part A2 - describe it; no behaviour change for
existing callers); no real landings, gates or git. IO rule; <= 6 workers (two other jobs run alongside); no private
absolute paths or sibling-repo name in committed files. Report: headline numbers, files, decisions.
