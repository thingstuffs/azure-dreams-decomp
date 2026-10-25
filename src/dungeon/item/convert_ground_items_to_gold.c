#include "shared/dungeon_item_entries.h"
#include "shared/item_ids.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

typedef struct S_800C4030_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C4030_1;   /* state in convert_ground_items_to_gold */


extern s32 lookup_item_category_mapped_value(s32, s32);
#include "dungeon/player/item.h"
extern s32 process_record_and_update_linked_state(s32, s32);
extern void clear_slot_and_update_linked_state(s32);
extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern s32 append_typed_formatted_value(s32, s32);
extern u8 *append_entity_display_text(void *record, u8 *out);
extern s32 write_status_prefix_bytes(s32);
extern void create_type_212_object(s32 flag, s8 value);
extern void play_sound_if_enabled(s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void place_actor_item(void *, s32);
extern s8 random_dungeon_range_16(s32, s32);
extern s32 feed_actor_restore_mp(void *, s32, s32);

extern u8 D_800893DC[];
extern u8 D_800E187C[];
extern u8 dungeon_ground_item_positions[];

/* Handles a target or active-slot update and decrements the shared count on completion. */
s32 convert_ground_items_to_gold(ActorRecord *target, s32 action, s16 action_type, s32 action_param)
{
    s32 result;
    s32 slot_index;
    u8 *slot_data;
    u8 *slot_state;
    u8 *table_base;
    u8 *table_base_2;
    s32 first_arg;
    s32 second_arg;
    void *second_arg_2;
    s32 scratch_value;
    void *saved_context;

    if (action_type == 0xD) {
        return process_record_and_update_linked_state(action, action_param);
    }

    if (target == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)target)->pending_item_action = action;
        begin_mode_selected_item_action(target, &view_reference_entity.x.v, &reference_tile_object.frame_entry, target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        result = get_unused_text_buffer();
        first_arg = action;
        second_arg_2 = result;
        saved_context = second_arg_2;
        result = append_typed_formatted_value(first_arg, second_arg_2);
        result = expand_text_control_codes(D_800E187C, result);
        result = append_entity_display_text(target, result);
        result = expand_text_control_codes(D_800893DC, result);
        result = write_status_prefix_bytes(result);
        clear_byte_and_advance(result);
        display_text_with_fullwidth_adjustment(saved_context);

        table_base = (u8 *)0x800E0000;
        scratch_value = target->species;
        table_base_2 = (u8 *)entity_action_selectors;
        second_arg = ((u16 *)table_base_2)[scratch_value];
        first_arg = second_arg & 3;
        if (feed_actor_restore_mp(target, first_arg, action) == 0) {
            place_actor_item(target, action);
            return 1;
        }
        table_base = (u8 *)0x80080000;
    } else {
        create_type_212_object(1, 8);
        play_sound_if_enabled(0x80F);
        slot_index = 0;
        slot_data = dungeon_ground_item_positions;
        for (; slot_index < 0x40; slot_index++) {
            slot_state = (u8 *)dungeon_ground_items + slot_index * 4;
            if (slot_state[1] != 0) {
                slot_state[1] = ITEM_KIND_COIN;
                slot_state[0] = ITEM_GOLD_COIN;
                *(s32 *)(slot_data + 8) = lookup_item_category_mapped_value(ITEM_KIND_COIN, ITEM_GOLD_COIN);
                slot_state[2] = random_dungeon_range_16(0x10, 0x18);
                slot_state[3] = 1;
            }
            slot_data += 0xC;
        }
        table_base = (u8 *)0x80080000;
    }
    table_base += 0x3460;
    result = ((S_800C4030_1 *)table_base)->unk_0A;
    first_arg = action;
    result--;
    ((S_800C4030_1 *)table_base)->unk_0A = result;
    clear_slot_and_update_linked_state(first_arg);
    return 1;

}

