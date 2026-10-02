# Disjoint roles and competing allocation priorities

Measured 2026-10-02 on `dungeon/func_80095160`, `2.7.2-cdk-G0 -O2`;
one 184-word function. Evidence: `docs/evidence/r88_80095160_height_storage.md`.

When retail reuses a saved register for a pointer and a later call result,
an explicit union can represent the disjoint roles without pointer/integer
casts. Use each member only during its own initialized lifetime. This is
variable hosting, a spelling trade to record, not proof of original source.

The union alone need not reproduce allocation. Here its 14 references over
93 live instructions outranked target X's 8/54, swapping s1/s2. Hosting a
later placement status in the now-dead target-X variable raised X to 10/54,
restoring the retail order. The status assignment and zero test affect
allocation, but later optimization keeps them in the call-result register
without an extra move. Together the changes remove one pin, byte-exact.

Measure both sides of the priority inequality and inspect the final code;
do not add dead reads or unused definitions to manipulate reference counts.
The lane's scalar-host diagnostic and union form are both exact. Current
name-to-pseudo tooling mislabels declarations after a local union, so verify
names against RTL before interpreting its allocation table.

## Hosting a final comparison in an existing scratch variable

Measured on the same row and recipe in r89: `docs/evidence/r89_80095160_rubber_duck.md`.
Removing a scratch register pin can expose local temporaries in expressions
that consume it. Here `if ((scratch >> 16) < 513)` creates a local quantity
that takes v0 before the global return-result variable is allocated. The
result then moves to a0, changing earlier call-result uses too.

Writing the real operations in place (`scratch >>= 16; scratch = scratch <
513; if (scratch) ...`) makes the comparison part of the scratch's existing
global allocno. It stays in v1 and the result regains v0: 4 -> 3 pins, exact.
Use `alloc_need.py` to establish the local/global conflict first. Merely
changing final return syntax or increasing a global's priority cannot
displace a register already occupied by local allocation.

## Check the role that would lose the newly requested register

Same row and recipe, r90: `docs/evidence/r90_80095160_coupled_centers.md`.
An apparent three-register rotation can depend on a fourth, currently
correct role. Center-Y needs to precede direction and body height, but
raising Y alone takes s0 from the X center. An exact global.c preference
replay, checked against cc1 on all 24 allocnos, restores the desired roles
only when X center precedes Y center and both move ahead of direction.

Do not treat an inverse tool's reference-count threshold as a sufficient
source fix. Replay the entire proposed order and inspect collateral
changes, including formerly correct values and spills. Then verify the
source still produces the assumed conflicts and post-sched1 live lengths.
On this shape, earlier height-delta preparation did not change the center's
18-instruction lifetime; map/center union sharing was undone by CSE. No
additional exact removal was found in that pass.
