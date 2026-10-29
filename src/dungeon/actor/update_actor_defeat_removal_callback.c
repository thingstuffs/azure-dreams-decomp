#include "common.h"
#include "dungeon/actor.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */

/* Runs the shared actor defeat and removal sequence with the supplied callback arguments. */
void update_actor_defeat_removal_callback(void *actor, void *motion, void *render, void *context)
{
    update_actor_defeat_removal(actor, motion, render, context);
}
