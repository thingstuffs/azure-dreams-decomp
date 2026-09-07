#include "common.h"

extern void func_80047784();
extern s16 D_80083208[16];
extern u8 D_8014A000[200000];
#define D_80173C8C_OFF 0x29C8C

void func_80171D3C(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 idx;
    u8 *tbl;

    *((s8 *)arg0 + 0x9A) = 0x10;
    *((s8 *)arg0 + 0x9B) = 0;
    tbl = &D_8014A000[D_80173C8C_OFF];
    *(void **)((u8 *)arg2 + 0x2C) = tbl;
    idx = ((*(s16 *)((u8 *)D_80083208 + 0x20) + *(s16 *)((u8 *)arg3 + 0x2A) + 0x100) >> 9) & 7;
    func_80047784(arg2, tbl[idx], 0);
}
