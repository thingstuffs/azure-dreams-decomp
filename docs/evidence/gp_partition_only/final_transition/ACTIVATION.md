# GP/SLUS transition activation draft

This runbook and `activate_transition.py` are an unexecuted activation proposal.
The script applies no patch unless passed `--execute`; that flag is only a
technical opt-in. Owner/user approval remains a separate decision. It never
commits, deletes a build root, or rolls back changed production files.

The final packet has 60 reviewed targets under `transition_final/`; its review
record is `final_root_review.json`. The matching private ownership
proof, ownership record, source pins, and full overlay gate are kept separately
under `retire_sink/`.

```sh
.venv/bin/python work/native_lane/gp_partition_only_tools/activate_transition.py \
  --check \
  --packet-dir work/native_lane/gp_partition_only_tools/transition_final \
  --patch combined.patch \
  --review work/native_lane/gp_partition_only_tools/final_root_review.json \
  --full-proof work/native_lane/gp_partition_only_tools/retire_sink/final_combined_receipt.json \
  --ownership-proof work/native_lane/gp_partition_only_tools/retire_sink/final_ownership_receipt.json \
  --overlay-proof work/native_lane/gp_partition_only_tools/retire_sink/overlay_gate/receipt.json \
  --proof-input-pins work/native_lane/gp_partition_only_tools/retire_sink/final_source_pins.json
```

The command is read-only because it uses `--check`. It pins every final payload
byte to the final full-proof input map, including the controls patch, and checks
the candidate assembler pair against the 2,175-window overlay receipt.

`--check` is read-only: it verifies the review's dynamic patch and inventory
hashes, every payload file and current target before hash, the complete private
ownership receipt, the private overlay gate, clean production status, and
`git apply --check`. It reports the payload count from the selected inventory;
it uses the final 60-target inventory. Do not pass `--execute` until the
selected packet and its final proof receipts have been reviewed and approved
outside this script.

With approval, run the same arguments with `--execute`. The transaction takes
`build_ovl/work/land.lock`, repeats clean-tree, target-hash and apply checks under
the lock, then applies that exact patch. It keeps a private pre-transition copy
of the SLUS row and input projections. A failure receipt records the phase and
actual patch state; all logs and work products remain for inspection, with no
automatic rollback.

The gates run in this order:

1. Run SLUS and configure unit tests plus the complete **418-test** candidate
   assembler suite. The script requires all 418 to pass; it does not accept a
   matching set of old failures.
2. Rebuild the SLUS source view, run normal configure, require generated Ninja
   to equal the proposed pinned recipe and the private proof's recipe hash, run
   `row_db.py check`, then run `build_slus.sh -j 2`. Require the recorded SLUS
   gate and retail image comparison to pass.
3. Build a fresh, uniquely named overlay view and force
   `gate_all.py --all --workers 4` with both assembler overrides bound to the
   installed candidate. Require all 2,175 window identities recorded by the
   selected private gate receipt to appear exactly once and match, and require
   candidate and transition-target hashes unchanged across the gate. The
   identity list is loaded from that receipt rather than embedded in the
   script.
4. Before ownership or placement proofs, find changed SLUS rows from three
   inputs: complete registry records, current source bytes for each SLUS row,
   and the logical SLUS edge recipe ledger (`ccver`, `ccflags`, `asflags`, and
   source/output identity). Run the cache rebaseline dry run for changed
   nonmodule rows, then apply it only if every row is accepted. Grouped rows
   are recorded as whole-owner proof scope and excluded from individual
   cache rebaseline.
5. Run complete production SLUS ownership for the manifest's modules with the
   explicit model row `slus/konami_runtime_w_80033D54`. Regenerate the
   `list_cursor_e0` and `runtime_directory` placement certificates after cache
   rebaseline; require `certificate_reason` to return no reason for each, then
   run the row database check again.

The script stops at `PASS_GATES_CENSUS_PENDING`. It does not reuse or import the
private census journal: its tool fingerprints include absolute roots and cache
inputs. After cache rebaseline, the integration process must run a fresh production-root
dependency census with exclusive scratch use, verify complete final
provenance, and perform the reviewed dependency-ledger import. Only after that
import should `tools/levels.py`, `tools/status.py`, and `tools/row_db.py check`
run, followed by `certificate_reason` validation for both placement
certificates and confirmation that the proof-input hashes have not changed.
The final fresh-census receipt path and census row count remain explicit pending
inputs; this draft does not invent them or add an importer.

No production command has been run from this draft.

The frozen GP57 `--check` passed earlier and remains recorded in the checkpoint.
The final 60-target `--check` passed against the exact final ownership, input-pin,
and overlay receipts. Its output is `activation_final_check.json`; the runbook
command and all companion paths are fixed. Do not substitute the
earlier 57- or 58-target packet for final activation.
