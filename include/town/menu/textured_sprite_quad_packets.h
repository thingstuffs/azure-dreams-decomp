#ifndef TOWN_MENU_TEXTURED_SPRITE_QUAD_PACKETS_H
#define TOWN_MENU_TEXTURED_SPRITE_QUAD_PACKETS_H

#include "common.h"

/* POLY_FT4 packet built in the frame draw context by draw_textured_sprite_quad. */
typedef struct TexturedSpriteQuadPacket {
    /* 0x00 */ u8 pad_00[0x4];
    /* 0x04 */ s32 color_code;
    /* 0x08 */ u16 x0;
    /* 0x0A */ u16 y0;
    /* 0x0C */ s8 u0;
    /* 0x0D */ s8 v0;
    /* 0x0E */ s16 clut;
    /* 0x10 */ u16 x1;
    /* 0x12 */ u16 y1;
    /* 0x14 */ s8 u1;
    /* 0x15 */ s8 v1;
    /* 0x16 */ s16 tpage;
    /* 0x18 */ u16 x2;
    /* 0x1A */ u16 y2;
    /* 0x1C */ s8 u2;
    /* 0x1D */ s8 v2;
    /* 0x1E */ u8 pad_1E[0x2];
    /* 0x20 */ u16 x3;
    /* 0x22 */ u16 y3;
    /* 0x24 */ s8 u3;
    /* 0x25 */ s8 v3;
} TexturedSpriteQuadPacket;

/* POLY_F4 overlay packet built beside the textured quad in the same frame. */
typedef struct FlatOverlayQuadPacket {
    /* 0x00 */ u8 pad_00[0x4];
    /* 0x04 */ u8 red;
    /* 0x05 */ u8 green;
    /* 0x06 */ u8 blue;
    /* 0x07 */ u8 pad_07;
    /* 0x08 */ u16 x0;
    /* 0x0A */ u16 y0;
    /* 0x0C */ u16 x1;
    /* 0x0E */ u16 y1;
    /* 0x10 */ u16 x2;
    /* 0x12 */ u16 y2;
    /* 0x14 */ u16 x3;
    /* 0x16 */ u16 y3;
} FlatOverlayQuadPacket;

#endif
