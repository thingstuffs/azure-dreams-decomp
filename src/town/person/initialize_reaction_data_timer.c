#include "common.h"
#include "m2c_compat.h"
#include "town/person.h"
#include "town/person/position.h"

/* Initializes the object's data pointer and associated value to 10. */
void start_reaction_vertical_ease(TownObjectRecord *object) {
    object->handler = &ease_reaction_position_with_vertical_offset;
    object->timer = 0xA;
}
