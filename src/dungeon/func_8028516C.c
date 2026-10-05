#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"

typedef struct DungeonCell {
    s16 unk0;
    s16 unk2;
    u16 flags;
} DungeonCell;

s16 func_800BCB04(s32 x, s32 y, s16 min_height);

/* Scans a dungeon record's rectangle for the first qualifying cell result and outputs its coordinates. */
s32 func_8001816C(s16 record_id, s16 *out_x, s16 *out_y)
{
    s16 rows_left;
    s16 cols_left;
    u16 y;
    s16 x;
    s16 cell_result;
    s32 row;
    u16 flags;
    s32 center_y;
    DungeonCell *cell;
    MapGrid *state;

    rows_left = D_800E2970[record_id].h;
    y = D_800E2970[record_id].y;
    state = &gameWork.map;
    if (rows_left > 0) {
        do {
            row = (s16)y;
            x = D_800E2970[record_id].x;
            cols_left = D_800E2970[record_id].w;
            cell = (DungeonCell *)state->cells + (row << state->shiftX) + x;
            if (cols_left > 0) {
                center_y = (row << 6) + 0x20;
                do {
                    flags = cell->flags;
                    if (!(flags & 0x8400)) {
                        if ((flags & 0x300) == 0x200) {
                            cell_result = func_800BCB04((((s16)x << 6) + 0x20) & 0xFFE0, center_y & 0xFFFF, -0x400);
                            if (cell_result < 0x200) {
                                *out_x = x;
                                *out_y = y;
                                return cell_result;
                            }
                        }
                    }
                    x++;
                    cols_left--;
                    cell++;
                } while ((cols_left << 16) > 0);
            }
            rows_left--;
            y++;
        } while ((rows_left << 16) > 0);
    }
    return 0x200;
}
