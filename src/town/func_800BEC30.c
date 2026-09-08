#include "common.h"

#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define VU16_AT(p, o) (*(volatile u16 *)((u8 *)(p) + (o)))

extern void func_800BC424(void *, s32);

void func_800BC390(void *arg0)
{
    s32 state;
    s32 next;
    s32 value;

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
    register s16 marker ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

    if ((next << 16) > 0) {
        goto done;
    }
    VU16_AT(arg0, 2) = 12;
    (void)VU16_AT(arg0, 0);
    marker = 3;
    S16_AT(arg0, 0x14) = marker;
    func_800BC424(arg0, next);
    goto done;
}

state_1:
    value = S32_AT(arg0, 8);
    if (value > 0) {
        S32_AT(arg0, 8) = value + (s32)0xFFF7FBFC;
    }
    if (S16_AT(arg0, 2) > 0) {
        goto done;
    }
    U16_AT(arg0, 0) = U16_AT(arg0, 0) + 1;
    goto done;

state_2:
{
    register u32 pagebase ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

    pagebase = 0x80080000;
    ASM_KEEP(pagebase);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    U16_AT(arg0, -2) = U16_AT(arg0, -2) | 0x8000;
    S32_AT((void *)pagebase, 0x14A0) |= 0x8000;
}

done:
    return;
}

/* MECHANISM: Frameless CFG with the original pointer held in a0 and decremented
   halfword held in a1 across all three tail-jump sites; signed/unsigned field
   aliases reproduce the retail lh/lhu split and the 0x8008 page base. */
