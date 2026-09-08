#include "common.h"

extern void func_800C2E84(void *arg0, s32 arg1, void *arg2);
extern u8 D_80082660[];
extern u8 D_800C81E4[];
extern u8 D_800D6110[];

// Initializes the object with D_800D6110, clears its status, and sets state 0x62.
void func_800C8248(void *object, s32 unused, s32 initializationArg) {
    *(s32 *)((u8 *)object + 0xA0) = 0;
    func_800C2E84(object, initializationArg, D_800D6110);
    D_80082660[*(s32 *)((u8 *)object + 0x60) * 8] = 0;
    *(void **)((u8 *)object + 0x54) = D_800C81E4;
    *(s16 *)((u8 *)object + 0x6C) = 0x62;
}
