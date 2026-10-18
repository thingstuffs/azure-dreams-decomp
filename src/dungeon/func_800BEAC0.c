#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


void begin_deferred_item_action();
void clear_slot_and_update_linked_state();
s32 play_sound_if_enabled();
void apply_item_effect_at_entity_position();
void display_item_status_message();
s32 apply_actor_food_preference();
s32 try_apply_action_by_chance();


/* Process an entity's item, deferring the primary entity's handling and cleaning up completed uses. */
s32 apply_sleep_item(EntityRec *entity, s32 item, s16 use_type) {
    if (entity == D_800E3D7C) {
        entity->unk_110 = item;
        begin_deferred_item_action(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }
    if ((s32)entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, item, use_type);
        if (apply_actor_food_preference(entity,
                          (D_800DDE84[(*(u8 *)((u8 *)&entity->unk_10 + 3))] >> 6) & 3,
                          0) == 0) {
            apply_item_effect_at_entity_position(entity, item);
            return 1;
        }
    }
    if (try_apply_action_by_chance(entity, 0x400, 8) != 0) {
        play_sound_if_enabled(0x520);
    }
    clear_slot_and_update_linked_state(item);
    g_dungeon_status.unk_0A--;
    return 1;
}
