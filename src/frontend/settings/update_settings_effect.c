#include "modules/main_title_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "engine/node.h"
#include "frontend/settings.h"
#include "main/data.h"
#include "sdk/libgte.h"

typedef struct S_80089608_0_pre {
    u16 unk_00;
} S_80089608_0_pre;   /* the 0x2 bytes before arg0 in update_settings_effect, addressed as arg0[-1] */

typedef struct S_80089608_0 {
    void * unk_00;
    s32 unk_04;
    s16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x2];
    union { u16 s; s16 u; } unk_0E;   /* accessed as both */
} S_80089608_0;   /* arg0 in update_settings_effect */

typedef struct S_80089608_1 {
    u8 pad_00[0x20];
    s16 unk_20;
    u8 pad_22[0x4];
    u16 unk_26;
} S_80089608_1;

typedef struct S_80089608_3 {
    u8 pad_00[0x28];
    s16 unk_28;
} S_80089608_3;

typedef struct S_80089608_5 {
    s32 unk_00;
    u8 pad_04[0x3C];
    s32 unk_40;
} S_80089608_5;

typedef struct S_80089608_6 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80089608_6;

typedef struct S_80089608_7 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_80089608_7;

extern s32 linked_sprite_renderer_address[3];

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
void update_settings_effect(void *effect) {
    unsigned char effect_tables[104];
    Words4 *style_src;
    Words4 *mask_src;
    Words4 *copy_dst;
    s16 phase_frame;
    s32 phase;
    s32 color_step_or_index;
    s32 brighten_rgb;
    s32 fade_rgb;
    s32 axis_offset;
    s32 x_product;
    s32 y_product;
    ObjectNodeHeader *element;
    void *element_state;
    SpriteFrameState *sprite;
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
        return;
    }
    phase = ((S_80089608_0 *)effect)->unk_08;
    switch (phase) {
    case 0:
        ((S_80089608_0 *)effect)->unk_04 = (s32) (((S_80089608_0 *)effect)->unk_04 + 0x20202);
        if (((S_80089608_1 *)owner)->unk_20 == 1) {
            ((S_80089608_0 *)effect)->unk_08++;
        }
        break;
    case 1:
        phase_frame = ((S_80089608_0 *)effect)->unk_0A + 1;
        ((S_80089608_0 *)effect)->unk_0A = (u16) phase_frame;
        if (phase_frame < 0x80) {
            if (!(phase_frame & 3)) {
                ((S_80089608_0 *)effect)->unk_04 += 0x10101;
            }
        } else if (phase_frame < 0x91) {
            brighten_rgb = ((S_80089608_0 *)effect)->unk_04;
            color_step_or_index = ((s32) (~brighten_rgb & 0xFF) >> 1);
            color_step_or_index = ((color_step_or_index << 8) + (color_step_or_index << 16)) + color_step_or_index;
            ((S_80089608_0 *)effect)->unk_04 = brighten_rgb + color_step_or_index;
        } else if (phase_frame < 0xA0) {
            fade_rgb = ((S_80089608_0 *)effect)->unk_04;
            color_step_or_index = ((s32) (fade_rgb & 0xFF) >> 3);
            color_step_or_index = ((color_step_or_index << 8) + (color_step_or_index << 16)) + color_step_or_index;
            ((S_80089608_0 *)effect)->unk_04 = fade_rgb - color_step_or_index;
        } else {
            ((S_80089608_0 *)effect)->unk_08 = 0xFF;
            ((S_80089608_0 *)effect)->unk_04 = 0;
        }
        ((S_80089608_0 *)effect)->unk_0E.s -= 12;
        break;
    case 0xFF:
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_80089608_0_pre *)effect)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    default:
        break;
    }
    color_step_or_index = 9;
    callback = (void *)mark_object_flags_dirty;
    do {
        element = allocate_flagged_object_node(0x111);
        if (element != NULL) {
            sprite = element->sprite;
            element->unk_10 = callback;
            register_node(element, &linked_sprite_renderer_address);
            x_product = rcos(((S_80089608_0 *)effect)->unk_0E.u) * ((S_80089608_3 *)(effect_tables + color_step_or_index * 2))->unk_28;
            axis_offset = x_product >> 0xC;
            ((S_80089608_7 *)(element->position))->unk_02 =
                (s16) ((axis_offset - (x_product >> 0xD)) + 0xA0);
            element_state = (void *)((s8 *)element + 0x20);
            y_product = rsin(((S_80089608_0 *)effect)->unk_0E.u) * ((S_80089608_3 *)(effect_tables + color_step_or_index * 2))->unk_28;
            axis_offset = y_product >> 0xC;
            ((S_80089608_7 *)(element->position))->unk_06 =
                (s16) ((axis_offset + (y_product >> 0xE)) + 0x78);
            sprite->scale_y = 0x1000;
            sprite->scale_x = 0x1000;
            if (color_step_or_index == 0) {
                sprite->angle_z = ((S_80089608_0 *)effect)->unk_0E.u;
            } else if (color_step_or_index == 1) {
                sprite->angle_z = (s16) (0 - (u16) ((S_80089608_0 *)effect)->unk_0E.u);
            }
            sprite->tpage_abr = 0x60;
            sprite->flags = (u16) (sprite->flags | 0xC);
            sprite->source = (s32) ((S_80089608_5 *)(effect_tables + color_step_or_index * 4))->unk_00;
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
            sprite->color.word =
                (s32) (((S_80089608_0 *)effect)->unk_04 & ((S_80089608_5 *)(effect_tables + color_step_or_index * 4))->unk_40);
            ((S_80089608_6 *)element_state)->unk_0C = color_step_or_index;
        }
        color_step_or_index -= 1;
    } while (color_step_or_index >= 0);
}
