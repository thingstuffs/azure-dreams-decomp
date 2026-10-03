#include "common.h"
#include "shared/game_work.h"

extern u8 D_800E50A8[];

/* Returns the masked nibble at the given grid coordinates. */
s32 func_8009EE4C(s16 x, s16 y) {
    u32 cell_index;
    u8 *cell_pair;
    u8 packed_cells;
    s32 odd_column;
    s32 row_shift;
    s16 *shift_page;

#ifndef NON_MATCHING
    shift_page = (s16 *)0x80080000;
    row_shift = *(s16 *)((s16 *)(&gameWork.map.shiftX));
#else
    row_shift = gameWork.map.shiftX;
#endif
    cell_index = (y << row_shift) + x;
    cell_pair = ((s32)((cell_index + (cell_index >> 31)) << 15) >> 16) + D_800E50A8;
    packed_cells = *cell_pair;
    odd_column = x & 1;
    if (odd_column == 0) {
        return packed_cells & 0xF;
    }
    return packed_cells & 0xF0;
}
