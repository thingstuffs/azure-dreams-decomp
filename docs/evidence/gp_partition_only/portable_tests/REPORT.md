# Portable partition-only test integration

The two production-shaped tests are
`candidate/tools/tests/test_slus_partition_only_build.py` (five cases) and
`candidate/tools/tests/test_slus_partition_only_evidence.py` (nine cases).
Their test-method names match the frozen originals exactly. They resolve the
repository from `Path(__file__).resolve().parents[2]`, import the installed
modules normally, and assert each imported tool's file path. They do not
replace `sys.modules` entries.

`python3 work/native_lane/gp_partition_only_tools/portable_regression.py`
ran all suites in **one Python interpreter** in the separate
`portable_regression_testroot`. This fixture copies the existing private
`regression_testroot/tools` tree and links only its existing private build
inputs. Result: **187/187 passed**, with 165 SLUS (151 existing plus 14 new),
eight configure, and 14 ASPSX comparator tests. No skips or failures.
Import identities before and after execution point to the fixture's nine
pinned candidate tool files. Those tool hashes, the fixture inputs, and selected
production config/build/image inputs remained unchanged.

The exact test IDs, source and tool hashes, resolved import paths, and log
hash are in `portable_regression_receipt.json`; full output is in
`portable_regression.log`. This is a candidate regression proof, not production
activation or a genuine compiler/full-image gate.
