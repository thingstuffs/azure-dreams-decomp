#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 func_800AD058();

void func_800D9F7C(void *actor, void *motion, void *render, void *context)
{
    func_800AD058(actor, motion, render, context);
}
