#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"

extern u8 D_800D7654[];
extern u8 D_800D765C[];
extern u8 D_800D7684[];
extern u8 D_800D7688[];

/*
 * Registers the object in scene slot 48 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_48(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    register_object_slot_with_tables(object, 48, D_800D7684, D_800D7688, D_800D7654, D_800D765C);
    context->clut = 0x40;
}
