#include "common.h"
#include "town/person.h"

extern u8 D_800D51C8[];
extern u8 D_800D51D0[];
extern u8 D_800D51F8[];
extern u8 D_800D51FC[];

/* Registers the object in scene slot 1 using the four local setup tables. */
void initialize_scene_slot_1_context(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 1, D_800D51F8, D_800D51FC, D_800D51C8, D_800D51D0);
}
