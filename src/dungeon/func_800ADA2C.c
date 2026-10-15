#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 func_800AC82C();

void func_800B318C(void *actor, void *motion, void *render, void *context)
{
    func_800AC82C(actor, motion, render, context);
}
