#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef s32 M2C_UNK;

typedef struct S_80170E9C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    s8 unk_9B;
} S_80170E9C_0;   /* arg0 in func_80170E9C */

typedef struct S_80170E9C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80170E9C_1;   /* arg3 in func_80170E9C */

typedef struct S_80170E9C_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    M2C_UNK * unk_2C;
} S_80170E9C_2;   /* arg2 in func_80170E9C */


typedef struct S_80170E9C_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170E9C_4;   /* case_entity in func_80170E9C */


typedef struct {
    u8 pad_00[0x24];
    u8 x;
    u8 y;
} RefPosition;

typedef struct {
    u8 pad_00[0xC];
    u16 flags;
    u8 pad_0E[6];
} TerrainEntry;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80170808[];
void func_80047784();
s32 func_8009A180();
s8 func_8009FB34();
s32 func_8009FD7C();
s16 func_800A0818();
s32 func_800A1C58();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AA258();
s32 func_800AA6B4();
M2C_UNK func_800AA79C();
M2C_UNK func_800AA888();
s32 func_800AA924();
s32 func_800AAB10();
M2C_UNK func_800AAF00();
M2C_UNK func_801713B8() __attribute__((noreturn));
M2C_UNK func_80171410();
M2C_UNK func_80171B58();
s32 func_80171E00();
M2C_UNK func_80171FC4();
M2C_UNK func_801737C4();
s32 func_80173A08();
M2C_UNK func_801747D0();
extern void *D_800814A8;
extern RefPosition D_80082E80;
extern u16 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern TerrainEntry D_800E2970[];
extern u8 D_80174EE0[];
extern M2C_UNK D_80174EF8;
extern M2C_UNK D_80174F00;
extern M2C_UNK D_80174F08;
extern M2C_UNK D_80174F10;

