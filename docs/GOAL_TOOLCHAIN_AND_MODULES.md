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
