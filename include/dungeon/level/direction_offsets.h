#ifndef DUNGEON_LEVEL_DIRECTION_OFFSETS_H
#define DUNGEON_LEVEL_DIRECTION_OFFSETS_H

#include "common.h"

/* Resident dungeon direction tables: eight halfword offsets per axis at
 * 0x800DCEAC and 0x800DCEBC; the next table begins at 0x800DCECC. */
extern u16 direction_x_offsets[8];
extern u16 direction_y_offsets[8];

#endif
