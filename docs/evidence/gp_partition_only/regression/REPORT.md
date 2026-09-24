# Partition-only candidate regression

Private test root with a copy of production tools overlaid by all nine pinned candidate tool files. The pinned SLUS build inputs and physical-certificate evidence are private copies. All import checks resolve to this test root, including the physical-certificate test’s explicit E/O loaders.

| Suite | Tests | Passed | Skipped | Failed |
| --- | ---: | ---: | ---: | ---: |
| slus | 151 | 151 | 0 | 0 |
| configure | 8 | 8 | 0 | 0 |
| aspsx_diff | 14 | 14 | 0 | 0 |
| partition_only_evidence | 9 | 9 | 0 | 0 |
| **Total** | **182** | **182** | **0** | **0** |

The suite exercises module, partition, plural collector, data-piece, fidelity, ownership, certificate, configure, and new partition-only evidence contracts. It does not run a genuine compiler or full-image integration gate. No production files were written.

Details and exact test IDs are in `regression_receipt.json`; raw logs are beside it.
