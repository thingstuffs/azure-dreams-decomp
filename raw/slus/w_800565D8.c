#include "common.h"

typedef struct {
    u8 pad[0x20];
    volatile u8 unk20;
    volatile u8 unk21;
} S_800565D8;

s32 func_800565D8(S_800565D8 *arg0, u32 arg1)
{
    s32 ret;

    if (arg1 < 0x40) {
        register s32 delta ASM_REG("$2");
        register s32 doubled ASM_REG("$3");
        register s32 product ASM_REG("$6");

        if (arg0->unk21 == 0) {
            goto zero;
        }
        delta = 0x3F - arg1;
        doubled = arg0->unk21;
        doubled *= 2;
        product = doubled * delta;
        ret = -product;
        goto sign;
    }

    if (arg1 != 0x40) {
        goto positive;
    }

zero:
    ret = 0;
    goto done;

positive:
    {
        register s32 delta ASM_REG("$3");

        delta = arg1 - 0x40;
        if (arg0->unk20 == 0) {
            goto zero;
        }
        ret = arg0->unk20;
        ret *= 2;
        ret *= delta;
    }

sign:
    ret = (s16)ret;

done:
    return ret;
}
