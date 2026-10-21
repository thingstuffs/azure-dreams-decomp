#ifndef DUNGEON_LEVEL_TERRAIN_SURFACE_HEIGHT_G00351_H
#define DUNGEON_LEVEL_TERRAIN_SURFACE_HEIGHT_G00351_H
/* Terrain surface height shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800B771C. */

#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Vertex;

typedef struct {
    u16 first;
    s16 value;
    u16 pad;
} Cell;

typedef struct {
    u16 v0;
    u16 v1;
    u16 v2;
    u16 v3;
    u8 pad08[8];
    u16 next;
    u8 pad12[4];
    u8 kind;
    s8 flags;
} Primitive;

typedef union {
    u32 word;
    struct {
        u16 x;
        u16 y;
    } half;
} WorkPair;

typedef struct {
    u8 pad000[0x140];
    u16 x;
    u16 y;
    s32 value;
    s32 best;
    s32 limit;
    u16 index;
    s16 offset;
    WorkPair p0;
    WorkPair p1;
    WorkPair p2;
    WorkPair p3;
} Work;

typedef struct S_800BCE7C_0 {
    u8 pad_00[0x154];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_154;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_158;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_15C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_160;   /* overlapping accesses */
    s32 unk_164;
    s32 unk_168;
    s32 unk_16C;
    s32 unk_170;
    u8 pad_174[0x4];
    s32 unk_178;
    s32 unk_17C;
    s32 unk_180;
} S_800BCE7C_0;

/* arg0 in are_quad_corner_turns_within_half_revolution */
s32 func_80065F90();

/* Functions defined in this translation unit. */
s16 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);
s32 are_quad_corner_turns_within_half_revolution(S_800BCE7C_0 *poly);

#endif
