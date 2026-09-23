#include "common.h"

typedef struct S_8001A760_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    void * unk_1C;
    u8 pad_20[0x10];
    void ** unk_30;
} S_8001A760_0;   /* ctx in func_8001A760 */

typedef struct S_8001A760_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
} S_8001A760_1;   /* tile in func_8001A760 */

typedef struct S_8001A760_2 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8001A760_2;   /* out1 in func_8001A760 */

typedef struct S_8001A760_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8001A760_3;   /* out2 in func_8001A760 */



extern u8 D_80016000[0x10];

/* Set destination coordinates from the tile center and scaled offsets. */
void func_8001A760(s32 unused, s32 x_offset, s32 y_offset) {
    S_8001A760_0 *ctx;
    S_8001A760_1 *tile;
    S_8001A760_2 *x_dest;
    S_8001A760_3 *y_dest;
    s32 tile_coord;
    s32 tile_coord_2;

    ctx = *(void **)D_80016000;
    tile = (u8 *)*ctx->unk_30 + (ctx->unk_08 << 5);
    x_dest = ctx->unk_1C;
    x_offset = (x_offset << 6) / 10;
    tile_coord_2 = tile->unk_0C;
    tile_coord_2 += 0x20;
    x_dest->unk_04 = x_offset + tile_coord_2;

    y_dest = ctx->unk_1C;
    y_offset = (y_offset << 6) / 10;
    tile_coord = tile->unk_0E;
    tile_coord += 0x20;
    y_dest->unk_08 = y_offset + tile_coord;
}

/* MECHANISM: Frameless leaf with ctx/tile held in $a3/$a0 and split destination
   bases in $t1/$a1. Each quotient is written back into its own parameter, which
   keeps it out of the shifted operand's register; the /10 magic lives in $t0. */
