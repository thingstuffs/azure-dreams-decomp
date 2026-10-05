#include "common.h"
#include "shared/dir_step.h"


s32 func_8009A350(s16 x, s16 y, s16 offset_index, u16 *flags);
s16 func_800BCB04(s32 x, s32 y, s16 min_height);

/* Tests for a flagged floor or a height above 0x200 at the layer-offset cell. */
s32 func_800A44E0(u16 x, u16 y, s16 height, u32 flags)
{
    s16 floor_height;
    s16 offset_height;
    s32 probe_height;
    s32 layer_offset;
    u16 offset_cell_x;
    u16 offset_cell_y;
    u16 *x_offsets;
    u16 *layer_x_offset;
    u16 *layer_y_offset;
    s16 saved_height;
    u32 cell_x;
    u32 cell_y;
    s32 layer;
    s32 query_cell_x;
    s32 query_cell_y;

    saved_height = height;
    cell_x = x >> 6;
    query_cell_x = cell_x;
    cell_y = y >> 6;
    query_cell_y = cell_y;
    layer = (flags >> 9) & 7;

    if ((func_8009A350(query_cell_x, query_cell_y, layer, &floor_height) << 16) == 0) {
        return 0;
    }
    if (floor_height & 0x8000) {
        return 1;
    }

    probe_height = (s16)(saved_height - 0x20);
    x_offsets = (u16 *)((s8 *)dirStepX);
    layer_offset = layer * 2;
    layer_x_offset = (u16 *)((s8 *)x_offsets + layer_offset);
    layer_y_offset = (u16 *)((s8 *)((s8 *)dirStepY) + layer_offset);
    offset_cell_x = *layer_x_offset + cell_x;
    offset_cell_y = *layer_y_offset + cell_y;
    offset_height = func_800BCB04(
        ((((offset_cell_x) & 0xFFFF) << 6) + 0x20) & 0xFFE0,
        ((((offset_cell_y) & 0xFFFF) << 6) + 0x20) & 0xFFE0,
        probe_height);
    floor_height = offset_height;
    return (offset_height << 16) > 0x02000000;
}
