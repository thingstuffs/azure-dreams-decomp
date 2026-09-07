#include "common.h"

extern s32 memset();
extern s32 D_800CFCB4;

void func_8008EF58(void) {
    s32 *base = &D_800CFCB4;
    void *ptr = base;

    memset(ptr, 0, 0x4C);
    *base = (s32)ptr;
    *(void **)((u8 *)ptr + 4) = ptr;
}
