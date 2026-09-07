#include "common.h"

void func_8002675C(void *arg0)
{
    volatile s32 sp0;
    s32 value;

    sp0 = 0x8040F0;
    *(s8 *)((u8 *)arg0 + 1) = 0x28;
    value = sp0;
    *(s8 *)((u8 *)arg0 + 3) = 0x18;
    *(s8 *)((u8 *)arg0 + 0xA) = 7;
    *(s8 *)((u8 *)arg0 + 2) = 0;
    *(s8 *)((u8 *)arg0 + 0xB) = 2;
    *(s32 *)((u8 *)arg0 + 4) = value;
    *(u8 *)arg0 |= 0x80;
}
