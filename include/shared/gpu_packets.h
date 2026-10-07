#ifndef SHARED_GPU_PACKETS_H
#define SHARED_GPU_PACKETS_H
/* Textured four-vertex packet. The grid renderer advances its cursor by
 * 0x28, copies four packed XY words, sets four UV pairs and fills the CLUT
 * and texture-page words. The high tag byte is preserved while linking.
 * Word members retain the demonstrated access widths and alignment. */
typedef struct PolyFT4 {
    /* 0x00 */ int tag;
    /* 0x04 */ int colorCode;
    /* 0x08 */ int xy0;
    /* 0x0C */ unsigned char u0;
    /* 0x0D */ unsigned char v0;
    /* 0x0E */ short clut;
    /* 0x10 */ int xy1;
    /* 0x14 */ unsigned char u1;
    /* 0x15 */ unsigned char v1;
    /* 0x16 */ short tpage;
    /* 0x18 */ int xy2;
    /* 0x1C */ unsigned char u2;
    /* 0x1D */ unsigned char v2;
    /* 0x1E */ unsigned char pad_1E[2];
    /* 0x20 */ int xy3;
    /* 0x24 */ unsigned char u3;
    /* 0x25 */ unsigned char v3;
    /* 0x26 */ unsigned char pad_26[2];
} PolyFT4;

/* Current render state reached through gameWork.unk_000. The grid renderer
 * inserts packets into the low 24 bits of +B0 and advances +8D0 after each
 * allocation. This is a partial observed layout; full allocation unknown. */
typedef struct GpuContext {
    /* 0x000 */ unsigned char pad_000[0xB0];
    /* 0x0B0 */ int orderTag;
    /* 0x0B4 */ unsigned char pad_0B4[0x81C];
    /* 0x8D0 */ unsigned char *packetCursor;
} GpuContext;
#endif
