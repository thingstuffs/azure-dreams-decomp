#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"


extern s32 get_unused_text_buffer(s32, u8 *, void *);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 write_text_byte_and_advance(s8 value, s8 *dest);
extern void display_text_with_fullwidth_adjustment(s8 *text);

extern u8 D_8016A808[];


typedef struct S_8016A9FC_0 {
    u8 pad_00[0x12];
    union { s16 s; u16 u; } unk_12;   /* accessed as both */
    u8 pad_14[0x6];
    u16 unk_1A;
} S_8016A9FC_0;   /* arg0 in animate_timed_fade_effect */

typedef struct S_8016A9FC_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8016A9FC_1;   /* counter_base in animate_timed_fade_effect */

/* Handles a timed fade-out and fade-in, then marks the effect complete. */
void animate_timed_fade_effect(void *effect) {
    s32 state;
    s32 state_arg;
    u16 frames;
    u8 fade_green;
    u8 fade_blue;
    GameWork *fade_colors;
    s32 result;
    s32 first_result;
    u8 cur;

    state = ((S_8016A9FC_0 *)effect)->unk_12.s;
    state_arg = ((S_8016A9FC_0 *)effect)->unk_12.u;
    fade_colors = &g_game_work;

    switch (state) {
    case 0:
        if (fade_colors->view.tint.parts.tint_r >= 0x65) {
            fade_colors->view.tint.parts.tint_r -= 4;
            fade_green = fade_colors->view.tint.parts.tint_g - 4;
            fade_blue = fade_colors->view.tint.parts.tint_b - 4;
            fade_colors->view.tint.parts.tint_g = fade_green;
            fade_colors->view.tint.parts.tint_b = fade_blue;
            return;
        }
        ((S_8016A9FC_0 *)effect)->unk_12.u = state_arg + 1;
        ((S_8016A9FC_0 *)effect)->unk_1A = 0;
        result = get_unused_text_buffer(state_arg, fade_colors, effect);
        first_result = result;
        result = write_text_byte_and_advance(0xA, result);
        result = write_text_byte_and_advance(0xA, result);
        result = expand_text_control_codes(D_8016A808, result);
        result = write_text_byte_and_advance(0xA, result);
        result = write_text_byte_and_advance(0xA, result);
        result = write_text_byte_and_advance(0xA, result);
        result = write_text_byte_and_advance(1, result);
        func_80099290(result);
        display_text_with_fullwidth_adjustment(first_result);
        return;

    case 1:
        frames = ((S_8016A9FC_0 *)effect)->unk_1A;
        ((S_8016A9FC_0 *)effect)->unk_1A = frames + 1;
        if ((s16)frames < 0x3C) {
            return;
        }
        ((S_8016A9FC_0 *)effect)->unk_1A = 0;
        ((S_8016A9FC_0 *)effect)->unk_12.u++;
        return;

    case 2:
        cur = fade_colors->view.tint.parts.tint_r;
        if (cur < 0x80) {
            fade_colors->view.tint.parts.tint_r = cur + 4;
            fade_green = fade_colors->view.tint.parts.tint_g + 4;
            fade_blue = fade_colors->view.tint.parts.tint_b + 4;
            fade_colors->view.tint.parts.tint_g = fade_green;
            fade_colors->view.tint.parts.tint_b = fade_blue;
            return;
        }
        fade_colors->view.tint.parts.tint_b = 0x80;
        fade_colors->view.tint.parts.tint_g = 0x80;
        fade_colors->view.tint.parts.tint_r = 0x80;
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        (*(u16 *)((u8 *)effect + (-2))) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;

    default:
        return;
    }
}
