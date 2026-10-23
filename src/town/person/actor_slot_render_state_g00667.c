/* Actor slot render state (G00667). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D5DD4, PD:town/engine:800D5DDC, PD:town/engine:800D5E04, PD:town/engine:800D5E08. */
#include "town/person/actor_slot_render_state_g00667.h"

/* Registers the object in scene slot 53 using the four local setup tables. */
void initialize_scene_slot_53(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 53, (s32)D_800D5E04, (s32)D_800D5E08, (s32)D_800D5DD4, (s32)D_800D5DDC);
}

/* Registers the object in scene slot 55 using the four local setup tables. */
void initialize_scene_slot_55(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 55, (s32)D_800D5E04, (s32)D_800D5E08, (s32)D_800D5DD4, (s32)D_800D5DDC);
}

/* Registers the object in scene slot 49 using the four local setup tables. */
void initialize_scene_slot_49(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 49, (s32)D_800D5E04, (s32)D_800D5E08, (s32)D_800D5DD4, (s32)D_800D5DDC);
}

/*
 * Configures scene slot 28 with the four local tables, stores 0x240 in render halfword 9, and
 * clears flag 0x100 in halfword 10.
 */
void configure_actor_slot_28_and_render_state(void *context, s32 unused, u16 *stateWords) {
    func_800C3050(context, 0x1C, (s32)D_800D5E04, (s32)D_800D5E08, (s32)D_800D5DD4,
                  (s32)D_800D5DDC);
    stateWords[9] = 0x240;
    stateWords[10] &= ~0x100;
}
