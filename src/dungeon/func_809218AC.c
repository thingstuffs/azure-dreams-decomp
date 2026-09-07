#include "common.h"

extern int D_800814A0[];
extern void func_800478B8(void *);

void func_809218AC(s16 *arg0, s32 *arg1, u16 *arg2) {
    *(s32 *)((u8 *)arg1 + 8) += 0xFFFE8000;
    func_800478B8(arg2);
    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x6000) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
