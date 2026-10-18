#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

s32 func_8004383C();                 /* extern */
void begin_deferred_item_action(void *, void *, void *, void *); /* extern */
void clear_slot_and_update_linked_state();                         /* extern */
void apply_item_effect_at_entity_position();                 /* extern */
void display_item_status_message();            /* extern */
s32 apply_actor_food_preference();            /* extern */
void create_colored_effect_with_sound();    /* extern */

/* Handles item use for an entity, updating its state and consuming the item. */
s32 use_level_gain_item(void *entity, s32 item, s16 action_id) {
    if (entity == ((u8 *)D_800E3D7C)) {
        ((EntityRec *)entity)->unk_110 = item;
        begin_deferred_item_action(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, item, action_id);
        if (apply_actor_food_preference(entity, (D_800DDE84[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            apply_item_effect_at_entity_position(entity, item);
            return 1;
        }
    }
    if ((u8) (*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 1)) < 0x63U) {
        ((EntityRec *)entity)->unk_18 = func_8004383C(entity, 0);
        ((EntityRec *)entity)->unk_42 = 0;
        ((EntityRec *)entity)->unk_41 = 0;
        D_800E296C |= 0x100000;
    }
    create_colored_effect_with_sound(entity - 0x20, 0x20F0F0, 0x616);
    clear_slot_and_update_linked_state(item);
    g_dungeon_status.unk_0A--;
    return 1;
}
