#include "common.h"

extern s32 func_807006AC();
extern s32 D_A0700000[];

__asm__(".set D_A0700000, 0xA0700000");

/* Call func_807006AC when the selected grid entry has bit 0 set. */
void func_808B9348(s32 row, s32 column) {
    if (*(s32 *)((s8 *)D_A0700000 + ((((row * 7) + column) * 8)) + 0xA08) & 1) {
        func_807006AC(0x152);
    }
}
