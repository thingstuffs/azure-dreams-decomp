#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"



void begin_deferred_item_action();
void clear_slot_and_update_linked_state();
s32 get_unused_text_buffer();
s32 expand_text_control_codes();
void *func_80099290();
s32 append_entity_display_text();
s32 set_or_clear_actor_status_slot();
s32 display_text_with_fullwidth_adjustment();
void apply_item_effect_at_entity_position();
void display_item_status_message();
s32 apply_actor_food_preference();
void create_colored_effect_with_event();

extern u8 D_80089358[];
extern u8 D_800E0FA4[];
extern u8 D_800E0FB9[];
extern u8 D_800E0FD7[];


typedef struct S_800BDEB8_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800BDEB8_0_pre;   /* 0x14-byte header immediately before the payload. */

typedef struct S_800BDEB8_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    u32 unk_1C;
    u8 pad_20[0x84];
    s32 unk_A4;
    u8 pad_A8[0x2];
    s16 unk_AA;
    u8 pad_AC[0x64];
    s32 unk_110;
} S_800BDEB8_0;

typedef struct S_800BDEB8_1 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_800BDEB8_1;

/* Applies an interaction to an entity and displays the outcome. */
s32 apply_frog_transformation_item(void *entity, s32 action_id, s16 mode) {
    void *current_entity = ((u8 *)D_800E3D7C);
    void *target = entity;
    s32 special_case = 0;
    register s32 original_id;
    s32 message_handle;
    s32 saved_id;
    s32 saved_id_2;
    u32 entity_id;
    s32 result;
    u32 flag_mask;

    if (entity == current_entity) {
        ((S_800BDEB8_0 *)entity)->unk_110 = action_id;
        begin_deferred_item_action(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
    } else {
        if ((u32)entity <= 0x9FFFFFFF) {
            display_item_status_message(entity, action_id, mode);
            if (apply_actor_food_preference(entity, (D_800DDE84[((S_800BDEB8_0 *)entity)->unk_13] >> 6) & 3, 0) == 0) {
                apply_item_effect_at_entity_position(entity, action_id);
                return 1;
            }
        }

        entity_id = ((S_800BDEB8_0 *)entity)->unk_13;
        if (entity_id < 0x2E) {
            if (entity_id == 0x1E) {
                if ((((S_800BDEB8_0 *)entity)->unk_A4 != 0) || (((S_800BDEB8_0 *)entity)->unk_AA != 0)) {
                    special_case = 1;
                }
                result = special_case;
            } else {
                result = special_case;
            }
            if (result != 0) {
                goto show_special;
            }

            flag_mask = 0x80000;
            original_id = ((S_800BDEB8_0 *)entity)->unk_13;
            if (((S_800BDEB8_0 *)entity)->unk_1C & flag_mask) {
                ((S_800BDEB8_1 *)(((S_800BDEB8_0_pre *)entity)[-1].unk_00))->unk_06 = 0;
            }
            {
                u8 *message; /* MATCH: Keep the merged message address in retail's argument register. */
                result = set_or_clear_actor_status_slot(entity, 10, 0x20);
                if ((s16)result >= 0) {
                    saved_id_2 = ((S_800BDEB8_0 *)entity)->unk_13;
                    message_handle = get_unused_text_buffer();
                    ((S_800BDEB8_0 *)entity)->unk_13 = original_id;
                    result = append_entity_display_text(entity, message_handle);
                    ((S_800BDEB8_0 *)entity)->unk_13 = saved_id_2;
                    message = D_800E0FA4;
                    result = expand_text_control_codes(message, result);
                } else {
                    message_handle = get_unused_text_buffer();
                    message = D_800E0FB9;
                    result = expand_text_control_codes(message, message_handle);
                }
            }
            func_80099290(result);
            display_text_with_fullwidth_adjustment(message_handle);
            create_colored_effect_with_event((u8 *)entity - 0x20, 0x20A0A0, 0x613);
        } else {
            special_case = 1;
        }
        result = special_case;
        if (result == 0) {
            clear_slot_and_update_linked_state(action_id);
            g_dungeon_status.unk_0A--;
            return 1;
        }
show_special:
        result = get_unused_text_buffer();
        {
            u8 *message = D_800E0FD7;
            u32 message_arg = result;
            saved_id = message_arg;
            result = expand_text_control_codes(message, message_arg);
        }
        result = append_entity_display_text(entity, result);
        result = expand_text_control_codes(D_80089358, result);
        func_80099290(result);
        display_text_with_fullwidth_adjustment(saved_id);

        clear_slot_and_update_linked_state(action_id);
        g_dungeon_status.unk_0A--;
        return 1;
    }
    return 0;
}
