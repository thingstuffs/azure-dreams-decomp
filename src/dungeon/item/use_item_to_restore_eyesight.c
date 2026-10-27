#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/item/message.h"
#include "dungeon/actor/status.h"

extern void clear_slots_of_type(ActorRecord *owner, s8 match_type);
#include "dungeon/player/item.h"
extern void clear_slot_and_update_linked_state();
extern void *get_unused_text_buffer(void);
extern s32 display_text_with_fullwidth_adjustment(s8 *text);
extern void place_actor_item();
extern void display_item_status_message();
extern void create_timed_paired_particle_emitter();

extern u8 D_800E188B[];

/* Updates an entity and its effects, decrementing the shared counter on completion. */
s32 use_item_to_restore_eyesight(void *entity_arg, s32 amount_arg, s16 effect_arg)
{
    s32 amount = amount_arg;
    void *initial_id;
    void *selected_id;

    if (entity_arg == dungeon_actor_ring_anchor) {
        *(s32 *)((u8 *)entity_arg + 0x110) = amount;
        begin_deferred_item_action(((void *)(entity_arg)), ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), ((void *)(entity_arg)));
        return 0;
    }

    if ((u32)entity_arg <= 0x9FFFFFFF) {
        void *lookup_entity;
        u16 *type_table;
        s32 entity_type;

        display_item_status_message(entity_arg, amount, effect_arg);
        lookup_entity = entity_arg;
        entity_type = *((u8 *)entity_arg + 0x13);
        type_table = (u16 *)&entity_action_selectors;
        if (feed_actor_restore_mp(lookup_entity,
                          (type_table[entity_type] >> 6) & 3,
                          0) == 0) {
            place_actor_item(entity_arg, amount);
            return 1;
        }
    }

    create_timed_paired_particle_emitter(*(s32 *)((u8 *)entity_arg - 0x18), 0xC02020, entity_arg);
    if (*(s32 *)((u8 *)entity_arg + 0x14) & ACTOR_PARTY_MEMBER) {
        initial_id = get_unused_text_buffer();
        selected_id = initial_id;
        if (!(*(s32 *)((u8 *)entity_arg + 0x1C) & ACTOR_BLIND)) {
            selected_id = expand_text_control_codes(D_800E188B, initial_id);
        }
        clear_byte_and_advance(selected_id);
        display_text_with_fullwidth_adjustment(initial_id);
    }
    clear_slots_of_type(entity_arg, STATUS_BLIND);
    clear_slot_and_update_linked_state(amount);
    g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
    return 1;
}
