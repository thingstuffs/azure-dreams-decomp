#include "common.h"
#include "m2c_compat.h"

typedef struct S_8016E528_0_pre {
    u16 unk_00;
} S_8016E528_0_pre;   /* the 0x2 bytes before arg0 in func_8016E528, addressed as arg0[-1] */

typedef struct S_8016E528_0 {
    u8 pad_00[0x12];
    s16 unk_12;
    s16 unk_14;
    u8 pad_16[0x2];
    s16 unk_18;
    u16 unk_1A;
    u8 pad_1C[0x28];
    u8 unk_44;
    u8 unk_45;
    u8 unk_46;
    u8 unk_47;
    s8 unk_48;
    s8 unk_49;
    u8 pad_4A[0x2];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_8016E528_0;   /* arg0 in func_8016E528 */

typedef struct S_8016E528_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8016E528_1;   /* arg2 in func_8016E528 */

typedef struct S_8016E528_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; volatile u16 v; } at02u; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_8016E528_2;   /* arg1 in func_8016E528 */

typedef struct S_8016E528_3 {
    s16 unk_00;
    s16 unk_02;
} S_8016E528_3;   /* temp_a1 in func_8016E528 */

typedef struct S_8016E528_4 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_8016E528_4;   /* ((((S_8016E528_0 *)arg0)->unk_18 * 4) + table_base) in func_8016E528 */


extern void *D_8016A868[];
s32 func_800A45D8();
s32 func_800A7234();
M2C_UNK func_800A7A7C();
s16 func_800BCB04();
void func_8016E63C(void) __attribute__((noreturn));
void func_8016E824(void) __attribute__((noreturn));
void func_8016E9E0(void) __attribute__((noreturn));
void func_8016EAF4(void) __attribute__((noreturn));
extern s32 D_800814A0;
extern u8 D_80174708;

