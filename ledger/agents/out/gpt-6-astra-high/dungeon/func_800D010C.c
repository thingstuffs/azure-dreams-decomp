#include "common.h"

extern s32 D_800814A0[];
extern void func_800478B8(void *arg);

// Updates the object, retains its 0x6000 flags, and marks the preceding and global flags if any remain.
void func_800D586C(void *dataAfterFlags, void *unused, void *object) {
    u16 retainedFlags;

    func_800478B8(object);
    retainedFlags = *(u16 *)((u8 *)object + 0x14) & 0x6000;
    *(u16 *)((u8 *)object + 0x14) = retainedFlags;
    if (retainedFlags != 0) {
        *(u16 *)((u8 *)dataAfterFlags - 2) |= 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
