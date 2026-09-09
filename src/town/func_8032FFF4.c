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

/* Scale and offset the two coordinates stored in the global destination. */
void func_8001A7F4(s32 unused, s32 x, s32 y)
{
    void *base;
    void *dst;

    (void)unused;
    base = *(void **)D_80016000;
    dst = ((S_8001A7F4_0 *)base)->unk_1C;
    x <<= 6;
    do {
        ((S_8001A7F4_1 *)dst)->unk_04 = x / 10 + 0x220;
    } while (0);
    base = ((S_8001A7F4_0 *)base)->unk_1C;
    y <<= 6;
    ((S_8001A7F4_0 *)base)->unk_08 = y / 10 + 0x220;
}

/* MECHANISM: Frameless leaf with the global base held in a0 and the first
   destination in a3; scaled coordinates remain in their a1/a2 ABI registers.
   The portable /10 form is byte-exact when sched2 is disabled, preventing its
   repeated sign-shift hoist across mfhi and the quotient shift. */
