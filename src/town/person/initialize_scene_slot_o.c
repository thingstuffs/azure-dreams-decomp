#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"

extern u8 D_800D76C8[];
extern u8 D_800D76D0[];
extern u8 D_800D76F8[];
extern u8 D_800D76FC[];

/*
 * Registers the object in scene slot 47 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_47(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 47, D_800D76F8, D_800D76FC, D_800D76C8, D_800D76D0);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