void func_8016E528(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    u8 sp18[4];
    s32 temp_s0;
    s16 temp_s0_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_v0;
    s32 var_v1;
    s32 temp_a0;
    s32 temp_y;
    u16 temp_v0;
    s16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_a2;
    u32 temp_v1;
    void *temp_a1;
    u8 *table_base;

    if (((S_8016E528_0 *)arg0)->unk_12 != 3) {
        goto block_4;
    }
    temp_v0 = ((S_8016E528_0 *)arg0)->unk_1A;
    ((S_8016E528_0 *)arg0)->unk_1A = (u16) (temp_v0 + 1);
    if ((s16) temp_v0 < 0x38) {
        goto block_3;
    }
    ((S_8016E528_0 *)arg0)->unk_12 = 0;
    ((S_8016E528_1 *)arg2)->unk_14 = (u16) (((S_8016E528_1 *)arg2)->unk_14 & 0xFF7F);
    ((S_8016E528_0 *)arg0)->unk_1A = 0U;
    ((S_8016E528_0 *)arg0)->unk_60 = 0x14900;
block_3:
block_4:
    if (((S_8016E528_0 *)arg0)->unk_12 != 1) {
        goto block_28;
    }
    if (((S_8016E528_0 *)arg0)->unk_14 != 0) {
        goto block_21;
    }
    ((S_8016E528_0 *)arg0)->unk_14 = (s16) ((u16) ((S_8016E528_0 *)arg0)->unk_14 + 1);
    temp_a0 = ((S_8016E528_0 *)arg0)->unk_49;
    var_v1 = ((S_8016E528_2 *)arg1)->unk_0E - ((S_8016E528_0 *)arg0)->unk_48;
    temp_y = ((S_8016E528_2 *)arg1)->unk_12;
    if (var_v1 >= 0) {
        goto block_8;
    }
    var_v1 = 0 - var_v1;
block_8:
    var_v0 = temp_y - temp_a0;
    if (var_v0 >= 0) {
        goto block_10;
    }
    var_v0 = 0 - var_v0;
block_10:
    temp_v1 = var_v1 + var_v0;
    if (temp_v1 >= 5U) {
        goto block_20;
    }
    (void)jt_keep; goto *D_8016A868[(u32)(temp_v1)];
jt_c0:
    var_v0 = 4;
    goto jt_set_countdown;
jt_c1:
    var_v0 = 8;
    goto jt_set_countdown;
jt_c2:
    var_v0 = 0xC;
    goto jt_set_countdown;
jt_c3:
    var_v0 = 0xE;
    goto jt_set_countdown;
jt_c4:
block_20:
    var_v0 = 0x10;
jt_set_countdown:
    ((S_8016E528_0 *)arg0)->unk_1A = var_v0;
block_21:
    temp_v0_2 = ((S_8016E528_0 *)arg0)->unk_1A - 1;
    ((S_8016E528_0 *)arg0)->unk_1A = temp_v0_2;
    if ((s16) temp_v0_2 == 0) {
        goto block_23;
    }
    {
        s32 interp_target;
        s32 interp_current;
        interp_target = ((S_8016E528_2 *)arg1)->unk_0E << 6;
        interp_current = ((S_8016E528_2 *)arg1)->unk_00.at02.v - 0x20;
        ((S_8016E528_2 *)arg1)->unk_00.at02.v = (s16) ((u16) ((S_8016E528_2 *)arg1)->unk_00.at02.v + (interp_target - interp_current) / (s16) temp_v0_2);
    }
    {
        s32 interp_target;
        s32 interp_current;
        interp_target = ((S_8016E528_2 *)arg1)->unk_12 << 6;
        interp_current = ((S_8016E528_2 *)arg1)->unk_04.at02.v - 0x20;
        ((S_8016E528_2 *)arg1)->unk_04.at02.v = (s16) ((u16) ((S_8016E528_2 *)arg1)->unk_04.at02.v + (interp_target - interp_current) / (s16) ((S_8016E528_0 *)arg0)->unk_1A);
    }
    ((S_8016E528_2 *)arg1)->unk_08.at02.v = (s16) ((u16) ((S_8016E528_2 *)arg1)->unk_08.at02.v + ((s32) (((S_8016E528_2 *)arg1)->unk_16 - ((S_8016E528_2 *)arg1)->unk_08.at02.v) / (s16) ((S_8016E528_0 *)arg0)->unk_1A));
block_23:
    if ((s16) ((S_8016E528_0 *)arg0)->unk_1A > 0) {
        goto block_26;
    }
    sp18[0] = ((S_8016E528_0 *)arg0)->unk_44;
    sp18[1] = ((S_8016E528_0 *)arg0)->unk_45;
    sp18[2] = ((S_8016E528_0 *)arg0)->unk_46;
    sp18[3] = ((S_8016E528_0 *)arg0)->unk_47;
    func_800A7A7C(((S_8016E528_2 *)arg1)->unk_0E, ((S_8016E528_2 *)arg1)->unk_12, ((S_8016E528_2 *)arg1)->unk_16, ((S_8016E528_1 *)arg2)->unk_08, sp18);
    func_8016E824();
    return;
block_26:
    if (((S_8016E528_1 *)arg2)->unk_14 & 0x8000) {
        goto block_3;
    }
block_27:
block_28:
    if (((S_8016E528_0 *)arg0)->unk_12 != 2) {
        goto loop_33;
    }
    ((S_8016E528_2 *)arg1)->unk_08.at00.v = (s32) (((S_8016E528_2 *)arg1)->unk_08.at00.v + ((S_8016E528_0 *)arg0)->unk_54);
    ((S_8016E528_0 *)arg0)->unk_54 = (s32) (((S_8016E528_0 *)arg0)->unk_54 + ((S_8016E528_0 *)arg0)->unk_60);
    temp_v0_3 = ((S_8016E528_1 *)arg2)->unk_1E - 0xC8;
    ((S_8016E528_1 *)arg2)->unk_1E = temp_v0_3;
    ((S_8016E528_1 *)arg2)->unk_1C = temp_v0_3;
    temp_a2 = ((S_8016E528_2 *)arg1)->unk_08.at02u.v;
    temp_s0 = ((S_8016E528_2 *)arg1)->unk_08.at02.v;
    if ((func_800BCB04((((S_8016E528_0 *)arg0)->unk_48 << 6) & 0xFFC0, (((S_8016E528_0 *)arg0)->unk_49 << 6) & 0xFFC0, (s16) (temp_a2 - 0x20)) - 7) >= temp_s0) {
        goto block_32;
    }
    ((S_8016E528_2 *)arg1)->unk_08.at02.v = func_800BCB04((((S_8016E528_0 *)arg0)->unk_48 << 6) & 0xFFC0, (((S_8016E528_0 *)arg0)->unk_49 << 6) & 0xFFC0, (s16) ((u16) ((S_8016E528_2 *)arg1)->unk_08.at02.v - 0x20));
    ((S_8016E528_2 *)arg1)->unk_08.at00u.v = 0;
    (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_8016E528_0_pre *)arg0)[-1].unk_00 | 0x8000);
    D_800814A0 |= 0x8000;
    return;
