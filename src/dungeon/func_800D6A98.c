#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern int D_800814A8[4];
s32 func_8004DC14();                    /* extern */
u32 func_80069E98();                             /* extern */
M2C_UNK func_800DBD5C(); /* extern */
M2C_UNK func_800DBE98();                            /* extern */
M2C_UNK func_800DBEE8();                            
typedef struct S_800DC1F8_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    u8 pad_30[0xC];
    void * unk_3C;
    void * unk_40;
} S_800DC1F8_0;   /* arg0 in func_800DC1F8 */

typedef struct S_800DC1F8_1 {
    u8 pad_00[0x4];
    void * unk_04;
    u16 * unk_08;
} S_800DC1F8_1;   /* state in func_800DC1F8 */

typedef struct S_800DC1F8_2 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800DC1F8_2;   /* temp_s0 in func_800DC1F8 */

typedef struct S_800DC1F8_3 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_800DC1F8_3;   /* temp_a3 in func_800DC1F8 */

typedef struct S_800DC1F8_4 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800DC1F8_4;   /* temp_a2 in func_800DC1F8 */

typedef struct S_800DC1F8_5 {
    u8 unk_00;
} S_800DC1F8_5;   /* temp_a1 in func_800DC1F8 */

typedef struct S_800DC1F8_6 {
    u8 unk_00;
} S_800DC1F8_6;   /* temp_a0_2 in func_800DC1F8 */

typedef struct S_800DC1F8_7 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_800DC1F8_7;   /* temp_v1_2 in func_800DC1F8 */

typedef struct S_800DC1F8_8 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_800DC1F8_8;   /* temp_v0_6 in func_800DC1F8 */

typedef struct S_800DC1F8_9 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
} S_800DC1F8_9;   /* temp_v0_7 in func_800DC1F8 */

typedef struct S_800DC1F8_10 {
    u8 pad_00[0x14A8];
    union { s32 i; void * p; } unk_14A8;   /* accessed as both */
} S_800DC1F8_10;   /* page_base in func_800DC1F8 */

typedef struct S_800DC1F8_11 {
    u8 pad_00[0x80];
    s32 unk_80;
    void * unk_84;
    u16 * unk_88;
} S_800DC1F8_11;   /* ((S_800DC1F8_0 *)arg0)->unk_3C in func_800DC1F8 */

typedef struct S_800DC1F8_12 {
    u8 pad_00[0x28];
    u8 unk_28;
} S_800DC1F8_12;   /* ((S_800DC1F8_10 *)page_base)->unk_14A8.i in func_800DC1F8 */

typedef struct S_800DC1F8_13 {
    u8 pad_00[0x29];
    u8 unk_29;
} S_800DC1F8_13;   /* ((S_800DC1F8_10 *)page_base)->unk_14A8.p in func_800DC1F8 */

/* extern */

