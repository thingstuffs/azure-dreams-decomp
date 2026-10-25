#include "common.h"
#include "town/person.h"






/* Initializes the object with configuration 0x4F and sets its state values. */
void initialize_reaction_object_type_4_f(void *object, s32 unused, s16 *stateValues) {
    initialize_object_and_register_slot(object, 0x4F, D_800D6718, D_800D671C, D_800D66E8, D_800D66F0);
    stateValues[9] = 3;
    ((u8 *)object)[0x70] = 2;
}
