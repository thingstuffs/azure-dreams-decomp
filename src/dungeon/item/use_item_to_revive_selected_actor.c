#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

void apply_entity_effects(void *);             /* extern */
s32 get_entity_effect_value();            /* extern */
void begin_mode_selected_item_action(); /* extern */
s32 process_record_and_update_linked_state();           /* extern */
void clear_slot_and_update_linked_state();                         /* extern */
void display_formatted_context_message();                   /* extern */
void adjust_source_value_and_finalize();           /* extern */
void place_actor_item();                 /* extern */
void display_item_status_message();            /* extern */
s32 feed_actor_restore_mp();            /* extern */
extern u8 D_800E1580[];
extern M2C_UNK D_800E15A2;
extern void *familiar_record_slots[];


typedef struct S_800C22EC_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C22EC_1;   /* counter in use_item_to_revive_selected_actor */

typedef struct S_800C22EC_2 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x1];
    u8 unk_03;
} S_800C22EC_2;

typedef struct S_800C22EC_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    s8 unk_28;
    u8 unk_29;
} S_800C22EC_3;

/* Processes an entity action and updates the selected target or reports failure. */
s32 use_item_to_revive_selected_actor(EntityRec *entity, s32 action, s16 action_type, void *context) {
    s32 target_index;
    s32 flags_mask;
    s32 target_updated;
    S_800C22EC_2 *selection;
    S_800C22EC_3 *target;

    target_updated = 0;
    if (action_type == 0xD) {
        return process_record_and_update_linked_state(action, context);
    }
    if (entity == ((s32)dungeon_actor_ring_anchor)) {
        entity->unk_110 = action;
        begin_mode_selected_item_action(entity, &view_reference_entity.x.v, &reference_tile_object.unk_000, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, action, action_type);
        if (feed_actor_restore_mp(entity, entity_action_selectors[(*(u8 *)((u8 *)&entity->unk_10 + 3))] & 3, 0) == 0) {
            place_actor_item(entity, action);
            return 1;
        }
        clear_slot_and_update_linked_state(action);
        {

            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        }
        return 1;
    }
    selection = *(void **)((u8 *)&reference_tile_object.unk_000 + 0x34);
    if (selection->unk_01 == 0x13) {
        target_index = selection->unk_03 & 0x1F;
        if (target_index < 0x14) {
            target = familiar_record_slots[target_index];
            if ((get_entity_effect_value(target, 0xE) << 0x10) != 0) {
                void *update_target;

                flags_mask = 0xFBFFFFFF;
                update_target = target;
                target->unk_28 = (s8) (((u8) target->unk_29 >> 1) + 1);
                target->unk_1C = (s32) (target->unk_1C & flags_mask);
                apply_entity_effects(update_target);
                target_updated = 1;
                adjust_source_value_and_finalize(target, D_800E1580);
            }
        }
    }
    if (target_updated == 0) {
        display_formatted_context_message(&D_800E15A2);
    }
    clear_slot_and_update_linked_state(action);
    {

        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
    }
    return 1;
}
