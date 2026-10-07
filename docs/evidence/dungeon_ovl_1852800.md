# dungeon/ovl_1852800.c — draft for orchestrator review

Reviewer: orchestrator-r99 (2026-10-07): membership, types and ownership reviewed.

This proposal reconstructs a complete four-function TU with one native const
entry pointer. It does not identify an original filename. The physical interval
is DUNGEON file [0x1852800,0x185321C), runtime [0x80024000,0x80024A1C).
The entry points to 0x80024004. Native code follows at 0x80024004, 0x800247E8,
0x80024860 and 0x800248F0. Sizes are 2020, 120, 144 and 300 bytes.

Membership evidence is in the adjacent .membership.json: exact whole-TU bytes,
complete emitted storage and contiguous coverage, a proven entry/load anchor,
and internal callback address relocations. The fourth function ends at the
claimed interval end. Following bytes remain outside this reconstructed object.
There are no gaps or borrowed switch tables. The strong proposal applies to
this reconstructed scope, not to a guessed historical TU boundary.

The entry has exactly the body's three pointer arguments. The shared header
provides consistent declarations for all four definitions. Callback symbols
formerly spelled D_80024860 / D_800248F0 now resolve to actual module functions;
no code-address array or assembly alias remains. Parameter view structures and
member bodies otherwise retain their byte-tested behavior.

The height query func_800BCB04 returns s32 in its defining source. This caller
now declares that return correctly and retains its narrowing at actual uses.
The table accessor func_800A3820's u8 return declaration conflicted with this
caller's signed-halfword use. The proposed contract returns the byte value as
s32; the caller explicitly converts to s16 before widening for the old call.
The defining source still loads one unsigned byte and returns the same value.
Its complete affected windows must pass separately; other legacy callers are
outside this contract repair. Argument widths, return consumers and source
contracts listed in review_inputs remain inspectable by the reviewer.

Only the 4-byte pointer is owned storage. dirStepX/Y remain 16-byte initialized
views into the PS-X EXE payload. D_800DEA68 and D_800DED70 remain unsized external
views into the proven resident dungeon asset; the recorded 8-byte observed
views do not claim complete array extents. objectFlagBlock, dungeonStatus and
D_80083498 remain external runtime storage declared by the existing shared
headers. No initialized retail bytes, original allocation sizes or zero-filled
file spans are invented for these runtime views. The exact imports and mapping
bases are in the adjacent .imports.json.

One CDK-G0 compile, genuine ASPSX 2.79, complete payload validation and natural
.rodata-then-text placement are required. Every affected production window,
the accessor's windows, and a fresh complete SLUS build are required proofs.
No reviewer or placement journal event is set by this lane.
