#include "common.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    s16 unk8;
    s16 active;
    u8 pad[8];
} DungeonArea;

extern s32 func_8001CE14(s16 value, s32 low, s32 high);
extern void func_8001E108(s32 x, s32 y, s16 *tile, s32 kind, s32 amount);

extern u8 D_8008333C[32];
extern u8 D_800E2970[];
extern u8 D_800EA000[];

/* Update tiles in active dungeon areas, alternating variants in the first tile range. */
void func_8001DE2C(void) {
    DungeonArea *area;
    u32 area_addr_hi;
    register u32 map_config_addr ASM_REG("$8");   /* MATCH pin: keeps a constant in a register as retail does */
    s16 *tile_id;
    s32 area_index;
    s32 x;
    s32 y;
    register s32 start_x ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 width ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 height ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 x_end ASM_REG("$22");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 y_end ASM_REG("$23");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 amount_small ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 amount_large ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */

    area_index = 0;
    amount_small = 0x20;
    amount_large = 0x100;
    area_addr_hi = 0x800E0000;
    ASM_KEEP_NV(area_addr_hi);   /* MATCH pin: retail immediate-load split depends on it */
    area = (DungeonArea *)(area_addr_hi + 0x2970);

outer_loop:
    if (area->active != 0) {
        y = area->y;
        start_x = area->x;
        width = area->width;
        height = area->height;
        x_end = start_x + width;
        y_end = y + height;
        if (y < y_end) {
y_loop:
            x = area->x;
            if (x < x_end) {
x_loop:
                map_config_addr = 0x80080000;
                ASM_KEEP(map_config_addr);   /* MATCH pin: load-bearing for the whole function shape */
                map_config_addr += 0x333C;
                ASM_KEEP_NV(map_config_addr);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                tile_id = (s16 *)&D_800EA000[((y << *(s16 *)(map_config_addr + 0x14)) + x) * 6];
                if (func_8001CE14(*tile_id, 0x13, 0x1C) != 0) {
                    func_8001E108(x, y, tile_id, 0x13, amount_small);
                    if (y & 1) {
                        if (x & 1) {
                            goto update_tile;
                        }
                        goto next_x;
                    }
                    if (x & 1) {
                        goto next_x;
                    }
update_tile:
                    *tile_id += 10;
                    goto next_x;
                }
                if (func_8001CE14(*tile_id, 0x27, 0x30) != 0) {
                    func_8001E108(x, y, tile_id, 0x27, amount_small);
                    goto next_x;
                }
                if (func_8001CE14(*tile_id, 0x31, 0x3A) != 0) {
                    func_8001E108(x, y, tile_id, 0x31, amount_small);
                    goto next_x;
                }
                if (func_8001CE14(*tile_id, 0x3B, 0x44) != 0) {
                    func_8001E108(x, y, tile_id, 0x3B, amount_small);
                    goto next_x;
                }
                if (func_8001CE14(*tile_id, 0x45, 0x4E) != 0) {
                    func_8001E108(x, y, tile_id, 0x45, amount_small);
                    goto next_x;
                }
                if (func_8001CE14(*tile_id, 0x6B, 0x6F) != 0) {
                    func_8001E108(x, y, tile_id, 0x6B, amount_large);
                    goto next_x;
                }
                if (func_8001CE14(*tile_id, 0x70, 0x74) != 0) {
                    func_8001E108(x, y, tile_id, 0x70, amount_large);
                    goto next_x;
                }
                if (func_8001CE14(*tile_id, 0x75, 0x79) != 0) {
                    func_8001E108(x, y, tile_id, 0x75, amount_large);
                    goto next_x;
                }
                if (func_8001CE14(*tile_id, 0x7A, 0x7E) != 0) {
                    func_8001E108(x, y, tile_id, 0x7A, amount_large);
                }
                goto next_x;
next_x:
                x++;
check_x:
                if (x >= x_end) {
                    goto next_y;
                }
                goto x_loop;
            }
next_y:
            y++;
            if (y >= y_end) {
                goto next_area;
            }
            goto y_loop;
        }
    }
next_area:
    area_index++;
    area++;
    if (area_index >= 0x24) {
        return;
    }
    goto outer_loop;
}
