#include "common.h"

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

typedef struct DungeonState {
    DungeonCell *cells;
    u8 pad[16];
    s16 shift;
} DungeonState;

extern DungeonState D_8008333C;
extern DungeonRecord D_800E2970[];

s16 func_800BCB04(s32, s32, s32);

/* Scans a dungeon record's rectangle for the first qualifying cell result and outputs its coordinates. */
s32 func_8001816C(s16 record_id, s16 *out_x, s16 *out_y)
{
    s8 *record_bytes;
    register s8 *records_base ASM_REG("$5");   /* MATCH pin: retail immediate-load split depends on it */
    DungeonRecord *record;
    DungeonState *state;
    register s8 *records_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 record_index ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 record_addr;
    s32 scan_record_index;
    DungeonCell *cell;
    register s16 cells_left ASM_REG("$18");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 start_x;
    s32 row_width;
    register s32 row_bits ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 row ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 row_offset ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    register s32 cell_offset ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 x;
    register s32 row_y_scaled ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s16 next_cells_left;
    s16 cell_result;
    u16 y;
    register s32 center_y ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    s16 rows_left;
    u16 flags;

    records_page = (s8 *)0x800E0000;
    ASM_KEEP_NV(records_page);   /* MATCH pin: load-bearing for the whole function shape */
    records_base = records_page + 0x2970;
    record_index = record_id;
    record_addr = record_index * 20;
    record_addr += (s32)records_base;
    record_bytes = (s8 *)record_addr;
    rows_left = *(s16 *)(record_bytes + 6);
    y = *(u16 *)(record_bytes + 2);
    state = &D_8008333C;

    if (rows_left > 0) {
        scan_record_index = record_index;
    scan_row:
        {
            s32 record_offset;
            register DungeonRecord *record_base ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */

            record_offset = scan_record_index << 2;
            record_offset += scan_record_index;
            record_offset <<= 2;
            record_base = (DungeonRecord *)0x800E0000;
            ASM_KEEP_NV(record_base);   /* MATCH pin: load-bearing for the whole function shape */
            record_base = (DungeonRecord *)((s8 *)record_base + 0x2970);
            record = (DungeonRecord *)(record_offset + (s32)record_base);
        }
        row_bits = (s32)y << 16;
        row = row_bits >> 16;
        start_x = record->x;
        row_offset = state->shift;
        ASM_KEEP_DEP_NV(record, row_offset);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        row_width = record->count;
        x = start_x;
        ASM_KEEP_NV(start_x);   /* MATCH pin: load-bearing for the whole function shape */
        row_offset = row << row_offset;
        cell_offset = row_offset * sizeof(DungeonCell);
        row_offset = (s32)state->cells;
        cells_left = row_width;
        row_offset += cell_offset;
        cell_offset = start_x * sizeof(DungeonCell);
        cell = (DungeonCell *)(row_offset + cell_offset);

        if (row_width > 0) {
            row_y_scaled = row << 6;
            ASM_KEEP_NV(row_y_scaled);   /* MATCH pin: load-bearing for the whole function shape */
            center_y = row_y_scaled + 0x20;
            ASM_KEEP_NV(center_y);   /* MATCH pin: retail register colouring depends on it */
        scan_cell:
            flags = cell->flags;
            if (!(flags & 0x8400)) {
                if ((flags & 0x300) == 0x200) {
                    cell_result = func_800BCB04(
                        ((((s32)x << 16) >> 10) + 0x20) & 0xFFE0,
                        (u16)center_y,
                        -0x400);
                    if (cell_result < 0x200) {
                        register s16 *y_ptr ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */

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
            if ((next_cells_left << 16) > 0) {
                goto scan_cell;
            }
        }

        rows_left--;
        y++;
        if ((rows_left << 16) > 0) {
            goto scan_row;
        }
    }

    return 0x200;
}
