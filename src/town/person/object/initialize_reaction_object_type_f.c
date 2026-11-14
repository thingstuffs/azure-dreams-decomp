#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"
#include "town/person/object.h"






/* Initializes the object with configuration 0x4F and sets its state values. */
void initialize_scene_slot_79(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *stateValues) {
    register_object_slot_with_tables(object, 0x4F, D_800D6718, D_800D671C, D_800D66E8, D_800D66F0);
    stateValues->clut = 3;
    object->unk_70 = 2;
}
