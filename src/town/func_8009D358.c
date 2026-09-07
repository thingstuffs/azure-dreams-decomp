#include "common.h"

extern void func_80099754(void *arg0);
extern s32 D_800D0608[];
extern u32 D_8009AB74;

void func_8009AAB8(void *arg0, void *arg1)
{
    u16 temp_v0;

    *(u16 *)((u8 *)arg0 + 0x10) += 0x200;
    *(s32 *)((u8 *)arg1 + 0xC) =
        (D_800D0608[0] - *(s32 *)((u8 *)arg1 + 0)) / 2;
    *(s32 *)((u8 *)arg1 + 0x10) =
        (D_800D0608[1] - *(s32 *)((u8 *)arg1 + 4)) / 2;
    temp_v0 = *(u16 *)((u8 *)arg0 + 0xA) - 1;
    *(u16 *)((u8 *)arg0 + 0xA) = temp_v0;
    if ((s16)temp_v0 < 0) {
        *(s32 *)((u8 *)arg1 + 0) = D_800D0608[0];
        *(s32 *)((u8 *)arg1 + 4) = D_800D0608[1];
        func_80099754(arg1);
        *(s32 **)((u8 *)arg0 + 4) = &D_8009AB74;
        *(u16 *)((u8 *)arg0 + 0x10) = 0;
    }
}
