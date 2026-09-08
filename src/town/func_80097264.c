#include "common.h"

void func_80048A44();
s32 func_80095360();
extern u8 D_80080A84;

/* Applies a selected source byte to the destination and adjusts its sixth byte. */
void func_800949C4(u8 *sourceBytes, s32 selection, u8 *destination) {
    s32 offset;

    offset = func_80095360(selection);
    func_80048A44(destination, *(sourceBytes + offset), 0, 0);
    destination[5] = destination[5] + (2 / (s32)D_80080A84);
}
