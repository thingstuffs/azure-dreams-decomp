#include "common.h"

extern s32 D_80082A38[];
extern u8 *D_800CFCC4[];
extern s32 D_800D0910[];

// Populate three global slots with a signed byte, lookup value, and record pointer from the first entry.
s32 func_8009E258(void) {
    D_80082A38[0x12] = (s8)D_800CFCC4[0][0x4E];
    D_80082A38[0x13] = D_800D0910[D_800CFCC4[0][0x4C]];
    D_80082A38[0x14] =
        (u32)((u8 *)0x80010AB4 +
              ((D_800CFCC4[0][0x4F] & 0x3F) * 0x54));
    return 0;
}
