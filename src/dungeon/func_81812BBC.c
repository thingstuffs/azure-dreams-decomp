#include "modules/dungeon_ovl_1831cd8.h"

void refresh_menu_entry_resources(void *entry_table, void *resource_names)
{
    ovl_1831cd8_81812BBC_Work name_buffer;
    s32 name_offset;
    s32 entry_index;
    ovl_1831cd8_81812BBC_Entry **entry_slot;

    entry_index = 6;
    entry_slot = (ovl_1831cd8_81812BBC_Entry **)((u8 *)entry_table + 0x18);
    name_offset = 0;
    for (;;) {
        ovl_1831cd8_81812BBC_Entry *entry = *entry_slot;
        ovl_1831cd8_81812BBC_Inner *inner = entry->unk4;
        s32 inner_value = inner->unkA;
        name_buffer.unk0 = D_8002503C;

        if (inner_value >= 0x79) {
            if (entry->unk0 == 0) {
                strncat(&name_buffer, (u8 *)resource_names + name_offset, 0x12);
                (*entry_slot)->unk0 = (s32 *)func_8004DC14(&name_buffer, 1);
            }
        } else if (entry->unk0 != 0) {
            func_8004E99C(entry->unk0);
            (*entry_slot)->unk0 = 0;
        }
        entry_slot += 1;
        entry_index += 1;
        name_offset += 0x12;
        if (entry_index >= 0xE) {
            break;
        }
    }
}
