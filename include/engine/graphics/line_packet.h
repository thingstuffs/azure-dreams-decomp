#ifndef ENGINE_GRAPHICS_LINE_PACKET_H
#define ENGINE_GRAPHICS_LINE_PACKET_H
#include "common.h"
/* Sixteen-byte horizontal line packet. Its DMA length byte and full link word
 * are both written before the packet joins the frame ordering table. */
typedef struct ShadedLinePacket {
    union { u32 word; struct { u8 pad_00[3]; u8 len; } bytes; } tag;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
} ShadedLinePacket;
#endif
