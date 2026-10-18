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
void apply_item_effect_at_entity_position();                 /* extern */
void display_item_status_message();            /* extern */
s32 apply_actor_food_preference();            /* extern */
void create_colored_effect_with_sound();    /* extern */
extern u8 D_800E1843[];


/* Process an entity event, increment its counter, and finish the event with a visual effect. */
s32 use_item_to_increase_luck(void *entity, s32 event, s16 event_type) {
    u8 entity_count;

    if (entity == ((s32)D_800E3D7C)) {
        ((EntityRec *)entity)->unk_110 = event;
        begin_deferred_item_action(entity, ((M2C_UNK *)(&D_80083780)), ((M2C_UNK *)(&D_80082E80)), entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, event, event_type);
        if (apply_actor_food_preference(entity, (D_800DDE84[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            apply_item_effect_at_entity_position(entity, event);
            return 1;
        }
    }
    entity_count = (*(u8 *)((u8 *)&((EntityRec *)entity)->x + 3));
    if (entity_count < 0xFFU) {
        (*(u8 *)((u8 *)&((EntityRec *)entity)->x + 3)) = (u8) (entity_count + 1);
        if (((EntityRec *)entity)->flags14 & 0x4000) {
            adjust_source_value_and_finalize(entity, D_800E1843);
        }
    }
    create_colored_effect_with_sound(entity - 0x20, 0x202020, 0x616);
    clear_slot_and_update_linked_state(event);

    g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) - 1);
    return 1;
}
