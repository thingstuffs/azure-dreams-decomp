#include "modules/dungeon_ovl_d54c.h"

void func_8008B0E8(s32 resource_flag, M2C_UNK resource_group, M2C_UNK resource_id) {
    s32 entry_index;

    entry_index = func_8008AD1C(resource_flag, resource_group, resource_id);
    if (entry_index < 0) {
        entry_index = func_8008AFB0(resource_flag, resource_group, resource_id, entry_index & 0x7FFFFFFF);
    }
    if (entry_index != 0) {
        func_8008AE4C(entry_index);
    }
}
