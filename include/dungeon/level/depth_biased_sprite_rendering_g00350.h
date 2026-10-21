#ifndef DUNGEON_LEVEL_DEPTH_BIASED_SPRITE_RENDERING_G00350_H
#define DUNGEON_LEVEL_DEPTH_BIASED_SPRITE_RENDERING_G00350_H
/* Depth biased sprite rendering shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800B6D74. */

#include "common.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"

typedef struct S_800BC3E4_0_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_800BC3E4_0_pre;

/* the 0x8 bytes before node in traverse_nodes_and_render_unflagged, addressed as node[-1] */
typedef struct S_800BC3E4_0 {
    void * unk_00;
} S_800BC3E4_0;

/* node in traverse_nodes_and_render_unflagged */
typedef struct S_800BC3E4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800BC3E4_1;

/* object in traverse_nodes_and_render_unflagged */
typedef struct S_800BC3E4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800BC3E4_2;

/* primitive in traverse_nodes_and_render_unflagged */
typedef struct S_800BC3E4_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BC3E4_3;

/* coord in traverse_nodes_and_render_unflagged */
typedef struct S_800BC3E4_4 {
    void * unk_00;
} S_800BC3E4_4;

/* state in traverse_nodes_and_render_unflagged */
typedef struct S_800BC3E4_5 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800BC3E4_5;

/* root in render_projected_sprite_with_depth_bias */
typedef struct S_800BC4D4_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    union { u32 u32; s32 s32; u16 u16; } unk_08;   /* accessed as both */
    union { u32 u; s32 s; } unk_0C;   /* accessed as both */
    union { u32 u32; u16 u16; s32 s32; } unk_10;   /* accessed as both */
    union { u32 u32; u16 u16; s32 s32; } unk_14;   /* accessed as both */
    u8 pad_18[0x8];
    u8 * unk_20;
    u16 unk_24;
    u8 pad_26[0xA];
    union { s32 s; u32 u; } unk_30;   /* accessed as both */
    union { s32 s; u32 u; } unk_34;   /* accessed as both */
    s32 unk_38;
    u8 pad_3C[0x34];
    union { s16 s; u16 u; } unk_70;   /* accessed as both */
    s16 unk_72;
    s16 unk_74;
    u8 pad_76[0x2];
    union { s16 s; u16 u; } unk_78;   /* accessed as both */
    s16 unk_7A;
    s16 unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    u8 pad_86[0x2];
    s16 unk_88;
    s16 unk_8A;
    s16 unk_8C;
    u8 pad_8E[0x2A];
    u16 unk_B8;
    u16 unk_BA;
    u8 pad_BC[0x4];
    u32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u16 unk_F0;
    u16 unk_F2;
    u16 unk_F4;
    u16 unk_F6;
    u16 unk_F8;
    u16 unk_FA;
    u16 unk_FC;
    u16 unk_FE;
} S_800BC4D4_1;

/* scratch in render_projected_sprite_with_depth_bias */
typedef struct S_800BC4D4_2 {
    u8 pad_00[0x8];
    u8 * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_800BC4D4_2;

/* arg1 in render_projected_sprite_with_depth_bias */
typedef struct S_800BC4D4_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BC4D4_3;

/* arg0 in render_projected_sprite_with_depth_bias */
typedef struct S_800BC4D4_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800BC4D4_4;

/* matrix in render_projected_sprite_with_depth_bias */
typedef struct S_800BC4D4_5_pre {
    s8 unk_00;
    u8 pad_01[0x3];
} S_800BC4D4_5_pre;

/* the 0x4 bytes before packet + 7 in render_projected_sprite_with_depth_bias, addressed as (packet + 7)[-1] */
typedef struct S_800BC4D4_5 {
    u8 unk_00;
    u8 pad_01[0xC];
    u8 unk_0D;
    u8 pad_0E[0x8];
    u8 unk_16;
    u8 pad_17[0x6];
    u8 unk_1D;
    u8 unk_1E;
} S_800BC4D4_5;

/* packet + 7 in render_projected_sprite_with_depth_bias */
typedef struct S_800BC4D4_6 {
    u16 unk_00;
} S_800BC4D4_6;

/* ((S_800BC3E4_4 *)state)->unk_00 in traverse_nodes_and_render_unflagged */
extern s32 is_frame_packet_arena_overflowed(void *);
extern s16 sample_terrain_surface_height(u16, u16, s16);
/* texture + 4 in render_projected_sprite_with_depth_bias */
/* *global in render_projected_sprite_with_depth_bias */
extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern u32 func_80065420(void *, void *, void *, void *);
extern void func_800654B0(s16 *, s16 *, s16 *, s16 *, s16 *, s16 *, s16 *, s16 *,
                          s16 *, s16 *);
extern void func_80065820(void *, void *);
extern void func_8006658C(void *, void *);
extern void func_80067EF4(void *, s32, s32);
extern u8 sprite_projection_matrix[];

/* Functions defined in this translation unit. */
s32 traverse_nodes_and_render_unflagged(void *start_node);
void render_projected_sprite_with_depth_bias(void *position, void *sprite, s16 world_z, s32 depth_bias);

#endif
