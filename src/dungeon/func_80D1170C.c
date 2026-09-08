#include "common.h"

#define FIELD(obj, type, offset) (*(type)((u8 *)(obj) + (offset)))

extern s32 D_800814A0;

/* Move and fade the effect, apply vertical acceleration, and flag it when its lifetime ends. */
void func_80170F0C(void *effect, void *position)
{
    s16 life_left;
    s32 red;
    s32 green;
    s32 blue;
    s32 color_product;
    s32 *flag_page;

    FIELD(position, s32 *, 0) += FIELD(effect, s32 *, 0x40);
    FIELD(position, s32 *, 4) += FIELD(effect, s32 *, 0x44);
    FIELD(position, s32 *, 8) += FIELD(effect, s32 *, 0x48);

    color_product = FIELD(effect, u8 *, 0) * FIELD(effect, s16 *, 0x32);
    red = color_product / FIELD(effect, s16 *, 0x34);
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    color_product = FIELD(effect, u8 *, 1) * FIELD(effect, s16 *, 0x32);
    green = color_product / FIELD(effect, s16 *, 0x34);
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    color_product = FIELD(effect, u8 *, 2) * FIELD(effect, s16 *, 0x32);
    blue = color_product / FIELD(effect, s16 *, 0x34);

    FIELD(effect, s32 *, 0x48) += FIELD(effect, s32 *, 0x54);
    life_left = FIELD(effect, u16 *, 0x32);
    life_left -= 1;
    FIELD(effect, u16 *, 0x32) = life_left;
    FIELD(effect, s8 *, 4) = red;
    FIELD(effect, s8 *, 5) = green;
    FIELD(effect, s8 *, 6) = blue;
    FIELD(effect, s32 *, 8) = FIELD(effect, s32 *, 4);

    if ((life_left << 16) <= 0) {
        FIELD(effect, u16 *, -2) |= 0x8000;
        flag_page = (s32 *)0x80080000;
        ASM_KEEP(flag_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        flag_page[0x14A0 / sizeof(s32)] =
            flag_page[0x14A0 / sizeof(s32)] | 0x8000;
    }
}

/* MECHANISM: Frameless leaf; a separate color_product temp keeps mflo in v0 while
   quotient lifetimes color a2/a1/a0, with memory barriers forcing each lh reload.
   Split u16 decrement selects addiu; kept 0x80080000 flag_page emits lone lui + 0x14a0. */
