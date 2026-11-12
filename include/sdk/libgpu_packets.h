#ifndef SDK_LIBGPU_PACKETS_H
#define SDK_LIBGPU_PACKETS_H

#include "common.h"

/* POLY_G3 initialized in the frame draw context by SetPolyG3. */
typedef struct POLY_G3 {
    /* 0x00 */ u8 pad_00[4];
    /* 0x04 */ s8 red0;
    /* 0x05 */ s8 green0;
    /* 0x06 */ s8 blue0;
    /* 0x07 */ u8 pad_07;
    /* 0x08 */ s16 x0;
    /* 0x0A */ s16 y0;
    /* 0x0C */ s8 red1;
    /* 0x0D */ s8 green1;
    /* 0x0E */ s8 blue1;
    /* 0x0F */ u8 pad_0F;
    /* 0x10 */ s16 x1;
    /* 0x12 */ s16 y1;
    /* 0x14 */ s8 red2;
    /* 0x15 */ s8 green2;
    /* 0x16 */ s8 blue2;
    /* 0x17 */ u8 pad_17;
    /* 0x18 */ s16 x2;
    /* 0x1A */ s16 y2;
    /* 0x1C */ u8 pad_1C[8];
} POLY_G3;

/* POLY_G4 packet built in the frame draw context and initialized by SetPolyG4. */
typedef struct POLY_G4 {
    /* 0x00 */ u32 tag; /* ordering-table link (low 24 bits) and command-word count (high byte) */
    /* 0x04 */ u8 red0;
    /* 0x05 */ u8 green0;
    /* 0x06 */ u8 blue0;
    /* 0x07 */ u8 code; /* GPU command byte SetPolyG4 writes; bit 1 selects semi-transparency */
    /* 0x08 */ u16 x0;
    /* 0x0A */ u16 y0;
    /* 0x0C */ u8 red1;
    /* 0x0D */ u8 green1;
    /* 0x0E */ u8 blue1;
    /* 0x0F */ u8 pad_0F;
    /* 0x10 */ u16 x1;
    /* 0x12 */ u16 y1;
    /* 0x14 */ u8 red2;
    /* 0x15 */ u8 green2;
    /* 0x16 */ u8 blue2;
    /* 0x17 */ u8 pad_17;
    /* 0x18 */ u16 x2;
    /* 0x1A */ u16 y2;
    /* 0x1C */ u8 red3;
    /* 0x1D */ u8 green3;
    /* 0x1E */ u8 blue3;
    /* 0x1F */ u8 pad_1F;
    /* 0x20 */ u16 x3;
    /* 0x22 */ u16 y3;
} POLY_G4;

/* POLY_F4 overlay packet built beside the textured quad in the same frame. */
typedef struct POLY_F4 {
    /* 0x00 */ u32 tag; /* ordering-table link (low 24 bits) and command-word count (high byte) */
    /* 0x04 */ u8 red;
    /* 0x05 */ u8 green;
    /* 0x06 */ u8 blue;
    /* 0x07 */ u8 code; /* GPU command byte SetPolyF4 writes */
    /* 0x08 */ u16 x0;
    /* 0x0A */ u16 y0;
    /* 0x0C */ u16 x1;
    /* 0x0E */ u16 y1;
    /* 0x10 */ u16 x2;
    /* 0x12 */ u16 y2;
    /* 0x14 */ u16 x3;
    /* 0x16 */ u16 y3;
} POLY_F4;

/* Textured projectile quad allocated at the frame draw context packet cursor by func_800248F8.
 * Each packet occupies 0x28 bytes and is linked into the depth ordering table. */
