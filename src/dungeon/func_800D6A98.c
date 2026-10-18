#include "common.h"
#include "shared/record_ptrs.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8004DC14();                    /* extern */
u32 func_80069E98();                             /* extern */
void draw_filler_first_number(); /* extern */
void pass_global_data_with_fixed_args();                            /* extern */
extern void copy_cached_hud_rectangle_to_fixed_position(void);
typedef struct S_800DC1F8_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    u8 pad_30[0xC];
    void * unk_3C;
    void * unk_40;
} S_800DC1F8_0;   /* arg0 in update_display_transition */

typedef struct S_800DC1F8_1 {
    u8 pad_00[0x4];
    void * unk_04;
    u16 * unk_08;
} S_800DC1F8_1;   /* state in update_display_transition */

typedef struct S_800DC1F8_2 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800DC1F8_2;

typedef struct S_800DC1F8_3 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_800DC1F8_3;

typedef struct S_800DC1F8_4 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800DC1F8_4;

typedef struct S_800DC1F8_5 {
    u8 unk_00;
} S_800DC1F8_5;

typedef struct S_800DC1F8_6 {
    u8 unk_00;
} S_800DC1F8_6;

typedef struct S_800DC1F8_7 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_800DC1F8_7;

typedef struct S_800DC1F8_8 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_800DC1F8_8;

typedef struct S_800DC1F8_9 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
} S_800DC1F8_9;

typedef struct S_800DC1F8_10 {
    u8 pad_00[0x14A8];
    union { s32 i; void * p; } unk_14A8;   /* accessed as both */
} S_800DC1F8_10;   /* page_base in update_display_transition */

typedef struct S_800DC1F8_11 {
    u8 pad_00[0x80];
    s32 unk_80;
    void * unk_84;
    u16 * unk_88;
} S_800DC1F8_11;   /* ((S_800DC1F8_0 *)arg0)->unk_3C in update_display_transition */

typedef struct S_800DC1F8_12 {
    u8 pad_00[0x28];
    u8 unk_28;
} S_800DC1F8_12;   /* ((S_800DC1F8_10 *)page_base)->unk_14A8.i in update_display_transition */

typedef struct S_800DC1F8_13 {
    u8 pad_00[0x29];
    u8 unk_29;
} S_800DC1F8_13;   /* ((S_800DC1F8_10 *)page_base)->unk_14A8.p in update_display_transition */

/* extern */

