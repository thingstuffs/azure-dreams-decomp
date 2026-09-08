#include "common.h"

/* Decodes a1's tile-count fields into a pixel/word count, checks whether the streaming decode buffer (D_80081480) has room for it against the buffer's base+size (D_8008148C + D_80080A7C); if not, resets the write pointer to the buffer base and waits for the GPU (DrawSync). It then decodes the object's data (func_8004068C / func_80048734), issues a LoadImage of the header via the (possibly reset) buffer, and finally advances the write pointer past the newly decoded data. */
/* This whole TU is compiled with -G0 (small-data disabled), so gcc
 * addresses these plain scalars via independent lui/%hi + lw/sw/%lo pairs
 * (no materialised base register reused across accesses), instead of via
 * $gp. D_80080A7C is a plain int elsewhere too (see code5.c func_8004066C,
 * same -G0 TU). D_80081480/D_8008148C are really running write/base
 * pointers into a growing decode buffer, stored as plain 32-bit values. */
extern s32 D_80080A7C;
extern s32 D_80081480;
extern s32 D_8008148C;

/* Object header this function operates on: a1 points at a struct whose
 * fields at 0x4/0x6 are s16 tile-dimension counters. */
typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
} S_8004878C_hdr;

extern void DrawSync(s32 a0);
/* RLE-style byte decoder; only the argument setup (src/dst pointers) needs
 * to match, so declare it minimally. */
extern void *func_8004068C(void *a0, void *a1);
extern void func_80048734(void *a0);
extern int LoadImage(void *rect, void *p);

void func_8004878C(void *a0, S_8004878C_hdr *a1)
{
    s32 product;
    s32 half;

    product = a1->unk04 * a1->unk06;
    half = product * 2;
    if ((u32)(D_8008148C + D_80080A7C) <= (u32)(D_80081480 + product * 4 + 2)) {
        D_80081480 = D_8008148C;
        DrawSync(0);
    }
    func_8004068C(a0, (void *)(D_80081480 + half));
    {
        register s32 t ASM_REG("$5") = D_80081480;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        func_80048734((void *)(t + half));
    }
    LoadImage(a1, (void *)D_80081480);
    D_80081480 = D_80081480 + half;
}
