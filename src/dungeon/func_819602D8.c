#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

extern u16 D_800273CC[8];
extern u8 D_8002744C[9];
extern u8 D_8002744D[9];
extern s16 D_8008333C_second[16] __asm__("D_8008333C");
extern s32 D_800274DC[7][8];
s32 func_80025D30(s32, s32, s32);
void *func_8009B4B0(void *, u16, u16);
s32 func_800BCA68(s32, u16);
extern s32 D_8002732C;

typedef struct S_819602D8_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_819602D8_0;   /* temp_v0 in func_819602D8 */

/* Sample a 7 by 7 area around the given tile and flag the tiles found there. */
void func_819602D8(u16 center_x, s32 center_y) {
    MapGrid *width_ref = &gameWork.map;
    s16 *height_ref = D_8008333C_second;
    s32 one = 1;
    s16 tile_x;
    s32 signed_y;
    s32 tile_y;
    u8 *sample_row;
    s32 world_y;
    s32 sample_y;
    u16 *sample_ptr;
    u32 col;
    u32 row;
    s32 sample_x;
    s32 tile_sample;
    void *map;
    S_819602D8_0 *tile;
    u32 output_row;
    s32 output_value;

    tile_y = center_y - 3;
    row = 0;
    sample_row = D_800273CC;
    *D_8002744C = center_x;
    *D_8002744D = center_y;
    do {
        tile_x = center_x - 3;
        col = 0;
        tile_sample = tile_y << 16;
        signed_y = tile_sample >> 16;
        world_y = signed_y;
        world_y <<= 6;
        sample_y = world_y + 0x20;
        sample_ptr = (u16 *)sample_row;
        do {
            tile_sample = func_800BCA68((tile_x << 6) & 0xFFC0, world_y);
            map = ((u8 *)D_800E3D7C);
            *sample_ptr = 0 - tile_sample;
            tile = func_8009B4B0(map, tile_x, tile_y);
            if ((tile != NULL) && (tile != D_8002732C)) {
                tile->unk_14 = (s32)(tile->unk_14 | 0x100000);
            }
            sample_x = (s16)tile_x;
            if (sample_x < 0 || sample_x >= (one << width_ref->shiftX) || signed_y < 0 ||
                signed_y >= (one << height_ref[11])) {
                output_value = 0;
            } else {
                sample_x <<= 6;
                sample_x += 0x20;
                sample_x &= 0xFFE0;
                output_value = func_80025D30(sample_x, sample_y & 0xFFFF, -0x400);
            }
            tile_sample = (u32)&D_800274DC[0][0];
            output_row = (u32)tile_sample;
            output_row += row << 5;
            ((s32 *)output_row)[col] = output_value;
            sample_ptr += 1;
            col += 1;
            tile_x += 1;
        } while (col < 7U);
        sample_row += 16;
        row += 1;
        tile_y += 1;
    } while (row < 7U);
}
