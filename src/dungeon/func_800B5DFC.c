#include "common.h"
#include "m2c_compat.h"

extern s32 D_80083460[3];
extern s32 D_800814A0[3];
s32 func_800644B8();
s32 func_80064584();
s16 func_800A07D0();
M2C_UNK func_800A56E0();
M2C_UNK func_800BB2E4();
M2C_UNK func_800BC0A8();

typedef struct DungeonWork {
    u8 pad_00[0x30];
    s16 field_30[5];
    u8 pad_3A[2];
    s16 field_3C[5];
} DungeonWork;


typedef struct S_800BB55C_0_pre {
    s32 unk_00;
    u8 pad_04[0xE];
    u16 unk_12;
} S_800BB55C_0_pre;   /* the 0x14 bytes before arg0 in func_800BB55C, addressed as arg0[-1] */

typedef struct S_800BB55C_0 {
    u8 pad_00[0x4A];
    union { s16 s; u16 u; } unk_4A;   /* accessed as both */
    s16 unk_4C;
    u16 unk_4E;
    s16 unk_50;
    u8 pad_52[0x6];
    s16 unk_58;
    u8 pad_5A[0x2];
    s32 unk_5C;
    s32 (*unk_60)();
    u16 unk_64;
} S_800BB55C_0;   /* arg0 in func_800BB55C */

typedef struct S_800BB55C_1 {
    u8 pad_00[0x30];
    s16 unk_30;
    u8 pad_32[0xA];
    s16 unk_3C;
} S_800BB55C_1;   /* var_s2_angle in func_800BB55C */

typedef struct S_800BB55C_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BB55C_2;   /* arg1 in func_800BB55C */

typedef struct S_800BB55C_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_800BB55C_3;   /* temp_a0 in func_800BB55C */

typedef struct S_800BB55C_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BB55C_4;   /* global_ptr in func_800BB55C */

