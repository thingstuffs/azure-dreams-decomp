#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800814A0.h"

typedef struct S_800C4F20_10 {
    u8 pad_00[0x1C];
    void * unk_1C;
    u8 pad_20[0x4];
    void * unk_24;
} S_800C4F20_10;   /* arg0 in func_800C4F20 */

typedef struct S_800C4F20_11 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x70];
    s16 unk_88;
} S_800C4F20_11;   /* ((S_800C4F20_10 *)arg0)->unk_24 in func_800C4F20 */

typedef struct S_800C4F20_12 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C4F20_12;   /* ((S_800C4F20_10 *)arg0)->unk_1C in func_800C4F20 */


typedef struct S_800C4F20_0_pre {
    u16 unk_00;
} S_800C4F20_0_pre;   /* the 0x2 bytes before arg0 in func_800C4F20, addressed as arg0[-1] */

typedef struct S_800C4F20_0 {
    u8 pad_00[0x20];
    void * unk_20;
    void * unk_24;
    union { s16 s; u16 u; } unk_28;   /* accessed as both */
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x2];
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
} S_800C4F20_0;   /* arg0 in func_800C4F20 */

typedef struct S_800C4F20_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_800C4F20_1;   /* arg2 in func_800C4F20 */

typedef struct S_800C4F20_2 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_800C4F20_2;   /* temp_a1_2 in func_800C4F20 */

typedef struct S_800C4F20_3 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_800C4F20_3;   /* tail_ptr in func_800C4F20 */

typedef struct S_800C4F20_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800C4F20_4;   /* temp_s3 in func_800C4F20 */

typedef struct S_800C4F20_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800C4F20_5;   /* arg1 in func_800C4F20 */

typedef struct S_800C4F20_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800C4F20_6;   /* (void *) c2_v0 in func_800C4F20 */

typedef struct S_800C4F20_7 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_800C4F20_7;   /* temp_a1_4 in func_800C4F20 */

typedef struct S_800C4F20_8 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800C4F20_8;   /* temp_a0_7 in func_800C4F20 */



extern void *D_800893E4[];
s32 func_800644B8();
s32 func_80064584();
s32 func_80069EF8();
M2C_UNK func_800A56E0();
extern void func_800C5254(void) __attribute__((noreturn));
extern void func_800C5344(void) __attribute__((noreturn));
extern void func_800C539C(void) __attribute__((noreturn));
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083780;

void func_800C4F20(void *arg0, S_800C4F20_5 *arg1, void *arg2_in) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17 };
    register S_800C4F20_1 *arg2 ASM_REG("$20") = arg2_in;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 temp_a0_4;
    s16 temp_a0_5;
    s16 temp_a0_6;
    s16 temp_a1;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_7;
    s32 temp_v1;
    s16 temp_v1_5;
    s16 var_v1;
    s32 temp_a0_3;
    s32 temp_a1_3;
    s32 temp_s0;
    s32 temp_v0_8;
    s32 var_s0;
    u16 temp_a0;
    u16 temp_a0_2;
    u16 temp_v0;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v1_2;
    u16 temp_v1_3;
    u16 temp_v1_6;
    u16 temp_v1_7;
    u16 temp_v1_8;
    S_800C4F20_8 *temp_a0_7;
    S_800C4F20_2 *temp_a1_2;
    S_800C4F20_7 *temp_a1_4;
    S_800C4F20_4 *temp_s3;
    void *temp_v1_4;

    temp_v1 = ((S_800C4F20_0 *)arg0)->unk_28.s;
    if ((u32) temp_v1 >= 0x12U) {
        goto block_24;
    }
    (void)jt_keep; goto *D_800893E4[(u32)(temp_v1)];
jt_c0:
    temp_a1 = ((S_800C4F20_0 *)arg0)->unk_2A;
    if (temp_a1 == 0) {
        goto block_4;
    }
    temp_a0 = arg2->unk_1E;
    temp_a0_2 = temp_a0 + ((s32) (0x1000 - temp_a0) / temp_a1);
    temp_v0 = arg2->unk_20;
    arg2->unk_1E = temp_a0_2;
    arg2->unk_1C = temp_a0_2;
    arg2->unk_20 = (u16) (temp_v0 + ((s32) (0x1000 - temp_v0) / (s16) ((S_800C4F20_0 *)arg0)->unk_2A));
    temp_a1_2 = ((S_800C4F20_0 *)arg0)->unk_20;
    temp_v1_2 = temp_a1_2->unk_1E;
    temp_v1_3 = temp_v1_2 + ((s32) (0x400 - temp_v1_2) / (s16) ((S_800C4F20_0 *)arg0)->unk_2A);
    temp_a1_2->unk_1E = temp_v1_3;
    temp_a1_2->unk_1C = temp_v1_3;
    ((S_800C4F20_0 *)arg0)->unk_32 = (s16) ((u16) ((S_800C4F20_0 *)arg0)->unk_32 - ((s16) ((S_800C4F20_0 *)arg0)->unk_32 / (s16) ((S_800C4F20_0 *)arg0)->unk_2A));
