#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern void clear_slots_of_type(void *entity, s32 value);
extern void begin_deferred_item_action(void *entity_ptr, void *ptr0, void *ptr1, void *entity);
extern void clear_slot_and_update_linked_state(s32 event);
extern void display_formatted_context_message(void *ptr);
extern void apply_item_effect_at_entity_position(void *entity, s32 event);
extern void display_item_status_message(void *entity, s32 event, s16 event_type);
extern s32 apply_actor_food_preference(void *entity, s32 value, s32 value2);
extern void create_timed_paired_particle_emitter(s32 value, s32 value2, void *entity);

extern u8 D_800E0E9B[];


typedef struct S_800BD72C_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800BD72C_0_pre;   /* the 0x18 bytes before arg0 in use_item_to_wake_actor, addressed as arg0[-1] */


/* Processes an entity event, handling the player separately and completing other events. */
s32 use_item_to_wake_actor(void *entity, s32 event, s16 event_type)
{
    if (entity == D_800E3D7C) {
        ((EntityRec *)entity)->unk_110 = event;
        begin_deferred_item_action(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }

    if ((s32)entity <= 0x9FFFFFFF) {
        display_item_status_message(entity, event, event_type);
        if (apply_actor_food_preference(
                entity, (D_800DDE84[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            apply_item_effect_at_entity_position(entity, event);
            return 1;
        }
    }

    create_timed_paired_particle_emitter(((S_800BD72C_0_pre *)entity)[-1].unk_00, 0xC0C0C0, entity);
    if ((((EntityRec *)entity)->flags14 & 0x4000) &&
        !(((EntityRec *)entity)->flags1C & 0x200)) {
        display_formatted_context_message(D_800E0E9B);
    }
    clear_slots_of_type(entity, 1);
    clear_slot_and_update_linked_state(event);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