/* Updates a display transition, synchronizes rotation and shading, and refreshes its counters. */
void update_display_transition(S_800DC1F8_0 *transition, void *anim_data) {
    s32 phase_offset;
    s32 flag_or_delay;
    s32 frames_left;
    s32 stage;
    u16 *angle;
    u16 *angle_step;
    u16 *paired_angle;
    u8 first_counter;
    u8 second_counter;
    u8 shade;
    u8 paired_shade;
    u8 neutral_shade;
    S_800DC1F8_6 *shade_source;
    S_800DC1F8_5 *red_channel;
    S_800DC1F8_4 *green_channel;
    S_800DC1F8_3 *blue_channel;
    S_800DC1F8_2 *layout;
    S_800DC1F8_8 *color_reset;
    S_800DC1F8_9 *paired_color_reset;
    S_800DC1F8_7 *paired_color;
    u8 *page_base;
    S_800DC1F8_1 *state = anim_data;

    if (transition->unk_18 != 0) {
        stage = transition->unk_28;
        switch (stage) {
        case 0:
            if ((((u16) *state->unk_08 >> 0xA) & 3) == 1) {
                SD_Call(0x504);
                flag_or_delay = transition->unk_20;
                stage = transition->unk_28;
                flag_or_delay ^= 1;
                transition->unk_20 = flag_or_delay;
                flag_or_delay = transition->unk_24;
                stage += 1;
                transition->unk_28 = stage;
                flag_or_delay ^= 1;
                transition->unk_24 = flag_or_delay;
            }
        case 1:
            if ((((u16) *state->unk_08 >> 0xA) & 3) == 2) {
                transition->unk_1C = 0x10;
                transition->unk_28 = (s32) (transition->unk_28 + 1);
            }
            break;
        case 2:
            if ((((u16) *state->unk_08 >> 0xA) & 3) == 3) {
                SD_Call(0x504);
                transition->unk_28 = 0;
                transition->unk_24 = (s32) (transition->unk_24 ^ 1);
                transition->unk_20 = (s32) (transition->unk_20 ^ 1);
            }
            break;
        }
        if (transition->unk_20 != 0) {
            if (transition->unk_24 != 0) {
                func_8004E99C(((S_800DC1F8_11 *)(transition->unk_3C))->unk_80);
                copy_cached_hud_rectangle_to_fixed_position();
                layout = transition->unk_40;
                layout->unk_88 = (s16) (((3 - (func_80069E98(transition->unk_2C) >> 1)) * 6) + 0xA4);
                ((S_800DC1F8_11 *)(transition->unk_3C))->unk_80 = func_8004DC14(transition->unk_2C, 6);
                if (((S_800DC1F8_11 *)(transition->unk_3C))->unk_80 == 0) {
                    return;
                }
                transition->unk_20 = 0;
            } else {
                func_8004E99C(((S_800DC1F8_11 *)(transition->unk_3C))->unk_80);
                ((S_800DC1F8_11 *)(transition->unk_3C))->unk_80 = 0;
                transition->unk_10 = 0;
                transition->unk_14 = 0;
                pass_global_data_with_fixed_args();
                transition->unk_20 = 0;
            }
        }
        red_channel = state->unk_04;
        green_channel = red_channel;
        blue_channel = red_channel;
        angle = state->unk_08;
        phase_offset = 0x400 - (((s16) *angle - 0x400) & 0x7FF);
        if (((s16) *angle & 0x7FF) < 0x400) {
            shade = (phase_offset >> 4) - 0x80;
        } else {
            shade = (phase_offset >> 3) - 0x80;
        }
        blue_channel->unk_02 = shade;
        green_channel->unk_01 = shade;
        red_channel->unk_00 = shade;
        shade_source = state->unk_04;
        paired_color = ((S_800DC1F8_11 *)(transition->unk_3C))->unk_84;
        paired_shade = shade_source->unk_00;
        paired_color->unk_02 = paired_shade;
        paired_color->unk_01 = paired_shade;
        paired_color->unk_00 = paired_shade;
        flag_or_delay = transition->unk_1C;
        if (flag_or_delay == 0) {
            angle_step = state->unk_08;
            *angle_step += 0x80;
            paired_angle = ((S_800DC1F8_11 *)(transition->unk_3C))->unk_88;
            *paired_angle += 0x80;
            frames_left = transition->unk_18 - 1;
            transition->unk_18 = frames_left;
            if (frames_left == 0) {
                transition->unk_28 = 0;
                *state->unk_08 = 0;
                *((S_800DC1F8_11 *)(transition->unk_3C))->unk_88 = 0x800;
                neutral_shade = 0x80U;
                color_reset = state->unk_04;
                color_reset->unk_02 = neutral_shade;
                color_reset->unk_01 = neutral_shade;
                color_reset->unk_00 = neutral_shade;
                paired_color_reset = ((S_800DC1F8_11 *)(transition->unk_3C))->unk_84;
                paired_color_reset->unk_02 = neutral_shade;
                paired_color_reset->unk_01 = neutral_shade;
                paired_color_reset->unk_00 = neutral_shade;
            }
        } else {
            transition->unk_1C = (s32) (flag_or_delay - 1);
        }
    }
    if (transition->unk_24 == 0) {
        page_base = (u8 *)0x80080000;
        first_counter = ((S_800DC1F8_12 *)(((S_800DC1F8_10 *)page_base)->unk_14A8.i))->unk_28;
        if (first_counter != transition->unk_10) {
            draw_filler_first_number(first_counter, transition->unk_10, 3, 0x1CA, 0x19C, 1);
        }
        second_counter = ((S_800DC1F8_13 *)(((S_800DC1F8_10 *)page_base)->unk_14A8.p))->unk_29;
        if (second_counter != transition->unk_14) {
            draw_padded_first_number(second_counter, transition->unk_14, 3, 0x1DA, 0x1A4, 1);
        }
    }
}
