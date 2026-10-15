#include "modules/dungeon_ovl_1831cd8.h"

void func_80027AD0(void *context, s32 currentValue, s32 maxValue) {
    ovl_1831cd8_81812AD0_RECT rect;

    rect = D_80025034[0];
    rect.h = ((s32) (currentValue * 0x90) / maxValue) + 4;
    func_800499E8(*(s32 *)((s8 *)context + 0x4C) + 0x18, &rect, D_80080B54);
}
