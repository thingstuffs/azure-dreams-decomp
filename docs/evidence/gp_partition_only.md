# Collector-only owners and the complete SLUS GP rehearsal

The private build now uses the proposed generic assembler for **all 860 active
SLUS C objects** and reproduces the retail image byte for byte. The generated
SHA-1 gate passes. All 29 selected repaired functions / 1,949 instructions also
match genuine ASPSX 2.79 and retail with zero masks, and all 70 selected data
records have their exact linked bytes and addresses.

This closes the three instruction mismatches found by the earlier
[all-858 audit](gp_cd_cohort/all858/REPORT.md). It is a private full-SLUS proof;
production still has 23 owners, 869 physical objects, 884 logical rows and
189 dependency records / 21 GP rows. Shared assembler activation, a refreshed dependency census, and the existing
final owner sign-off remain separate work. The broader overlay gate now passes
as recorded below.

## Two small owners, original collector identities

The new private manifest has 33 owners and the same 884 logical rows. It preserves
all earlier candidate modules and adds two explicitly collector-only owners:

| Owner | Functions | Original compiler recipe | Owned storage |
| --- | --- | --- | --- |
| `accessors_814c8` | F5D4, F5E0 from `code.c` | 2.7.2 | Four-byte `D_800814C8` |
| `table_counters_b1b_b1c` | 48DA0 from `code2.c` | 2.8.1 | One byte each at `D_80080B1B` and `D_80080B1C` |

Each aggregator defines its ordinary small globals and includes function bodies
extracted from its canonical collector. The B18 table remains an external address
view, with no duplicate storage. Named data pieces allow B1B and B1C to keep their
one-byte alignment and exact addresses without claiming surrounding bytes.
No new pin, padding, recipe change, or assembler exception is needed for these
three functions. The copied F624 comment was also corrected without changing C
expressions or instructions.

The `code.c` remainder retains 149 functions / 1,218 words and `code2.c` retains
21 functions / 213 words, all unchanged. Complete connected coverage contains
198 functions with no duplicate owner. The other 856 physical objects retain
their canonical instructions, data, and relocations; 266 have raw ELF metadata
changes only. The image SHA-256 remains
`ae19d8d4bdd2db9a933b1e44d70dd61be670781e441d7cb37da85250a7aed31f`.

## Tooling contract

The candidate adds `partition_only: true` with exactly `members: []`. Existing
modules still require whole-row members. The partition plan must supply at least
one nonempty incoming fragment. Build, isolated verification, and registry checks
reject orphan owners even when the optional plan is absent. Frozen collector
provenance, original recipes, and complete emitted function coverage still apply.
The physical object gains no invented logical row.

Ownership verification processes the real contributing collector rows through
the existing plural pipeline. It requires complete collector pipeline and retail
coverage, then direct genuine and unmasked retail equality for the selected
owner's **entire physical TU**. An unrelated collector stream may retain separately
reported genuine-assembler debt. The receipt distinguishes these scopes; an empty
whole-member list cannot silently skip code proof.

Collector-only owners grant no whole-row placement certificate. The certifier
explicitly directs these owners to the ownership prover, and status does not
grant placement to a collector from a fragment proof.

## Validation and remaining work

The private tooling regression passes **182 tests with zero skips**, covering the
existing module, partition, data-piece, genuine-verification, ownership and
certificate contracts plus nine new evidence checks. Five additional build-schema
checks pass, including two-parent ownership and orphan/duplicate rejection.
Candidate import paths and hashes were verified. These tests use synthetic
contracts where appropriate; they do not substitute for live compiler evidence.

The separate [ready29 report](gp_partition_only/ready29/REPORT.md) and
[receipt](gp_partition_only/ready29/receipt.json) record the actual complete C
rebuild, normal generated link, SHA-1 gate, fresh genuine comparisons, and exact
data checks. Production code/configuration/build bytes and all production objects
are unchanged. The [normal ownership-prover integration](gp_partition_only/live/REPORT.md) also
passes using real `A.process_row` calls for both collectors. Its schema-5 receipt
proves both complete new owner TUs (six and eleven words), their three data
symbols, and the full generated image, with all production inputs unchanged.
The [portable combined regression](gp_partition_only/portable_tests/receipt.json)
now passes all 187 tests in one interpreter: 151 existing SLUS checks, 14 new
checks, eight configure checks and 14 ASPSX-comparator checks. No test is skipped.

Next: finish the candidate dependency census and full 33-owner recertification,
then finalize the concrete assembler/source transition for the plan's required
owner sign-off. No compatibility pass is retired here.
The [archive index](gp_partition_only/archive.json) binds retained scripts,
receipts, sources, tooling patch and tests to their original and scrubbed hashes.

The [live-proof archive index](gp_partition_only/live_archive.json) binds the
normal prover receipts, runner, production snapshots and portable test sources.

The [assembler test migration](gp_partition_only/assembler_tests/REPORT.md)
also passes 418/418 with the candidate CLI and package. Production already had
three stale local-switch-table expectations; nine other failures expected emitted
external-size metadata, and one assumed a GP hazard on a true external. Updated
checks preserve exact instruction assertions and add an explicit local-owned GP
hazard case. The main-output golden changes only by six removed metadata lines.
No assembler code was changed to make these tests pass.

## Complete overlay gate

The exact guarded generic assembler passes all **2,175/2,175 overlay windows**
in a forced isolated run, with no serial retries. The candidate CLI/package
hashes and all 9,749 tracked production inputs covered by the gate snapshot
are unchanged before and after. The [report](gp_partition_only/overlay_gate/REPORT.md),
[receipt](gp_partition_only/overlay_gate/receipt.json), and full per-window
[journal](gp_partition_only/overlay_gate/journal.jsonl) retain the reproducible proof.
The original-suite failures listed in that gate receipt are the stale expectations
resolved by the separately archived 418/418 test migration above.

A complete private transition patch now covers the repaired sources, ownership
plans, build adapters, guarded assembler, tests, and full logical-row projections.
Its generated Ninja graph matches the retail-exact ready29 graph byte for byte.
The whole-tree six-version census and full normal ownership/certificate rehearsal
are running against isolated inputs; their completion is not claimed here.

## Final source review

Four small source cleanups remove stale padded-declaration comments, unused page
macros and an unused page variable. Each complete compiler assembly stream is
byte-identical before and after at its registered CDK recipe. The independent
[source-hygiene reproduction](gp_partition_only/source_review/source_hygiene/reproduction_receipt.json)
binds the compiler, headers, source snapshots and exact assembly streams.

The normal all-owner rehearsal then exposed a source-organization defect in
`gp_d92c_owned` (also present in `gp_order_bytes_owner`): copied bodies violated
the documented canonical-fragment/include contract. The proposed correction
keeps each body at its original row path and makes the owner include it once,
with exactly one data definition. Both complete owner compiler streams preserve
every instruction and directive except one added `.file` source metadata line;
see the [comparison](gp_partition_only/source_review/canonical_sources/receipt.json).
The full normal ownership/build rehearsal is being rerun on these final sources.
The original frozen whole-tree census is retained; any affected-row failures
must be resolved with separate final-source measurements and explicit provenance,
not erased or labeled as a wholly passing original run.
