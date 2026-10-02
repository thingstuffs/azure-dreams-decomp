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
