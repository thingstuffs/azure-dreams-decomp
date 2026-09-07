#include "common.h"

extern void func_80047784();
extern s32 func_800A2B5C();
extern void func_800A4ACC();
extern void func_800C7930();
extern s16 D_80083208[16];
extern u16 D_80083460[4];
extern u8 D_8014A000[200000];
#define D_801764A0_OFF 0x2C4A0

void func_8017272C(void *arg0, s32 arg1, void *arg2, void *arg3) {
    u8 *tbl;
    s32 idx;

    *((u8 *)arg3 + 0x71) = (u8)(*((u8 *)arg3 + 0x71) & 0x7F);
    if (!(*(u16 *)((u8 *)D_80083460 + 2) & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
        {
            void *t = (u8 *)arg3 - 0x20;
            func_800C7930(t, arg1, 8, 0x300);
        }
        if ((func_800A2B5C(arg3) << 0x10) == 0) {
            *((s8 *)arg0 + 0x9A) = 0x17;
            *(s32 *)((u8 *)arg0 + 0x8C) = 0;
            *((s8 *)arg0 + 0x9B) = 0;
            tbl = &D_8014A000[D_801764A0_OFF];
            *(void **)((u8 *)arg2 + 0x2C) = tbl;
            idx = ((*(s16 *)((u8 *)D_80083208 + 0x20) + *(s16 *)((u8 *)arg3 + 0x2A) + 0x100) >> 9) & 7;
            func_80047784(arg2, tbl[idx], 0);
            func_800A4ACC(arg3);
            *((u8 *)arg3 + 0x6D) = (u8)(*((u8 *)arg3 + 0x6D) - 1);
            *(u16 *)((u8 *)arg0 + 0x98) = (u16)(*(u16 *)((u8 *)arg0 + 0x98) | 8);
        }
    }
}
