#include "modules/dungeon_dungeon_setup.h"

void dungeonClearDungeonStateBytes(void) {
    s32 byte_index;
    s32 clear_base;
    byte_index = 6;
    clear_base = (s32)((u8 *)&D_800E3D7C + 0x24);
    do {
        *(u8*)(byte_index + clear_base) = 0;
        byte_index -= 1;
    } while (byte_index >= 0);
}
