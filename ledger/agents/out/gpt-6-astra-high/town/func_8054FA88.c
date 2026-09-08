#include "common.h"

extern u16 D_80017AA0[];

/* Decrements the first value in D_80017AA0. */
void func_80016288(void) {
    D_80017AA0[0]--;
}
