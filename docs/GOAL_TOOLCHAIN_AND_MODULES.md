# Goal: finish toolchain fidelity repairs and prove module cleanup

Recorded 2026-09-24 at the owner's request. This is the next work programme while
Claude usage awaits reset (approximately three days), and remains the handoff plan
afterward. The reset is a checkpoint, not a deadline or permission to weaken proof.

## Intended result

Advance readable, well-structured C that rebuilds the retail game byte-exact:
resolve the remaining SLUS small-global assembler discrepancy, remove obsolete
compatibility passes where proved unnecessary, and establish a repeatable module
cleanup workflow with one verified pilot. Keep unresolved coverage and toolchain
limitations explicit. Pins may remain; raw pin count is not the primary target.

## Order of work and completion evidence

1. **Resolve the SLUS `$gp` discrepancy first.** Reproduce genuine ASPSX's handling
   of externally declared versus translation-unit-defined small globals. Start
   with the 59 dependent SLUS rows and six measured candidates in
   `evidence/fidelity_step4_measure.md`. Recover supported data ownership and
   declarations; prepare the assembler correction and affected source repairs
   together in isolation. The pinned-object `$gp` whitelist was a measurement
   aid, not an acceptable production fix. Completion requires genuine-ASPSX
   comparison, retail byte equality, the full SLUS link/SHA-1 gate, and refreshed
   dependency evidence. If ownership cannot yet be established, record the
   exact symbols, missing evidence, measured failures, and next experiment.

2. **Retire obsolete maspsx imitation passes.** Refresh the dependency census
   after the `$gp` work. Prioritize passes with few remaining dependents, repair
   their C or evidenced recipe, then remove a pass only after checking all its
   consumers and passing the required full gates. Do not remove a faithful
   assembler expansion merely because it fires. Retain the two accepted
   missing-compiler epilogue model rules; reopen the compiler hunt only on new
   relevant evidence. Preserve documented old-ASPSX dials until disproved.

3. **Prove one real module cleanup.** Choose a small module with strong membership
   evidence and a coherent compiler recipe. Establish shared types, declarations,
   and a header; group functions in retail order while preserving row identities
   and verification. Demonstrate the build and status tooling on this pilot and
   document how to repeat it. Claim L4/L5 only when their actual criteria pass,
   including pin, tail-jump, and toolchain-residue requirements. The earlier
   estimate of 5,951 active rows blocked only by module placement is a selection
   hint, not proof that those rows can be grouped mechanically.

4. **Account for the three unregistered MAIN routines.** Audit
   `func_800217C8`, `func_800218A0`, and `func_80021958` separately from the
   registered-function C census. Establish their memory-card SDK/kernel provenance
   and platform boundary, then recover a suitable implementation and retail-byte
   proof where possible. Otherwise retain precise, evidence-backed coverage gaps;
   do not report the whole game as C-complete from registered rows alone.

At the three-day checkpoint, report landed changes, gates, remaining dependencies,
the module pilot's result, and concrete blockers. A documented blocker completes
an investigation checkpoint, not the underlying repair goal. Continue independent
work where another item is blocked. Leave the difficult H28 source reconstructions
and separate egcs proxy question as a clear queue for Claude's return.

## Agent roles (owner-authorized)

The primary agent owns orchestration, difficult compiler/assembler attribution,
source reconstruction, architectural decisions, evidence review, and integration.
**Sol (`gpt-6-sol`) and Luna (`gpt-6-luna`) agents may be delegated bounded grunt
work.** Use Luna for narrow inventories, receipt checks, mechanical comparisons,
and documentation extraction; use Sol for bounded scripts, reproducible probes,
candidate preparation, and verification runs. Escalate ambiguous findings to the
primary agent rather than turning a mechanical result into a toolchain verdict.

Give each delegate explicit input paths, a bounded question, expected artifacts,
and acceptance checks. Use private scratch/build directories and disjoint edits;
honor the global IO restrictions. Avoid duplicate searches and open-ended compiler
or mutation grinding. Delegates return evidence and candidate changes; the primary
agent reviews and integrates them through the existing landing gates. Coordinate
with running landers and snapshots before shared changes. Delegation is permitted,
not required when the primary agent can finish a task more cheaply.

## Standing constraints and starting evidence

- Preserve retail-byte exactness, stock compiler policy, and the pin campaign
  charter. No new pins, source/address-keyed assembler exceptions, or artificial
  source dependencies to conceal a mismatch.
- At a trial recipe, genuine-ASPSX equality with maspsx is insufficient: also
  prove retail equality with `cell_retail_check.py` and the relevant linked gate.
- Follow existing owner decisions in `TOOLCHAIN_FIDELITY_PLAN.md`. Prepare a
  concrete isolated patch and validation before any still-required final sign-off
  for shared assembler semantics or pass removal; do not repeat approvals already
  granted or halt independent preparation.
- Refresh live counts rather than treating the following snapshot as current:
  H28 recovery landed 11 CDK moves, removed 74 pins, made nine rows pin-free, and
  reduced the maspsx dependency ledger from 237 to 226. Registered rows all had C
  representations; parked movie assembly and unregistered coverage gaps remain.
