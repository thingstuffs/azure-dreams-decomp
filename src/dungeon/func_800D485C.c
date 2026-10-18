#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 advance_actor_removal();

void func_800D9FBC(void *actor, void *motion, void *render, void *context)
{
    advance_actor_removal(actor, motion, render, context);
}
