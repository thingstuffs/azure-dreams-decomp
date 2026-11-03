#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "dungeon/effect/particle.h"

typedef struct S_801671AC_0 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_801671AC_0;   /* arg2 in update_color_cycling_pulse */




/* Pulse the color through three phases and mark the effect finished when its timer expires. */
void update_color_cycling_pulse(ColorCyclingPulseBody *state, void *unused, void *color) {
    s16 phase;
    s16 remaining;
    s32 red;
    s32 green;
    s32 blue;
    u16 flags;
    u16 next_phase;

    flags = ((S_801671AC_0 *)color)->unk_14;
    ((S_801671AC_0 *)color)->unk_14 = (u16) (flags & 0xFF7F);
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
        ((S_801671AC_0 *)color)->unk_0C = (s8) ((red * remaining) / 20);
        ((S_801671AC_0 *)color)->unk_0D = (s8) ((green * (s16) state->ticks_remaining) / 20);
        ((S_801671AC_0 *)color)->unk_0E = (s8) ((blue * (s16) state->ticks_remaining) / 20);
    } else {
        ((S_801671AC_0 *)color)->unk_0C = (s8) ((red * (0x1E - remaining)) / 10);
        ((S_801671AC_0 *)color)->unk_0D = (s8) ((green * (0x1E - (s16) state->ticks_remaining)) / 10);
        ((S_801671AC_0 *)color)->unk_0E = (s8) ((blue * (0x1E - (s16) state->ticks_remaining)) / 10);
    }
    if ((s16) state->ticks_remaining <= 0) {
        (*(u16 *)((u8 *)state + -2)) = (u16) (NODE_HEADER(state)->flags | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
