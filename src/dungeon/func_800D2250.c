#include "common.h"

extern void func_800478B8(void *arg0);
extern s32 D_800814A0;

/* Marks the record when target flags are set, then processes the target. */
void func_800D79B0(u16 *record, void *unused, u16 *target) {
    if (*(u16 *)((u8 *)target + 0x14) & 0x6000) {
        u16 *record_flags = (u16 *)((u8 *)record - 2);
        *record_flags = (u16)(*record_flags | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }
    func_800478B8(target);
}
