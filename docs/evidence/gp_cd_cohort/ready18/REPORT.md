# Ready18 rehearsal on the CD-contract baseline

Baseline commit: `89b1465834114c4cfb67dba1f298e86fb3303b18`. The private
rehearsal passed against the unchanged production tree. The prior ready18
receipt is pinned by SHA-256; all 869 historical active object hashes still
match. Among its existing file pins, only `tools/build/configure.py` changed
(`c5a9cb7a…` to `bab4b98f…`). The new script pins the current data-piece tools,
the CD header, and all seven CD source files. Eleven copied stage inputs were
checked against those pins before private substitutions.

The generated SLUS image is byte-identical to retail
(`ae19d8d4bdd2db9a933b1e44d70dd61be670781e441d7cb37da85250a7aed31f`).
The trial has 30 modules, 864 physical outputs, and 884 logical rows, from the
23-module/869-physical baseline. It makes exactly eight scoped recipe changes
and applies the guarded generic assembler to exactly 12 private TUs. All 18
declared functions (891 words) match their complete genuine 2.79 streams and
retail with zero masks. All 56 owned data records and all 851 active outputs
outside the change set are exact. The connected `code`/`code2` closure has 191
functions across five owners; this receipt does not claim genuine equality for
the whole collector objects. The current remaining GP cohort is nine rows:
the two collectors and seven CD rows.

Production input and active-object snapshots match before and after the run.
No production files were edited. This is a selective private generic rehearsal,
not a production assembler transition.

Artifacts: `probe.py` (SHA-256
`e38e72b910f777bebc66a4bad9f0bb2d4918e94d40f714509bca4c6e203f7cd3`),
`receipt.json` (SHA-256
`423e42907042df85305a781764fcf1094072feab45b00503ce2fd1837b78dcbe`),
`build.log`, `run.log`, and the preserved `stage/` and `genuine/` outputs.
