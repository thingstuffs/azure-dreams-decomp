#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

void begin_deferred_item_action(); /* extern */
void clear_player_linked_action_flags();                            /* extern */
void clear_slot_and_update_linked_state();                         /* extern */
void display_formatted_context_message();                   /* extern */
void adjust_source_value_and_finalize();           /* extern */
s32 play_sound_if_enabled();                     /* extern */
void place_actor_item();                 /* extern */
void display_item_status_message();            /* extern */
s32 feed_actor_restore_mp();            /* extern */
extern u8 D_800E17C6[41];
extern M2C_UNK D_800E17EF;
extern M2C_UNK D_800E180E;


typedef struct S_800C3900_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C3900_1;

/* Processes an entity action, preserves its state flag, and updates the shared counter. */
s32 apply_familiar_magic_drain_item(EntityRec *entity, s32 action, s16 action_param) {
    void *counter_page;
    DungeonGlobalStatus *counter_base;
    s32 saved_flag;
    s32 flag_test;
    u32 flags;

    if (entity == ((s32)dungeon_actor_ring_anchor)) {
        entity->unk_110 = action;
        begin_deferred_item_action(entity, &view_reference_entity.x.v, &reference_tile_object.unk_000, entity);
        return 0;
    }
    if (((u32) ((*(u8 *)((u8 *)&entity->unk_10 + 3)) - 1) < 0x2EU) && ((u32) entity <= 0x9FFFFFFFU)) {
        display_item_status_message(entity, action, action_param);
        saved_flag = ((u32) ((u32)entity->flags1C) >> 3) & 1;
        if (feed_actor_restore_mp(entity, (entity_action_selectors[(*(u8 *)((u8 *)&entity->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            place_actor_item(entity, action);
            return 1;
        }
        flag_test = saved_flag;
        if (flag_test != 0) {
            entity->flags1C = (u32) (((u32)entity->flags1C) | 8);
        }
        flags = ((u32)entity->flags1C);
        (*(s16 *)&entity->tileX) = 0;
        if (!(flags & 8)) {
            flag_test = flags & 0x80000;
            counter_page = (void *)0x80080000;
            if (flag_test != 0) {
                clear_player_linked_action_flags();
                counter_page = (void *)0x80080000;
            }
            counter_page = &g_dungeon_status.turn_scale;
            ((S_800C3900_1 *)counter_page)->unk_0A = (u16) (((S_800C3900_1 *)counter_page)->unk_0A + 1);
        }
        play_sound_if_enabled(0x51E);
        if (entity->flags14 & 0x4000) {
            adjust_source_value_and_finalize(entity, D_800E17C6);
        }
        clear_slot_and_update_linked_state(action);
    } else if ((*(u8 *)((u8 *)&entity->unk_10 + 3)) == 0) {
        display_formatted_context_message(&D_800E17EF);
        play_sound_if_enabled(0x506);
    } else {
        clear_slot_and_update_linked_state(action);
        display_formatted_context_message(&D_800E180E);
    }
    counter_base = &g_dungeon_status;
    counter_base->activity_counts.parts.pending_action_count = (u16) (((u16)counter_base->activity_counts.parts.pending_action_count) - 1);
    return 1;
}
