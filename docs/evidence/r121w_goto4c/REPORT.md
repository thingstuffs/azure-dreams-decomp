# r121w_goto4c

Base: B13 private snapshot `ddc07bc5949684593cdc45a67e378a1f18324318`. No Git metadata is present; `preimage_manifest.json` binds the supplied file preimages and final patch. No commits or ref moves were made.

**Seven gotos removed across five existing homes; all five are goto-free and independently byte-exact at their existing `2.7.2-cdk-G0` recipes.** The fixed queue is **119 -> 112 gotos**, including its one frozen relink copy. The authoritative home-only subset is **118 -> 111 gotos** across 67 homes. All 68 queue files have a `results.tsv` line: five exact, zero installed partial, 62 held homes, and one held non-home copy skipped under LL4.

**39 / 39 scoped production windows MATCH, with the final current-input audit passing.** Scope: 39 windows, 90 rows including six existing link-list placements and the sibling rows of two native modules. These five home extents total 3,532 bytes; they are existing coverage. New rows and new coverage bytes are both zero. The six placements of `80D6A4D8` now share its goto-free source. No shared headers, link lists, registry rows, recipes, rowbases, raw first passes, or promotion records changed.

**Per-item status**

| Home | Gotos before -> after | Exact extent |
|---|---:|---:|
| `dungeon/func_80D6A4D8` | 2 -> 0 | 2308 bytes |
| `dungeon/func_800C30E4` | 2 -> 0 | 188 bytes |
| `dungeon/func_81810198` | 1 -> 0 | 484 bytes |
| `dungeon/func_800B62E0` | 1 -> 0 | 416 bytes |
| `dungeon/func_800A1284` | 1 -> 0 | 136 bytes |

`results.tsv` gives before/after counts, measured shapes, best candidate, aligned substitutions/indels, and status for every queue item. `holds.tsv` gives a concrete continuation route for each remaining item. `80B8B054` is the frozen non-home relink copy; its one goto remains untouched as instructed.

`80D6A4D8`: repeat the one-statement flag tail in its earlier arm, and repeat the timer/deceleration return tail in the approach arm. Each closes independently; both together preserve all 2,308 bytes and the switch targets.

`81810198`: break from the real three-resource scan and return through the existing common join. Replacing the goto with a direct return instead changes five register uses around the saved object and global-flag update.

`800B62E0`: index the existing setup base by `angle_index * 2`. The straightforward do/while reverses the otherwise-unused counter into 4..0 and loses one instruction. Giving the index its real address use preserves all 416 bytes.

`800A1284`: derive the scaled spawn value from `(call_index + 2) << 16` inside the real first loop. The live index prevents the extra held-step register introduced by the direct do/while spelling. All 136 bytes match.

`800C30E4`: retain the existing threshold/result carriers, use short-circuit threshold arms, and return the result from the failed sign-test arm. Sharing all results in one final return converts the sign test into three different instructions. The early failure return preserves the retail branch and all 188 bytes.

**Additional exact partial candidate, unapplied**

`candidates/func_8187C45C/duplicate_reach_target_clean.c` removes one goto (**5 -> 4**) by copying its short target-position/return tail and deleting the original unreachable stub. Complete-TU comparison proves both retail and genuine ASPSX 2.79 equality for `dungeon_ovl_189a800`. A lane-local script initially shadowed Python's `inspect`, so that attempt was correctly recorded as a harness error. Its corrected recheck completed after the final production gate had launched. The candidate is also provided as `followup_candidate.patch`. It remains unapplied and outside `delivery.patch`; the single production gate's scope remains unchanged. This is an exact partial candidate, not an installed cleanup or a coverage claim. Its source and compact proof metadata remain available in this lane.

**Measured holds**

