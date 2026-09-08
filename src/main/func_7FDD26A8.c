#include "common.h"
#include "m2c_compat.h"

typedef struct S_80089608_0_pre {
    u16 unk_00;
} S_80089608_0_pre;   /* the 0x2 bytes before arg0 in func_80089608, addressed as arg0[-1] */

typedef struct S_80089608_0 {
    void * unk_00;
    s32 unk_04;
    s16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x2];
    union { u16 s; s16 u; } unk_0E;   /* accessed as both */
} S_80089608_0;   /* arg0 in func_80089608 */

typedef struct S_80089608_1 {
    u8 pad_00[0x20];
    s16 unk_20;
    u8 pad_22[0x4];
    u16 unk_26;
} S_80089608_1;   /* temp_t1 in func_80089608 */

typedef struct S_80089608_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80089608_2;   /* temp_v0 in func_80089608 */

typedef struct S_80089608_3 {
    u8 pad_00[0x28];
    s16 unk_28;
} S_80089608_3;   /* var_s4 in func_80089608 */

typedef struct S_80089608_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80089608_4;   /* temp_s1 in func_80089608 */

typedef struct S_80089608_5 {
    s32 unk_00;
    u8 pad_04[0x3C];
    s32 unk_40;
} S_80089608_5;   /* var_s5 in func_80089608 */

typedef struct S_80089608_6 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80089608_6;   /* var_sub in func_80089608 */

typedef struct S_80089608_7 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_80089608_7;   /* ((S_80089608_2 *)temp_v0)->unk_08 in func_80089608 */


void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_80044BB0;
extern s32 D_800814A0;
extern M2C_UNK D_80088790;
extern M2C_UNK D_800887B8;
extern M2C_UNK D_800887CC;
extern M2C_UNK D_80089A14;

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
} __attribute__((packed)) Packed12;
typedef struct {
    s32 w0;
    s32 w1;
} __attribute__((packed)) Packed8;
typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
} __attribute__((packed)) Packed20;
typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} Words4;
typedef struct {
    s32 w0;
    s32 w1;
} Words2;

/* Updates effect brightness and rotation and spawns ten visual elements. */
void func_80089608(void *effect) {
    unsigned char effect_tables[104];
    Words4 *style_src;
    Words4 *mask_src;
    Words4 *copy_dst;
    s8 *radius_cursor;
    s8 *style_cursor;
    s16 phase_frame;
    s32 phase;
    s32 color_step_or_index;
    s32 brighten_rgb;
    s32 fade_rgb;
    s32 axis_offset;
    s32 x_product;
    s32 y_product;
    void *element;
    void *element_state;
    void *sprite;
    void *owner;
    void *callback;

    copy_dst = (Words4 *)&effect_tables[0];
    style_src = (Words4 *)&D_80088790;
    owner = ((S_80089608_0 *)effect)->unk_00;
    do {
        *copy_dst = *style_src;
        style_src++;
        copy_dst++;
    } while (style_src != ((Words4 *)&D_80088790 + 2));
    *(Words2 *)copy_dst = *(Words2 *)style_src;
    *(Packed20 *)(effect_tables + 40) = *(Packed20 *)&D_800887B8;
    copy_dst = (Words4 *)&effect_tables[64];
    mask_src = &D_800887CC;
    do {
        *copy_dst = *mask_src;
        mask_src++;
        copy_dst++;
    } while (mask_src != ((Words4 *)&D_800887CC + 2));
    *(Words2 *)copy_dst = *(Words2 *)mask_src;
    if (((S_80089608_1 *)owner)->unk_26 & 1) {
        ((S_80089608_0 *)effect)->unk_08 = 0xFF;
    }
    if (((S_80089608_1 *)owner)->unk_20 >= 2) {
        ((S_80089608_0 *)effect)->unk_08 = 0xFF;
        goto epilogue;
    }
    phase = ((S_80089608_0 *)effect)->unk_08;
    switch (phase) {
    case 1:
        goto angle_mode;
    case 0:
        ((S_80089608_0 *)effect)->unk_04 = (s32) (((S_80089608_0 *)effect)->unk_04 + 0x20202);
        if (((S_80089608_1 *)owner)->unk_20 == 1) {
            ((S_80089608_0 *)effect)->unk_08++;
            goto set_spawn_count;
        }
        color_step_or_index = 9;
        goto spawn_setup;
    case 0xFF:
        goto error_mode;
    default:
        color_step_or_index = 9;
        goto spawn_setup;
    }

angle_mode:
    phase_frame = ((S_80089608_0 *)effect)->unk_0A + 1;
    ((S_80089608_0 *)effect)->unk_0A = (u16) phase_frame;
    if (phase_frame < 0x80) {
        if (!(phase_frame & 3)) {
            ((S_80089608_0 *)effect)->unk_04 += 0x10101;
        }
        goto pre_spawn_angle;
    }
    if (phase_frame < 0x91) {
        brighten_rgb = ((S_80089608_0 *)effect)->unk_04;
        color_step_or_index = ((s32) (~brighten_rgb & 0xFF) >> 1);
        color_step_or_index = ((color_step_or_index << 8) + (color_step_or_index << 16)) + color_step_or_index;
        ((S_80089608_0 *)effect)->unk_04 = brighten_rgb + color_step_or_index;
        goto pre_spawn_angle;
    }
    if (phase_frame < 0xA0) {
        fade_rgb = ((S_80089608_0 *)effect)->unk_04;
        color_step_or_index = ((s32) (fade_rgb & 0xFF) >> 3);
        color_step_or_index = ((color_step_or_index << 8) + (color_step_or_index << 16)) + color_step_or_index;
        ((S_80089608_0 *)effect)->unk_04 = fade_rgb - color_step_or_index;
        goto pre_spawn_angle;
    }
    ((S_80089608_0 *)effect)->unk_08 = 0xFF;
    ((S_80089608_0 *)effect)->unk_04 = 0;
pre_spawn_angle:
    ((S_80089608_0 *)effect)->unk_0E.s -= 12;
    goto set_spawn_count;

error_mode:
    (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_80089608_0_pre *)effect)[-1].unk_00 | 0x8000);
    D_800814A0 |= 0x8000;
    goto epilogue;
