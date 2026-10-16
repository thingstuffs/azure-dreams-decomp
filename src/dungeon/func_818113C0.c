#include "modules/dungeon_ovl_1831370.h"

void inventorySetObjectEntryAddress(ovl_1831370_818113C0_S_800263C0_0 *object, M2C_UNK source) {
    dungeonReleaseObjectHandle(object);
    *object->unk_0C = func_8004DC14(source, 0);
}
