/* Relink of matched dungeon/func_800D481C; every changed retail word is a paired relocation. */
#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 dungeonUpdateActorDefeatRemoval();

void func_80173568(void *actor, void *motion, void *render, void *context)
{
    dungeonUpdateActorDefeatRemoval(actor, motion, render, context);
}
