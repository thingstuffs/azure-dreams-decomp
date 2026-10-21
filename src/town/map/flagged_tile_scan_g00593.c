/* Flagged tile scan (G00593).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AE700, CL:town/func_800AE78C, CL:town/func_800AEA50, CL:town/func_800AEC1C.
 */
#include "town/map/flagged_tile_scan_g00593.h"

/* Appends an accepted byte pair to the first list and marks its end. */
void append_valid_key_pair(s32 first_value, s32 second_value, u32 unused_cell) {
    S_80081508 *entry;

    if (tile_key_pair_count[0] < 64) {
        if ((s16)has_runtime_key_pair((u16)first_value, (u16)second_value) == 0) {
            entry = &D_80081508[0][tile_key_pair_count[0]];
            entry->a = (u8)first_value;
            entry->b = (u8)second_value;
            tile_key_pair_count[0]++;
            entry[1].a = 0;
        }
    }
}

/* Visit and count flagged grid cells along two opposite directions for up to ten steps. */
s32 count_flagged_cells_in_opposite_directions(s32 dir, s16 start_x, s16 start_y) {
        /* The six spilled locals. Declaration order == stack slot order:
       0x10, 0x18, 0x20, 0x28, 0x30, 0x34($sp). */
    s32 map_base;
    u16 reverse_dir;
    u16 fwd_count;
    u16 rev_count;
    s32 fwd_step_offset;
    u16 *fwd_x_step;

    s32 fwd_dir_offset;
    register s32 fwd_check_x;
    s32 fwd_check_y;
    s32 rev_check_x;
    s32 rev_check_y;
    register s16 fwd_y;
    register s16 rev_y;
    register s16 fwd_x;
    register s16 fwd_blocked;
    register s16 rev_blocked;
    register GridInfo *grid;
    register s32 step_count;
    s32 one;
    register s32 fwd_x_test;
    s32 fwd_y_high;
    s32 fwd_stopped;
    s32 rev_x_high;
    s32 rev_y_high;
    s32 rev_stopped;
    u16 *fwd_cell;
    u16 *rev_cell;
    register u32 fwd_cell_flags;
    register u32 rev_cell_flags;
    s16 rev_x;
    u8 *x_steps;
    s32 fwd_map_y;
    s32 fwd_dx;
    s32 rev_map_y;
    s32 rev_dx;
    s32 visit_count;
    s32 fwd_dy;
    s32 rev_step_offset;
    s32 rev_dy;
    s32 fwd_map_x;
    s32 fwd_map_base;
    s32 rev_map_base;
    s32 fwd_row_shift;
    s32 rev_row_shift;
    s32 rev_map_x;
    s32 y_steps_addr;
    u16 *rev_y_step;
    s32 rev_step_dir;
    grid = scene_geometry;
    rev_blocked = 0;
    fwd_blocked = rev_blocked;
    rev_x = start_x;
    fwd_x = start_x;
    rev_y = start_y;
    fwd_y = start_y;
    step_count = 0;
    one = 1;
    map_base = scene_geometry[0].map_base;
    x_steps = (u8 *)((s8 *)dir_step_x);
    rev_count = 0;
    fwd_count = 0;
    reverse_dir = (dir - 2) & 7;
    fwd_dir_offset = ((dir + 2) & 7) << 1;
    fwd_step_offset = fwd_dir_offset;
    fwd_x_step = (u16 *)(x_steps + fwd_dir_offset);
        /* Dead pre-set (removed by flow): gives `rev_step_dir`'s real definition a
       non-first regno_first_uid so loop.c refuses to hoist the invariant
       reverse_dir read+shift out of the loop, as retail keeps it in-loop. */
    rev_step_dir = dir;
    do {
        fwd_x_test = fwd_x << 0x10;
        fwd_check_x = fwd_x_test >> 0x10;
        if ((fwd_check_x < 0) ||
            ((fwd_check_x < (one << grid->x_shift)) == 0)) {
            fwd_blocked = 1;
        }
        fwd_y_high = fwd_y << 0x10;
        fwd_check_y = fwd_y_high >> 0x10;
        if ((fwd_check_y < 0) ||
            ((fwd_check_y < (one << grid->y_shift)) == 0)) {
            fwd_blocked = 1;
        }
        fwd_stopped = fwd_blocked;
        if (fwd_stopped == 0) {
            fwd_map_x = (fwd_x << 0x10) >> 0x10;
            fwd_map_y = (fwd_y << 0x10) >> 0x10;
            fwd_row_shift = grid->x_shift;
            fwd_map_base = map_base;
            fwd_cell = (u16 *)(fwd_map_base +
                ((fwd_map_x + (fwd_map_y << fwd_row_shift)) << 1));
            fwd_cell_flags = *fwd_cell;
            if (fwd_cell_flags & 0x8000) {
                *fwd_cell = fwd_cell_flags | 0x4000;
                append_valid_key_pair((u16)fwd_x, (u16)fwd_y, fwd_cell_flags);
                {
                    u16 *fwd_y_step;
                    u16 *fwd_x_step_ptr;

                    fwd_count += 1;
                    y_steps_addr = (s32)((s8 *)dir_step_x) + 0x10;
                    fwd_y_step = (u16 *)(fwd_step_offset + y_steps_addr);
                    fwd_x_step_ptr = fwd_x_step;
                    fwd_dy = *fwd_y_step;
                    fwd_dx = *fwd_x_step_ptr;
                    fwd_y += fwd_dy;
                    fwd_x += fwd_dx;
                }
            } else {
                fwd_blocked = 1;
            }
        }
        rev_x_high = rev_x << 0x10;
        rev_check_x = rev_x_high >> 0x10;
        if ((rev_check_x < 0) ||
            ((rev_check_x < (one << grid->x_shift)) == 0)) {
            rev_blocked = 1;
        }
        rev_y_high = rev_y << 0x10;
        rev_check_y = rev_y_high >> 0x10;
        if ((rev_check_y < 0) ||
            ((rev_check_y < (one << grid->y_shift)) == 0)) {
            rev_blocked = 1;
        }
        rev_stopped = rev_blocked;
        if (rev_stopped == 0) {
            rev_map_x = (rev_x << 0x10) >> 0x10;
            rev_map_y = (rev_y << 0x10) >> 0x10;
            rev_row_shift = grid->x_shift;
            rev_map_base = map_base;
            rev_cell = (u16 *)(rev_map_base +
                ((rev_map_x + (rev_map_y << rev_row_shift)) << 1));
            rev_cell_flags = *rev_cell;
            if (rev_cell_flags & 0x8000) {
                *rev_cell = rev_cell_flags | 0x4000;
                append_valid_key_pair((u16)rev_x, (u16)rev_y, rev_cell_flags);
                {
                    register u16 *rev_x_step;

                    rev_count += 1;
                    rev_step_dir = reverse_dir;
                    rev_step_offset = rev_step_dir << 1;
                    rev_x_step = (u16 *)(rev_step_offset + (s32)x_steps);
                    rev_y_step = (u16 *)(rev_step_offset + (s32)((s8 *)dir_step_y));
                    rev_dx = *rev_x_step;
                    rev_dy = *rev_y_step;
                    rev_x += rev_dx;
                    rev_y += rev_dy;
                }
            } else {
                rev_blocked = 1;
            }
        }
        step_count += 1;
        visit_count = fwd_x << 0x10; /* loop-bottom reference; keeps the s2/s3
                                       walker birth order (do not remove) */
    } while (step_count < 10);
    visit_count = (s16)(fwd_count + rev_count);
    return visit_count;
}

