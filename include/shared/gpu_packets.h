#ifndef SHARED_GPU_PACKETS_H
#define SHARED_GPU_PACKETS_H
/* DMA/GPU packet tag: addr is the next packet's low 24-bit address,
 * len is the command-word count in the high byte. The existing bitfield
 * consumers in the layered renderer and text renderer use this layout. */
/* DMA tag embedded in a render packet; builders set its count and link it into the ordering table.
 * It has the containing packet's frame lifetime; changing addr must preserve the high length byte. */
typedef struct GpuLinkTag {
    unsigned int addr : 24; /* next packet address, low 24 bits */
    unsigned int len : 8; /* number of following GPU command words, in 32-bit words */
} GpuLinkTag;

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

/* Current render state reached through gameWork.unk_000. The grid renderer
 * inserts packets into the low 24 bits of +B0 and advances +8D0 after each
 * allocation. This is a partial observed layout; full allocation unknown. */
/* Partial frame draw context owned by the frame-buffer setup, borrowed through GameWork.draw_buffer.
 * render_scene_frame_with_timing reuses contexts, clears ordering tags and resets packet storage each frame. */
typedef struct GpuContext {
    /* 0x000 */ unsigned char pad_000[0x70];
    /* 0x070 */ unsigned int orderTag070; /* ordering-table tag used by text sprites and draw-mode packets */
    /* 0x074 */ unsigned int orderTag074; /* ordering-table tag used by tile and draw-mode packets */
    /* 0x078 */ unsigned char pad_078[0x38];
    /* 0x0B0 */ int orderTag; /* ordering-table tag used by the textured grid renderer */
    /* 0x0B4 */ unsigned char pad_0B4[0x17C];
    /* 0x230 */ unsigned int orderTag230; /* ordering-table tag used by the three-line shade renderer */
    /* 0x234 */ unsigned char pad_234[0x5F8];
    /* 0x82C */ int orderTag82C; /* ordering-table tag used by the layered tile renderer */
    /* 0x830 */ unsigned char pad_830[0x80];
    /* 0x8B0 */ unsigned int orderTag8B0; /* ordering-table tag used by clipped draw/fill packets */
    /* 0x8B4 */ unsigned char pad_8B4[0x1C];
    /* 0x8D0 */ void *packetCursor; /* next free packet byte; reset to context +0x8D4 when reused, then advanced by each packet builder */
} GpuContext;

/* Exact access views shared across registered binary consumers. */
/* Three signed words supplying packed GPU vertex colors; not a position vector. */
typedef struct PacketColorWords {
    int unk_00;
    int unk_04;
    int unk_08;
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
    unsigned short unk_00;
} DisplayXHalfView;

#endif
