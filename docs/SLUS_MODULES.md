# Executable modules

SLUS is the resident executable (`SLUS_006.14`); its public sources are under
`src/engine/`. Stable row IDs and exported build tokens can still say `slus`.
Resolve editable files through [SOURCE_LAYOUT.md](SOURCE_LAYOUT.md).

A module groups related logical rows in one compiler translation unit. That
grouping is a supported build organization, not automatic recovery of retail's
filename or TU boundary. The [runtime-directory review](evidence/runtime_directory_module.md),
for example, explicitly distinguishes an inferred cluster from a historical claim.

## Manifest and physical inputs

`config/slus_modules.json` declares module source, ordered members, shared
headers, recipe and evidence. `config/slus_partitions.json` can assign functions
from a collector to separate physical owners. Build adapters resolve historical
tokens to the current sources; do not recreate a removed fragment just because
an old manifest example names one. Native merged source is edited as its complete TU.

The compiler recipe must agree across the complete physical module. Logical
row accounting retains the original identities even when fewer physical inputs
are compiled. Recipe trials must include the whole cohort. For partition-only
owners, the collector identity remains and the connected physical streams must
cover every function exactly once. See [SLUS_PARTITIONS.md](SLUS_PARTITIONS.md).

## Data ownership

Initialized small data, zero-initialized storage, `.rodata` jump tables and
initialized `.data` tables require evidence of the symbol, allocated section,
extent, offset, address and asset carve. COMMON or
absolute symbols cannot stand in for real allocated ownership. The full linked
image must preserve the surrounding bytes and section order.

`tools/build/slus_modules.py` validates manifests and link planning;
`tools/fidelity/prove_slus_ownership.py` measures actual emitted storage and
retail/genuine-assembler equality. Declared compiler-model exceptions remain
visible and do not grant direct-genuine placement certification.

For reviewed scattered storage, `data_pieces` can identify individual small-data
allocations. The transformation preserves instruction bytes and relocation
identity, checks selected symbol extents and zero-only gaps, and requires fresh
independently checked sidecars. It does not establish the historical C type or
module membership. See [data-piece evidence](evidence/gp_data_pieces.md).

A `.rodata` or `.data` owner's object is cut back to its manifest span after
assembly (`tools/build/slus_rodata_trim.py`), because GNU as pads each section
to its alignment and the original linker did not. See the
[script opcode table owner](evidence/slus_script_opcode_handlers.md).

## Build and proof

From the repository root, after setup, the executable image gate is:

```sh
bash tools/build/build_slus.sh -j 4
```

**Requires a user-owned disc and provisioned free tools.** This image gate does
not require Psy-Q; genuine ownership/module comparisons do. The script creates
the build view, compiles, checks the retail SHA-1 and reports whether the generated
recipe equals the pinned recipe. Inspect both the image and recipe results.

A module candidate must be checked in the complete linked context, including
siblings, collector streams and owned data. The certificate producer
`tools/fidelity/certify_slus_module.py` additionally binds reviewed membership,
source/header inputs, recipe, tool identities, genuine comparison and retail image.
Do not hand-edit a missing or stale certificate. Changing a bound input requires
review and renewal.

The certificate supplies current placement evidence. [L4/L5](PLAN.md) still
require their own source-quality and fidelity conditions. A partition-only data
owner does not grant whole-row module credit to its collector; a recipe-only
owner with no data is not a data-ownership proof.
