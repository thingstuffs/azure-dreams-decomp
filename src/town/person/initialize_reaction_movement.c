#include "common.h"
#include "town/person/object_setup.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "engine/window.h"
#include "town/person.h"
extern u8 D_800C9AD4[];
extern s32 reaction_movement_heading_entries[];

// Initialize the object's data, movement state, and variant.
void initialize_reaction_movement(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    initialize_object_entries(object, sprite, reaction_movement_heading_entries);
    object->state_callback.as_pm = D_800C9AD4;
    position->velocity_z = 0xFFF60000;
    object->unk_90 = (s16)(scale_random_by_limit(3) + 1);
}
