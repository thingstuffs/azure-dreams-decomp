#include "modules/dungeon_ovl_e0365c.h"
#include "shared/sprite_frame_state.h"

void set_actor_directional_animation(void *object, void *unused, SpriteFrameState *display, void *orientation) {
    s32 directionIndex;
    u8 *directionTable;

    *((s8 *)object + 0x9A) = 0x10;
    *((s8 *)object + 0x9B) = 0;
    directionTable = D_80174528;
    display->frameTable = directionTable;
    directionIndex = ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)orientation + 0x2A) + 0x100) >> 9) & 7;
    select_sprite_entry(display, directionTable[directionIndex], 0);
}
