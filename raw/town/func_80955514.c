#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_800814A0;

void func_80022514(void *arg0) {
    s16 mode;
    s32 delta;
    s32 next;
    register s32 value ASM_REG("$4");

    mode = FIELD(arg0, s16, 0);
    value = FIELD(arg0, u16, 0);
    next = FIELD(arg0, u16, 2) - 1;
    FIELD(arg0, u16, 2) = next;
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
    ASM_SCHED_BARRIER();
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
    ASM_MEM_BARRIER();
    sum = FIELD(arg0, s32, 8);
    count = FIELD(arg0, s16, 2);
    sum += delta;
    FIELD(arg0, s32, 8) = sum;
    if (count >= 0) {
        goto done;
    }
    increment = FIELD(arg0, u16, 0);
    FIELD(arg0, u16, 2) = 0x10E;
    increment++;
    FIELD(arg0, u16, 0) = increment;
    goto done;
}

mode_one:
{
    if ((s16)next >= 0) {
        goto done;
    }
    {
        register s32 increment ASM_REG("$2");

        increment = value + 1;
        FIELD(arg0, u16, 0) = increment;
    }
    goto done;
}

mode_two:
{
    s32 offset;
    s32 sum;

    offset = 0xFFF7F7F8;
    sum = FIELD(arg0, s32, 8) + offset;
    FIELD(arg0, s32, 8) = sum;
    if (sum <= 0x80808) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

done:
    ASM_CLOBBER("$2");
    return;
}
