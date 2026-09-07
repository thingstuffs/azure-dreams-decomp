#include "common.h"

extern void func_800478B8(void *arg0);
extern s32 D_800814A0;

void func_81892A0C(void *arg0, void *arg1, void *arg2)
{
    void *ptr;
    s32 total;
    s32 value;

    ptr = *(void **)arg0;
    *(u16 *)((u8 *)ptr + 0x14) += 1;
    *(u16 *)((u8 *)arg0 + 4) += 1;

    total = *(s32 *)((u8 *)arg1 + 8);
    value = *(s32 *)((u8 *)arg1 + 0x14);
    *(s32 *)((u8 *)arg1 + 8) = total + value;
    if (*(s16 *)((u8 *)arg0 + 4) < 8) {
        *(s32 *)((u8 *)arg1 + 0x14) *= 2;
    }

    if (*(s16 *)((u8 *)arg0 + 4) == *(s16 *)((u8 *)arg0 + 6)) {
        *(u16 *)((u8 *)arg2 + 0x1E) >>= 1;
    }

    func_800478B8(arg2);

    if (*(s16 *)((u8 *)arg0 + 4) > *(s16 *)((u8 *)arg0 + 6)) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: The 0x18 frame follows from holding arg0 in s0 across the call.
   Ordered accumulators preserve the two lw roles; the compound alias re-read emits move+sll.
   Spelling the final relation as field4 > field6 preserves the retail tail-load order. */
