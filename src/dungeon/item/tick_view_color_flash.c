#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "dungeon/item.h"

/* Fades the color toward the target, then back to neutral, and marks completion. */
void tick_view_color_flash(void *fade)
{
    GameView *color_state;
    ViewColorFlashState *state;
    u16 frames_left;

    color_state = &g_game_work.view;
    state = fade;
    if (state->phase.s == 0) {
        color_state->tint.parts.tint_r +=
            (state->target_red - color_state->tint.parts.tint_r) /
            state->frames_remaining.s;
        color_state->tint.parts.tint_g +=
            (state->target_green - color_state->tint.parts.tint_g) /
            state->frames_remaining.s;
        color_state->tint.parts.tint_b +=
            (state->target_blue - color_state->tint.parts.tint_b) /
            state->frames_remaining.s;
        frames_left = state->frames_remaining.u - 1;
        state->frames_remaining.u = frames_left;
        if ((s16)frames_left <= 0) {
            state->frames_remaining.s = 0x10;
            state->phase.u++;
        }
    } else {
        color_state->tint.parts.tint_r +=
            (0x80 - color_state->tint.parts.tint_r) /
            state->frames_remaining.s;
        color_state->tint.parts.tint_g +=
            (0x80 - color_state->tint.parts.tint_g) /
            state->frames_remaining.s;
        color_state->tint.parts.tint_b +=
            (0x80 - color_state->tint.parts.tint_b) /
            state->frames_remaining.s;
        frames_left = state->frames_remaining.u - 1;
        state->frames_remaining.u = frames_left;
        if ((s16)frames_left <= 0) {
            color_state->tint.parts.tint_r = 0x80;
            color_state->tint.parts.tint_g = 0x80;
            color_state->tint.parts.tint_b = 0x80;
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            (*(u16 *)((u8 *)fade + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
