#include "common.h"

#include "town/person/object/initialize_object_entries_api.h"
extern s32 scale_random_to_unsigned_halfword_limit(s32);
extern u8 D_800C9AD4[];
extern s32 D_800D6504[];

// Initialize the object's data, movement state, and variant.
void initialize_reaction_movement(void *object, void *movementState, void *initializationValue) {
    initialize_object_entries(object, initializationValue, D_800D6504);
    *(void **)((u8 *)object + 0x50) = D_800C9AD4;
    *(s32 *)((u8 *)movementState + 0x14) = 0xFFF60000;
    *(s16 *)((u8 *)object + 0x90) = (s16)(scale_random_to_unsigned_halfword_limit(3) + 1);
}
