# Reproducible B13 census

From a fresh clone at B13 plus the cumulative patch, run:

```sh
python3 tools/census/regenerate.py --disc /path/to/Azure_Dreams.bin \
  --output /tmp/azure-census --check
```

Only Python 3's standard library and a user-owned US disc BIN/ISO are required.
The command verifies the committed input snapshot, extracts five containers into
a temporary directory, checks their SHA-256 identities, runs the census without a
cache, then generates and compares the exact `link/` byte-map file set. Success
means every generated file is byte-identical to git. `regeneration_receipt.json`
and `coverage.tsv` are in the output directory. Raw spans are ignored outputs,
never prerequisites. Output retail containers are removed on exit.

`config/census/snapshot.json` records the B13 metadata/source snapshot and retail
identity hashes. `typed_data.jsonl` contains 69 bounded reads still valid on B13;
`replayed_prefixes.jsonl` contains three strictly checked prefixes. The 541 stale
historical proposals are omitted. Source and binary identities, instruction hash
and load opcode, C read extent, complete donor extent and relocation masks are
checked again each run. No proposal is re-signed. `slus_layout.json` is linked
section geometry, and `cd_bank_map.json` records conditional static loader extents;
it makes no runtime-observation claim. None contains retail payloads or binaries.

`rules.json` maps each committed rule ID to its evidence kind and census label.
In `census.py`, `ledger_layers` builds the ledger/layout layers, `apply_read_evidence`
and `apply_replayed_code` validate the bounded inputs, `binary_pass` calls the code
and data detectors, and `label` applies precedence. The format detectors are
`det_tim`, `det_vab`, `det_seq`, `det_tmd`, `det_adpcm`, `det_ptrtab`, `det_offtab`,
`det_sjis` and `det_ascii`. `det_zero` implements `census:zero_fill>=16`;
`noncode_decode` implements `census:noncode:decode`.

`validate` measures detector precision before `admitted_tiers` applies the exact
0.999 threshold. `masked_prefix_probe.validate` uses fold-crossed positives and
union negatives; `apply_masked_prefixes` only recovers unknown bytes when both
precision gates admit it. `validate_neighbours` and `apply_neighbours` use the
original immediate neighbours simultaneously, so new labels cannot propagate.
They protect return words. The unit tests exercise these gates and refusal paths.

The precedence is proven code, library code, ledger/format data, explicit stale
images, admitted strongly-code tiers, independently confirmed audit data, ledger
padding/zero runs, terminal non-code, and remaining unknown. The final prefix and
neighbour passes may consume only bounded eligible unknown intervals. All seven
labels remain distinct, and no census tier creates a compiled TU. See
`docs/LINK_LISTS.md` for the compact representation and validation commands.

```sh
python3 -m unittest discover -s tools/census/tests -q
```
