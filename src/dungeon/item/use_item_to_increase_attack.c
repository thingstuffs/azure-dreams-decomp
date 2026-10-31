#include "shared/actor_property_flags.h"
#include "shared/dungeon_item_entries.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

#include "dungeon/player/item.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/system.h"
#include "dungeon/player/state.h"
#include "engine/entity.h"

extern void create_colored_effect_with_sound(void *source, s32 color, unsigned short sound_id);

extern u8 D_800E1350[];


/* Handles an entity action, advancing capped counters and updating dungeon state. */
s32 use_item_to_increase_attack(ActorRecord *entity, DungeonItemEntry *action_id, s16 action_param)
{
    u32 progress_value;
    u8 progress;
    u8 completion_count;

    if (entity == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)entity)->pending_item_action = action_id;
        begin_deferred_item_action(entity, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFF) {
        display_item_status_message(entity, action_id, action_param);
        if (feed_actor_restore_mp(
                entity, (entity_action_selectors[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            place_actor_item(entity, action_id);
            return 1;
        }
    }

    if (entity->current_attack == entity->base_attack) {
        completion_count = (*(u8 *)&((EntityRec *)entity)->x);
        if (completion_count < 0xFF) {
            (*(u8 *)&((EntityRec *)entity)->x) = completion_count + 1;
            apply_entity_effects(entity);
        }
    }

    progress = entity->current_attack;
    progress_value = progress & 0xFF;
    if (progress_value < 0xFF && progress_value < entity->base_attack) {
        entity->current_attack = progress + 1;
    }

    if (entity->flags14 & ACTOR_PARTY_MEMBER) {
        adjust_source_value_and_finalize(entity, D_800E1350);
    }
    create_colored_effect_with_sound((u8 *)entity - 0x20, 0x2020F0, 0x616);
    clear_slot_and_update_linked_state(action_id);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
