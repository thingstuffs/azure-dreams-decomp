#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Clear the current object's two state fields. */
void clear_ghosh_scripted_action(void) {
    ActorRecord *state;
    void *body;

    body = ghosh_scripted_actor + 1;
    state = body;
    state->action_id = 0;
    state->action_timer = 0;
}
