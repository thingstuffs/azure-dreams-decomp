#include "shared/entity_action_selectors.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/actor.h"
#include "dungeon/system.h"
#include "dungeon/player/state.h"

extern u8 D_800E1035[];

extern void display_actor_item_status_message(void *actor, struct DungeonItemEntry *item);

extern void display_formatted_context_message(void *context);

/* Handle an item against a target using its type flags, decrementing the counter on fallback. */
s32 feed_egg_to_monster(void *target, DungeonItemEntry *item) {
    u32 type_flags;

    if ((u32) target <= 0x9FFFFFFFU) {
        display_actor_item_status_message(target, item);
        type_flags = entity_action_selectors[((u8 *) target)[0x13]];
        if (feed_actor_restore_mp(target, (type_flags >> 2) & 3, 0) == 0) {
            place_actor_item(target, item);
            return 1;
        }
        clear_slot_and_update_linked_state(item);
    } else {
        display_formatted_context_message(D_800E1035);
    }

    g_dungeon_status.activity_counts.parts.pending_action_count -= 1;
    return 1;
}
