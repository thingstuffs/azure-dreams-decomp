#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "sdk/libgte.h"
#include "dungeon/effect/sprite.h"

typedef struct S_800F62BC_0_pre {
    u16 unk_00;
} S_800F62BC_0_pre;   /* the 0x2 bytes before state in update_pulsing_actor_color, addressed as state[-1] */



extern u8 D_80173AF8;

/* Pulses the actor color, then fades it out and marks completion. */
void update_pulsing_actor_color(FixedTileEffectIfAvailableBody *state_data, ObjectPosition *unused, SpriteFrameState *actor_data) {
    s16 fade_ticks;
    s16 pulse;
    s16 pulse_color;
    u8 fade_color;
    FixedTileEffectIfAvailableBody *state = state_data;
    SpriteFrameState *actor = actor_data;

    if (state->phase.s == 0) {
        pulse = rsin(state->angle << 7) >> 6;
        pulse_color = pulse + 0x80;
        pulse = (s32) (pulse << 0x10) >> 0x11;
        pulse_color += pulse;
        actor->color.c.g = pulse_color;
        actor->color.c.b = pulse_color;
        actor->color.c.r = pulse_color;
        if (D_80173AF8 != 0) {
            state->fade_ticks = 0x20;
            state->phase.u = (u16) (state->phase.u + 1);
        }
    } else {
        fade_color = actor->color.c.r;
        fade_color -= (s32) fade_color / state->fade_ticks;
        actor->color.c.r = fade_color;
        actor->color.c.g = fade_color;
        actor->color.c.b = fade_color;
        fade_ticks = (u16) state->fade_ticks - 1;
        state->fade_ticks = fade_ticks;
        if ((fade_ticks << 0x10) <= 0) {
            (*(u16 *)((u8 *)state + -2)) = (u16) (((S_800F62BC_0_pre *)state)[-1].unk_00 | NODE_REMOVE);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
    actor->angle_z = (u16) (actor->angle_z + 0x40);
    state->angle = (s16) ((u16) state->angle + 1);
}
