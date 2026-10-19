# Unit suite: B16 vs release head

Method: every `tools/tests/test_*.py` module run in its own process
(`python3 -m unittest discover -s tools/tests -p <module> -v`, TMPDIR under the root,
1200 s per-module timeout, 5-6 modules in parallel; `runsuite.sh`). A single
`discover` run on B16 deadlocked (all threads in futex) inside
`test_land_isolated.LazyCacheRaceTests.test_every_thread_sees_the_whole_window_table`
after ~860 tests; that test passes alone (234 s) and in the per-module runs, so the hang
is cross-test state in one process, pre-existing and unrelated to these patches.
Parser: `parse_suite.py` (per-test verdicts + per-module FAILED/OK lines; both agree).

| run | tree | tests | ok | FAIL | ERROR | skip |
|---|---|---:|---:|---:|---:|---:|
| before | B16 `c52cce141` | 3,851 | 3,744 | 35 | 32 | 3 |
| after (lane patches + seed fix) | `f70bb5a29` | 3,884 | 3,781 | 35 | 28 | 3 |
| after (+ fixes 2, 3) | `46dd9a6ff` | 3,885 | 3,782 | 35 | 28 | 3 |
| after (+ ll34 tools, fix 5) = release | `e16997c54` | 3,894 | 3,791 | 35 | 28 | 3 |

New failures vs B16: **0** in every after-run. Fixed: **4**
(`test_gate_all_inputs_sha.InputsShaCensusFiles.*`, the lane's legacy-v3 oracle conversion;
v4 replacements live in `test_proof_receipts`).

## Pre-existing failures (identical before/after): 63 tests in 19 modules + 1 empty module

| module | B16 result | cause (environment / fixture / unrelated) |
|---|---|---|
| test_asv_trial | 1 F | compiler-behaviour expectation (`'none' != 'gp_allow_la'`) |
| test_fresh_window_receipts | 2 E | proof view vs canonical `src` / TMPDIR outside build_ovl view (root-layout assumption) |
| test_gen_noreturn_syms | 1 F | view-root path equality (build_ovl vs root), known from the lane |
| test_land_followups, test_land_fast_front, test_land_issue, test_land_process | 1+5+6+2 | lander fixture contracts out of date (`fast-levels`/`fast-graph` steps, scrub hook text) |
| test_land_recipe_move | 7 E | needs `build_slus/config` (no SLUS build in a scratch root) |
| test_land_selective | 8 F + 8 E | fixture header expectations / IndexError in lander fixture |
| test_land_slus_rebaseline | 15 F | fixture tree lacks `tools/source_layout.py` |
| test_native_external_assets | 1 E | import error `No module named 'gate'` (sys.path) |
| test_pin_research | 1 F | historical source hash drift |
| test_perturb_struct, test_t130_pagelocal, test_t63_memdep, test_slus_ccproc | 1 each | generator/compiler-shape expectations unrelated to gate tools |
| test_slus_module_member_scope | 3 E | `No module named 'linklist'` (sys.path) |
| test_slus_partition_export | 3 F | `No module named 'source_layout'` in subprocess |
| test_verify_rebaseline_slus | 7 E | needs `ledger/cache/slus_obj.json` (gitignored cache) |
| test_t10_epilogue | rc 5 | no tests collected (empty module) |

## Focused modules on the release head (e16997c54)

test_linklist 16, test_linklist_load 9 (ll34 + method allowlist), test_certify_batch 5,
test_certify_batch_process 23, test_gate_required_windows 7, test_readers_placement 11,
test_overlay_module_placements 25, test_overlay_home_namespace 2 (followup),
test_module_scoped_fingerprint 9, test_overlay_scoped_fingerprint 112 (incl. 3 seed tests),
test_levels 43, test_levels_scoped 5, test_status_states 10, test_byte_map 32,
test_byte_map_format 10, test_byte_map_rollout 10, test_native_package 24, test_proof_receipts 19,
test_land_package_proofs 15, test_gate_all_inputs_sha 8, test_placement_independent_data 13,
test_lanekit_kitgaps 32, test_rename_proof 29: all OK.

## Smoke gate (scoped, workers 4, private root, never a full gate)

`python3 -u tools/build/gate_all.py --workers 4 --only-window ...` x6 in the release root
(build_ovl rebuilt by mk_ovl_root.sh after every tool commit). Run twice: at `46dd9a6ff`
(773 s) and at the release head `e16997c54` with ll34's tool hunks (873 s). Both:
`{'MATCH': 6}`, 0 retries, final inputs_sha audit 6/6, rc 0.

| window | why | projections in the gated window (release head) | result |
|---|---|---|---|
| town_scene | 4 town modules + 36 seed-level rows (finding 1) | 4 home | MATCH (B16: gate_all crashes in planning, KeyError 'pins_left') |
| dungeon_deep_c65250_truebase_8016aa50 | converted copies, fileless projections | 3 placements (p01/p03/p04 bank_c65000) | MATCH |
| dungeon_deep_t8_0d07 | PD59 broad home + copies window (followup patch) | 13 home + 11 placements | MATCH |
| dungeon_deep_t8b_c11000 | lane-touched home window | 1 home | MATCH |
| dungeon_deep_102b278_truebase_8016aa78 | seed row, no module | none | MATCH |
| town_deep_t8_02ab | plain window, untouched by placements | none | MATCH |

Placement projections are computational (all 116 reviews pending/lane-signed, no shard issued);
no certificate was issued and `valid_placements` stays empty.

`proof_receipts.validate_view(ROOT, ROOT/'build_ovl', w)` after the merged gate: PASS for all 6 windows.

Note: the `after_merged` suite ran in `repo2`, whose `build_ovl/` view was not rebuilt after the
ll34 merge; the focused modules import `tools/gate` directly (and copy it into fixtures), so the
numbers stand. The release root's view was rebuilt before each gate.

## Public readers (B16 vs release, private clones)

| reader | B16 | release (fixes 1-3) |
|---|---|---|
| levels.py | rc 0, recomputed == committed levels.jsonl | rc 0; 77 rows differ, all ll5b copies, field `records` only (before fix 2: 168 rows incl. 42 `l5_residue: inline_asm`) |
| status.py | rc 0, certificates 193 stale + 4 needs attention (KeyError) | rc 0, 197 stale, 0 needs attention |
| coverage.py | rc 0 | rc 0, output identical |
| row_db.py check | OK | OK |
| registry writer source_row vs descriptors | - | 0 mismatches (116 placements, 162 rows) |
| byte_map.py check --catalogue link | PASS | PASS (does not compare against config/link; see REVIEW C1) |
| link/ vs config/link TU entries | 833 images, 0 differ | 19 images differ (ll5b copies absent from LL6 maps) |
