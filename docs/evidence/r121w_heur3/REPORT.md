# r121w_heur3 — partial delivery against B13

Base: `ddc07bc5949684593cdc45a67e378a1f18324318`. **36 new C rows / 3,520 bytes**, all in TOWN. **One scoped production invocation, four workers, one window MATCH**. Canonical source scores: 36 exact, zero substitutions or indels. Genuine raw baselines: 36 compiling but different; all raw differences remain measured differences. No compiler, assembler, scorer, window, existing C source, source recipe or rowbase changes.

## Per-item status

| Item | Status | Delivery / remaining |
|---|---|---|
| Heuristic-only spans | Partial C delivery | 52,508 -> 48,988 B; 3,520 new C bytes |
| MAIN heuristic | Held | 3,924 B; no new C |
| TOWN heuristic | Partial | 13,464 -> 9,944 B; 36 new C rows |
| DUNGEON heuristic | Held after bounded donor replay | 35,120 B; no new C |
| Undecompiled split bucket | SDK classification reconciled | 1,396 -> 0 B in that bucket; library code rises by 1,396 B, C credit zero |
| SLUS other bucket | Audited, held | 204 B startup assembly; 24 B already declared data/padding in its historical 228 B bucket |
| Census handoffs | Audited, held | All 67 supplied records reconciled; 45 placed handoffs remain. The 84-B TOWN caller at 0x5c70c8 has an exact clean candidate but its true-address name is already used by another scene |
| Census next queue | Reconciled, held | 647 supplied records retained, including 16 terminal non-code aggregates; 18,954 residual positional bytes across the queue and repeated handoff holds |
| Prior heur holds | Partial | All 742 supplied records reconciled against B13 and this delivery; 48,988 B remain |

The queues overlap. Do not add their byte totals. `measure.tsv` covers the 337 original STATUS intervals and four SLUS pieces; `results.tsv` covers those plus every supplied TSV record. Each result partitions its own bytes into prior C, new C, SDK library, inherited non-code and held bytes. `holds.tsv` retains queue identity and exact residual extents. No data is promoted to C. No new non-code type is claimed.

## C behavior and proof

The new callbacks configure distinct slot/table/state values, copy global state, reset object handlers, update alternate menu bounds, arrange ten objects in columns and write alternate menu coordinates. Semantic constants and structure-member offsets differ from the existing donor bodies, so link-list rebinding cannot represent them. Each is a new home TU with its own genuine spimdisasm/m2c raw first pass and a snake_case function name. Existing donor text is unchanged. No copied relink or hand-copy source is modified or created.

Each new body has an independently matched C caller or an interior callback-table entry in its independently bounded proven load context. Existing donor declarations retain their interface. Aliased callee contexts require complete matched source/target callee bodies; their witnesses are in `evidence/staged.json`. Source and target instruction bodies are compared without admission masks. The final production manifest independently confirms that every one of the 36 exact extents is compiled from its registered source rather than supplied by raw fill.

The source scorer rejects a negative control that changes slot 28 to 29: one substitution, zero indels. All 36 clean source scores are zero; all 36 genuine raw first passes compile with differences. The raw files contain only the unchanged generator output behind the standard compatibility preamble. Baseline, promotion and reverify facts are appended; levels are left for ordinary integration policy.

## Classification correction

The 420 MAIN, 96 TOWN and 880 OVMOVIE split bytes were already identified as Sony SDK code in `docs/evidence/r121_remnants.sdk.json` and its report. The reporting path preferred historical raw splits, and then unported regions, over this library evidence. Five append-only coverage events reconcile 1,228 B from that existing evidence into the interval ledger. The other 168 B already had SDK intervals. STATUS now gives evidenced SDK intervals priority over raw split/unported views while retaining compiled-C/copy priority. The focused 10-test STATUS suite includes overlapping C, SDK, raw-split and unported witnesses. No SDK bytes are credited as C.

The SLUS 228-B bucket is 204 B at 0x101f8 plus three existing 8-B bin spans at 0x37e80, 0x39788 and 0x3d608. Those are two SDK header/data fragments and alignment padding; their declarations are preserved. This checkout has no complete linked SLUS executable proof, and no SLUS C or executable claim is made.

## Deliveries

