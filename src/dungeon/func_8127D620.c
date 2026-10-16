/* Relink of matched dungeon/func_800D481C at file 0xF481C; imports and data use paired retail relocations. */
#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 func_800ABD10();

void func_80171E20(void *actor, void *motion, void *render, void *context)
{
    func_800ABD10(actor, motion, render, context);
}
