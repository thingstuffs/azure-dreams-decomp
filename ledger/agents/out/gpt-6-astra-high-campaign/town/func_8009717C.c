#include "common.h"

extern s32 D_800D0460;
extern void func_80053DA8(s32);

/* Dispatch code 0x518 or 0x50A according to the global flag. */
void func_800948DC(void) {
    if (D_800D0460 != 0) {
        func_80053DA8(0x518);
        return;
    }
    func_80053DA8(0x50A);
}
