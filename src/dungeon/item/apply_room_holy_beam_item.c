#include "dungeon/level/room_flags.h"
#include "shared/dungeon_item_entries.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/item.h"


typedef struct {
    u8 pad[0xC];
    u16 flags;
    u8 pad_E[6];
} DungeonRecord;

extern u8 D_800E12D6[];
extern u8 D_800E1303[];

#include "dungeon/player/item.h"
extern s32 process_record_and_update_linked_state(struct DungeonItemEntry *, s32);
extern void clear_slot_and_update_linked_state(struct DungeonItemEntry *);
extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern u8 *clear_byte_and_advance(u8 *byte_ptr);
extern void display_formatted_context_message(void *);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void place_actor_item(void *, struct DungeonItemEntry *);
extern void display_actor_item_status_message(void *, struct DungeonItemEntry *, s16);
extern s32 feed_actor_restore_mp(void *, s32, struct DungeonItemEntry *);
extern void * create_timed_region_flag_expiry(s32 unused0, s32 unused1, s32 unused2, s16 payloadValueA, s16 payloadValueC);


typedef struct S_800BF7FC_0_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_800BF7FC_0_pre;   /* the 0x14 bytes before arg0 in apply_room_holy_beam_item, addressed as arg0[-1] */


typedef struct S_800BF7FC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800BF7FC_1;   /* obj in apply_room_holy_beam_item */

/* Handles an item action for a target and updates dungeon record flags. */
s32 apply_room_holy_beam_item(void *target, DungeonItemEntry *item, s16 action, s32 action_param)
{
    DungeonRecord *record;
    S_800BF7FC_1 *record_obj;
    void *random_value;
    void *event_value;
    s8 record_index;

    if (action == 13) {
        return process_record_and_update_linked_state(item, action_param);
    }

    if (target == ((u8 *)dungeon_actor_ring_anchor)) {
        ((PlayerRecord *)target)->pending_item_action = item;
        begin_mode_selected_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, item, action);
        if (feed_actor_restore_mp(target,
                          entity_action_selectors[(*(u8 *)((u8 *)&((EntityRec *)target)->unk_10 + 3))] & 3,
                          item) == 0) {
            place_actor_item(target, item);
            return 1;
        }
    } else {
        record_obj = (S_800BF7FC_1 *)((S_800BF7FC_0_pre *)target)[-1].unk_00;
        record_index = record_obj->unk_26;
        if (record_index >= 0 && !(dungeon_rooms[record_index].flags & ROOM_HOLY_BEAM)) {
            if (create_timed_region_flag_expiry(record_obj->unk_24,
                              record_obj->unk_25,
                              ((EntityRec *)target)->unk_88,
                              item->unk_00, record_index) == 0) {
                return 0;
            }

            record = &dungeon_rooms[record_obj->unk_26];
            record->flags |= ROOM_HOLY_BEAM;
            create_view_color_flash(0x20C0C0, 1);
            random_value = get_unused_text_buffer();
            event_value = random_value;
            random_value = expand_text_control_codes(D_800E12D6, random_value);
            clear_byte_and_advance(random_value);
            display_text_with_fullwidth_adjustment(event_value);
        } else {
            display_formatted_context_message(D_800E1303);
        }
    }

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_slot_and_update_linked_state(item);
    return 1;
}
