#ifndef DUNGEON_EFFECT_ROTATING_QUAD_H
#define DUNGEON_EFFECT_ROTATING_QUAD_H
#include "common.h"

typedef struct RotatingQuadVertex {
    u16 x, y, z, pad;
} RotatingQuadVertex;

typedef struct RotatingQuadColor {
    u8 r, g, b, pad;
} RotatingQuadColor;

/* Shared by the two rotating-quad callbacks. Relative vertices enter
 * func_80065320; the rotated triples are then translated into world space. */
typedef struct RotatingQuadScratch {
    u8 pad_00[0x70];
    RotatingQuadVertex relative[4];
    u8 pad_90[4];
    s32 transform_flags;
    RotatingQuadVertex rotated[4];
} RotatingQuadScratch;

#endif
