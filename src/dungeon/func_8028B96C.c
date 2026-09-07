#include "common.h"

extern int D_800E3548[64];

void func_8001E96C(void) {
    s32 i;

    for (i = 0x3F; i >= 0; i--) {
        D_800E3548[i] = 0;
    }
}
