#include "common.h"

extern u16 D_80017AA0[8];

/* Increment the first 16-bit counter in D_80017AA0. */
void func_8054FA70(void) {
    D_80017AA0[0] = (u16)(D_80017AA0[0] + 1);
}
