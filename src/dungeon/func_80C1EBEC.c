/* Relink of matched dungeon/func_800ADAF4; every changed retail word is a paired relocation. */
#define func_800B2A60 func_8016B3A8
#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 func_800ACE34();
extern void func_8016B3A8();

void func_8016E3EC(void *actor, void *motion, void *render, void *context)
{
    if (func_800ACE34(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = func_8016B3A8;
    }
}
