#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AF254_arg1.h"


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
} S_800AF36C_4;   /* ((Rec_func_800AF254_arg1 *)arg0)->unk_00 in func_800AF36C */

typedef struct S_800AF36C_5 {
    u8 pad_00[0x10];
    void * unk_10;
} S_800AF36C_5;   /* ((Rec_func_800AF254_arg1 *)arg0)->unk_A8.as_pv in func_800AF36C */

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
} S_800AF36C_10;   /* ((S_800AF36C_5 *)(((Rec_func_800AF254_arg1 *)arg0)->unk_A8.as_pv))->unk_10 in func_800AF36C */

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
} S_800AF36C_15;   /* ((S_800AF36C_10 *)(((S_800AF36C_5 *)(((Rec_func_800AF254_arg1 *)arg0)->unk_A8.as_pv))->unk_10))->unk_04 in func_800AF36C */





/* Set paired coordinates from the object's last decimal digit. */
void func_800AF36C(Rec_func_800AF254_arg1 *object) {
    s32 digit;
    s32 row;
    S_800AF36C_2 *x_parts;
    S_800AF36C_3 *y_parts;

    digit = ((S_800AF36C_4 *)(((Rec_func_800AF254_arg1 *)object)->unk_00))->unk_18 % 10;
    row = digit / 5;
    ((S_800AF36C_15 *)(((S_800AF36C_10 *)(((S_800AF36C_5 *)(((Rec_func_800AF254_arg1 *)object)->unk_A8.as_pv))->unk_10))->unk_04))->unk_08 = (s16) ((row << 7) - 0x38);
    ((S_800AF36C_15 *)(((S_800AF36C_10 *)(((S_800AF36C_5 *)(((Rec_func_800AF254_arg1 *)object)->unk_A8.as_pv))->unk_10))->unk_04))->unk_0A = (s16) (((digit - (row * 5)) << 4) + 8);
    x_parts = object->unk_A8.as_pv;
    ((S_800AF36C_11 *)(((S_800AF36C_6 *)(x_parts->unk_14))->unk_04))->unk_08 = (s16) (((S_800AF36C_12 *)(((S_800AF36C_7 *)(x_parts->unk_10))->unk_04))->unk_08 + 0x38);
    y_parts = object->unk_A8.as_pv;
    ((S_800AF36C_13 *)(((S_800AF36C_8 *)(y_parts->unk_14))->unk_04))->unk_0A = (s16) (((S_800AF36C_14 *)(((S_800AF36C_9 *)(y_parts->unk_10))->unk_04))->unk_0A - 9);
}
