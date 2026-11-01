#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "sdk/libgte.h"
#include "dungeon/effect/sprite.h"

typedef struct S_800F62BC_0_pre {
    u16 unk_00;
} S_800F62BC_0_pre;   /* the 0x2 bytes before state in update_pulsing_actor_color, addressed as state[-1] */

typedef struct S_800F62BC_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_800F62BC_1;   /* actor in update_pulsing_actor_color */


extern u8 D_80173AF8;

/* Pulses the actor color, then fades it out and marks completion. */
void update_pulsing_actor_color(FixedTileEffectIfAvailableBody *state_data, s32 unused, void *actor_data) {
    s16 fade_ticks;
    s16 pulse;
    s16 pulse_color;
    u8 fade_color;
    FixedTileEffectIfAvailableBody *state = state_data;
    S_800F62BC_1 *actor = actor_data;

    if (state->phase.s == 0) {
        pulse = rsin(state->angle << 7) >> 6;
        pulse_color = pulse + 0x80;
        pulse = (s32) (pulse << 0x10) >> 0x11;
        pulse_color += pulse;
        actor->unk_0D = pulse_color;
        actor->unk_0E = pulse_color;
        actor->unk_0C = pulse_color;
        if (D_80173AF8 != 0) {
            state->fade_ticks = 0x20;
            state->phase.u = (u16) (state->phase.u + 1);
        }
    } else {
        fade_color = actor->unk_0C;
        fade_color -= (s32) fade_color / state->fade_ticks;
        actor->unk_0C = fade_color;
        actor->unk_0D = fade_color;
        actor->unk_0E = fade_color;
        fade_ticks = (u16) state->fade_ticks - 1;
        state->fade_ticks = fade_ticks;
        if ((fade_ticks << 0x10) <= 0) {
            (*(u16 *)((u8 *)state + -2)) = (u16) (((S_800F62BC_0_pre *)state)[-1].unk_00 | NODE_REMOVE);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
    actor->unk_1A = (u16) (actor->unk_1A + 0x40);
    state->angle = (s16) ((u16) state->angle + 1);
}
