/* Relink of matched dungeon/func_80284BEC; every changed retail word is a paired relocation. */
#include "modules/dungeon_floor_generate.h"

s32 func_80017BEC(s16 region_id) {
    s16 *dx = dirStepX;
    s16 *dy = dirStepY;
    s16 x;
    s16 y;
    floor_generate_isolated_80284BEC_S_80017BEC_M *map;
    floor_generate_isolated_80284BEC_S_80017BEC_T *tiles;
    s16 tile_id;
    s16 steps;
    s32 direction;
    s16 next_direction;
    s32 open_count;
    u16 flags;
    s32 idx;

    tiles = (*(floor_generate_isolated_80284BEC_S_80017BEC_M *)D_8008333C).tiles;
    map = &(*(floor_generate_isolated_80284BEC_S_80017BEC_M *)D_8008333C);
    tile_id = func_80017F88(region_id, &x, &y, 0);
    if (tile_id >= 0x200) {
        return 0;
    }
    idx = x + (y << map->unk_14);
    tiles[idx].unk_04 |= 0x100;
    steps = func_80017EBC(region_id);
    for (;;) {
        next_direction = -1;
        open_count = 0;
        for (direction = 7; direction >= 0; direction--) {
            if ((s16)func_80018304(x, y, tile_id, (s16)direction) != 0) {
                floor_generate_isolated_80284BEC_S_80017BEC_T *tile;
                idx = (x + dx[direction]) + ((y + dy[direction]) << map->unk_14);
                tile = (floor_generate_isolated_80284BEC_S_80017BEC_T *)((idx * 6) + (s32)tiles);
                flags = tile->unk_04;
                if (!(flags & 0x100)) {
                    tile->unk_04 = flags | 0x200;
                    next_direction = direction;
                }
                open_count++;
            }
        }
        if (open_count == 0) {
            return 0;
        }
        if (next_direction >= 0) {
            floor_generate_isolated_80284BEC_S_80017BEC_T *tile;
            x += dx[next_direction];
            y += dy[next_direction];
            idx = x + (y << map->unk_14);
            tile = (floor_generate_isolated_80284BEC_S_80017BEC_T *)((idx * 6) + (s32)tiles);
            steps--;
            tile->unk_04 |= 0x100;
            if (steps <= 0) {
                break;
            }
            tile_id = func_800BCB04(((x << 6) + 0x20) & 0xFFE0, ((y << 6) + 0x20) & 0xFFE0, -0x400);
        } else {
            tile_id = func_8001816C(region_id, &x, &y, 1);
            if (tile_id >= 0x200) {
                return 0;
            }
            idx = x + (y << map->unk_14);
            tiles[idx].unk_04 |= 0x100;
            if (--steps <= 0) {
                break;
            }
        }
    }
    return 1;
}
