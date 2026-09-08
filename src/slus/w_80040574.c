#include "common.h"

/* This function's TU is compiled with -G0 (small-data disabled, matching
 * the code5.c / w_8004878C.c family that touches these SAME three globals),
 * so gcc addresses these plain scalars via independent lui/%hi + lw/sw/%lo
 * pairs (no materialised/reused base register), instead of via $gp or an
 * oversized-struct hi/lo forcing trick. */
extern s32 D_8008148C; /* base address of the streaming/scratch ring buffer */
extern s32 D_80080A7C; /* ring buffer's total size */
extern s32 D_80081480; /* running write pointer into the ring buffer */

extern void DrawSync(s32 a0);

/* Allocates ring buffer space, wrapping and syncing the GPU when the request reaches the buffer end. */
void *func_80040574(s32 size)
{
    s32 buffer_base = D_8008148C;

    if ((u32)(buffer_base + D_80080A7C) <= (u32)(D_80081480 + size)) {
        D_80081480 = buffer_base;
        DrawSync(0);
    }
    {
        void *allocation = (void *)D_80081480;
        D_80081480 = D_80081480 + size;
        return allocation;
    }
}
