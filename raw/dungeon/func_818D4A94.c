#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern s16 D_80025118[5];
extern s32 D_800814A0[3];

void func_818D4A94(void *arg0, void *arg1)
{
    register s32 x ASM_REG("$2");
    register s32 a ASM_REG("$4");
    register s32 aux ASM_REG("$6");
    register s32 one ASM_REG("$3");
    s32 z;

    x = FIELD(arg1, s32, 0);
    x += FIELD(arg0, s32, 0x3C);
    FIELD(arg1, s32, 0) = x;
    x = FIELD(arg1, s32, 4);
    x += FIELD(arg0, s32, 0x40);
    FIELD(arg1, s32, 4) = x;
    x = FIELD(arg1, s32, 8);
    x += FIELD(arg0, s32, 0x44);
    FIELD(arg1, s32, 8) = x;

    x = FIELD(arg0, s32, 0x3C);
    z = FIELD(arg0, s32, 0x48);
    a = FIELD(arg0, s32, 0x4C);
    aux = FIELD(arg0, s32, 0x50);
    x += z;
    FIELD(arg0, s32, 0x3C) = x;
    x = FIELD(arg0, s32, 0x40);
    z = FIELD(arg0, s32, 0x44);
    x += a;
    z += aux;
    ASM_USE(z);
    FIELD(arg0, s32, 0x40) = x;
    x = FIELD(arg0, s16, 0x34);
    ASM_USE(x);
    ASM_KEEP_MEM_NV(a, D_80025118[0]);
    ASM_USE2_NV(a, x);
    FIELD(arg0, s32, 0x44) = z;
    ASM_USE(z);
    a = FIELD(arg1, s16, 2);
    ASM_USE(a);
    one = 1;
    ASM_USE2_NV(a, one);
    x -= a;
    if (x < 0) {
        x = -x;
    }
    x = x < 0x10;
    ASM_KEEP_DEP_NV(one, x);
    D_80025118[0] = one;
    if (x) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

    x = FIELD(arg0, u16, 0x32);
    x -= 8;
    FIELD(arg0, u16, 0x32) = x;
    x <<= 16;
    if (x <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
