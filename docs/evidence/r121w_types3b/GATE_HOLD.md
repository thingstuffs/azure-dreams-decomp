# Gate metadata hold — no production metadata/tool changes applied

The corrected final scoped gate produced 392 MATCH records before two jobs raised `KeyError: 'pins_left'` in `tools/gate/overlay_scoped_fingerprint.py:row_eligibility`. The unfinished configs are `town_scene.overlay.yaml` and `town_scene_79.overlay.yaml`. The error occurs while hashing neighbour eligibility, before those two byte gates complete.

`ledger/levels.jsonl` contains 40 existing sentinel records of exactly `{id, level: -1}`. They lack `pins_left`, `tail_jumps`, and `l4_residue`; the ledger's modification time predates this lane. None of their resolved source paths is in this slice. `metadata_blocker.json` records their IDs, source paths, timestamp and SHA-256. Missing fields must not be filled with zero or treated as a passing review.

The ledger and gate tool are outside the partition's allowed write paths. They remain unchanged. All delivered C type changes have exact home-row or complete-TU proof. The two broad town windows remain unproved by the normal gate.

A tool owner can either regenerate complete, truthful screening records or teach neighbour eligibility to represent an existing negative-level sentinel as unavailable. A conservative proposal for review is:

```diff
 def row_eligibility(row, level):
-    if level is None: return None
+    if level is None or level['level'] < 0: return None
```

This proposal is **not applied** and is not part of `delivery.patch`. Native member screening must continue to require complete records and L3 eligibility; positive-level records missing required fields must continue to fail. Any tool change needs its normal tests, fingerprint transition review, and renewed affected proofs.

HOW TO CONTINUE: resolve the sentinel handling under the tool/ledger owner, rerun the two held configs on the integrated source hashes, then complete the full scoped current-input audit. Renew every additional proof whose input digest changes under the repair. Keep the 392 existing verdicts as evidence at their recorded input hashes; do not label the failed aggregate invocation PASS or create a synthetic PASS index.

The atomic dungeon module's 20 required windows are disjoint from the two failures. Its scratch certificate reuses those actual successful snapshots only after a stock current-input audit and complete artifact-inventory checks. The canonical `certificate_reason` validator remains the final authority for that certificate. No global receipt index is fabricated.
