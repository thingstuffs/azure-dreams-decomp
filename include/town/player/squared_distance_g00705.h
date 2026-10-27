#ifndef TOWN_PLAYER_SQUARED_DISTANCE_G00705_H
#define TOWN_PLAYER_SQUARED_DISTANCE_G00705_H
/* Squared distance. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00705 - CL:town/func_80330320. */

#include "common.h"
#include "shared/vector.h"
#include "shared/record_ptrs.h"
#include "town/player/coordinates.h"

typedef void (*TownCopyFn)(void *, void *, s32);

typedef void (*TownSetFn)(s32);

extern s8 D_80016130[];
extern s8 D_80016158[];

/* Functions defined in this translation unit. */
GteShortVector *find_nearest_point_3s(GteShortVector *entries, GteShortVector *eval_context, s32 entry_count);

#endif
