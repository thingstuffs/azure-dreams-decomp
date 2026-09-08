#include "common.h"

extern void func_8004E994(s32 arg0);

// Process and clear three referenced values, then clear a fourth referenced value.
void func_800240EC(void *owner) {
    s32 slotIndex;

    for (slotIndex = 0; slotIndex < 3; slotIndex++) {
        func_8004E994(*(*(s32 **)((u8*)owner + 0x260 + slotIndex * 4)));
        *(*(s32 **)((u8*)owner + 0x260 + slotIndex * 4)) = 0;
    }
    *(*(s32 **)((u8*)owner + 0x26C)) = 0;
}
