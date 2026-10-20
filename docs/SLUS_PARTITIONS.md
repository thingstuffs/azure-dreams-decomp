# Executable function partitions

A collector can contain functions that belong to different compiler/storage
contexts. `config/slus_partitions.json` assigns explicit function subsets to
physical owners while retaining the collectors' logical row identities and
frozen provenance. Public editable paths are resolved through
[SOURCE_LAYOUT.md](SOURCE_LAYOUT.md); historical `src/<stem>.c` tokens refer to
the exported executable build view.

## Required invariants

`tools/build/slus_partitions.py` validates original recipes, frozen hashes,
canonical definition sets, disjoint destination subsets and the remainder.
Every compiled function must occur exactly once across connected streams.
The emitted object check matters: source parsing alone can miss a function
created by a macro. Unsupported conditional/source forms fail closed.

Rendering writes generated source views beneath the build directory. Canonical
editable C and logical IDs remain the source of truth. A fragment's original
recipe is provenance, not a claim that a moved function still compiles there.
The destination owner's recipe and complete function inventory enter its proof.

`tools/slus_module_context.py` supplies connected sources and fingerprints;
`tools/verify.py` compiles the physical streams and verifies candidates through
the complete executable image where required. A collector edit must check both
the moved functions and every remainder stream, including siblings whose source
text was not edited.

## Ownership and limits

An owner can use `partition_only: true` when all of its functions come from
collector parts. It must have incoming parts and no whole-row members.
Data ownership requires allocated storage, genuine-assembler comparison and
retail proof for the selected physical TU. A recipe-only owner may have no data;
the ownership prover correctly refuses a data-ownership claim for it.

Partition-only proof does not grant whole-collector placement credit. A direct
genuine requirement cannot be silently replaced by compiler-model equality,
and a successful image hash does not establish historical membership or types.
See [executable modules](SLUS_MODULES.md) and [quality levels](PLAN.md).

## Detailed evidence

The [list-cursor partition investigation](evidence/gp_e0_partition.md),
[partition build evidence](evidence/slus_partitions/) and
[collector-only ownership review](evidence/gp_partition_only.md) retain the
implementation and negative checks. The
[production transition](evidence/gp_partition_only/production_transition/README.md)
supersedes earlier private-build/pending-activation descriptions.
[Sound recipe partition evidence](evidence/sound_tu_code_partition.md) illustrates
a partition that serves a compiler recipe rather than a new data owner.

These records describe their measured snapshots. Read current manifests,
certificate freshness and generated status for the present set of owners;
do not replay a private research script as a public build prerequisite.
