# Recovered draw-chain callback at file 0x19800D8

Review: pending. Reviewer: pending. This row is not a module certificate.

The previous r101 audit called index 194's 21 registered functions contiguous.
They omit [0x19800D8,0x198012C): 84 bytes between func_8195FD40 and
func_8196012C. The omitted bytes are a complete function with a 24-byte frame,
saved s0/ra, a loop calling RAM 0x80025540, and a zero return followed by
jr ra and its delay slot. The next row materializes 0x800258D8 as a draw
callback passed to func_8004491C. Its old D_800258D8 array declaration named
code. The new shared function declaration and explicit address conversion
repair that caller without changing its instructions.

The callback follows object-header links at payload-8. It draws each payload
with its position, render state, and signed render halfword at +6. When a next
header exists, the new payload is header+0x20 and position/render are header
fields +8/+12. It returns zero when the chain ends. The imported draw routine's
ABI matches the existing func_8195FD40 definition: s32 first argument, two
pointer arguments, and s16 depth bias; the first is unused there.

The local j at file 0x198010C targets 0x800258E8, the loop at function+0x10.
The caller's explicit callback address independently fixes the function base
at 0x800258D8. This yields delta 0x7E6A5800, agreeing with the adjacent proven
bank records. The append-only proven map covers these 84 code bytes only.
No asset extent, historical source boundary, or module ownership follows.

Use the new bounded production window dungeon_native_19800d8_recovered and
all existing production windows covering the repaired caller. The lane proof
uses unchanged tools/build/gate_all.py and also rebuilds SLUS from scratch.
The GNU and genuine objects each have exactly 84 function bytes. An initial
exploratory linker script appended four zero bytes by admitting an empty
aligned .text section; the corrected diagnostic script checks those default
sections are empty before discarding them. No function bytes are trimmed.
The production row gate is the authoritative proof, not that diagnostic.

The new weak assignment joins index 194 as a grouping hint. A complete native
merge would now require 23 functions (the entry plus 22 following functions),
not the prior 22-function proposal. It still requires membership, complete
load coverage, data ownership, types and whole-TU production proofs. The
existing D_80025460 declaration in the caller is a separate inherited callback
contract issue to resolve with that group's full type review.

Adding this split row invalidates all live overlay module certificates. The
orchestrator must re-certify dungeon_cd_control_d79c4,
town_minigame_dispatch_44b44, and dungeon_ovl_1852800 after landing and review.
