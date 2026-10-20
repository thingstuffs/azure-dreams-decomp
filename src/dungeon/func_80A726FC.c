#include "modules/dungeon_resource07_slot0.h"
#include "shared/sprite_frame_state.h"

void initialize_opposite_facing_effect(void *effect, s32 *position, SpriteFrameState *sprite, void *source)
{
    s32 direction;
    s16 *direction_x;

    direction = (*(u16 *)((s8 *)source + 0x2A) >> 9) & 7;
    *((s8 *)effect + 0x9A) = 0x10;
    *((s8 *)effect + 0x9B) = 0;
    sprite->frameTable = ((u8 *)D_80174158);
    select_sprite_entry(sprite,(s16)(((u8 *)D_80174158)[((g_game_work.view.camera_rotation.parts.viewAngle +
                               *(s16 *)((s8 *)source + 0x2A) + 0x100) >> 9) & 7]),(s16)(0));
    direction_x = dir_step_x;
    direction *= 2;
    position[0] -= *(s16 *)((u8 *)direction_x + direction) << 19;
    position[1] -= *(s16 *)((u8 *)dir_step_y + direction) << 19;
}
