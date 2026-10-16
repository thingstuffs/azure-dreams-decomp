# r121 continuation 3 — complete tail site maps

## DUNGEON file 0x19BAF84, true 0x80024784, 416 bytes

Inputs a0 = particle view, a1 = destination coordinate packet, a2 = state/packet.
Frame 0x30, ra +0x28, s0..s5 +0x10..0x24. s3 holds particle; s4 holds
state; s2 walks destination 4 bytes at a time; s1 walks input halfwords at +0x18;
s0 counts three samples; s5 holds weight table 0x80024AE0. Counter 0x80024A70
increments before the optional coordinate copy. The pointer at particle+0x14
supplies halfwords +2,+6,+0xA to destination +0xE,+0x12,+0x16.

Loop order is rand(), signed particle+0x32 weight lookup, subtract 8 from random
low nibble, multiply signed weight, load next input halfword, then store and
advance. Loading the coordinate before rand() wrongly adds a saved register.
After the loop, state+8 advances 12; end pointer is the same weight-table address,
and wrap destination is its containing pool's packet member, 0x54 bytes earlier.
The source names a bounded 0x54-byte ring before the weights marker, leaving
the adjacent weights-table extent unspecified.
State depth +0x1E decays by unsigned depth/24 and also stores at +0x1C. Particle
fade +0x3C subtracts 8 before adding signed particle+0x32/2; reusing the RNG local
for fade changes the register lifetime. Copy fade byte to +0xE,+0xD,+0xC. If signed
fade <=0, set bit0x8000 in the particle flags at -2 and resident 0x800814A0.

## DUNGEON file 0x1954F40, true 0x80024740, 488 bytes

Input a0 is a particle view in a linked list. Frame0x50 with position[4] at +0x18,
projection outputs at +0x20/+0x24. s4 holds current view; s5 holds &gameWork;
s8/s7 point to the projection outputs; s3 holds 24-bit address mask; s6 command
mask; s2 line packet; s0 first projection then draw-mode packet; s1 depth offset
then final OT address. Allocate20 bytes through gameWork.unk_000+0x8D0. Write
line colour0x202020 and second colour0; SetLineG2 takes ONE pointer, not a
spurious second argument inferred from live a1. SetSemiTrans takes pointer,1.
Collect three source halfwords at +0x1E,+0x22,+0x26 in one four-halfword vector;
separate scalar objects allow the compiler to delete the final two stores.
Project that vector, then source+0xC, then sign extend only the FIRST result and
average. If unsigned16 average <480, append line to the ordering table at +0xB0,
allocate12 bytes, GetTPage(0,1,0,0), SetDrawMode(packet,0,0,result&0xFFFF,0), append
that packet too. Advance through view-8 and view=next+0x20; return0.

This candidate remains a bounded C-shape near miss. Current residual is primarily
s3/s4 allocation and loop-latch a0/v0 choice, with the original OT-expression order restored. No compiler or assembler impossibility is asserted. The retail
fingerprint is family-neutral here; the fixed recipe is the proven neighbouring
2.7.2-cdk-G0 cohort. No recipe sweep or pipeline edit has been made.

## TOWN devkit file 0x7F5808/0x7F5858/0x7F58AC

Complete extents are80/84/96 bytes, including the return and its delay slot,
not the heuristic80-minus8/84-minus8/96-minus8 queue portions. Bit-index quotient
uses signed divide-by32 correction and remainder; pointer global0x80701968.
The common exit of the third function is0x80701904 at file0x7F5904; both retail
absolute jumps fix delta0x7FF0C000. Header at0x7F4000 also names the following
full-copy callback0x8070190C, physically0x7F590C. The first two candidates are
one instruction apart at the original C shape: li1 expands addiu while retail
spells ori. Unsigned C spelling did not remove that assembler-dialect residual.
The third has additional register-lifetime differences. These remain unported;
there is no independent SDK provenance and no sdk_asm relabel.
