#include "common.h"
#include "dungeon/effect/shade.h"
#include "dungeon/effect/shade/emit_particles_until_expired.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"


typedef struct S_800D4CB0_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800D4CB0_1;   /* arg2 in advance_damped_effect_motion */

typedef struct S_800D4CB0_2_pre {
    u16 unk_00;
} S_800D4CB0_2_pre;   /* the 0x2 bytes before arg0 in advance_damped_effect_motion, addressed as arg0[-1] */

/* Advance and damp motion, fade the effect color, and flag expiration. */
void advance_damped_effect_motion(void *effect, ObjectPosition *motion, void *color_arg) {
    S_800D4CB0_1 *color = color_arg;
    s16 ticks_left;
    EmitParticlesUntilExpiredBody *effect_state;

    effect_state = effect;
    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    motion->z.v += motion->velocity_z;
    motion->velocity_x /= 2;
    motion->velocity_y /= 2;
    motion->velocity_z /= 2;
    color->unk_0C =
        (s8) ((s32) (effect_state->red * effect_state->remaining_ticks) / effect_state->initial_ticks);
    color->unk_0D =
        (s8) ((s32) (effect_state->green * effect_state->remaining_ticks) / effect_state->initial_ticks);
    color->unk_0E =
        (s8) ((s32) (effect_state->blue * effect_state->remaining_ticks) / effect_state->initial_ticks);
    ticks_left = (u16) effect_state->remaining_ticks - 1;
    effect_state->remaining_ticks = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_800D4CB0_2_pre *)effect)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
