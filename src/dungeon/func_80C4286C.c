#include "common.h"

#define M2C_FIELD(p, type, off) (*(type)((u8 *)(p) + (off)))

typedef s32 M2C_UNK;

typedef struct S_8017406C_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x24];
    s32 unk_40;
    s32 unk_44;
} S_8017406C_0;   /* temp_s0 in func_8017406C */

typedef struct S_8017406C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    u8 unk_20;
} S_8017406C_1;   /* temp_v0 in func_8017406C */

typedef struct S_8017406C_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8017406C_2;   /* temp_s1 in func_8017406C */

typedef struct S_8017406C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8017406C_3;   /* temp_s3 in func_8017406C */

typedef struct S_8017406C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8017406C_4;   /* temp_v1 in func_8017406C */


M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 rand();
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEC70;
extern M2C_UNK D_80173FF4;

void func_8017406C(void *arg0, void *arg1) {
    S_8017406C_0 *temp_s0;
    S_8017406C_2 *temp_s1;
    void *temp_v0;
    S_8017406C_3 *temp_s3 = arg1;
    S_8017406C_4 *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_s0 = temp_v0 + 0x20;
        temp_s0->unk_1A = 0xF;
        ((S_8017406C_1 *)temp_v0)->unk_10 = &D_80173FF4;
        func_8004491C(temp_v0, &D_80045340);
        temp_s1 = ((S_8017406C_1 *)temp_v0)->unk_0C;
        temp_s1->unk_10 = 0x20;
        temp_s1->unk_14 = (u16)(temp_s1->unk_14 | 0xC);
        temp_v1 = ((S_8017406C_1 *)temp_v0)->unk_08;
        temp_s0->unk_40 = (s32)temp_s3->unk_00.at00.v;
        temp_s0->unk_44 = (s32)temp_s3->unk_04.at00.v;
        temp_v1->unk_02 = (u16)temp_s3->unk_00.at02.v;
        temp_v1->unk_06 = (u16)temp_s3->unk_04.at02.v;
        temp_v1->unk_0A = (u16)temp_s3->unk_0A;
        temp_s1 = ((S_8017406C_1 *)temp_v0)->unk_0C;
        temp_s1->unk_1E = 0x800;
        temp_s1->unk_1C = 0x800;
        temp_s1->unk_0E = 0x60U;
        temp_s1->unk_0D = 0xFFU;
        temp_s1->unk_0C = 0xFFU;
        ((S_8017406C_1 *)temp_v0)->unk_20 = 0xFFU;
        temp_s0->unk_01 = (u8)temp_s1->unk_0D;
        temp_s0->unk_02 = (u8)temp_s1->unk_0E;
        func_8003DB94(temp_s1, &D_800DEC70, rand() & 1);
        temp_s1->unk_12 = 0x7DCF;
        temp_s1->unk_14 = (u16)(temp_s1->unk_14 | 0x100);
    }
}
