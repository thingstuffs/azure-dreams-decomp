/* Scene slot context initialization (G00669).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D5EF4, PD:town/engine:800D5EFC, PD:town/engine:800D5F24, PD:town/engine:800D5F28.
 */
#include "town/scene/scene_slot_context_initialization_g00669.h"

/* Registers the object in scene slot 41 using the four local setup tables. */
void initialize_scene_slot_41_context(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 41, (s32)D_800D5F24, (s32)D_800D5F28, (s32)D_800D5EF4, (s32)D_800D5EFC);
}

/* Registers the object in scene slot 42 using the four local setup tables. */
void initialize_scene_slot_42_context(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 42, (s32)D_800D5F24, (s32)D_800D5F28, (s32)D_800D5EF4, (s32)D_800D5EFC);
}
