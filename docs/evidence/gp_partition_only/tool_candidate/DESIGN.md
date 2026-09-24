# Explicit owners consisting only of collector fragments

This private candidate adds `partition_only: true` with `members: []`. Ordinary
modules still require whole-row members. False, nonboolean, and mixed forms are
rejected. The partition plan supplies every function and its original row identity;
the new aggregator never becomes a synthetic logical row.

Validation requires at least one nonempty incoming part, no duplicate function
ownership, frozen collector source/recipe provenance, and full emitted coverage.
Both generated configuration and isolated builds reject an orphan even when the
optional partition plan is absent. Physical edge projection adds an owner object
without adding a logical function row.

The context adapter uses a real contributing collector as the fingerprint entry
point. That fingerprint covers all connected parents, owners, members, headers,
partition metadata, and opted-in data-piece transformation code.

Ownership proof measures each real collector through the normal plural pipeline.
It checks the collector's complete pipeline and unmasked retail coverage, then
requires direct genuine-ASPSX and unmasked retail equality for the selected
owner's entire physical TU, including incoming functions from other collectors.
An unrelated collector stream may still have genuine-assembler debt; the new
schema explicitly scopes direct equality to the selected physical owner. No
synthetic whole-member record is manufactured and no empty member loop can grant
an ownership proof. Data-piece transformations keep their existing whole-TU gates.

Whole-row placement certification is explicitly unavailable for these owners:
`certify_slus_module.py` directs callers to the ownership prover, and status emits
no placement grant for the collector. A later partial-row placement policy would
need its own design; this change does not imply one.

The motivating owners are C8 getter/setter at 2.7.2 and B1B/B1C state writes at
2.8.1. Their ordinary C definitions already match 17 instructions separately.
The private ready29 rehearsal tests their integration with the earlier 26 repairs
and the corrected generic assembler across all active SLUS objects. Production
activation and global assembler/pass approvals remain separate steps.
