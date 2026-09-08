#include "common.h"

extern s32 func_8003FA44(u32);
extern void func_800C1A44(u8, u8, s16);

extern u8 *D_800E3D7C[3];

/* Processes the two object slots if func_8003FA44(2) succeeds. */
s32 func_800C152C(void)
{
    s32 slot;
    u8 *object;
    u8 *linked_object;

    if (func_8003FA44(2) == 0) {
        return 0;
    }

    slot = 0;
    do {
        object = *(u8 **)(D_800E3D7C[0] + 0xAC + slot * 4);
        if (object != 0) {
            linked_object = *(u8 **)(object - 0x14);
            func_800C1A44(linked_object[0x24], linked_object[0x25],
                         *(s16 *)(object + 0x88));
        }
        slot++;
    } while (slot < 2);

    return 1;
}
