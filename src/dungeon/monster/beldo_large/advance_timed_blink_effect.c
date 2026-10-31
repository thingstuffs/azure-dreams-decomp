/* cfail-repair: recovered external dispatch table */
#include "common.h"
#include "shared/object_flags.h"



extern void initialize_timed_motion_step(s32, s32);
extern void play_sound_if_enabled(u32);
extern s16 encounter_blink_update_flag[5];


typedef struct S_80170534_0_pre {
    u16 unk_00;
} S_80170534_0_pre;   /* the 0x2 bytes before state in advance_timed_blink_effect, addressed as state[-1] */

typedef struct S_80170534_0 {
    u8 pad_00[0x12];
    union { s16 s; u16 u; } unk_12;   /* accessed as both */
    u8 pad_14[0x4];
    u16 unk_18;
} S_80170534_0;   /* state in advance_timed_blink_effect */

typedef struct S_80170534_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    union { s8 s; u8 u; } unk_0D;   /* accessed as both */
    union { s8 s; u8 u; } unk_0E;   /* accessed as both */
} S_80170534_1;   /* input in advance_timed_blink_effect */

/* Advances a timed blinking effect, triggers sounds, and sets completion flags. */
void advance_timed_blink_effect(void *state_data_arg, void *unused, void *color_data_arg) {
    S_80170534_1 *color_data = color_data_arg;
    S_80170534_0 *state_data = state_data_arg;
    s32 phase;
    s32 bright_shade;
    u16 dim_shade;
    u16 next_phase;
    u16 frame;
    u16 blink_frame;

    phase = state_data->unk_12.s;
    switch ((u32) phase) {
    case 1:
        frame = state_data->unk_18 + 1;
        state_data->unk_18 = frame;
        if (!(frame & 3)) {
            initialize_timed_motion_step(6, 0xC);
            play_sound_if_enabled(0x818);
        }
        if (!(state_data->unk_18 & 7)) {
            bright_shade = 0xFF;
            if (color_data->unk_0C != bright_shade) {
                color_data->unk_0E.s = bright_shade;
                color_data->unk_0D.s = bright_shade;
                color_data->unk_0C = bright_shade;
            } else {
                dim_shade = 0x80;
                color_data->unk_0E.u = dim_shade;
                color_data->unk_0D.u = dim_shade;
                color_data->unk_0C = dim_shade;
            }
        }
        if ((s16) state_data->unk_18 == 0x28) {
            {
                u8 *flag_page = (u8 *) 0x80170000;
                *(u16 *)((u8 *)&encounter_blink_update_flag) = 1;
            }
        }
        if ((s16) state_data->unk_18 >= 0x28) {
            next_phase = state_data->unk_12.u + 1;
            state_data->unk_12.u = next_phase;
            return;
        }
        break;
    case 2:
        blink_frame = state_data->unk_18 + 1;
        state_data->unk_18 = blink_frame;
        if (!(blink_frame & 3)) {
            play_sound_if_enabled(0x818);
        }
        if (!(state_data->unk_18 & 7)) {
            bright_shade = 0xFF;
            if (color_data->unk_0C != bright_shade) {
                color_data->unk_0E.s = bright_shade;
                color_data->unk_0D.s = bright_shade;
                color_data->unk_0C = bright_shade;
            } else {
                dim_shade = 0x80;
                color_data->unk_0E.u = dim_shade;
                color_data->unk_0D.u = dim_shade;
                color_data->unk_0C = dim_shade;
            }
        }
        if ((s16) state_data->unk_18 >= 0x3C) {
            state_data->unk_18 = 0U;
            state_data->unk_12.s = (s16) ((u16) state_data->unk_12.s + 1);
            color_data->unk_0E.u = 0x80;
            color_data->unk_0D.u = 0x80;
            color_data->unk_0C = 0x80;
            return;
        }
        break;
    case 4:
        ((S_80170534_0_pre *)state_data)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    case 0:
    case 3:
    default:
        break;
    }
}
