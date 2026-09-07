#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_800930F0_12 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_800930F0_12;   /* ((Rec_D_800E3D7C *)arg0)->unk_C8 in func_800930F0 */



typedef struct S_800930F0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800930F0_1;   /* arg2 in func_800930F0 */

typedef struct S_800930F0_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800930F0_2;   /* arg3 in func_800930F0 */

typedef struct S_800930F0_3 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_800930F0_3;   /* var_s2 in func_800930F0 */

typedef struct S_800930F0_4 {
    u8 pad_00[0x234];
    s32 unk_234;
    u8 pad_238[0x1E58];
    s32 unk_2090;
    u8 pad_2094[0x1680];
    union { u16 s; s16 u; } unk_3714;   /* accessed as both */
    s16 unk_3716;
    s16 unk_3718;
    s16 unk_371A;
} S_800930F0_4;   /* var_s0 in func_800930F0 */

typedef struct S_800930F0_5 {
    union { M2C_UNK * s; void * (*u)(s32, s32); } unk_00;   /* accessed as both */
    s32 unk_04;
    s32 unk_08;
} S_800930F0_5;   /* &D_800E4938 in func_800930F0 */

typedef struct S_800930F0_6 {
    s32 unk_00;
} S_800930F0_6;   /* &D_800E296C in func_800930F0 */

typedef struct S_800930F0_7 {
    u16 unk_00;
} S_800930F0_7;   /* &D_80013714 in func_800930F0 */

typedef struct S_800930F0_8 {
    u8 pad_00[0x3CD0];
    union { u8 s; s8 u; } unk_3CD0;   /* accessed as both */
} S_800930F0_8;   /* var_v1 in func_800930F0 */

typedef struct S_800930F0_9 {
    u8 pad_00[0x2E76];
    u16 unk_2E76;
} S_800930F0_9;   /* store_base in func_800930F0 */

typedef struct S_800930F0_10 {
    u8 pad_00[0xCC];
    s32 unk_CC;
    u8 pad_D0[0x84];
    s32 unk_154;
} S_800930F0_10;   /* var_v0 in func_800930F0 */


extern void *D_80088A10[];
void func_80040AA0();
void func_80041094();
s32 func_800429E4();
void func_80043568();
void func_800481E0();
M2C_UNK func_800945E8();
M2C_UNK func_800948BC();
M2C_UNK func_800A56E0();
s32 func_800A613C();
M2C_UNK func_800A6780();
void func_800B2074();
M2C_UNK func_800C542C();
extern s32 D_80010234;
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} __attribute__((packed)) UnalignedCopy3;
extern UnalignedCopy3 D_80012080;
extern UnalignedCopy3 D_80013710;
extern M2C_UNK D_80013714;
extern M2C_UNK D_80021268;
extern u16 D_8008146C;
extern u8 D_80082E6B;
extern u16 D_80082E76;
extern s32 D_80082EB8;
extern M2C_UNK D_80083160;
extern s16 D_800DCED4[];
extern s32 D_800DCF64;
extern M2C_UNK D_800E296C;
extern M2C_UNK D_800E3CD0;
extern M2C_UNK D_800E4938;

void func_800930F0(void *arg0, s32 arg1, S_800930F0_1 *arg2, S_800930F0_2 *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17 };
    M2C_UNK *var_v0;
    M2C_UNK *var_v1;
    u8 *var_s0;
    s32 *var_s2;
    s32 var_s1;
    s32 temp_s0;
    s32 temp_v0_2;
    u16 temp_v0;
    u8 temp_v1;
    void *temp_v0_3;
    s16 *var_s4;

    temp_v1 = ((Rec_D_800E3D7C *)arg0)->unk_9B;
    if (temp_v1 >= 0x12U) {
        goto block_25;
    }
    (void)jt_keep; goto *D_80088A10[(u32)(temp_v1)];
jt_c0:
    var_s1 = 1;
    ((Rec_D_800E3D7C *)arg0)->unk_96 = 0U;
    func_800B2074((arg2->unk_24 << 6) | 0x20, (arg2->unk_25 << 6) | 0x20);
    var_s4 = &D_800DCED4;
    var_s2 = (s32 *)arg0 + 1;
    arg3->unk_1C = (s32) (arg3->unk_1C | 0x40000000);
    do {
        temp_s0 = ((S_800930F0_3 *)var_s2)->unk_AC;
        if (temp_s0 != 0) {
            func_800C542C(temp_s0, var_s4[func_800429E4(temp_s0)], (s16)var_s1, 0);
        }
        var_s1 -= 1;
        var_s2 -= 1;
    } while (var_s1 >= 0);
    ((Rec_D_800E3D7C *)arg0)->unk_9B = (u8) (((Rec_D_800E3D7C *)arg0)->unk_9B + 1);
