#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


typedef struct S_800BF074_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800BF074_1;   /* base in identify_selected_item */

typedef struct S_800BF074_2 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800BF074_2;   /* ((S_800BF074_1 *)base)->unk_04 in identify_selected_item */


extern u8 D_80089374[];
extern u8 D_800E11F5[];

#include "dungeon/player/item.h"
extern s32 process_record_and_update_linked_state(s32, s32);
extern void clear_slot_and_update_linked_state(s32);
extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern s32 append_typed_formatted_value(void *, s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void place_actor_item(void *, s32);
extern void display_actor_item_status_message(void *, s32);
extern void clear_selected_item_flag_400(void *);
extern s32 feed_actor_restore_mp(void *, s32, s32);

/*
 * Routes type 0xD actions to linked-state processing and player actions to the pending item
 * handler. Other targets receive item messages and feeding or placement handling before the
 * pending action is cleared.
 */
s32 identify_selected_item(ActorRecord *entity, s32 action_id, s16 action_type, s32 action_arg) {
    s32 *entity_state;
    void *message_pos;
    void *saved_message_pos;

    if (action_type == 0xD) {
        return process_record_and_update_linked_state(action_id, action_arg);
    }

    if (entity == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)entity)->pending_item_action = action_id;
        begin_mode_selected_item_action(entity, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFF) {
        display_actor_item_status_message(entity, action_id);
        if (feed_actor_restore_mp(entity, entity_action_selectors[entity->species] & 3, action_id) == 0) {
            place_actor_item(entity, action_id);
            return 1;
        }
    } else {
        message_pos = get_unused_text_buffer();
        entity_state = ((s32 *)(&reference_tile_object.selected_item));
        saved_message_pos = message_pos;
        message_pos = expand_text_control_codes(D_800E11F5, append_typed_formatted_value(((S_800BF074_1 *)entity_state)->unk_04, message_pos));
        ((S_800BF074_2 *)(((S_800BF074_1 *)entity_state)->unk_04))->unk_03 &= 0x7F;
        clear_selected_item_flag_400(((S_800BF074_1 *)entity_state)->unk_04);
        clear_byte_and_advance(expand_text_control_codes(D_80089374, append_typed_formatted_value(((S_800BF074_1 *)entity_state)->unk_04, message_pos)));
        display_text_with_fullwidth_adjustment(saved_message_pos);
    }

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_slot_and_update_linked_state(action_id);
    return 1;
}
