#ifndef ENGINE_GRAPHICS_SPRITE_PACKET_H
#define ENGINE_GRAPHICS_SPRITE_PACKET_H
#include "common.h"
#include "shared/gpu_packets.h"
/* The settings renderer emits 0x14-byte textured sprites with these access
 * widths before linking their tags into the ordering table. */
typedef struct TexturedSpritePacket {
    GpuLinkTag tag;
    s32 color_code;
    s16 x;
    s16 y;
    union { s16 packed; struct { u8 u; u8 v; } bytes; } texture;
    u16 clut;
    s16 width;
    s16 height;
} TexturedSpritePacket;
#endif
