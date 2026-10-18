#include "modules/dungeon_town_map.h"

void write_resource_command(s32 value, s32 command) {
    D_800CFC24[3] = (s8)(value >> 8);
    D_800CFC24[2] = value;
    D_800CFC24[4] = (s8)(value >> 0x10);
    D_800CFC24[5] = (s8)(value >> 0x18);
    D_800CFC24[6] = command;
    func_80035208(&D_800CFC24);
}
