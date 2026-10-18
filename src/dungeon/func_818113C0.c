#include "modules/dungeon_ovl_1831370.h"

void inventory_set_object_entry_address(ovl_1831370_818113C0_S_800263C0_0 *object, s32 source) {
    release_object_handle(object);
    *object->unk_0C = func_8004DC14(source, 0);
}
