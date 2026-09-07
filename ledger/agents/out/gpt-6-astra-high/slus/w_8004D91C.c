#include "common.h"

extern void func_8004D8F0(s32 arg0, u8 *arg1);

/* Converts the selected rectangle to VRAM coordinates and dimensions. */
void func_8004D91C(s32 rect_id, s16 *vram_rect)
{
    u8 source_rect[4];

    func_8004D8F0(rect_id & 0xFF, source_rect);
    vram_rect[0] = (s16)((source_rect[0] >> 2) + 0x3C0);
    vram_rect[1] = (s16)(source_rect[1] + 0x100);
    vram_rect[2] = (s16)(source_rect[2] >> 2);
    vram_rect[3] = (s16)source_rect[3];
}
