#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"

extern u8 D_800D74F8[];
extern u8 D_800D7500[];
extern u8 D_800D7528[];
extern u8 D_800D752C[];

/*
 * Registers the object in scene slot 58 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_58(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    register_object_slot_with_tables(object, 58, D_800D7528, D_800D752C, D_800D74F8, D_800D7500);
    context->clut = 0x40;
}
