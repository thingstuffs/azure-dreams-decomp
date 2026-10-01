#include "common.h"

typedef struct S_800AEBC4_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x1];
    u8 unk_0F;
} S_800AEBC4_2;   /* the position / secondary records config links */

typedef struct S_800AEBC4_4 {
    s32 unk_00;
    S_800AEBC4_2 *unk_04;
    S_800AEBC4_2 *unk_08;
} S_800AEBC4_4;   /* config */

typedef struct S_800AEBC4_6 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
} S_800AEBC4_6;   /* vectors */

extern s32 D_8002E5D8[4];
extern s32 D_8002E5E8[3];

/* Copies two templates into linked records and initializes position and offset vectors. */
void func_800AEBC4(S_800AEBC4_6 *vectors, S_800AEBC4_4 *config, s32 *position_data,
                   s32 *secondary_data, s32 x, s32 y) {
    const s32 *src0 = D_8002E5D8;
    const s32 *src1 = D_8002E5E8;
    position_data[0] = src0[0];
    position_data[1] = src0[1];
    position_data[2] = src0[2];
    position_data[3] = src0[3];
    secondary_data[0] = src1[0];
    secondary_data[1] = src1[1];
    secondary_data[2] = src1[2];
    config->unk_08 = (S_800AEBC4_2 *)secondary_data;
    config->unk_04 = (S_800AEBC4_2 *)position_data;
    config->unk_00 = 0;
    config->unk_08->unk_02 = -0x400;
    config->unk_04->unk_08 = x;
    config->unk_04->unk_0A = y;
    config->unk_04->unk_0C = 0x400;
    config->unk_04->unk_0F = 4;
    vectors->unk_0C = x;
    vectors->unk_0E = y;
    vectors->unk_10 = 0x400;
    if (x < 0) {
        vectors->unk_14 = 0x30 - x;
    } else {
        vectors->unk_14 = -0x60 - x;
    }
    vectors->unk_16 = -0x40 - y;
    vectors->unk_18 = -0x200;
}
