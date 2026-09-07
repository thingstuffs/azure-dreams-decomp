#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_801728B4_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    void * unk_A0;
} S_801728B4_0;   /* arg0 in func_801728B4 */


typedef struct S_801728B4_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801728B4_2_pre;   /* the 0x14 bytes before var_v0 in func_801728B4, addressed as var_v0[-1] */

typedef struct S_801728B4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801728B4_3;   /* temp_v1_3 in func_801728B4 */


typedef struct S_801728B4_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801728B4_5;   /* arg1 in func_801728B4 */

typedef struct S_801728B4_6 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x36];
    u16 unk_4A;
    u8 pad_4C[0x6F];
    s8 unk_BB;
} S_801728B4_6;   /* temp_v0_2 in func_801728B4 */

typedef struct S_801728B4_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_801728B4_7;   /* temp_a0 in func_801728B4 */


typedef struct S_801728B4_9 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xAB];
    u8 unk_BB;
} S_801728B4_9;   /* var_s0 in func_801728B4 */

typedef struct S_801728B4_10 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801728B4_10;   /* temp_v1_4 in func_801728B4 */

typedef struct S_801728B4_11 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801728B4_11;   /* ((S_801728B4_6 *)temp_v0_2)->unk_08 in func_801728B4 */

extern void *D_80170838[];
s32 func_8003F270(void);
void *func_8003FD64();
s32 func_8004491C();
void func_80047784();
void *func_800A05A4();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
s32 func_800A94A0(void *, u8 *, s32, void *);
extern M2C_UNK D_80045340;
extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[];
extern s32 D_8008346C;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800D7960;
extern M2C_UNK D_80170E54;
extern u8 D_80173C6C[];

void func_801728B4(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_a1_2;
    s32 var_s4;
    s32 var_v0_2;
    s32 var_v1;
    u16 pending[4];
    u16 temp_v0_3;
    u16 temp_v0_5;
    u16 temp_v1_5;
    u8 *var_s0;
    s32 temp_v1;
    u8 *temp_v1_4;
    void *temp_a0;
    void *temp_v0_2;
    register void *temp_v0_4 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register void *temp_v1_3 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    void *var_v0;

    temp_v1 = ((S_801728B4_0 *)arg0)->unk_9B;
    var_s4 = 0;
    if (temp_v1 == 1) {
        goto block_37;
    }
    if ((s32) temp_v1 >= 2) {
        goto block_4;
    }
    if (temp_v1 == 0) {
        goto block_6;
    }
    return;
block_4:
    if (temp_v1 == 2) {
        goto block_40;
    }
    return;
block_6:
    if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x2000)) {
        goto block_12;
    }
    temp_v0 = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x3FFF;
    if ((u32) (temp_v0 - 1) >= 7U) {
        goto block_20;
    }
    (void)jt_keep; goto *D_80170838[(u32)((temp_v0) - 1)];
jt_c7:
    var_s4 = 1;
    goto block_17;
jt_c6:
    var_s4 = 1;
    goto block_18;
jt_c5:
    var_s4 = 1;
    goto block_19;
block_12:
    temp_v1_2 = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x3FFF;
    if (temp_v1_2 == 2) {
        goto block_18;
    }
    if (temp_v1_2 >= 3) {
        goto block_16;
    }
    var_s0 = NULL;
    if (temp_v1_2 == 1) {
        goto block_19;
    }
    goto block_21;
block_16:
    var_s0 = NULL;
    if (temp_v1_2 != 3) {
        goto block_21;
    }
jt_c3:
block_17:
    var_s0 = arg3 + 0xE;
    goto block_21;
jt_c2:
block_18:
    var_s0 = arg3 + 0xB;
    goto block_21;
jt_c1:
block_19:
    var_s0 = arg3 + 8;
    goto block_21;
jt_c4:
block_20:
    var_s0 = NULL;
