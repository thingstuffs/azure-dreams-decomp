#include "shared/actor_property_flags.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern void apply_entity_effects(void *);
extern void begin_deferred_item_action(void *, void *, void *, void *);
extern void clear_slot_and_update_linked_state(u32);
extern void adjust_source_value_and_finalize(void *, void *);
extern void place_actor_item(void *, s32);
extern void display_item_status_message(void *, s32, s16);
extern s32 feed_actor_restore_mp(void *, s32, s32);
extern void create_colored_effect_with_sound(void *source, s32 color, unsigned short sound_id);

extern u8 D_800E2056[];

/* Updates entity state and progress counters, then triggers the associated effects. */
s32 use_item_to_increase_defense(void *entity, s32 update_value, s16 update_mode)
{
    u32 progress_value;
    u8 progress;
    u8 completion_count;

    if (entity == dungeon_actor_ring_anchor) {
        ((EntityRec *)entity)->unk_110 = update_value;
        begin_deferred_item_action(entity, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFF) {
        display_item_status_message(entity, update_value, update_mode);
        if (feed_actor_restore_mp(
                entity, (entity_action_selectors[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            place_actor_item(entity, update_value);
            return 1;
        }
    }

    if (((EntityRec *)entity)->unk_27 == ((EntityRec *)entity)->unk_69) {
        completion_count = (*(u8 *)((u8 *)&((EntityRec *)entity)->x + 1));
        if (completion_count < 0xFF) {
            (*(u8 *)((u8 *)&((EntityRec *)entity)->x + 1)) = completion_count + 1;
            apply_entity_effects(entity);
        }
    }

    progress = ((EntityRec *)entity)->unk_27;
    progress_value = progress & 0xFF;
    if (progress_value < 0xFF && progress_value < ((EntityRec *)entity)->unk_69) {
        ((EntityRec *)entity)->unk_27 = progress + 1;
    }

    if (((EntityRec *)entity)->flags14 & ACTOR_PARTY_MEMBER) {
        adjust_source_value_and_finalize(entity, D_800E2056);
    }
    create_colored_effect_with_sound((u8 *)entity - 0x20, 0x20F020, 0x616);
    clear_slot_and_update_linked_state(update_value);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
