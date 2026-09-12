#include "common.h"

typedef struct S_80016BF0_0 {
    u8 pad_00[0x10];
    u8 * unk_10;
    s16 unk_14;
    s16 unk_16;
} S_80016BF0_0;   /* temp_t0 in func_80016BF0 */

typedef struct S_80016BF0_1 {
    u8 pad_00[0x1DC];
    s32 unk_1DC;
} S_80016BF0_1;   /* temp_base in func_80016BF0 */

typedef struct S_80016BF0_2_pre {
    u16 unk_00;
} S_80016BF0_2_pre;   /* the 0x2 bytes before temp_a0 in func_80016BF0, addressed as temp_a0[-1] */

typedef struct S_80016BF0_2 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
    u8 pad_06[0x4];
    u16 unk_0A;
} S_80016BF0_2;   /* temp_a0 in func_80016BF0 */

typedef struct S_80016BF0_3 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80016BF0_3;   /* temp_v1_4 in func_80016BF0 */

typedef struct S_80016BF0_4 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80016BF0_4;   /* temp_v1_5 in func_80016BF0 */



extern u8 D_80083160[];

/* Apply tile type flags to a map rectangle and mark adjacent tiles where required. */
void func_80016BF0(s16 start_x, s16 start_y, s16 width, s16 height)
{
    s32 tile_y;
    s32 tile_x;
    s32 tiles_base;
    s16 row_width;
    s32 col;
    s32 row;
    u32 tile_id;
    u8 *flag_table;
    u8 *tile_flags;
    u8 *flags;
    u8 *extra_flags;
    void *tile;
    S_80016BF0_0 *map;
    u8 *state;
    S_80016BF0_3 *tile_above;
    S_80016BF0_4 *tile_below;

    state = D_80083160;
    map = state + 0x1DC;
    flag_table = map->unk_10;
    if (flag_table != 0) {
        row = 0;
        tiles_base = ((S_80016BF0_1 *)state)->unk_1DC;
        tile_flags = flag_table;
        if ((height << 0x10) > 0) {
            do {
                col = 0;
                if (width > 0) {
                    tile_y = start_y + row;
                    row_width = width;
                    do {
                        tile = (void *)(tiles_base + (((tile_y << map->unk_14) + start_x + col) * 6));
                        tile_id = ((S_80016BF0_2 *)tile)->unk_00;
                        flags = tile_flags + tile_id;
                        if (*flags & 1) {
                            ((S_80016BF0_2 *)tile)->unk_04 = (u16)(((S_80016BF0_2 *)tile)->unk_04 | 1);
                        }
                        if (*flags & 4) {
                            ((S_80016BF0_2 *)tile)->unk_04 = (u16)(((S_80016BF0_2 *)tile)->unk_04 | 4);
                        }
                        if (*flags & 8) {
                            ((S_80016BF0_2 *)tile)->unk_04 = (u16)(((S_80016BF0_2 *)tile)->unk_04 | 8);
                        }
                        if (*flags & 0x20) {
                            ((S_80016BF0_2 *)tile)->unk_04 = (u16)(((S_80016BF0_2 *)tile)->unk_04 | 0x400);
                        }
                        tile_x = col + start_x;
                        if (*flags & 2) {
                            if (tile_x > 0) {
                                ((S_80016BF0_2_pre *)tile)[-1].unk_00 = (u16)(((S_80016BF0_2_pre *)tile)[-1].unk_00 | 1);
                            }
                            if (tile_x < ((1 << map->unk_14) - 1)) {
                                ((S_80016BF0_2 *)tile)->unk_0A = (u16)(((S_80016BF0_2 *)tile)->unk_0A | 1);
                            }
                            if (tile_y > 0) {
                                tile_above = (void *)((((0 - (1 << map->unk_14)) * 6)) + (u32)tile);
                                tile_above->unk_04 = (u16)(tile_above->unk_04 | 1);
                            }
                            if (tile_y < ((1 << map->unk_16) - 1)) {
                                tile_below = (u8 *)tile + (6 << map->unk_14);
                                tile_below->unk_04 = (u16)(tile_below->unk_04 | 1);
                            }
                        }
                        extra_flags = tile_flags + tile_id;
                        if (*extra_flags & 0x80) {
                            ((S_80016BF0_2 *)tile)->unk_04 = (u16)(((S_80016BF0_2 *)tile)->unk_04 | 0x8000);
                        }
                        if (*extra_flags & 0x40) {
                            ((S_80016BF0_2 *)tile)->unk_04 = (u16)(((S_80016BF0_2 *)tile)->unk_04 | 0x40);
                        }
                        col += 1;
                    } while (col < row_width);
                }
                row += 1;
            } while (row < height);
        }
    }
}

/* MECHANISM: The 8-byte leaf frame preserves width in pinned s0; the body
   holds the D_80083160 base through the early branch and hoists its 0x1dc
   table pointer before both nested loops. The map pointer and signed inner
   bound split v1->t4 and s0->t5; BASE[index] fixes the neighbor addu order. */
