#include "modules/dungeon_resource12_slot0.h"

void advance_linked_actor_motion_script(void *object, void *unused, void *display, void *orientation) {
    s32 directionIndex;
    u8 *directionTable;

    *((s8 *)object + 0x9A) = 0x10;
    *((s8 *)object + 0x9B) = 0;
    directionTable = ((u8 *)D_80175A64);
    *(void **)((u8 *)display + 0x2C) = directionTable;
    directionIndex = ((g_game_work.view.viewAngle + *(s16 *)((u8 *)orientation + 0x2A) + 0x100) >> 9) & 7;
    select_sprite_entry(display, directionTable[directionIndex], 0);
}
