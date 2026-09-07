#include "common.h"

extern s32 func_8009A350();
extern s32 func_800BCB04();

/* Checks whether the current and offset tile centers both yield values above 0x200. */
s32 func_800A4778(s32 x, s32 y, s32 z, s32 skip_check) {
    register s32 source_x ASM_REG("$19") = x;   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 source_y = y;
    s16 probe_result;
    s16 center_result;
    register s32 center_delta ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 x_distance;
    s32 y_distance;
    register s32 center_x ASM_REG("$16");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 probe_coord;
    register s32 source_z ASM_REG("$21");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 center_y;
    s32 x_offset;
    s32 x_step;
    s32 y_offset;
    u32 probe_x;
    register u32 probe_y ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 probe_z ASM_REG("$6");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u32 coord_work ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    ASM_KEEP_NV(source_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
    probe_coord = z;
    coord_work = source_x;
    source_z = probe_coord;
    if (skip_check == 0) {
        coord_work = (u32) (coord_work & 0xFFFF) >> 6;
        probe_x = coord_work - 1;
        probe_y = (u32) (source_y & 0xFFFF) >> 6;
        probe_z = 0;
        ASM_USE(probe_z);   /* MATCH pin: keeps a statement from moving across a call/branch */
        center_x = coord_work;
        center_y = probe_y;
        if ((func_8009A350(probe_x, probe_y, probe_z, &probe_result) << 0x10) != 0) {
            coord_work = center_x << 6;
            ASM_KEEP(coord_work);   /* MATCH pin: load-bearing for the whole function shape */
            center_x = coord_work + 0x20;
            probe_x = center_x & 0xFFE0;
            coord_work = center_y << 6;
            ASM_KEEP(coord_work);   /* MATCH pin: load-bearing for the whole function shape */
            coord_work += 0x20;
            probe_y = coord_work & 0xFFE0;
            probe_z = (s16) (probe_coord - 0x20);
            center_y = coord_work;
            center_result = func_800BCB04(probe_x, probe_y, probe_z);
            probe_result = center_result;
            if (center_result >= 0x201) {
                probe_coord = center_x;
                ASM_KEEP_NV(center_x);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                coord_work = center_x - source_x;
                center_delta = (s16) coord_work;
                x_distance = center_delta;
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
                coord_work = center_y - source_y;
                center_delta = (s16) coord_work;
                y_distance = center_delta;
                if (center_delta < 0) {
                    y_distance = 0 - y_distance;
                }
                if (y_distance >= 0x16) {
                    y_offset = 0x40;
                    if (center_delta > 0) {
                        y_offset = -0x40;
                    }
                } else {
                    y_offset = 0;
                }
                probe_result = func_800BCB04((probe_coord + x_offset) & 0xFFFF, (center_y + y_offset) & 0xFFFF, (s16) (source_z - 0x20));
                return probe_result > 0x200;
            }
        }
    }
    return 0;
}
