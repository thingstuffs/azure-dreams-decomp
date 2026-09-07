#include "common.h"

extern s32 func_800374F4(s32);
extern void func_800C2E84(void *, s32, void *);
extern u8 D_800C7604[];
extern u8 D_800D5FC4[];

void func_800C7A6C(void *arg0, void *arg1, s32 arg2) {
    *(s32 *)((u8 *)arg1 + 0x10) = 0;
    *(s32 *)((u8 *)arg1 + 0xC) = 0;
    func_800C2E84(arg0, arg2, D_800D5FC4);
    *(void **)((u8 *)arg0 + 0x50) = D_800C7604;
    *(s16 *)((u8 *)arg0 + 0x6C) = (s16) (func_800374F4(0x3F) + 0x15);
}
