#include "common.h"

/* BuildLandBuilding: store the selected palette and preserve the previous common palette. */
void BuildLandBuilding(s32 slot, s16 palette)
{
    s32 palette_offset;

    palette_offset = slot;
    if (palette <= 0) {
        goto common;
    }
    if (palette < 4) {
        goto small;
    }
    if (palette >= 42) {
        goto common;
    }
    if (palette >= 37) {
        goto special;
    }

common:
    {
        u8 *state = (u8 *)0x80010000;
        s32 index = (s16)palette_offset * 2;
        u8 previous_palette;

        state[0x33A5 + index] = (u8)palette;
        previous_palette = state[0x360A];
        state[0x360A] = (u8)palette;
        state[0x360B] = previous_palette;
        return;
    }

small:
    {
        u8 *state = (u8 *)0x80010000;
        s32 index = (slot << 16) >> 15;

        state[0x33A5 + index] = (u8)palette;
        return;
    }

special:
    *(u8 *)0x800133E7 = palette;
}
