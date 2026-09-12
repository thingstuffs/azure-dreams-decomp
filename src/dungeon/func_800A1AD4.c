#include "common.h"

extern u16 D_8008347E[];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
s32 func_8009A350();
s32 func_800BCB04();
extern u16 D_800DCE6C[];
extern u16 D_800DCE8C[];

/* Finds a nearby unblocked position with a distance below 0x200. */
s32 func_800A7234(s32 x, s32 y, s32 z, s16 *out_x, s16 *out_y, s16 *out_distance) {
    u16 tile_flags;
    s32 tile_valid;
    s32 packed_x;
    s32 probe_x;
    s32 distance;
    s32 shifted_x;
    s32 shifted_y;
    s32 inner_x;
    s32 inner_y;
    s32 outer_x;
    s32 inner_count;
    s32 inner_dir;
    register s32 outer_count ASM_REG("$19");
    register s32 outer_dir ASM_REG("$17");
    s32 call_dir;
    register s32 call_x ASM_REG("$4");
    register s32 call_y ASM_REG("$5");
    register s32 distance_z ASM_REG("$6");
    register s32 probe_dir ASM_REG("$6");
    register u16 *flags_ptr ASM_REG("$7");
    s32 inner_offset;
    s32 outer_offset;
    register u32 addr ASM_REG("$8");
    s32 zero = 0;
    s32 next_inner_dir;
    register s32 next_outer_dir ASM_REG("$2");
    register u16 dir_seed ASM_REG("$3");
    register s32 base_x ASM_REG("$22");
    register s32 base_y ASM_REG("$23");
    s32 base_z;
    u16 *dx;
    u16 *dy;
    register s32 saved_x ASM_REG("$16");
    register s32 saved_y ASM_REG("$17");
    register s32 saved_z ASM_REG("$19");
    s32 probe_y;
    register s32 found_x ASM_REG("$2");
    register s32 found_y ASM_REG("$3");

    saved_x = x;
    saved_y = y;
    saved_z = z;
    ASM_KEEP_NV(saved_x);
    probe_x = (s16)(saved_x - 1);
    probe_y = (s16)saved_y;
    tile_valid = func_8009A350(probe_x, probe_y, 0, &tile_flags);
    base_x = saved_x;
    base_y = saved_y;
    base_z = saved_z;
    if ((tile_valid << 0x10) != 0) {
        if (!(tile_flags & 0x8820)) {
            packed_x = saved_x << 0x10;
            distance = func_800BCB04((((packed_x >> 0xA) + 0x20) & 0xFFE0), ((probe_y << 6) + 0x20) & 0xFFE0, (s16)(saved_z - 0x20));
            if ((s16)distance < 0x200) {
                addr = (u32)out_x;
                ASM_KEEP_NV(addr);
                *(s16 *)addr = (s16)saved_x;
                addr = (u32)out_y;
                ASM_KEEP_NV(addr);
                *(s16 *)addr = (s16)saved_y;
                goto store_result;
            }
        }
    }

    goto scan_start;
found:
    found_x = *dx;
    ASM_KEEP(found_x);
    addr = (u32)out_x;
    ASM_KEEP_NV(addr);
    found_x = base_x + found_x;
    *(s16 *)addr = found_x;
    found_y = *dy;
    ASM_KEEP(found_y);
    addr = (u32)out_y;
    ASM_KEEP_NV(addr);
    found_y = base_y + found_y;
    *(s16 *)addr = found_y;
store_result:
    addr = (u32)out_distance;
    ASM_KEEP(addr);
    *(s16 *)addr = distance;
    return 1;
scan_start:
    shifted_x = base_x << 0x10;
    inner_x = shifted_x >> 0x10;
    shifted_y = base_y << 0x10;
    inner_y = shifted_y >> 0x10;
    inner_count = 0;
    dir_seed = D_8008347E[0];
    inner_dir = dir_seed & 7;
scan_inner:
    call_x = inner_x;
    call_y = inner_y;
    call_dir = inner_dir;
    ASM_KEEP_NV(call_dir);
    if (((func_8009A350(call_x, call_y, call_dir, &tile_flags) << 0x10) == 0) || (tile_flags & 0x8820)) {
        goto next_inner;
    }
    inner_offset = call_dir << 1;
    do {
        addr = (u32)D_8006CCD8;
    } while (0);
    dx = (u16 *)(inner_offset + addr);
    distance_z = (s16)(base_z - 0x20);
    dy = (u16 *)((u8 *)D_8006CCE8 + inner_offset);
    distance = func_800BCB04(((((inner_x + (s16)*dx) << 6) + 0x20) & 0xFFE0), ((((inner_y + (s16)*dy) << 6) + 0x20) & 0xFFE0), distance_z);
    if ((s16)distance < 0x200) {
        goto found;
    }
next_inner:
    inner_count += 1;
    next_inner_dir = inner_dir + 1;
    inner_dir = next_inner_dir & 7;
    if (inner_count < 8) {
        goto scan_inner;
    }

    outer_count = 0;
    outer_x = (base_x << 0x10) >> 0x10;
    dir_seed = D_8008347E[0];
    probe_x = (base_y << 0x10) >> 0x10;
    outer_dir = dir_seed & 0xF;
scan_outer:
    probe_dir = zero;
    outer_offset = outer_dir << 1;
    do {
        addr = (u32)D_800DCE6C;
    } while (0);
    dx = (u16 *)(outer_offset + addr);
    flags_ptr = &tile_flags;
    ASM_KEEP_NV(flags_ptr);
    addr = (u32)D_800DCE8C;
    dy = (u16 *)(outer_offset + addr);
    call_x = *dx;
    ASM_KEEP_NV(call_x);
    call_y = *dy;
    ASM_KEEP_NV(call_y);
    call_x = (s16)(base_x + call_x - 1);
    call_y = (s16)(base_y + call_y);
    if (((func_8009A350(call_x, call_y, probe_dir, flags_ptr) << 0x10) == 0) || (tile_flags & 0x8820)) {
        goto next_outer;
    }
    call_x = (s16)*dx;
    call_y = (s16)*dy;
    call_x = (((outer_x + call_x) << 6) + 0x20) & 0xFFE0;
    call_y = (((probe_x + call_y) << 6) + 0x20) & 0xFFE0;
    distance = func_800BCB04(call_x, call_y, (s16)(base_z - 0x20));
    if ((s16)distance < 0x200) {
        goto found;
    }
next_outer:
    outer_count += 1;
    next_outer_dir = outer_dir + 1;
    outer_dir = next_outer_dir & 0xF;
    if (outer_count < 0x10) {
        goto scan_outer;
    }
    return 0;
}
