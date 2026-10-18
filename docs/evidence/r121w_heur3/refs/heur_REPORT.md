# r121_heur cumulative delivery

Base: `42fd882da7f1dbd2a563da18c938015e6d9e9135` (private source snapshot; no Git metadata). Work and generated artifacts stay inside the private root. No binaries or retail asset bytes are delivered.

## Per-item status

- Inventory: complete, 628 original heuristic spans / 377,312 B; matches the supplied brief. `inventory.tsv` preserves original priority and extents.
- Classification: every original byte has one non-overlapping `results.tsv` outcome; span_status.tsv rolls these up to all 628 original spans. Class a contains 307,408 B: delivered compiler/linker proofs and complete byte-identical donor copies whose placements are held. Relocated discoveries remain class e until actual ELF replay. 305,440 B have full production placement proof. Class b identifies semantic variants, with delivered new C and remaining holds listed separately below; classes c/d have no admitted claims. A masked donor hit alone never changes coverage.
- Copies: 365 shared-TU link-list placements / 305,440 B delivered; no new src/ or raw/ copy files. LL0 derives source_row through the normal registry function.
- New code: the initial survey found 48 complete variant sites / 3,880 B with unported twins (initial class b), supported by original complete donor extents, instruction/register agreement, complete entry/terminal checks and a second full-body twin. 17 new C row(s) / 1380 B delivered with genuine raw and exact source/window proofs. Their proved copies use LL placements; results.tsv separates the remaining holds. No non-code labels or runtime contracts are asserted. 11 pre-existing solved regions additionally pass the same normal strict promotion hook without any extent or delta change. The old static-proof narrative is preserved. Its historical JSON reference is absent in this snapshot; fresh target jump witnesses and the actual strict C promotion are recorded in solved_candidates.json/solved_promotions.json. Those unique configuration records are updated in place by the unmodified hook; all row/split/baseline ledger prefixes remain intact. 5 tight rowbase regions / 4,640 B passed the unmodified solved-to-proven promotion hook; every proposal has two distinct internal jump anchors and a strict linked C comparison.
- Census handoffs and unknowns: all physical records are cross-referenced in handoffs_audit.tsv and unknowns_audit.tsv; nonpositional terminal data aggregates remain separate. No new labels are asserted in these secondary queues.

## Counts and gates

| container | original bytes | delivered C bytes | held bytes |
|---|---:|---:|---:|
| dungeon | 351,148 | 302,616 | 48,532 |
| town | 22,240 | 4,204 | 18,036 |
| main | 3,924 | 0 | 3,924 |

| class | outcome | partition items | bytes |
|---|---|---:|---:|
| a | DELIVERED_LINK_PLACEMENT | 365 | 305,440 |
| a | HOLD | 9 | 1,968 |
| b | DELIVERED_NEW_C | 17 | 1,380 |
| b | HOLD | 4 | 272 |
| e | HOLD | 754 | 68,252 |
| c | no claims | 0 | 0 |
| d | no claims | 0 | 0 |

Original spans: 256 DELIVERED, 347 HOLD, 25 PARTIAL.

Combined final-tree verification: MATCH; 123 windows, 382 exact compiled-C extent/object checks. Binding negative control: PASS. Frozen interval/census/source audit: PASS. See evidence/final_gates.json and evidence/negative_control.json.

123 complete production windows MATCH. 17 new C row(s) retain their measured source and raw results in the normal ledgers. Every delivered placement extent is present as compiled C in its production manifest, resolves to its home TU, uses the donor recipe and has an independent ELF relocation check for every differing word. Row database checks pass after each successful transaction. Existing retail hashes and home source hashes bind the receipts. Compiler output stays in ignored scratch/build paths.

## Deliveries

`delivery.patch` and `delivery_manifest.json` are cumulative against the supplied SCRATCH_HEAD content. `results.tsv`, `holds.tsv`, `levels_seed_needed.tsv`, `link_list_entries.tsv`, `evidence/placements.json`, `evidence/summary.json`, and the scripts are text-only receipts. Link lists are in `config/link/<container>/heur_*.json` and included in the patch. scripts/check_delivery.py reconstructs the patch against frozen before-images; evidence/patch_check.json records the verified final patch hash. Placements reuse the home raw baseline; copies require no new m2c pass. New C retains its genuine m2c first pass and its actual normal scorer measurements. Compiler and gate implementations are unchanged. The normal view builder regenerates the physical module graph; its compact hash/check receipt is in final_gates.json, while the multi-megabyte derived graph cache is rebuilt during integration. An existing source fix adds its already existing guarded module header to src/dungeon/func_80F88C94.c, allowing independent compilation. Its normal source score is zero and its original full production window matches (evidence/standalone_fix.json). The type interface repair (evidence/effect_interface.json) moves the existing EffectColor definition unchanged from its earlier module member into their already shared guarded header; both affected members score exactly and all three home windows MATCH. Exact source repairs are recorded in evidence/palette_adoption.json and evidence/item_adoption.json: the former names the palette symbol directly and the latter names an independent state halfword instead of deriving it from a neighboring table. Both repairs have fresh zero-difference source scores and every home window MATCH. Their recovered copies separately passed linked ELF replay. Existing control flow in a shared donor, including goto, is reused without creating source copies; the strict source rules apply to newly written C. Each of the 17 new C rows has a source/raw pair and English snake_case function alias; baseline failures remain measured failures.