| Hold reason | Files |
|---|---:|
| structured source mismatch: addressing | 10 |
| structured source mismatch: polarity | 11 |
| exact partial candidate held outside frozen production-gate scope | 1 |
| structured source mismatch: code-motion | 2 |
| switch-target or compiler validation failure | 5 |
| structured source mismatch: length-drift | 4 |
| structured source mismatch: hold-set | 3 |
| structured source mismatch: reg-rename | 2 |
| structured source mismatch: broad | 6 |
| structured source mismatch: block-order | 5 |
| complete-module retail or extent mismatch | 2 |
| structured source mismatch: slot-rotation | 6 |
| structured source mismatch: li-expansion | 4 |
| non-home frozen relink copy (LL4 skip) | 1 |
| structured source mismatch: const-remat | 1 |

The numeric residue classes describe the best measured source shapes, not compiler-version walls. The child-cleanup loop in `8185D488` is three substitutions from exact: its structured loop addresses children from `ctrl + 0x34` with zero displacement, while retail retains `ctrl + 0x1c` with displacement `0x18`. The full retail site map, consistent CDK lineage scan, aligned regions, and ordinary for/while/indexed variants are retained in `evidence/` and `candidates/`. The closest optional-random-arm spellings in `80B73054` and `80B7F054` remain one branch displacement off. Both are genuine holds, not near-miss landings. The renderer's full face/edge rewrite removes all nine gotos in its candidate but remains 122 aligned edits away.

All 67 home preimages were verified exact; three require their complete native-module context. There are 257 recorded measurements and 184 distinct post-baseline shape names. Repeated measurements, rejected control-shape attempts, and harness failures are explicitly distinguished in `measurements_reviewed.jsonl`; no invalid candidate is used to justify a landing. The original chronological records remain in `measurements.jsonl`.

**Deliveries**

`delivery.patch`, `results.tsv`, `holds.tsv`, `touched_windows.txt`, `gate.log`, this report, and `preimage_manifest.json`. The separate `followup_candidate.patch` is an unapplied exact partial candidate. The main patch contains only the five source files and compact ledger changes: exact reverify facts, scoped gate facts, and the two refreshed module certificates. It contains no lane paths, binaries, retail bytes, or new forbidden C mechanisms. No shared header extensions were needed. `patch_check.log` records reconstruction from the B13 preimages and final-hash equality.

Internal compiler objects, retail slices, disassembly, and module/window proof payloads remain in ignored private directories. Larger receipts are represented in `evidence_summary.json` by summaries and SHA-256 values; they are not shipped in the patch. The module certificate files reference those private proof directories. An integration checkout must regenerate those proof payloads from the canonical sources before treating the certificates as fresh there.

**HOW TO CONTINUE**

1. Apply only `delivery.patch` to the B13 preimages bound by `preimage_manifest.json`. Check all before hashes and the patch hash. Keep the existing six placements; they earn no new coverage. Do not reset the raw baseline or promotions ledger.
2. Start the projectile home from `candidates/func_8187C45C/duplicate_reach_target_clean.c` and its `duplicate_reach_target_clean_native` receipt. Four gotos remain: collision handling, fade completion, the particle loop, and the busy-flag tail. Finish those shapes with complete-module substitutions; include all affected `dungeon_ovl_189a800` windows in the next final scoped gate.
3. Continue the one-word random-arm holds and the three-word child-cursor hold from the candidate paths in `holds.tsv`. Preserve the common argument-copy entry in the former and cursor bias/live ranges in the latter. Use aligned regions at the existing recipe; no new masks, casts, pins, barriers, or recipe changes are justified by these measurements.
4. Use each row's `how_to_continue` field for the remaining queue. Keep switch-target and complete-module failures visible. The non-home `80B8B054` copy stays for LL4.
5. After additional exact changes, refresh the exported roster and source projection, recompute source/placement/module/window closure, validate the view, and run one scoped production gate with `--workers 4 --only-window ...`. Renew native-module certificates by consuming that gate's fresh receipts, with every certificate window reused.
