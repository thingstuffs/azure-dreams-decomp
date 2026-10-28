/* G00693: scene slot pair offsets. */
/* Original-file evidence (G00693): inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D75E0, PD:town/engine:800D75E8, PD:town/engine:800D7610, PD:town/engine:800D7614. */
#include "town/person/scene_slot_pair_offsets_g00693.h"
#include "shared/sprite_frame_state.h"

/*
 * Registers the object in scene slot 62 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_62(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 62, D_800D7610, D_800D7614, D_800D75E0, D_800D75E8);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}

/*
 * Registers the object in scene slot 57 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_57(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 57, D_800D7610, D_800D7614, D_800D75E0, D_800D75E8);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