typedef struct POLY_FT4 {
    u32 tag; /* DMA link/count word; low 24 bits link the ordering-table chain */
    u8 r0; /* red modulation byte, initialized to neutral 0x80 */
    u8 g0; /* green modulation byte, initialized to neutral 0x80 */
    u8 b0; /* blue modulation byte, initialized to neutral 0x80 */
    u8 code; /* GPU textured-quad primitive command byte */
    s16 x0; /* vertex 0 screen X, in pixels */
    s16 y0; /* vertex 0 screen Y, in pixels */
    u8 u0; /* vertex 0 texture U, in texels */
    u8 v0; /* vertex 0 texture V, in texels */
    u16 clut; /* GPU texture palette identifier */
    s16 x1; /* vertex 1 screen X, in pixels */
    s16 y1; /* vertex 1 screen Y, in pixels */
    u8 u1; /* vertex 1 texture U, in texels */
    u8 v1; /* vertex 1 texture V, in texels */
    u16 tpage; /* GPU texture-page and blend-mode bits */
    s16 x2; /* vertex 2 screen X, in pixels */
    s16 y2; /* vertex 2 screen Y, in pixels */
    u8 u2; /* vertex 2 texture U, in texels */
    u8 v2; /* vertex 2 texture V, in texels */
    u16 pad2;
    s16 x3; /* vertex 3 screen X, in pixels */
    s16 y3; /* vertex 3 screen Y, in pixels */
    u8 u3; /* vertex 3 texture U, in texels */
    u8 v3; /* vertex 3 texture V, in texels */
    u16 pad3;
} POLY_FT4;

/* Psy-Q POLY_GT4: Gouraud-shaded textured quad (SetPolyGT4 sets its 0xC-word tag length and code).
 * The screen coordinates are unsigned like POLY_G4's: an opposite-sign trial in
 * transform_sprite_parts_to_quads needs 4 value casts that way (the two signed seam compares) and 8 signed. */
typedef struct POLY_GT4 {
    /* 0x00 */ u32 tag; /* ordering-table link (low 24 bits) and command-word count (high byte) */
    /* 0x04 */ u8 r0;
    /* 0x05 */ u8 g0;
    /* 0x06 */ u8 b0;
    /* 0x07 */ u8 code; /* GPU command byte; bit 1 selects semi-transparency */
    /* 0x08 */ u16 x0;
    /* 0x0A */ u16 y0;
    /* 0x0C */ u8 u0;
    /* 0x0D */ u8 v0;
    /* 0x0E */ u16 clut;
    /* 0x10 */ u8 r1;
    /* 0x11 */ u8 g1;
    /* 0x12 */ u8 b1;
    /* 0x13 */ u8 p1;
    /* 0x14 */ u16 x1;
    /* 0x16 */ u16 y1;
    /* 0x18 */ u8 u1;
    /* 0x19 */ u8 v1;
    /* 0x1A */ u16 tpage;
    /* 0x1C */ u8 r2;
    /* 0x1D */ u8 g2;
    /* 0x1E */ u8 b2;
    /* 0x1F */ u8 p2;
    /* 0x20 */ u16 x2;
    /* 0x22 */ u16 y2;
    /* 0x24 */ u8 u2;
    /* 0x25 */ u8 v2;
    /* 0x26 */ u16 pad2;
    /* 0x28 */ u8 r3;
    /* 0x29 */ u8 g3;
    /* 0x2A */ u8 b3;
    /* 0x2B */ u8 p3;
    /* 0x2C */ u16 x3;
    /* 0x2E */ u16 y3;
    /* 0x30 */ u8 u3;
    /* 0x31 */ u8 v3;
    /* 0x32 */ u16 pad3;
} POLY_GT4;

/* Psy-Q TILE_1: a one-pixel flat tile (tag length 2; GPU code 0x68, bit 1 selects semi-transparency). */
typedef struct TILE_1 {
    /* 0x00 */ u32 tag; /* ordering-table link (low 24 bits) and command-word count (high byte) */
    /* 0x04 */ u8 r0;
    /* 0x05 */ u8 g0;
    /* 0x06 */ u8 b0;
    /* 0x07 */ u8 code;
    /* 0x08 */ s16 x0;
    /* 0x0A */ s16 y0;
} TILE_1;

#endif
