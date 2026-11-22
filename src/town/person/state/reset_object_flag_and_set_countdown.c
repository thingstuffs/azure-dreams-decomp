#include "common.h"
#include "m2c_compat.h"
#include "town/person/state.h"
#include "town/data.h"


/* Clears D_80082688 and initializes the object's unk_6E field to 0x400. */
void reset_person_slot_flag_and_angle(TownObjectRecord *object) {
    person_slot_reset_byte = 0;
    object->unk_6E = 0x400;
}
