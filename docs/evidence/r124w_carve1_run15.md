# Street-event callback split repair

Base: 9ba75d1c1. The authenticated CD map in
`docs/evidence/town_ovl_2d3f0c.rowbase.json` maps TOWN.BIN +0x2D2000..+0x2D4000
to 0x8001DCD0. Its shared delta is 0x7FD4BCD0.

Two old rows claimed only an eight-byte return tail. Each is the final two
instructions of a complete 32-byte framed function. Opcode 0x4C operands in
the street-event script reference their real entries, rather than the tails:

| Stable row | Complete file extent | Entry | Script opcode | Behavior |
| --- | --- | --- | --- | --- |
| town/func_80353EE4 | 0x2D3ECC..0x2D3EEC | 0x8001FB9C | 0x8001F6AB | set_script_flag_bit(0xDB3) |
| town/func_80353F04 | 0x2D3EEC..0x2D3F0C | 0x8001FBBC | 0x8001F6C3 | clear_script_flag_bit(0xDB3) |

The calls are to the already named town flag services at 0x8001ACE8 and
0x8001AD60. Both use a 24-byte stack frame, save/restore ra, and return without
changing the callee's result. Their C contract remains void(void).

Split records are corrected in place. Historical row IDs remain stable;
file offsets, sizes, true runtime labels, owning source paths, name records,
and proof windows describe the complete functions. The two former return-tail
names are removed. Prototypes live in the existing town scene folder header.
No new readability debt is introduced.

The preceding 56-byte function ends exactly at 0x2D3ECC; the following 44-byte
function begins exactly at 0x2D3F0C. Neither owns the missing prefixes. The gaps
between those neighbors are replaced by the two complete C producers. The
estimated-code coverage region already covers these bytes; no data exclusion
is withdrawn or shortened. If a future repair affects such a region, retire
it by re-appending active:false before adding the corrected coverage interval.

A full-file scan checks the same 32-byte framed immediate-call form against
all active eight-byte TOWN split rows. A second scan checks every eight-byte
return row for opcode 0x4C references to a possible entry 24 bytes before it.
Only structurally validated complete functions are candidates; a pointer-like
byte pattern alone does not establish code ownership. Receipts and the
repeatable scanner accompany the lane delivery.

This repair adds 48 previously imported code bytes to C ownership, for 64
complete callback bytes. It makes no native runtime-coverage claim without a
separate execution witness.
