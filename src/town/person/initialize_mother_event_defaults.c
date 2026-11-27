#include "common.h"
#include "m2c_compat.h"
#include "town/person.h"

/* Initializes the object's state fields to fixed defaults. */
void initialize_mother_event_defaults(TownObjectRecord *object) {
    object->origin_x = 0x520;
    object->origin_y = 0x2A0;
    object->state_index = 2;
    object->origin_heading = 0x400;
}
