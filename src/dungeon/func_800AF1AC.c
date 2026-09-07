#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800B490C_0_pre {
    u16 unk_00;
} S_800B490C_0_pre;   /* the 0x2 bytes before arg0 in func_800B490C, addressed as arg0[-1] */

typedef struct S_800B490C_0 {
    void * unk_00;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    void * unk_14;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
} S_800B490C_0;   /* arg0 in func_800B490C */

typedef struct S_800B490C_1 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_800B490C_1;   /* temp_v0 in func_800B490C */

typedef struct S_800B490C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800B490C_2;   /* arg1 in func_800B490C */

typedef struct S_800B490C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800B490C_3;   /* temp_v0_2 in func_800B490C */

typedef struct S_800B490C_4 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0xC];
    u16 unk_1C;
    u16 unk_1E;
} S_800B490C_4;   /* arg2 in func_800B490C */

typedef struct S_800B490C_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B490C_5;   /* ((S_800B490C_0 *)arg0)->unk_14 in func_800B490C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_800892E4[];
s32 func_8004491C();
extern s32 D_80044C54;
extern s32 D_800814A0[];

void func_800B490C(void *arg0, S_800B490C_2 *arg1, S_800B490C_4 *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    s32 temp_v1;
    s16 var_v0;
    s32 var_v0_3;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 var_v0_2;
    s32 var_v1;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v1_4;
    u16 temp_v1_5;
    u8 temp_v1_2;
    u8 temp_v1_3;
    S_800B490C_1 *temp_v0;
    S_800B490C_3 *temp_v0_2;

    temp_v0 = ((S_800B490C_0 *)arg0)->unk_00;
    if (temp_v0 == NULL) {
        goto block_3;
    }
    if (!(temp_v0->unk_1E & 0x8000)) {
        goto block_3;
    }
    ((S_800B490C_0 *)arg0)->unk_00 = NULL;
    ((S_800B490C_0 *)arg0)->unk_14 = NULL;
block_3:
    if (((S_800B490C_0 *)arg0)->unk_10 == 0) {
        goto block_5;
    }
    ((S_800B490C_0 *)arg0)->unk_10 = (s16) ((u16) ((S_800B490C_0 *)arg0)->unk_10 - 1);
    return;
block_5:
    temp_v0_2 = ((S_800B490C_0 *)arg0)->unk_14;
    if (temp_v0_2 == NULL) {
        goto block_7;
    }
    arg1->unk_02 = (u16) (arg1->unk_02 - (((S_800B490C_0 *)arg0)->unk_18 - temp_v0_2->unk_02));
    ((S_800B490C_0 *)arg0)->unk_18 = (u16) ((S_800B490C_5 *)(((S_800B490C_0 *)arg0)->unk_14))->unk_02;
    arg1->unk_06 = (u16) (arg1->unk_06 - (((S_800B490C_0 *)arg0)->unk_1A - ((S_800B490C_5 *)(((S_800B490C_0 *)arg0)->unk_14))->unk_06));
    ((S_800B490C_0 *)arg0)->unk_1A = (u16) ((S_800B490C_5 *)(((S_800B490C_0 *)arg0)->unk_14))->unk_06;
    arg1->unk_08.at02.v = (u16) (arg1->unk_08.at02.v - (((S_800B490C_0 *)arg0)->unk_1C - ((S_800B490C_5 *)(((S_800B490C_0 *)arg0)->unk_14))->unk_0A));
    ((S_800B490C_0 *)arg0)->unk_1C = (u16) ((S_800B490C_5 *)(((S_800B490C_0 *)arg0)->unk_14))->unk_0A;
block_7:
    temp_v1 = ((S_800B490C_0 *)arg0)->unk_08;
    if ((u32) temp_v1 >= 5U) {
        goto block_19;
    }
    (void)jt_keep; goto *D_800892E4[(u32)(temp_v1)];
jt_c0:
    arg1->unk_14 = 0x200000;
    arg1->unk_08.at02.v = (u16) (arg1->unk_08.at02.v - 0x80);
    ((S_800B490C_0 *)arg0)->unk_04.at00.v = 0x200000;
    arg2->unk_1E = 0x1000U;
    arg2->unk_1C = 0x1000U;
    func_8004491C(arg0 - 0x20, &D_80044C54);
    ((S_800B490C_0 *)arg0)->unk_0A = 0x10U;
    ((S_800B490C_0 *)arg0)->unk_08 = (s16) ((u16) ((S_800B490C_0 *)arg0)->unk_08 + 1);
jt_c1:
    temp_v0_3 = ((S_800B490C_0 *)arg0)->unk_0A - 1;
    ((S_800B490C_0 *)arg0)->unk_0A = temp_v0_3;
    if ((s16) temp_v0_3 <= 0) {
        goto block_12;
    }
    temp_v1_2 = arg2->unk_0C.at02.v;
    temp_v1_3 = temp_v1_2 + ((s32) (0x80 - temp_v1_2) / (s16) temp_v0_3);
    arg2->unk_0C.at02.v = temp_v1_3;
    arg2->unk_0C.at01.v = temp_v1_3;
    arg2->unk_0C.at00.v = temp_v1_3;
    goto block_19;
block_12:
    var_v0 = (u16) ((S_800B490C_0 *)arg0)->unk_08 + 1;
    goto block_15;
jt_c3:
    temp_v0_4 = ((S_800B490C_0 *)arg0)->unk_0A - 1;
    ((S_800B490C_0 *)arg0)->unk_0A = temp_v0_4;
    if ((temp_v0_4 << 0x10) > 0) {
        goto block_19;
    }
    var_v1 = 8;
    ((S_800B490C_0 *)arg0)->unk_0A = var_v1;
    var_v0 = (u16) ((S_800B490C_0 *)arg0)->unk_08 + 1;
block_15:
    ((S_800B490C_0 *)arg0)->unk_08 = var_v0;
    goto block_19;
jt_c4:
    temp_v0_5 = ((S_800B490C_0 *)arg0)->unk_0A - 1;
    ((S_800B490C_0 *)arg0)->unk_0A = temp_v0_5;
    if ((s16) temp_v0_5 <= 0) {
        goto block_18;
    }
    temp_v1_4 = arg2->unk_1E;
    temp_v1_5 = temp_v1_4 + ((s32) (0 - temp_v1_4) / (s16) temp_v0_5);
    arg2->unk_1E = temp_v1_5;
    arg2->unk_1C = temp_v1_5;
    arg1->unk_08.at02.v = (u16) (arg1->unk_08.at02.v + 6);
    goto block_19;
block_18:
    ((S_800B490C_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800B490C_0_pre *)arg0)[-1].unk_00 | 0x8000);
    D_800814A0[0] |= 0x8000;
jt_c2:
block_19:
    arg1->unk_08.at00.v = (s32) (arg1->unk_08.at00.v + arg1->unk_14);
    temp_v0_6 = ((S_800B490C_0 *)arg0)->unk_0C + 1;
    ((S_800B490C_0 *)arg0)->unk_0C = temp_v0_6;
    if (!(temp_v0_6 & 1)) {
        goto block_28;
    }
    temp_v0_7 = arg1->unk_14;
    var_v1 = temp_v0_7 >> 1;
    var_v0_2 = temp_v0_7 >> 0x11;
    if (var_v0_2 >= 0) {
        goto block_22;
    }
    var_v0_2 = 0 - var_v0_2;
block_22:
    arg1->unk_14 = var_v1;
    if (var_v0_2 >= 2) {
        goto block_28;
    }
    temp_v0_8 = 0 - ((s32) ((S_800B490C_0 *)arg0)->unk_04.at00.v >> 1);
    ((S_800B490C_0 *)arg0)->unk_04.at00.v = temp_v0_8;
    arg1->unk_14 = temp_v0_8;
    var_v0_3 = ((S_800B490C_0 *)arg0)->unk_04.at02.v;
    if (var_v0_3 >= 0) {
        goto block_25;
    }
    var_v0_3 = 0 - var_v0_3;
block_25:
    if (var_v0_3 >= 2) {
        goto block_28;
    }
    if (((S_800B490C_0 *)arg0)->unk_08 >= 3) {
        goto block_28;
    }
    ((S_800B490C_0 *)arg0)->unk_08 = 3;
    ((S_800B490C_0 *)arg0)->unk_0A = 8U;
block_28:
    if (((S_800B490C_0 *)arg0)->unk_0E == 0) {
        goto block_32;
    }
    var_v1 = 0x2CF0F0F0;
    if (!(((S_800B490C_0 *)arg0)->unk_0C & 3)) {
        goto block_31;
    }
    var_v1 = 0x2C404040;
block_31:
    arg2->unk_0C.at00u.v = var_v1;
block_32:
    return;
}