/* Counts flagged tiles along a direction for up to ten in-bounds positions. */
s32 count_flagged_tiles_along_direction(s16 direction, s16 start_x, s16 start_y) {
    u16 *tiles;
    MapGrid *config;
    s16 next_x;
    s16 next_y;
    s16 y;
    s16 x;
    s32 tile_x;
    s32 direction_offset;
    s32 steps_left;
    s16 flagged_count;
    s32 direction_shifted;
    u16 *x_step;
    u8 *x_steps;
    u8 *y_steps = 0;

    x = start_x;
    y = start_y;
    steps_left = 0xA;
    flagged_count = 0;
    config = &g_game_work.map;
    tiles = *(u16 **)((Config *)((u8 *)&g_game_work + 476));
    if (start_x < 0 || start_x >= (1 << config->shiftX) || start_y < 0 || start_y >= (1 << config->shiftY)) {
        return 0;
    }
    direction_shifted = direction << 0x10;
    x_steps = (u8 *)dir_step_x;
    direction_offset = direction_shifted >> 0xF;
    x_step = (u16 *)(x_steps + direction_offset);
    do {
        tile_x = x;
        if ((*(u16 *)((u8 *)tiles + ((tile_x + (y << config->shiftX)) << 1)) & 0x8000) &&
            (flagged_count += 1,
             ((s16)count_flagged_cells_in_opposite_directions(direction_shifted >> 0x10, tile_x, y) >= 2))) {
            break;
        }
        next_x = x + *x_step;
        x = next_x;
        if (next_x < 0) {
            break;
        }
        if (next_x >= (1 << config->shiftX)) {
            break;
        }
        y_steps = (u8 *)dir_step_y;
        next_y = y + *(u16 *)(y_steps + direction_offset);
        y = next_y;
        if (next_y < 0) {
            break;
        }
        if (next_y >= (1 << config->shiftY)) {
            break;
        }
        steps_left -= 1;
    } while (steps_left > 0);
    return flagged_count;
}

void clear_flagged_cells_and_reset_list(void) {
    u8 *coordinateEntry;
    u16 *cell;
    u16 cellFlags;
    MapGrid *gridDescriptor;
    u8 *gridBase;

    gridDescriptor = &g_game_work.map;
    coordinateEntry = (u8 *)D_80081508[0];
    gridBase = ((u8 *)gridDescriptor->cells);
    if (*coordinateEntry != 0) {
        do {
            cell = (u16 *)(gridBase +
                (coordinateEntry[0] + (coordinateEntry[1] << gridDescriptor->shiftX)) * 2);
            cellFlags = *cell;
            coordinateEntry += 4;
            *cell = cellFlags & 0xBFFF;
        } while (*coordinateEntry != 0);
    }
    tile_key_pair_count[0] = 0;
    *(u8 *)D_80081508[0] = 0;
}

void refresh_state_and_dispatch_angles(void) {
    GameView *state = &g_game_work.view;
    u32 firstScaledAngle;
    u32 secondScaledAngle;
    u32 controlAngle;

    clear_flagged_cells_and_reset_list();
    firstScaledAngle = ((u16)state->camera_position.parts.camera_position_x) >> 6;
    secondScaledAngle = ((u16)state->camera_position.parts.camera_position_y) >> 6;
    controlAngle = ((u16)state->camera_rotation.parts.viewAngle);
    if (controlAngle & 0x3FF) {
        count_flagged_tiles_along_direction(
            ((s32)(((0x400 - controlAngle) & 0xFFF) - 0x400) < 0x801U) * 4,
            firstScaledAngle,
            secondScaledAngle);
    }
}
