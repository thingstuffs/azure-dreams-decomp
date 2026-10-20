#include "shared/entity_action_selectors.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


typedef struct {
    u8 pad_0[0xA];
    u16 field_A;
} D_80083460_Type;


void begin_deferred_item_action();
void clear_slot_and_update_linked_state();
void adjust_source_value_and_finalize();
s32 lower_entity_level();
void apply_item_effect_at_entity_position();
void display_item_status_message();
s32 apply_actor_food_preference();
extern M2C_UNK D_800E173A;

/* Processes an entity's item interaction and consumes the item when finished. */
s32 use_item_to_lower_level(EntityRec *entity, s32 item, s16 action) {
    if (entity == ((s32)D_800E3D7C)) {
        entity->unk_110 = item;
        begin_deferred_item_action(entity, &D_80083780.x.v, &D_80082E80.unk_000, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, item, action);
        if (apply_actor_food_preference(
                entity,
                (entity_action_selectors[(*(u8 *)((u8 *)&entity->unk_10 + 3))] >> 6) & 3,
                0) == 0) {
            apply_item_effect_at_entity_position(entity, item);
            return 1;
        }
    }
    if (lower_entity_level(entity, 1) == 0) {
        adjust_source_value_and_finalize(entity, &D_800E173A);
    }
    clear_slot_and_update_linked_state(item);
    {
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
    }
    return 1;
}
