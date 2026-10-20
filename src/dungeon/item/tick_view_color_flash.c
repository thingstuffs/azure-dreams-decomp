#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct S_800C4C00_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x1];
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
} S_800C4C00_0;   /* arg0 in tick_view_color_flash */


/* Fades the color toward the target, then back to neutral, and marks completion. */
void tick_view_color_flash(void *fade)
{
    GameView *color_state;
    u16 frames_left;

    color_state = &g_game_work.view;
    if (((S_800C4C00_0 *)fade)->unk_04.s == 0) {
        color_state->tint.parts.tint_r +=
            (((S_800C4C00_0 *)fade)->unk_00 - color_state->tint.parts.tint_r) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        color_state->tint.parts.tint_g +=
            (((S_800C4C00_0 *)fade)->unk_01 - color_state->tint.parts.tint_g) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        color_state->tint.parts.tint_b +=
            (((S_800C4C00_0 *)fade)->unk_02 - color_state->tint.parts.tint_b) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        frames_left = ((S_800C4C00_0 *)fade)->unk_06.u - 1;
        ((S_800C4C00_0 *)fade)->unk_06.u = frames_left;
        if ((s16)frames_left <= 0) {
            ((S_800C4C00_0 *)fade)->unk_06.s = 0x10;
            ((S_800C4C00_0 *)fade)->unk_04.u++;
        }
    } else {
        color_state->tint.parts.tint_r +=
            (0x80 - color_state->tint.parts.tint_r) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        color_state->tint.parts.tint_g +=
            (0x80 - color_state->tint.parts.tint_g) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        color_state->tint.parts.tint_b +=
            (0x80 - color_state->tint.parts.tint_b) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        frames_left = ((S_800C4C00_0 *)fade)->unk_06.u - 1;
        ((S_800C4C00_0 *)fade)->unk_06.u = frames_left;
        if ((s16)frames_left <= 0) {
            color_state->tint.parts.tint_r = 0x80;
            color_state->tint.parts.tint_g = 0x80;
            color_state->tint.parts.tint_b = 0x80;
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            (*(u16 *)((u8 *)fade + -2)) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
    }
}
