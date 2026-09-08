#include "common.h"

extern s32 D_80082A38[];
extern u8 *D_800CFCC4[];
extern s32 D_800D0910[];

/* Store the current record's signed value and table lookup in the script globals. */
s32 func_8009E218(void) {
    D_80082A38[0x12] = (s8)D_800CFCC4[0][0x4E];
    D_80082A38[0x13] = D_800D0910[D_800CFCC4[0][0x4C]];
    return 0;
}
