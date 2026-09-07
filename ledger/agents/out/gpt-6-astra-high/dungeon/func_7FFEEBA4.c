#include "common.h"

extern int D_800814A0[];
extern void func_8008C28C(s32);
extern s32 D_800CFCA8;

// Processes the current counter value, increments it, and sets completion flags at 128.
void func_8008C304(void *counterPtr) {
    s32 nextCounter;

    func_8008C28C(*(s32 *)counterPtr);
    nextCounter = *(s32 *)counterPtr + 1;
    *(s32 *)counterPtr = nextCounter;
    if (nextCounter >= 0x80) {
        ((u16 *)counterPtr)[-1] |= 0x8000;
        D_800CFCA8 = 0;
        D_800814A0[0] |= 0x8000;
    }
}
