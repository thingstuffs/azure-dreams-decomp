#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 func_800AB778();

void func_800B308C(void *actor, void *motion, void *render, void *context)
{
    func_800AB778(actor, motion, render, context);
}
