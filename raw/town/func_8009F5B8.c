#include "common.h"

extern void func_8004491C(s32, void *);
extern u8 D_80046398[];
extern u8 D_80083160[];

void func_8009CD18(s32 arg0, void *arg1, s32 arg2)
{
    u8 *state;

    *(s16 *)((u8 *)arg1 + 0x20) = 0x1000;
    do { *(s16 *)((u8 *)arg1 + 0x1E) = 0x1000; } while (0);
    *(s16 *)((u8 *)arg1 + 0x1C) = 0x1000;
    *(s16 *)((u8 *)arg1 + 0x12) = 0;
    *(s16 *)((u8 *)arg1 + 0x14) = 0;
    *(s16 *)((u8 *)arg1 + 0x10) = 0;
    state = D_80083160;
    *(u8 *)((u8 *)arg1 + 0xC) = state[0xA8];
    *(u8 *)((u8 *)arg1 + 0xD) = state[0xA9];
    *(u8 *)((u8 *)arg1 + 0xE) = state[0xAA];
    *(s16 *)((u8 *)arg1 + 0x14) = 0;
    *(s16 *)((u8 *)arg1 + 0x1A) = 0;
    *(s16 *)((u8 *)arg1 + 0x18) = 0;
    *(s16 *)((u8 *)arg1 + 0x16) = 0;
    *(s32 *)((u8 *)arg1 + 0) = 0;
    *(s8 *)((u8 *)arg1 + 4) = 0;
    *(s8 *)((u8 *)arg1 + 5) = 0;
    func_8004491C(arg0 - 0x20, D_80046398);
    *(s32 *)((u8 *)arg1 + 8) = arg2;
}
