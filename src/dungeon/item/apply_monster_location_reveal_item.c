#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern u8 D_800E1279[];

extern void begin_mode_selected_item_action(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
extern s32 process_record_and_update_linked_state(s32, s32);
extern void clear_slot_and_update_linked_state(s32);
extern void display_formatted_context_message(void *, s32, s16);
extern void apply_item_effect_at_entity_position(void *, s32);
extern void display_actor_item_status_message(void *, s32);
extern s32 apply_actor_food_preference(void *, s32, s32);

/* Apply an item to its target and handle action completion. */
s32 apply_monster_location_reveal_item(EntityRec *target, s32 item, s16 action_type, s32 source)
{
    if (action_type == 13) {
        return process_record_and_update_linked_state(item, source);
    }

    if (target == ((u8 *)D_800E3D7C)) {
        target->unk_110 = item;
        begin_mode_selected_item_action(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, item);
        if (apply_actor_food_preference(target,
                          D_800DDE84[(*(u8 *)((u8 *)&target->unk_10 + 3))] & 3,
                          item) == 0) {
            apply_item_effect_at_entity_position(target, item);
            return 1;
        }
    } else {
        display_formatted_context_message(D_800E1279, source, action_type);
        D_800E296C |= 0x400;
    }

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_slot_and_update_linked_state(item);
    return 1;
}
