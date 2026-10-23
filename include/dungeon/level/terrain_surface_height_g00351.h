#ifndef DUNGEON_LEVEL_TERRAIN_SURFACE_HEIGHT_G00351_H
#define DUNGEON_LEVEL_TERRAIN_SURFACE_HEIGHT_G00351_H
/* Terrain surface height shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800B771C. */

#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

/* Signed three-component map vertex or surface-normal entry.
 * The map loader supplies the geometry tables; the terrain-height query reads both through this layout. */
typedef struct {
    s16 x; /* X vertex or normal component, according to the selected table */
    s16 y; /* Y vertex or normal component, according to the selected table */
    s16 z; /* height or Z normal component, according to the selected table */
    s16 pad;
} Vertex;

/* Six-byte terrain cell addressed through MapGrid.cells.
 * Map loading supplies the grid; sample_terrain_surface_height uses the face index and height offset. */
typedef struct {
    u16 first; /* face-list table index; zero means no face list */
    s16 value; /* cell height value; terrain queries add its negation to the face height */
    u16 pad;
} Cell;

/* Map face record used by the terrain-height query, separate from a GPU command packet.
 * The loaded cell face list owns the record. */
typedef struct {
    u16 v0; /* first vertex index into MapGrid.vertices */
    u16 v1; /* second vertex index into MapGrid.vertices */
    u16 v2; /* vertex index loaded into the fourth corner of the containment test */
    u16 v3; /* vertex index loaded into the third corner of the containment test */
    u8 pad08[8];
    u16 next; /* surface-normal index into MapGrid.surface_planes */
    u8 pad12[4];
    u8 kind; /* face encoding; high nibble changes the stride when low nibble is 1 */
    s8 flags; /* bit 0 skips the face; bit 7 ends the low-nibble-1 face list */
} Primitive;

/* Packed pair of tile-local corner coordinates in terrain-query scratch storage.
 * sample_terrain_surface_height fills it from a vertex and subtracts the query position. */
typedef union {
    u32 word; /* packed X/Y halfwords copied from the vertex */
    struct {
        u16 x; /* corner X relative to the query point, in world units */
        u16 y; /* corner Y relative to the query point, in world units */
    } half;
} WorkPair;

/* Scratchpad work for one terrain-height query, filled by sample_terrain_surface_height.
 * The query uses this view at scratchpad offset +0x140 and returns its best height. */
typedef struct {
    u8 pad000[0x140];
    u16 x; /* query X within its tile, x & 63 */
    u16 y; /* query Y within its tile, y & 63 */
    s32 value; /* candidate surface height including the cell height offset */
    s32 best; /* lowest qualifying height; initialized to the 0x400 no-surface result */
    s32 limit; /* minimum accepted height supplied by the caller */
    u16 index; /* linear map cell index after clamping tile coordinates to 0..63 */
    s16 offset; /* negated current cell height value */
    WorkPair p0; /* first corner relative to the query point */
    WorkPair p1; /* second corner relative to the query point */
    WorkPair p2; /* third corner relative to the query point */
    WorkPair p3; /* fourth corner relative to the query point */
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
s32 ratan2();

/* Functions defined in this translation unit. */
s16 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);
s32 are_quad_corner_turns_within_half_revolution(S_800BCE7C_0 *poly);

#endif
