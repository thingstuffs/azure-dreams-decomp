#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern int D_800814A8[4];
s32 func_8004DC14();                    /* extern */
u32 func_80069E98();                             /* extern */
M2C_UNK func_800DBD5C(); /* extern */
M2C_UNK func_800DBE98();                            /* extern */
M2C_UNK func_800DBEE8();                            
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
} S_800DC1F8_0;   /* arg0 in func_800DC1F8 */

typedef struct S_800DC1F8_1 {
    u8 pad_00[0x4];
    void * unk_04;
    u16 * unk_08;
} S_800DC1F8_1;   /* state in func_800DC1F8 */

typedef struct S_800DC1F8_2 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800DC1F8_2;   /* temp_s0 in func_800DC1F8 */

typedef struct S_800DC1F8_3 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_800DC1F8_3;   /* temp_a3 in func_800DC1F8 */

typedef struct S_800DC1F8_4 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800DC1F8_4;   /* temp_a2 in func_800DC1F8 */

typedef struct S_800DC1F8_5 {
    u8 unk_00;
} S_800DC1F8_5;   /* temp_a1 in func_800DC1F8 */

typedef struct S_800DC1F8_6 {
    u8 unk_00;
} S_800DC1F8_6;   /* temp_a0_2 in func_800DC1F8 */

typedef struct S_800DC1F8_7 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_800DC1F8_7;   /* temp_v1_2 in func_800DC1F8 */

typedef struct S_800DC1F8_8 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_800DC1F8_8;   /* temp_v0_6 in func_800DC1F8 */

typedef struct S_800DC1F8_9 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
} S_800DC1F8_9;   /* temp_v0_7 in func_800DC1F8 */

typedef struct S_800DC1F8_10 {
    u8 pad_00[0x14A8];
    union { s32 i; void * p; } unk_14A8;   /* accessed as both */
} S_800DC1F8_10;   /* page_base in func_800DC1F8 */

typedef struct S_800DC1F8_11 {
    u8 pad_00[0x80];
    s32 unk_80;
    void * unk_84;
    u16 * unk_88;
} S_800DC1F8_11;   /* ((S_800DC1F8_0 *)arg0)->unk_3C in func_800DC1F8 */

typedef struct S_800DC1F8_12 {
    u8 pad_00[0x28];
    u8 unk_28;
} S_800DC1F8_12;   /* ((S_800DC1F8_10 *)page_base)->unk_14A8.i in func_800DC1F8 */

typedef struct S_800DC1F8_13 {
    u8 pad_00[0x29];
    u8 unk_29;
} S_800DC1F8_13;   /* ((S_800DC1F8_10 *)page_base)->unk_14A8.p in func_800DC1F8 */

/* extern */

/* Updates a display transition, synchronizes rotation and shading, and refreshes its counters. */
void func_800DC1F8(S_800DC1F8_0 *transition, void *anim_data) {
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
        if (stage == 1) {
            goto wait_half_turn;
        }
        if (stage < 2) {
            if (stage == 0) {
                goto wait_first_quarter;
            }
            goto update_display;
        }
        if (stage == 2) {
            goto wait_third_quarter;
        }
        goto update_display;

wait_first_quarter:
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
wait_half_turn:
        if ((((u16) *state->unk_08 >> 0xA) & 3) == 2) {
            transition->unk_1C = 0x10;
            transition->unk_28 = (s32) (transition->unk_28 + 1);
        }
        goto update_display;

wait_third_quarter:
        if ((((u16) *state->unk_08 >> 0xA) & 3) == 3) {
            SD_Call(0x504);
            transition->unk_28 = 0;
            transition->unk_24 = (s32) (transition->unk_24 ^ 1);
            transition->unk_20 = (s32) (transition->unk_20 ^ 1);
        }
update_display:
        if (transition->unk_20 != 0) {
            if (transition->unk_24 != 0) {
                func_8004E99C(((S_800DC1F8_11 *)(transition->unk_3C))->unk_80);
                func_800DBEE8();
                layout = transition->unk_40;
                layout->unk_88 = (s16) (((3 - (func_80069E98(transition->unk_2C) >> 1)) * 6) + 0xA4);
                ((S_800DC1F8_11 *)(transition->unk_3C))->unk_80 = func_8004DC14(transition->unk_2C, 6);
                if (((S_800DC1F8_11 *)(transition->unk_3C))->unk_80 != 0) {
                    transition->unk_20 = 0;
                    goto animate_display;
                }
            } else {
                func_8004E99C(((S_800DC1F8_11 *)(transition->unk_3C))->unk_80);
                ((S_800DC1F8_11 *)(transition->unk_3C))->unk_80 = 0;
                transition->unk_10 = 0;
                transition->unk_14 = 0;
                func_800DBE98();
                transition->unk_20 = 0;
                goto animate_display;
            }
        } else {
animate_display:
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
                    goto update_counters;
                }
                goto update_counters;
            }
            transition->unk_1C = (s32) (flag_or_delay - 1);
            goto update_counters;
        }
    } else {
update_counters:
        if (transition->unk_24 == 0) {
            page_base = (u8 *)0x80080000;
            first_counter = ((S_800DC1F8_12 *)(((S_800DC1F8_10 *)page_base)->unk_14A8.i))->unk_28;
            if (first_counter != transition->unk_10) {
                func_800DBD5C(first_counter, transition->unk_10, 3, 0x1CA, 0x19C, 1);
            }
            second_counter = ((S_800DC1F8_13 *)(((S_800DC1F8_10 *)page_base)->unk_14A8.p))->unk_29;
            if (second_counter != transition->unk_14) {
                func_800DBC20(second_counter, transition->unk_14, 3, 0x1DA, 0x1A4, 1);
            }
        }
    }
}
