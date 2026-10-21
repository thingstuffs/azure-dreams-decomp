/* inferred-strong G00584: washed_dish_effects_g00584; joins PD:town/engine:800D0E44,PD:town/engine:800F8A70; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0E44, PD:town/engine:800F8A70. */
#include "town/menu/washed_dish_effects_g00584.h"

/* Initialize the object state, shared counter, context resource, and callback. */
void initialize_timed_resource_object(void *object, s32 unused, void *context) {
    void *resource_base;

    *(s32 **) ((s8 *) object - 0x10) = &finalize_object_or_select_town_record;
    dish_counter = 0x14;
    resource_base = &D_800F8A70;
    *(void **) ((s8 *) context + 8) = (void *) ((s8 *) resource_base + 0xF0);
    register_node_if_unregistered(object, (s32)(project_sprite_chain));
}

/* Clears and flags a handled object, or clamps the town index and selects a record. */
void finalize_object_or_select_town_record(void *object, void *check_context, void *record_holder)
{
    u8 *state_byte;

    if (classify_object_against_bounds(object, check_context) != 0) {
        state_byte = *(u8 **)((u8 *)object + 0x98);
        if (state_byte != 0) {
            *state_byte = 0;
        }
        unlink_node_if_registered(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }

    if (dish_counter < 0) {
        dish_counter = 0;
    } else if (dish_counter >= 21) {
        dish_counter = 20;
    }
    *(TownRecord **)((u8 *)record_holder + 8) = &D_800F8A70[D_800D0E40[1]];
}

/* washed_dish_suu_set: Set and return the washed dish count. */
s32 washed_dish_suu_set(s32 new_count) {
    s32 dish_count = new_count;

    (*(D800D0E44 *)&dish_counter).value = dish_count;
    return dish_count;
}

/* washed_dish_suu_inc: Decrement the washed dish count, clamp it to zero, and return it. */
s32 washed_dish_suu_inc(void) {
    dish_counter--;
    if (dish_counter < 0) {
        dish_counter = 0;
    }
    return dish_counter;
}
