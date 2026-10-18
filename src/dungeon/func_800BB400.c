#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/def_table.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern void begin_deferred_item_action();
extern void display_item_status_message();
extern s32 apply_actor_food_preference();
extern void apply_item_effect_at_entity_position();
extern void create_colored_effect_with_sound();
extern void func_80042984();
extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes();
extern u8 *append_entity_display_text();
extern void func_80099290();
extern void display_text_with_fullwidth_adjustment();
extern void clear_slot_and_update_linked_state();

extern u8 D_800E13FB[];
extern u8 D_800E1402[];
extern u8 D_800E1411[];
extern u8 D_800E1426[];
extern u8 D_80089380[];
extern u8 D_800E140A[];

/* Changes the target's element, updates its slots, and displays the result. */
s32 apply_genus_change_item(u8 *target, u8 *event, s32 value)
{
    
    u8 *message;
    u8 *message_end;
    s32 slot_index;
    u8 *slot;

    if (target == ((u8 *)D_800E3D7C)) {
        *(u8 **)(target + 0x110) = event;
        begin_deferred_item_action(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }
    if ((u32)target <= 0x9FFFFFFF) {
        display_item_status_message(target, event, (s16)value);
        if (apply_actor_food_preference(target, (D_800DDE84[target[0x13]] >> 6) & 3, 0) == 0) {
            apply_item_effect_at_entity_position(target, event);
            return 1;
        }
        *(s32 *)(target + 0x14) &= -8;
        *(s32 *)(target + 0x1C) &= -8;
        {
            u8 *effect_target;
            s32 color_mask;
            s32 effect_code;
            s32 event_type;
            event_type = event[0];
            if (event_type == 5) {
                message = D_800E13FB;
                effect_target = target - 32;
                color_mask = 0xF0;
                effect_code = 0x81C;
                *(s32 *)(target + 0x14) |= 1;
                *(s32 *)(target + 0x1C) |= 1;
            } else if (event_type == 6) {
                message = D_800E1402;
                effect_target = target - 32;
                color_mask = 0xF00000;
                effect_code = 0x81C;
                *(s32 *)(target + 0x14) |= 2;
                *(s32 *)(target + 0x1C) |= 2;
            } else {
                message = D_800E140A;
                effect_target = target - 32;
                color_mask = 0xF000;
                effect_code = 0x81C;
                *(s32 *)(target + 0x14) |= 4;
                *(s32 *)(target + 0x1C) |= 4;
            }
            create_colored_effect_with_sound(effect_target, color_mask, effect_code);
        }
        func_80042984(target);

        slot = target + 8;
        for (slot_index = 0; slot_index < 3; slot_index++, slot += 3) {
            if (slot[0] != 0) {
                s32 item = slot[0];
                s32 flags = *(s32 *)(target + 0x14);

                if (((D_8006DE24[item].unk_10 & 7) & flags) == 0) {
                    if (flags & 1) {
                        slot[0] = ((item - 1) / 3) * 3 + 1;
                    } else if (flags & 2) {
                        slot[0] = ((item - 1) / 3) * 3 + 2;
                    } else if (flags & 4) {
                        slot[0] = ((item - 1) / 3) * 3 + 3;
                    }
                }
            }
        }

        if (*(s32 *)(target + 0x14) & 0x4000) {
            u8 *message_start;
            message_end = get_unused_text_buffer();
            message_start = message_end;
            message_end = append_entity_display_text(target, message_end);
            message_end = expand_text_control_codes(D_800E1411, message_end);
            message_end = expand_text_control_codes(message, message_end);
            message_end = expand_text_control_codes(D_80089380, message_end);
            func_80099290(message_end);
            display_text_with_fullwidth_adjustment(message_start);
        }
    } else {
        u8 *message_start;
        message_end = get_unused_text_buffer();
        message_start = message_end;
        message_end = expand_text_control_codes(D_800E1426, message_end);
        message_end = append_entity_display_text(target, message_end);
        message_end = expand_text_control_codes(D_80089380, message_end);
        func_80099290(message_end);
        display_text_with_fullwidth_adjustment(message_start);
    }

    clear_slot_and_update_linked_state(event);
    g_dungeon_status.unk_0A -= 1;
    return 1;
}