void func_80170E9C(void *in0, M2C_UNK in1, void *in2, void *in3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    void *arg0 = in0;
    M2C_UNK arg1 = in1;
    void *arg2 = in2;
    M2C_UNK sp18;
    M2C_UNK *var_v0;
    void *case_entity;
    RefPosition *case_ref;
    RefPosition *late_ref;
    s16 case_floor;
    s32 temp_a1;
    s32 temp_v0_3;
    s32 temp_v1;
    s8 temp_v0;
    u8 current_mode;
    u16 temp_v0_2;
    register void *arg3 ASM_REG("$18") = in3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u32 mode_14;

    if (!(D_80083462 & 0x1000)) {
        goto block_3;
    }
    ((S_80170E9C_0 *)arg0)->unk_9A = 0xEU;
    func_80171B58(arg0);
    return;
block_3:
    ASM_CLOBBER("$7");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    if (((S_80170E9C_1 *)arg3)->unk_25 != 0) {
        goto block_7;
    }
    func_800AA79C(arg0, arg1, arg2, arg3);
    if (((S_80170E9C_2 *)arg2)->unk_2C == &D_80174F00) {
        goto block_63;
    }
    {
        register M2C_UNK *dead_a1 ASM_REG("$5") = &D_80174EF8;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_TAILSLOT_PIN(dead_a1);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_801713B8();
    }
    return;
block_7:
    temp_v1 = ((S_80170E9C_1 *)arg3)->unk_1C;
    if (!(temp_v1 & 0x200)) {
        goto block_14;
    }
    if (((S_80170E9C_2 *)arg2)->unk_2C != &D_80174F00) {
        goto block_11;
    }
    ((S_80170E9C_0 *)arg0)->unk_9A = 0xDU;
    ((S_80170E9C_0 *)arg0)->unk_9B = 1;
    ((S_80170E9C_0 *)arg0)->unk_8C = 0;
    ((S_80170E9C_1 *)arg3)->unk_1C = (s32)(((S_80170E9C_1 *)arg3)->unk_1C & 0xFFFBFFFF);
    ((S_80170E9C_2 *)arg2)->unk_0E = 0x40;
    ((S_80170E9C_2 *)arg2)->unk_0D = 0x40;
    ((S_80170E9C_2 *)arg2)->unk_0C = 0x40;
    return;
block_11:
    if (func_800AA924(arg0, arg1, arg2, &D_80174EF8) == 0) {
        goto block_63;
    }
    ((S_80170E9C_1 *)arg3)->unk_1C |= 0x10000000;
    return;
block_14:
    if (D_80083462 & 0x2000) {
        goto block_30;
    }
    if (!(temp_v1 & 0x100)) {
        goto block_18;
    }
    func_800AA258(arg0, arg1, arg2, arg3);
    return;
block_18:
    current_mode = ((S_80170E9C_0 *)arg0)->unk_9A;
    mode_14 = 0xE;
    if (current_mode == mode_14) {
        goto block_22;
    }
    if (((S_80170E9C_2 *)arg2)->unk_2C == D_80174EE0) {
        goto block_21;
    }
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = D_80174EE0;
    func_80047784(arg2, D_80174EE0[((s32)(D_80083228 + ((S_80170E9C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
block_21:
    ((S_80170E9C_0 *)arg0)->unk_9A = mode_14;
block_22:
    ((S_80170E9C_0 *)arg0)->unk_98 = (u16)(((S_80170E9C_0 *)arg0)->unk_98 & 0xFFF3);
    if (((S_80170E9C_1 *)arg3)->unk_64 == 0) {
        goto block_24;
    }
    if (func_800AA6B4(arg0, arg1, arg2, &D_80174F10) != 0) {
        goto block_63;
    }
block_24:
    if (!(((S_80170E9C_1 *)arg3)->unk_1C & 0x80000)) {
        goto block_27;
    }
    func_800AA888(arg0, arg1, arg2, arg3);
    func_801737C4(arg0, arg1, arg2, arg3);
    return;
block_27:
    if ((func_800A1C58(arg3) << 0x10) == 0) {
        goto block_30;
    }
    if ((func_800AAB10(arg0, arg1, arg2, arg3) << 0x10) == 0) {
        goto block_30;
    }
    func_801747D0(arg0, arg1, arg2, arg3);
block_30:
    temp_v0 = func_8009FB34(((S_80170E9C_2 *)arg2)->unk_24.at00.v, ((S_80170E9C_2 *)arg2)->unk_24.at01.v);
    ((S_80170E9C_2 *)arg2)->unk_26 = temp_v0;
    if (((S_80170E9C_1 *)arg3)->unk_6D <= 0) {
        goto block_52;
    }
    if (((S_80170E9C_1 *)arg3)->unk_1C & 0x20) {
        goto block_44;
    }
    if (((S_80170E9C_2 *)arg2)->unk_24.at00u.v == D_80082EA4) {
        goto block_50;
    }
    if (((S_80170E9C_1 *)arg3)->unk_46 & 0x8000) {
        goto block_38;
    }
    if (!(D_80083462 & 0x2000)) {
        goto block_36;
    }
    if ((func_8009A180(arg3, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 0x10) != 0) {
        goto block_63;
    }
block_36:
    if ((func_80173A08(arg0, arg1, arg2, 0) << 0x10) == 0) {
        goto block_63;
    }
    temp_v0_2 = ((S_80170E9C_1 *)arg3)->unk_46 | 0x4000;
    ((S_80170E9C_1 *)arg3)->unk_46 = temp_v0_2;
    if (!(temp_v0_2 & 0x8000)) {
        goto block_50;
    }
block_38:
    temp_v0_3 = ((S_80170E9C_1 *)arg3)->unk_46 & 0x3FFF;
    if ((u32)(temp_v0_3 - 1) >= 0xCU) {
        goto block_49;
    }
    (void)jt_keep;
    goto *D_80170808[(u32)(temp_v0_3 - 1)];
jt_c8:
jt_c9:
    if ((func_80171E00(arg0, arg1, arg2, arg3) << 0x10) != 0) {
        goto block_63;
    }
    func_80171FC4(arg0, arg1, arg2, arg3);
    return;
jt_c5:
jt_c6:
jt_c7:
    case_ref = &D_80082E80;
    case_floor = func_800A0818(((S_80170E9C_2 *)arg2)->unk_24.at00.v, ((S_80170E9C_2 *)arg2)->unk_24.at01.v, case_ref->x, case_ref->y, &sp18);
    case_entity = D_800814A8;
    ((S_80170E9C_1 *)arg3)->unk_2A = case_floor;
    if (((S_80170E9C_4 *)case_entity)->unk_9A == 0x11) {
        goto jt_c1;
    }
jt_c12:
block_44:
    func_800A9A0C(arg3);
    return;
jt_c1:
jt_c2:
jt_c3:
    var_v0 = (M2C_UNK *)func_80170E9C;
block_47:
    func_800AAF00(arg0, arg1, arg2, &D_80174F08, var_v0);
    return;
jt_c4:
jt_c10:
jt_c11:
block_49:
block_50:
    func_80171410(arg0, arg1, arg2, arg3);
    return;
block_52:
    temp_a1 = ((S_80170E9C_1 *)arg3)->unk_1C;
    if (temp_a1 & 0x2000) {
        goto block_59;
    }
    if (temp_v0 < 0) {
        goto block_55;
    }
    if (D_800E2970[temp_v0].flags & 2) {
        goto block_59;
    }
block_55:
    if (temp_a1 & 0x430) {
        goto block_59;
    }
    late_ref = &D_80082E80;
    if ((func_8009FD7C(((S_80170E9C_2 *)arg2)->unk_24.at00.v, ((S_80170E9C_2 *)arg2)->unk_24.at01.v, late_ref->x, late_ref->y) << 0x10) == 0) {
        goto block_58;
    }
    ((S_80170E9C_1 *)arg3)->unk_2A = func_800A0818(((S_80170E9C_2 *)arg2)->unk_24.at00.v, ((S_80170E9C_2 *)arg2)->unk_24.at01.v, late_ref->x, late_ref->y, &sp18);
block_58:
block_59:
    if (D_80083462 & 0x2000) {
        goto block_63;
    }
    if (((S_80170E9C_2 *)arg2)->unk_14 & 0x40) {
        goto block_63;
    }
    if (((S_80170E9C_2 *)arg2)->unk_2C == D_80174EE0) {
        goto block_63;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = D_80174EE0;
    func_80047784(arg2, D_80174EE0[((s32)(D_80083228 + ((S_80170E9C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
block_63:
    return;
}
