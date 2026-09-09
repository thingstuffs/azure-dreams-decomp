#include "common.h"

extern void func_800182A8(s32, s32, s32);
extern void *D_80016000;
extern s32 D_8001691C;
extern s32 *D_80019BB8;
extern s32 D_80019BBC;

void func_8047641C(s32 arg0, s32 arg1, s32 arg2) {
    void *base;

    func_800182A8(arg0, arg1, arg2);
    base = D_80016000;
    D_80019BB8 = &D_8001691C;
    D_80019BBC = *(s32 *)((u8 *)base + 0x40) + 8;
}
