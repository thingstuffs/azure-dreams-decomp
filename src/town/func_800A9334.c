#include "common.h"
#ifndef NULL
#define NULL 0
#endif

extern void *func_8009C390(s32, s32, void *, s32);
extern void *func_8009CD18(void *, void *, s32);
extern s32 D_800A6B10;

void func_800A6A94(s32 arg0) {
    s8 *temp_s0;
    s8 *temp_v0;

    temp_v0 = (s8 *) func_8009C390(0, arg0, &D_800A6B10, 0);
    if (temp_v0 != NULL) {
        temp_s0 = *(s8 **)(temp_v0 + 0xC);
        func_8009CD18(temp_v0 + 0x20, temp_s0, 0x3A1);
        *(s16 *)(temp_s0 + 0x20) = 0xC00;
        *(s16 *)(temp_s0 + 0x1E) = 0xC00;
        *(s16 *)(temp_s0 + 0x1C) = 0xC00;
        *(u8 *)(temp_s0 + 0xE) = 0xFF;
        *(u8 *)(temp_s0 + 0xD) = 0xFF;
        *(u8 *)(temp_s0 + 0xC) = 0xFF;
        *(u16 *)(temp_s0 + 0x14) = (u16) (*(u16 *)(temp_s0 + 0x14) | 0x1C);
    }
}