void func_800DC1F8(S_800DC1F8_0 *arg0, void *arg1) {
    s32 temp_a0;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1;
    u16 *temp_v0;
    u16 *temp_v1_3;
    u16 *temp_v1_4;
    u8 temp_a0_3;
    u8 temp_a0_4;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 v0_const80;
    S_800DC1F8_6 *temp_a0_2;
    S_800DC1F8_5 *temp_a1;
    S_800DC1F8_4 *temp_a2;
    S_800DC1F8_3 *temp_a3;
    S_800DC1F8_2 *temp_s0;
    S_800DC1F8_8 *temp_v0_6;
    S_800DC1F8_9 *temp_v0_7;
    S_800DC1F8_7 *temp_v1_2;
    u8 *page_base;
    S_800DC1F8_1 *state = arg1;

    if (arg0->unk_18 != 0) {
        temp_v1 = arg0->unk_28;
        if (temp_v1 == 1) {
            goto block_state_1;
        }
        if (temp_v1 < 2) {
            if (temp_v1 == 0) {
                goto block_state_0;
            }
            goto block_16;
        }
        if (temp_v1 == 2) {
            goto block_state_2;
        }
        goto block_16;

block_state_0:
        if ((((u16) *state->unk_08 >> 0xA) & 3) == 1) {
            func_80053DA8(0x504);
            temp_v0_4 = arg0->unk_20;
            temp_v1 = arg0->unk_28;
            temp_v0_4 ^= 1;
            arg0->unk_20 = temp_v0_4;
            temp_v0_4 = arg0->unk_24;
            temp_v1 += 1;
            arg0->unk_28 = temp_v1;
            temp_v0_4 ^= 1;
            arg0->unk_24 = temp_v0_4;
        }
block_state_1:
        if ((((u16) *state->unk_08 >> 0xA) & 3) == 2) {
            arg0->unk_1C = 0x10;
            arg0->unk_28 = (s32) (arg0->unk_28 + 1);
        }
        goto block_16;

block_state_2:
        if ((((u16) *state->unk_08 >> 0xA) & 3) == 3) {
            func_80053DA8(0x504);
            arg0->unk_28 = 0;
            arg0->unk_24 = (s32) (arg0->unk_24 ^ 1);
            arg0->unk_20 = (s32) (arg0->unk_20 ^ 1);
        }
block_16:
        if (arg0->unk_20 != 0) {
            if (arg0->unk_24 != 0) {
                func_8004E99C(((S_800DC1F8_11 *)(arg0->unk_3C))->unk_80);
                func_800DBEE8();
                temp_s0 = arg0->unk_40;
                temp_s0->unk_88 = (s16) (((3 - (func_80069E98(arg0->unk_2C) >> 1)) * 6) + 0xA4);
                ((S_800DC1F8_11 *)(arg0->unk_3C))->unk_80 = func_8004DC14(arg0->unk_2C, 6);
                if (((S_800DC1F8_11 *)(arg0->unk_3C))->unk_80 != 0) {
                    arg0->unk_20 = 0;
                    goto block_22;
                }
            } else {
                func_8004E99C(((S_800DC1F8_11 *)(arg0->unk_3C))->unk_80);
                ((S_800DC1F8_11 *)(arg0->unk_3C))->unk_80 = 0;
                arg0->unk_10 = 0;
                arg0->unk_14 = 0;
                func_800DBE98();
                arg0->unk_20 = 0;
                goto block_22;
            }
        } else {
block_22:
            temp_a1 = state->unk_04;
            temp_a2 = temp_a1;
            temp_a3 = temp_a1;
            temp_v0 = state->unk_08;
            temp_a0 = 0x400 - (((s16) *temp_v0 - 0x400) & 0x7FF);
            if (((s16) *temp_v0 & 0x7FF) < 0x400) {
                temp_v0_2 = (temp_a0 >> 4) - 0x80;
            } else {
                temp_v0_2 = (temp_a0 >> 3) - 0x80;
            }
            temp_a3->unk_02 = temp_v0_2;
            temp_a2->unk_01 = temp_v0_2;
            temp_a1->unk_00 = temp_v0_2;
            temp_a0_2 = state->unk_04;
            temp_v1_2 = ((S_800DC1F8_11 *)(arg0->unk_3C))->unk_84;
            temp_v0_3 = temp_a0_2->unk_00;
            temp_v1_2->unk_02 = temp_v0_3;
            temp_v1_2->unk_01 = temp_v0_3;
            temp_v1_2->unk_00 = temp_v0_3;
            temp_v0_4 = arg0->unk_1C;
            if (temp_v0_4 == 0) {
                temp_v1_3 = state->unk_08;
                *temp_v1_3 += 0x80;
                temp_v1_4 = ((S_800DC1F8_11 *)(arg0->unk_3C))->unk_88;
                *temp_v1_4 += 0x80;
                temp_v0_5 = arg0->unk_18 - 1;
                arg0->unk_18 = temp_v0_5;
                if (temp_v0_5 == 0) {
                    arg0->unk_28 = 0;
                    *state->unk_08 = 0;
                    *((S_800DC1F8_11 *)(arg0->unk_3C))->unk_88 = 0x800;
                    v0_const80 = 0x80U;
                    temp_v0_6 = state->unk_04;
                    temp_v0_6->unk_02 = v0_const80;
                    temp_v0_6->unk_01 = v0_const80;
                    temp_v0_6->unk_00 = v0_const80;
                    temp_v0_7 = ((S_800DC1F8_11 *)(arg0->unk_3C))->unk_84;
                    temp_v0_7->unk_02 = v0_const80;
                    temp_v0_7->unk_01 = v0_const80;
                    temp_v0_7->unk_00 = v0_const80;
                    goto block_30;
                }
                goto block_30;
            }
            arg0->unk_1C = (s32) (temp_v0_4 - 1);
            goto block_30;
        }
    } else {
block_30:
        if (arg0->unk_24 == 0) {
            page_base = (u8 *)0x80080000;
            temp_a0_3 = ((S_800DC1F8_12 *)(((S_800DC1F8_10 *)page_base)->unk_14A8.i))->unk_28;
            if (temp_a0_3 != arg0->unk_10) {
                func_800DBD5C(temp_a0_3, arg0->unk_10, 3, 0x1CA, 0x19C, 1);
            }
            temp_a0_4 = ((S_800DC1F8_13 *)(((S_800DC1F8_10 *)page_base)->unk_14A8.p))->unk_29;
            if (temp_a0_4 != arg0->unk_14) {
                func_800DBC20(temp_a0_4, arg0->unk_14, 3, 0x1DA, 0x1A4, 1);
            }
        }
    }
}
