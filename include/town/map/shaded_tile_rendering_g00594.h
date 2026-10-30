#ifndef TOWN_MAP_SHADED_TILE_RENDERING_G00594_H
#define TOWN_MAP_SHADED_TILE_RENDERING_G00594_H
/* Shaded tile rendering (G00594). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AF9D8, PD:town/engine:800D1548. */

#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/dungeon_floor.h"

typedef struct S_func_800AED64_1 {
    void * unk_00;
    u8 pad_04[0x16];
    s16 unk_1A;
    u8 pad_1C[0x2];
    s16 unk_1E;
    u8 pad_20[0x88];
    s32 unk_A8;
    u8 pad_AC[0x130];
    void * unk_1DC;
} S_func_800AED64_1;

typedef struct S_func_800AED64_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x4];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_func_800AED64_2;

typedef struct S_func_800AED64_3 {
    u8 pad_00[0x84];
    s32 unk_84;
    s32 unk_88;
} S_func_800AED64_3;

typedef struct S_func_800AED64_7 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    u8 pad_24[0x4];
} S_func_800AED64_7;

typedef struct S_func_800AED64_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    union {
        s32 s32;
        u16 u16;
    } unk_14;
    s32 unk_18;
    S_func_800AED64_7 edges[4];
    s32 unk_BC;
    s32 unk_C0;
    u8 pad_C4[0x4];
    s32 unk_C8;
    u8 pad_CC[0x8];
    s32 unk_D4;
    u8 pad_D8[0x4];
    s32 unk_DC;
    s32 unk_E0;
    union {
        s16 s16;
        u16 u16;
    } unk_E4;
    u8 pad_E6[0x2];
    s32 unk_E8;
    s16 unk_EC;
    u8 pad_EE[0x2];
    s32 unk_F0;
    s16 unk_F4;
    u8 pad_F6[0x2];
    s32 unk_F8;
    s16 unk_FC;
    u8 pad_FE[0x12];
    s32 unk_110;
    s32 unk_114;
    s32 unk_118;
    s32 unk_11C;
    s32 unk_120;
    s32 unk_124;
    s32 unk_128;
    union {
        s32 s32;
        u16 u16;
    } unk_12C;
    u8 pad_130[0x4];
    s32 unk_134;
    s32 unk_138;
    u8 pad_13C[0x8];
    s32 unk_144;
    u8 pad_148[0x4];
    s32 unk_14C;
    u8 pad_150[0x14];
    s32 unk_164;
    union {
        s32 s32;
        u16 u16;
        struct {
            u8 pad_168[0x2];
            u16 unk_16A;
        } at_16A;
    } unk_168;
    union {
        s32 s32;
        struct {
            u8 pad_16C[0x2];
            u8 unk_16E;
        } at_16E;
        struct {
            u8 pad_16C[0x3];
            u8 unk_16F;
        } at_16F;
    } unk_16C;
    union {
        s32 s32;
        struct {
            u8 pad_170[0x2];
            u16 unk_172;
        } at_172;
    } unk_170;
    u16 unk_174;
    u16 unk_176;
    u16 unk_178;
    u8 pad_17A[0x2];
    s32 unk_17C;
} S_func_800AED64_4;

typedef struct S_func_800AED64_5 {
    u8 pad_00[0x3180];
    s32 unk_3180;
    u8 unk_3184;
    u8 unk_3185;
} S_func_800AED64_5;

typedef struct S_func_800AED64_6 {
    u8 pad_00[0x8D0];
    u32 unk_8D0;
} S_func_800AED64_6;

typedef struct S_func_800AED64_10 {
    u8 pad_00[0x4];
    s32 unk_04;
    u16 unk_08;
    u16 unk_0A;
} S_func_800AED64_10;

typedef struct S_func_800AED64_11 {
    s32 unk_00;
} S_func_800AED64_11;

typedef struct S_func_800AED64_12 {
    void * unk_00;
} S_func_800AED64_12;

typedef struct S_func_800AED64_13 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    union {
        s32 s32;
        struct {
            u8 pad_14[0x2];
            u8 unk_16;
        } at_16;
        struct {
            u8 pad_14[0x3];
            s8 unk_17;
        } at_17;
    } unk_14;
} S_func_800AED64_13;

typedef struct S_func_800AED64_14 {
    u8 pad_00[0x3];
    s8 unk_03;
    union {
        s32 s32;
        struct {
            u8 pad_04[0x3];
            u8 unk_07;
        } at_07;
    } unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u16 unk_1C;
    u8 pad_1E[0x2];
    void * unk_20;
    u16 unk_24;
} S_func_800AED64_14;

