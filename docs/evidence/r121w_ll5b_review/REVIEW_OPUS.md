# Review: r121w_ll5b LL5 tooling (+ r121w_ll34 gate-tool hunks), rebased on B16

Reviewer: Opus subagent, 2026-10-18. Base: B16 `c52cce141`. Private clones only
(`ll5b_review/repo` = release head, `b16` = baseline, `repo2` = reader/suite twin).
No live-repo writes, no refs moved.

Release head (private clone `ll5b_review/repo`, branch `ll5b_review`):

| commit | content |
|---|---|
| 365aa0a1f | ll5b `delivery.patch` (applied clean on B16, `git apply`, no fuzz) |
| 4d21b52e2 | ll5b `consolidation_followup.patch` (clean) |
| f70bb5a29 | review fix 1: seed level records in scoped eligibility (+3 tests) |
| ac6b462e0 / b7388c7a3 | review fix 3: fileless-copy rejection only for copies of module members (+2 tests) |
| 46dd9a6ff | review fix 2: B16 home source context restored; copies take their home context (test updated) |
| e16997c54 | ll34 tool hunks (linklist.py, overlay_local_gate.py, test_linklist_load.py) + review fix 5 (load-record method allowlist, +1 test) + regenerated `src/dungeon/INDEX.md` |

`release.patch` = `git diff --binary c52cce141 e16997c54 -- . ':!work'` (no work/ files,
no `/home` paths). It carries ll5b content (link lists, placements index, evidence,
rows/splits/graph, 53 relink retirements) + both lanes' tool changes. It does NOT carry
ll34 content.

## Conflicts resolved

Textual: none. Both ll5b patches apply cleanly to B16; ll34's tool hunks apply on top
with offsets only (linklist.py +5, overlay_local_gate.py +2).

