# cdk-G0: capture byte bits before signed conversion

Scope: stock 2.7.2-cdk, -O2 -G0, ordinary project assembler pipeline;
DUNGEON status handlers at files 0xED184 and 0xED9E0 (244 bytes each).
Do not generalize this observation to other recipes or shapes without measuring.

Retail tests a signed byte at state+0x6D, then reloads it unsigned into $s0,
converts it to signed eight bits, and carries the signed result across a call.
A borrowed exact source used `(s8)(state[0x6D] + 0)`. This delivery removes
that artifact with a real two-step conversion:

```c
u16 previous_bits;
s16 previous_status;
previous_bits = state[0x6D];
previous_status = (s8)previous_bits;
```

Both complete functions are exact with this form. A u32 bit temporary also
matches. A u8 temporary lets the compiler reuse the earlier signed load and
changes the body. Two assignments to the same s16 variable retain the complete
61-word length but leave four register substitutions; separate wide-bit and
signed-value temporaries coalesce into retail's $s0 live range. These are
measured shape-dependent outcomes, not a compiler impossibility or a new flag.

Evidence and exact source hashes: docs/evidence/r121_remnants.receipt.json.
Original probes and aligned decompositions:
work/native_lane/r121_remnants/evidence/status_temp_u16.score.json,
status_temp_u32.score.json, status_temp_u8.score.json and status_promote.diff.
No pins, asm, volatile, artificial zero, dead arm, or new helper call is needed.
