#include "common.h"

extern s32 func_80406B9C(void *ptr);
extern s32 D_80406DA0;

void func_80406BEC(void *ptr) {
    if (*(s32 *)((u8 *)ptr + 0x38) != 0) {
        *(s32 *)((u8 *)ptr - 16) = (s32)&D_80406DA0;
        return;
    } else {
        func_80406B9C(ptr);
    }
}