void func_800BB55C(void *arg0, S_800BB55C_2 *arg1, s32 arg2) {
    s32 sp20[2];
    s16 sp28[2];
    s16 sp30[2];
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    register s32 var_s2_angle ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 var_s5;
    s32 temp_a0_2;
    register s32 temp_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 saved_arg2;
    s32 var_s1;
    s32 var_s3;
    u16 temp_a3;
    u16 temp_v0_4;
    u16 temp_v1_4;
    register u16 temp_decay ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 *global_ptr;
    S_800BB55C_3 *temp_a0;
    register DungeonWork *var_s3_2 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    DungeonWork *var_s6_ptr;

    sp20[0] = 0x01000340;
    sp20[1] = 0x460044;
    temp_s0 = arg0 + 0xC;
    func_800478B8(temp_s0);
    saved_arg2 = arg2;
    ((S_800BB55C_0_pre *)arg0)[-1].unk_00 = temp_s0;
    func_800BB2E4(NULL, NULL, sp20, 0, arg0);
    var_s5 = -0x400;
    var_s3 = 0;
    var_s2_angle = (s32) arg0;
    do {
        temp_s0 = (s16)var_s5;
        sp28[0] = (func_80064584(temp_s0) >> 7) + 0x362;
        sp28[1] = (func_800644B8(temp_s0) >> 7) + 0x122;
        temp_s0 += 0x999;
        sp30[0] = (func_80064584(temp_s0) >> 7) + 0x362;
        temp_v0 = (func_800644B8(temp_s0) >> 7) + 0x122;
        sp30[1] = temp_v0;
        temp_v0_2 = func_800A07D0(sp28[0], sp28[1], sp30[0], temp_v0);
        sp30[0] = (u16) sp28[0] + ((s32) (func_80064584(temp_v0_2) * ((S_800BB55C_1 *)var_s2_angle)->unk_30) >> 0xB);
        sp30[1] = (u16) sp28[1] + ((s32) (func_800644B8(temp_v0_2) * ((S_800BB55C_1 *)var_s2_angle)->unk_30) >> 0xB);
        ((S_800BB55C_1 *)var_s2_angle)->unk_3C = var_s5;
        var_s5 += 0x999;
        func_800BB2E4(sp28, sp30, sp20, 0, NULL);
        var_s3 += 1;
        var_s2_angle += 2;
    } while (var_s3 < 5);
    var_s5 = -0x400;
    ASM_KEEP_NV(var_s5);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(arg0);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    var_s3_2 = arg0;
    temp_s0 = var_s5 << 0x10;
    do {
        temp_s0 >>= 0x10;
        sp28[0] = (func_80064584((s16) temp_s0) >> 7) + 0x362;
        sp28[1] = (func_800644B8((s16) temp_s0) >> 7) + 0x122;
        var_s2_angle = var_s5;
        var_s1 = 0;
        if (var_s3_2->field_30[0] > 0) {
            var_s6_ptr = var_s3_2;
            temp_s0 = var_s2_angle + 0x19;
            do {
                var_s2_angle = temp_s0;
                ASM_KEEP_NV(temp_s0);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                sp30[0] = (func_80064584((s16)temp_s0) >> 7) + 0x362;
                sp30[1] = (func_800644B8((s16)temp_s0) >> 7) + 0x122;
                func_800BB2E4(sp28, sp30, sp20, 0, NULL);
                sp28[0] = (u16) sp30[0];
                sp28[1] = (u16) sp30[1];
                temp_s0 = var_s2_angle + 0x19;
            } while (++var_s1 < var_s6_ptr->field_30[0]);
        }
        temp_v0_3 = (u16) var_s3_2->field_30[0] + 1;
        var_s3_2->field_30[0] = temp_v0_3;
        var_s5 += 0x333;
        if (temp_v0_3 >= 0x1F) {
            var_s3_2->field_30[0] = 0x1F;
            if (((S_800BB55C_0 *)arg0)->unk_4A.s == 0) {
                if (((S_800BB55C_0 *)arg0)->unk_60() != 0) {
                    ((S_800BB55C_0 *)arg0)->unk_50 = 0x120;
                    ((S_800BB55C_0 *)arg0)->unk_4A.s = (s16) ((u16) ((S_800BB55C_0 *)arg0)->unk_4A.s + 1);
                    func_800A56E0(0x603);
                }
            }
            ((S_800BB55C_0 *)arg0)->unk_4C = 0x20;
        }
        var_s3_2 = (DungeonWork *)((u8 *)var_s3_2 + 2);
        temp_s0 = var_s5 << 0x10;
    } while ((s32) var_s3_2 < (s32) (arg0 + 0xA));
    func_800BB2E4(NULL, NULL, sp20, 1, NULL);
    ((S_800BB55C_0_pre *)arg0)[-1].unk_00 = saved_arg2;
    if (((S_800BB55C_0 *)arg0)->unk_4A.s != 0) {
        ((S_800BB55C_0 *)arg0)->unk_4E = (u16) (((S_800BB55C_0 *)arg0)->unk_4E + 0x100);
        var_s3_2 = (DungeonWork *) 0;
        do {
            var_s3_2 = (DungeonWork *)((s32) var_s3_2 + 1);
            temp_a3 = ((S_800BB55C_0 *)arg0)->unk_4E + 0x400;
            ((S_800BB55C_0 *)arg0)->unk_4E = temp_a3;
            func_800BC0A8(arg1->unk_02, arg1->unk_06, arg1->unk_0A, (s16) temp_a3, (s32) ((S_800BB55C_0 *)arg0)->unk_50, (s32) ((S_800BB55C_0 *)arg0)->unk_58, ((S_800BB55C_0 *)arg0)->unk_5C, 6);
        } while ((s32) var_s3_2 < 4);
        if (((S_800BB55C_0 *)arg0)->unk_58 < 0x20) {
            ((S_800BB55C_0 *)arg0)->unk_58 = (s16) ((u16) ((S_800BB55C_0 *)arg0)->unk_58 + 1);
        }
        if (((S_800BB55C_0 *)arg0)->unk_4A.s == 1) {
            temp_v0_4 = ((S_800BB55C_0 *)arg0)->unk_64 + 1;
            ((S_800BB55C_0 *)arg0)->unk_64 = temp_v0_4;
            if ((s16) temp_v0_4 >= 0x21) {
                temp_v1_4 = ((S_800BB55C_0 *)arg0)->unk_4A.u + 1;
                ((S_800BB55C_0 *)arg0)->unk_64 = 0x10U;
                ((S_800BB55C_0 *)arg0)->unk_4A.u = temp_v1_4;
                return;
            }
        } else {
            temp_v1 = (u8) ((S_800BB55C_0 *)arg0)->unk_5C;
            temp_a0 = arg0 + 0x5C;
            temp_a0->unk_00 = (u8) (temp_v1 - ((s32) temp_v1 / (s16) ((S_800BB55C_0 *)arg0)->unk_64));
            temp_v1_2 = temp_a0->unk_01;
            temp_a0->unk_01 = (u8) (temp_v1_2 - ((s32) temp_v1_2 / (s16) ((S_800BB55C_0 *)arg0)->unk_64));
            temp_v1_3 = temp_a0->unk_02;
            temp_a0->unk_02 = (u8) (temp_v1_3 - ((s32) temp_v1_3 / (s16) ((S_800BB55C_0 *)arg0)->unk_64));
            temp_a0_2 = (s16) ((S_800BB55C_0 *)arg0)->unk_50 / (s16) ((S_800BB55C_0 *)arg0)->unk_64;
            temp_decay = ((S_800BB55C_0 *)arg0)->unk_64 - 1;
            ((S_800BB55C_0 *)arg0)->unk_64 = temp_decay;
            ((S_800BB55C_0 *)arg0)->unk_50 = (s16) ((u16) ((S_800BB55C_0 *)arg0)->unk_50 - temp_a0_2);
            if ((temp_decay << 0x10) <= 0) {
                global_ptr = (u8 *)D_80083460;
                ((S_800BB55C_4 *)global_ptr)->unk_0A = (u16) (((S_800BB55C_4 *)global_ptr)->unk_0A - 1);
                ((S_800BB55C_0_pre *)arg0)[-1].unk_12 = (u16) (((S_800BB55C_0_pre *)arg0)[-1].unk_12 | 0x8000);
                D_800814A0[0] = D_800814A0[0] | 0x8000;
            }
        }
    }
}
