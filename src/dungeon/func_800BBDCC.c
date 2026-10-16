#include "common.h"
#include "shared/record_ptrs.h"

extern s32 hasEnoughAvailableRuntimeNodes(u32);
extern void func_800C1A44(u8, u8, s16);


/* Processes the two object slots if hasEnoughAvailableRuntimeNodes(2) succeeds. */
s32 dungeonBeginFamiliarRestorationEffects(void)
{
    s32 slot;
    u8 *object;
    u8 *linked_object;

    if (hasEnoughAvailableRuntimeNodes(2) == 0) {
        return 0;
    }

    slot = 0;
    do {
        object = *(u8 **)(((u8 *)D_800E3D7C) + 0xAC + slot * 4);
        if (object != 0) {
            linked_object = *(u8 **)(object - 0x14);
            func_800C1A44(linked_object[0x24], linked_object[0x25],
                          *(s16 *)(object + 0x88));
        }
        slot++;
    } while (slot < 2);

    return 1;
}
