#ifndef SHARED_DUNGEON_HEIGHT_QUERY_H
#define SHARED_DUNGEON_HEIGHT_QUERY_H
#include "common.h"
/* Retail TUs declared 800BCB04 differently: these native banks used s32;
 * FA7000 used s16. The returned word is sign-extended from a signed halfword.
 * Keep FA7000's separate declaration: its row and native proofs require it. */
/* The left-cell query takes world coordinates. The diagonal side query takes tile coordinates. */
s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
s16 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);

s32 get_surface_height_at_coordinates(s32 xCoord, s32 yCoord);

#endif
