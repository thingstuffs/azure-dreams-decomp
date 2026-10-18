#include "modules/dungeon_ovl_1830850.h"

void inventory_clear_object_field_and_entry(s32 object_addr) {
    ovl_1830850_818112EC_S_800262EC_0 *object_data;

    object_data = object_addr + 0x20;
    object_data->unk_10 = 0;
    inventory_clear_entry_value(object_data->unk_54);
}
