#include "common.h"

extern void func_800478B8(s32);
extern struct { s32 unk0; s32 pad[2]; } D_800814A0;

void func_800B21B8(void *arg0, void *arg1, s32 arg2) {
    s16 temp;

    *((s32 *) arg1 + 2) = *((s32 *) arg1 + 2) + 0x8000;
    func_800478B8(arg2);
    temp = *(u16 *) ((u8 *) arg0 + 6) - 1;
    *(u16 *) ((u8 *) arg0 + 6) = temp;
    if (temp < 0) {
        *(u16 *) ((u8 *) arg0 - 2) |= 0x8000;
        D_800814A0.unk0 = D_800814A0.unk0 | 0x8000;
    }
}