jt_c1:
    temp_v0 = ((Rec_D_800E3D7C *)arg0)->unk_96 + 1;
    ((Rec_D_800E3D7C *)arg0)->unk_96 = temp_v0;
    if ((s16) temp_v0 < 0x3D) {
        goto block_26;
    }
    var_v1 = (M2C_UNK *)0x800E0000;
    var_s0 = (u8 *)0x80010000;
    if (((S_800930F0_4 *)var_s0)->unk_3714.s & 4) {
        goto block_21;
    }
    func_800945E8(arg0);
    func_800948BC();
    ASM_KEEP(var_s0);   /* MATCH pin: load-bearing for the whole function shape */
    {
        register UnalignedCopy3 *copy_src ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
        UnalignedCopy3 *copy_dst;
        register s32 copy_v0 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
        s32 copy_v1;

        copy_src = (UnalignedCopy3 *)0x80013710;
        copy_dst = (UnalignedCopy3 *)0x80012080;
        ASM_KEEP(copy_dst);   /* MATCH pin: keeps a constant in a register as retail does */
        copy_v0 = copy_src->unk0;
        copy_v1 = copy_src->unk4;
        copy_dst->unk0 = copy_v0;
        copy_dst->unk4 = copy_v1;
        copy_v0 = copy_src->unk8;
        copy_dst->unk8 = copy_v0;
        ((S_800930F0_4 *)var_s0)->unk_3714.u = 0;
        ((S_800930F0_4 *)var_s0)->unk_3716 = 0;
        ((S_800930F0_4 *)var_s0)->unk_3718 = 0;
        ((S_800930F0_4 *)var_s0)->unk_371A = 0;
        func_800A6780(copy_dst, copy_src);
    }
    if (((S_800930F0_4 *)var_s0)->unk_2090 == 0) {
        goto block_12;
    }
    if (((S_800930F0_4 *)var_s0)->unk_2090 != 1) {
        goto block_12;
    }
    ((S_800930F0_4 *)var_s0)->unk_234 = (s32) (((S_800930F0_4 *)var_s0)->unk_234 + 1);
    func_80043568();
    ((S_800930F0_4 *)var_s0)->unk_2090 = 0;
    goto block_13;
block_12:
    ((S_800930F0_4 *)var_s0)->unk_234 = (s32) (((S_800930F0_4 *)var_s0)->unk_234 + 1);
block_13:
    func_800A56E0(0x514);
    ((S_800930F0_5 *)(&D_800E4938))->unk_00.s = &D_80021268;
    D_80082EB8 = 0;
    (*(s32 *)&D_800E296C) = (s32) (((S_800930F0_6 *)(&D_800E296C))->unk_00 | 0x2000);
    goto block_24;
jt_c2:
    temp_v0_2 = func_800A613C();
    D_800DCF64 = temp_v0_2;
    if (temp_v0_2 == 0) {
        goto block_25;
    }
    goto block_24;
jt_c3:
    temp_v0_3 = ((S_800930F0_5 *)(&D_800E4938))->unk_00.u(((S_800930F0_5 *)(&D_800E4938))->unk_04, ((S_800930F0_5 *)(&D_800E4938))->unk_08);
    ((Rec_D_800E3D7C *)arg0)->unk_C8 = temp_v0_3;
    if (temp_v0_3 == NULL) {
        goto block_27;
    }
    ((Rec_D_800E3D7C *)arg0)->unk_9B = (u8) (((Rec_D_800E3D7C *)arg0)->unk_9B + 1);
jt_c4:
    if (!(((S_800930F0_12 *)(((Rec_D_800E3D7C *)arg0)->unk_C8))->unk_1E & 0x8000)) {
        goto block_25;
    }
    func_80040AA0(D_80082E6B);
    D_8008146C = *(u16 *)0x80010234;
    func_800481E0();
    goto block_24;
jt_c16:
    var_v1 = (M2C_UNK *)0x800E0000;
    if (!(((S_800930F0_7 *)(&D_80013714))->unk_00 & 4)) {
        goto block_23;
    }
block_21:
    if (((S_800930F0_8 *)var_v1)->unk_3CD0.s != 0) {
        goto block_26;
    }
    ((S_800930F0_8 *)var_v1)->unk_3CD0.u = 1;
    func_80040AA0(3U);
    goto block_26;
block_23:
    func_800945E8(arg0);
    func_800948BC();
    {
        s32 call_a0;
        register s32 call_a1 ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
        register s32 call_a2 ASM_REG("$6");   /* MATCH pin: keeps a statement from moving across a call/branch */
        register s32 call_a3 ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
        u8 *store_base;
        register u16 store_value ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

        call_a0 = 6;
        call_a1 = 0;
        call_a2 = call_a1;
        call_a3 = call_a1;
        ASM_KEEP4_NV(call_a0, call_a1, call_a2, call_a3);   /* MATCH pin: retail schedule: same instructions, different order without it */
        store_base = (u8 *)0x80080000;
        ASM_KEEP(store_base);   /* MATCH pin: keeps a statement from moving across a call/branch */
        store_value = 0x8000;
        ((S_800930F0_9 *)store_base)->unk_2E76 = store_value;
        func_80041094(call_a0, call_a1, call_a2, call_a3, 0x8000);
    }
block_24:
    ((Rec_D_800E3D7C *)arg0)->unk_9B = (u8) (((Rec_D_800E3D7C *)arg0)->unk_9B + 1);
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
jt_c17:
block_25:
    goto block_26;
block_26:
    var_v0 = &D_80083160;
    ((S_800930F0_10 *)var_v0)->unk_CC = 0;
    ((S_800930F0_10 *)var_v0)->unk_154 = 0;
    (*(s32 *)&D_800E296C) = (s32) (((S_800930F0_6 *)(&D_800E296C))->unk_00 | 0x40000);
block_27:
    return;
}
