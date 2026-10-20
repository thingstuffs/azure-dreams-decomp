# Toolchain and module work

The continuing goal is readable, well-structured C with a faithful build and
explicit limits. The [generated status](../STATUS.md) and current proof readers
determine completion; this page does not maintain a second set of progress counts.

## Completed work and its scope

The SLUS small-data correction and associated ownership/module work reached a
production transition. Its
[transition evidence](evidence/gp_partition_only/production_transition/README.md)
records the linked retail checks, ownership proof and dependency refresh. Earlier
notes saying the combined transition awaits approval are superseded by that record.

The module and partition infrastructure distinguishes logical rows from physical
compiler inputs. Module grouping does not alone prove an original filename, data
ownership or source-quality level. Read [SLUS_MODULES.md](SLUS_MODULES.md),
[SLUS_PARTITIONS.md](SLUS_PARTITIONS.md) and
[LL5_MODULE_PLACEMENTS.md](LL5_MODULE_PLACEMENTS.md) for the current contracts.

## Continuing work

* Replace source-driven compiler/assembler workarounds only with supported source
  or recipe evidence and retail proof.
* Retire a compatibility pass only after identifying every consumer and verifying
  its replacement. A faithful assembler expansion is not debt merely because it runs.
* Improve shared declarations, complete TUs and ownership proofs without merging
  unrelated functions to reduce file counts.
* Keep library code, unresolved extents and data outside the registered-C total
  explicit in the byte maps and generated status.

[FIDELITY.md](FIDELITY.md) explains the remaining dependency categories;
[OPEN_ITEMS.md](OPEN_ITEMS.md) describes how to choose and report a bounded task.
The [decision record](evidence/r97_decisions.md) preserves original rulings and
later changes. Historical staffing, private work directories and research
checkpoints are not requirements for contributing to the public repository.
