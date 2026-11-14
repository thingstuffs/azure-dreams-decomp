#include "common.h"
#include "town/person.h"
#include "town/scene.h"

extern u8 D_800D7C7C[];
extern u8 D_800D7C84[];
extern u8 D_800D7CAC[];
extern u8 D_800D7CB0[];

/* Registers the object in scene slot 37 using the four local setup tables. */
void initialize_scene_slot_37(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    register_object_slot_with_tables(object, 37, D_800D7CAC, D_800D7CB0, D_800D7C7C, D_800D7C84);
}
