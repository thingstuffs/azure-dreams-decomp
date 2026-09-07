#include "common.h"

extern s32 func_807006AC();
extern s32 D_A0700000[];

__asm__(".set D_A0700000, 0xA0700000");

void func_808B9348(s32 arg0, s32 arg1) {
    if (*(s32 *)((s8 *)D_A0700000 + ((((arg0 * 7) + arg1) * 8)) + 0xA08) & 1) {
        func_807006AC(0x152);
    }
}
