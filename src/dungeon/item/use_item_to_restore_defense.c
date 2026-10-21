#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern void begin_deferred_item_action();
extern void clear_slot_and_update_linked_state();
extern void adjust_source_value_and_finalize();
extern void apply_item_effect_at_entity_position();
extern void display_item_status_message();
extern s32 feed_actor_restore_mp();
extern void create_timed_paired_particle_emitter();

extern u8 D_800E0F07[];


typedef struct S_800BDB74_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800BDB74_0_pre;   /* the 0x18 bytes before arg0 in use_item_to_restore_defense, addressed as arg0[-1] */


/* Apply an item effect to the entity and consume the item when handled. */
s32 use_item_to_restore_defense(void *entity, s32 item, s16 use_type) {
    if (entity == D_800E3D7C) {
        ((EntityRec *)entity)->unk_110 = item;
        begin_deferred_item_action(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }

    if ((s32)entity <= 0x9FFFFFFF) {
        display_item_status_message(entity, item, use_type);
        if (feed_actor_restore_mp(entity, (entity_action_selectors[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            apply_item_effect_at_entity_position(entity, item);
            return 1;
        }
    }

    create_timed_paired_particle_emitter(((S_800BDB74_0_pre *)entity)[-1].unk_00, 0x40C040, entity);
    ((EntityRec *)entity)->unk_27 = ((EntityRec *)entity)->unk_69;
    if (((EntityRec *)entity)->flags14 & 0x4000) {
        adjust_source_value_and_finalize(entity, D_800E0F07);
    }
    clear_slot_and_update_linked_state(item);
    g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
    return 1;
}
