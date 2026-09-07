#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AF36C_1 {
    void * unk_00;
    u8 pad_04[0xA4];
    void * unk_A8;
} S_800AF36C_1;   /* arg0 in func_800AF36C */

typedef struct S_800AF36C_2 {
    u8 pad_00[0x10];
    void * unk_10;
    void * unk_14;
} S_800AF36C_2;   /* temp_v1 in func_800AF36C */

typedef struct S_800AF36C_3 {
    u8 pad_00[0x10];
    void * unk_10;
    void * unk_14;
} S_800AF36C_3;   /* temp_v1_2 in func_800AF36C */

typedef struct S_800AF36C_4 {
    u8 pad_00[0x18];
    s32 unk_18;
} S_800AF36C_4;   /* ((S_800AF36C_1 *)arg0)->unk_00 in func_800AF36C */

typedef struct S_800AF36C_5 {
    u8 pad_00[0x10];
    void * unk_10;
} S_800AF36C_5;   /* ((S_800AF36C_1 *)arg0)->unk_A8 in func_800AF36C */

typedef struct S_800AF36C_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AF36C_6;   /* ((S_800AF36C_2 *)temp_v1)->unk_14 in func_800AF36C */

typedef struct S_800AF36C_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AF36C_7;   /* ((S_800AF36C_2 *)temp_v1)->unk_10 in func_800AF36C */

typedef struct S_800AF36C_8 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AF36C_8;   /* ((S_800AF36C_3 *)temp_v1_2)->unk_14 in func_800AF36C */

typedef struct S_800AF36C_9 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AF36C_9;   /* ((S_800AF36C_3 *)temp_v1_2)->unk_10 in func_800AF36C */

typedef struct S_800AF36C_10 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AF36C_10;   /* ((S_800AF36C_5 *)(((S_800AF36C_1 *)arg0)->unk_A8))->unk_10 in func_800AF36C */

typedef struct S_800AF36C_11 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800AF36C_11;   /* ((S_800AF36C_6 *)(((S_800AF36C_2 *)temp_v1)->unk_14))->unk_04 in func_800AF36C */

typedef struct S_800AF36C_12 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_800AF36C_12;   /* ((S_800AF36C_7 *)(((S_800AF36C_2 *)temp_v1)->unk_10))->unk_04 in func_800AF36C */

typedef struct S_800AF36C_13 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800AF36C_13;   /* ((S_800AF36C_8 *)(((S_800AF36C_3 *)temp_v1_2)->unk_14))->unk_04 in func_800AF36C */

typedef struct S_800AF36C_14 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AF36C_14;   /* ((S_800AF36C_9 *)(((S_800AF36C_3 *)temp_v1_2)->unk_10))->unk_04 in func_800AF36C */

typedef struct S_800AF36C_15 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800AF36C_15;   /* ((S_800AF36C_10 *)(((S_800AF36C_5 *)(((S_800AF36C_1 *)arg0)->unk_A8))->unk_10))->unk_04 in func_800AF36C */




typedef struct S_800AF36C_0 {
    u8 pad_00[0xA8];
    void * unk_A8;
} S_800AF36C_0;   /* arg0 in func_800AF36C */

void func_800AF36C(S_800AF36C_0 *arg0) {
    s32 digit;
    s32 row;
    S_800AF36C_2 *temp_v1;
    S_800AF36C_3 *temp_v1_2;

    digit = ((S_800AF36C_4 *)(((S_800AF36C_1 *)arg0)->unk_00))->unk_18 % 10;
    row = digit / 5;
    ((S_800AF36C_15 *)(((S_800AF36C_10 *)(((S_800AF36C_5 *)(((S_800AF36C_1 *)arg0)->unk_A8))->unk_10))->unk_04))->unk_08 = (s16) ((row << 7) - 0x38);
    ((S_800AF36C_15 *)(((S_800AF36C_10 *)(((S_800AF36C_5 *)(((S_800AF36C_1 *)arg0)->unk_A8))->unk_10))->unk_04))->unk_0A = (s16) (((digit - (row * 5)) << 4) + 8);
    temp_v1 = arg0->unk_A8;
    ((S_800AF36C_11 *)(((S_800AF36C_6 *)(temp_v1->unk_14))->unk_04))->unk_08 = (s16) (((S_800AF36C_12 *)(((S_800AF36C_7 *)(temp_v1->unk_10))->unk_04))->unk_08 + 0x38);
    temp_v1_2 = arg0->unk_A8;
    ((S_800AF36C_13 *)(((S_800AF36C_8 *)(temp_v1_2->unk_14))->unk_04))->unk_0A = (s16) (((S_800AF36C_14 *)(((S_800AF36C_9 *)(temp_v1_2->unk_10))->unk_04))->unk_0A - 9);
}

/* MECHANISM: Frameless leaf with no saved registers or stack locals.
   Cache the decimal digit and row as sibling scalars so the two coordinate stores
   share retail's division results instead of recomputing the modulo chain. */
