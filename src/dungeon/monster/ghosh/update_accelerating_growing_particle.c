#include "common.h"
#include "shared/entity.h"
#include "dungeon/monster/ghosh/growing_particle.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/monster/ghosh.h"
#include "slus.h"

/* Advance effect motion and animation, and flag completion when its lifetime ends. */
void update_accelerating_growing_particle(void *effect_arg, ObjectPosition *position, SpriteFrameState *animation) {
    GhoshGrowingParticleBody *effect = effect_arg;
    u16 frame_count;
    u16 remaining_ticks;

    effect->velocity_x = effect->velocity_x + effect->acceleration_x;
    effect->velocity_y = effect->velocity_y + effect->acceleration_y;
    effect->velocity_z = effect->velocity_z + effect->acceleration_z;
    position->x.v = position->x.v + effect->velocity_x;
    position->y.v = position->y.v + effect->velocity_y;
    position->z.v = position->z.v + effect->velocity_z;
    frame_count = effect->animation_ticks + 1;
    effect->animation_ticks = frame_count;
    if (!(frame_count & 1)) {
        advance_sprite_animation_and_textures(animation);
    }
    animation->scale_x = animation->scale_x + 0x28;
    animation->scale_y = animation->scale_y + 0x28;
    remaining_ticks = effect->remaining_ticks - 1;
    effect->remaining_ticks = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        NODE_HEADER(effect)->flags = NODE_HEADER(effect)->flags | 0x8000;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
    if (animation->flags & 0x8000) {
        NODE_HEADER(effect)->flags = NODE_HEADER(effect)->flags | 0x8000;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
