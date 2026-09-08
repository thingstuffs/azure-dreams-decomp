#include "common.h"

extern s16 D_80025924;
extern s32 D_800814A0;

/* Decrement the record counter and set completion flags when it reaches zero. */
void func_818CED78(void *record)
{
    u8 *record_bytes = record;
    u16 counter;

    counter = *(u16 *)(record_bytes + 2);
    D_80025924 = 1;
    counter--;
    *(u16 *)(record_bytes + 2) = counter;
    if ((counter << 16) <= 0) {
        *(u16 *)(record_bytes - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: A long-lived u8 base preserves the retail may-alias load-delay nops.
   Loading the counter before the global store lets that store cover load latency
   and naturally yields the a1 pointer, a0 constant, and v1 counter roles. */
