#include "common.h"
#include "shared/town_object.h"
#include "m2c_compat.h"
#include "town/person/object.h"
#include "town/person.h"

/* Pass the object to start_reaction_vertical_ease. */
void forward_reaction_object(TownObjectRecord *object) {
    start_reaction_vertical_ease(object);
}
