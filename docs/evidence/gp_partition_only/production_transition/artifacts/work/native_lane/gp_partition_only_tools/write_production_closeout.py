#!/usr/bin/env python3
"""Publish the actual completed production evidence and goal checkpoint."""
import json
from pathlib import Path
import subprocess
import sys
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[2]
r=json.loads((HERE/'production_completion.json').read_text())
assert r['status']=='PASS'
c=r['census']
base='work/native_lane/gp_partition_only_tools/'
args=[sys.executable,str(HERE/'archive_production_transition.py'),
 '--census-run',base+'production_census','--dependency-proposal',base+'production_dependency_proposal',
 '--import-proof',base+'production_import_receipt.json',
 '--completion-file',base+'production_completion.json',
 '--completion-file',base+'production_object_hashes.json',
 '--completion-file',base+'production_object_comparison.json',
 '--completion-file','ledger/modules/list_cursor_e0.json',
 '--completion-file','ledger/modules/runtime_directory.json',
 '--script-file',base+'finish_production_transition.py',
 '--script-file',base+'compare_production_objects.py',
 '--script-file',base+'write_production_closeout.py']
for p in sorted((HERE/'production_census/report').iterdir()):
 if p.is_file():args.extend(['--report-file',str(p)])
for name in ['production_levels.log','production_status.log','production_row_db.log','production_census_followthrough.log']:
 args.extend(['--completion-file',base+name])
subprocess.run(args,cwd=ROOT,check=True)
dest=ROOT/'docs/evidence/gp_partition_only/production_transition'
prefix='artifacts/'+base
act=prefix+'activation_runs/20260925T010431Z_625211_resumed3/'
(dest/'README.md').write_text(f'''# Approved production GP transition — complete

Completed {r['completed_utc']}. The owner explicitly approved the reviewed
transition on 2026-09-25 and requested application, production gates and closeout.
The correction and obsolete-pass removal are installed; the fresh production
census is imported and live levels/status are refreshed.

## Production evidence

- [Activation receipt]({act}activation_receipt.json): the SLUS image matches all
  524,288 retail bytes, SHA-1 `{r['ownership']['image_sha1']}`. The active recipe
  has 860 physical C objects and 884 logical SLUS rows.
- All **2,175 active overlay windows MATCH**, with zero retries and unchanged
  transition inputs. [Journal]({act}overlay_journal.jsonl) and
  [gate log]({act}overlay_gate.log) retain every window result.
- **166 SLUS tests, eight configure tests, 418 assembler tests, and 60 fidelity
  controls pass**. The control run has zero skips. Its
  [receipt]({prefix}production_controls/receipt.json) binds the production tools.
- [Ownership proof]({act}ownership_receipt.json): all 33 owners / 59 measured row
  records pass. The existing explicit `t272` model row remains
  `slus/konami_runtime_w_80033D54`; it is not claimed as unmodelled compiler proof.
  Both `list_cursor_e0` and `runtime_directory` certificates were regenerated and
  remain current after the census/import/status refresh.
- [Object comparison]({prefix}production_object_comparison.json): all 860 objects
  agree with the private proof in parsed code/data sections, relevant symbols,
  relocations, extents and diagnostics. 602 raw objects are identical; 258 differ
  in ELF bookkeeping (register information, raw symbol/string/relocation tables,
  or section headers). Raw whole-object equality is not claimed. The full linked
  image provides the separate retail-byte proof.

## Fresh production census and import

The [fresh run]({prefix}production_census/receipt.json) measures all {c['rows']:,}
registered rows directly from production after cache refresh. All pipeline/scorer
and trace self-checks pass, with unchanged measured inputs. {c['genuine_common']:,}
rows match a common genuine ASPSX version; **{c['dependencies']} remain dependent**.
The [reviewed import]({prefix}production_import_receipt.json) removes exactly 22
of the previous 189 dependencies and adds none. Production provenance and every
row key were validated; no private-fixture keys were imported.

Retained ladder classifications stay unchanged. The remaining causes for
`slus/code` and `slus/code2` are scoped to their dependent remainder units. Exact
extracted owners do not make either complete collector genuine-exact.
The external-GP detector finds zero rows; this does not relabel retained ledger
classifications. `_sink_call_separated_la` is removed. `_split_funcaddr_la` remains
required by `dungeon/func_818D4E68`; accepted compiler-model rules and old-ASPSX
dials remain intact.

The census masks {c['masked_words']} relocation words across {c['masked_rows']}
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

[Final completion receipt]({prefix}production_completion.json) binds the live
counts, refreshed levels/status, certificates, gates and proof-input checks.
[archive.json](archive.json) distinguishes original, scrubbed-content and stored
hashes. Large journals use deterministic gzip. Restore recorded work paths and
expand placeholders for replay; local historical toolchains and retail inputs
remain prerequisites. Earlier private/sign-off-pending receipts are historical
stages superseded by this production evidence.
''')
p=ROOT/'docs/GOAL_TOOLCHAIN_AND_MODULES.md'
with p.open('a') as f:f.write(f'''\n\n## Completion checkpoint: approved production transition\n\nCompleted {r['completed_utc']} after explicit owner approval on 2026-09-25.\nThe [production transition and requirement audit](evidence/gp_partition_only/production_transition/README.md)\nrecords the installed GP correction and sink-pass retirement, retail-exact SLUS\nimage, all 2,175 overlay windows, 33 ownership proofs, and both fresh placement\ncertificates. All 166 SLUS, eight configure, 418 assembler tests and 60 controls\npass. Setup/alias-validator corrections and their original failed runs are retained.\n\nThe fresh production six-version census passes all {c['rows']:,} registered rows;\n{c['genuine_common']:,} match a common genuine version and {c['dependencies']} remain dependent. The live ledger\nnow has 167 dependencies (189 before; 22 removed, none added), with levels/status\nrefreshed and proof inputs/certificates still current. The pilot remains L5/L4/L5.\nThe three MAIN C gaps are explicitly evidenced under item 4's fallback; 22 movie\nrows remain parked. Census masks and data/helper comparison limits stay explicit.\n\nAll four original goal requirements are satisfied at their stated scope. Remaining\nH28 reconstructions, the egcs proxy question, the 167 dependencies and MAIN gaps\nare the follow-up queue. No whole-game C-complete or pin-free claim is made.\n''')
p=ROOT/'docs/TOOLCHAIN_FIDELITY_PLAN.md'
with p.open('a') as f:f.write('''\n- 2026-09-25: owner explicitly approved the reviewed GP correction and sink-pass\n  retirement. Production activation, all retail gates, ownership/placement proofs,\n  fresh six-version census and live dependency/level/status refresh completed.\n  Dependencies 189 -> 167 (22 removed, none added). See\n  [production transition evidence](evidence/gp_partition_only/production_transition/README.md).\n  The retained split pass still has a required consumer; accepted model rules and\n  old-ASPSX dials remain. Earlier sign-off-pending entries are historical.\n''')
p=ROOT/'docs/evidence/gp_partition_only/final_transition/README.md'
s=p.read_text()
s=s.replace('Status: **ready for owner sign-off; not applied to production**.',
'''Status: **historical reviewed proposal; approved and activated on 2026-09-25**.\nSee the [completed production transition](../production_transition/README.md) for\nactual gates, integration supplements, fresh census and live ledger import.\nThe frozen receipts below retain their original pre-approval state.''')
p.write_text(s)
print('Production evidence archive and completion documentation written.')
