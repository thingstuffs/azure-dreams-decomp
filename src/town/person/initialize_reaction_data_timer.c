#include "common.h"
#include "m2c_compat.h"
#include "town/person.h"
#include "town/person/position.h"

/* Initializes the object's data pointer and associated value to 10. */
void initialize_reaction_data_and_timer_10(TownObjectRecord *object) {
    object->handler = &ease_reaction_position_with_vertical_offset;
    object->timer = 0xA;
}
