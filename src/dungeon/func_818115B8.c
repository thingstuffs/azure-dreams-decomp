#include "modules/dungeon_ovl_1831370.h"

void func_800265B8(s32 objectAddress, s32 updateValue) {
    s32 updatedValue;
    s32 *object;

    object = (s32 *)(objectAddress + 0x20);
    func_8004EAC4(object[5], updateValue, object[2]);
    func_800263C0(object[28], object[5]);
    updatedValue = func_80026388(1, object[2], object[4]);
    object[2] = updatedValue;
    func_80026370(object[28], updatedValue);
}
