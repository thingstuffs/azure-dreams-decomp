#ifndef SHARED_GPU_PACKETS_H
#define SHARED_GPU_PACKETS_H
#include "sdk/libgpu_types.h"

/* Packed-word access for renderers that keep the link mask in a local. */
#define GPU_TAG_LINK(tag, mask) ((tag) & (mask))
#define GPU_SET_TAG_LINK(tag, address, mask) \
    ((tag) = ((tag) & 0xFF000000) | GPU_TAG_LINK((address), (mask)))

/* Textured four-vertex packet. The grid renderer advances its cursor by
 * 0x28, copies four packed XY words, sets four UV pairs and fills the CLUT
 * and texture-page words. The high tag byte is preserved while linking.
 * Word members retain the demonstrated access widths and alignment. */
/* Textured quad built in the current frame context's packet storage, then linked into its ordering table.
 * The grid renderer advances by 0x28 bytes; the packet is valid until that draw context is reused. */
typedef struct PolyFT4 {
    /* 0x00 */ int tag; /* DMA link address/count word; link updates preserve the high length byte */
    /* 0x04 */ int colorCode; /* packed RGB modulation and GPU primitive command byte */
    /* 0x08 */ int xy0; /* vertex 0 packed signed screen X/Y halfwords */
    /* 0x0C */ unsigned char u0; /* vertex 0 texture U coordinate, in texels */
    /* 0x0D */ unsigned char v0; /* vertex 0 texture V coordinate, in texels */
    /* 0x0E */ short clut; /* texture palette identifier for this quad */
    /* 0x10 */ int xy1; /* vertex 1 packed signed screen X/Y halfwords */
    /* 0x14 */ unsigned char u1; /* vertex 1 texture U coordinate, in texels */
    /* 0x15 */ unsigned char v1; /* vertex 1 texture V coordinate, in texels */
    /* 0x16 */ short tpage; /* texture-page and blend-mode bits */
    /* 0x18 */ int xy2; /* vertex 2 packed signed screen X/Y halfwords */
    /* 0x1C */ unsigned char u2; /* vertex 2 texture U coordinate, in texels */
    /* 0x1D */ unsigned char v2; /* vertex 2 texture V coordinate, in texels */
    /* 0x1E */ unsigned char pad_1E[2];
    /* 0x20 */ int xy3; /* vertex 3 packed signed screen X/Y halfwords */
    /* 0x24 */ unsigned char u3; /* vertex 3 texture U coordinate, in texels */
    /* 0x25 */ unsigned char v3; /* vertex 3 texture V coordinate, in texels */
    /* 0x26 */ unsigned char pad_26[2];
} PolyFT4;

enum { GPU_ORDER_DEPTH_BASE = 16 };

/* One of the two frame draw contexts (0x108D4 bytes each, back to back in upper_draw_context), reached through
 * GameWork.draw_buffer. init_double_buffered_gpu_environments fills both environments; each frame
 * render_scene_frame_with_timing applies the current one, draws its ordering table, swaps to the other context,
 * clears that context's ordering table and resets its packet cursor to the start of its packet storage. */
typedef struct GpuContext {
    /* 0x000 */ DRAWENV draw; /* drawing environment, applied by PutDrawEnv */
    /* 0x05C */ DISPENV disp; /* display environment, applied by PutDispEnv */
    /* 0x070 */ unsigned int orderTag[0x218]; /* ordering buckets cleared together by frame setup (ClearOTagR) */
    /* 0x8D0 */ void *packetCursor; /* next free packet byte; reset to packets when reused, then advanced by each packet builder */
    /* 0x8D4 */ unsigned char packets[0x10000]; /* packet storage for one frame */
} GpuContext;

/* The two frame draw contexts, back to back; init_double_buffered_gpu_environments fills them and every frame swap
 * steps between them. */
extern GpuContext upper_draw_context[2];

/* Exact access views shared across registered binary consumers. */
/* Three signed words supplying packed GPU vertex colors; not a position vector. */
typedef struct PacketColorWords {
    int vertex1_color;
    int vertex2_color;
    int vertex3_color;
} PacketColorWords;

/* Three-word display template rooted at D_8002E5E8 and its copied instances. */
/* Three-word auxiliary display template and its caller-owned copies.
 * initialize_text_entity_templates and initialize_menu_backdrop_display_nodes copy display_vector_defaults into it. */
typedef struct DisplayPositionWords {
    int unk0;
    int unk4;
    int unk8;
} DisplayPositionWords;

/* Unsigned display coordinate read from the overlay drawing global. */
typedef struct DisplayXHalfView {
    unsigned short x;
} DisplayXHalfView;

/* Eight-byte screen rectangle: unsigned X/size and signed Y. */
typedef struct GpuRect {
    unsigned short x;
    short y;
    union {
        unsigned int word4;
        struct {
            unsigned short z;
            unsigned short w;
        } half;
    } data;
} GpuRect;

/* Alternate construction views retain the original aligned word stores. */
typedef union GpuRectBuffer {
    int words[2];
    short halves[4];
    GpuRect rect;
} GpuRectBuffer;

#endif