block_4:
    temp_v0_2 = (u16) ((S_800C4F20_0 *)arg0)->unk_2A - 1;
    ((S_800C4F20_0 *)arg0)->unk_2A = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        goto block_24;
    }
    arg2->unk_1E = 0x1000U;
    arg2->unk_1C = 0x1000U;
    arg2->unk_20 = 0x1000U;
    {
        S_800C4F20_3 *tail_ptr = ((S_800C4F20_0 *)arg0)->unk_20;
        tail_ptr->unk_1E = 0x800U;
        tail_ptr->unk_1C = 0x800U;
    }
    {
        u16 tail_v0;
        register u32 tail_v1 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        tail_v0 = ((S_800C4F20_0 *)arg0)->unk_28.u;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a computation the compiler would drop */
        tail_v1 = 0x20;
        ASM_KEEP(tail_v1);   /* MATCH pin: retail basic-block layout depends on it */
        ASM_KEEP(tail_v0);   /* MATCH pin: retail basic-block layout depends on it */
        ((S_800C4F20_0 *)arg0)->unk_32 = 0;
        func_800C5254();
    }
jt_c1:
    temp_v0_8 = func_80064584(((S_800C4F20_0 *)arg0)->unk_2E);
    temp_s3 = &D_80083780;
    temp_s0 = temp_s3->unk_02 + (temp_v0_8 >> 6);
    temp_a1_3 = temp_s3->unk_06 + (func_800644B8(((S_800C4F20_0 *)arg0)->unk_2E) >> 6);
    var_s0 = temp_s0 - arg1->unk_02;
    if (var_s0 >= 0) {
        goto block_8;
    }
    var_s0 += 3;
block_8:
    arg1->unk_02 = (s16) ((u16) arg1->unk_02 + (var_s0 >> 2));
    arg1->unk_06 = (s16) ((u16) arg1->unk_06 + ((s32) (temp_a1_3 - arg1->unk_06) / 4));
    temp_v0_8 = (func_800644B8(((S_800C4F20_0 *)arg0)->unk_2C << 5, temp_a1_3) >> 6) + 0x40;
    temp_a0_3 = temp_s3->unk_0A - arg1->unk_0A;
    arg1->unk_0A = (s16) ((u16) arg1->unk_0A + ((s32) (temp_a0_3 - temp_v0_8) / 4));
    ((S_800C4F20_0 *)arg0)->unk_2E = (s16) ((u16) ((S_800C4F20_0 *)arg0)->unk_2E + 0x40 + (func_80069EF8(temp_a0_3) & 0x1F));
    temp_a0_4 = ((S_800C4F20_0 *)arg0)->unk_36;
    if (temp_a0_4 == 0) {
        goto block_24;
    }
    temp_v0_3 = (u16) ((S_800C4F20_0 *)arg0)->unk_2A - 1;
    ((S_800C4F20_0 *)arg0)->unk_2A = temp_v0_3;
    if ((temp_v0_3 << 0x10) > 0) {
        goto block_24;
    }
    temp_v1 = temp_a0_4;
    if (temp_v1 == 1) {
        goto block_16;
    }
    if (temp_v1 == 3) {
        goto block_16;
    }
    ((S_800C4F20_0 *)arg0)->unk_2A = 0x20;
    ((S_800C4F20_0 *)arg0)->unk_28.s = (s16) ((u16) ((S_800C4F20_0 *)arg0)->unk_28.s + 0x10);
    func_800A56E0(0x518);
    func_800C539C();
jt_c2:
    temp_a0_5 = ((S_800C4F20_0 *)arg0)->unk_2A;
    if (temp_a0_5 == 0) {
        goto block_15;
    }
    {
        s32 c2_v0;
        s32 c2_v1;

        c2_v0 = (s32) ((S_800C4F20_0 *)arg0)->unk_20;
        c2_v1 = ((S_800C4F20_6 *)((void *) c2_v0))->unk_24;
        c2_v0 = arg1->unk_02;
        c2_v1 <<= 6;
        c2_v0 -= 0x20;
        c2_v1 -= c2_v0;
        c2_v1 /= temp_a0_5;
        arg1->unk_02 = (s16) ((u16) arg1->unk_02 + c2_v1);
    }
    {
        s32 c2_v0;
        s32 c2_v1;
        register s32 c2_a0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

        c2_v0 = (s32) ((S_800C4F20_0 *)arg0)->unk_20;
        c2_a0 = ((S_800C4F20_0 *)arg0)->unk_2A;
        c2_v1 = ((S_800C4F20_6 *)((void *) c2_v0))->unk_25;
        c2_v0 = arg1->unk_06;
        c2_v1 <<= 6;
        c2_v0 -= 0x20;
        c2_v1 -= c2_v0;
        c2_v1 /= c2_a0;
        arg1->unk_06 = (s16) ((u16) arg1->unk_06 + c2_v1);
    }
    arg1->unk_0A = (s16) ((u16) arg1->unk_0A + ((s32) (((S_800C4F20_11 *)(((S_800C4F20_10 *)arg0)->unk_24))->unk_88 - arg1->unk_0A) / (s16) ((S_800C4F20_0 *)arg0)->unk_2A));
