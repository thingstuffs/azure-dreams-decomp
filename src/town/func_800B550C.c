#include "common.h"

extern void func_80033D44(u32 arg0);
extern void func_800A48A4(s32 arg0);
extern void func_800B2A38(void *arg0);
extern void func_800B3A80(s32 arg0);
extern void func_800B46CC(s32 arg0);
extern void func_800B50BC(s32 arg0);
extern s32 D_800814A0[];

void func_800B2C6C(void *arg0)
{
    func_800B3A80(*(s32 *)((s8 *)arg0 + 0));
    func_800B50BC(*(s32 *)((s8 *)arg0 + 4));
    func_800B46CC(*(s32 *)((s8 *)arg0 + 8));
    *(u16 *)((s8 *)arg0 - 2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
    func_800A48A4(3);
    func_80033D44(0);
    func_800B2A38(arg0);
}
