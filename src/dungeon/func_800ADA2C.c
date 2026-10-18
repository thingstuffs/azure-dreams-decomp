#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 update_actor_transform_from_parent();

void update_actor_transform_from_parent_callback(void *actor, void *motion, void *render, void *context)
{
    update_actor_transform_from_parent(actor, motion, render, context);
}
