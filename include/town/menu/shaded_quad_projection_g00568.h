#ifndef TOWN_MENU_SHADED_QUAD_PROJECTION_G00568_H
#define TOWN_MENU_SHADED_QUAD_PROJECTION_G00568_H
/* inferred-strong G00568: shaded_quad_projection_g00568; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A56D0. */

#include "common.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"

/* POLY_G4 packet built in the frame draw context and initialized by SetPolyG4. */
typedef struct ShadedQuadPacket {
    /* 0x00 */ u8 pad_00[0x4];
    /* 0x04 */ u8 red0;
    /* 0x05 */ u8 green0;
    /* 0x06 */ u8 blue0;
    /* 0x07 */ u8 pad_07;
    /* 0x08 */ u16 x0;
    /* 0x0A */ u16 y0;
    /* 0x0C */ u8 red1;
    /* 0x0D */ u8 green1;
    /* 0x0E */ u8 blue1;
    /* 0x0F */ u8 pad_0F;
    /* 0x10 */ u16 x1;
    /* 0x12 */ u16 y1;
    /* 0x14 */ u8 red2;
    /* 0x15 */ u8 green2;
    /* 0x16 */ u8 blue2;
    /* 0x17 */ u8 pad_17;
    /* 0x18 */ u16 x2;
    /* 0x1A */ u16 y2;
    /* 0x1C */ u8 red3;
    /* 0x1D */ u8 green3;
    /* 0x1E */ u8 blue3;
    /* 0x1F */ u8 pad_1F;
    /* 0x20 */ u16 x3;
    /* 0x22 */ u16 y3;
} ShadedQuadPacket;

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
extern s32 copy_odd_halfwords_3();
extern s32 copy_menu_vector_halfwords();

/* Functions defined in this translation unit. */
void project_and_enqueue_shaded_quad(Coord8 vertex_0, Coord8 vertex_1, Packed8 vertex_2, Packed8 vertex_3, s32 shade);
void draw_segmented_menu_ring(s32 center_source, s32 radius_a, s32 radius_b, s16 segment_arg);

#endif
