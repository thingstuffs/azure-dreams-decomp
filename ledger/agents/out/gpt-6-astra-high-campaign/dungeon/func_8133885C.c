#include "common.h"

extern u16 D_80016000[8];
extern void func_80041344(void *arg0, s32 arg1);

/* Update the shared data for mode one and pass it to the handler. */
void func_8016F85C(s32 mode)
{
    if (mode == 1) {
        D_80016000[4] += 0x40;
    }
    func_80041344(D_80016000, 0);
}
