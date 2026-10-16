/* Relink of matched dungeon/func_800ADA84; every changed retail word is a paired relocation. */
#define func_800B2A60 func_80171400
#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 func_800AC480();
extern void func_80171400();

void func_80174344(void *actor, void *motion, void *render, void *context)
{
    if (func_800AC480(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = func_80171400;
    }
}
