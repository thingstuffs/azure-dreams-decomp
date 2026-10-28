#include "common.h"
#include "town/person.h"

extern u8 D_800D5F68[];
extern u8 D_800D5F70[];
extern u8 D_800D5F98[];
extern u8 D_800D5F9C[];

/* Registers the object in scene slot 27 using the four local setup tables. */
void initialize_scene_slot_27(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 27, D_800D5F98, D_800D5F9C, D_800D5F68, D_800D5F70);
}
