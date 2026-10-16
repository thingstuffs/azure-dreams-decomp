#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 dungeonUpdateActorHopAndShrink();

void func_800D9F9C(void *actor, void *motion, void *render, void *context)
{
    dungeonUpdateActorHopAndShrink(actor, motion, render, context);
}
