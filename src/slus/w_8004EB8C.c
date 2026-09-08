#include "common.h"

/* func_8003E4FC(kind, callback, arg) - registers a callback in some table */
extern s32 func_8003E4FC(s32 a0, void *a1, void *a2);
extern void func_8003E140(u8 *a0);
extern u8 D_80071644;

/* Clears the state byte and registers two callbacks, binding the default handler to it. */
void func_8004EB8C(u8 *state)
{
    *state = 0;
    func_8003E4FC(6, &D_80071644, 0);
    func_8003E4FC(0xFF, func_8003E140, state);
}
