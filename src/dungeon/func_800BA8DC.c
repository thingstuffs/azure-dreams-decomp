#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

void begin_deferred_item_action(); /* extern */
void clear_slot_and_update_linked_state();                         /* extern */
void adjust_source_value_and_finalize();           /* extern */
s16 set_or_clear_actor_status_slot();    /* extern */
void apply_item_effect_at_entity_position();                 /* extern */
void display_item_status_message();            /* extern */
s32 apply_actor_food_preference();            /* extern */
void create_colored_effect_with_sound();    /* extern */
extern M2C_UNK D_800E206A;


/* Update entity state and counters, with special handling for the primary entity. */
s32 use_item_to_apply_speed_boost(void *entity, s32 event_id, s16 event_param) {
    u8 update_count;

    if (entity == D_800E3D7C) {
        ((EntityRec *)entity)->unk_110 = event_id;
        begin_deferred_item_action(entity, &D_80083780.x.v, &D_80082E80.unk_000, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, event_id, event_param);
        if (apply_actor_food_preference(entity, (D_800DDE84[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            apply_item_effect_at_entity_position(entity, event_id);
            return 1;
        }
    }
    update_count = (*(u8 *)((u8 *)&((EntityRec *)entity)->x + 2));
    if (update_count < 0xFFU) {
        (*(u8 *)((u8 *)&((EntityRec *)entity)->x + 2)) = (u8) (update_count + 1);
    }
    set_or_clear_actor_status_slot(entity, 7, 8);
    if (((EntityRec *)entity)->flags14 & 0x4000) {
        adjust_source_value_and_finalize(entity, &D_800E206A);
    }
    create_colored_effect_with_sound(entity - 0x20, 0xF02020, 0x616);
    clear_slot_and_update_linked_state(event_id);
    g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) - 1);
    return 1;
}

