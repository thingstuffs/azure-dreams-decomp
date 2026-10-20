#include "dungeon/level/generate.h"

void fill_region_with_random_patches(floor_generate_isolated_8028A5D8_DungeonRect *rect, s32 update_id) {
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
    u16 swap_styles;
    s16 patch_style;
    s16 fill_value;
    s32 style_value_hi;
    floor_generate_isolated_8028A5D8_DungeonCell *cell;
    s32 patch_row;
    s32 right_hi;
    u32 col_hi;
    floor_generate_isolated_8028A5D8_DungeonState *state = &(*(floor_generate_isolated_8028A5D8_DungeonState *)D_8008333C);

    left = rect->x;
    top = rect->y;
    width = rect->width;
    height = rect->height;
    right = left + width;
    bottom = top + height;
    fill_value = value - 0x80;
    scan_y = top;

    if ((s16)top < (s16)bottom) {
        for (; (s16)scan_y < (s16)bottom; scan_y++) {
            scan_x = left;
            if (((s32)(s16)left << 16) <
                (right_hi = (s32)(s16)right << 16)) {
                s32 fill_row;
                s32 fill_right;

                fill_row = (s16)scan_y;
                fill_right = right_hi >> 16;

                do {
                    s16 next_x;

                    col_hi = (u32)(u16)scan_x << 16;
                    next_x = scan_x + 1;
                    scan_x = next_x;
                    cell = &((floor_generate_isolated_8028A5D8_DungeonCell *)D_800EA000)[
                        (fill_row << state->stride) +
                        ((s32)col_hi >> 16)];
                    cell->kind = 25;
                    cell->value = fill_value;
                    cell->flags = 6;
                } while ((s16)scan_x < fill_right);
            }
        }
    }
    swap_styles = generate_random_value() & 1;
    signed_width = (s16)width;
    signed_height = (s16)height;
    size_sum = signed_width + signed_height;

    if (size_sum < 0) {
        size_sum += 3;
    }
    patch_count = size_sum >> 2;
    {
        floor_generate_isolated_8028A5D8_DungeonPage *level_page = (floor_generate_isolated_8028A5D8_DungeonPage *)D_80080000;

        if (level_page->level < 5) {
            patch_count = size_sum >> 4;
        }
    }
    patches_left = patch_count;
    if (patch_count > 0) {
        do {
            patch_x = (s16)left + ((generate_random_value() & 0xFFFF) % signed_width);
            patch_y = (s16)top + ((generate_random_value() & 0xFFFF) % signed_height);
            scan_x = patch_x;
            scan_y = patch_y;
            patch_width = ((signed_width - (patch_x - (s16)left)) / 2 +
                (generate_random_value() & 7)) - 4;
            patch_height = ((signed_height - (patch_y - (s16)top)) / 2 +
                (generate_random_value() & 7)) - 4;
            patch_style = (generate_random_value() & 7) != 0;

            rows_left = patch_height;
            if (patch_height > 0) {
                do {
                    register s32 coord_hi = (s32)scan_y << 16;
                    register s16 coord = coord_hi >> 16;
                    if (coord < (s16)bottom) {
                        cell_x = scan_x;
                        cols_left = patch_width;

                        if (cols_left > 0) {
                            s32 row_style;

                            patch_row = coord;
                            row_style = patch_style;
                            style_value_hi = (value - 0x40) << 16;
                            do {
                                s32 alt_value;
                                floor_generate_isolated_8028A5D8_DungeonCell *patch_cell;
                                coord_hi = (s32)cell_x << 16;
                                coord = coord_hi >> 16;
                                if (coord < (s16)right) {
                                    cell = &((floor_generate_isolated_8028A5D8_DungeonCell *)D_800EA000)[(patch_row << state->stride) + coord];
                                    coord = swap_styles;
                                    if (coord != 0) {
                                        patch_cell = cell;
                                        if (row_style != 0) {
                                            advance_generation_step_pair(patch_cell, style_value_hi >> 16);
                                        } else {
                                            alt_value = value - 0xC0;
                                            retreat_generation_step_pair(patch_cell, (s16)alt_value);
                                        }
                                    } else {
                                        patch_cell = cell;
                                        if (row_style != 0) {
                                            alt_value = value - 0xC0;
                                            retreat_generation_step_pair(patch_cell, (s16)alt_value);
                                        } else {
                                            advance_generation_step_pair(patch_cell, style_value_hi >> 16);
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
    write_rectangular_border((s16)left, (s16)top, (s16)right, (s16)bottom, (s16)value);
}
