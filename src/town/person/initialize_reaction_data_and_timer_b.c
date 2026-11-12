#include "common.h"
#include "m2c_compat.h"
#include "town/person.h"
#include "town/person/position.h"

/* Initializes the object's data pointer and sets its initial value to 10. */
void initialize_reaction_data_and_timer_10_b(TownObjectRecord *object, void *unused_position, void *unused_context, void *unused_game) {
    object->handler = &ease_reaction_position_to_target;
    object->timer = 0xA;
}
