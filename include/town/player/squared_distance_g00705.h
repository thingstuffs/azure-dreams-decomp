#ifndef TOWN_PLAYER_SQUARED_DISTANCE_G00705_H
#define TOWN_PLAYER_SQUARED_DISTANCE_G00705_H
/* Squared distance. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00705 - CL:town/func_80330320. */

#include "common.h"
#include "shared/record_ptrs.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef void (*TownCopyFn)(void *, void *, s32);

typedef void (*TownSetFn)(s32);

extern s8 D_80016130[];
extern s8 D_80016158[];

/* Functions defined in this translation unit. */
s32 squared_distance_3s(Vec3s *point_a, Vec3s *point_b);
s32 find_nearest_point_3s(s32 entries, s32 eval_context, s32 entry_count);

#endif
