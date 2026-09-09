#include "common.h"

extern s32 D_800D0460;
extern void SD_Call(s32);

/* Dispatch code 0x518 or 0x50A according to the global flag. */
void func_800948DC(void) {
    if (D_800D0460 != 0) {
        SD_Call(0x518);
        return;
    }
    SD_Call(0x50A);
}
