#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/monster/cyclone.h"
#include "engine/graphics.h"
#include "slus.h"
#include "dungeon/monster/cyclone_frames.h"

/* Updates object direction and grows it to full scale after an eight-tick delay. */
void grow_object_after_delay(DirectionalRenderObjectBody *animation, ObjectPosition *unused_position, SpriteFrameState *object) {
    s32 direction_index;
    s16 phase;
    u16 phase_u;
    u16 scale;

    animation->ticks.s = animation->ticks.s + 1;
    advance_sprite_animation_and_textures(object);
    if (object->flags & 0x6000) {
        direction_index = g_game_work.view.camera_rotation.parts.viewAngle;
        direction_index += animation->facing_angle.s;
        direction_index += 0x100;
        direction_index >>= 9;
        direction_index &= 7;
        select_sprite_entry(object, cyclone_move_direction_frames[direction_index], 0);
    }

    phase = animation->phase.s;
    phase_u = animation->phase.u;
    if (phase != 1) {
        if (phase >= 2) {
            return;
        }
        if (phase != 0) {
            return;
        }
        if (animation->ticks.u < 8) {
            return;
        }
        animation->phase.u = phase_u + 1;
        return;
    }
    scale = object->scale_y + 0x100;
    object->scale_y = scale;
    object->scale_x = scale;
    if ((u16)scale >= 0x1000U || object->scale_y >= 0x1000U) {
        object->scale_y = 0x1000;
        object->scale_x = 0x1000;
        animation->phase.u = animation->phase.u + 1;
    }
}
