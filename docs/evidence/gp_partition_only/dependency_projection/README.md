# Dependency import preparation and comparison scope

Status: **private projection only; production activation and census pending**.

The [proposed ledger](maspsx_dependence.proposed.jsonl) derives from the completed
[private six-version census](../census/README.md): 189 dependencies become 167,
with 22 removed and none added. The [receipt](receipt.json) binds both ledger
hashes. The remaining rows retain their existing ladder classifications.
For `slus/code` and `slus/code2`, causes are scoped to the dependent remainder
physical unit; exact extracted owners do not prove the entire collector exact.
Only those two retained cause descriptions change. Owner-only ablations do not
establish minimal per-pass source attribution or a new ladder classification.

The [preparation script](dependency_import.py) only writes a new private proposal
directory. Its production-validation mode requires a fresh production-root census,
current registry/source/tool/assembler bindings and row measurement keys, and an
exact retail SLUS image. It rejects private fixture keys. Installation and the
subsequent level/status/certificate refresh remain separate reviewed steps under
the landing lock. No production acceptance is claimed before that census exists.

The [checks](checks.json) pass on the actual 6,767-row dataset: duplicate and missing
identities, a failed trace self-check, an incomplete genuine-version set, private
fixture evidence presented as production evidence, and a new unreviewed dependency
are rejected. The complete projection yields the expected 167 rows, preserves
classifications, and scopes both collectors to their remainders. The successful
fresh-production acceptance path remains untested until approved activation.

The census counts registered rows, not directly compared retail functions:

- `slus/gte_port_state` is data-only (zero functions and words), so this row supplies
  no instruction comparison.
- `slus/w_8003FE78` and `slus/w_8005DA88` each emit two object functions, but the retail
  comparator checks one. Their extra eight-byte inline helpers have no symbol in
  the final private linked ELF; their principal functions do. The
  [scope check](scope_check.json) binds the actual objects, linked ELF, reader and
  comparator. Symbol absence does not establish whether helper instructions occur
  elsewhere in the image.

These qualifications accompany the already recorded 872 masked relocation words
across 302 overlay rows. The separate complete SLUS image and 2,175 active-window
byte gates retain their own scope. None of these observations adds a demonstrated
retail byte mismatch or resolves the three unregistered MAIN C gaps.

## Replay

[archive.json](archive.json) records each original and archived hash. Restore the
three scripts at `work/native_lane/gp_partition_only_tools/`, alongside the original
census runner, reconciled census and preceding private fixtures, and restore the
projection files in its `dependency_projection/` directory. Run the checks with
`.venv/bin/python work/native_lane/gp_partition_only_tools/dependency_import_checks.py`
and the scope inspection with the corresponding `dependency_scope_check.py`.
The scripts depend on repository fidelity modules and local proof inputs; this
archive is not a self-contained toolchain. Keep private measurement keys out of
the production ledger. The reviewed 60-file transition remains unchanged.