block_21:
    if (*var_s0 == 0) {
        goto block_36;
    }
    ((S_801728B4_0 *)arg0)->unk_98 = (u16) (((S_801728B4_0 *)arg0)->unk_98 & 0xFF7F);
    {
        s32 flag = var_s4;

        ASM_KEEP(flag);   /* MATCH pin: retail basic-block layout depends on it */
        if (flag == 0) {
            goto block_24;
        }
    }
    var_v0 = D_800814A8;
    ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv = var_v0;
    goto block_26;
block_24:
    if (D_8006DE24[(*var_s0 * 0x14) + 0x12] != 2) {
        goto block_27;
    }
    var_v0 = ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv;
    if (var_v0 == NULL) {
        goto block_33;
    }
block_26:
    temp_v1_3 = ((S_801728B4_2_pre *)var_v0)[-1].unk_00;
    ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8 = (s8) ((S_801728B4_3 *)temp_v1_3)->unk_24;
    ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8 = (s8) ((S_801728B4_3 *)temp_v1_3)->unk_25;
    goto block_32;
block_27:
    ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv = func_800A05A4(arg3, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 0x10);
    ASM_KEEP(arg3);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    var_v0_2 = ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8;
    var_v1 = ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8;
    if (var_v0_2 >= 0) {
        goto block_29;
    }
    var_v0_2 = 0 - var_v0_2;
block_29:
    if (var_v1 >= 0) {
        goto block_31;
    }
    var_v1 = 0 - var_v1;
block_31:
    ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8 = var_v0_2;
    ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8 = var_v1;
block_32:
block_33:
    pending[0] = ((S_801728B4_5 *)arg1)->unk_00.at02.v;
    pending[1] = ((S_801728B4_5 *)arg1)->unk_04.at02.v;
    pending[2] = ((S_801728B4_5 *)arg1)->unk_08.at02.v;
    if (func_800A94A0(arg3, var_s0, var_s4, arg0 + 0x98) == 0) {
        goto block_56;
    }
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xF7FF);
    func_800A56E0(0x703);
    ((S_801728B4_0 *)arg0)->unk_9B = (u8) (((S_801728B4_0 *)arg0)->unk_9B + 1);
    temp_v0_2 = func_8003FD64(0x112, &D_80083498);
    ((S_801728B4_0 *)arg0)->unk_A0 = temp_v0_2;
    if (temp_v0_2 == NULL) {
        goto block_56;
    }
    func_8004491C(temp_v0_2, &D_80045340);
    ((S_801728B4_6 *)temp_v0_2)->unk_10 = &D_800D7960;
    ((S_801728B4_11 *)(((S_801728B4_6 *)temp_v0_2)->unk_08))->unk_00 = (s32) ((S_801728B4_5 *)arg1)->unk_00.at00.v;
    ((S_801728B4_11 *)(((S_801728B4_6 *)temp_v0_2)->unk_08))->unk_04 = (s32) ((S_801728B4_5 *)arg1)->unk_04.at00.v;
    ((S_801728B4_11 *)(((S_801728B4_6 *)temp_v0_2)->unk_08))->unk_08 = (s32) (((S_801728B4_5 *)arg1)->unk_08.at00.v + 0xFF800000);
    ((S_801728B4_6 *)temp_v0_2)->unk_BB = 0;
    temp_a0 = ((S_801728B4_6 *)temp_v0_2)->unk_0C;
    ((S_801728B4_6 *)temp_v0_2)->unk_4A = (u16) ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16;
    temp_v1_2 = ((Rec_D_80082E80 *)arg2)->unk_28.at00_s32.v;
    ((S_801728B4_7 *)temp_a0)->unk_1E = 0x1000;
    ((S_801728B4_7 *)temp_a0)->unk_1C = 0x1000;
    ((S_801728B4_7 *)temp_a0)->unk_28 = temp_v1_2;
    temp_v0_3 = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v;
    temp_a1_2 = 0x2D;
    ((S_801728B4_7 *)temp_a0)->unk_14 = temp_v0_3;
    temp_v1_5 = ((Rec_D_80082E80 *)arg2)->unk_12.at00_u16.v;
    ((S_801728B4_7 *)temp_a0)->unk_10 = 0;
    ((S_801728B4_7 *)temp_a0)->unk_14 = (u16) (temp_v0_3 | 0xC);
    ((S_801728B4_7 *)temp_a0)->unk_12 = (s16) (temp_v1_5 - 0x80);
    ((S_801728B4_7 *)temp_a0)->unk_0C = (s32) ((Rec_D_80082E80 *)arg2)->unk_0C.at00_s32.v;
    func_80047784(temp_a0, temp_a1_2, 0);
    return;
