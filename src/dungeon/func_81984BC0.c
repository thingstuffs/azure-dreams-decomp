#include "modules/dungeon_ovl_19a332c.h"

void inventory_set_object_entry_address(ovl_19a332c_81984BC0_S_81984BC0_0 *object, s16 entry_index) {
    object->unk_00 = (s32) (((ovl_19a332c_81984BC0_S_81984BC0_2 *)(((ovl_19a332c_81984BC0_S_81984BC0_1 *)object)->unk_08))->unk_0C + (entry_index * 0x16));
}
