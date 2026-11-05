#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "dungeon/effect/particle.h"
#include "shared/sprite_frame_state.h"




/* Pulse the color through three phases and mark the effect finished when its timer expires. */
void update_color_cycling_pulse(ColorCyclingPulseBody *state, void *unused, SpriteFrameState *color) {
    s16 phase;
    s16 remaining;
    s32 red;
    s32 green;
    s32 blue;
    u16 flags;
    u16 next_phase;

    flags = color->flags;
    color->flags = (u16) (flags & 0xFF7F);
    state->ticks_remaining--;
    state->phase_index++;
    next_phase = state->phase_index;
    if ((s16) next_phase == 3) {
        state->phase_index = 0U;
    }
    blue = 0x30;
    green = blue;
    phase = (s16) state->phase_index;
    red = 0x30;
    if (phase == 0) {
        red = 0x54;
    }
    if (phase == 1) {
        green = 0x54;
    }
    if (phase == 2) {
        blue = 0x54;
    }
    remaining = (s16) state->ticks_remaining;
    if (remaining < 0x14) {
        color->color.c.r = (s8) ((red * remaining) / 20);
        color->color.c.g = (s8) ((green * (s16) state->ticks_remaining) / 20);
        color->color.c.b = (s8) ((blue * (s16) state->ticks_remaining) / 20);
    } else {
        color->color.c.r = (s8) ((red * (0x1E - remaining)) / 10);
        color->color.c.g = (s8) ((green * (0x1E - (s16) state->ticks_remaining)) / 10);
        color->color.c.b = (s8) ((blue * (0x1E - (s16) state->ticks_remaining)) / 10);
    }
    if ((s16) state->ticks_remaining <= 0) {
        (*(u16 *)((u8 *)state + -2)) = (u16) (NODE_HEADER(state)->flags | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
