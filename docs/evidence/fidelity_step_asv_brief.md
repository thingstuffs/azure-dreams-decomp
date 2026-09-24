# Toolchain fidelity plan: ASPSX version trial (measurement only)

Read: docs/evidence/fidelity_step1_aspsx_diff.md ("decision 2"). Finding: every genuine-exact row is reproduced by
genuine ASPSX 2.77/2.79/2.81, while the pipeline tells maspsx `--aspsx-version=2.56`, which cannot even parse %hi/%lo
(4,690 rows). The recorded assembler version is therefore historically wrong. Question: is switching maspsx's
`--aspsx-version` from 2.56 to 2.79 (and, separately, 2.77) BYTE-NEUTRAL over the whole tree? Every row, not a sample:
the step-1 run tested only ~613 non-exact rows.

Method: tools/fidelity/aspsx_diff.py already re-runs the maspsx leg per row with the row's flags (`--asflags`); extend
it (or a sibling tool) to run the maspsx leg with the version overridden and compare the object to retail exactly as the
maspsx leg is judged now. Report per version: rows that change, rows that stop matching, rows that START matching (a
row exact only at 2.56 is evidence too), by container/cell, and which maspsx version-gated behaviours
(`tools/maspsx`: grep the version comparisons) cause each change. Also list the per-row version overrides
(e.g. town rows at 2.40/2.34) and what they do.

Deliverables: docs/evidence/fidelity_asv_trial.md; tool changes in tools/fidelity/ (+ test); data in work/fidelity/asv/.
Rules: as in docs/evidence/fidelity_step1_brief.md (measurement only; no edits to src/, ledger/, config/, tools/maspsx,
tools/build; no gates/landings/git; IO rule; <= 8 workers; no private absolute paths or sibling-repo name in committed
files). Report: headline, doc path, decisions.
