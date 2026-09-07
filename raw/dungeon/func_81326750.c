#include "common.h"

extern void *D_80174704;
extern s32 D_80174928[];
extern s32 *D_80174CCC;
extern s16 D_80174CD0;

void func_8016DF50(void) {
    void *ptr;

    ptr = D_80174704;
    if (ptr != 0) {
        ptr = (s8 *)ptr + 0x20;
        *(s8 *)((s8 *)ptr + 0xB2) = 1;
        *(s16 *)((s8 *)ptr + 0xAE) = 1;
        D_80174CCC = D_80174928;
        D_80174CD0 = 0;
    }
}
