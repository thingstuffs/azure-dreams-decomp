#include "common.h"

extern s32 func_800006C4(s32);
extern s32 func_80000754(s32);
extern s32 func_80000858(s32, s32);

extern s32 D_00000F08[3];
extern s32 D_00000F4C[3];
extern s32 D_00001028[3];

/* Returns the selected table entry's value plus the global offset after updating state. */
s32 func_808BB364(void) {
    s32 selectedIndex;
    s32 entryValue;

    func_80000754(1);
    selectedIndex = D_00000F08[0];
    entryValue = D_00000F4C[selectedIndex * 4];
    func_80000858(selectedIndex, 1);
    func_800006C4(1);
    return entryValue + D_00001028[0];
}
