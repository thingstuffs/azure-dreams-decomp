#include "modules/dungeon_ovl_d54c.h"

void townEnsureResourceAtFront(s32 resource_flag, M2C_UNK resource_group, M2C_UNK resource_id) {
    s32 entry_index;

    entry_index = townFindResourceIndexByKey(resource_flag, resource_group, resource_id);
    if (entry_index < 0) {
        entry_index = townInstallResourceDescriptorAtFront(resource_flag, resource_group, resource_id, entry_index & 0x7FFFFFFF);
    }
    if (entry_index != 0) {
        townMoveResourceToFront(entry_index);
    }
}
