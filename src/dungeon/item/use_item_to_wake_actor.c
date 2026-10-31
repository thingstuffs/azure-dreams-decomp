#include "dungeon/item.h"
#include "shared/actor_property_flags.h"
#include "shared/dungeon_item_entries.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern void clear_slots_of_type(void *entity, s32 value);
#include "dungeon/player/item.h"
#include "dungeon/actor.h"
#include "dungeon/system.h"
#include "dungeon/player/state.h"

extern void display_formatted_context_message(void *ptr);

extern u8 D_800E0E9B[];


typedef struct S_800BD72C_0_pre {
    ObjectPosition *unk_00;
    u8 pad_04[0x14];
} S_800BD72C_0_pre;   /* the 0x18 bytes before arg0 in use_item_to_wake_actor, addressed as arg0[-1] */


/* Processes an entity event, handling the player separately and completing other events. */
s32 use_item_to_wake_actor(ActorRecord *entity, DungeonItemEntry *event, s16 event_type)
{
    if (entity == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)entity)->pending_item_action = event;
        begin_deferred_item_action(entity, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), entity);
        return 0;
    }

    if ((s32)entity <= 0x9FFFFFFF) {
        display_item_status_message(entity, event, event_type);
        if (feed_actor_restore_mp(
                entity, (entity_action_selectors[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            place_actor_item(entity, event);
            return 1;
        }
    }

    create_timed_paired_particle_emitter(((S_800BD72C_0_pre *)entity)[-1].unk_00, 0xC0C0C0, entity);
    if ((entity->flags14 & ACTOR_PARTY_MEMBER) &&
        !(entity->flags1C & ACTOR_ASLEEP)) {
        display_formatted_context_message(D_800E0E9B);
    }
    clear_slots_of_type(entity, STATUS_SLEEP);
    clear_slot_and_update_linked_state(event);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
