#include "common.h"

extern void func_80047784(void *arg0, s32 arg1, s32 arg2);
extern s16 D_80083228;
extern u8 D_801760B4;

void func_801725C8(void *arg0, void *arg1, void *arg2, void *arg3) {
    *((s8 *)arg0 + 0x9A) = 0x10;
    *((s8 *)arg0 + 0x9B) = 0;
    *(s16 *)((u8 *)arg2 + 0x1C) = 0x1400;
    *(s16 *)((u8 *)arg2 + 0x1E) = 0xC00;
    *(u8 **)((u8 *)arg2 + 0x2C) = &D_801760B4;
    func_80047784(
        arg2,
        *(&D_801760B4 + (((D_80083228 + *(s16 *)((u8 *)arg3 + 0x2A) + 0x100) >> 9) & 7)),
        0);
}
