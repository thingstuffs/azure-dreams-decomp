#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_800C30D4_0 {
    void * unk_00;
    u8 pad_04[0x23];
    u8 unk_27;
    s32 unk_28;
    u8 pad_2C[0x70];
    s16 unk_9C;
    u8 pad_9E[0x86];
    s32 unk_124;
} S_800C30D4_0;   /* arg0 in use_item_to_apply_poison; pointer addresses record offset 0x14 */




/* cfail-repair: tf7-phase1-cache-v3 */
void begin_deferred_item_action(void *entity, void *first_ptr, void *second_ptr, void *entity_again);          /* extern */
void clear_slot_and_update_linked_state();                         /* extern */
void adjust_source_value_and_finalize();           /* extern */
s32 set_or_clear_actor_status_slot();        /* extern */
void apply_item_effect_at_entity_position();                 /* extern */
void display_item_status_message(void *entity, s32 item, s16 action_type);   /* extern */
s32 feed_actor_restore_mp();            /* extern */
void *spawn_randomized_particle_burst(); /* extern */
extern M2C_UNK D_800E1729;

/* Handles an item action for an entity, including its effect and item cleanup. */
s32 use_item_to_apply_poison(void *entity, s32 item, s16 action_type) {
    MovingTile *tile;

    if (entity == ((u8 *)D_800E3D7C)) {
        ((S_800C30D4_0 *)((u8 *)entity - 0x14))->unk_124 = item;
        begin_deferred_item_action(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, item, action_type);
        if (feed_actor_restore_mp(entity, (*((u16 *)(((u8 *)entity_action_selectors) + ((S_800C30D4_0 *)((u8 *)entity - 0x14))->unk_27 * 2))
            >> 6) & 3, 0) == 0) {
            apply_item_effect_at_entity_position(entity, item);
            return 1;
        }
    }
    tile = ((S_800C30D4_0 *)((u8 *)entity - 0x14))->unk_00;
    spawn_randomized_particle_burst((tile->unk_24 << 6) | 0x20, (tile->unk_25 << 6) | 0x20,
        ((S_800C30D4_0 *)((u8 *)entity - 0x14))->unk_9C, 0x802080, 0x20, 1);
    if (((set_or_clear_actor_status_slot(entity, 5, 8) << 0x10) != 0) && (((S_800C30D4_0 *)((u8 *)entity - 0x14))->unk_28 & 0x4000)) {
        adjust_source_value_and_finalize(entity, &D_800E1729);
    }
    clear_slot_and_update_linked_state(item);
    {
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
    }
    return 1;
}
