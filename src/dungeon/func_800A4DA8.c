#include "common.h"

extern s32 D_80083460;

void func_800AA508(void *arg0) {
    u16 *temp_v1;
    s8 *temp_a0;
    s32 *temp_v0;

    do {
        *(s8 *)((s8 *)arg0 + 0x9A) = 3;
        *(s32 *)((s8 *)arg0 + 0x8C) = (*(s8 *)((s8 *)arg0 - -0x9B) = 0);
        temp_v0 = &D_80083460;
        temp_a0 = (s8 *)temp_v0;
        temp_v1 = (u16 *)(temp_a0 + 0xA);
        *(s16 *)((s8 *)arg0 + 0x96) = 4;
    } while (0);

    *temp_v1 = (u16)(*(u16 *)(temp_a0 - -0xA) + 1);
}