block_32:
    if (((S_8016E528_1 *)arg2)->unk_14 & 0x8000) {
        goto block_27;
    }
loop_33:
    if (((S_8016E528_0 *)arg0)->unk_12 != 0) {
        goto block_49;
    }
    ((S_8016E528_2 *)arg1)->unk_00.at00.v = (s32) (((S_8016E528_2 *)arg1)->unk_00.at00.v + ((S_8016E528_0 *)arg0)->unk_4C);
    ((S_8016E528_0 *)arg0)->unk_4C = (s32) (((S_8016E528_0 *)arg0)->unk_4C + ((S_8016E528_0 *)arg0)->unk_58);
    ((S_8016E528_2 *)arg1)->unk_04.at00.v = (s32) (((S_8016E528_2 *)arg1)->unk_04.at00.v + ((S_8016E528_0 *)arg0)->unk_50);
    table_base = &D_80174708;
    ((S_8016E528_0 *)arg0)->unk_50 = (s32) (((S_8016E528_0 *)arg0)->unk_50 + ((S_8016E528_0 *)arg0)->unk_5C);
    temp_a1 = (((S_8016E528_0 *)arg0)->unk_18 * 4) + table_base;
    var_v1 = ((S_8016E528_0 *)arg0)->unk_48 + ((S_8016E528_3 *)temp_a1)->unk_00;
    var_a0 = ((S_8016E528_2 *)arg1)->unk_00.at02.v;
    if (var_a0 >= 0) {
        goto block_36;
    }
    var_a0 += 0x3F;
block_36:
    if (var_v1 != (var_a0 >> 6)) {
        goto block_45;
    }
    var_v1 = ((S_8016E528_0 *)arg0)->unk_49 + ((S_8016E528_3 *)temp_a1)->unk_02;
    var_a0_2 = ((S_8016E528_2 *)arg1)->unk_04.at02.v;
    if (var_a0_2 >= 0) {
        goto block_39;
    }
    var_a0_2 += 0x3F;
block_39:
    if (var_v1 != (var_a0_2 >> 6)) {
        goto block_45;
    }
    if ((func_800A45D8((u16) ((S_8016E528_2 *)arg1)->unk_00.at02.v, (u16) ((S_8016E528_2 *)arg1)->unk_04.at02.v, ((S_8016E528_2 *)arg1)->unk_08.at02.v) << 0x10) != 0) {
        goto block_42;
    }
    if (func_800BCB04((u16) ((S_8016E528_2 *)arg1)->unk_00.at02.v, (u16) ((S_8016E528_2 *)arg1)->unk_04.at02.v, ((S_8016E528_2 *)arg1)->unk_08.at02.v) < 0x200) {
        goto block_44;
    }
