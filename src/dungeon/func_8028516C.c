#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"

typedef struct DungeonCell {
    s16 unk0;
    s16 unk2;
    u16 flags;
} DungeonCell;

typedef struct DungeonRecord {
    s16 x;
    u16 y;
    s16 count;
    s16 rows;
    u8 pad[12];
} DungeonRecord;


s16 func_800BCB04(s32, s32, s32);

/* Scans a dungeon record's rectangle for the first qualifying cell result and outputs its coordinates. */
s32 func_8001816C(s16 record_id, s16 *out_x, s16 *out_y)
{
    MapGrid *state;
    s8 *records_page;
    s32 record_index;
    s32 record_addr;
    s32 scan_record_index;
    DungeonCell *cell;
    s16 cells_left;
    s32 start_x;
    s32 row_width;
    s32 row;
    s32 row_offset;
    s32 x;
    s16 next_cells_left;
    s16 cell_result;
    u16 y;
    s32 center_y;
    s16 rows_left;
    u16 flags;

    start_x = (s32)&D_800E2970;
    record_index = record_id;
    record_addr = record_index * 20;
    record_addr += start_x;
    records_page = (s8 *)record_addr;
    rows_left = *(s16 *)(records_page + 6);
    y = *(u16 *)(records_page + 2);
    state = &gameWork.map;

    if (rows_left > 0) {
        register s16 *y_ptr ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        scan_record_index = record_index;
        do {
            {
                row_width = scan_record_index << 2;
                row_width += scan_record_index;
                row_width <<= 2;
                y_ptr = (s16 *)((DungeonRecord *)&D_800E2970);
                row_width += (s32)y_ptr;
            }
            record_addr = (s32)y << 16;
            row = record_addr >> 16;
            start_x = ((DungeonRecord *)row_width)->x;
            row_offset = state->shiftX;
            row_width = ((DungeonRecord *)row_width)->count;
            x = start_x;
            ASM_KEEP_NV(start_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            record_addr = ((s32)(row << row_offset)) * sizeof(DungeonCell);
            row_offset = (s32)((DungeonCell *)state->cells);
            cells_left = row_width;
            row_offset += record_addr;
            record_addr = start_x * sizeof(DungeonCell);
            cell = (DungeonCell *)(row_offset + record_addr);

            if (row_width > 0) {
                records_page = (s8 *)(row << 6);
                center_y = (s32)records_page + 0x20;
                do {
                    flags = cell->flags;
                    if (!(flags & 0x8400)) {
                        if ((flags & 0x300) == 0x200) {
                            cell_result = func_800BCB04(
                                ((((s32)x << 16) >> 10) + 0x20) & 0xFFE0,
                                (u16)center_y,
                                -0x400);
                            if (cell_result < 0x200) {

                                *out_x = x;
                                y_ptr = *(s16 **)&out_y;
                                *y_ptr = y;
                                return cell_result;
                            }
                        }
                    }

                    x++;
                    next_cells_left = cells_left - 1;
                    cells_left = next_cells_left;
                    cell++;
                    if ((next_cells_left << 16) <= 0) {
                        break;
                    }
                } while (1);
            }

            rows_left--;
            y++;
        } while ((rows_left << 16) > 0);
    }

    return 0x200;
}
