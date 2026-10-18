#ifndef SHARED_DUNGEON_HEIGHT_QUERY_H
#define SHARED_DUNGEON_HEIGHT_QUERY_H
#include "common.h"
/* Retail TUs declared 800BCB04 differently: these native banks used s32;
 * FA7000 used s16. The returned word is sign-extended from a signed halfword.
 * Keep FA7000's separate declaration: its row and native proofs require it. */
s32 sample_terrain_surface_height(s32 x, s32 y, s16 minimum_height);
#endif