block_42:
    ((S_8016E528_2 *)arg1)->unk_00.at00.v = (s32) (((S_8016E528_2 *)arg1)->unk_00.at00.v - ((S_8016E528_0 *)arg0)->unk_4C);
    ((S_8016E528_0 *)arg0)->unk_4C = 0;
    ((S_8016E528_0 *)arg0)->unk_58 = 0;
    ((S_8016E528_2 *)arg1)->unk_04.at00.v = (s32) (((S_8016E528_2 *)arg1)->unk_04.at00.v - ((S_8016E528_0 *)arg0)->unk_50);
    ((S_8016E528_0 *)arg0)->unk_50 = 0;
    ((S_8016E528_0 *)arg0)->unk_5C = 0;
    func_8016E9E0();
    return;
block_44:
    ((S_8016E528_0 *)arg0)->unk_48 = (s8) ((u8) ((S_8016E528_0 *)arg0)->unk_48 + *((((S_8016E528_0 *)arg0)->unk_18 * 4) + table_base));
    ((S_8016E528_0 *)arg0)->unk_49 = (s8) ((u8) ((S_8016E528_0 *)arg0)->unk_49 + ((S_8016E528_4 *)(((((S_8016E528_0 *)arg0)->unk_18 * 4) + table_base)))->unk_02);
    ((S_8016E528_1 *)arg2)->unk_06 = 0;
block_45:
    ((S_8016E528_2 *)arg1)->unk_08.at00.v = (s32) (((S_8016E528_2 *)arg1)->unk_08.at00.v + ((S_8016E528_0 *)arg0)->unk_54);
    ((S_8016E528_0 *)arg0)->unk_54 = (s32) (((S_8016E528_0 *)arg0)->unk_54 + ((S_8016E528_0 *)arg0)->unk_60);
    temp_s0_2 = ((S_8016E528_2 *)arg1)->unk_08.at02.v;
    if ((func_800BCB04(((((S_8016E528_0 *)arg0)->unk_48 << 6) + 0x20) & 0xFFE0, ((((S_8016E528_0 *)arg0)->unk_49 << 6) + 0x20) & 0xFFE0, temp_s0_2) - 0x10) >= temp_s0_2) {
        goto block_48;
    }
    ((S_8016E528_2 *)arg1)->unk_08.at02.v = func_800BCB04(((((S_8016E528_0 *)arg0)->unk_48 << 6) + 0x20) & 0xFFE0, ((((S_8016E528_0 *)arg0)->unk_49 << 6) + 0x20) & 0xFFE0, ((S_8016E528_2 *)arg1)->unk_08.at02.v);
    ((S_8016E528_2 *)arg1)->unk_08.at00u.v = 0;
    ((S_8016E528_0 *)arg0)->unk_5C = 0;
    ((S_8016E528_0 *)arg0)->unk_50 = 0;
    ((S_8016E528_0 *)arg0)->unk_58 = 0;
    ((S_8016E528_0 *)arg0)->unk_4C = 0;
    ((S_8016E528_0 *)arg0)->unk_12 = (s16) ((u16) ((S_8016E528_0 *)arg0)->unk_12 + 1);
    if ((func_800A7234(((S_8016E528_0 *)arg0)->unk_48, ((S_8016E528_0 *)arg0)->unk_49, (s16) ((u16) ((S_8016E528_2 *)arg1)->unk_08.at02.v - 0x20), arg1 + 0xE, arg1 + 0x12, arg1 + 0x16) << 0x10) != 0) {
        goto block_48;
    }
    ((S_8016E528_0 *)arg0)->unk_12 = 2;
    ((S_8016E528_0 *)arg0)->unk_54 = 0xFFF80000;
block_48:
    if (((S_8016E528_1 *)arg2)->unk_14 & 0x8000) {
        goto loop_33;
    }
block_49:
    return;
}