## Holds by reason

| reason | bytes |
|---|---:|
| no complete registered C donor at bounded survey offset; code/entry or non-C donor evidence still needed | 35,636 |
| donor source debt: volatile | 17,476 |
| native placement replay mismatch; symbol or address-literal recovery needed | 8,592 |
| no unique proven rowbase for complete target | 7,004 |
| complete target entry lacks independent boundary/reference | 1,512 |
| complete unported variant twin; genuine m2c, clean C rebuild and production proof needed | 272 |

Discovery currently covers 738 complete masked donor leads / 341,436 B; the other 35,876 B require further boundaries/donor or data evidence. Tiny epilogue twins with no independent entry are held. The three volatile donor homes were measured with qualifiers removed at their stock recipes: 24, 24 and 14 differences (volatile_homes.json), so those repairs are not adopted or credited. Missing proven rowbases and donor source debt are explicit. `ref/handoff_code.tsv` and `ref/next.tsv` retain their original meaning and are not counted as this lane’s deliveries.

## HOW TO CONTINUE

1. From this lane, run `python3 -I scripts/place.py` to resume serial placement transactions in original span priority. Completed successes and failures are checkpoints. Do not run a second mutation runner. Use `--batch-groups 12 --jobs 6` to gate independent windows together and `--limit-groups N` for bounded checkpoints. `--retry-home dungeon/func_80F88C94` retries only compiler holds for the repaired home; use the equivalent flag only after proving another home repair. `--retry-replay-home <row-id>` retries native replay holds after a proved source-symbol repair; the admitted palette and item repairs are examples. `--retry-row-ids` retries historical ID collisions using unique ledger labels; it does not change any linked address.
2. evidence/SYMBOLIC_REBUILD.md records the attempted symbolic-table C repair of dungeon/func_812A85D4. The best natural symbolic version remains two substitutions from retail; retain the exact original and investigate the high-half carrier/coalescing in RTL before further C edits. The normal recipe comparison did not justify a compiler change. The analogous 724-byte motion home also has a measured two-substitution symbolic candidate (motion_symbol.json); neither repair is adopted.
3. For missing entry evidence, prove the complete function start from its preceding function, matched caller/pointer, or loader image. For missing rowbase, require an independent image/base proof before normal promotion. For source-debt and differing literal/member-offset variants, use the original source evidence and normal C rebuild; no relocation masks or copy source files.
4. Process residual class e extents with genuine m2c first passes; compare non-C twins across placed images. Type non-code only with independent proof, applying decision 58 in-place split corrections or active:false coverage events.
5. Rebuild/export the affected view, require exact row scoring for new C and every covering full production window. Run `python3 tools/row_db.py check`; regenerate `python3 -I scripts/publish.py` here after each change.
6. The original inventory is frozen: do not rerun scripts/inventory.py against a changed tree. After new deliveries, rerun discover.py (preserving variant_twins.json), place.py, audit_queues.py and publish.py; require final_audit.py, negative_control.py and final_gates.py, then publish.py and check_delivery.py in that order. A fresh publish changes the patch hash, so run check_delivery.py last.
7. At integration, apply the text patch at the recorded base, refresh `bash tools/build/mk_ovl_root.sh`, export/check row DB and gate the listed windows. Seed new placement levels according to integration policy. If other changes have landed, re-gate the combined tree first.

## Continuation delivery 2 — incremental above wave 1

Wave 1 was already applied: its 626-file manifest matched exactly. `delivery_wave1.patch`, `results.tsv`, and `holds.tsv` are unchanged; the original report is retained above. This addendum and `delivery2.patch` contain only continuation work.

### Per-item status

| container:file offset | bytes | status |
|---|---:|---|
| dungeon:0xc41ba8 | 1320 | DELIVERED link placement from dungeon/func_80C15BA8 |
| dungeon:0xc53ba8 | 1320 | DELIVERED link placement from dungeon/func_80C15BA8 |
| dungeon:0xd23850 | 1316 | DELIVERED link placement from dungeon/func_80CEB850 |
| dungeon:0xd23d74 | 1068 | DELIVERED link placement from dungeon/func_80CEBD74 |
| dungeon:0xd21f34 | 1044 | DELIVERED link placement from dungeon/func_80CE9F34 |
| dungeon:0xd23444 | 884 | DELIVERED link placement from dungeon/func_80CEB444 |
| dungeon:0xd22348 | 868 | DELIVERED link placement from dungeon/func_80CEA348 |
| dungeon:0xd20564 | 848 | DELIVERED link placement from dungeon/func_80CE8564 |
| dungeon:0x18ada2c | 460 | DELIVERED C: create_moving_fading_particle |
| dungeon:0x134a660 | 208 | DELIVERED C: update_receding_scaled_rgb_fade |
| dungeon:0xd21e78 | 188 | DELIVERED link placement from dungeon/func_80CE9E78 |
| town:0x50d64 | 116 | DELIVERED C: advance_actor_reaction_downward |

