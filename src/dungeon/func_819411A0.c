#include "common.h"

extern s16 D_8002571C;
extern s32 D_800814A0;

/* Decrements the object counter and sets flags when it reaches zero. */
void func_800249A0(void *object)
{
    u8 *object_bytes = object;
    u16 counter;

    counter = *(u16 *)(object_bytes + 42);
    D_8002571C = 1;
    counter--;
    *(u16 *)(object_bytes + 42) = counter;
    if ((counter << 16) <= 0) {
        *(u16 *)(object_bytes - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: A long-lived u8 base preserves the retail may-alias load-delay nops.
   Loading the counter before the global store lets that store cover load latency
   and naturally yields the a1 pointer, a0 constant, and v1 counter roles. */
