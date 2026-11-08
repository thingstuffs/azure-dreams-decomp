#include "town/map/animation.h"
#include "town/map/burst_particle_body.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "shared/position_views.h"
#include "slus.h"
#include "town/map/motion.h"

/* Update effect motion, size and brightness, then mark it finished. */
void update_effect_motion_size_and_brightness(void *effect_fields, ObjectPosition *position, SpriteFrameState *sprite) {
    TownBurstParticleBody *body = effect_fields;
    s16 state;
    s32 fade_end_state;
    s32 global_flags;
    s32 grow_end_state;
    u16 size;

    body->ticks_left = (u16) (body->ticks_left - 1);
    advance_sprite_animation_and_textures(sprite);
    state = body->phase;
    switch (state) {
    case 0:
        size = sprite->scale_y + 0x80;
        sprite->scale_y = size;
        sprite->scale_x = size;
        sprite->color.word = (s32) (sprite->color.word + 0x80808);
        position->x.w.i = (s16) ((u16) position->x.w.i + ((s32) (body->target_x - position->x.w.i) >> 2));
        position->y.w.i = (s16) ((u16) position->y.w.i + ((s32) (body->target_y - position->y.w.i) >> 2));
        position->z.w.i = (s16) ((u16) position->z.w.i + ((s32) (body->target_z - position->z.w.i) >> 2));
        grow_end_state = 0xFF;
        if (!((s16) body->ticks_left > 0)) {
            body->phase = grow_end_state;
        }
        return;

    case 1:
    {
        ObjectPosition *motion = position;
        motion->x.v = motion->x.v + motion->velocity_x;
        motion->y.v = motion->y.v + motion->velocity_y;
        motion->z.v = motion->z.v + motion->velocity_z;
        motion->velocity_x = motion->velocity_x - (motion->velocity_x >> 3);
        motion->velocity_y = motion->velocity_y - (motion->velocity_y >> 3);
        motion->velocity_z = motion->velocity_z - (motion->velocity_z >> 3);
    }
        sprite->color.word = (s32) (sprite->color.word + 0xFFF7F7F8);
        fade_end_state = 0xFF;
        if ((u8) sprite->color.word == 0) {
            body->phase = fade_end_state;
            return;
        }
        return;

    case 0xFF:
        NODE_HEADER(body)->flags = (u16) (NODE_HEADER(body)->flags | 0x8000);
        global_flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        object_flag_block.flags = global_flags;
        return;
    default:
        return;
    }
}
