#include "common.h"
#include "town/person.h"
#include "shared/entity.h"
#include "town/person/motion.h"

/* Set the object's data pointer and state to 13. */
void start_reaction_move_toward_target(TownObjectRecord *object) {
    object->handler = &move_reaction_toward_target;
    object->timer = 0xD;
}
