#include "modules/dungeon_resource08_slot0.h"

void func_80171F40(void *object, void *unused, void *display, void *orientation) {
    s32 directionIndex;
    u8 *directionTable;

    *((s8 *)object + 0x9A) = 0x10;
    *((s8 *)object + 0x9B) = 0;
    directionTable = ((u8 *)D_80174C4C);
    *(void **)((u8 *)display + 0x2C) = directionTable;
    directionIndex = ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)orientation + 0x2A) + 0x100) >> 9) & 7;
    select_sprite_entry(display, directionTable[directionIndex], 0);
}
