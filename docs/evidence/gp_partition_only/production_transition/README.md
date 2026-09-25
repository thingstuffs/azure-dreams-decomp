# Approved production GP transition — complete

Completed 2026-09-25T02:02:18Z. The owner explicitly approved the reviewed
transition on 2026-09-25 and requested application, production gates and closeout.
The correction and obsolete-pass removal are installed; the fresh production
census is imported and live levels/status are refreshed.

## Production evidence

- [Activation receipt](artifacts/work/native_lane/gp_partition_only_tools/activation_runs/20260925T010431Z_625211_resumed3/activation_receipt.json): the SLUS image matches all
  524,288 retail bytes, SHA-1 `e6bfbb95ff6676899e077481221d73ddd4d3bf52`. The active recipe
  has 860 physical C objects and 884 logical SLUS rows.
- All **2,175 active overlay windows MATCH**, with zero retries and unchanged
  transition inputs. [Journal](artifacts/work/native_lane/gp_partition_only_tools/activation_runs/20260925T010431Z_625211_resumed3/overlay_journal.jsonl) and
  [gate log](artifacts/work/native_lane/gp_partition_only_tools/activation_runs/20260925T010431Z_625211_resumed3/overlay_gate.log) retain every window result.
- **166 SLUS tests, eight configure tests, 418 assembler tests, and 60 fidelity
  controls pass**. The control run has zero skips. Its
  [receipt](artifacts/work/native_lane/gp_partition_only_tools/production_controls/receipt.json) binds the production tools.
- [Ownership proof](artifacts/work/native_lane/gp_partition_only_tools/activation_runs/20260925T010431Z_625211_resumed3/ownership_receipt.json): all 33 owners / 59 measured row
  records pass. The existing explicit `t272` model row remains
  `slus/konami_runtime_w_80033D54`; it is not claimed as unmodelled compiler proof.
  Both `list_cursor_e0` and `runtime_directory` certificates were regenerated and
  remain current after the census/import/status refresh.
- [Object comparison](artifacts/work/native_lane/gp_partition_only_tools/production_object_comparison.json): all 860 objects
  agree with the private proof in parsed code/data sections, relevant symbols,
  relocations, extents and diagnostics. 602 raw objects are identical; 258 differ
  in ELF bookkeeping (register information, raw symbol/string/relocation tables,
  or section headers). Raw whole-object equality is not claimed. The full linked
  image provides the separate retail-byte proof.

## Fresh production census and import

The [fresh run](artifacts/work/native_lane/gp_partition_only_tools/production_census/receipt.json) measures all 6,767
registered rows directly from production after cache refresh. All pipeline/scorer
and trace self-checks pass, with unchanged measured inputs. 6,600
rows match a common genuine ASPSX version; **167 remain dependent**.
The [reviewed import](artifacts/work/native_lane/gp_partition_only_tools/production_import_receipt.json) removes exactly 22
of the previous 189 dependencies and adds none. Production provenance and every
row key were validated; no private-fixture keys were imported.

Retained ladder classifications stay unchanged. The remaining causes for
`slus/code` and `slus/code2` are scoped to their dependent remainder units. Exact
extracted owners do not make either complete collector genuine-exact.
The external-GP detector finds zero rows; this does not relabel retained ledger
classifications. `_sink_call_separated_la` is removed. `_split_funcaddr_la` remains
required by `dungeon/func_818D4E68`; accepted compiler-model rules and old-ASPSX
dials remain intact.

The census masks 872 relocation words across 302
overlay rows. SLUS has zero masks. One row is data-only, and two objects contain
extra inline helpers without linked symbols; these are not direct instruction
comparisons. The separate full-image/window gates retain their own scope.
The 22 parked movie rows are counted in the registered census, outside the active
overlay gate. Three unregistered MAIN routines are outside both registered counts.

## Integration corrections and preserved failures

The immutable approved patch is
`6fc7ead242d82bac80b18ccfce92e3d12a7e24fb6054a8099607383e0d095da8`.
Production activation exposed setup/validator issues that were repaired before
continuing: the E758 configure fixture still expected old flags; the managed SLUS
source view needed refresh before the identity test; and the row database did not
recognize registered function aliases. The validator now uses the existing
conservative alias-aware parser, with a regression test and an updated empty-alias
fixture. These supplements change tests/validation, not game C or assembler
semantics. All original failures and successful resumed receipts are archived.
The final receipt pins the 60 installed targets with the validator supplement
explicitly identified. The original reviewed packet remains unmodified.

## Goal audit and remaining project work

1. The SLUS GP discrepancy is corrected with genuine-ASPSX, complete retail gates,
   ownership proof and fresh production dependency evidence.
2. The unused sink pass is retired; consumers are repaired and all production
   gates pass. Still-required behavior is retained with explicit evidence.
3. The runtime-directory cleanup pilot is implemented, documented and freshly
   certified. Its rows remain L5 / L4 / L5; the middle row retains a PASSTHRU
   fidelity site. [Workflow](../../../SLUS_MODULES.md) and
   [pilot audit](../../goal_module_coverage_checkpoint.md) describe reuse.
4. The MAIN fallback is explicitly accounted for in the
   [coverage audit](../../main_kernel_coverage_audit.md) and
   [caller evidence](../../main_kernel_callers/REPORT.md). Three C gaps remain;
   exact SDK attribution and retail loading remain unresolved. This completes
   the goal's evidence-backed accounting requirement, not whole-game C coverage.

The original goal is complete. Remaining project work includes the 167 assembler
dependencies, difficult H28 source reconstructions, the separate egcs proxy
question, and the explicitly documented MAIN gaps. These are retained follow-ups,
not silently claimed repairs.

[Final completion receipt](artifacts/work/native_lane/gp_partition_only_tools/production_completion.json) binds the live
counts, refreshed levels/status, certificates, gates and proof-input checks.
[archive.json](archive.json) distinguishes original, scrubbed-content and stored
hashes. Log/report trailing whitespace is normalized where noted in the manifest; original source hashes remain intact. Large journals use deterministic gzip. Restore recorded work paths and
expand placeholders for replay; local historical toolchains and retail inputs
remain prerequisites. Earlier private/sign-off-pending receipts are historical
stages superseded by this production evidence.
