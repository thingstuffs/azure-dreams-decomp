#include "common.h"

extern s16 func_800A20D8();
extern s32 D_800A0C30;

void func_800A0BE4(void *arg0) {
    s16 temp_v0;
    s32 unk;

    temp_v0 = func_800A20D8(arg0, *(s32 *)((u8 *)arg0 + 0x98), unk, *(s16 *)((u8 *)arg0 + 0x90));
    *(s16 *)((u8 *)arg0 + 0x90) = temp_v0;
    if ((temp_v0 << 0x10) == 0) {
        *(void **)((u8 *)arg0 + 0x50) = &D_800A0C30;
    }
}
