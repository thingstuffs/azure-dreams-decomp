#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"

extern u8 D_800D7410[];
extern u8 D_800D7418[];
extern u8 D_800D7440[];
extern u8 D_800D7444[];

/*
 * Registers the object in scene slot 59 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_59(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 59, D_800D7440, D_800D7444, D_800D7410, D_800D7418);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