block_15:
    temp_v0_4 = (u16) ((S_800C4F20_0 *)arg0)->unk_2A - 1;
    ((S_800C4F20_0 *)arg0)->unk_2A = temp_v0_4;
    if ((temp_v0_4 << 0x10) > 0) {
        goto block_24;
    }
block_16:
    var_v1 = 0x10;
block_17:
    ((S_800C4F20_0 *)arg0)->unk_2A = var_v1;
    ((S_800C4F20_0 *)arg0)->unk_28.s = (s16) ((u16) ((S_800C4F20_0 *)arg0)->unk_28.s + 1);
    goto block_24;
jt_c3:
    temp_v1_5 = ((S_800C4F20_0 *)arg0)->unk_2A;
    if (temp_v1_5 == 0) {
        goto block_22;
    }
    temp_v0_5 = arg2->unk_1E;
    temp_v0_6 = temp_v0_5 - ((s32) temp_v0_5 / temp_v1_5);
    arg2->unk_1E = temp_v0_6;
    arg2->unk_1C = temp_v0_6;
    temp_v1_6 = arg2->unk_20;
    arg2->unk_20 = (u16) (temp_v1_6 + ((s32) (0x2000 - temp_v1_6) / (s16) ((S_800C4F20_0 *)arg0)->unk_2A));
    temp_a1_4 = ((S_800C4F20_0 *)arg0)->unk_20;
    temp_v1_7 = temp_a1_4->unk_1E;
    temp_v1_8 = temp_v1_7 + ((s32) (0x1000 - temp_v1_7) / (s16) ((S_800C4F20_0 *)arg0)->unk_2A);
    temp_a1_4->unk_1E = temp_v1_8;
    temp_a1_4->unk_1C = temp_v1_8;
    ((S_800C4F20_0 *)arg0)->unk_32 = (s16) ((u16) ((S_800C4F20_0 *)arg0)->unk_32 + ((s32) (0x400 - ((S_800C4F20_0 *)arg0)->unk_32) / (s16) ((S_800C4F20_0 *)arg0)->unk_2A));
    func_800C5344();
jt_c17:
    temp_a0_6 = ((S_800C4F20_0 *)arg0)->unk_2A;
    if (temp_a0_6 == 0) {
        goto block_22;
    }
    arg1->unk_0A = (s16) ((u16) arg1->unk_0A + ((s32) (-0x400 - arg1->unk_0A) / temp_a0_6));
block_22:
    temp_v0_7 = (u16) ((S_800C4F20_0 *)arg0)->unk_2A - 1;
    ((S_800C4F20_0 *)arg0)->unk_2A = temp_v0_7;
    if ((temp_v0_7 << 0x10) > 0) {
        goto block_24;
    }
    temp_a0_7 = ((S_800C4F20_0 *)arg0)->unk_24;
    temp_a0_7->unk_14 = (s32) (temp_a0_7->unk_14 & 0xFFEFFFFF);
    ((S_800C4F20_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800C4F20_0_pre *)arg0)[-1].unk_00 | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((Rec_D_800814A0 *)(&D_800814A0))->unk_00 | 0x8000);
    return;
jt_c4:
jt_c5:
jt_c6:
jt_c7:
jt_c8:
jt_c9:
jt_c10:
jt_c11:
jt_c12:
jt_c13:
jt_c14:
jt_c15:
jt_c16:
block_24:
    if (!(((S_800C4F20_11 *)(((S_800C4F20_10 *)arg0)->unk_24))->unk_14 & 0x100000)) {
        goto block_26;
    }
    ((S_800C4F20_12 *)(((S_800C4F20_10 *)arg0)->unk_1C))->unk_02 = (u16) arg1->unk_02;
    ((S_800C4F20_12 *)(((S_800C4F20_10 *)arg0)->unk_1C))->unk_06 = (u16) arg1->unk_06;
    ((S_800C4F20_12 *)(((S_800C4F20_10 *)arg0)->unk_1C))->unk_0A = (u16) arg1->unk_0A;
block_26:
    ((S_800C4F20_0 *)arg0)->unk_2C = (s16) ((u16) ((S_800C4F20_0 *)arg0)->unk_2C + 1);
    arg2->unk_1A = (u16) (arg2->unk_1A - 0x80);
    return;
}
