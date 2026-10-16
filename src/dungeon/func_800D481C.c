#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 dungeonUpdateActorDefeatRemoval();

void func_800D9F7C(void *actor, void *motion, void *render, void *context)
{
    dungeonUpdateActorDefeatRemoval(actor, motion, render, context);
}
