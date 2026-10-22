/* Initialize scene slot b.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01187 - PD:town/engine:800D6824, PD:town/engine:800D682C, PD:town/engine:800D6854, PD:town/engine:800D6858.
 */
#include "town/person/initialize_scene_slot_b_g01187.h"

void initialize_scene_slot_46(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 46, (s32)D_800D6854, (s32)D_800D6858, (s32)D_800D6824, (s32)D_800D682C);
}

void initialize_scene_slot_38(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 38, (s32)D_800D6854, (s32)D_800D6858, (s32)D_800D6824, (s32)D_800D682C);
}

void initialize_scene_slot_30(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 30, (s32)D_800D6854, (s32)D_800D6858, (s32)D_800D6824, (s32)D_800D682C);
}

void initialize_scene_slot_57_context(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 57, (s32)D_800D6854, (s32)D_800D6858, (s32)D_800D6824, (s32)D_800D682C);
}

void initialize_scene_slot_62_context(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 62, (s32)D_800D6854, (s32)D_800D6858, (s32)D_800D6824, (s32)D_800D682C);
}

void initialize_scene_slot_24(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 24, (s32)D_800D6854, (s32)D_800D6858, (s32)D_800D6824, (s32)D_800D682C);
}

void configure_actor_slot_25_and_render_state(void *context, s32 unused, u16 *stateWords) {
    func_800C3050(context, 0x19, D_800D6854, D_800D6858, D_800D6824,
                  D_800D682C);
    stateWords[9] = 0x240;
    stateWords[10] &= ~0x100;
}

void initialize_scene_slot_69(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 69, (s32)D_800D6854, (s32)D_800D6858, (s32)D_800D6824, (s32)D_800D682C);
}
