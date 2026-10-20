#include "modules/dungeon_resource03_slot0.h"
#include "shared/sprite_frame_state.h"

void copy_display_orientation_state(void *object, void *unused, void *display, void *orientation) {
    s32 directionIndex;
    u8 *directionTable;

    *((s8 *)object + 0x9A) = 0x10;
    *((s8 *)object + 0x9B) = 0;
    directionTable = ((u8 *)D_80173C8C);
    ((SpriteFrameState *)display)->frameTable = directionTable;
    directionIndex = ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)orientation + 0x2A) + 0x100) >> 9) & 7;
    select_sprite_entry(display, directionTable[directionIndex], 0);
}
