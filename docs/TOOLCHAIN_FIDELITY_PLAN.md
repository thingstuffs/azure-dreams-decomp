# Toolchain fidelity work

The build uses pinned stock compiler drops and a function-blind assembler front
end. Source shape, compiler recipe, assembler behavior and storage ownership
must be diagnosed separately when a candidate differs from retail. See
[FIDELITY.md](FIDELITY.md) for the dependency categories.

## Evidence and current workflow

1. Reproduce the difference at the registered recipe and determine its scope:
   instruction selection/order, relocation target, data ownership or placement.
2. Where needed, compare the compiler stream through genuine ASPSX and the free
   pipeline, resolving relocations against retail in both cases. Equality between
   two assemblers at a trial recipe is not evidence that either equals retail.
3. Use the compiler fingerprint, complete TU and linked storage evidence before
   changing a recipe. One function's success does not establish its siblings.
4. Prove the proposed repair through the affected window or full executable
   image, then refresh dependency records and certificates binding changed inputs.
5. Remove a compatibility pass only after all consumers are accounted for and
   the required gates pass.

The [lost-compiler investigation](evidence/fidelity_lost_compiler_case.md)
records the accepted historical-compiler model and its limits. Reopen it when
new relevant evidence exists; an unsupported compiler download or a speculative
flag search does not settle the source question.

The [small-data production transition](evidence/gp_partition_only/production_transition/README.md)
supersedes the earlier pending transition plan. Other compiler-model rules and
assembler dependencies remain measured separately. Do not infer their retirement
from that one completed correction. The current counts belong in generated status.

## Required inputs

Free-tool provisioning is described by `tools/setup.sh` and
`tools/toolchain.lock.json`. Retail gates require the contributor's own disc.
Complete overlay-module comparison additionally requires the pinned genuine
assembler in [TOOLCHAIN_PSYQ.md](TOOLCHAIN_PSYQ.md). The repository does not supply
the proprietary SDK. Historical experiments with other Psy-Q versions do not
extend the normal setup requirement.

Record the measured input hashes, scope, failures and remaining dependencies.
Keep compiled objects, extracted assets and SDK files out of Git. Use the
[toolchain/module overview](GOAL_TOOLCHAIN_AND_MODULES.md) and
[decision history](evidence/r97_decisions.md) for related work and original rulings.
