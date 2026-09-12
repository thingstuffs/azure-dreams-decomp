#include "common.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 value;
} DungeonRect;

typedef struct {
    s16 unused[10];
    s16 stride;
} DungeonState;

typedef struct {
    s16 kind;
    s16 value;
    s16 flags;
} DungeonCell;

typedef struct {
    u8 unused[0x146E];
    s16 level;
} DungeonPage;

extern DungeonState D_8008333C;
extern DungeonCell D_800EA000[];

extern void func_8001D9CC(s16 x0, s16 y0, s16 x1, s16 y1, s16 value);
extern void func_8001DD08(DungeonCell *cell, s16 value);
extern void func_8001DD48(DungeonCell *cell, s16 value);
extern s32 func_800A6D30(void);

/* Fills a dungeon rectangle and applies randomly sized patches of two cell styles. */
void func_8001D5D8(DungeonRect *rect) {
    register u32 value = rect->value;
    s16 left;
    u16 top;
    u16 width;
    u16 height;
    u16 right;
    s16 bottom;
    s16 patch_x;
    s16 patch_y;
    s16 scan_x;
    s16 scan_y;
    s16 cell_x;
    s32 patches_left;
    s16 patch_width;
    s16 patch_height;
    s16 cols_left;
    s16 rows_left;
    s16 signed_width;
    s16 signed_height;
    s32 size_sum;
    s32 patch_count;
    s16 swap_styles;
    s16 patch_style;
    s32 fill_value;
    register s32 style_value_hi ASM_REG("$18");
    DungeonCell *cell;
    register s32 patch_row ASM_REG("$23");
    s32 right_hi;
    u32 col_hi = 0x80080000;
    DungeonState *state = &D_8008333C;

    ASM_KEEP(col_hi);
    ASM_KEEP_NV(value);
    top = rect->y;
    scan_y = top;
    fill_value = value - 0x80;
    left = rect->x;
    width = rect->width;
    height = rect->height;
    right = left + width;
    bottom = top + height;

    if ((s16)top < (s16)bottom) {
        do {
            scan_x = left;
            if (((s32)(s16)left << 16) <
                (right_hi = (s32)(s16)right << 16)) {
                s32 fill_row;
                s32 fill_right;

                ASM_SCHED_BARRIER();
                fill_row = (s16)scan_y;
                fill_right = right_hi >> 16;

                do {
                    s16 next_x;

                    col_hi = (u32)(u16)scan_x << 16;
                    next_x = scan_x + 1;
                    scan_x = next_x;
                    cell = &D_800EA000[
                        (fill_row << state->stride) +
                        ((s32)col_hi >> 16)];
                    cell->kind = 25;
                    cell->value = fill_value;
                    cell->flags = 6;
                } while ((s16)scan_x < fill_right);
            }
            scan_y++;
        } while ((s16)scan_y < (s16)bottom);
    }
    swap_styles = func_800A6D30() & 1;
    signed_width = (s16)width;
    signed_height = (s16)height;
    size_sum = signed_width + signed_height;

    if (size_sum < 0) {
        size_sum += 3;
    }
    patch_count = size_sum >> 2;
    {
        DungeonPage *level_page = (DungeonPage *)0x80080000;

        ASM_KEEP_NV(level_page);
        if (level_page->level < 5) {
            patch_count = size_sum >> 4;
        }
    }
    patches_left = patch_count;
    if (patch_count > 0) {
        do {
            patch_x = (s16)left + ((func_800A6D30() & 0xFFFF) % signed_width);
            patch_y = (s16)top + ((func_800A6D30() & 0xFFFF) % signed_height);
            scan_x = patch_x;
            scan_y = patch_y;
            patch_width = ((signed_width - (patch_x - (s16)left)) / 2 +
                (func_800A6D30() & 7)) - 4;
            patch_height = ((signed_height - (patch_y - (s16)top)) / 2 +
                (func_800A6D30() & 7)) - 4;
            patch_style = (func_800A6D30() & 7) != 0;

            rows_left = patch_height;
            if (patch_height > 0) {
                do {
                    register s32 coord_hi = (s32)scan_y << 16;
                    register s32 coord = coord_hi >> 16;
                    if (coord < (s16)bottom) {
                        cols_left = patch_width;
                        cell_x = scan_x;

                        if (cols_left > 0) {
                            s32 row_style;

                            register s32 row_offset ASM_REG("$2");

                            patch_row = coord;
                            row_style = patch_style;
                            row_offset = value - 0x40;
                            style_value_hi = row_offset << 16;
                            do {
                                s32 alt_value;
                                DungeonCell *patch_cell;
                                coord_hi = (s32)cell_x << 16;
                                coord = coord_hi >> 16;
                                if (coord < (s16)right) {
                                    row_offset = patch_row << D_8008333C.stride;
                                    cell = &D_800EA000[row_offset + coord];
                                    if (swap_styles != 0) {
                                        patch_cell = cell;
                                        if (row_style != 0) {
                                            func_8001DD08(patch_cell, style_value_hi >> 16);
                                        } else {
                                            alt_value = value - 0xC0;
                                            goto apply_alt;
                                        }
                                    } else {
                                        patch_cell = cell;
                                        if (row_style != 0) {
                                            alt_value = value - 0xC0;
                                        apply_alt:
                                            func_8001DD48(patch_cell, (s16)alt_value);
                                        } else {
                                            func_8001DD08(patch_cell, style_value_hi >> 16);
                                        }
                                    }
                                }
                                cols_left--;
                                cell_x++;
                            } while (cols_left > 0);
                        }
                    }
                    rows_left--;
                    scan_y++;
                } while (rows_left > 0);
            }
            patches_left--;
        } while (patches_left > 0);
    }
    ASM_USE_G_NV(state);
    func_8001D9CC((s16)left, (s16)top, (s16)right, (s16)bottom, (s16)value);
}
