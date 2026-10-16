#include "modules/dungeon_ovl_1831370.h"

void func_800265B8(s32 objectAddress, s32 updateValue) {
    s32 updatedValue;
    s32 *object;

    object = (s32 *)(objectAddress + 0x20);
    func_8004EAC4(object[5], updateValue, object[2]);
    inventorySetObjectEntryAddress(object[28], object[5]);
    updatedValue = dungeonAdjustSelectionByItemCount(1, object[2], object[4]);
    object[2] = updatedValue;
    dungeonSetIndexedObjectField(object[28], updatedValue);
}
