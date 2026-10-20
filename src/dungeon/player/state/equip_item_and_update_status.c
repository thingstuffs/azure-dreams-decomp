#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
} Item;

typedef struct {
    u8 pad0[0x1C];
    s32 flags;
    u8 pad20[0x2C];
    Item *field4C;
    u8 pad50[0x34];
    u8 b84;
    u8 b85;
} Arg0;

extern u8 D_800E07C0[];
extern u8 D_800E07D3[];
extern s32 *D_800E3D18[];
extern Item *register_item_object_in_free_slot(void *target, void *ptr1, void *ptr2, s16 flag);
/* Retail sets a3 to 10 at 0x80099114 before reading it; no incoming argument. */
extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 write_text_byte_and_advance(s8 value, s8 *dest);
extern s32 append_typed_formatted_value(Item *, s32);
extern s32 append_entity_display_text(void *record, u8 *out);
extern void play_sound_if_enabled(s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void clear_alternate_texture_regions(s32);
extern void load_default_object_palette(s32);
extern void load_equipment_palette_for_category_sixteen(s32);
extern u8 D_80088B64[];
extern u8 D_800DD2B4[];
extern u8 D_800DD2C4[];
extern u8 D_800DD2D4[];
extern u8 D_800DD2E0[];
extern u8 D_800E080A[];
extern u8 D_800E081C[];
extern u8 D_800E0844[];
extern u8 D_800E0853[];
extern u8 D_800E0862[];
extern u8 D_800E3CF8[];
extern u8 D_800E3D80[];
extern u8 D_800DD2C4[];
extern u8 D_800DD2B4[];

void equip_item_and_update_status(Arg0 *context, Item *item) {
    s32 value;
    register s32 result_value;
    s32 item_index;
    s16 tail_index;
    s16 state;
    s32 item_b3;
    Item *current_item;
    Item *selected_item;
    u8 *head_c;
    u8 *head_b;
    u8 head_b_value;

    selected_item = item;
    result_value = 0;
    state = 0;
    if (selected_item != NULL) {
        if (selected_item->b1 == 0xF && selected_item->b0 >= 0xD) {
            play_sound_if_enabled(0x506);
            result_value = get_unused_text_buffer();
            item_b3 = append_typed_formatted_value(selected_item, expand_text_control_codes(D_800E080A, append_entity_display_text(context, write_text_byte_and_advance(8, result_value))));
            func_80099290(expand_text_control_codes(D_80088B64, item_b3));
            display_text_with_fullwidth_adjustment(result_value);
            return;
        }
        selected_item = register_item_object_in_free_slot(selected_item, D_800E07C0, D_800E07D3, 0);
        if (selected_item == NULL) {
            return;
        }
    }

    current_item = context->field4C;
    if (current_item != NULL) {
        value = current_item->b3;
        if (value & 0x40) {
            play_sound_if_enabled(0x70A);
            result_value = get_unused_text_buffer();
            item_b3 = append_typed_formatted_value(current_item, write_text_byte_and_advance(8, result_value));
            func_80099290(expand_text_control_codes(D_800E081C, item_b3));
            display_text_with_fullwidth_adjustment(result_value);
            return;
        }
        current_item->b3 = value & 0xDF;
        D_800E3D18[0] = (s32 *)D_800E3CF8;
        if (current_item == selected_item) {
            selected_item = NULL;
        }
        state = 1;
    }

    if (selected_item != NULL) {
        item_b3 = selected_item->b3;
        item_index = selected_item->b0;
        selected_item->b3 = item_b3 & 0x7F;
        result_value = get_unused_text_buffer();
        func_80099290(expand_text_control_codes(D_800E0844, append_typed_formatted_value(selected_item, write_text_byte_and_advance(8, result_value))));
        display_text_with_fullwidth_adjustment(result_value);
        D_800E3D18[0] = (s32 *)D_800E3D80;
        tail_index = 0x70A;
        if (selected_item->b3 & 0x40) {
            context->flags |= 0x800;
            play_sound_if_enabled(tail_index);
            result_value = get_unused_text_buffer();
            func_80099290(expand_text_control_codes(D_800E0853, append_typed_formatted_value(selected_item, result_value)));
            display_text_with_fullwidth_adjustment(result_value);
        }
        selected_item->b3 |= 0x20;
    } else {
        if (state != 0) {
            result_value = get_unused_text_buffer();
            value = write_text_byte_and_advance(8, result_value);
            value = append_typed_formatted_value(context->field4C, value);
            value = expand_text_control_codes(D_800E0862, value);
            func_80099290(value);
            display_text_with_fullwidth_adjustment(result_value);
        }
        head_c = D_800DD2C4;
        context->b84 = head_c[0];
        head_b = D_800DD2B4;
        head_b_value = head_b[0];
        item_index = 0;
        context->b85 = head_b_value;
    }
    context->field4C = selected_item;
    play_sound_if_enabled(0x508);
    tail_index = item_index;
    if (selected_item->b1 == 0x10) {
        context->b84 = D_800DD2E0[tail_index];
        context->b85 = D_800DD2D4[tail_index];
        if (tail_index == 0) {
            clear_alternate_texture_regions(1);
            return;
        }
        load_equipment_palette_for_category_sixteen(tail_index);
    } else {
        context->b84 = D_800DD2C4[tail_index];
        context->b85 = D_800DD2B4[tail_index];
        if (tail_index == 0) {
            clear_alternate_texture_regions(1);
            return;
        }
        load_default_object_palette(tail_index);
    }
    if (item_index == 0) {
        clear_alternate_texture_regions(1);
    }
}
