#include "common.h"

extern void *D_80174704;
extern s32 D_80174928[];
extern s32 *D_80174CCC;
extern s16 D_80174CD0;

/* Initialize the current object state and reset the default table counter. */
void func_8016DF50(void) {
    void *state;

    state = D_80174704;
    if (state != 0) {
        state = (s8 *)state + 0x20;
        *(s8 *)((s8 *)state + 0xB2) = 1;
        *(s16 *)((s8 *)state + 0xAE) = 1;
        D_80174CCC = D_80174928;
        D_80174CD0 = 0;
    }
}
