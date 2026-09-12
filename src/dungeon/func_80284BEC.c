#include "common.h"
#include "m2c_compat.h"

s32 func_80017EBC();
s16 func_80017F88();
s16 func_8001816C();
s32 func_80018304();
M2C_UNK func_800BCB04();
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_8008333C;

typedef struct S_80017BEC_0 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_80017BEC_0;   /* temp_fp in func_80017BEC */

typedef struct S_80017BEC_1 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80017BEC_1;   /* temp_v0 in func_80017BEC */

typedef struct S_80017BEC_2 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80017BEC_2;   /* temp_a0 in func_80017BEC */

typedef struct S_80017BEC_3 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80017BEC_3;   /* temp_v0_3 in func_80017BEC */

typedef struct S_80017BEC_4 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80017BEC_4;   /* temp_v0_4 in func_80017BEC */

/* Marks a path through neighboring tiles, retrying within the region when needed. */
s32 func_80017BEC(s16 region_id) {
    struct {
        s16 sp10;
        s16 sp12;
        s32 pad;
        s16 sp18;
    } cursor;
    s16 *x_step;
    s16 *y_step;
    register s16 next_y ASM_REG("$5");
    register s16 next_x ASM_REG("$6");
    s32 direction;
    s16 next_direction;
    register s16 tile_id ASM_REG("$20");
    s32 *map_info;
    register s32 index_work ASM_REG("$4");
    s32 tiles_base;
    register s32 coord_work ASM_REG("$2");
    s32 open_count;
    s32 steps_left;
    s32 result;
    s32 failure;
    u16 neighbor_flags;
    s32 value_work;
    S_80017BEC_2 *neighbor;
    S_80017BEC_1 *start_tile;
    register S_80017BEC_3 *next_tile ASM_REG("$2");
    S_80017BEC_4 *retry_tile;
    register u8 *lookup_base ASM_REG("$9");
    u16 *next_x_step;

    tiles_base = D_8008333C;
    map_info = &D_8008333C;
    cursor.sp18 = region_id;
    tile_id = func_80017F88(region_id, &cursor.sp10, &cursor.sp12, 0);
    if (tile_id < 0x200) {
        goto mark_start;
    }
failure_return:
    ASM_SCHED_BARRIER();
    failure = 0;
    return failure;
mark_start:
    {
        s32 start_y;
        s32 row_shift;
        register s32 start_x ASM_REG("$4");

        start_y = cursor.sp12;
        row_shift = ((S_80017BEC_0 *)map_info)->unk_14;
        start_x = cursor.sp10;
        start_tile = ((start_x + (start_y << row_shift)) * 6) + tiles_base;
    }
    start_tile->unk_04 = (u16)(start_tile->unk_04 | 0x100);
    steps_left = func_80017EBC(region_id);
scan_neighbors:
    next_direction = -1;
    open_count = 0;
    direction = 7;
    lookup_base = (u8 *)&D_8006CCE8;
    y_step = (s16 *)(lookup_base + 0xE);
    lookup_base = (u8 *)&D_8006CCD8;
    x_step = (s16 *)(lookup_base + 0xE);
    do {
        if ((func_80018304(cursor.sp10, cursor.sp12, tile_id, (s16)direction) << 0x10) != 0) {
            register s32 neighbor_x ASM_REG("$5");

            neighbor_x = cursor.sp10;
            coord_work = *x_step;
            value_work = *y_step;
            neighbor_x += coord_work;
            coord_work = cursor.sp12;
            index_work = ((S_80017BEC_0 *)map_info)->unk_14;
            coord_work += value_work;
            coord_work <<= index_work;
            index_work = neighbor_x + coord_work;
            ASM_KEEP_NV(index_work);
            neighbor = (void *)((index_work * 6) + tiles_base);
            neighbor_flags = neighbor->unk_04;
            if (!(neighbor_flags & 0x100)) {
                neighbor->unk_04 = (u16)(neighbor_flags | 0x200);
                next_direction = direction;
            }
            open_count += 1;
        }
        y_step -= 1;
        direction -= 1;
        x_step -= 1;
    } while (direction >= 0);
    if (open_count != 0) {
        coord_work = (s16)next_direction;
        if (coord_work >= 0) {
            s32 tile_x;
            s16 tile_y;

            coord_work *= 2;
            lookup_base = (u8 *)&D_8006CCD8;
            next_x_step = (u16 *)(lookup_base + coord_work);
            lookup_base = (u8 *)&D_8006CCE8;
            next_tile = lookup_base + coord_work;
            next_x = (u16)cursor.sp10;
            value_work = *next_x_step;
            next_y = (u16)cursor.sp12;
            coord_work = *(u16 *)next_tile;
            next_x += value_work;
            next_y += coord_work;
            coord_work = (u32)(u16)next_x << 16;
            {
                register s32 tile_index ASM_REG("$4");

                tile_x = coord_work >> 16;
                value_work = (u32)(u16)next_y << 16;
                coord_work = ((S_80017BEC_0 *)map_info)->unk_14;
                tile_y = value_work >> 16;
                tile_index = tile_x + (tile_y << coord_work);
                ASM_KEEP_NV(tile_index);
                next_tile = (tile_index * 6) + tiles_base;
            }
            index_work = steps_left - 1;
            steps_left = index_work;
            ASM_KEEP(steps_left);
            value_work = next_tile->unk_04;
            cursor.sp10 = next_x;
            cursor.sp12 = next_y;
            next_tile->unk_04 = (u16)(value_work | 0x100);
            if ((index_work << 0x10) > 0) {
                tile_id = func_800BCB04(((tile_x << 6) + 0x20) & 0xFFE0, ((tile_y << 6) + 0x20) & 0xFFE0, -0x400, tile_x);
                goto scan_neighbors;
            }
            goto success;
        }
        {
            s16 *out_x;
            s16 *out_y;
            s32 retry_mode;
            s32 retry_region;

            lookup_base = (u8 *)(u32)(u16)cursor.sp18;
            out_x = &cursor.sp10;
            ASM_KEEP_NV(out_x);
            out_y = &cursor.sp12;
            retry_mode = 1;
            retry_region = (s16)(u32)lookup_base;
            tile_id = func_8001816C(retry_region, out_x, out_y, retry_mode);
        }
        result = 0;
        if (tile_id < 0x200) {
            s32 retry_y;
            s32 retry_shift;
            register s32 retry_x ASM_REG("$4");

            retry_y = cursor.sp12;
            retry_shift = ((S_80017BEC_0 *)map_info)->unk_14;
            retry_x = cursor.sp10;
            retry_tile = ((retry_x + (retry_y << retry_shift)) * 6) + tiles_base;
            ASM_KEEP(retry_tile);
            index_work = steps_left - 1;
            steps_left = index_work;
            value_work = retry_tile->unk_04;
            index_work <<= 0x10;
            retry_tile->unk_04 = (u16)(value_work | 0x100);
            if (index_work <= 0) {
success:
                result = 1;
                return result;
            }
            goto scan_neighbors;
        }
        return result;
    }
    goto failure_return;
}
