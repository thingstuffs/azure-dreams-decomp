#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 dungeonUpdateActorFadeIn();
extern void dungeonDispatchTargetAction();

void func_800B3254(void *actor, void *motion, void *render, void *context)
{
    if (dungeonUpdateActorFadeIn(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = dungeonDispatchTargetAction;
    }
}
