#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "dungeon/monster/golem.h"


/* Initialize the object's two state bytes to 0x10 and zero. */
void initialize_directional_action_state(ActorRecord *body) {
    body->action_id = 0x10;
    body->action_phase = 0;
}
