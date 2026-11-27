#ifndef DUNGEON_EFFECT_MESH_STAR_EDGE_EFFECT_H
#define DUNGEON_EFFECT_MESH_STAR_EDGE_EFFECT_H

#include "common.h"

/* Star center body initialized by the owner effect and advanced by
 * initialize_star_effect_sequence. The two arrays hold five planar vertices. */
typedef struct StarSequenceBody {
    s16 mode;
    s16 frame;
    u16 initial_count;
    u8 pad_06[0x4];
    s16 radius;
    s16 base_angle;
    u8 pad_0E[0xE];
    s16 edge_index;
    u16 x[5];
    u8 pad_28[0x2];
    u16 y[5];
} StarSequenceBody;

/* Body of an edge node allocated by initialize_star_effect_sequence. */
typedef struct StarEdgeEffectBody {
    u8 pad_00[0x2];
    u16 remaining_ticks;
    u8 pad_04[0x1A];
    s16 end_x;
    s16 tip_x;
    u8 pad_22[0x8];
    s16 end_y;
    s16 tip_y;
    u8 pad_2E[0x8];
    u8 base_red;
    u8 base_green;
    u8 base_blue;
    u8 pad_39[0x7];
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u16 v; } at00p; struct { u8 pad[0x2]; s16 v; } at02; } unk_40;   /* overlapping accesses */
    u8 pad_44[0x8];
    u8 texture_u;
    u8 texture_v;
    u8 texture_width;
    u8 texture_height;
    u8 pad_50[0x8];
    s16 quad_x0;
    u16 quad_x1;
    u16 quad_x2;
    u16 quad_x3;
    s16 quad_y0;
    u16 quad_y1;
    u16 quad_y2;
    u16 quad_y3;
    u16 quad_z0;
    u16 quad_z1;
    u16 quad_z2;
    u16 quad_z3;
} StarEdgeEffectBody;

#endif
