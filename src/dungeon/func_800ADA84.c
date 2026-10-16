#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 dungeonInterpolateActorToTerrainTile();
extern void dungeonDispatchTargetAction();

void func_800B31E4(void *actor, void *motion, void *render, void *context)
{
    if (dungeonInterpolateActorToTerrainTile(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = dungeonDispatchTargetAction;
    }
}
