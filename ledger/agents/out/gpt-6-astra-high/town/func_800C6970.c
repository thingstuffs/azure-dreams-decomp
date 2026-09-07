#include "common.h"

extern s32 D_800C3960;
s16 func_800C2BE8(void *arg0);
void func_800C4174(void *arg0, s32 arg1, s32 arg2);

// Initialize the object's state and delegate the remaining setup.
void func_800C40D0(void *object, s32 setupParam1, s32 setupParam2) {
    *(s8 *)((u8 *)object + 0x15) = 0;
    *(void **)((u8 *)object + 0x50) = &D_800C3960;
    *(s16 *)((u8 *)object + 0x72) = func_800C2BE8(object);
    func_800C4174(object, setupParam1, setupParam2);
}
