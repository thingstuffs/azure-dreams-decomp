# B68 fallback script: primary used-extent review

The fallback address registered by DCA8 denotes a one-byte return script view.
This does not recover its historical allocation size or claim ownership of B68.
The adjacent bytes `01 01 01` have not been assigned a meaning by this review.

The retail bytes beginning at 80080B68 are `16 01 01 01 23 00 00 00`.
The actual D8006AA90 dispatch table entries 15 and 16 are respectively
800395F0 and 80039640. The DD2C/DDE4 packet header word 15080707 emits the
bytes `07 07 08 15`, followed by the address registered through DCA8.
The actual table entries for 07/08 are 391B4/391BC. The former is an eight-byte
return/nop, and the latter clears the image without advancing the script cursor.
Thus the two 07 commands and the 08 command leave 15 as the next opcode, which
invokes the registered address as a script subroutine.

Retail 395F0 saves the current operand cursor plus four bytes through the
stack pointer at context+7C, advances that stack pointer by four, reconstructs
the destination from four byte loads, and writes it to context+1C. This agrees
with the canonical C body in konami_runtime_w_800395F0.c.

The 16 handler at 39640 loads context+7C, subtracts four, saves that new stack
pointer, loads its word and writes that word to context+1C in the return delay
slot at 39658. It consumes no inline operand from B69 or later.

After the handler returns, the dispatcher reloads context+1C at 38B74 before
the signed-byte lookahead at 38B7C. Consequently this lookahead reads the
restored caller script, not B69. A one-byte `u8 B68[1]` view therefore covers
the complete used fallback script. Unlike B6C's two-byte termination sequence,
this fallback does not need an adjacent sentinel because its opcode replaces
the cursor before the lookahead.

The current `int B68[3]` declaration explicitly advertises a false extent to
force addressing. A private candidate may replace it with the measured byte
view while retaining its existing pointer expression and register pin. Its
compiler and assembler behavior still needs complete-function and linked
retail proof before adoption. This is a source-view repair, not justification
for new assembler exceptions or for claiming any adjacent storage.

Separately, E130's retail computes the selected slot address into a0 at
E148/E14C and preserves it until `jal 3528C` at E168. Passing that address
explicitly matches the canonical `void func_8003528C(s32)` signature and the
actual call; the former no-argument prototype hid this dataflow.
