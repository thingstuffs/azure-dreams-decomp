/* Relink of matched dungeon/func_800AD94C; every changed retail word is a paired relocation. */
#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 func_800ABDBC();
extern void func_8015FA80();

void func_801623A4(void *actor, void *motion, void *render, void *context)
{
    if (func_800ABDBC(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = func_8015FA80;
    }
}