set_spawn_count:
    color_step_or_index = 9;
spawn_setup:
    callback = &D_80089A14;
    style_cursor = (M2C_UNK *)&effect_tables[36];
    radius_cursor = (M2C_UNK *)&effect_tables[18];
    do {
        element = func_8003FC64(0x111);
        if (element != NULL) {
            sprite = ((S_80089608_2 *)element)->unk_0C;
            ((S_80089608_2 *)element)->unk_10 = callback;
            func_8004491C(element, &D_80044BB0);
            x_product = func_80064584(((S_80089608_0 *)effect)->unk_0E.u) * ((S_80089608_3 *)radius_cursor)->unk_28;
            axis_offset = x_product >> 0xC;
            ((S_80089608_7 *)(((S_80089608_2 *)element)->unk_08))->unk_02 = (s16) ((axis_offset - (x_product >> 0xD)) + 0xA0);
            element_state = (void *)((s8 *)element + 0x20);
            y_product = func_800644B8(((S_80089608_0 *)effect)->unk_0E.u) * ((S_80089608_3 *)radius_cursor)->unk_28;
            axis_offset = y_product >> 0xC;
            ((S_80089608_7 *)(((S_80089608_2 *)element)->unk_08))->unk_06 = (s16) ((axis_offset + (y_product >> 0xE)) + 0x78);
            ((S_80089608_4 *)sprite)->unk_1E = 0x1000;
            ((S_80089608_4 *)sprite)->unk_1C = 0x1000;
            if (color_step_or_index == 0) {
                ((S_80089608_4 *)sprite)->unk_1A = ((S_80089608_0 *)effect)->unk_0E.u;
                goto configure_spawn;
            }
            if (color_step_or_index == 1) {
                ((S_80089608_4 *)sprite)->unk_1A = (s16) (0 - (u16) ((S_80089608_0 *)effect)->unk_0E.u);
            }
configure_spawn:
            ((S_80089608_4 *)sprite)->unk_10 = 0x60;
            ((S_80089608_4 *)sprite)->unk_14 = (u16) (((S_80089608_4 *)sprite)->unk_14 | 0xC);
            ((S_80089608_4 *)sprite)->unk_08 = (s32) ((S_80089608_5 *)style_cursor)->unk_00;
            ((S_80089608_4 *)sprite)->unk_04 = 0;
            ((S_80089608_4 *)sprite)->unk_05 = 0;
            ((S_80089608_4 *)sprite)->unk_0C = (s32) (((S_80089608_0 *)effect)->unk_04 & ((S_80089608_5 *)style_cursor)->unk_40);
            ((S_80089608_6 *)element_state)->unk_0C = color_step_or_index;
            goto next_element;
        }
next_element:
        style_cursor -= 4;
        color_step_or_index -= 1;
        radius_cursor -= 2;
    } while (color_step_or_index >= 0);
    return;
epilogue:
    return;
}
