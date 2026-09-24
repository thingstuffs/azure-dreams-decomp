# 81554/58 source review and accepted candidate

The accepted direct candidate is `candidate_v4`, at default CDK. It owns only
the two actual four-byte zero words at 81554/58. The command table remains an
external 32-word view; the fallback remains external. The five complete retail
bodies contain 14, 34, 4, 41 and 22 words, respectively (115 total).

## Retail map and attribution

The full retail listing is in `retail.s`. The unchanged lineage scanner run on
each exact SLUS byte slice is recorded in `lineage.json`: all five are
inconclusive, with too few diagnostic global-store forms. This does not claim
a uniquely recovered historical compiler. CDK is the existing recipe for the
two packet builders and E130; the bounded default/no-schedule comparison
isolates source scheduling at that recipe. No alternative family is selected
from a distance ranking.

- DCA8 is a frameless leaf. It copies the argument to a1, substitutes the
  fallback absolute address on null, holds the command-table address in v0,
  loads the slot counter into a0, computes a slot in v1, stores the pointer
  word, and advances the counter through GP. Its branch slot carries the
  table's high half; its return slot is empty.
- DD2C and DDE4 use 24-byte frames saving s0 and ra. s0 holds the table base
  across DCA8. Their identical header region masks the next index, saves it
  in both owned words, writes 15080707 and advances the counter. DD2C appends
  23; DDE4 appends 20C11 and 1. The final submission address is completed
  in the call slot. Both use the standard load/load/pop/return/nop epilogue.
- In DDE4's second region, v1 first holds 20C11, a1 the advancing slot index,
  a0 the starting index then its byte offset, and v0 successive write-slot
  addresses. After the first command store, v0 is rebuilt from the advanced
  index; v1 becomes 1; the first counter store precedes its increment and
  the second command store. The final counter store precedes submission.
- DDB4 is four words: store zero to 54, store zero to 58, return, nop. Its
  full extent is independently confirmed by the production ELF symbol size.
- E130 uses a 24-byte frame saving only ra. Its chosen word-slot pointer
  is in a0 at E14C and remains the argument to 3528C. The explicit argument
  repairs a mismatching no-argument declaration without changing instructions.

## Source causes and controlled changes

The initial group had four exact functions at default CDK. DDE4 had the same
41-word extent and correct frame/register roles but different instruction
ordering in the second region. Its existing no-schedule flag fixes that body
while disturbing DCA8 and DD2C. That is a scoped source/recipe observation,
not a compiler-wall verdict.

The C-rebuild step transcribed the packet operations directly: mask the
counter, save its starting value, append the header with post-increment, call
DCA8, append 20C11 and 1 with post-increments, and submit the saved starting
slot. This removes the manually staged index/offset/pointer temporaries and
premature saved-index read. Default CDK supplies the exact retail load lifetime
and instruction order. All five bodies then match without special flags.
The two intermediate variants only changed portions of the old temporary
structure and were rejected; their private receipts are not closeness rankings.

The B68 review establishes a one-byte return-script view. With the old pin
retained, changing its declaration alone preserves all function words. With
that byte view, replacing the pinned pointer with an ordinary local still
matches DCA8's complete fourteen words. The control `candidate_large_unpinned`
restores the inflated twelve-byte declaration and emits fifteen DCA8 words.
Thus the repaired declaration makes the old pin unnecessary at default CDK;
this is not a blanket claim about either allocator or all pointer constants.

The common word-table view replaces incompatible pointer-table declarations.
Pointer values are explicitly cast at storage/submission sites, agreeing with
the existing one-word 3528C parameter. These are present typed views and an
evidenced grouping, not a recovered historical translation-unit boundary.

## Limits

External callers still propagate a claimed DD2C return value through 49374
and two wrappers; the bounded source audit cannot establish how indirect or
external callers consume that value. This change preserves DD2C's current void
definition and makes no project-wide return-type reconciliation claim.

Fresh genuine comparison and the isolated linked gate are separate required
checks. The subsequent direct proof shows stock, generic and genuine all match,
including equal stock/generic object hashes. Unlike the earlier 81550 candidate,
this source repair can activate independently after its stock ownership/link
gates. The separate generic assembler transition retains its global gates and
existing owner signoff; this local result does not satisfy them.
