# LL3b / LL3c / LL4 delivery

Base: supplied B13 private snapshot `ddc07bc5949684593cdc45a67e378a1f18324318`. The supplied tree has no Git metadata; a SHA-256-bound copy of every starting file changed by this lane is preserved under ignored `scratch/base/`. The patch is a text diff against those exact starting files. All work and outputs stayed in this private root and lane.

## Per-item status

Measurement complete. The brief's 242,312 bytes reconcile to **236,296 uncovered proven-instance bytes** in this snapshot. The 6,016-byte difference is exactly four already registered 1,504-byte dungeon placements of `dungeon/func_81005278`; see `already_placed.tsv`. Their old instance events still say proven, and coverage correctly gives registered rows priority. There is no double credit.

| Container | Brief bytes | Starting remaining instances | Moved to C by this patch | Remaining proven-instance bytes |
|---|---:|---:|---:|---:|
| town | 184,048 | 184,048 | 178,768 | 5,280 |
| dungeon | 56,972 | 50,956 | 12,824 | 38,132 |
| main | 1,292 | 1,292 | 1,292 | 0 |

LL3b: no fully proven, uncovered instance remains in a solved region. The 12 solved-region partials (7,032 bytes) require C/proof work before promotion. No rowbase region was promoted or weakened.

LL3c: **1,662 instances / 192,884 bytes** become fileless placements. Every admitted instance compiles current home text; 1,615 had a since-changed source attestation. Exact full relocation evaluation precedes placement, with 2,652 paired HI16/LO16 sites across all admitted rows. Each placement adopts its home's exact baseline under decision 64 and retains its own window byte obligation.

LL4: **523 hand-copy rows** become placements. An additional 30 legacy relinks, whose headers were preceded by aliases, pass the same proof and are reported separately. Total source retirements: 553; raw retirements: 553; total files deleted: 1106. `ledger/raw_retired.jsonl` records each raw path, SHA-256 and home. The allowlist shrinks by 30 files.

The historical 743-row hand-copy roster is absent from the supplied references. A reproducible current census instead finds 1,020 ordinary module-context candidates / 233,068 bytes, plus 55 legacy relinks / 39,404 bytes. It requires body equality after address/registered-alias normalization and an immediately neighboring registered row at the same file displacement with an equal body and extent. Previously placed neighbors can witness context. Object equality and the gate decide admission. These figures describe this snapshot and method; they do not claim to reproduce the historical roster. `item_inventory.tsv` includes each context witness.

## Proof and tooling

A no-region image binds an exact current record in `ledger/instance_load_regions.jsonl` by canonical record SHA-256. The gate checks container, complete image containment, base/delta, row extent and split true name before taking the image VMA. Free-form evidence cannot authorize the new path; a solved region cannot opt into it. Existing legacy placements retain their original rowbase/window path. The evidence ledger participates in window fingerprints. MAIN's witness establishes a documented devkit-linked base; it does not establish runtime execution.

Assembler flags resolve using a placement's logical row identity. Negative tests cover stale/missing evidence, wrong geometry, absent authority, solved-region bypass and proven-base disagreement. A real native-object control changes a binding by 0x30000: LO16 stays equal and HI16 rejects it. No relocation field is masked in the admission byte comparison. No C bodies, names, compiler binaries or retail data are added.

Existing resolver values are preserved before newly local definitions can change them. `resolution_preserved.json` records 6,512 old resolution checks and the inserted explicit preservation bindings. `integrity.json` checks every actual relocation binding for every admitted object. The final resolver also reproduces all 2,215 retail extents after evaluating 8,572 actual relocation fields. Three alias collisions were withdrawn before gating; five proposed homes found to be legacy relinks were also withdrawn. Frozen noreturn name sets remain identical in all 476 retired-raw bank scopes. Physical module members remain held for LL5; no L4/L5 certificate is granted by this lane.

