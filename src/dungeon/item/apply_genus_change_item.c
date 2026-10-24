#include "shared/item_ids.h"
#include "shared/actor_property_flags.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/def_table.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "engine/entity.h"

#include "dungeon/player/item.h"
extern void display_item_status_message();
extern s32 feed_actor_restore_mp();
extern void place_actor_item();
extern void create_colored_effect_with_sound();
extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes();
extern u8 *append_entity_display_text();
extern void clear_byte_and_advance();
extern void display_text_with_fullwidth_adjustment();
extern void clear_slot_and_update_linked_state();

extern u8 D_800E13FB[];
extern u8 D_800E1402[];
extern u8 D_800E1411[];
extern u8 D_800E1426[];
extern u8 D_80089380[];
extern u8 genus_change_text[];

/* Changes the target's element, updates its slots, and displays the result. */
s32 apply_genus_change_item(u8 *target, u8 *event, s32 value)
{
    
    u8 *message;
    u8 *message_end;
    s32 slot_index;
    u8 *slot;

    if (target == ((u8 *)dungeon_actor_ring_anchor)) {
        *(u8 **)(target + 0x110) = event;
        begin_deferred_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }
    if ((u32)target <= 0x9FFFFFFF) {
        display_item_status_message(target, event, (s16)value);
        if (feed_actor_restore_mp(target, (entity_action_selectors[target[0x13]] >> 6) & 3, 0) == 0) {
            place_actor_item(target, event);
            return 1;
        }
        *(s32 *)(target + 0x14) &= ~ACTOR_ELEMENT_MASK;
        *(s32 *)(target + 0x1C) &= ~ACTOR_ELEMENT_MASK;
        {
            u8 *effect_target;
            s32 color_mask;
            s32 effect_code;
            s32 event_type;
            event_type = event[0];
            if (event_type == ITEM_LIGHT_SEED) {
                message = D_800E13FB;
                effect_target = target - 32;
                color_mask = 0xF0;
                effect_code = 0x81C;
                *(s32 *)(target + 0x14) |= ACTOR_ELEMENT_FIRE;
                *(s32 *)(target + 0x1C) |= ACTOR_ELEMENT_FIRE;
            } else if (event_type == ITEM_SEA_SEED) {
                message = D_800E1402;
                effect_target = target - 32;
                color_mask = 0xF00000;
                effect_code = 0x81C;
                *(s32 *)(target + 0x14) |= ACTOR_ELEMENT_WATER;
                *(s32 *)(target + 0x1C) |= ACTOR_ELEMENT_WATER;
            } else {
                message = genus_change_text;
                effect_target = target - 32;
                color_mask = 0xF000;
                effect_code = 0x81C;
                *(s32 *)(target + 0x14) |= ACTOR_ELEMENT_WIND;
                *(s32 *)(target + 0x1C) |= ACTOR_ELEMENT_WIND;
            }
            create_colored_effect_with_sound(effect_target, color_mask, effect_code);
        }
        update_owner_class_bits(target);

        slot = target + 8;
        for (slot_index = 0; slot_index < 3; slot_index++, slot += 3) {
            if (slot[0] != 0) {
                s32 item = slot[0];
                s32 flags = *(s32 *)(target + 0x14);

                if (((item_action_definitions[item].unk_10 & ACTOR_ELEMENT_MASK) & flags) == 0) {
                    if (flags & ACTOR_ELEMENT_FIRE) {
                        slot[0] = ((item - 1) / 3) * 3 + 1;
                    } else if (flags & ACTOR_ELEMENT_WATER) {
                        slot[0] = ((item - 1) / 3) * 3 + 2;
                    } else if (flags & ACTOR_ELEMENT_WIND) {
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
            clear_byte_and_advance(message_end);
            display_text_with_fullwidth_adjustment(message_start);
        }
    } else {
        u8 *message_start;
        message_end = get_unused_text_buffer();
        message_start = message_end;
        message_end = expand_text_control_codes(D_800E1426, message_end);
        message_end = append_entity_display_text(target, message_end);
        message_end = expand_text_control_codes(D_80089380, message_end);
        clear_byte_and_advance(message_end);
        display_text_with_fullwidth_adjustment(message_start);
    }

    clear_slot_and_update_linked_state(event);
    g_dungeon_status.activity_counts.parts.pending_action_count -= 1;
    return 1;
}
