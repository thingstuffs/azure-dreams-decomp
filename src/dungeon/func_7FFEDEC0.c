#include "modules/dungeon_town_map.h"

void send_resource_command_23(s32 entry_index) {
    write_resource_command(D_800CFBA0[entry_index], 0x23);
}
