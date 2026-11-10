#include "engine/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/dungeon_item_entries.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/entity_action_selectors.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/item.h"
#include "dungeon/effect.h"

extern s32 entity_level_thresholds[];
extern u8 D_800E131C[];

#include "dungeon/player/item.h"
#include "dungeon/player/object.h"
#include "dungeon/actor.h"
#include "dungeon/item/message.h"
#include "dungeon/system.h"

extern s32 process_record_and_update_linked_state(struct DungeonItemEntry *, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
#include "dungeon/player/state/clear_slot_and_update_linked_state_api.h"

typedef struct S_800BF9EC_2 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x2];
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0x3C];
    void * unk_5C;
} S_800BF9EC_2;   /* node in use_item_to_level_up_eligible_actors */


/* Applies an action to the target or eligible list nodes and updates action state. */
s32 use_item_to_level_up_eligible_actors(ActorRecord *target, DungeonItemEntry *action_id, s16 action_type, s32 action_param)
{
    ActorRecord *head;
    void *node;

    if (action_type == 13) {
        return process_record_and_update_linked_state(action_id, action_param);
    }

    if (target == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)target)->pending_item_action = action_id;
        begin_mode_selected_item_action(target, ((&view_reference_entity)), ((&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, action_id);
        if (feed_actor_restore_mp(target, entity_action_selectors[(*(&target->unk_10 + 3))] & 3, action_id) == 0) {
            place_actor_item(target, action_id);
            return 1;
        }
    } else {
        create_view_color_flash(0x2020C0, 1);
        display_formatted_context_message(D_800E131C);

        head = primary_actor_record;
        node = NODE_BODY(head->next_actor_header);
        if (node != head) {
            do {
                /*
                 * BUG: the level cap below tests target, the original item user, instead of
                 * node. When Koh is level 99, this skips every otherwise eligible lower-level actor and
                 * still consumes the item. raise_entity_level tests the individual actor's level; this
                 * guard should do the same.
                 */
                if (((((S_800BF9EC_2 *)node)->unk_1C & (ACTOR_CONFUSED | ACTOR_PLAYER_SIDE)) != 0x2000 ||
                     (get_entity_effect_value(node, STATUS_BRAINWASH) << 16) != 0) &&
                    (*(&target->unk_10 + 1)) < 99) {
                    ((S_800BF9EC_2 *)node)->unk_18 = entity_level_thresholds[((S_800BF9EC_2 *)node)->unk_11];
                    raise_entity_level(node, 0);
                    if ((((SpriteFrameState *)(NODE_HEADER(node)->sprite))->flags & 0x8000) == 0) {
                        s32 effect_id = 0x8003;
                        if (((S_800BF9EC_2 *)node)->unk_14 & ACTOR_CLASS_ENABLED) {
                            effect_id = 0x8002;
                        }
                        create_actor_value_popup(effect_id, node, -2, 1);
                    }
                }
                node = (u8 *)((S_800BF9EC_2 *)node)->unk_5C + 0x20;
            } while (node != head);
        }
    }

    clear_slot_and_update_linked_state(action_id);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
