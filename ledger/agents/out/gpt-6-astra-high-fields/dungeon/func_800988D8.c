#include "common.h"
#include "m2c_compat.h"

extern void *D_80088CB8[];
void func_8009DF0C();
s32 func_800A2C34();
M2C_UNK func_800A634C();
M2C_UNK func_800A67F4();
extern s16 D_80013630[4];
extern M2C_UNK D_8001363C;
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083160;
extern M2C_UNK D_800E296C;
extern void *D_800E3D7C;

typedef struct S_func_8009E038_0 {
    u8 pad_00[4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    u8 pad_18[2];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u16 unk_2C;
} S_func_8009E038_0;

typedef struct S_func_8009E038_1 {
    u8 pad_00[2];
    s16 unk_02;
    u8 pad_04[2];
    s16 unk_06;
} S_func_8009E038_1;

typedef struct S_func_8009E038_2 {
    u8 pad_00[0xC];
    union {
        s32 s32;
        struct {
            u8 unk_0C;
            u8 unk_0D;
            u8 unk_0E;
        } bytes;
    } unk_0C;
    u8 pad_10[0xC];
    u16 unk_1C;
    u16 unk_1E;
    union {
        s16 s16;
        u16 u16;
    } unk_20;
    union {
        s16 s16;
        u16 u16;
    } unk_22;
} S_func_8009E038_2;

typedef struct S_func_8009E038_3 {
    s32 unk_00;
} S_func_8009E038_3;

typedef struct S_func_8009E038_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_func_8009E038_4;

typedef struct S_func_8009E038_5 {
    u8 pad_00[8];
    s32 unk_08;
    u8 pad_0C[4];
    s32 unk_10;
} S_func_8009E038_5;

typedef struct S_func_8009E038_6 {
    u8 pad_00[0x296C];
    s32 unk_296C;
} S_func_8009E038_6;

typedef struct S_func_8009E038_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_func_8009E038_7;

typedef struct S_func_8009E038_8 {
    u8 pad_00[0x3630];
    s16 unk_3630;
    s16 unk_3632;
    s16 unk_3634;
    s16 unk_3636;
} S_func_8009E038_8;

void func_8009E038(S_func_8009E038_0 *arg0, S_func_8009E038_1 *arg1, S_func_8009E038_2 *arg2, M2C_UNK *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c16, &&jt_c32, &&jt_c48 };
    s32 var_a1;
    S_func_8009E038_7 *var_a3;
    S_func_8009E038_5 *var_s3;
    s16 temp_a0;
    s16 temp_a0_3;
    s16 temp_v0_10;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s32 temp_v1;
    register s16 temp_v1_10 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 temp_state_1e;
    s32 temp_a0_4;
    s32 temp_flags;
    s32 temp_flags_cleared;
    s32 temp_state;
    s32 var_a1_2;
    u16 temp_a0_2;
    u16 temp_v0;
    u16 temp_v0_11;
    u16 temp_v0_12;
    u16 temp_v0_2;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_8;
    u16 temp_v0_9;
    u16 temp_v1_4;
    u16 temp_v1_5;
    u16 temp_v1_6;
    u16 temp_v1_7;
    u16 temp_v1_8;
    u16 temp_v1_9;
    u8 temp_v1_2;
    u8 temp_v1_3;
    S_func_8009E038_2 *temp_s1;
    S_func_8009E038_8 *var_dpage;
    S_func_8009E038_6 *var_epage;
    S_func_8009E038_7 *var_v0_base;
    s32 var_a2;
    register s32 shared_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 reset_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    temp_s1 = arg2;
    var_s3 = (S_func_8009E038_5 *)&D_80083160;
    if (!(((S_func_8009E038_3 *)&D_800E296C)->unk_00 & 0x2000)) {
        goto block_3;
    }
    if (arg0->unk_1A >= 0x20) {
        goto block_3;
    }
    arg0->unk_1A = 0x20;
block_3:
    temp_flags = ((S_func_8009E038_3 *)&D_800E296C)->unk_00;
    if (!(temp_flags & 0x800000)) {
        goto block_7;
    }
    temp_state = arg0->unk_1A;
    temp_flags_cleared = temp_flags & ~0x2000;
    (*(s32 *)&D_800E296C) = temp_flags_cleared;
    if (temp_state < 2) {
        goto block_6;
    }
    arg0->unk_1A = 0;
    arg0->unk_1C = 8;
block_6:
    reset_flags = ((S_func_8009E038_3 *)&D_800E296C)->unk_00;
    arg0->unk_2C = 0U;
    (*(s32 *)&D_800E296C) = reset_flags & 0xFEFFFFFF;
    goto block_10;
block_7:
    if ((u32) ((u16) arg0->unk_1A - 0x20) >= 0x10U) {
        goto block_10;
    }
    if (((S_func_8009E038_3 *)&D_800E296C)->unk_00 & 0x2000) {
        goto block_10;
    }
    arg0->unk_1A = 0x30;
block_10:
    if (arg0->unk_1A != 0) {
        goto block_12;
    }
    if (!(((S_func_8009E038_4 *)D_800E3D7C)->unk_1C & 0x10)) {
        goto block_13;
    }
block_12:
    reset_flags = ((S_func_8009E038_3 *)&D_800E296C)->unk_00;
    arg0->unk_2C = 0U;
    (*(s32 *)&D_800E296C) = reset_flags & 0xFEFFFFFF;
block_13:
    temp_v1 = arg0->unk_1A;
    if ((u32) temp_v1 >= 0x31U) {
        goto block_46;
    }
    (void)jt_keep; goto *D_80088CB8[(u32)(temp_v1)];
jt_c0:
    if ((*(s32 *)((u8 *)&D_800E296C + 0)) & 0x800000) {
        goto block_20;
    }
    temp_v0 = arg0->unk_2C + 1;
    arg0->unk_2C = temp_v0;
    if ((s16) temp_v0 != 0x1F) {
        goto block_18;
    }
    (*(s32 *)&D_800E296C) = (s32) (((S_func_8009E038_3 *)&D_800E296C)->unk_00 | 0x01000000);
    func_800A634C(0);
    goto block_20;
block_18:
    if ((s16) temp_v0 < 0x20) {
        goto block_20;
    }
    arg0->unk_2C = 0x20U;
block_20:
    temp_a0 = arg0->unk_1C;
    if (temp_a0 <= 0) {
        goto block_22;
    }
    temp_v1_2 = temp_s1->unk_0C.bytes.unk_0E;
    temp_v1_3 = temp_v1_2 + ((s32) (0x80 - temp_v1_2) / temp_a0);
    temp_s1->unk_0C.bytes.unk_0E = temp_v1_3;
    temp_s1->unk_0C.bytes.unk_0D = temp_v1_3;
    temp_s1->unk_0C.bytes.unk_0C = temp_v1_3;
    temp_v1_4 = temp_s1->unk_1E;
    temp_a0_2 = temp_s1->unk_20.u16;
    temp_v1_5 = temp_v1_4 + ((s32) (0x3000 - temp_v1_4) / (s16) arg0->unk_1C);
    temp_s1->unk_1E = temp_v1_5;
    temp_s1->unk_1C = temp_v1_5;
    temp_v0_2 = temp_s1->unk_22.u16;
    temp_s1->unk_20.u16 = (u16) (temp_a0_2 + ((s32) (0x20 - temp_a0_2) / (s16) arg0->unk_1C));
    temp_s1->unk_22.u16 = (u16) (temp_v0_2 + ((s32) (0x20 - temp_v0_2) / (s16) arg0->unk_1C));
    arg1->unk_02 = (s16) ((u16) arg1->unk_02 + ((s32) (0xA0 - arg1->unk_02) / (s16) arg0->unk_1C));
    arg1->unk_06 = (s16) ((u16) arg1->unk_06 + ((s32) (0x78 - arg1->unk_06) / (s16) arg0->unk_1C));
    arg0->unk_04 = (s16) ((u16) arg0->unk_04 + ((s32) (0 - arg0->unk_04) / (s16) arg0->unk_1C));
    arg0->unk_06 = (s16) ((u16) arg0->unk_06 + ((s32) (0 - arg0->unk_06) / (s16) arg0->unk_1C));
    arg0->unk_08 = (s16) ((u16) arg0->unk_08 + ((s32) (0x140 - arg0->unk_08) / (s16) arg0->unk_1C));
    arg0->unk_0A = (s16) ((u16) arg0->unk_0A + ((s32) (0xE0 - arg0->unk_0A) / (s16) arg0->unk_1C));
block_22:
    temp_v0_3 = (u16) arg0->unk_1C - 1;
    arg0->unk_1C = temp_v0_3;
    if ((temp_v0_3 << 0x10) > 0) {
        goto block_46;
    }
    arg1->unk_02 = 0xA0;
    arg1->unk_06 = 0x78;
    temp_s1->unk_1E = 0x3000U;
    temp_s1->unk_1C = 0x3000U;
    temp_s1->unk_20.u16 = 0x20U;
    temp_s1->unk_22.u16 = 0x20U;
    temp_s1->unk_0C.s32 = 0x808080;
    arg0->unk_08 = 0x140;
    arg0->unk_0A = 0xE0;
    reset_flags = ((S_func_8009E038_3 *)&D_800E296C)->unk_00;
    arg0->unk_04 = 0;
    arg0->unk_06 = 0;
    arg0->unk_1C = 0;
    if (!(reset_flags & 0x800000)) {
        goto block_25;
    }
    arg0->unk_1C = 0x1E;
    arg0->unk_1A = (s16) ((u16) arg0->unk_1A + 1);
    goto block_46;
block_25:
    if (var_s3->unk_08 & 0x100) {
        goto block_46;
    }
    arg0->unk_1C = 4;
    arg0->unk_1A = 0x10;
    goto block_46;
jt_c1:
    temp_v0_4 = (u16) arg0->unk_1C - 1;
    arg0->unk_1C = temp_v0_4;
    if ((temp_v0_4 << 0x10) > 0) {
        goto block_46;
    }
    var_a1_2 = 0xFF7FFFFF;
    shared_flags = 8;
    var_epage = (S_func_8009E038_6 *)0x800E0000;
    arg0->unk_1C = shared_flags;
    shared_flags = var_epage->unk_296C;
    arg0->unk_1A = 0x10;
    goto block_shared_flags;
jt_c16:
    temp_a0_3 = arg0->unk_1C;
    if (temp_a0_3 == 0) {
        goto block_32;
    }
    temp_v1_7 = ((s32) (arg0->unk_1E - temp_s1->unk_1E) / temp_a0_3) + temp_s1->unk_1E;
    temp_s1->unk_1E = temp_v1_7;
    temp_s1->unk_1C = temp_v1_7;
    arg1->unk_02 = (s16) ((u16) arg1->unk_02 + ((s32) (arg0->unk_14 - arg1->unk_02) / (s16) arg0->unk_1C));
    arg1->unk_06 = (s16) ((u16) arg1->unk_06 + ((s32) (arg0->unk_16 - arg1->unk_06) / (s16) arg0->unk_1C));
    var_a3 = (S_func_8009E038_7 *)&D_80082E80;
    temp_s1->unk_20.u16 = (u16) (((s32) (var_a3->unk_24 - temp_s1->unk_20.u16) / (s16) arg0->unk_1C) + temp_s1->unk_20.u16);
    temp_s1->unk_22.u16 = (u16) (((s32) (var_a3->unk_25 - temp_s1->unk_22.u16) / (s16) arg0->unk_1C) + temp_s1->unk_22.u16);
    var_a2 = (s32) (arg0->unk_0C - arg0->unk_04) / (s16) arg0->unk_1C;
    arg0->unk_04 = (s16) ((u16) arg0->unk_04 + var_a2);
    var_a1 = (s32) (arg0->unk_0E - arg0->unk_06) / (s16) arg0->unk_1C;
    arg0->unk_06 = (s16) ((u16) arg0->unk_06 + var_a1);
    arg0->unk_08 = (s16) ((u16) arg0->unk_08 + ((s32) (arg0->unk_10 - arg0->unk_08) / (s16) arg0->unk_1C));
    temp_a0_4 = (s32) (arg0->unk_12 - arg0->unk_0A) / (s16) arg0->unk_1C;
    temp_v1_10 = (u16) arg0->unk_1C - 1;
    arg0->unk_1C = temp_v1_10;
    arg0->unk_0A = (s16) ((u16) arg0->unk_0A + temp_a0_4);
    if ((temp_v1_10 << 0x10) > 0) {
        goto block_33;
    }
    arg1->unk_02 = (s16) (u16) arg0->unk_14;
    arg1->unk_06 = (s16) (u16) arg0->unk_16;
    temp_v0_5 = (u16) arg0->unk_1E;
    temp_s1->unk_1E = temp_v0_5;
    temp_s1->unk_1C = temp_v0_5;
    temp_s1->unk_20.s16 = (s16) ((S_func_8009E038_7 *)&D_80082E80)->unk_24;
    temp_s1->unk_22.s16 = (s16) ((S_func_8009E038_7 *)&D_80082E80)->unk_25;
    temp_v0_6 = (u16) arg0->unk_0C;
    var_dpage = (S_func_8009E038_8 *)0x80010000;
    arg0->unk_04 = (s16) temp_v0_6;
    var_dpage->unk_3630 = temp_v0_6;
    temp_v0_7 = (u16) arg0->unk_0E;
    arg0->unk_06 = (s16) temp_v0_7;
    var_dpage->unk_3632 = temp_v0_7;
    temp_v0_8 = (u16) arg0->unk_10;
    arg0->unk_08 = (s16) temp_v0_8;
    var_dpage->unk_3634 = temp_v0_8;
    temp_v0_9 = (u16) arg0->unk_12;
    arg0->unk_0A = (s16) temp_v0_9;
    var_dpage->unk_3636 = temp_v0_9;
    goto block_33;
block_32:
    var_v0_base = (S_func_8009E038_7 *)&D_80082E80;
    temp_s1->unk_20.s16 = (s16) var_v0_base->unk_24;
    temp_s1->unk_22.s16 = (s16) var_v0_base->unk_25;
block_33:
    if (!(var_s3->unk_08 & 0x10)) {
        goto block_39;
    }
    if (!(var_s3->unk_10 & 8)) {
        goto block_39;
    }
    temp_state_1e = arg0->unk_1E;
    if (temp_state_1e >= 0x5000) {
        goto block_37;
    }
    temp_v0_10 = (u16) arg0->unk_1E + 0x1000;
    arg0->unk_1E = temp_v0_10;
    *(s32 *)0x8001363C = (s32) temp_v0_10;
    goto block_38;
block_37:
    arg0->unk_1E = 0;
    *(s32 *)0x8001363C = 0;
block_38:
    arg0->unk_1C = 4;
block_39:
    if (!(var_s3->unk_08 & 0x100)) {
        goto block_46;
    }
    if ((func_800A2C34(0) << 0x10) != 0) {
        goto block_46;
    }
    func_800A67F4();
    var_a1_2 = 0xFEFFFFFF;
    ASM_KEEP(var_a1_2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_epage = (S_func_8009E038_6 *)0x800E0000;
    shared_flags = var_epage->unk_296C;
    arg0->unk_2C = 0U;
    arg0->unk_1A = 0;
    arg0->unk_1C = 1;
block_shared_flags:
    var_epage->unk_296C = shared_flags & var_a1_2;
    goto block_46;
jt_c32:
    temp_v0_11 = temp_s1->unk_1E;
    temp_v0_12 = temp_v0_11 - (temp_v0_11 >> 2);
    temp_s1->unk_1E = temp_v0_12;
    if ((u32) (temp_v0_12 & 0xFFFF) >= 0x100U) {
        goto block_46;
    }
    temp_s1->unk_1E = 0U;
    goto block_46;
jt_c48:
    arg0->unk_1A = 0x10;
    arg0->unk_1C = 4;
block_46:
    func_8009DF0C(arg0);
    return;
}