- `delivery.patch`: text delta against B13, including the 36 source/raw pairs, append-only ledgers, names, SDK reporting correction and compact evidence under docs/evidence/r121w_heur3. No binaries or retail payloads.
- `measure.tsv`, `results.tsv`, `holds.tsv`, `touched_windows.txt`, `gate.log`, this report, `levels_seed_needed.tsv`.
- `evidence/final_gate.json`: exact production extents and source/object/target hashes, normal source/raw scores and the semantic negative control. `evidence/verification.json`: source debt, ledger prefixes and patch reconstruction.
- `evidence/discovery_summary.json`: summary plus SHA-256 of the large ignored donor-discovery receipt; masked leads remain discovery only. `evidence/large_entry_audit.json` records seven omitted eight-byte prefixes. All multi-megabyte receipts remain under ignored scratch or are regenerated.
- `scripts/`: bounded survey, native replay, semantic/layout reconstruction, staging, raw measurement, classification and packaging recipes. Discovery inputs are frozen; do not rerun the original inventory on the delivered tree.

The sole touched production config is `config/overlays/town_scene.overlay.yaml`. The source projection, row database and module graph are refreshed. The large derived graph is excluded from the patch and must be regenerated. Source/row/module identity tools and production gate implementations are unchanged. No module ownership or L4/L5 certificate is manufactured.

## Holds by reason

This table partitions the remaining original heuristic hold queue (48,988 B); the census and SLUS queues remain separate.

| Reason | Pieces | Bytes |
|---|---:|---:|
| no complete registered C donor at bounded survey offset; code/entry or non-C donor evidence still needed | 289 | 18,944 |
| donor source debt: volatile | 13 | 17,476 |
| complete twin lacks independent matched caller or pointer-table entry | 84 | 5,588 |
| retail difference lacks native ELF relocation | 8 | 4,104 |
| no unique proven rowbase for complete target | 119 | 2,208 |
| Prefix of a complete 396-byte function; terminal 8 B already owned by standalone row dungeon/func_813250A4; full-function ownership repair required | 1 | 388 |
| Internal function tail with live incoming registers; whole-function boundary/ownership reconstruction required | 2 | 144 |
| complete unported variant twin; genuine m2c, clean C rebuild and production proof needed | 2 | 136 |

Census placed handoffs still require complete clean C and actual entry/placement evidence. Seven 1,144-B DUNGEON detector starts omit an eight-byte load-before-prologue prefix; the complete candidates are 1,152 B and cannot be registered at the detector starts. Two 468-B handoffs have current clean donor leads but their leading extents lack a proven production rowbase. Tiny return tails are not minted as functions. No version-wall, data or leftover verdict is inferred from these holds.

## HOW TO CONTINUE

1. Apply `delivery.patch` at the recorded B13 contents. Run `bash tools/build/mk_ovl_root.sh`, `python3 tools/row_db.py export build_ovl`, and `python3 tools/row_db.py check`. Regenerate the module graph and derive the 36 levels listed in `levels_seed_needed.tsv` under integration policy. Re-gate the listed window if any bound inputs change during integration.
2. Freeze a new incremental base before more admissions. Use the remaining `holds2` rows in `holds.tsv` as the physical heuristic partition; census queues overlap it and each other. Do not rerun `survey.py` on a changed tree to replace the original inventory. Regenerate discovery from the corresponding base or retain the ignored scratch receipt, whose digest is delivered.
3. Largest remaining families: the 1,420/1,400-B volatile donors need a natural source lifetime/scheduling repair; the 724/708-B animation families need genuine symbolic relocations. Preserve existing exact homes and the prior reports. A native relocation hit is insufficient where even one differing word lacks an ELF relocation.
4. For the seven large census handoffs, start eight bytes before the detector entry as recorded in `large_entry_audit.json`. Recover the complete renderer C and its typed scratchpad/callee contracts, prove the entry, then register the entire 1,152-B extent. The two 468-B initializer copies need independently evidenced leading rowbase records and normal solved-to-proven promotion before link-list admission.
5. For the exact 84-B candidate at TOWN 0x5c70c8, resolve region-specific readable naming without changing the existing unrelated scene's alias. The candidate is reproducible with `variants.py`; keep it held until its definition can retain both correct semantics and the required production identity. Other small entries still need independent callers or bounded callback tables.
6. Preserve genuine raw generator output and actual failing baseline measurements. Require exact canonical source scores, compiled extent ownership and a single final gate with four workers over the new touched-window closure. Continue SDK/data typing from the existing evidence without calling it C. SLUS startup requires the complete ordinary executable link/SHA1 proof.
7. `package.py` rebuilds the text patch using local frozen before-images and reconstructs every file in an ignored check tree. A fresh checkout can apply and gate the delivered change; re-emitting the exact original patch also requires those ignored B13 before-images. The held donor caches and binaries are intentionally not distributed.
