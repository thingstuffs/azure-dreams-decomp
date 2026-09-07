#include "common.h"

extern void func_800478B8(void *arg0);
extern s32 D_800814A0[3];

void func_800241D8(void *arg0, void *unused, void *arg2)
{
    void *object;

    object = *(void **)arg0;
    *(u16 *)((u8 *)object + 0x14) += 1;
    *(u16 *)((u8 *)arg0 + 4) += 1;
    func_800478B8(arg2);
    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x6000) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
