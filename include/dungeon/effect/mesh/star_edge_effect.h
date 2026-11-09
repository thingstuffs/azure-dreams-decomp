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
    u16 unk_02;
    u8 pad_04[0x1A];
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0x8];
    s16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x8];
    u8 unk_36;
    u8 unk_37;
    u8 unk_38;
    u8 pad_39[0x7];
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u16 v; } at00p; struct { u8 pad[0x2]; s16 v; } at02; } unk_40;   /* overlapping accesses */
    u8 pad_44[0x8];
    u8 unk_4C;
    u8 unk_4D;
    u8 unk_4E;
    u8 unk_4F;
    u8 pad_50[0x8];
    s16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    s16 unk_60;
    u16 unk_62;
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
} StarEdgeEffectBody;

#endif
