#include "common.h"

extern void func_800C78A0(void *, s32, s32, s32, s32, s32);
extern u8 D_80082E80[];
extern u8 D_80083478[];
extern void *D_800E3D7C;

void func_80170BC4(void) {
    func_800C78A0(
        D_80083478,
        (D_80082E80[0x24] << 6) | 0x20,
        (D_80082E80[0x25] << 6) | 0x20,
        *(s16 *)((u8 *)D_800E3D7C + 0x88),
        1,
        0x400
    );
}
