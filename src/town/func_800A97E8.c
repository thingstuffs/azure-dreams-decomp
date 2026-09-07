#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A6F48_12 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800A6F48_12;   /* temp_v0_2 in func_800A6F48 */

typedef struct S_800A6F48_13 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800A6F48_13;   /* temp_v0_3 in func_800A6F48 */

typedef struct S_800A6F48_14 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800A6F48_14;   /* ((S_800A6F48_12 *)temp_v0_2)->unk_08 in func_800A6F48 */

typedef struct S_800A6F48_15 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800A6F48_15;   /* ((S_800A6F48_13 *)temp_v0_3)->unk_08 in func_800A6F48 */




void *func_800A75B8();                         /* extern */
M2C_UNK func_800ABD74();               /* extern */
extern M2C_UNK D_800A70EC;
extern M2C_UNK D_800D0DD8;

typedef struct S_800A6F48_0 {
    u8 pad_00[0xC];
    M2C_UNK * unk_0C;
} S_800A6F48_0;   /* arg1 in func_800A6F48 */

typedef struct S_800A6F48_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_800A6F48_1;   /* &D_800D0DD8 in func_800A6F48 */

typedef struct S_800A6F48_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A6F48_2;   /* arg2 in func_800A6F48 */

typedef struct S_800A6F48_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_800A6F48_3;   /* temp_v1 in func_800A6F48 */

typedef struct S_800A6F48_4 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0xA4];
    s16 unk_B0;
} S_800A6F48_4;   /* temp_v0_2 in func_800A6F48 */

typedef struct S_800A6F48_5 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800A6F48_5;   /* temp_v1_2 in func_800A6F48 */

typedef struct S_800A6F48_6 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800A6F48_6;   /* temp_v1_3 in func_800A6F48 */

typedef struct S_800A6F48_7 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_800A6F48_7;   /* temp_v1_4 in func_800A6F48 */

typedef struct S_800A6F48_8 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0xA4];
    s16 unk_B0;
} S_800A6F48_8;   /* temp_v0_3 in func_800A6F48 */

typedef struct S_800A6F48_9 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800A6F48_9;   /* temp_v1_5 in func_800A6F48 */

typedef struct S_800A6F48_10 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
} S_800A6F48_10;   /* arg0 in func_800A6F48 */

typedef struct S_800A6F48_11 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800A6F48_11;   /* arg3 in func_800A6F48 */

void func_800A6F48(S_800A6F48_10 *arg0, S_800A6F48_0 *arg1, S_800A6F48_2 *arg2, S_800A6F48_11 *arg3) {
    s32 position[5];
    M2C_UNK *temp_v1;
    M2C_UNK *temp_v1_4;
    s32 var_v0;
    s32 var_v0_2;
    u32 temp_v0;
    S_800A6F48_4 *temp_v0_2;
    register S_800A6F48_8 *temp_v0_3 ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    S_800A6F48_5 *temp_v1_2;
    S_800A6F48_6 *temp_v1_3;
    S_800A6F48_9 *temp_v1_5;

    arg1->unk_0C = &D_800D0DD8;
    temp_v0 = ((S_800A6F48_1 *)(&D_800D0DD8))->unk_04 + ((S_800A6F48_1 *)(&D_800D0DD8))->unk_10;
    position[0] = arg2->unk_00 + ((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1);
    temp_v1 = arg1->unk_0C;
    position[1] = arg2->unk_04 + ((S_800A6F48_3 *)temp_v1)->unk_04 + ((S_800A6F48_3 *)temp_v1)->unk_10;
    position[2] = arg2->unk_08;
    temp_v0_2 = func_800A75B8(position);
    ((S_800A6F48_14 *)(((S_800A6F48_12 *)temp_v0_2)->unk_08))->unk_0C = 0x10000;
    temp_v1_2 = temp_v0_2->unk_08;
    var_v0 = temp_v1_2->unk_10;
    if (var_v0 < 0) {
        var_v0 += 3;
    }
    temp_v1_2->unk_10 = (s32) (var_v0 >> 2);
    temp_v1_3 = temp_v0_2->unk_08;
    var_v0_2 = temp_v1_3->unk_14;
    if (var_v0_2 < 0) {
        var_v0_2 += 3;
    }
    temp_v1_3->unk_14 = (s32) (var_v0_2 >> 2);
    temp_v0_2->unk_B0 = 0;
    func_800ABD74(position, temp_v0_2);
    temp_v1_4 = arg1->unk_0C;
    position[0] = arg2->unk_00 - ((((S_800A6F48_7 *)temp_v1_4)->unk_04 + ((S_800A6F48_7 *)temp_v1_4)->unk_10) / 3);
    temp_v0_3 = func_800A75B8(position);
    ((S_800A6F48_15 *)(((S_800A6F48_13 *)temp_v0_3)->unk_08))->unk_0C = -0x8000;
    temp_v1_5 = temp_v0_3->unk_08;
    temp_v1_5->unk_10 = (s32) (temp_v1_5->unk_10 / 3);
    temp_v0_3->unk_B0 = 0;
    func_800ABD74(position, temp_v0_3);
    arg0->unk_50 = &D_800A70EC;
    arg0->unk_6C = 0xA;
    arg3->unk_0E = 0x80;
    arg3->unk_0D = 0x80;
    arg3->unk_0C = 0x80;
}

/* MECHANISM: A five-word position array exposes all three initialized siblings and
   supplies the retail 0x40 frame; the four arguments naturally occupy s3/s0/s1/s2.
   A guarded $a1 pin holds the second factory result across its field updates, while
   unsigned byte lvalues preserve the retail li 0x80 before the final sb sequence. */
