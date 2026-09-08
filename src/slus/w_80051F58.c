#include "common.h"

#include "common.h"

typedef struct S_80051F58_ptr {
    u8 pad00[6];
    u16 unk06;
    u8 pad08[0x10];
    s32 unk18;
} S_80051F58_ptr;

typedef struct S_80051F58 {
    S_80051F58_ptr *unk00;
    s16 state;
    u16 timer;
    u8 pad08[4];
    s16 unk0C;
} S_80051F58;

typedef struct S_80051F58_a2 {
    u8 pad00[0xC];
    u8 unk0C;
    u8 unk0D;
    u8 unk0E;
} S_80051F58_a2;

extern s32 D_800814A0_abs __attribute__((section(".data")));
__asm__(".set D_800814A0_abs, 0x800814A0");

void func_80051F58(S_80051F58 *a0, void *a1, S_80051F58_a2 *a2, void *a3)
{
    u16 timer = a0->timer;
    u16 next_state;
    int new_var;
    int state = a0->state;
    u16 ustate = *(volatile u16 *)&a0->state;

    new_var = timer + 1;
    a0->timer = new_var;
    if (state == 1) {
        goto case1;
    }
    if (state < 2) {
        if (state == 0) {
            goto case0;
        }
        goto default_case;
    }
    if (state == 2) {
        goto case2;
    }
    if (state == 3) {
        goto case3;
    }
    goto default_case;

case0:
    if (a0->unk0C == 0) {
        return;
    }
    a0->unk0C = 0;
    next_state = *(volatile u16 *)&a0->state;
    goto advance;

case1:
    {
        u8 v = a2->unk0E + 2;
        a2->unk0E = v;
        a2->unk0D = v;
        a2->unk0C = v;
    }
    if ((s16)a0->timer < 0x40) {
        return;
    }
    next_state = *(volatile u16 *)&a0->state;

advance:
    a0->timer = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    a0->state = next_state + 1;
    return;

case2:
    if ((s16)new_var < 0x100) {
        return;
    }
    {
        u16 next_state = ustate + 1;
        a0->state = next_state;
    }
    a0->timer = 0;
    return;

case3:
    {
        u8 v = a2->unk0E - 2;
        a2->unk0E = v;
        a2->unk0D = v;
        a2->unk0C = v;
    }
    if ((s16)a0->timer < 0x40) {
        return;
    }
    goto finish;

default_case:
    a2->unk0E = 0;
    a2->unk0D = 0;
    a2->unk0C = 0;

finish:
    a0->unk00->unk18 = 0;
    a0->unk00->unk06 += 1;
    *(volatile u16 *)((u16 *)a0 - 1) |= 0x8000;
    D_800814A0_abs |= 0x8000;
}
