# Round 49: a local-return repair transfers to a second bank

**Six pins removed: 6,032 remain in 1,272 functions; 71 removed from 6,103.**
Both covering overlay windows and SLUS match; row database and host syntax checks
pass. See the [durable receipt](evidence/pin_research_round49_20260917.json) and
[independent review](evidence/pin_research_twins_review_20260917.md).

The two item-return bodies `80E9D000` and `80EA3000` each lose three of their
six pins. They retain the unchanged stock 2.8.0 recipe. The same source repair
works in both banks despite the shared slot having positive versus negative
low-address displacement. This is a demonstrated transfer between two copies
of the same body, not evidence that all local returns share the pattern.

## Why the complete repair works

Each row starts with 264 bytes of bank data and then a 492-byte C body. The
last apparent external noreturn call is actually a jump to the local restore
and return sequence. At that edge, retail already holds the shared-slot address
in v0. Returning that address expresses the real control flow.

Return repair alone misses eleven register substitutions. Replacing the two
later hard-coded shared-page calculations with the actual declared shared-slot
symbol also removes their keeps and restores retail's register roles. The first
branch still needs separate investigation: making its slot address natural
reorders two stores, putting the shared-slot store in the jump delay slot where
retail clears the source. Retaining that original branch makes the entire row
exact, including bank data: **189/189 words in each row**.

Each function retains that first scheduling keep and two loop bindings. All six
isolated erasures fail, with corresponding failure classes in the two banks.
There is no extra erasure-cascade gain. No new pin, volatile access, fake use,
interface trick or function-specific backend change was introduced. Existing
pointer-to-word returns and unchanged bank-data declarations remain outside this
bounded repair; neither is claimed solved by removing the three C pins.

The whole-row lineage fingerprint initially sees bank data and stops before the
body. Scanning the measured body instead finds an allocated split store and two
stores in local-jump delay slots, consistent with the CDK/2.8 family. This corrects
the measurement scope; it does not establish the exact historical release.

## More selective delegation

The refreshed routing audit excludes the landed switch and now-repaired twins.
It leaves **29 rows / 56 in-row targets: 16 straight-line epilogues and 40 internal
targets**. Seven rows have only epilogue targets, nine mix epilogues and internal
edges, and thirteen contain only internal targets. Five remaining data-prefixed rows and the two repaired twins were
checked against measured body boundaries. These are conservative routing facts,
not pin-removal promises or a census of distinct C patterns.

Gemini via `agy` hit its five-minute print timeout with one saved candidate for
`8182D698` and no final report. The CLI returned zero despite the unfinished turn.
Local verification finds its ordinary-return reconstruction exact at 101/101
words, but all three pins remain and their erasures fail. Nothing from that
candidate was landed. Classify this as a partial timed-out worker result, not a
completed six-probe experiment or a failed reconstruction.

The useful next batch is the seven epilogue-only rows, starting with `819A764C`
and `818B78E8`. Give a worker the verified local return and actual global object
relationships together, rather than asking it merely to replace one call or
remove one pin. Keep internal loop targets in a separate allocator/CFG lane.
Do not repeat the saved motion erasures or the first-store/loop-binding erasures
from the twins without new compiler evidence.
