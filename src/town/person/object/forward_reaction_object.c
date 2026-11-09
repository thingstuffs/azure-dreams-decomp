#include "common.h"
#include "shared/town_object.h"
#include "m2c_compat.h"
#include "town/person/object.h"
#include "town/person.h"

/* Pass the object to initialize_reaction_data_and_timer_10. */
void forward_reaction_object(TownObjectRecord *object) {
    initialize_reaction_data_and_timer_10(object);
}
