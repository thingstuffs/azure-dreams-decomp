#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

s16 func_8009A350(s16 x, s16 y, s16 offset_index, u16 *flags);
s32 func_800BCB04(s32 x, s32 y, s16 min_height);
extern u16 D_800DCE6C[];
extern u16 D_800DCE8C[];

/* Finds a nearby unblocked position with a distance below 0x200. */
s32 func_800A7234(s16 x, s16 y, s16 z, s16 *out_x, s16 *out_y, s16 *out_distance) {
    u16 tile_flags;
    s32 distance;
    s32 i;
    s16 dir;

    if (func_8009A350(x - 1, y, 0, &tile_flags) != 0 && !(tile_flags & 0x8820)) {
        distance = func_800BCB04(((x << 6) + 0x20) & 0xFFE0, ((y << 6) + 0x20) & 0xFFE0, z - 0x20);
        if ((s16)distance < 0x200) {
            *out_x = x;
            *out_y = y;
            *out_distance = distance;
            return 1;
        }
    }

    dir = dungeonStatus.unk_1E & 7;
    for (i = 0; i < 8; i++, dir = (dir + 1) & 7) {
        if (func_8009A350(x, y, dir, &tile_flags) != 0 && !(tile_flags & 0x8820)) {
            distance = func_800BCB04((((x + dirStepX[dir]) << 6) + 0x20) & 0xFFE0,
                (((y + dirStepY[dir]) << 6) + 0x20) & 0xFFE0, z - 0x20);
            if ((s16)distance < 0x200) {
                *out_x = x + dirStepX[dir];
                *out_y = y + dirStepY[dir];
                *out_distance = distance;
                return 1;
            }
        }
    }

    dir = dungeonStatus.unk_1E & 0xF;
    for (i = 0; i < 0x10; i++, dir = (dir + 1) & 0xF) {
        if (func_8009A350(x + D_800DCE6C[dir] - 1, y + D_800DCE8C[dir], 0, &tile_flags) != 0 && !(tile_flags & 0x8820)) {
            distance = func_800BCB04((((x + (s16)D_800DCE6C[dir]) << 6) + 0x20) & 0xFFE0,
                (((y + (s16)D_800DCE8C[dir]) << 6) + 0x20) & 0xFFE0, z - 0x20);
            if ((s16)distance < 0x200) {
                *out_x = x + D_800DCE6C[dir];
                *out_y = y + D_800DCE8C[dir];
                *out_distance = distance;
                return 1;
            }
        }
    }
    return 0;
}
