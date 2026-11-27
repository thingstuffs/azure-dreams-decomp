#include "common.h"
#include "shared/game_state.h"
#include "shared/entity.h"
#include "shared/dungeon_item_entries.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/action_control_dispatch_g00352.h"

typedef struct Entity {
    u8 pad[0x13];
    u8 species;
    u32 flags;
    u8 pad2[0x110 - 0x18];
    DungeonItemEntry *pending_item_action;
} Entity;

extern u8 return_magic_refused_period[];
extern u8 familiar_return_magic_floor_restriction_message[];
extern u8 return_magic_refused_lead_text[];

#include "dungeon/player/item.h"
#include "dungeon/item.h"
#include "dungeon/player/state.h"
#include "engine/runtime.h"
#include "dungeon/item/message.h"
#include "dungeon/system.h"

s32 create_return_magic_effect(Entity *); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

/* Handles an item's effect on an entity and updates the pending action count. */
s32 use_return_magic(Entity *entity, DungeonItemEntry *item, s16 action_type) {
    if (entity == ((Entity *)dungeon_actor_ring_anchor)) {
        entity->pending_item_action = item;
        begin_deferred_item_action(entity, ((&view_reference_entity)), ((&reference_tile_object)), entity);
        return 0;
    }
    if (entity->flags & 0x4000) {
        if ((u32)(entity->species - 3) < 0x2B) {
            if (GAME_STATE->dungeon_mode_state == 0 && current_dungeon_floor == 0x28 && test_resident_bit(0xA2) == 0) {
                DungeonGlobalStatus *counter;
                display_formatted_context_message(familiar_return_magic_floor_restriction_message);
                counter = &g_dungeon_status;
                (*(u16 *)&counter->activity_counts.parts.pending_action_count)--;
                clear_item_slot(item);
                return 1;
            }
            if (create_return_magic_effect(entity) != 0) {
                DungeonGlobalStatus *counter;
                clear_item_slot(item);
                counter = &g_dungeon_status;
                (*(u16 *)&counter->activity_counts.parts.pending_action_count)--;
                return 1;
            }
            return 0;
        }
        {
            void *original_value;
            void *current_value;
            void *adjusted_value;

            adjusted_value = append_entity_display_text(entity, current_value = get_unused_text_buffer());
            original_value = current_value;
            current_value = adjusted_value;
            clear_byte_and_advance(expand_text_control_codes(return_magic_refused_period, append_item_name_with_value(item, expand_text_control_codes(return_magic_refused_lead_text, current_value))));
            display_text_with_fullwidth_adjustment(original_value);
            place_actor_item(entity, item);
        }
        return 1;
    }
    if ((u32)(entity->species - 3) < 0x2B) {
        if (create_return_magic_effect(entity) != 0) {
            DungeonGlobalStatus *counter = &g_dungeon_status;
            (*(u16 *)&counter->activity_counts.parts.pending_action_count)--;
            return 1;
        }
        return 0;
    }
    display_item_status_message(entity, item, action_type);
    {
        DungeonGlobalStatus *counter = &g_dungeon_status;
        (*(u16 *)&counter->activity_counts.parts.pending_action_count)--;
    }
    return 1;
}
