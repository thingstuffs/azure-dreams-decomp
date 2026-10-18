# LL3a delivery: proven instances become link-list placements

Base: staged B10 private tree `ebf0bb89f11b43101506c3fdbfb1ac90bed4716a`. Work stayed inside this lane/private root; the directed r121_instances attestations were read-only.

Status: 1,080 placements, 458,860 bytes. Final gate: 1251/1251 current MATCH, rc 0.

| Container | Converted | Bytes moved to C | C share before | C share after |
|---|---:|---:|---:|---:|
| dungeon | 430 | 376,480 | 92.8582% | 98.4654% |
| town | 650 | 82,380 | 65.8814% | 75.8686% |

Percentages use coverage.py's classified/estimated code denominator. Each container gains exactly the converted bytes in c_rows and loses the same bytes in proven_instances; denominators and other partitions are unchanged. See coverage_before.json and coverage_after.json.

## Per-item status

`results.tsv` lists every converted span, home TU, image, source/object/retail hashes, paired-relocation counts and covering gate windows. `holds.tsv` gives every held span and its next step. The current staged scope has 1,095 eligible proven spans: 1,085 without row overlap, plus 10 partial-overlap holds. The older design census predates the staged B10 ownership.

## Proof and implementation

- Rehearsal: all four LL3a instances in dungeon/bank_cdd000 (336 bytes); row_db check OK; all 14 bank windows MATCH. `rehearsal_gate.log` and `rehearsal_journal.jsonl` retain the proof.
- Negative controls: VMA +4 refused by link-list load; a data binding +4 gives NO MATCH at file 0xCE00E0 (also on the gate's automatic serial retry). Restoring the list restores the original input SHA/current MATCH. See `controls.json` and `wrong_binding_gate.log`.
- Admission: compile the current home TU at the placement recipe with home bank evidence. Verify every non-relocation instruction bit, infer full symbol values from paired HI16/LO16 addends, and evaluate every relocation field against retail. 4,543 paired HI16/LO16 sites and 16,682 admitted relocation records; 1,012 converted instances had stale source-text attestations. Directed receipt hashes and identities were checked. Inferred referenced bindings agree with the old attestations.
- A real-object addend control changes a full binding by 0x30000: LO16 still matches, HI16 fails. `screen_summary.json` records the observed fields. The 3+ MB detailed screen stays under ignored scratch with its SHA256 and compact summary, per decision 62.
- 12 converted placements use objects whose entry symbols differ from their home load addresses. Their entries explicitly bind those actual object symbols to their placement VMA. The scoped gate also exposed a pre-existing LL2 placement whose legacy entry name blocked local .rodata lookup. An entry-only binding repair restores that resolver. Its complete dependency scope is one window; the repair was applied under the build lock while that window was still queued behind the unknown-cost frontier, so the same scoped run proves it. See queued_repair.json, existing_repair_plan.json, repairs.tsv and gate_summary.json. No function/source names changed.
- 8,935 old resolution checks pass. 3,097 explicit bindings preserve existing placements when new local definitions change rule 3. Final resolver bindings and rename collisions were checked on the actual object symbol sets.
- Split records, instance promotion events (result=promoted, superseded_by=row), and L0 baseline adoptions are append-only. Every new placement has an exact home-proof baseline adoption under decision 50. There are no new copy source/raw files.
- 195 home TUs serve 1,080 placements in 192 images. 212 link lists change (31 new lists). 94 bounded windows cover candidates that previously lacked a production window; their bases come only from existing proven rowbase records. Rowbase files, source bodies, names and gate tools do not change.
- Registry, source indices and physical module graph regenerated; source_layout check and row_db check pass. gen_noreturn_syms --check passes unchanged (main 32, town 213, dungeon 1,014, ovmovie 0). No full gate was run.

The final scope includes split/registry intersections (including partial intersections), changed link-list dependencies, bank frozen-source sets (new placements add absent raw paths), and dependent module-window fingerprints. Exact before/after input hashes are measured at the same canonical root. The conservative scope had 1251 windows; 1251 actually re-keyed, and 0 unchanged windows were removed.

## Holds by reason

| Reason | Instances | Bytes |
|---|---:|---:|
| Existing registered rows overlap the proven instance span | 10 | 11,820 |
| Legacy home split/symbol identity disagrees with proven rowbase | 2 | 164 |
| Home lies outside any proven image region | 3 | 292 |
| Total | 15 | 12,276 |

Overlap holds include 80 bytes already owned by existing rows; their still-uncovered bytes total 11,740. They require an ownership decision before any row retirement or replacement. Home identity holds are town/func_806C90F8 and town/func_806C91D8. The remaining three placements depend on town/func_8080E534 or town/func_808105EC, whose homes lack proven image regions.

## Deliveries

- `delivery.patch`: text-only patch against the staged root base, including generated registry/index/graph outputs. `patch_summary.json` records SHA256 and file list.
- `results.tsv`, `holds.tsv`, `windows_union.txt`, `gate.log`, `REPORT.md`.
- `controls.json`, `screen_summary.json`, `integrity.json`, `scope_summary.json`, `repairs.tsv`, coverage before/after, and `patch_check.log` are compact supporting evidence.
- Lane-local reproduction scripts: `ll3a.py`, `make_windows.py`, `regen.py`, `complete_scope.py`, `exact_scope.py`, `run_gate.py`, `make_delivery.py`, `apply_existing_repairs.py`, `repair_queued_window.py`, `finish_gate.py`. Objects, gate build products, and the large detailed screen remain local scratch/build outputs and are not in the patch.

## HOW TO CONTINUE

1. Review/apply delivery.patch against the matching staged B10 base. The patch is checked by applying it to a separate pristine subset and comparing all changed files byte-for-byte with this private root. Run the normal registry/index/module-graph regeneration after integration.
2. Run row_db/source_layout checks, then a four-worker gate restricted to windows_union.txt. Lane journals document this private proof; the integration root must establish its own current input hashes. Renew affected module certificates through the normal landing flow.
3. Resolve the ten overlap ownership holds before replacing any existing row. Reconcile the two legacy home identities with proven rowbase, and establish proven home images (or independently screen an already-proven donor) for the three remaining town placements. Then repeat the paired screen and gate only their new input changes.
