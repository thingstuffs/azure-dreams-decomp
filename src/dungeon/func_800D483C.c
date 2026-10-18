#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 update_actor_hop_and_shrink();

void func_800D9F9C(void *actor, void *motion, void *render, void *context)
{
    update_actor_hop_and_shrink(actor, motion, render, context);
}
