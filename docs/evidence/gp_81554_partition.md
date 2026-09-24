# Command-slot ownership and source repair

`command_slots_81554` groups five command-buffer functions in retail order:
DCA8, DD2C, the DDB4 reset from `code`, DDE4 and E130. It owns the actual
zero-initialized `s32` words at 81554/58, replacing exactly eight bytes at
offsets B14/B18 of asset 54240. The external 32-word command table and fallback
script remain outside this storage claim. This is a present C grouping, not a
recovered historical translation-unit boundary.

## Source repairs

The shared header gives the command table a word view, matching its mixture of
encoded commands and pointer addresses. Pointer stores and submissions use
explicit casts. The `func_8003528C(s32)` declaration agrees with its canonical
definition. E130 now explicitly passes its selected slot address, which retail
already holds in a0 at the call.

The [fallback review](gp_81554_partition/b68_primary_review.md) follows the
actual dispatch table and script-call stack. B68's opcode 16 restores the
caller cursor before the dispatcher's next byte read. Its complete used view is
one byte; adjacent bytes and historical allocation size remain unclaimed.
Replacing the explicitly inflated `int[3]` declaration with `u8[1]` allows an
ordinary local pointer to reproduce DCA8's fourteen words. The old register pin
is removed. A control restoring the large declaration without the pin emits
fifteen words; this is a scoped source-declaration result.

DDE4 now expresses its actual operations directly: mask and save the starting
slot, append the header, register the supplied script address, append two
command words and submit the starting slot. Removing its manually staged
index/offset/pointer temporaries lets default CDK reproduce the retail load
lifetime and scheduling. Its special no-schedule flag is removed. DCA8 changes
from 2.8.1 to default CDK; the whole owner has one recipe. The incoming collector
part retains its original recipe provenance in the logical projection.

The [primary source review](gp_81554_partition/primary_source_review.md) records
register roles, the bounded recipe controls and intermediate source trials.
The byte-signature classifier is inconclusive for this small scope; no unique
historical compiler is inferred from a sweep. No assembler change, new pin,
padding, duplicate storage or keyed exception is introduced.

## Verification and limits

The [direct proof](gp_81554_partition/direct_receipt.json) compares the complete
five-function set with authoritative lengths 14/34/4/41/22. All **115 words**
match stock assembly, genuine ASPSX 2.79 `-q`, the existing private generic
correction and retail, with zero masked relocations. Stock and generic object
hashes agree. This owner can therefore activate independently of the pending
global assembler correction.

The [private full-link receipt](gp_81554_partition/private_link_receipt.json)
proves eight actual `.sdata` bytes, non-absolute linked symbols at 81554/58 and
the exact retail image. All 867 outside active objects are unchanged. The
23-module build has 869 physical inputs and preserves 884 logical rows; all
188 functions in the connected collector/owner group are emitted exactly once.
The [complete-owner proof](gp_81554_partition/private_genuine_receipt.json)
checks the new owner alongside E0, B98 and 81540. The
[negative gates](gp_81554_partition/gate_receipt.json) reject mutations in the
new part, each existing owner part and the collector remainder, restoring
canonical inputs and the retail image after every trial.

The [production ownership receipt](gp_81554_partition/ownership_receipt.json)
and [live rows](gp_81554_partition/live_rows.json) support removing only the four
whole-member dependency entries. Unrelated collector GP dependencies remain.
The E0 and runtime-directory placement certificates are refreshed. This review
establishes data ownership and source cleanup; it does not itself grant L4/L5
placement. The [activation review](gp_81554_partition/activation_review.json)
records the production gate, tests, counts and actual ladder results.

The [bounded return audit](gp_81554_partition/return_audit.md) records an existing
external prototype conflict: 49374 and two wrappers propagate a claimed DD2C
return value, whereas DD2C's canonical definition is void. Their indirect callers
remain unaudited. This change preserves that definition and does not claim
project-wide prototype recovery. The original canonical collector bodies remain
unchanged; DDB4 is moved physically through the generated partition only.

Reproduction scripts and isolated inputs are under
`work/native_lane/gp_81554_partition/`. The pending generic assembler change and
pass retirement still require their own complete transition gates and the
existing final owner signoff.
