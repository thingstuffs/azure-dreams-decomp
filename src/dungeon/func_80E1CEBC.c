/* Relink of matched dungeon/func_800ADAF4; every changed retail word is a paired relocation. */
#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 func_800ACE34();
extern void func_80165094();

void func_801686BC(void *actor, void *motion, void *render, void *context)
{
    if (func_800ACE34(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = func_80165094;
    }
}
