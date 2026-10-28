#include "common.h"
#include "town/person.h"

extern u8 D_800D5A50[];
extern u8 D_800D5A58[];
extern u8 D_800D5A80[];
extern u8 D_800D5A84[];

/* Registers the object in scene slot 15 using the four local setup tables. */
void initialize_scene_slot_15(void *object, void *unused, struct SpriteFrameState *context)
{
    initialize_object_and_register_slot(object, 15, D_800D5A80, D_800D5A84, D_800D5A50, D_800D5A58);
}
