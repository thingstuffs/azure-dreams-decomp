#include "common.h"

/* Running write/base pointers into a growing decode buffer, plain 32-bit
 * scalars accessed via %hi/%lo (not $gp-relative) -- same globals as the
 * sibling func_8004878C family (same -G0 TU). */
extern s32 D_80080A7C;
extern s32 D_80081480;
extern s32 D_8008148C;

/* Object header this function operates on: image_rect points at a struct whose
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

/* Decodes and uploads an image, wrapping the decode buffer and waiting for the GPU when full. */
void func_80047270(void *encoded_data, S_80047270_hdr *image_rect)
{
    s32 height_bytes;
    s32 image_bytes;

    height_bytes = image_rect->unk06 * 2;
    image_bytes = image_rect->unk04 * height_bytes;
    if ((u32)(D_8008148C + D_80080A7C) <= (u32)(D_80081480 + image_bytes)) {
        D_80081480 = D_8008148C;
        DrawSync(0);
    }
    func_800407C0(encoded_data, (void *)D_80081480);
    LoadImage(image_rect, (void *)D_80081480);
    height_bytes = image_rect->unk06 * 2;
    image_bytes = image_rect->unk04 * height_bytes;
    D_80081480 = D_80081480 + image_bytes;
}
