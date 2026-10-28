#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"

extern u8 D_800D756C[];
extern u8 D_800D7574[];
extern u8 D_800D759C[];
extern u8 D_800D75A0[];

/*
 * Registers the object in scene slot 45 using the four local setup tables and sets the context
 * halfword at offset 0x12 to 0x40.
 */
void initialize_scene_slot_45(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 45, D_800D759C, D_800D75A0, D_800D756C, D_800D7574);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
