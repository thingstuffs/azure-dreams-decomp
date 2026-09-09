#include "common.h"

extern s8 D_800133E7[9];

/* BuildLandBuilding: store the selected palette and preserve the previous common palette. */
void BuildLandBuilding(s32 slot, s32 palette)
{
    s32 raw_palette = palette;
    register s32 signed_palette ASM_REG("$5") = palette;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 palette_offset;
    s32 small_offset;

    ASM_KEEP(signed_palette);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    signed_palette = (s16)signed_palette;
    palette_offset = slot;
    if (signed_palette <= 0) {
        goto common;
    }
    if (signed_palette < 4) {
        goto small;
    }
    if (signed_palette >= 42) {
        goto common;
    }
    if (signed_palette >= 37) {
        goto special;
    }

common:
    {
        register u8 *state ASM_REG("$2") = (u8 *)0x80010000;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        u8 previous_palette;

        ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        palette_offset = (s16)palette_offset * 2;
        state[0x33A5 + palette_offset] = (u8)raw_palette;
        previous_palette = state[0x360A];
        state[0x360A] = (u8)raw_palette;
        state[0x360B] = previous_palette;
        return;
    }

small:
    {
        u8 *state = (u8 *)0x80010000;

        small_offset = slot << 16;
        ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        small_offset >>= 15;
        state[0x33A5 + small_offset] = (u8)raw_palette;
        return;
    }

special:
    ASM_KEEP(signed_palette);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    D_800133E7[0] = (u8)raw_palette;
}

