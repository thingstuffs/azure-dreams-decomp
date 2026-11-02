#ifndef ENGINE_GRAPHICS_LIT_MESH_H
#define ENGINE_GRAPHICS_LIT_MESH_H
#include "common.h"
/* The face stream advances by 0x18, and each emitted quad by 0x28.
 * The scratch record names only the offsets observed by draw_lit_mesh.
 * UV words overlap the actual palette/page halfwords modified by the draw. */
typedef struct LitMeshFace {
    u16 vertex_indices[4];
    s32 uv_clut;
    s32 uv_page;
    u16 normal_index;
    u16 uv2;
    u16 uv3;
    u8 unk_16;
    s8 unk_17;
} LitMeshFace;

typedef struct LitMeshQuadPacket {
    s32 tag;
    u8 color[3];
    u8 command;
    s32 xy0;
    union { s32 word; struct { u16 uv; u16 clut; } halves; } uv_clut;
    s32 xy1;
    union { s32 word; struct { u16 uv; u16 page; } halves; } uv_page;
    s32 xy2;
    u16 uv2;
    u8 pad_1E[2];
    s32 xy3;
    u16 uv3;
    u8 pad_26[2];
} LitMeshQuadPacket;

typedef struct {
    s32 value;
    u16 depth;
    u16 pad;
} Vertex;

typedef struct ScratchVertex {
    s32 xy;
    u16 z;
    u16 pad;
} ScratchVertex;
typedef struct RenderScratch {
    u8 pad00[0x20];
    void *ordering_table;
    u8 pad24[0xC];
    s32 scale[3];
    u8 pad3C[4];
    s32 translation[3];
    u8 pad4C[0x24];
    ScratchVertex vertices[4];
    u8 pad90[0x30];
    s32 depth;
    u8 padC4[0x50];
    s32 clip;
} RenderScratch;
#endif
