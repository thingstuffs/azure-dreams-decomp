#include "common.h"
#include "shared/dungeon_moving_views.h"


   /* arg0 in check_row_column_or_diagonal_alignment */

   /* arg1 in check_row_column_or_diagonal_alignment */

static __inline__ s32 position_delta_abs(u8 a, u8 b) {
    return __builtin_abs(a - b);
}

/* Return whether two positions share a row, column, or diagonal. */
s32 check_row_column_or_diagonal_alignment(MovingTile *source, MovingTile *target) {
    s32 aligned;
    s32 y_delta;
    s32 x_delta;

    x_delta = position_delta_abs(source->unk_24, target->unk_24);
    y_delta = position_delta_abs(source->unk_25, target->unk_25);

    aligned = 0;
    if ((x_delta == y_delta) || (x_delta == 0) || (y_delta == 0)) {
        aligned = 1;
    }
    return aligned;
}

