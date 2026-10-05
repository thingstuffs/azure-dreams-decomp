#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

extern s16 func_800ABEEC(s32 dir, s16 start_x, s16 start_y);

typedef struct {
    u8 *field0;
    u8 unk04[0x10];
    s16 field14;
    s16 field16;
} Config;


/* Counts flagged tiles along a direction for up to ten in-bounds positions. */
s32 func_800AC1B0(s16 direction, s16 start_x, s16 start_y, s32 unused) {
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
    config = &gameWork.map;
    tiles = *(u16 **)((Config *)((u8 *)&gameWork + 476));
    if (start_x < 0 || start_x >= (1 << config->shiftX) || start_y < 0 || start_y >= (1 << config->shiftY)) {
        return 0;
    }
    direction_shifted = direction << 0x10;
    x_steps = (u8 *)dirStepX;
    direction_offset = direction_shifted >> 0xF;
    x_step = (u16 *)(x_steps + direction_offset);
    do {
        tile_x = x;
        if ((*(u16 *)((u8 *)tiles + ((tile_x + (y << config->shiftX)) << 1)) & 0x8000) &&
            (flagged_count += 1,
             (func_800ABEEC(direction_shifted >> 0x10, tile_x, y) >= 2))) {
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
        y_steps = (u8 *)dirStepY;
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
