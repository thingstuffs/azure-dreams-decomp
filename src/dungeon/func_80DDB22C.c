/* Relink of matched dungeon/func_800ADAF4; every changed retail word is a paired relocation. */
#define func_800B2A60 func_80153E20
#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 func_800ACE34();
extern void func_80153E20();

void func_80156A2C(void *actor, void *motion, void *render, void *context)
{
    if (func_800ACE34(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = func_80153E20;
    }
}
