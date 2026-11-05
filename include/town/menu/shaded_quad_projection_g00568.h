#ifndef TOWN_MENU_SHADED_QUAD_PROJECTION_G00568_H
#define TOWN_MENU_SHADED_QUAD_PROJECTION_G00568_H
/* inferred-strong G00568: shaded_quad_projection_g00568; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A56D0. */

#include "common.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"

#include "sdk/libgpu_packets.h"
typedef POLY_G4 ShadedQuadPacket;

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

extern s32 RotTransPers4(InputPair *, InputPair *, InputPair *, InputPair *,
                         OutputPair *, OutputPair *, OutputPair *, OutputPair *,
                         u32 *, u32 *);
extern s32 GetTPage(s32, s32, s32, s32);
extern void AddPrim(void *, void *);
extern void SetSemiTrans(void *, s32);
extern void SetPolyG4(void *);
extern void SetDrawMode(void *, s32, s32, u16, s32);
extern s32 rsin();
extern s32 rcos();
extern void copy_odd_halfwords_3();
extern void copy_menu_vector_halfwords();

/* Functions defined in this translation unit. */
void project_and_enqueue_shaded_quad(Coord8 vertex_0, Coord8 vertex_1, Packed8 vertex_2, Packed8 vertex_3, s32 shade);
void draw_segmented_menu_ring(s32 center_source, s32 radius_a, s32 radius_b, s16 segment_arg);

#endif
