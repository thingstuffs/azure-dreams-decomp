#include "shared/object_node.h"
#include "common.h"
#include "dungeon/effect/shade.h"
#include "dungeon/effect/shade/emit_particles_until_expired.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"


/* Advance and damp motion, fade the effect color, and flag expiration. */
void advance_damped_effect_motion(void *effect, ObjectPosition *motion, SpriteFrameState *color) {
    s16 ticks_left;
    FadingMotionParticleBody *effect_state;

    effect_state = effect;
    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    motion->z.v += motion->velocity_z;
    motion->velocity_x /= 2;
    motion->velocity_y /= 2;
    motion->velocity_z /= 2;
    color->color.c.r =
        (s8) ((s32) (effect_state->color.c.r * effect_state->remaining_ticks) / effect_state->initial_ticks);
    color->color.c.g =
        (s8) ((s32) (effect_state->color.c.g * effect_state->remaining_ticks) / effect_state->initial_ticks);
    color->color.c.b =
        (s8) ((s32) (effect_state->color.c.b * effect_state->remaining_ticks) / effect_state->initial_ticks);
    ticks_left = (u16) effect_state->remaining_ticks - 1;
    effect_state->remaining_ticks = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        NODE_HEADER(effect)->flags = (u16) (NODE_HEADER(effect)->flags | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
