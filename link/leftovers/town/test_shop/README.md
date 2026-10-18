# Test shop

TOWN `0x80B800` and `0x84C000` each have a verified 2048-byte identical slice of
the generic buy/sell template described in the supplied report. A SLUS optional
load descriptor names the first unit; the cited static analysis finds no callers
of its loading functions. `placements.json` keeps only offsets, sizes and hashes.

The report describes four copies, but provides only these two starts and no
four-placement extent/relocation table. This delivery therefore admits two exact
slices and holds the four-copy/shared-TU claim. Full unit lengths, any additional
copies and byte-exact compilation still need evidence. Existing home, relink and
hand-copy files are untouched. See report Highlights 3 and Q3.

The continuation independently decodes the SLUS descriptor at `0x54AD0`,
using the matched loader's sector-count rule. It bounds the load at TOWN `0x80B800`
to exactly 2,048 bytes with load VMA `0x80016000`. The audit searches the entire
TOWN container for that complete slice and finds exactly the two listed offsets.
This closes the descriptor-selected load extent; the second occurrence's enclosing
allocation and a shared compiled TU still need independent evidence.
See `link/leftovers/evidence/audit.json`.