Semantic (B14-B16 landed after the lanes' B13 base):

| # | conflict | resolution |
|---|---|---|
| C1 | B14 LL6 byte maps `link/dungeon/*.tsv` are "complete counterparts" of `config/link`; ll5b adds 53 copy TU entries to 19 dungeon link lists (bank_c5f000, c65000..c83000, d31000..d55000, e81000..e9f000) that the maps lack. `byte_map.py check` still passes (it only checks the catalogue internally) and no unit test catches it. | NOT fixed in release: regeneration needs the LL6 census pipeline. Note `tools/census/regenerate.py --check` is ALREADY broken on B16 (census snapshot inputs `ledger/rows.jsonl`, `coverage_regions.jsonl`, `splits/town.jsonl`, one SLUS source drifted in B14-B16). Required follow-up: rerun the LL6 rollout for those 19 images (or the whole catalogue) after consolidation, or the owner accepts the B13-snapshot drift. |
| C2 | `src/dungeon/INDEX.md` (generated) still listed the 53 deleted relink files | regenerated (status.py/gen_src_index output; only the file column of the 53 copy rows changes) |
| C3 | B14 heur3 rows / B15-16 goto + m2c edits | no overlap with placed homes or the 53 retired copies (checked: no B14-16 change touches a placed module's source/headers/members); physical graph recomputed on B16+patch == `ledger/splits/overlay_modules.build.json` (equal) |

## Findings

Severity: High = proof/authority or whole-gate breakage; Medium = changes existing outputs or
a landing dependency; Low = robustness/cosmetic.

| # | Sev | file:line (release head) | issue | fix | test |
|---|---|---|---|---|---|
| 1 | High (pre-existing, requested) | tools/gate/overlay_scoped_fingerprint.py:441-467 | `row_eligibility`/`screening` index `pins_left`/`tail_jumps`/`l4_residue`; the 40 seed records `{"id","level":-1}` on B16 raise KeyError. Worse than "4 certificates": on B16 `gate_all --only-window town_scene` crashes the whole gate process in planning (`inputs_sha` -> proof_receipts.window_inputs -> module fingerprint -> row_eligibility; log `logs/gate_b16_town_scene.log`), so a full consolidation gate on B16 would abort. | New `eligibility(level,data)`: a record with `level < 0` binds `{l3/l2: False, pins: None, tail_jumps: None, residue: ['unleveled'], level: -1}` (never eligible, deterministic digest); any other incomplete record still raises (fail closed). Full records hash exactly as before. Same helper in `screening` (member seeds still fail `load_modules`' L3 screen with ValueError first). | `test_overlay_scoped_fingerprint`: `test_seed_level_neighbor_is_bound_not_eligible` (fails with KeyError without the fix), `test_seed_level_grants_no_eligibility`, `test_seed_level_member_fails_screen`. Real path: release gate planning of town_scene (4 modules + 36 seeds) passes; STATUS "4 needs attention" -> "stale" (renewable). |
| 2 | Medium-High (lane change) | tools/overlay_module_evidence.py:108-130 | ll5a/ll5b changed `source_contexts` for EXISTING home modules to include all sibling member bodies, contradicting the function's own docstring ("Sibling bodies retain their own logical row checks"). Measured with levels.py on B16 vs B16+patch: 168 level records change for non-placement reasons; 42 rows of `dungeon_engine_dungeon_util` gain `l5_residue: inline_asm` (L5-blocking) from a sibling; T7 record rows +83; STATUS audit-site bytes change. | Restored B16 home semantics (glue + headers minus member bodies); fileless copies receive exactly their home's context (the part the placement work needs). After fix: only the 77 placement-copy rows change, field `records` only, no level/pins/l5 change. | lane test renamed `test_shared_context_excludes_siblings_and_projects_to_copy_rows`, asserts no sibling body in any context and copy context == home context; levels A/B (`logs/readers_*.log`). |
| 3 | Medium (lane change) | tools/lanes/lanekit/native_member.py:46-50; tools/lanes/native_package.py:68-70 | `membership(row)` raised for ANY row with `source_row` (9,410 pre-existing ordinary link-list copies on B16) -> `lab.compile_stderr`, `rename_proof`, `score_batch` break on ordinary copies; `native_package.collect` raised for any staged copy instead of the ordinary deferral. | Reject only copies whose `source_row` is a module member (the LL5 case); ordinary copies keep the B16 route. | `test_native_package.test_copy_rows_fileless_only_for_module_homes`; `test_overlay_module_placements` fileless test extended with an ordinary-copy deferral case. |
| 4 | Medium (decision) | config/overlays/module_placements.json (5 p04 descriptors) + docs/evidence/dungeon_ovl_7f469800_p04_bank_{d0d000,d13000,d19000,d25000,d2b000}.placement.json | 5 destination reviews are signed `reviewer: codex-r121w_ll5b` by the lane itself. Existing module reviews are `orchestrator-rNNN` (one precedent `codex-r121w-certs`). Nothing issues automatically (certify_batch / home certify only renew RECORDED shards; issuance needs an explicit `--placement` run), so no grant today; but an issued shard would grant L4 on a lane self-review. | Not changed (would invalidate the v2 records). Orchestrator: countersign (rewrite reviewer in descriptor + v2 record) or reset to pending before any `--placement` issuance. | - |
| 5 | Medium (ll34) | tools/gate/linklist.py `placement_vma` / `LOAD_METHODS` | ll34 accepted any truthy `method` on the bound `instance_load_regions` record. 234 of ll34's 269 bound records are `internal link-evidence` (link-base evidence, which LL6 byte maps deliberately do NOT treat as a VMA; only `validated ...` gets a vma there). A future heuristic record with any method string would authorize a base. Bytes still have to MATCH retail in the window, so this is attribution/authority, not a byte bypass. | Allowlist `("validated ", "internal link-evidence")` (covers all 269 current refs); anything else -> "disagrees with load evidence". Owner should confirm internal link-evidence is acceptable as placement base authority (it is link evidence, not runtime-load evidence). | `test_linklist_load.test_unrecognised_record_method_refused` (+ fixture method renamed `validated synthetic loader witness`). |
| 6 | Low (ll34, verified) | tools/gate/overlay_local_gate.py:950 | as-flags now resolved by the placement's row identity instead of `seg.match.func`, for all placements (not only load-evidence ones). | none needed: evaluated `default_as_flags` old vs new for all 9,463 existing link-list placements on the release tree: 0 differ. | - |
| 7 | Low (ll34, verified) | tools/gate/linklist.py `placement_vma`, overlay_local_gate.py:365 | Can the image record give a MATCH without load evidence? No: the only caller passes `allow_legacy=True`, so an image without `load_evidence` returns None and keeps the B16 proven-rowbase path; an image with it must bind one exact current record by canonical SHA-256 (schema, container, image containment, base/delta, image delta), cannot sit in any rowbase region unless proven and equal, and the split true_name must equal `func_<vma>`; the ledger file joins `window_files` so the digest re-keys on record edits. | - | ll34's 8 tests + finding 5 test. |
| 8 | Low | tools/gate/overlay_module_placements.py:70-205 (`_load`) | Placement validation is global and fail-closed inside every `_window_digest`, `graph()`, `gate_all.window_modules`, `native_package`: one invalid descriptor (e.g. a placed row's split marked rerun/non-MATCH, link-list edit, rowbase change) aborts fingerprints of every window and every home certificate (accounting degrades to "invalid", not crash). Consistent with `modules.json` validation; landers editing splits/link lists of placed rows must keep `module_placements.json` in sync (`linklist.check` reports it). | none (design); note for landers | - |
| 9 | Low/Info | tools/gate/overlay_module_placements.py:324-363 | Home windows now reuse a content-addressed artifact `work/module_artifacts/<key>/<fp>` (revalidated by retail + genuine replay and fingerprint equality) instead of recompiling per window; `home_build` rewrites the copied receipt's `fingerprint` to the full window fingerprint. A consolidation gate may therefore not recompile unchanged modules. Sound, but a semantic change of what a gate run exercises. | none | smoke gate (below) |
| 10 | Low | tools/lanes/proof_receipts.py:668 `import_placement` | copies carried proof files into `work/module_placement_proofs/<key>/...` before validation; a failed import leaves them (proof dirs are unique per issuance, so overwriting a live shard's files is unlikely). `next(...)` StopIteration if the carried key is absent from the manifest (fail-closed, untyped). | none | - |
| 11 | Low | tools/gate/overlay_module_gate.py:378,380 | legacy (non-scoped) module fingerprint still indexes `pins_left` directly; unreachable for seeds because `load_modules` rejects `level < 3` first. | not changed | - |
| 12 | Info | tools/lanes/land_packages.py ~1167 | lander event prints `authority='diagnostic only'` for an adopted placement certificate's windows. | cosmetic | - |

Authority audit (a), verdict: no path found that yields a placement MATCH, certificate PASS or
L4/L5 grant without real receipts. Production shard reading (`certificate_reason`) requires: complete
home + placement review AND exactly one v2 record equal to the whole current descriptor; kind
`overlay_module_link_placement` (scratch kind rejected); fingerprint incl. all destination window
digests; whole-TU receipt replay (ELF + genuine LNK resolved at the destination, == retail);
every destination window artifact == retail and a projection naming this placement/artifact.
On the release tree `P.valid_placements == {}` (116 descriptors, 0 shards); levels gives no
L4/L5 to any copy; `accounting_modules` adds only `valid_placements`.

Existing-window effects (b): tool identity changes re-key everything (consolidation gate needed,
as the lanes state). Beyond that: windows with no intersecting placement keep the same digest
shape (`module_placements` key absent; `load_evidence` files only for images that carry it);
windows holding converted copies re-key via their link lists; the 5 windows holding seed rows
now digest instead of crashing. coverage.py output identical B16 vs release; row_db check OK;
registry writer source_row == every descriptor home (0 mismatches); levels: only the 77 copy rows'
`records` change (after fix 2); STATUS: certificates 193 stale + 4 needs-attention -> 197 stale.

## ll34 content (not in release.patch) vs B16 + release.patch

`git apply --check` of ll34's 1,964 non-tool hunks:
- fails on B16 alone (B14-B16 landed): docs/LINK_LISTS.md, ledger/baseline.jsonl, ledger/rows.jsonl,
  ledger/splits/overlay_modules.build.json, ledger/splits/town.jsonl, src/dungeon/INDEX.md,
  src/town/INDEX.md, and 4 copy deletions of files B16 edited (m2c scaffolding, r121w_proto1a/b):
  src/town/func_8067F4C0.c, func_80697498.c, func_806C59A0.c, func_806D4A90.c (deletion must be
  re-attested against the B16 text; the copies compile home text after conversion anyway).
- additionally fails with release.patch: 11 link lists rewritten by both lanes
  (dungeon bank_d31000, d37000, d3d000, d43000, d49000, d4f000, d55000, e8d000, e93000, e99000,
  e9f000). Semantic diff: purely additive, ll34 adds 1 entry per file (func_80D14664 ... ,
  func_80E703D8 ...), ll5b adds 1-5; no row has different homes; the union has no extent overlap.
  Union-merge these 11 files, then regenerate rows/baseline/graph/INDEX with the normal tools.
- No row is retired by both lanes (ll34 1,106 deletions vs ll5b 106: disjoint).

## Validation (details in tests.md)

- Unit suite, per-module processes: B16 3,851 tests (35 F / 32 E / 3 skip) -> release head
  3,894 tests (35 F / 28 E / 3 skip). New failures 0; fixed 4; 63 pre-existing failures identical
  (environment/fixture debt, classified in tests.md).
- Scoped smoke gate in the release root, 6 windows, workers 4: `{'MATCH': 6}`, final audit 6/6,
  at both 46dd9a6ff and the merged head (town_scene = seed rows + 4 modules; c65250 = 3 placement
  projections; t8_0d07 = 13 home + 11 placement projections; t8b_c11000; 102b278 seed-only;
  town_deep_t8_02ab plain). Same town_scene window on B16: gate_all aborts (KeyError).
- release.patch: 2,324,696 bytes, 273 files, `git apply --check` clean on a fresh B16 worktree,
  0 `/home` paths, 0 work/ files.

## Verdict

**READY AFTER LISTED FIXES** (review fixes 1, 2, 3, 5 are already in release.patch).

- Blocks the consolidation landing unless the owner waives it in writing: C1, the 19 LL6 byte maps
  under `link/dungeon/` that no longer match `config/link`. Regenerating them can ride the same landing.
- Blocks placement issuance, not landing: finding 4. The 5 p04 reviews are signed by the lane itself.
  Nothing issues automatically. Before any `--placement` run, the orchestrator countersigns them or
  resets them to pending.
- Owner call, not a blocker: finding 5, whether internal link-evidence counts as placement base
  authority. The allowlist in release.patch is a no-op on all 269 current references.
- ll34's tool hunks have no effect on the release tree. No `config/link` image carries `load_evidence`,
  so `placement_vma` never takes the new path, and the as-flags change gives the same flags for all
  9,463 placements. They only change tool hashes until ll34's content lands. ll34's content is a
  separate landing. It needs:
  - the 11-file union merge,
  - the 4 town deletions re-checked against B16 text,
  - the generated ledgers regenerated (see the ll34 section).
