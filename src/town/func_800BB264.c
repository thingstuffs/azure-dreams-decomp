#include "common.h"

/* BuildLandBuilding: store the selected palette and preserve the previous common palette. */
void BuildLandBuilding(s32 slot, s16 palette)
{
    s32 palette_offset = slot;

    switch (palette) {
    default:
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
    case 1:
    case 2:
    case 3:
        {
            u8 *state = (u8 *)0x80010000;
            s32 index = (slot << 16) >> 15;

            state[0x33A5 + index] = (u8)palette;
            return;
        }
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
        *(u8 *)0x800133E7 = palette;
        return;
    }
}
