#include "common.h"

typedef struct S_8001A7F4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    void * unk_1C;
} S_8001A7F4_0;   /* base in func_8001A7F4 */

typedef struct S_8001A7F4_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8001A7F4_1;   /* dst in func_8001A7F4 */



extern s8 D_80016000[];

/* Sets the destination coordinates with scaling and a fixed offset. */
void func_8001A7F4(s32 unused, s32 x, s32 y)
{
    register void *base ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *dst ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    (void)unused;
    base = *(void **)D_80016000;
    dst = ((S_8001A7F4_0 *)base)->unk_1C;
    ASM_KEEP(dst);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    x <<= 6;
    ((S_8001A7F4_1 *)dst)->unk_04 = x / 10 + 0x220;
    base = ((S_8001A7F4_0 *)base)->unk_1C;
    ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    y <<= 6;
    ((S_8001A7F4_0 *)base)->unk_08 = y / 10 + 0x220;
}

/* MECHANISM: Frameless leaf with the global base held in a0 and the first
   destination in a3; scaled coordinates remain in their a1/a2 ABI registers.
   The portable /10 form is byte-exact when sched2 is disabled, preventing its
   repeated sign-shift hoist across mfhi and the quotient shift. */
