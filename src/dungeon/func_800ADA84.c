#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 func_800AC480();
extern void func_800B2A60();

void func_800B31E4(void *actor, void *motion, void *render, void *context)
{
    if (func_800AC480(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = func_800B2A60;
    }
}
