#include "common.h"

extern s32 func_800478B8();
extern s32 D_800814A0[3];

void func_8185C98C(void *arg0, void *unused, void *arg2) {
    void *object;
    u16 value;

    object = *(void **)arg0;
    *(u16 *)((u8 *)object + 0x14) =
        (u16)(*(u16 *)((u8 *)object + 0x14) + 1);
    value = *(u16 *)((u8 *)arg2 + 0x1E) + 0x800;
    *(u16 *)((u8 *)arg2 + 0x1E) = value;
    *(u16 *)((u8 *)arg2 + 0x1C) = value;
    func_800478B8(arg2);
    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x6000) {
        *(u16 *)((u8 *)arg0 - 2) =
            (u16)(*(u16 *)((u8 *)arg0 - 2) | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
}
