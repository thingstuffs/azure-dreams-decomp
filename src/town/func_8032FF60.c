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

void func_8001A760(s32 arg0, s32 arg1, s32 arg2) {
    S_8001A760_0 *ctx;
    S_8001A760_1 *tile;
    S_8001A760_2 *out1;
    S_8001A760_3 *out2;
    register s32 quotient ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 coord ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    ctx = *(void **)D_80016000;
    tile = (u8 *)*ctx->unk_30 + (ctx->unk_08 << 5);
    out1 = ctx->unk_1C;
    quotient = (arg1 << 6) / 10;
    coord = tile->unk_0C;
    coord += 0x20;
    quotient += coord;
    out1->unk_04 = quotient;

    out2 = ctx->unk_1C;
    quotient = (arg2 << 6) / 10;
    coord = tile->unk_0E;
    coord += 0x20;
    quotient += coord;
    out2->unk_08 = quotient;
}

/* MECHANISM: Frameless leaf with ctx/tile held in $a3/$a0 and split destination
   bases in $t1/$a1. Quotient and coordinate live ranges are pinned to $v1/$v0;
   the split load seams preserve both lh delay nops and leave $t0/$t2 for /10. */
