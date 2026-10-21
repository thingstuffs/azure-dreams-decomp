#ifndef TOWN_MENU_SHADED_QUAD_PROJECTION_G00568_H
#define TOWN_MENU_SHADED_QUAD_PROJECTION_G00568_H
/* inferred-strong G00568: shaded_quad_projection_g00568; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A56D0. */

#include "common.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"

typedef struct S_800A2E30_1 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 pad_07[0x1];
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 pad_17[0x1];
    u16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 pad_1F[0x1];
    u16 unk_20;
    u16 unk_22;
} S_800A2E30_1;

typedef struct InputPair {
    u32 first;
    u32 second;
} InputPair;

typedef struct OutputPair {
    u16 first;
    u16 second;
    u32 pad;
} OutputPair;

typedef struct {
    u16 h[4];
} Coord8;

typedef struct {
    u32 w0;
    u32 w1;
} __attribute__((packed)) Packed8;

extern s32 func_800654B0(InputPair *, InputPair *, InputPair *, InputPair *,
                         OutputPair *, OutputPair *, OutputPair *, OutputPair *,
                         u32 *, u32 *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80066640(void *, s32);
extern void func_80066708(void *);
extern void func_80067F20(void *, s32, s32, u16, s32);
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 copy_odd_halfwords_3();
extern s32 copy_menu_vector_halfwords();

/* Functions defined in this translation unit. */
void project_and_enqueue_shaded_quad(Coord8 vertex_0, Coord8 vertex_1, Packed8 vertex_2, Packed8 vertex_3, s32 shade);
void draw_segmented_menu_ring(s32 center_source, s32 radius_a, s32 radius_b, s16 segment_arg);

#endif