block_36:
    ((S_801728B4_5 *)arg1)->unk_14 = 0;
    ((S_801728B4_5 *)arg1)->unk_10 = 0;
    ((S_801728B4_5 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    D_8008346C = 0;
    ((Rec_D_800814A8 *)D_800814A8)->unk_A6 = (u16) ((*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1);
    func_800A4ACC(arg3);
    ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 - 1);
    ((S_801728B4_0 *)arg0)->unk_8C = &D_80170E54;
    ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8 = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8 = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x7FFF);
    return;
block_37:
    if (func_8003F270() == 0) {
        goto block_39;
    }
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v | 0x800);
    return;
block_39:
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xF7FF);
    ((S_801728B4_0 *)arg0)->unk_9B = (u8) (((S_801728B4_0 *)arg0)->unk_9B + 1);
block_40:
    temp_v0_4 = ((S_801728B4_0 *)arg0)->unk_A0;
    if (temp_v0_4 == NULL) {
        goto block_43;
    }
    var_s0 = temp_v0_4;
    temp_a0 = ((S_801728B4_9 *)var_s0)->unk_0C;
    if (!(((S_801728B4_7 *)temp_a0)->unk_14 & 0xE000)) {
        goto block_43;
    }
    ((S_801728B4_9 *)var_s0)->unk_BB = 0xFF;
    ((S_801728B4_0 *)arg0)->unk_A0 = NULL;
block_43:
    if (((Rec_D_80082E80 *)arg2)->unk_04.as_s8 != 4) {
        goto block_45;
    }
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x1000) {
        goto block_46;
    }
block_45:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto block_47;
    }
block_46:
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v | 0x800);
    ((S_801728B4_0 *)arg0)->unk_96 = 3U;
    ((S_801728B4_0 *)arg0)->unk_98 = (u16) (((S_801728B4_0 *)arg0)->unk_98 | 0x80);
block_47:
    temp_v0_5 = ((S_801728B4_0 *)arg0)->unk_96 - 1;
    ((S_801728B4_0 *)arg0)->unk_96 = temp_v0_5;
    if ((temp_v0_5 << 0x10) > 0) {
        goto block_49;
    }
    ((S_801728B4_0 *)arg0)->unk_96 = 0U;
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xF7FF);
block_49:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto block_56;
    }
    ((S_801728B4_5 *)arg1)->unk_14 = 0;
    ((S_801728B4_5 *)arg1)->unk_10 = 0;
    ((S_801728B4_5 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pm == &D_80173C6C) {
        goto block_52;
    }
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = &D_80173C6C;
    func_80047784(arg2, D_80173C6C[((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
block_52:
    temp_v1_4 = D_80083460;
    if (((S_801728B4_10 *)temp_v1_4)->unk_0C != 0) {
        goto block_56;
    }
    ((S_801728B4_10 *)temp_v1_4)->unk_0A = (u16) (((S_801728B4_10 *)temp_v1_4)->unk_0A - 1);
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xF7FF);
    ((S_801728B4_0 *)arg0)->unk_8C = &D_80170E54;
    func_800A4ACC(arg3);
    if ((s8) ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 <= 0) {
        goto block_55;
    }
    ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 - 1);
block_55:
    ((Rec_D_800E3D7C *)arg3)->unk_73.as_s8 = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_72.as_s8 = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x7FFF);
    func_800A56E0(0xB4);
block_56:
    return;
}
