#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

s32 lookup_level_experience_threshold();                 /* extern */
#include "dungeon/player/item.h"
void clear_slot_and_update_linked_state();                         /* extern */
void place_actor_item();                 /* extern */
void display_item_status_message();            /* extern */
s32 feed_actor_restore_mp();            /* extern */
void create_colored_effect_with_sound();    /* extern */

/* Handles item use for an entity, updating its state and consuming the item. */
s32 use_level_gain_item(void *entity, s32 item, s16 action_id) {
    if (entity == ((u8 *)dungeon_actor_ring_anchor)) {
        ((EntityRec *)entity)->unk_110 = item;
        begin_deferred_item_action(entity, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, item, action_id);
        if (feed_actor_restore_mp(entity, (entity_action_selectors[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            place_actor_item(entity, item);
            return 1;
        }
    }
    if ((u8) (*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 1)) < 0x63U) {
        ((EntityRec *)entity)->unk_18 = lookup_level_experience_threshold(entity, 0);
        ((EntityRec *)entity)->unk_42 = 0;
        ((EntityRec *)entity)->unk_41 = 0;
        dungeon_floor_flags |= 0x100000;
    }
    create_colored_effect_with_sound(entity - 0x20, 0x20F0F0, 0x616);
    clear_slot_and_update_linked_state(item);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
