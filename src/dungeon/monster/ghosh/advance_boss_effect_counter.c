#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "m2c_compat.h"



/* Clear the object's halfword field and increment its byte counter. */
void advance_boss_effect_counter(void) {
    ActorRecord *object;
    void *body;

    body = ghosh_scripted_actor + 1;
    object = body;
    object->action_timer = 0;
    object->action_id = (u8) (object->action_id + 1);
}
