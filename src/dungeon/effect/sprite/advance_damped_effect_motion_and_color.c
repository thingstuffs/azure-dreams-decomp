#include "shared/object_node_flags.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "dungeon/effect/sprite.h"

/* Three-word object task callback installed in the node's +0x10 slot.
 * The dispatcher supplies payload, position/motion and render data. */
typedef struct SpriteDecayState {
    u8 source_red;
    u8 source_green;
    u8 source_blue;
    u8 pad03;
    union { u32 word; u8 channel[4]; } color;
    u32 displayed_color;
    u8 pad0C[0x26];
    s16 life;
    s16 initial_life;
} SpriteDecayState;

typedef struct SpriteDecayMotion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} SpriteDecayMotion;

/* Moves a particle while halving its velocity and fading its saved color over the remaining lifetime. */
void advance_damped_effect_motion_and_color(SpriteDecayState *state, SpriteDecayMotion *motion, void *unused_render)
{
    u16 remaining;

    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;
    motion->dx /= 2;
    motion->dy /= 2;
    motion->dz /= 2;
    state->color.channel[0] = state->source_red * state->life / state->initial_life;
    state->color.channel[1] = state->source_green * state->life / state->initial_life;
    state->color.channel[2] = state->source_blue * state->life / state->initial_life;
    remaining = (u16)state->life - 1;
    state->life = remaining;
    state->displayed_color = state->color.word;
    if ((s16)remaining <= 0) {
        ((ObjectNodeHeader *)((u8 *)state - 0x20))->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
