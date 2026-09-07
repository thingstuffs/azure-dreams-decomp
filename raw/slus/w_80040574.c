#include "common.h"

/* Bump/ring allocator: returns the current write pointer (D_80081480) and advances it by `size` bytes; resets to the buffer base and syncs the GPU on overflow. */
/* This function's TU is compiled with -G0 (small-data disabled, matching
 * the code5.c / w_8004878C.c family that touches these SAME three globals),
 * so gcc addresses these plain scalars via independent lui/%hi + lw/sw/%lo
 * pairs (no materialised/reused base register), instead of via $gp or an
 * oversized-struct hi/lo forcing trick. */
extern s32 D_8008148C; /* base address of the streaming/scratch ring buffer */
extern s32 D_80080A7C; /* ring buffer's total size */
extern s32 D_80081480; /* running write pointer into the ring buffer */

extern void DrawSync(s32 a0);

void *func_80040574(s32 size)
{
    s32 base = D_8008148C;

    if ((u32)(base + D_80080A7C) <= (u32)(D_80081480 + size)) {
        D_80081480 = base;
        DrawSync(0);
    }
    {
        void *ret = (void *)D_80081480;
        D_80081480 = D_80081480 + size;
        return ret;
    }
}
