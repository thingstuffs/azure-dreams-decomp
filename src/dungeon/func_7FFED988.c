#include "modules/dungeon_ovl_d54c.h"

void ensure_resource_at_front(s32 resource_flag, M2C_UNK resource_group, M2C_UNK resource_id) {
    s32 entry_index;

    entry_index = find_resource_index_by_key(resource_flag, resource_group, resource_id);
    if (entry_index < 0) {
        entry_index = install_resource_descriptor_at_front(resource_flag, resource_group, resource_id, entry_index & 0x7FFFFFFF);
    }
    if (entry_index != 0) {
        move_resource_to_front(entry_index);
    }
}
