#ifndef SHARED_DUNGEON_HEIGHT_QUERY_H
#define SHARED_DUNGEON_HEIGHT_QUERY_H
#include "common.h"
#include "dungeon/level.h"
/* Retail TUs declared 800BCB04 differently: these native banks used s32;
 * FA7000 used s16. The returned word is sign-extended from a signed halfword.
 * Keep FA7000's separate declaration: its row and native proofs require it. */
#endif
