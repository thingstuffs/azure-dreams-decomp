#include "common.h"

extern s32 func_8009B120(void *arg0);
extern void func_8004437C(s32 a0, s32 a1);
extern short func_80053DA8(int a0);
extern u8 D_8009B9BC[];

/* Clear object state, assign the context handler, and trigger effects if the check succeeds. */
void func_8009C1B4(u8 *context, s8 *object, s32 *state)
{
    object[0x15] = 0;
    state[3] = 0;
    state[4] = 0;
    state[5] = 0;
    *(void **)(context + 0x50) = D_8009B9BC;
    if (func_8009B120(context + 0x4C) != 0) {
        func_8004437C(0x26, 0);
        func_80053DA8(0x200);
    }
}
