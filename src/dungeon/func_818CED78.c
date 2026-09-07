#include "common.h"

extern s16 D_80025924;
extern s32 D_800814A0;

void func_818CED78(void *arg0)
{
    u8 *ptr = arg0;
    u16 value;

    value = *(u16 *)(ptr + 2);
    D_80025924 = 1;
    value--;
    *(u16 *)(ptr + 2) = value;
    if ((value << 16) <= 0) {
        *(u16 *)(ptr - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: A long-lived u8 base preserves the retail may-alias load-delay nops.
   Loading the counter before the global store lets that store cover load latency
   and naturally yields the a1 pointer, a0 constant, and v1 counter roles. */