Registry, source indices and physical module graph regenerated. Row database and source layout pass; 24 link-list tests pass. The tracked noreturn audit also passes unchanged (MAIN 32, town 213, dungeon 1,014, movie 0); admitted objects have zero COMMON allocations. Metadata preflight loads 1,916 active windows / 19,189 matched segments without failure. Scope includes converted/split intersections, homes, changed link-list dependencies, raw-bank neighbors and the home evidence scopes used by remote placements.

Final gate: return code 0; **{'MATCH': 1917}**, 1917/1917 windows, elapsed 14950.4 seconds. One scoped invocation uses `--workers 4 --all` over 1916 windows; 1 required per-row home-window check completes the union. The main gate closing audit and the per-row pre/post checks verify current input hashes.

The two changed gate tools re-key global tool identities. This lane runs only its content dependency union as instructed; integration must include the normal consolidation gate for other windows and renew any affected module certificates. Private module proof bundles are rebuilt by the normal gate rather than assumed present.

Queued metadata correction: the 252 new YAML SHA-1 fields initially held slice hashes. They now hold full-container hashes, matching the extractor contract. All changed windows and both affected town modules were still queued. One additional required home window is checked after the four-worker run; `queued_repairs.json` records the exact scope and hash changes.

## Holds by reason

| Reason | Items | Span bytes | Still-uncovered instance bytes |
|---|---:|---:|---:|
| ambiguous_existing_image | 198 | 7,488 | 1,736 |
| copy_is_existing_linklist_home | 6 | 2,520 | 0 |
| copy_is_physical_module_member | 109 | 22,580 | 0 |
| current_object_not_exact | 17 | 5,984 | 0 |
| existing_row_overlap | 10 | 11,820 | 11,740 |
| home_is_legacy_relink | 5 | 3,508 | 0 |
| home_or_copy_identity_disagrees_with_rowbase | 5 | 408 | 408 |
| home_or_copy_missing_load_evidence | 16 | 2,936 | 292 |
| missing_load_evidence | 47 | 28,720 | 28,720 |
| native_object_shape | 120 | 165,524 | 132 |
| no_independent_home | 81 | 2,844 | 0 |
| object_symbol_alias_collision | 3 | 384 | 384 |
| partial_instance_requires_C_work | 306 | 160,112 | 160,104 |
| raw_retirement_changes_frozen_census | 1 | 480 | 0 |

`holds.tsv` contains all 924 held items with their exact reason and next action. Span bytes include already-C copy rows and partial ownership overlaps; they must not be added to the remaining-instance coverage partition. There are 1758 initial proven spans and 306 uncovered partial spans. Coverage uses interval unions and subtracts existing row ownership.

## Deliveries

`delivery.patch`, `measure.tsv`, `results.tsv`, `holds.tsv`, `touched_windows.txt`, `gate.log`, and this report. Supporting files include `item_inventory.tsv`, `already_placed.tsv`, `reconciliation.tsv`, `hold_summary.tsv`, coverage before/after, screen/load/census/integrity/control summaries, `gate_summary.json` when complete, and patch validation. Large screen and inventory JSON stay in ignored scratch with compact SHA-256 summaries. Native objects and build outputs remain local; they are not in the patch. Lane scripts preserve the measurement, context census, current-object screen, conversion and delivery procedure. Start measurement/conversion in a fresh matching base; clear scratch/objects when compiler, headers, ccproc or bank evidence change.

## HOW TO CONTINUE

1. Apply `delivery.patch` to the matching B13 snapshot; inspect `patch_summary.json` and `patch_check.log`. Regenerate registry, managed projection and module graph with the normal tools. Run the integration consolidation gate with four workers; the lane replay is `python3 run_gate.py` from this lane after removing/archiving its scratch journal.
2. Recover independent loader or pointer-table witnesses for missing-load holds before adding their image descriptors. Resolve catalogue ambiguities and legacy home identities with the physical-owner evidence. The three alias-collision rows require alias-preserving linkage or a reviewed alternative home.
3. Follow `refs/LL5_PLAN.md` for physical module members and complete native allocation/rodata proofs. Keep partial instances and span-overlap holds out of the placement ledger until their own C/ownership proof is complete. Rerun the native screen and gate the newly affected union for each continuation batch.
