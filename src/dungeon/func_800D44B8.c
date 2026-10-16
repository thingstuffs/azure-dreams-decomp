#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 dungeonUpdateLinkedActorMotion(void *, void *, void *, void *);
extern s32 dungeonCheckActorFloorTrap();
extern void dungeonUpdateActorFacingAnimation();

void func_800D9C18(void *actor, void *motion, void *render, void *context)
{
    if (dungeonUpdateLinkedActorMotion(actor, motion, render, context) &&
        ((s16)dungeonCheckActorFloorTrap(render, context) > 0)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = dungeonUpdateActorFacingAnimation;
    }
}
