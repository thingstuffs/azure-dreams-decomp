#include "common.h"
#include "town/person/object_setup.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "engine/window.h"
#include "town/person.h"
extern u8 D_800C9AD4[];
extern s32 D_800D6504[];

// Initialize the object's data, movement state, and variant.
void initialize_reaction_movement(TownObjectRecord *object, void *movementState, void *initializationValue) {
    initialize_object_entries(object, initializationValue, D_800D6504);
    object->unk_50.as_pm = D_800C9AD4;
    *(s32 *)((u8 *)movementState + 0x14) = 0xFFF60000;
    object->unk_90 = (s16)(scale_random_to_unsigned_halfword_limit(3) + 1);
}
