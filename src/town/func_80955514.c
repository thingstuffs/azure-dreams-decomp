#include "common.h"

typedef struct S_80022514_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x4];
    s32 unk_08;
} S_80022514_0;   /* arg0 in func_80022514 */



extern s32 D_800814A0;

void func_80022514(void *arg0) {
    s16 mode;
    s32 delta;
    s32 next;
    register s32 value ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

    mode = ((S_80022514_0 *)arg0)->unk_00.s;
    value = ((S_80022514_0 *)arg0)->unk_00.u;
    next = ((S_80022514_0 *)arg0)->unk_02.s - 1;
    ((S_80022514_0 *)arg0)->unk_02.s = next;
    if (mode == 1) {
        goto mode_one;
    }
    if (mode < 2) {
        delta = 0x40000;
        if (mode == 0) {
            goto mode_zero;
        }
        goto done;
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if (mode == 2) {
        goto mode_two;
    }
    goto done;

mode_zero:
{
    s32 count;
    s32 increment;
    s32 sum;

    delta |= 0x404;
    ASM_MEM_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    sum = ((S_80022514_0 *)arg0)->unk_08;
    count = ((S_80022514_0 *)arg0)->unk_02.u;
    sum += delta;
    ((S_80022514_0 *)arg0)->unk_08 = sum;
    if (count >= 0) {
        goto done;
    }
    increment = ((S_80022514_0 *)arg0)->unk_00.u;
    ((S_80022514_0 *)arg0)->unk_02.s = 0x10E;
    increment++;
    ((S_80022514_0 *)arg0)->unk_00.u = increment;
    goto done;
}

mode_one:
{
    if ((s16)next >= 0) {
        goto done;
    }
    {
        register s32 increment ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

        increment = value + 1;
        ((S_80022514_0 *)arg0)->unk_00.u = increment;
    }
    goto done;
}

mode_two:
{
    s32 offset;
    s32 sum;

    offset = 0xFFF7F7F8;
    sum = ((S_80022514_0 *)arg0)->unk_08 + offset;
    ((S_80022514_0 *)arg0)->unk_08 = sum;
    if (sum <= 0x80808) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

done:
    ASM_CLOBBER("$2");   /* MATCH pin: load-bearing for the whole function shape */
    return;
}
