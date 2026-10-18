# Debug NPC

TOWN `0x84E000` and `0x868000` each have a verified 2048-byte identical slice.
The supplied report identifies a debug NPC with map selection and flag-clearing
commands. A SLUS descriptor points to the second unit; the static analysis finds
no callers of the optional-descriptor loading functions.

`placements.json` records the slices' exact offsets, lengths and SHA-256 values.
Their enclosing unit boundaries and a compiled shared TU have not been proved.
The generator refuses differing slice hashes. Runtime non-loading is an open
confirmation, not a new claim from slice identity. See the supplied report
Highlights 3 and Q3, preserved under `docs/evidence/r121w_ll6/`.

The continuation independently decodes the SLUS descriptor at `0x54AC8`,
using the matched loader's sector-count rule. It bounds the load at TOWN `0x868000`
to exactly 2,048 bytes with load VMA `0x80016000`. The audit searches the entire
TOWN container for that complete slice and finds exactly the two listed offsets.
This closes the descriptor-selected load extent; the second occurrence's enclosing
allocation and a shared compiled TU still need independent evidence.
See `link/leftovers/evidence/audit.json`.
