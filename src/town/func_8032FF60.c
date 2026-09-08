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
    register s32 scaled_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 tile_coord ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    ctx = *(void **)D_80016000;
    tile = (u8 *)*ctx->unk_30 + (ctx->unk_08 << 5);
    x_dest = ctx->unk_1C;
    scaled_offset = (x_offset << 6) / 10;
    tile_coord = tile->unk_0C;
    tile_coord += 0x20;
    scaled_offset += tile_coord;
    x_dest->unk_04 = scaled_offset;

    y_dest = ctx->unk_1C;
    scaled_offset = (y_offset << 6) / 10;
    tile_coord = tile->unk_0E;
    tile_coord += 0x20;
    scaled_offset += tile_coord;
    y_dest->unk_08 = scaled_offset;
}

/* MECHANISM: Frameless leaf with ctx/tile held in $a3/$a0 and split destination
   bases in $t1/$a1. Quotient and coordinate live ranges are pinned to $v1/$v0;
   the split load seams preserve both lh delay nops and leave $t0/$t2 for /10. */
