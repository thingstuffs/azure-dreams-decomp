#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "slus.h"

typedef struct S_81814A80_0 {
    u16 unk_00;
} S_81814A80_0;   /* state in accumulate_effect_motion; pointer addresses record offset 0x2 */

typedef struct {
    unsigned char pad00[2];
    u16 remaining_ticks;
    unsigned char pad04[20];
    s16 anim_mode;
    s16 anim_period;
    u16 anim_tick;
    unsigned char pad1e[0x3a];
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 accel_x;
    s32 accel_y;
    s32 accel_z;
} State;

typedef struct {
    unsigned char pad00[0x14];
    u16 unk14;
} Flags;

extern s16 particle_effect_active;

/* Accumulate motion, process the update mode, and mark expired or flagged state. */
void accumulate_effect_motion(State *state, s32 *sum, SpriteFrameState *flags) {
    s32 update_count;
    s32 more_updates;
    u16 next_tick;

    state->remaining_ticks = state->remaining_ticks - 1;
    state->velocity_x = state->velocity_x + state->accel_x;
    state->velocity_y = state->velocity_y + state->accel_y;
    state->velocity_z = state->velocity_z + state->accel_z;
    sum[0] = sum[0] + state->velocity_x;
    sum[1] = sum[1] + state->velocity_y;
    particle_effect_active = 1;
    sum[2] = sum[2] + state->velocity_z;

    switch (state->anim_mode) {
    case 0:
        advance_sprite_animation_and_textures(flags);
        break;
    case 1:
        if (state->anim_period > 0) {
            update_count = 0;
            do {
                advance_sprite_animation_and_textures(flags);
                update_count = update_count + 1;
                more_updates = update_count < state->anim_period;
            } while (more_updates);
        }
        break;
    case 2:
        next_tick = state->anim_tick + 1;
        state->anim_tick = next_tick;
        if ((s16) next_tick >= state->anim_period) {
            advance_sprite_animation_and_textures(flags);
            state->anim_tick = 0;
        }
        break;
    default:
        break;
    }

    if ((s16) state->remaining_ticks <= 0) {
        ((S_81814A80_0 *)((u8 *)state - 0x2))->unk_00 = ((S_81814A80_0 *)((u8 *)state - 0x2))->unk_00 | 0x8000;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
    if (flags->flags & 0x8000) {
        ((S_81814A80_0 *)((u8 *)state - 0x2))->unk_00 = ((S_81814A80_0 *)((u8 *)state - 0x2))->unk_00 | 0x8000;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
