#include "common.h"

extern int D_800E3648[64];

void func_8001F32C(void) {
    s32 i;

    for (i = 0x1F; i >= 0; i--) {
        D_800E3648[i] = 0;
    }
}
