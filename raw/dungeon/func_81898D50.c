#include "common.h"

extern void func_800478B8(void *arg0);
extern s32 D_800814A0;

void func_80024550(void *arg0, s32 arg1, void *arg2) {
    u8 *obj;

    obj = *(u8 **)((u8 *)arg0 + 0x0);
    *(u16 *)(obj + 0x14) += 1;
    func_800478B8(arg2);
    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x6000) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
