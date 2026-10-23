#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/dungeon_status.h"

extern u8 D_800E1035[];

extern void display_actor_item_status_message(void *actor, s32 item);
typedef struct {
    u8 pad00[0x1C];
    s32 unk1C;
    u8 pad20[4];
    u16 unk24;
    u8 pad26[0x40];
    u8 unk66;
} DungeonState;

extern s32 feed_actor_restore_mp(DungeonState *state, s32 mode, u8 *item);
extern void place_actor_item(void *object_context, s32 target);
extern void clear_slot_and_update_linked_state(s32 slot);
extern void display_formatted_context_message(void *context);

/* Handle an item against a target using its type flags, decrementing the counter on fallback. */
s32 feed_egg_to_monster(void *target, s32 item) {
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
