/* Scene slot initialization (G00668).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D5E0C, PD:town/engine:800D5E14, PD:town/engine:800D5E3C, PD:town/engine:800D5E40.
 */
#include "town/scene/scene_slot_initialization_g00668.h"
#include "town/scene.h"

/* Registers the object in scene slot 52 using the four local setup tables. */
void initialize_scene_slot_52_context(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 52, D_800D5E3C, D_800D5E40, D_800D5E0C, D_800D5E14);
}

/* Registers the object in scene slot 54 using the four local setup tables. */
void initialize_scene_slot_54(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 54, D_800D5E3C, D_800D5E40, D_800D5E0C, D_800D5E14);
}

/* Registers the object in scene slot 56 using the four local setup tables. */
void initialize_scene_slot_56(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 56, D_800D5E3C, D_800D5E40, D_800D5E0C, D_800D5E14);
}
