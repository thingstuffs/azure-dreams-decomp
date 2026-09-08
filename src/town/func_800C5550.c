#include "common.h"

extern s32 func_8003DB94();
extern s32 func_80047784(int, short, short);

void func_800C2CB0(void *arg0, int arg1, int arg2, s16 arg3) {
    *(s8 *)((s8 *)arg0 + 0x92) = 0;
    if (*(u8 *)((s8 *)arg0 + 0x93) == 0) {
        func_8003DB94(arg1, arg2, arg3);
        return;
    } else {
        func_80047784(arg1, arg2, arg3);
    }
}
