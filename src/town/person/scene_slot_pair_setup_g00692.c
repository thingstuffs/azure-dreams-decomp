/* scene slot pair setup. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D7484, PD:town/engine:800D748C, PD:town/engine:800D74B4, PD:town/engine:800D74B8. */
#include "town/person/scene_slot_pair_setup_g00692.h"
#include "shared/sprite_frame_state.h"

/*
 * Registers the object in scene slot 83 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_83(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 83, D_800D74B4, D_800D74B8, D_800D7484, D_800D748C);
    context->clut = 0x40;
}

/*
 * Registers the object in scene slot 84 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_84(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 84, D_800D74B4, D_800D74B8, D_800D7484, D_800D748C);
    context->clut = 0x40;
}
