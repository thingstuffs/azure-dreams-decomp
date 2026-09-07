#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_8009CFE0(void);
extern s32 D_800814A0[];

void func_800BB030(void *arg0) {
    s8 *ptr;
    s32 state;
    s32 counter;
    s32 quotient;
    register s32 intensity ASM_REG("$2");

    if (func_8009CFE0() != 0) {
        ptr = FIELD(arg0, s8 *, 0x98);
        if (ptr != 0) {
            *ptr = 0;
        }
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        goto end;
    }

    counter = FIELD(arg0, u16, 0x6C) + 1;
    state = FIELD(arg0, s16, 0x68);
    FIELD(arg0, u16, 0x6C) = counter;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto end;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto end;

state_0:
    quotient = (s16)counter / 4;
    FIELD(arg0, s16, 0x66) = quotient * 3;
    intensity = (s16)FIELD(arg0, u16, 0x6C) / 2;
    FIELD(arg0, s8, 0x97) = intensity;
    if (FIELD(arg0, s16, 0x6C) < 0x40) {
        goto end;
    }
    FIELD(arg0, u16, 0x6C) = 0;
    FIELD(arg0, u16, 0x68)++;
    goto end;

state_1: {
    register s32 q ASM_REG("$2");

    q = (s16)counter / 4;
    FIELD(arg0, s16, 0x66) = 0x30 - q * 3;
    FIELD(arg0, s8, 0x97) = 0x20;
    if (FIELD(arg0, s16, 0x6C) >= 0x40) {
        FIELD(arg0, u16, 0x6C) = 0;
        FIELD(arg0, u16, 0x68)++;
    }
    goto end;
}

state_2: {
    register s32 half ASM_REG("$4");

    quotient = (s16)counter / 4;
    FIELD(arg0, s16, 0x66) = quotient * 3;
    half = (s16)FIELD(arg0, u16, 0x6C) / 2;
    intensity = 0x20 - half;
    FIELD(arg0, s8, 0x97) = intensity;
    if (FIELD(arg0, s16, 0x6C) < 0x40) {
        goto end;
    }
    FIELD(arg0, u16, 0x6C) = 0;
    FIELD(arg0, u16, 0x68)++;
    goto end;
}

state_3: {
    register s32 q ASM_REG("$2");

    q = (s16)counter / 4;
    FIELD(arg0, s16, 0x66) = 0x30 - q * 3;
    FIELD(arg0, s8, 0x97) = 0;
    if (FIELD(arg0, s16, 0x6C) < 0x40) {
        goto end;
    }
    FIELD(arg0, u16, 0x6C) = 0;
    FIELD(arg0, s16, 0x68) = 0;
}

end:
    return;
}
