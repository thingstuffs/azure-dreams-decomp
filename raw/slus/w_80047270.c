#include "common.h"

/* Streaming decode: checks whether the decode buffer (D_80081480) has room for a1's tile byte count against the buffer's base+size (D_8008148C + D_80080A7C); if not, resets the write pointer to the buffer base and waits for the GPU (DrawSync). Then decodes the object's data via func_800407C0, issues a LoadImage of the header via the (possibly reset) buffer, and advances the write pointer past the newly decoded data. */
/* Running write/base pointers into a growing decode buffer, plain 32-bit
 * scalars accessed via %hi/%lo (not $gp-relative) -- same globals as the
 * sibling func_8004878C family (same -G0 TU). */
extern s32 D_80080A7C;
extern s32 D_80081480;
extern s32 D_8008148C;

/* Object header this function operates on: a1 points at a struct whose
 * fields at 0x4/0x6 are s16 tile-dimension counters (same shape as the
 * S_8004878C_hdr sibling). */
typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
} S_80047270_hdr;

extern void DrawSync(s32 a0);
extern void *func_800407C0(void *a0, void *a1);
extern int LoadImage(void *rect, void *p);

void func_80047270(void *a0, S_80047270_hdr *a1)
{
    s32 half;
    s32 product;

    half = a1->unk06 * 2;
    product = a1->unk04 * half;
    if ((u32)(D_8008148C + D_80080A7C) <= (u32)(D_80081480 + product)) {
        D_80081480 = D_8008148C;
        DrawSync(0);
    }
    func_800407C0(a0, (void *)D_80081480);
    LoadImage(a1, (void *)D_80081480);
    half = a1->unk06 * 2;
    product = a1->unk04 * half;
    D_80081480 = D_80081480 + product;
}
