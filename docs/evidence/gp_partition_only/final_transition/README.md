# Final GP correction and obsolete-pass retirement proposal

Status: **ready for owner sign-off; not applied to production**.

The [60-file patch](transition_final/combined.patch) combines the SLUS data-owner
and source repairs, corrected generic small-data addressing, removal of the unused
`_sink_call_separated_la` pass, migrated assembler tests, and refreshed fidelity
validation controls. No new pins or source/address-keyed assembler exceptions are
introduced. Existing accepted compiler-model rules and old assembler dials remain.

Patch SHA-256: `6fc7ead242d82bac80b18ccfce92e3d12a7e24fb6054a8099607383e0d095da8`.
The [root review](final_root_review.json) verifies every production before hash,
every proposed after hash, the exact patch target set, and all 60 payload hashes
against the final ownership proof's input map. Patch replay and `git apply --check`
pass. The packaging receipt predates the final proof; the root review and final
receipts below supersede its pending-proof status without rewriting history.

## Passed private checks

- The retired-assembler candidate forcibly rebuilds all 860 C objects and matches
  the complete 524,288-byte retail SLUS image. The final validation-only tool
  refresh preserves all 860 object hashes and the image.
- The [final ownership proof](retire_sink/final_combined_receipt.json) measures all
  33 owners / 59 row records and passes both placement certifiers. The accepted
  `t272` model row remains explicit; it is not direct genuine-compiler equality.
- All 2,175 active overlay windows match, with zero retries and unchanged candidate
  and production input hashes: [full gate](../retire_sink_baseline/artifacts/overlay_gate/REPORT.md).
- The migrated assembler suite passes 418/418. The former sink-pass consumer has
  an identical complete object. The [retirement probe](../retire_sink_baseline/artifacts/receipt.json)
  records both results.
- The [exact retired-assembler control recheck](controls_refresh/retired_run_receipt.json) passes 60/60 with
  no skips, including historical casesi controls, the repaired SLUS functions,
  and the remaining split-pass consumer. Measurement/trace executable code is
  unchanged outside the validation controls; the root AST comparison is archived. The final
  retired-assembler log is byte-identical to the preceding guarded-assembler run.
- The [read-only activation preflight](activation_final_check.json) passes for
  this exact 60-target patch, its final proof inputs, and all 2,175 window identities.

The [six-version census](../census/README.md) measures 6,767 registered rows at the
GP-corrected candidate: 6,600 genuine-versus-pipeline matches and 167 remaining
dependencies, versus 189 in production (22 removed, zero added). The removed sink
pass fires on zero logical rows or physical units; its deletion is separately
byte-gated above. Validation-only changes do not alter the measurement logic.
The census masks 872 relocation words in 302 overlay rows, with zero SLUS masks;
its comparisons are distinct from the full image/window byte gates. Three MAIN
coverage gaps remain outside the registered census; 22 movie rows remain parked.

## Activation and remaining work

The [activation procedure](ACTIVATION.md) applies only this reviewed patch under
the landing lock, repeats the production build and window gates, rebaselines the
five changed individual SLUS caches before ownership/certificate generation, and
recertifies both module placements. Fifteen changed grouped rows use whole-owner
proofs. The transaction deliberately reports census-pending until a fresh
production-root census is measured and imported, followed by level/status refresh
and certificate revalidation. Private census keys are not transplanted.

The project [fidelity plan](../../../TOOLCHAIN_FIDELITY_PLAN.md#owner-sign-off-needed)
explicitly requires final owner sign-off for the maspsx GP fix and pass deletion.
No sign-off or production activation is claimed by this packet. The verified
runtime-directory module pilot and evidence-backed MAIN gaps are recorded in the
[goal audit](../../goal_module_coverage_checkpoint.md).

## Archive

[archive.json](archive.json) distinguishes original input hashes from archived
text hashes. Paths are scrubbed to `<repo>`, `<reference-repo>`, and `<user-home>`.
Restore the original work paths and expand placeholders to replay the scripts;
historical toolchains, retail inputs, and preceding private fixtures are still
prerequisites. The separately archived GP57 transition and retirement baseline
retain the earlier proof stages. This archive is not a standalone toolchain.
