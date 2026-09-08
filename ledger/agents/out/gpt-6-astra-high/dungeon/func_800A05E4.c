#include "common.h"

extern s32 D_8001362C;
extern u16 D_8008347E;

/* Copy D_8008347E into the 32-bit value D_8001362C. */
void func_800A5D44(void) {
    D_8001362C = (s32) D_8008347E;
}
