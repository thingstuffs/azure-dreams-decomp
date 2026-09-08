#include "common.h"

extern s32 func_8003FA44(u32);
extern void func_800C1A44(u8, u8, s16);

extern u8 *D_800E3D7C[3];

s32 func_800C152C(void)
{
    s32 i;
    u8 *object;
    u8 *linked;

    if (func_8003FA44(2) == 0) {
        return 0;
    }

    i = 0;
    do {
        object = *(u8 **)(D_800E3D7C[0] + 0xAC + i * 4);
        if (object != 0) {
            linked = *(u8 **)(object - 0x14);
            func_800C1A44(linked[0x24], linked[0x25],
                         *(s16 *)(object + 0x88));
        }
        i++;
    } while (i < 2);

    return 1;
}
