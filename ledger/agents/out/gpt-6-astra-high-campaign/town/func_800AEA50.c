#include "common.h"

extern s16 func_800ABEEC(s16, s32, s32);
extern s8 D_8006CCD8[9];
extern s8 D_8006CCE8[9];

typedef struct {
    u8 *field0;
    u8 unk04[0x10];
    s16 field14;
    s16 field16;
} Config;

extern Config D_8008333C;

/* Counts flagged tiles along a direction for up to ten in-bounds positions. */
s32 func_800AC1B0(s16 direction, s16 start_x, s16 start_y, s32 unused) {
    u16 *tiles;
    u16 *tile_data;
    Config *config;
    s32 bounds_one;
    s16 next_x;
    s16 next_y;
    register s16 y ASM_REG("$18");
    register s16 x ASM_REG("$19");
    s32 tile_x;
    s32 direction_offset;
    register s32 steps_left ASM_REG("$17");
    register s16 flagged_count ASM_REG("$20");
    s32 result;
    s32 x_shifted;
    s32 direction_shifted;
    register s32 step_one ASM_REG("$23");
    u16 *x_step;
    u8 *x_steps;

    bounds_one = unused;
    x = start_x;
    y = start_y;
    steps_left = 0xA;
    flagged_count = 0;
    config = &D_8008333C;
    tile_data = *(u16 **)&D_8008333C;
    tiles = tile_data;
    if (start_x < 0) {
        goto invalid_position;
    }
    bounds_one = 1;
    if (start_x >= (bounds_one << config->field14)) {
        goto invalid_position;
    }
    if (start_y < 0) {
        return 0;
    }
    if (start_y < (bounds_one << config->field16)) {
        goto scan_start;
    }
invalid_position:
    return 0;
scan_start:
    direction_shifted = direction << 0x10;
    x_steps = (u8 *)&D_8006CCD8;
    direction_offset = direction_shifted >> 0xF;
    x_step = (u16 *)(x_steps + direction_offset);
    step_one = 1;
scan_next:
    x_shifted = x << 0x10;
    tile_x = x_shifted >> 0x10;
    if (!(*(u16 *)((u8 *)tiles +
                  ((tile_x + (y << config->field14)) << 1)) & 0x8000) ||
        (flagged_count += 1,
         (func_800ABEEC((s16)(direction_shifted >> 0x10), tile_x, y) < 2))) {
        next_x = x + *x_step;
        x = next_x;
        if (next_x >= 0) {
            if (next_x < (step_one << config->field14)) {
                next_y = y + *(u16 *)((u8 *)&D_8006CCE8 + direction_offset);
                y = next_y;
                if (next_y >= 0) {
                    if (next_y < (step_one << config->field16)) {
                        steps_left -= 1;
                        if (steps_left <= 0) {
                            goto scan_done;
                        }
                        goto scan_next;
                    }
                }
            } else {
scan_done:
                ;
            }
        }
    }
    result = flagged_count;
    return result;
}
