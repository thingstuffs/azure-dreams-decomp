#include "shared/entity_action_selectors.h"
#include "shared/dungeon_item_entries.h"
#include "shared/item_ids.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern u8 D_800E14D8[];
extern u8 D_800E14EB[];
extern u8 D_800E1514[];

#include "dungeon/player/item.h"
#include "dungeon/actor.h"
#include "dungeon/item/message.h"
#include "dungeon/item.h"
#include "dungeon/system.h"

extern s32 resolve_item_attack(struct DungeonItemEntry *, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
#include "dungeon/player/state/clear_slot_and_update_linked_state_api.h"

typedef struct S_800C1B1C_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800C1B1C_1;   /* base in use_item_to_increase_ball_charges */

typedef struct S_800C1B1C_2 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 unk_02;
} S_800C1B1C_2;   /* ((S_800C1B1C_1 *)base)->unk_04 in use_item_to_increase_ball_charges */

/* Apply a target action or update the current item and display its result message. */
s32 use_item_to_increase_ball_charges(ActorRecord *target, DungeonItemEntry *action, s16 action_type, s32 action_arg)
{
    s32 *item_state;
    void *message;
    void *message_end;

    if (action_type == 13) {
        return resolve_item_attack(action, action_arg);
    }

    if (target == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)target)->pending_item_action = action;
        begin_mode_selected_item_action(target, ((&view_reference_entity)), ((&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, action);
        if (feed_actor_restore_mp(
                target, entity_action_selectors[(*(&target->unk_10 + 3))] & 3, 0) == 0) {
            place_actor_item(target, action);
            return 1;
        }
    } else {
        message = get_unused_text_buffer();
        item_state = ((&reference_tile_object.selected_item));
        if (((S_800C1B1C_2 *)(((S_800C1B1C_1 *)item_state)->unk_04))->unk_01 == ITEM_KIND_BALL) {
            message_end = expand_text_control_codes(
                D_800E14EB,
                copy_selected_text_without_terminator(
                    ((S_800C1B1C_1 *)item_state)->unk_04,
                    expand_text_control_codes(D_800E14D8, message)));
            play_sound_if_enabled(0x80F);
            if (((s8)((S_800C1B1C_2 *)(((S_800C1B1C_1 *)item_state)->unk_04))->unk_02) < 99) {
                ((S_800C1B1C_2 *)(((S_800C1B1C_1 *)item_state)->unk_04))->unk_02++;
            }
        } else {
            message_end = expand_text_control_codes(D_800E1514, message);
        }
        clear_byte_and_advance(message_end);
        display_text_with_fullwidth_adjustment(message);
    }

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_item_slot(action);
    return 1;
}
