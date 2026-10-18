#include "modules/dungeon_ovl_1954800.h"
s32 decrement_flagged_item_parameters(DungeonObject *object) {
    s32 changed_count;
    DungeonObjectEntry *entry;
    u8 group;
    u8 column;

    changed_count = 0;
    if (is_linked_object_flagged_10000() != 0) {
        return changed_count;
    }
    entry = object->entry4C;
    if (entry != 0) {
        group = entry->group;
        column = entry->column;
        if ((D_80073414[group].cells[column].flags & 0x8000) != 0 &&
            entry->amount >= -0x62) {
            entry->amount = (u8)entry->amount - 1;
            changed_count = 1;
        }
    }
    entry = object->entry50;
    if (entry != 0) {
        group = entry->group;
        column = entry->column;
        if ((D_80073414[group].cells[column].flags & 0x8000) != 0) {
            if (entry->amount >= -0x62) {
                entry->amount = (u8)entry->amount - 1;
                changed_count += 1;
            }
        }
    }
    return changed_count;
}
