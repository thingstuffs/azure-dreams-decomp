#include "common.h"

extern void func_80099754(void *arg0);
extern s32 D_800D0608[];
extern s32 D_8009AAB8;

void func_8009AA2C(void *arg0, void *arg1) {
    u16 temp_v0;

    *(s32 *)((u8 *)arg1 + 0x14) = (D_800D0608[2] - *(s32 *)((u8 *)arg1 + 8)) / 2;
    temp_v0 = *(u16 *)((u8 *)arg0 + 0xA) - 1;
    *(u16 *)((u8 *)arg0 + 0xA) = temp_v0;
    if ((s16) temp_v0 < 0) {
        *(s32 *)((u8 *)arg1 + 8) = D_800D0608[2];
        func_80099754(arg1);
        *(u16 *)((u8 *)arg0 + 0xA) = 0xA;
        *(s32 **)((u8 *)arg0 + 4) = &D_8009AAB8;
    }
}
