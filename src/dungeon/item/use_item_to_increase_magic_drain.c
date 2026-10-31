#include "shared/actor_property_flags.h"
#include "shared/entity.h"
#include "shared/dungeon_item_entries.h"
#include "shared/actor_status_ids.h"
#include "dungeon/actor/status.h"

struct ObjectNodeHeader;
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

#include "dungeon/player/item.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/system.h"
#include "dungeon/player/state.h"

extern void display_formatted_context_message(void *);
extern s32 generate_random_value(void);
extern void create_colored_effect_with_event(struct ObjectNodeHeader *source, s32 color, unsigned short event_id);

extern u8 D_800E10C0[];
extern u8 D_800E10F2[];

/* Applies an item effect with randomized duration and handles item consumption. */
s32 use_item_to_increase_magic_drain(ActorRecord *target, DungeonItemEntry *item, s16 message_kind)
{
    s32 random_value;

    if (target == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)target)->pending_item_action = item;
        begin_deferred_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_item_status_message(target, item, message_kind);
        if (feed_actor_restore_mp(
                target, (entity_action_selectors[target->species] >> 6) & 3, 0) == 0) {
            place_actor_item(target, item);
            return 1;
        }

        random_value = generate_random_value();
        set_or_clear_actor_status_slot(target, STATUS_MP_DRAIN, (random_value & 0x1F) | 0x20);
        if (target->flags14 & ACTOR_PARTY_MEMBER) {
            adjust_source_value_and_finalize(target, D_800E10C0);
        }
        create_colored_effect_with_event((u8 *)target - 0x20, 0x804040, 0x612);
    } else {
        display_formatted_context_message(D_800E10F2);
    }
    clear_slot_and_update_linked_state(item);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
