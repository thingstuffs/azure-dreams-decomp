/* Relink of matched dungeon/func_800AD94C; every changed retail word is a paired relocation. */
#define func_800B2A60 func_8015F4D4
#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 func_800ABDBC();
extern void func_8015F4D4();

void func_801615D4(void *actor, void *motion, void *render, void *context)
{
    if (func_800ABDBC(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = func_8015F4D4;
    }
}
