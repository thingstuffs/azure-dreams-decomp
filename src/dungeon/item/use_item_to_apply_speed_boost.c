#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

#include "dungeon/player/item.h"
struct Owner_800A48F0;
void clear_slot_and_update_linked_state();                         /* extern */
void adjust_source_value_and_finalize(void *context, const void *source);           /* extern */
s16 set_or_clear_actor_status_slot(struct Owner_800A48F0 *owner, s8 id, s8 value);    /* extern */
void place_actor_item();                 /* extern */
void display_item_status_message();            /* extern */
s32 feed_actor_restore_mp();            /* extern */
void create_colored_effect_with_sound(void *source, s32 color, unsigned short sound_id);    /* extern */
extern u8 D_800E206A[24];


/* Update entity state and counters, with special handling for the primary entity. */
s32 use_item_to_apply_speed_boost(void *entity, s32 event_id, s16 event_param) {
    u8 update_count;

    if (entity == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)entity)->pending_item_action = event_id;
        begin_deferred_item_action(entity, &view_reference_entity.x.v, &reference_tile_object.frame_entry, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, event_id, event_param);
        if (feed_actor_restore_mp(entity, (entity_action_selectors[((ActorRecord *)entity)->species] >> 6) & 3, 0) == 0) {
            place_actor_item(entity, event_id);
            return 1;
        }
    }
    update_count = (*(u8 *)((u8 *)&((ActorRecord *)entity)->unk_00 + 2));
    if (update_count < 0xFFU) {
        (*(u8 *)((u8 *)&((ActorRecord *)entity)->unk_00 + 2)) = (u8) (update_count + 1);
    }
    set_or_clear_actor_status_slot(entity, STATUS_SPEED, 8);
    if (((ActorRecord *)entity)->flags14 & ACTOR_PARTY_MEMBER) {
        adjust_source_value_and_finalize(entity, D_800E206A);
    }
    create_colored_effect_with_sound(entity - 0x20, 0xF02020, 0x616);
    clear_slot_and_update_linked_state(event_id);
    g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
    return 1;
}

