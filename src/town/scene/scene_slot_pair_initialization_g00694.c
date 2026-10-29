/* Scene slot pair initialization (G00694).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D784C, PD:town/engine:800D7854, PD:town/engine:800D787C, PD:town/engine:800D7880.
 */
#include "town/scene/scene_slot_pair_initialization_g00694.h"
#include "shared/sprite_frame_state.h"
#include "town/scene.h"

/*
 * Registers the object in scene slot 41 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_41(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 41, D_800D787C, D_800D7880, D_800D784C, D_800D7854);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}

/*
 * Registers the object in scene slot 42 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_42(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 42, D_800D787C, D_800D7880, D_800D784C, D_800D7854);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
