#ifndef TILE_MAP_ABI_VIEWS_H
#define TILE_MAP_ABI_VIEWS_H
#include "common.h"
/* The finder consumes low-halfword coordinates/height. Word arguments
 * preserve the original ABI carriers; the same executable entry is bound. */
void *tile_finder_words(void *node, s32 x, s32 y, s32 height) __asm__("func_8009B25C");
s16 map_height_short(s32 x, s32 y, s16 minimum) __asm__("func_800BCB04");
s16 map_height_wrapped(u16 x, u16 y, s16 minimum) __asm__("func_800BCB04");
#endif
