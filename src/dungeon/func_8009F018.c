#include "common.h"

extern s16 func_8009A350();
extern s32 func_800BCB04();

/* Checks whether the current and offset tile centers both yield values above 0x200. */
s16 func_800A4778(u16 x, u16 y, s32 z, void *skip_check) {
    s16 probe_result;
    s16 center_result;
    s32 center_delta;
    s32 x_distance;
    u32 center_x;
    s16 source_z;
    u32 center_y;
    u16 start_y;
    u16 start_x;
    s32 x_offset;
    s32 x_step;
    s32 y_offset;
    u32 probe_x;
    u32 probe_y;
    u32 cell;
    u32 cell_y;
    u32 coord_work;

    source_z = z;
    if (skip_check == 0) {
        cell = x >> 6;
        probe_x = cell - 1;
        cell_y = y >> 6;
        start_x = cell;
        start_y = cell_y;
        if (func_8009A350(probe_x, cell_y, 0, &probe_result) != 0) {
            center_x = (start_x << 6) + 0x20;
            probe_x = center_x & 0xFFE0;
            coord_work = (start_y << 6) + 0x20;
            probe_y = coord_work & 0xFFE0;
            center_y = coord_work;
            center_result = func_800BCB04(probe_x, probe_y, (s16) (z - 0x20));
            probe_result = center_result;
            z = center_x;
            if (center_result >= 0x201) {
                center_delta = (s16) (center_x - x);
                x_distance = (s32) (s16) center_delta;
                if (center_delta < 0) {
                    x_distance = 0 - x_distance;
                }
                x_offset = 0;
                if (x_distance >= 0x16) {
                    x_step = 0x40;
                    if (center_delta > 0) {
                        x_step = -0x40;
                    }
                    x_offset = x_step;
                }
                center_delta = (s16) (center_y - y);
                y_offset = (s32) (s16) center_delta;
                if (center_delta < 0) {
                    y_offset = 0 - y_offset;
                }
                if (y_offset >= 0x16) {
                    y_offset = 0x40;
                    if (center_delta > 0) {
                        y_offset = -0x40;
                    }
                } else {
                    y_offset = 0;
                }
                probe_result = func_800BCB04((z + x_offset) & 0xFFFF, (center_y + y_offset) & 0xFFFF,
                    (s16) (source_z - 0x20));
                center_x = probe_result > 0x200;
                return center_x;
            }
        }
    }
    return 0;
}
