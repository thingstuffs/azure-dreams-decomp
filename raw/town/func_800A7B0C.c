#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_80083160[0xB2];
extern u8 D_800A51CC[16];

void func_800A526C(void *arg0)
{
    u8 *base;
    s32 timer;
    u16 component;

    base = D_80083160;
    FIELD(base, s16, 0xAC) =
        FIELD(base, u16, 0xAC) +
        ((FIELD(arg0, s16, 0x0) - FIELD(base, s16, 0xAC)) /
         FIELD(arg0, s32, 0x18));
    FIELD(base, s16, 0xAE) =
        FIELD(base, u16, 0xAE) +
        ((FIELD(arg0, s16, 0x2) - FIELD(base, s16, 0xAE)) /
         FIELD(arg0, s32, 0x18));
    FIELD(base, s16, 0xB0) =
        FIELD(base, u16, 0xB0) +
        ((FIELD(arg0, s16, 0x4) - FIELD(base, s16, 0xB0)) /
         FIELD(arg0, s32, 0x18));

    timer = FIELD(arg0, s32, 0x18) - 1;
    FIELD(arg0, s32, 0x18) = timer;
    if (timer <= 0) {
        component = FIELD(arg0, u16, 0x0);
        FIELD(arg0, u16, 0x10) = component;
        FIELD(base, u16, 0xAC) = component;

        component = FIELD(arg0, u16, 0x2);
        FIELD(arg0, u16, 0x12) = component;
        FIELD(base, u16, 0xAE) = component;

        component = FIELD(arg0, u16, 0x4);
        FIELD(arg0, u16, 0x14) = component;
        FIELD(base, u16, 0xB0) = component;

        FIELD(arg0, void *, 0x20) = D_800A51CC;
    }
}
