#include "common.h"

extern void func_800A0B74(void *arg0, s32 arg1);
extern void *D_800A08E8;

void func_800A0884(void *arg0, void *arg1) {
    u16 temp_v0;

    temp_v0 = *(u16 *)((u8 *)arg0 + 0x6E) + 0x40;
    *(u16 *)((u8 *)arg0 + 0x6E) = temp_v0;
    if ((s16) temp_v0 >= 0x400) {
        *(u16 *)((u8 *)arg0 + 0x6E) = 0x400U;
        func_800A0B74(arg0, *(s32 *)((u8 *)arg1 + 0x48));
        *(void **)((u8 *)arg0 + 0x50) = &D_800A08E8;
    }
}
