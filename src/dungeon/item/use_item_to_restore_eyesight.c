#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern void clear_slots_of_type();
extern void begin_deferred_item_action();
extern void clear_slot_and_update_linked_state();
extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes();
extern void func_80099290();
extern void display_text_with_fullwidth_adjustment();
extern void apply_item_effect_at_entity_position();
extern void display_item_status_message();
extern s32 apply_actor_food_preference();
extern void create_timed_paired_particle_emitter();

extern u8 D_800E188B[];

/* Updates an entity and its effects, decrementing the shared counter on completion. */
s32 use_item_to_restore_eyesight(void *entity_arg, s32 amount_arg, s16 effect_arg)
{
    s32 amount = amount_arg;
    s32 initial_id;
    s32 selected_id;

    if (entity_arg == D_800E3D7C) {
        *(s32 *)((u8 *)entity_arg + 0x110) = amount;
        begin_deferred_item_action(((void *)(entity_arg)), ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), ((void *)(entity_arg)));
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
        if (apply_actor_food_preference(lookup_entity,
                          (type_table[entity_type] >> 6) & 3,
                          0) == 0) {
            apply_item_effect_at_entity_position(entity_arg, amount);
            return 1;
        }
    }

    create_timed_paired_particle_emitter(*(s32 *)((u8 *)entity_arg - 0x18), 0xC02020, entity_arg);
    if (*(s32 *)((u8 *)entity_arg + 0x14) & 0x4000) {
        initial_id = get_unused_text_buffer();
        selected_id = initial_id;
        if (!(*(s32 *)((u8 *)entity_arg + 0x1C) & 0x10)) {
            selected_id = expand_text_control_codes(D_800E188B, initial_id);
        }
        func_80099290(selected_id);
        display_text_with_fullwidth_adjustment(initial_id);
    }
    clear_slots_of_type(entity_arg, 3);
    clear_slot_and_update_linked_state(amount);
    g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
    return 1;
}
