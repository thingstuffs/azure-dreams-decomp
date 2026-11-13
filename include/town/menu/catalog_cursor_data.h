#ifndef TOWN_MENU_CATALOG_CURSOR_DATA_H
#define TOWN_MENU_CATALOG_CURSOR_DATA_H

#include "common.h"

/* Catalog cursor column positions; the source uses the base and indexed entries.
 * catalog_cursor_columns is s16 by opposite-sign trial over its four readers (menu_row_index,
 * interpolate_catalog_grid_cursor and the two cursor animations): s16 needs no value cast (the old
 * (u16) on the interpolation base was a no-op); u16 makes the interpolation differ and needs (s16)
 * on both operands of its difference. */
extern s16 catalog_cursor_columns[];
extern u16 catalog_cursor_rows[];
extern u8 catalog_number_marker[];
extern void *catalog_normal_digits[];

#endif
