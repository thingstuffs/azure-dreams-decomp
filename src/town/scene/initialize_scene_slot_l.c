#include "common.h"
#include "town/person.h"

extern u8 D_800D6490[];
extern u8 D_800D6498[];
extern u8 D_800D64C0[];
extern u8 D_800D64C4[];

/* Registers the object in scene slot 68 using the four local setup tables. */
void initialize_scene_slot_68(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 68, D_800D64C0, D_800D64C4, D_800D6490, D_800D6498);
}
