#include "common.h"

extern s32 func_80406B9C(void *arg0);
extern s32 func_80406C1C() __attribute__((noreturn));
extern s32 D_80406DA0;

void func_8001FBEC(void *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x38) != 0) {
        *(s32 *)((u8 *)arg0 - 16) = (s32)&D_80406DA0;
        func_80406C1C();
    } else {
        func_80406B9C(arg0);
    }
}
