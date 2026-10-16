/* Relink of matched dungeon/func_800ADABC; every changed retail word is a paired relocation. */
#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 func_800AC5C8();
extern void func_8016AE70();

void func_8016DEC8(void *actor, void *motion, void *render, void *context)
{
    if (func_800AC5C8(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = func_8016AE70;
    }
}
