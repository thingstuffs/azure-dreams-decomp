#ifndef TOWN_MENU_FLICKERING_TRIANGLE_PACKET_H
#define TOWN_MENU_FLICKERING_TRIANGLE_PACKET_H

#include "common.h"

/* POLY_G3 initialized in the frame draw context by SetPolyG3. */
typedef struct FlickeringTrianglePacket {
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
} FlickeringTrianglePacket;

#endif
