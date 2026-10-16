/* Relink of matched dungeon/func_800AD92C; every changed retail word is a paired relocation. */
#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 func_800AB778();

void func_80150BAC(void *actor, void *motion, void *render, void *context)
{
    func_800AB778(actor, motion, render, context);
}
