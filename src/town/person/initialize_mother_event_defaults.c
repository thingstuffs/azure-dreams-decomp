#include "common.h"
#include "m2c_compat.h"
#include "town/person.h"

/* Initializes the object's state fields to fixed defaults. */
void initialize_mother_event_defaults(TownObjectRecord *object) {
    object->unk_84 = 0x520;
    object->unk_86 = 0x2A0;
    object->unk_94 = 2;
    object->unk_6E = 0x400;
}
