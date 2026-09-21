#include "common.h"

extern s8 D_800133E7[9];

/* BuildLandBuilding: store the selected palette and preserve the previous common palette. */
void BuildLandBuilding(s32 slot, s16 palette)
{
    s32 palette_offset;
    s32 small_offset;

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
        register u8 *state ASM_REG("$2") = (u8 *)0x80010000;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        u8 previous_palette;

        ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        palette_offset = (s16)palette_offset * 2;
        state[0x33A5 + palette_offset] = (u8)palette;
        previous_palette = state[0x360A];
        state[0x360A] = (u8)palette;
        state[0x360B] = previous_palette;
        return;
    }

small:
    {
        u8 *state = (u8 *)0x80010000;

        small_offset = slot << 16;
        ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        small_offset >>= 15;
        state[0x33A5 + small_offset] = (u8)palette;
        return;
    }

special:
    D_800133E7[0] = (u8)palette;
}