Delivered 9,640 new bytes: 9 placements / 8,856 B and 3 new C rows / 784 B. Combined with wave 1: 316,460 / 377,312 B delivered; 60,852 B held.

Largest volatile families remain held after measured clean-source lifetime probes and scheduler RTL attribution. The 348-byte town initializer improves to 3 substitutions / 10 indels but remains held. The 388-byte dungeon prefix requires correction of an existing eight-byte return owner. Internal tails were read and remain boundary/ownership holds. See evidence/CONTINUATION2_NOTES.md.

The single final scoped production run used `--workers 4` with nine explicit `--only-window` arguments from touched_windows2.txt: all 9 windows MATCH. All 12 exact compiled-C extent/object checks pass, as do 234 changed-field ELF relocation checks, current input fingerprints, normal row DB validation, and the regenerated module graph. Canonical source scores are zero for all three new rows; measured failing raw baselines are preserved. No compiler, assembler, scorer, or gate implementation changed.

### Deliveries

- `delivery2.patch`: apply after `delivery_wave1.patch`; incremental text changes only.
- `results2.tsv`: partitions only the incoming 70,492 B hold queue; wave-1 successes are not repeated.
- `holds2.tsv`: every remaining hold with a reason; `touched_windows2.txt`: the exact final gate scope.
- `link_list_entries2.tsv`, `levels_seed_needed2.tsv`, `gate_results2.tsv`, `evidence/final_gates2.json`, `evidence/summary2.json`: integration and proof receipts.
- `delivery_manifest2.json` and `evidence/patch_check2.json`: hashes and exact incremental patch reconstruction.

Two new production windows cover complete 1,320-byte functions that straddled older windows. The matching old image deltas are preserved and their left-edge extensions pass the unmodified strict promotion hook. Seven other tight rowbases are new independently proved extents. Link placements reuse the donor TU; there are no new C/raw copy files. Derived module graph and object/retail binaries are excluded from the patch.

### Holds by reason

| reason | items | bytes |
|---|---:|---:|
| no complete registered donor / boundary evidence | 396 | 27,060 |
| donor source debt: volatile | 13 | 17,476 |
| native replay mismatch / symbolic-address recovery | 12 | 8,592 |
| no unique proven rowbase for complete target | 131 | 5,052 |
| entry lacks independent boundary/reference | 181 | 1,448 |
| existing return-row ownership conflict | 1 | 388 |
| new C scheduling/lifetime mismatch | 1 | 348 |
| complete unported variant twin; genuine m2c, clean C rebuild and production proof needed | 4 | 272 |
| internal tail / full-function ownership | 3 | 216 |

### HOW TO CONTINUE

1. Apply wave 1, then `delivery2.patch`. Refresh the ordinary view with `bash tools/build/mk_ovl_root.sh`; seed only the rows in `levels_seed_needed2.tsv`. Regate the listed windows if integration changes any bound inputs.
2. Start from `holds2.tsv`, ordered by container and decreasing bytes. Do not rerun the original inventory or old `publish.py`: it overwrites the wave-1 report and regenerates a cumulative patch. `scripts/package2.py` regenerates and reconstructs this incremental patch from frozen wave-1 content.
3. Keep one serial mutation owner. Wave-2 base proofs, new-source/raw measurements, final gate receipts, and per-field checks are under `evidence/*2.json`. Do not rerun `stage2.py` or `gate2.py`; both deliberately refuse duplicate work. The gate invocation count is one.
4. For the 1,420/1,400-byte volatile donors, study the scheduler anti-dependency and natural target/coordinate lifetimes described in CONTINUATION2_NOTES.md. The measured direct-store, target-local, state-local, and narrow-coordinate probes do not match. Keep the original exact sources until a clean repair is proved.
5. For the 724/708-byte replay families, retain wave-1 SYMBOLIC_REBUILD.md and its two-substitution symbolic candidates. For the 348-byte town function use the best retained countdown candidate and the full retail map; its frame/roles match, and the residual is sentinel reset scheduling plus a redundant signed-byte branch.
6. Repair the standalone return-row ownership before admitting the complete 396-byte function at file 0x1344F20. Reconstruct whole function ownership for the live-register tails; do not label them data or independent entries. Missing bases and tiny leaf entries still need independent image/reference evidence.
7. A later delivery must freeze the post-wave-2 tree as its own incremental base. Run one final production gate scoped to its touched windows, with four workers. Package only fresh successes and explicit holds; no copied C, forced volatility, pins, instruction rewrites, or binary payloads.
