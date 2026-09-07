#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_80083160[0xB2];
extern u8 D_800A526C[16];

extern void func_800A5264(void *arg0, s32 arg1, void *arg2);

void func_800A51CC(void *arg0)
{
    u8 *base;
    s32 value;
    u16 component;

    base = D_80083160;
    value = FIELD(arg0, s32, 0x0);
    if ((value != FIELD(base, s32, 0xAC)) ||
        (FIELD(arg0, s16, 0x4) != FIELD(base, s16, 0xB0))) {
        if ((value != FIELD(arg0, s32, 0x10)) ||
            (FIELD(arg0, s16, 0x4) != FIELD(arg0, s16, 0x14))) {
            FIELD(arg0, s32, 0x18) = 9;
            FIELD(arg0, void *, 0x20) = D_800A526C;
            return func_800A5264(arg0, value, base);
        }

        component = FIELD(base, u16, 0xAC);
        FIELD(arg0, u16, 0x0) = component;
        FIELD(arg0, u16, 0x10) = component;
        component = FIELD(base, u16, 0xAE);
        FIELD(arg0, u16, 0x2) = component;
        FIELD(arg0, u16, 0x12) = component;
        component = FIELD(base, u16, 0xB0);
        FIELD(arg0, u16, 0x4) = component;
        FIELD(arg0, u16, 0x14) = component;
    }
}
