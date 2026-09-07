#include "common.h"

/* This whole TU is compiled with -G0 (small-data disabled), so gcc
 * addresses these plain scalars via independent lui/%hi + lw/sw/%lo pairs
 * (no materialised base register reused across accesses), instead of via
 * $gp. D_80080A7C is a plain int elsewhere too (see code5.c func_8004066C,
 * same -G0 TU). D_80081480/D_8008148C are really running write/base
 * pointers into a growing decode buffer, stored as plain 32-bit values. */
extern s32 D_80080A7C;
extern s32 D_80081480;
extern s32 D_8008148C;

/* Object header this function operates on: rect points at a struct whose
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

/* Decodes and uploads an image, wrapping the decode buffer when needed. */
void func_8004878C(void *src, S_8004878C_hdr *rect)
{
    s32 pixel_count;
    s32 image_bytes;

    pixel_count = rect->unk04 * rect->unk06;
    image_bytes = pixel_count * 2;
    if ((u32)(D_8008148C + D_80080A7C) <= (u32)(D_80081480 + pixel_count * 4 + 2)) {
        D_80081480 = D_8008148C;
        DrawSync(0);
    }
    func_8004068C(src, (void *)(D_80081480 + image_bytes));
    {
        register s32 write_ptr ASM_REG("$5") = D_80081480;   /* MATCH pin: slus-diff */
        func_80048734((void *)(write_ptr + image_bytes));
    }
    LoadImage(rect, (void *)D_80081480);
    D_80081480 = D_80081480 + image_bytes;
}
