#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern s32 entity_level_thresholds[];
extern u8 D_800E131C[];

extern s32 get_entity_effect_value(void *, s32);
extern void begin_mode_selected_item_action(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
extern s32 process_record_and_update_linked_state(s32, s32);
extern void clear_slot_and_update_linked_state(s32);
extern void display_formatted_context_message(void *);
extern void raise_entity_level(void *, s32);
extern void place_actor_item(void *, s32);
extern void display_actor_item_status_message(void *, s32, s16);
extern s32 feed_actor_restore_mp(void *, s32, s32);
extern void create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
extern void create_view_color_flash(s32, s16);


typedef struct S_800BF9EC_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800BF9EC_2_pre;   /* the 0x14 bytes before node in use_item_to_level_up_eligible_actors, addressed as node[-1] */

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

typedef struct S_800BF9EC_3 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800BF9EC_3;   /* ((S_800BF9EC_2_pre *)node)[-1].unk_00 in use_item_to_level_up_eligible_actors */

/* Applies an action to the target or eligible list nodes and updates action state. */
s32 use_item_to_level_up_eligible_actors(EntityRec *target, s32 action_id, s16 action_type, s32 action_param)
{
    ActorRecord *head;
    void *node;

    if (action_type == 13) {
        return process_record_and_update_linked_state(action_id, action_param);
    }

    if (target == ((u8 *)dungeon_actor_ring_anchor)) {
        target->unk_110 = action_id;
        begin_mode_selected_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, action_id, action_type);
        if (feed_actor_restore_mp(target, entity_action_selectors[(*(u8 *)((u8 *)&target->unk_10 + 3))] & 3, action_id) == 0) {
            place_actor_item(target, action_id);
            return 1;
        }
    } else {
        create_view_color_flash(0x2020C0, 1);
        display_formatted_context_message(D_800E131C);

        head = primary_actor_record;
        node = (u8 *)((void *)head->next_actor_header) + 0x20;
        if (node != head) {
            do {
                /*
                 * Original bug: the level cap below tests target, the original item user, instead of
                 * node. When Koh is level 99, this skips every otherwise eligible lower-level actor and
                 * still consumes the item. raise_entity_level tests the individual actor's level; this
                 * guard should do the same.
                 */
                if (((((S_800BF9EC_2 *)node)->unk_1C & 0x2400) != 0x2000 ||
                     (get_entity_effect_value(node, 12) << 16) != 0) &&
                    (*(u8 *)((u8 *)&target->unk_10 + 1)) < 99) {
                    ((S_800BF9EC_2 *)node)->unk_18 = entity_level_thresholds[((S_800BF9EC_2 *)node)->unk_11];
                    raise_entity_level(node, 0);
                    if ((((S_800BF9EC_3 *)(((S_800BF9EC_2_pre *)node)[-1].unk_00))->unk_14 & 0x8000) == 0) {
                        s32 effect_id = 0x8003;
                        if (((S_800BF9EC_2 *)node)->unk_14 & 0x2000) {
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