- Starting references: `evidence/r77_h28_recovery.md`,
  `evidence/fidelity_step4_measure.md`, `evidence/fidelity_step1_aspsx_diff.md`,
  `evidence/fidelity_lost_compiler_case.md`, `TOOLCHAIN_FIDELITY_PLAN.md`,
  `PIN_CAMPAIGN_CHARTER.md`, and `PLAN.md`.

## Resumption checkpoint: linked CD layout prototype

The [E758 data-piece experiment](evidence/gp_cd_partition/object_split/REPORT.md)
now passes fresh genuine-ASPSX instruction comparison and both stock/generic
full-image links. It preserves all surrounding data and 868 outside C objects.
Production remains 189 dependencies / 21 GP rows; this private proof earns no
removal. Next: integrate explicit data-piece plans into build/fidelity/ownership
checks, reconcile the shared CD declarations, then measure the complete consumer
group. The goal remains active with the same primary/Sol/Luna division of work.

The [data-piece tooling candidate](evidence/gp_data_pieces.md) now also passes
normal generated Ninja, fresh whole-owner genuine verification, the private
generic assembler arm, and three candidate-rejection/restoration cases. The
complete patch is recorded. Next is portable integration-test completion and a
production tooling/recertification transaction, followed by the shared CD source
repairs. No production dependency count has changed at this checkpoint.

The data-piece tooling is now integrated with 159 passing tests, an unchanged
production recipe and all 869 C objects unchanged. All 23 ownership proofs and
both existing placement certificates have been refreshed. See the
[production receipt](evidence/gp_data_pieces/production/integration_receipt.json).
Next is the shared CD source contract and complete consumer repair; the private
E758 layout proof has not activated an owner or removed a GP dependency.

The [shared CD declaration repair](evidence/gp_cd_contract.md) now gives seven
whole rows one header for the selected small globals and an eight-byte result
type, preserving F368's four-byte save/restore. All three assembler arms match
their respective prior outputs; stock remains retail-exact and all 869 production
objects are unchanged. Existing overlapping address views and driver/queue type
conflicts still need repair before joining consumers. The 21 GP dependencies
remain; this source cleanup claims no new owner or assembler transition.

A further private E758 probe replaces the padded state-byte array bounds with
observed one-/two-byte access spans while keeping array access semantics. With
explicit ownership and data-piece projection, corrected/genuine assemblers both
match all 698 words unmasked; stock's external-size GP rule produces 667 words.
This candidate is queued with the generic transition, not activated separately.
See the [next-probe evidence](evidence/gp_cd_contract.md#next-probes-recorded-after-the-shared-header-gate).

## Resumption checkpoint: common CD recipe

The [eight-function CD candidate](evidence/gp_cd_cohort.md) now matches all
1,041 words through genuine ASPSX and the corrected generic assembler at one
`2.7.2-cdk -G32` recipe, with zero masked relocations. Shared queue/driver
types, bounded result views, and a distinct completion-offset lifetime reconcile
the formerly mixed recipes. Eleven globals are defined once, with an explicit
data-piece plan and one new code2 partition for F240. Its full linked trial also
passes: eleven exact data pieces, 861 unaffected objects unchanged, all 22 code2
remainder functions unchanged, and a retail-exact image/SHA-1 gate. The merged
ready18+CD8 rehearsal now also passes: 26 functions / 1,932 exact words, 67 data
records, 858 physical objects and 884 logical rows. Production remains 189 dependencies / 21 GP rows;
no global assembler transition or pass retirement is claimed.

The complete generic-assembler rebuild of all 858 objects isolates the remaining
changes to three collector functions: F5D4/F5E0 (C8 accessors) and 48DA0
(B1B/B1C table-state bytes). The full link succeeds but the image gains four
instructions / 16 bytes and fails SHA-1. All three already match individually
with explicit data definitions at their original compiler recipes (17 words).
Next: add strict support for owners consisting entirely of collector fragments,
integrate these two small owners, then repeat the complete generic build/gate.
The [closure evidence](evidence/gp_cd_cohort.md#whole-slus-generic-audit-and-the-final-three-functions)
retains both the passing selective rehearsal and the failed unrestricted trial.

## Resumption checkpoint: all-active SLUS generic build matches

The [collector-only tooling and ready29 rehearsal](evidence/gp_partition_only.md)
now close the last three SLUS instruction differences in isolation. All 860 active
C objects rebuild with the corrected generic assembler; the generated image and
SHA-1 gate match retail. Fresh genuine/retail checks cover 29 repaired functions /
1,949 words with zero masks and 70 exact data records. The private graph has 33
owners and preserves all 884 logical rows. Tooling regression: 182 tests, zero
skips, plus five focused build-schema checks. Production remains unchanged.
Next: normal ownership-prover integration, complete overlay gate, refreshed
candidate dependency census, and final transition review/sign-off. The previously
failed all-858 trial remains preserved as the diagnosis, superseded for the
repaired private candidate by this passing full-SLUS gate.

The normal private ownership prover now also passes for both collector-only
owners through real code/code2 measurements. Complete selected TUs are genuine
and retail exact; unrelated collector debt stays explicit. Portable tests pass
187/187 together with no skips. Full overlay gating and a private whole-tree
dependency census are the next transition gates; production remains unchanged.
