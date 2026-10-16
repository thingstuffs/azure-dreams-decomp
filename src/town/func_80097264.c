#include "common.h"
#include "shared/town_handler.h"

void func_80048A44();
s32 townViewRelativeAngleSector();
extern u8 D_80080A84;

/* Applies a selected source byte to the destination and adjusts its sixth byte. */
void townApplyASelectedSourceByteDestinationAdjustsSixthByte(u8 *sourceBytes, s32 selection, u8 *destination) {
    s32 offset;

    offset = townViewRelativeAngleSector(selection);
    func_80048A44(destination, *(sourceBytes + offset), 0, 0);
    destination[5] = destination[5] + (2 / (s32)D_80080A84);
}