typedef struct S_func_800AED64_15 {
    s32 unk_00;
    u16 unk_04;
} S_func_800AED64_15;

typedef struct S_func_800AED64_16 {
    s32 unk_00;
    s16 unk_04;
} S_func_800AED64_16;

typedef struct S_func_800AED64_17 {
    u8 pad_00[0x18];
    s16 unk_18;
    u16 unk_1A;
} S_func_800AED64_17;

typedef union { S_func_800AED64_4 *ptr; u32 address; } ScratchAddress;

typedef struct Slot800AF9D8 {
    u8 pad00[0x1C];
    s32 position;
    s32 decrement;
    u8 pad24[8];
    s32 remaining;
    s32 increment;
    u8 pad34[8];
    s32 phase;
} Slot800AF9D8;


/* record in draw_empty_map_cell_quads */
typedef struct S_800AD138_1 {
    u8 * unk_00;
    u16 unk_04;
    u8 pad_06[0xA2];
    s32 unk_A8;
    u8 pad_AC[0x130];
    u16 * unk_1DC;
} S_800AD138_1;

/* state in draw_empty_map_cell_quads */
typedef struct S_800AD138_2_pre {
    s8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_800AD138_2_pre;

/* the 0x4 bytes before packet_use in draw_empty_map_cell_quads, addressed as packet_use[-1] */
typedef struct S_800AD138_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    s8 unk_06;
    u8 pad_07[0x6];
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x6];
    u8 unk_15;
    s8 unk_16;
    u8 pad_17[0x6];
    s8 unk_1D;
    s8 unk_1E;
} S_800AD138_2;

/* packet_use in draw_empty_map_cell_quads */
typedef struct S_800AD138_3 {
    s32 unk_00;
} S_800AD138_3;

/* (u8 *)list in draw_empty_map_cell_quads */
typedef struct S_800AD138_4 {
    s32 unk_00;
} S_800AD138_4;

/* (void *)((MapQuadScratch *)scratch)->chain_address in draw_empty_map_cell_quads */
typedef struct S_800AD138_5 {
    u8 pad_00[0x8D0];
    s32 * unk_8D0;
} S_800AD138_5;

/* ((S_800AD138_1 *)state)->unk_00 in draw_empty_map_cell_quads */
typedef struct MapQuadTextureWords {
    u8 pad_00[0xE];
    s16 palette;
    u8 pad_10[6];
    s16 texture_page;
} MapQuadTextureWords;

typedef struct MapQuadEdge {
    s32 position;
    s32 unused_04;
    s32 error_step;
    s32 rows_left;
    s32 error;
    s32 unused_14;
    s32 start_y;
    s32 active;
    u8 pad_20[8];
} MapQuadEdge;

typedef struct MapQuadVertex {
    u16 x, y, z, pad;
} MapQuadVertex;

typedef union MapQuadCoordinate {
    s32 value;
    u16 low_half;
} MapQuadCoordinate;

typedef struct MapQuadScratch {
    s32 color;
    s32 unused_04;
    s32 edge_x;
    MapQuadCoordinate scan_y;
    s32 unused_10;
    MapQuadCoordinate min_x;
    s32 max_x;
    MapQuadEdge edges[4];
    s32 chain_address;
    s32 shade;
    s32 last_shade;
    s32 depth;
    u8 pad_CC[8];
    s32 last_depth;
    s32 unused_D8;
    s32 clip_area;
    MapQuadVertex vertices[4];
    u8 pad_100[0x14];
    s32 step_x;
    s32 step_y;
    s32 map_width;
    s32 map_height;
    s32 x_shift;
    s32 y_shift;
    u8 pad_12C[8];
    s32 cell_x;
    s32 row_base;
    u8 pad_13C[8];
    s32 cell_index;
    u8 pad_148[0x28];
    u16 edge_count;
    u8 pad_172[0xA];
    s16 normal_x, normal_y, normal_z;
    u8 pad_182[0x8A];
    union { u16 value; u8 low_byte; } uv_scroll;
} MapQuadScratch;

extern void build_screen_outline(void *, void *, s32);
extern void SetFogFar(s32, s32);
extern void SetLightMatrix(void *);
extern void SetColorMatrix(void *);
/* extern */
extern u8 map_runtime_state[];
extern u8 map_wide_culling[9];
extern void AddPrim(void *, void *);
extern void SetDrawMode(void *, s32, s32, s32, void *);

extern s8 map_tile_uvs[12];
#include "engine/effect.h"
/* Functions defined in this translation unit. */
void set_texture_quad_32_uv(u16 texture_page, u16 palette, u8 texture_u, u8 texture_v);
void render_shaded_map_tiles(void);
void draw_empty_map_cell_quads(u32 packet_limit);

#endif
