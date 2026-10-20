# Source and build ownership

The repository owns its editable C sources, shared headers, build descriptions,
proof tools and committed evidence. It does not require an upstream working
checkout to verify a source change. A contributor supplies the retail disc and,
for the complete overlay-module proof, the proprietary assembler documented in
[TOOLCHAIN_PSYQ.md](TOOLCHAIN_PSYQ.md).

The current source tree is the single editable tree. Frozen first-pass hashes
and lineage metadata in `config/frozen_raw.jsonl` support comparisons without
shipping a second source corpus. Historical journals describe an earlier
pin/replay process; their removed source trees and cleanup scripts are not
prerequisites for a fresh public clone. `PIN` and the baseline metadata record
lineage rather than an instruction to fetch another local checkout.

The distinction that motivated the transition still matters: an object-only
check can miss relocation/placement errors, so overlay changes need the retail
window proof and executable changes need the relevant linked image check.
See [proof and quality levels](PLAN.md).

[SOURCE_LAYOUT.md](SOURCE_LAYOUT.md) explains the present subsystem paths and
inlined TUs. [LINK_LISTS.md](LINK_LISTS.md) explains shared placements and physical
coverage. The [decision record](evidence/r97_decisions.md) retains the
transition's rulings; old byte totals and commands in dated evidence are not
current status.
