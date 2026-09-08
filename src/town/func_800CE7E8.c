#include "common.h"

extern void func_800C2E84(void *arg0, s32 arg1, void *arg2);
extern u8 D_80082660[];
extern u8 D_800CBFAC[];
extern u8 D_800D6A70[];

// Initialize the object, clear its state fields and indexed flag, and set its data pointer.
void func_800CBF48(void *object, s32 unused, s32 initValue) {
    func_800C2E84(object, initValue, D_800D6A70);
    D_80082660[*(s32 *)((u8 *)object + 0x60) * 8] = 0;
    *(s16 *)((u8 *)object + 0x68) = 0;
    *(s16 *)((u8 *)object + 0x6A) = 0;
    *(void **)((u8 *)object + 0x54) = D_800CBFAC;
    *(s16 *)((u8 *)object + 0x6C) = 0;
}
