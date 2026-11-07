#include "shared/object_node.h"
#include "modules/main_title_callbacks.h"
#include "engine/graphics.h"
#include "shared/object_links.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "engine/node.h"
#include "frontend/settings.h"
#include "frontend/settings/controller_body.h"
#include "main/data.h"
#include "sdk/libgte.h"

   /* the 0x2 bytes before arg0 in update_settings_effect, addressed as arg0[-1] */

typedef struct S_80089608_6 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80089608_6;

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
} __attribute__((packed)) Packed20;
typedef SettingsEffectBlock Words4;
typedef struct {
    s32 w0;
    s32 w1;
} Words2;

typedef struct SettingsVisualLookup {
    s32 source_words[10];
    s16 radii[10];
    u8 pad_3C[4];
    s32 masks[10];
} SettingsVisualLookup;

/* Updates effect brightness and rotation and spawns ten visual elements. */
void update_settings_effect(SettingsVisualEffectBody *effect) {
    SettingsVisualLookup effect_tables;
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
    S_80089608_6 *element_state;
    SpriteFrameState *sprite;
    SettingsMenuBody *owner;
    void *callback;

    copy_dst = (Words4 *)&effect_tables.source_words[0];
    style_src = D_80088790.blocks;
    owner = effect->owner;
    do {
        *copy_dst = *style_src;
        style_src++;
        copy_dst++;
    } while (style_src != ((Words4 *)&D_80088790 + 2));
    *(Words2 *)copy_dst = *(Words2 *)style_src;
    *(Packed20 *)(&effect_tables.radii[0]) = *(Packed20 *)&D_800887B8;
    copy_dst = (Words4 *)&effect_tables.masks[0];
    mask_src = D_800887CC.blocks;
    do {
        *copy_dst = *mask_src;
        mask_src++;
        copy_dst++;
    } while (mask_src != ((Words4 *)&D_800887CC + 2));
    *(Words2 *)copy_dst = *(Words2 *)mask_src;
    if (owner->flags & 1) {
        effect->phase = 0xFF;
    }
    if (owner->state >= 2) {
        effect->phase = 0xFF;
        return;
    }
    phase = effect->phase;
    switch (phase) {
    case 0:
        effect->color = (s32)(effect->color + 0x20202);
        if (owner->state == 1) {
            effect->phase++;
        }
        break;
    case 1:
        phase_frame = effect->ticks + 1;
        effect->ticks = (u16) phase_frame;
        if (phase_frame < 0x80) {
            if (!(phase_frame & 3)) {
                effect->color += 0x10101;
            }
        } else if (phase_frame < 0x91) {
            brighten_rgb = effect->color;
            color_step_or_index = ((s32) (~brighten_rgb & 0xFF) >> 1);
            color_step_or_index = ((color_step_or_index << 8) + (color_step_or_index << 16)) + color_step_or_index;
            effect->color = brighten_rgb + color_step_or_index;
        } else if (phase_frame < 0xA0) {
            fade_rgb = effect->color;
            color_step_or_index = ((s32) (fade_rgb & 0xFF) >> 3);
            color_step_or_index = ((color_step_or_index << 8) + (color_step_or_index << 16)) + color_step_or_index;
            effect->color = fade_rgb - color_step_or_index;
        } else {
            effect->phase = 0xFF;
            effect->color = 0;
        }
        effect->angle -= 12;
        break;
    case 0xFF:
        NODE_HEADER(effect)->flags = (u16) (NODE_HEADER(effect)->flags | NODE_REMOVE);
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
            element->update_callback = callback;
            register_node(element, draw_linked_sprites);
            x_product = rcos((s16)effect->angle) * effect_tables.radii[color_step_or_index];
            axis_offset = x_product >> 0xC;
            element->position->x.w.i =
                (s16) ((axis_offset - (x_product >> 0xD)) + 0xA0);
            element_state = NODE_BODY(element);
            y_product = rsin((s16)effect->angle) * effect_tables.radii[color_step_or_index];
            axis_offset = y_product >> 0xC;
            element->position->y.w.i =
                (s16) ((axis_offset + (y_product >> 0xE)) + 0x78);
            sprite->scale_y = 0x1000;
            sprite->scale_x = 0x1000;
            if (color_step_or_index == 0) {
                sprite->angle_z = (s16)effect->angle;
            } else if (color_step_or_index == 1) {
                sprite->angle_z = (s16) (0 - (u16) effect->angle);
            }
            sprite->tpage_abr = 0x60;
            sprite->flags = (u16) (sprite->flags | 0xC);
            sprite->source = (s32) effect_tables.source_words[color_step_or_index];
            sprite->unk_04 = 0;
            sprite->frame_ticks = 0;
            sprite->color.word =
                (s32)(effect->color & effect_tables.masks[color_step_or_index]);
            element_state->unk_0C = color_step_or_index;
        }
        color_step_or_index -= 1;
    } while (color_step_or_index >= 0);
}
