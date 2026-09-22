#include "common.h"

extern s32 func_80406B9C(void *arg0);
extern s32 D_80406DA0;

void func_80406BEC(void *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x38) != 0) {
        *(s32 *)((u8 *)arg0 - 16) = (s32)&D_80406DA0;
        return;
    } else {
        func_80406B9C(arg0);
    }
}
