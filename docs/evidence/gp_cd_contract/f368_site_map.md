# F368 source-rebuild handoff

Scope: the complete 113-word `func_8003F368` retail function at
8003F368..8003F52B (end exclusive 8003F52C), read from the production linked
ELF whose complete image equals retail. `f368_retail.dis` is the full listing.
The unchanged signature classifier reports <=2.7.2-family macro stores. Keep
the existing plain 2.7.2 default recipe: no broader exact-version attribution
is inferred from that family signature. The current repaired source is stock
retail-exact; genuine still expands external small globals absolutely.

| Region / relative offset | Register roles and source requirement |
|---|---|
| 00..34 | 48-byte frame; save s0/s1/s2/ra at 32/36/40/44. s2 holds only the initial four-byte D81450 word for recovery. Clear that word before CdSync(1, sp+24). Eight SDK bytes fit sp+24..31. |
| 34..78 | s0 is the retry count 16, s1 is constant 1. CdControl receives absolute D81451-1. Failed countdown calls E70C and F624, then loops. Keep the call/result comparison and branch-delay decrement. |
| 78..C8 | s0 resets to 16; s1 becomes the held D814D3 byte base. CdSync gets absolute D81451-1. On timeout call E70C then F240; mask its return with 0xff and compare to 0x1b. |
| C8..118 | Read head via -3(s1), write state 0xff with an assembler-macro store, conditionally decrement GP D0 or write 0x1f via -3(s1), then GP-mask D0 with 0x1f. Retry F624 and return to the first loop. |
| 118..124 | Restore only s2's four bytes to GP D81450; restart the sync loop. |
| 124..158 | Load first result byte via GP D81450, next two via separate absolute D81451 and D81452 bases. Build local position bytes at sp+16..18. Call CdPosToInt, move result into s0 across later calls, and test the first byte through F688. |
| 158..1A8 | Check remaining fields through D81452-1 then D81451+1. Existing result-register pin remains. Error branches return zero; positive s0 returns the sector. |
| 1A8..1C4 | Restore saved registers and the unchanged 48-byte frame; jr ra/nop. |

The outstanding source-owned representation problem is the padded D81451/52
views and their backward/forward address arithmetic. Replacing them requires
preserving the full GP/absolute access map above, plus the exact frame and
register live ranges. Keep one hypothesis per candidate and compare whole
functions with aligned metrics if lengths change. Do not enlarge saved_loc to
the complete eight-byte SDK result or add storage to force address selection.
Route: az-c-rebuild, with assembler/address-selection failures attributed before
further source iteration. E758's separate site map covers the other result user.
