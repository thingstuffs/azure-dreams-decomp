#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u32 word0;
    u32 word1;
} __attribute__((packed)) UA64;

struct S_8003E2D8 {
    char pad0[8];
    s32 field_8;
    s32 field_C;
    s32 field_10;
};
typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern u8 D_80082E80[];
extern s8 D_800E2970[];
extern u8 D_800E50A8[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern void func_800672D8(void *, u8 *);
extern u8 D_80088CB0;
extern u8 D_800EA000[];

typedef struct S_8009D3B0_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
} S_8009D3B0_0;   /* temp_t3 in func_8009D3B0 */

typedef struct S_8009D3B0_1 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_8009D3B0_1;   /* temp_t8 in func_8009D3B0 */

typedef struct S_8009D3B0_2 {
    u16 unk_00;
    u16 unk_02;
} S_8009D3B0_2;   /* var_a2 in func_8009D3B0 */

/* Update packed map levels for the current region or neighboring tiles, then submit the map. */
void func_8009D3B0(void) {
    UA64 map_params;
    s16 neighbor_x;
    register s32 x_limit ASM_REG("$14");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 x_limit_shifted ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 next_coord;
    s32 tile_value;
    s16 x;
    s16 x_end_or_neighbor;
    register s16 y ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 next_x;
    s32 y_limit;
    M2C_UNK offset_index;
    s32 x_sum;
    s32 next_x_shifted;
    s32 level_shifted;
    s32 map_index;
    s32 neighbor_level_shifted;
    register s16 y_end ASM_REG("$15");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *tile_or_map;
    u8 *grid_config;
    register s32 tile_index_or_level ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register u8 *status_or_level ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s8 region_index;

    tile_or_map = &D_80088CB0;
    map_params = *(UA64 *)tile_or_map;
    tile_index_or_level = (s32)&D_80083160;
    grid_config = (u8 *)tile_index_or_level + 0x1DC;
    status_or_level = D_80082E80;
    region_index = ((s8 *)status_or_level)[0x26];
    if (region_index >= 0) {
        register u8 *region ASM_REG("$11");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u8 *grid;
        u8 *map;
        s32 row_y;
        s32 row_x_end;
        s32 x_shifted;
        s32 column_x;
        s32 coord_shifted;
        s32 excluded_tile_type;
        register s32 packed_levels ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        tile_index_or_level = region_index * 0x14;
        status_or_level = (u8 *)D_800E2970;
        region = tile_index_or_level + status_or_level;
        tile_index_or_level = ((S_8009D3B0_0 *)region)->unk_02 - 1;
        y = tile_index_or_level;
        x_sum = ((S_8009D3B0_0 *)region)->unk_00 + ((S_8009D3B0_0 *)region)->unk_04;
        tile_value = x_sum + 1;
        ASM_KEEP(x_sum);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        y_limit = ((S_8009D3B0_0 *)region)->unk_06 + tile_index_or_level + 2;
        y_end = y_limit;
        if ((tile_index_or_level << 0x10) < (y_limit << 0x10)) {
            x_end_or_neighbor = tile_value;
            x_limit_shifted = tile_value << 0x10;
            x_limit = x_limit_shifted >> 0x10;
            grid = D_800EA000;
            map = D_800E50A8;
scan_row:
            next_coord = ((S_8009D3B0_0 *)region)->unk_00 - 1;
            x = next_coord;
            if (next_coord < x_limit) {
                ASM_KEEP(y);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                next_x_shifted = x << 0x10;
                coord_shifted = y << 0x10;
                row_y = coord_shifted >> 0x10;
                coord_shifted = x_end_or_neighbor << 0x10;
                row_x_end = coord_shifted >> 0x10;
scan_tile:
                x_shifted = x << 0x10;
                column_x = x_shifted >> 0x10;
                tile_index_or_level = (row_y << ((S_8009D3B0_1 *)grid_config)->unk_14) + column_x;
                tile_or_map = (u8 *)((tile_index_or_level * 6) + (s32)grid);
                tile_value = ((S_8009D3B0_2 *)tile_or_map)->unk_00;
                if (tile_value != 0) {
                    ASM_KEEP(x);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                    excluded_tile_type = 3;
                    if (tile_value != excluded_tile_type) {
                        ASM_KEEP(tile_index_or_level);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                        map_index = tile_index_or_level / 2;
                        ASM_KEEP(tile_index_or_level);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                        tile_index_or_level = ((S_8009D3B0_2 *)tile_or_map)->unk_02;
                        tile_or_map = (u8 *)(map_index + (s32)map);
                        status_or_level = (u8 *)((s16)(tile_index_or_level + 0x200) / 64);
                        tile_value = (s32)status_or_level;
                        ASM_KEEP(status_or_level);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        tile_index_or_level = (s32)status_or_level;
                        if (tile_index_or_level >= 0x10) {
                            tile_value = 15;
                            goto clamp_region_level;
                        }
                        level_shifted = tile_value << 0x10;
                        if (tile_index_or_level <= 0) {
                            tile_value = 1;
clamp_region_level:
                            level_shifted = tile_value << 0x10;
                        }
                        tile_index_or_level = level_shifted >> 0x10;
                        tile_value = *tile_or_map;
                        if (x & 1) {
                            packed_levels = tile_value | (tile_index_or_level << 4);
                        } else {
                            packed_levels = tile_value | tile_index_or_level;
                        }
                        *tile_or_map = packed_levels;
                    }
                }
advance_x:
                next_x = x + 1;
                x = next_x;
                next_x_shifted = next_x << 0x10;
                if (next_x >= row_x_end) {
                    next_coord = y + 1;
                    goto advance_y;
                }
                goto scan_tile;
            }
advance_y:
            next_coord = y + 1;
            y = next_coord;
            if ((next_coord << 0x10) < (y_end << 0x10)) {
                goto scan_row;
            }
            goto done;
        }
    } else {
        u8 *position;
        register s32 neighbor_packed_levels ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 excluded_neighbor_type;
        s16 next_neighbor;
        s32 neighbor_value;
        u8 *x_offsets;
        u8 *y_offsets;
        u8 *grid;
        u8 *map;
        x_end_or_neighbor = 7;
        position = status_or_level;
        x_offsets = D_8006CCD8;
        y_offsets = D_8006CCE8;
        grid = D_800EA000;
        map = D_800E50A8;
scan_neighbor:
        offset_index = (x_end_or_neighbor << 0x10) >> 0xF;
        neighbor_x = position[0x24] + *(u16 *)(offset_index + (s32)x_offsets);
        tile_index_or_level = ((s16) (position[0x25] + *(u16 *)(offset_index + (s32)y_offsets)) << ((S_8009D3B0_1 *)grid_config)->unk_14) + neighbor_x;
        tile_or_map = (u8 *)((tile_index_or_level * 6) + (s32)grid);
        neighbor_value = ((S_8009D3B0_2 *)tile_or_map)->unk_00;
        if (neighbor_value != 0) {
            ASM_KEEP(neighbor_x);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            excluded_neighbor_type = 3;
            if (neighbor_value != excluded_neighbor_type) {
                ASM_KEEP(tile_index_or_level);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                map_index = tile_index_or_level / 2;
                ASM_KEEP(tile_index_or_level);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                tile_index_or_level = ((S_8009D3B0_2 *)tile_or_map)->unk_02;
                tile_or_map = (u8 *)(map_index + (s32)map);
                status_or_level = (u8 *)((s16)(tile_index_or_level + 0x200) / 64);
                neighbor_value = (s32)status_or_level;
                ASM_KEEP(status_or_level);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                tile_index_or_level = (s32)status_or_level;
                if (tile_index_or_level >= 0x10) {
                    neighbor_value = 15;
                    goto clamp_neighbor_level;
                }
                neighbor_level_shifted = neighbor_value << 0x10;
                if (tile_index_or_level <= 0) {
                    neighbor_value = 1;
clamp_neighbor_level:
                    neighbor_level_shifted = neighbor_value << 0x10;
                }
                tile_index_or_level = neighbor_level_shifted >> 0x10;
                neighbor_value = *tile_or_map;
                if (neighbor_x & 1) {
                    neighbor_packed_levels = neighbor_value | (tile_index_or_level << 4);
                } else {
                    neighbor_packed_levels = neighbor_value | tile_index_or_level;
                }
                *tile_or_map = neighbor_packed_levels;
            }
        }
advance_neighbor:
        next_neighbor = x_end_or_neighbor - 1;
        x_end_or_neighbor = next_neighbor;
        if ((next_neighbor << 0x10) < 0) {
            goto done;
        }
        goto scan_neighbor;
    }
done:
    return func_800672D8(&map_params, D_800E50A8);
}
