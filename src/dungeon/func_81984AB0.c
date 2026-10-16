#include "modules/dungeon_ovl_19a332c.h"

void inventorySelectEntryAndResetObject(ovl_19a332c_81984AB0_S_81984AB0_0 *object, s16 entry_index) {
    s32 entry_base;

    object->unk_04 = entry_index;
    object->unk_05 = 0;
    entry_base = ((ovl_19a332c_81984AB0_S_81984AB0_2 *)(((ovl_19a332c_81984AB0_S_81984AB0_1 *)object)->unk_08))->unk_0C;
    object->unk_14 = (u16) (object->unk_14 & 0x9FFF);
    object->unk_00 = (s32) (entry_base + (entry_index * 0x16));
}
