#include "common.h"

#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define VU16_AT(p, o) (*(volatile u16 *)((u8 *)(p) + (o)))

void func_800BC390(void *arg0)
{
    s32 state;
    s32 next;
    s32 value;
    u16 increment;

    state = S16_AT(arg0, 0);
    next = U16_AT(arg0, 2) - 1;
    U16_AT(arg0, 2) = next;
    if (state == 1) {
        goto state_1;
    }
    if (state >= 2) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    return;
    goto done;

state_ge_2:
    if (state == 2) {
        goto state_2;
    }
    return;
    goto done;

state_0:
{
    register s16 marker ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    if ((next << 16) > 0) {
        goto done;
    }
    VU16_AT(arg0, 2) = 12;
    increment = VU16_AT(arg0, 0);
    marker = 3;
    S16_AT(arg0, 0x14) = marker;
    goto advance_state;
}

state_1:
    value = S32_AT(arg0, 8);
    if (value > 0) {
        S32_AT(arg0, 8) = value + (s32)0xFFF7FBFC;
    }
    if (S16_AT(arg0, 2) > 0) {
        goto done;
    }
    increment = U16_AT(arg0, 0);
advance_state:
    U16_AT(arg0, 0) = increment + 1;
    goto done;

state_2:
{
    register u32 pagebase ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    pagebase = 0x80080000;
    ASM_KEEP(pagebase);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    U16_AT(arg0, -2) = U16_AT(arg0, -2) | 0x8000;
    S32_AT((void *)pagebase, 0x14A0) |= 0x8000;
}

done:
    return;
}

/* MECHANISM: Frameless CFG with the original pointer held in a0 and decremented
   halfword held in a1 across all three tail-jump sites; signed/unsigned field
   aliases reproduce the retail lh/lhu split and the 0x8008 page base. */
