#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 func_800AB378(void *, void *, void *, void *);
extern s32 func_800AD9B4();
extern void func_800D8C64();

void func_800D9C18(void *actor, void *motion, void *render, void *context)
{
    if (func_800AB378(actor, motion, render, context) &&
        ((s16)func_800AD9B4(render, context) > 0)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = func_800D8C64;
    }
}
