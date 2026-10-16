#include "modules/dungeon_resource12_slot0.h"

void func_80171D74(void *object, void *unused, void *display, void *orientation) {
    s32 directionIndex;
    u8 *directionTable;

    *((s8 *)object + 0x9A) = 0x10;
    *((s8 *)object + 0x9B) = 0;
    directionTable = ((u8 *)D_80175A64);
    *(void **)((u8 *)display + 0x2C) = directionTable;
    directionIndex = ((gameWork.view.viewAngle + *(s16 *)((u8 *)orientation + 0x2A) + 0x100) >> 9) & 7;
    func_80047784(display, directionTable[directionIndex], 0);
}
