#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    s16 unk8;
    s16 active;
    u8 pad[8];
} DungeonArea;

extern s32 func_8001CE14(s16 value, s32 lower_bound, s16 upper_bound);
extern void func_8001E108(s32 x, s32 y, s16 *tile, s32 kind, s32 amount);

extern u8 D_800EA000[];

/* Update tiles in active dungeon areas, alternating variants in the first tile range. */
void func_8001DE2C(void) {
    DungeonArea *area;
    s16 *map_config = (s16 *)&gameWork.map;
    s16 *tile_id;
    s32 area_index;
    s32 x;
    s32 y;
    s32 start_x;
    s32 width;
    s32 height;
    s32 x_end;
    s32 y_end;
    s32 amount_small;
    s32 amount_large;

    area_index = 0;
    amount_small = 0x20;
    amount_large = 0x100;
    area = (DungeonArea *)D_800E2970;

outer_loop:
    if (area->active != 0) {
        y = area->y;
        start_x = area->x;
        width = area->width;
        height = area->height;
        x_end = start_x + width;
        y_end = y + height;
        for (; y < y_end; y++) {
            x = area->x;
            if (x < x_end) {
x_loop_done:
                tile_id = (s16 *)&D_800EA000[((y << map_config[10]) + x) * 6];
                if (func_8001CE14(*tile_id, 0x13, 0x1C) != 0) {
                    func_8001E108(x, y, tile_id, 0x13, amount_small);
                    if ((y & 1) ? (x & 1) : !(x & 1)) {
                        *tile_id += 10;
                    }
                } else if (func_8001CE14(*tile_id, 0x27, 0x30) != 0) {
                    func_8001E108(x, y, tile_id, 0x27, amount_small);
                } else if (func_8001CE14(*tile_id, 0x31, 0x3A) != 0) {
                    func_8001E108(x, y, tile_id, 0x31, amount_small);
                } else if (func_8001CE14(*tile_id, 0x3B, 0x44) != 0) {
                    func_8001E108(x, y, tile_id, 0x3B, amount_small);
                } else if (func_8001CE14(*tile_id, 0x45, 0x4E) != 0) {
                    func_8001E108(x, y, tile_id, 0x45, amount_small);
                } else if (func_8001CE14(*tile_id, 0x6B, 0x6F) != 0) {
                    func_8001E108(x, y, tile_id, 0x6B, amount_large);
                } else if (func_8001CE14(*tile_id, 0x70, 0x74) != 0) {
                    func_8001E108(x, y, tile_id, 0x70, amount_large);
                } else if (func_8001CE14(*tile_id, 0x75, 0x79) != 0) {
                    func_8001E108(x, y, tile_id, 0x75, amount_large);
                } else if (func_8001CE14(*tile_id, 0x7A, 0x7E) != 0) {
                    func_8001E108(x, y, tile_id, 0x7A, amount_large);
                }
                x++;
                if (x >= x_end) {
                    continue;
                }
                goto x_loop_done;
            }
        }
    }
    area_index++;
    area++;
    if (area_index >= 0x24) {
        return;
    }
    goto outer_loop;
}
