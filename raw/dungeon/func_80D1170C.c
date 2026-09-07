#include "common.h"

#define FIELD(obj, type, offset) (*(type)((u8 *)(obj) + (offset)))

extern s32 D_800814A0;

void func_80170F0C(void *arg0, void *arg1)
{
    s16 timer;
    s32 red;
    s32 green;
    s32 blue;
    s32 product;
    s32 *page;

    FIELD(arg1, s32 *, 0) += FIELD(arg0, s32 *, 0x40);
    FIELD(arg1, s32 *, 4) += FIELD(arg0, s32 *, 0x44);
    FIELD(arg1, s32 *, 8) += FIELD(arg0, s32 *, 0x48);

    product = FIELD(arg0, u8 *, 0) * FIELD(arg0, s16 *, 0x32);
    red = product / FIELD(arg0, s16 *, 0x34);
    ASM_MEM_BARRIER();
    product = FIELD(arg0, u8 *, 1) * FIELD(arg0, s16 *, 0x32);
    green = product / FIELD(arg0, s16 *, 0x34);
    ASM_MEM_BARRIER();
    product = FIELD(arg0, u8 *, 2) * FIELD(arg0, s16 *, 0x32);
    blue = product / FIELD(arg0, s16 *, 0x34);

    FIELD(arg0, s32 *, 0x48) += FIELD(arg0, s32 *, 0x54);
    timer = FIELD(arg0, u16 *, 0x32);
    timer -= 1;
    FIELD(arg0, u16 *, 0x32) = timer;
    FIELD(arg0, s8 *, 4) = red;
    FIELD(arg0, s8 *, 5) = green;
    FIELD(arg0, s8 *, 6) = blue;
    FIELD(arg0, s32 *, 8) = FIELD(arg0, s32 *, 4);

    if ((timer << 16) <= 0) {
        FIELD(arg0, u16 *, -2) |= 0x8000;
        page = (s32 *)0x80080000;
        ASM_KEEP(page);
        page[0x14A0 / sizeof(s32)] =
            page[0x14A0 / sizeof(s32)] | 0x8000;
    }
}

/* MECHANISM: Frameless leaf; a separate product temp keeps mflo in v0 while
   quotient lifetimes color a2/a1/a0, with memory barriers forcing each lh reload.
   Split u16 decrement selects addiu; kept 0x80080000 page emits lone lui + 0x14a0. */
