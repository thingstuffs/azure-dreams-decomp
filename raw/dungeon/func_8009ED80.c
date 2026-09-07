#include "common.h"

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;

s32 func_8009A350(s32 x, s32 y, s32 layer, s16 *height);
s16 func_800BCB04(s32 x, s32 y, s32 height);

s32 func_800A44E0(u16 x, u16 y, s16 height, u32 flags)
{
    s16 floor_height;
    s16 moved_height;
    s32 z;
    s32 table_offset;
    s32 x_sum;
    s32 y_sum;
    u16 *x_base;
    u16 *x_offset;
    u16 *y_offset;
    register s16 saved_height ASM_REG("$17");
    register u32 cell_x ASM_REG("$19");
    register u32 cell_y ASM_REG("$18");
    register s32 layer ASM_REG("$16");
    register s32 call_x ASM_REG("$4");
    register s32 call_y ASM_REG("$5");

    saved_height = height;
    cell_x = x >> 6;
    call_x = cell_x;
    ASM_KEEP_NV(call_x);
    cell_y = y >> 6;
    call_y = cell_y;
    ASM_KEEP_NV(call_y);
    layer = (flags >> 9) & 7;

    if ((func_8009A350(call_x, call_y, layer, &floor_height) << 16) == 0) {
        return 0;
    }
    if (floor_height & 0x8000) {
        return 1;
    }

    ASM_KEEP(saved_height);
    ASM_KEEP(cell_x);
    ASM_KEEP(cell_y);
    ASM_KEEP(layer);
    z = (s16)(saved_height - 0x20);
    ASM_KEEP(z);
    x_base = (u16 *)&D_8006CCD8;
    table_offset = layer * 2;
    x_offset = (u16 *)((s8 *)x_base + table_offset);
    y_offset = (u16 *)((s8 *)&D_8006CCE8 + table_offset);
    ASM_KEEP(layer);
    x_sum = *x_offset + cell_x;
    y_sum = *y_offset + cell_y;
    ASM_USE2(x_sum, y_sum);
    moved_height = func_800BCB04(
        ((((x_sum) & 0xFFFF) << 6) + 0x20) & 0xFFE0,
        ((((y_sum) & 0xFFFF) << 6) + 0x20) & 0xFFE0,
        z);
    floor_height = moved_height;
    return (moved_height << 16) > 0x02000000;
}

/* MECHANISM: The 0x30 frame pins s1=height, s3/s2=cells, and s0=layer; s32 z forces one sign extension.
   Named table pointers, a shared byte offset, and paired sums reproduce the base/index/load order.
   Immediate a0/a1 call locals with ASM_KEEP_NV preserve progressive moves without save-scatter. */
