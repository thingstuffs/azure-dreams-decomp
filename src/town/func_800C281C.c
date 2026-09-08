#include "common.h"

extern int func_800478B8(void *arg);
extern int D_800814A0;

/* Updates state and sets local and global flags when either status bit is set. */
void func_800BFF7C(void *flags_end, void *unused, void *state) {
    func_800478B8(state);
    *(s32 *)((s8 *)state + 0xC) += 0xFFEFEFF0;
    if (*(u16 *)((s8 *)state + 0x14) & 0x6000) {
        *(u16 *)((s8 *)flags_end - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
