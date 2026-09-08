#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8196012C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_8196012C_0;   /* object in func_8196012C */

typedef struct S_8196012C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_8196012C_1;   /* position in func_8196012C */

typedef struct S_8196012C_2 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
} S_8196012C_2;   /* render in func_8196012C */

typedef struct S_8196012C_3 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    s8 unk_08;
    s8 unk_09;
    s8 unk_0A;
    s8 unk_0B;
    u8 pad_0C[0x40];
    s16 unk_4C;
} S_8196012C_3;   /* primitive in func_8196012C */



extern void *func_8003FC64();
extern void func_8004491C();
extern s16 func_800644B8();
extern s16 func_80064584();
extern s32 rand();
extern s32 D_80025460[];
extern s32 D_800258D8[];

/* Spawn a textured particle with randomized motion at the given position. */
void func_8196012C(s16 x, s16 y, s16 z, s16 tile_col, s16 tile_row) {
    s32 random_angle;
    s32 primitive_word;
    s16 tile_row_copy;
    S_8196012C_1 *position;
    S_8196012C_3 *primitive;
    S_8196012C_2 *render;
    void *object;

    tile_row_copy = tile_row;
    object = func_8003FC64(0x202);
    if (object != NULL) {
        ((S_8196012C_0 *)object)->unk_10 = D_80025460;
        func_8004491C(object, D_800258D8);
        position = ((S_8196012C_0 *)object)->unk_08;
        position->unk_02 = x;
        position->unk_06 = y;
        position->unk_0A = z;
        position->unk_0E = (rand() & 0xF) - 8;
        position->unk_12 = (rand() & 0xF) - 8;
        position->unk_16 = -0x10 - (rand() & 0xF);
        render = ((S_8196012C_0 *)object)->unk_0C;
        render->unk_1E = 0x400;
        render->unk_1C = 0x400;
        random_angle = rand();
        render->unk_20 = func_80064584(random_angle);
        render->unk_22 = func_800644B8(random_angle);
        render->unk_10 = 0x20;
        primitive = (s8 *)object + 0x20;
        render->unk_14 = 0xC;
        render->unk_0C = 0x808080;
        primitive_word = 0xF8F82CC0;
        ((S_8196012C_0 *)object)->unk_20 = primitive_word;
        primitive->unk_04 = 0x13D;
        primitive->unk_08 = (s8)(tile_col * 0x10);
        primitive->unk_09 = (s8)(((s32)(tile_row << 0x10) >> 0xC) - 0x80);
        primitive->unk_0A = tile_col == 7 ? 0xF : 0x10;
        primitive->unk_0B = tile_row_copy == 7 ? 0xF : 0x10;
        primitive->unk_4C = (rand(primitive_word) & 0x1F) + 0x20;
        render->unk_08 = primitive;
    }
}
