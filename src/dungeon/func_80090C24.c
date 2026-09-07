#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"


extern void func_8003DB94();
extern void func_80040AA0(s32);
extern void func_8008CBA0();
extern void func_8008CF6C();
extern s16 func_8009074C();
extern s32 func_80094EA4(void);
extern void func_8009693C(void) __attribute__((noreturn));
extern void func_80096990() __attribute__((noreturn));
extern void func_800969B8();
extern void func_80096AC0();
extern void func_80096C24();
extern s32 func_800973F0();
extern void func_80097898();
extern void func_80097C50();
extern void *func_8009F868();
extern void func_8009F988();
extern s32 func_800A2C34();
extern void func_800A4300();
extern s32 func_800A4474();
extern void func_800A56E0();
extern s32 func_800A6D30(void);

extern u16 D_80013714[];
extern u8 D_800245A8[];
extern u8 D_8004F5F4[];
extern s32 D_80082EB0[];
extern u8 D_80083160[];
extern s16 D_80083228[];
extern u8 D_80083460[];
extern void *D_800DD274[];
extern void (*D_800DD830[])();
extern u8 D_800E3544[];
extern s32 D_800E4940[];




typedef struct S_80096384_2 {
    u8 pad_00[0x8];
    union { s32 s; u32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0xBC];
    s16 unk_C8;
} S_80096384_2;   /* temp_s5 in func_80096384 */

typedef struct S_80096384_3 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x24];
    s16 unk_8A;
} S_80096384_3;   /* arg3 in func_80096384 */

typedef struct S_80096384_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80096384_4;   /* temp_s4 in func_80096384 */

typedef struct S_80096384_5 {
    u8 unk_00;
    u8 unk_01;
} S_80096384_5;   /* temp_v0_2 in func_80096384 */

void func_80096384(void *arg0, s32 arg1, Rec_D_80082E80 *arg2, void *arg3)
{
    s16 temp_v0;
    s16 temp_v0_3;
    s32 temp_a0;
    s32 kind;
    s32 angle_target;
    s32 normalized;
    register s32 sign_tmp ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 signed_target;
    s32 current_s;
    u32 current_u;
    s32 var_v0_4;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 var_v0_3;
    u32 tail_data_flags;
    u16 temp_a1;
    u16 temp_v1_2;
    u16 temp_v1_5;
    u16 temp_v1_6;
    u8 *temp_a1_2;
    S_80096384_5 *temp_v0_2;
    u8 *temp_s5 = D_80083160;
    u8 *temp_s4;
    u16 *flags_page;   /* MATCH pin: retail register colouring depends on it */
    s32 flags;
    s32 temp_s4_value = 0x32;
    s32 temp_state;

    if (((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_u8 != temp_s4_value) {
        arg2->unk_2C.as_pv = D_800DD274;
        func_8003DB94(arg2,
            *(void **)((u8 *)D_800DD274 +
                ((((s32)(((S_80096384_2 *)temp_s5)->unk_C8 +
                    ((S_80096384_3 *)arg3)->unk_2A.s + 0x100)) >> 7) & 0x1C)),
            0);
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_u8 = temp_s4_value;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 &= 0xFEFF;
        arg2->unk_14.at00_u16.v &= 0xF7FF;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_s8 = 0;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_s16 = 0;
        func_800A4300(arg2, arg3);
    }

    temp_s4 = D_80083460;
    ((S_80096384_4 *)temp_s4)->unk_02 &= 0xFF7F;
    temp_v0 = ((S_80096384_3 *)arg3)->unk_64;
    if (temp_v0 < 0) {
        func_80097898(arg0, arg1, arg2, arg3);
        func_80096990();
    }
    if (temp_v0 > 0) {
        func_8008CBA0(arg0, arg1, arg2, arg3);
    }

    temp_v1 = ((S_80096384_3 *)arg3)->unk_14;
    if (temp_v1 & 0x20000) {
        ((S_80096384_3 *)arg3)->unk_14 = temp_v1 & 0xFFFDFFFF;
    }

    temp_v1_2 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2;
    if (!(temp_v1_2 & 0x10)) {
        func_80096AC0(arg0, arg1, arg2, arg3);
        func_80096990();
    }

    temp_a0 = ((S_80096384_3 *)arg3)->unk_1C;
    if (temp_a0 & 0x200) {
        func_80097C50(arg0, arg1, arg2, arg3);
        func_80096990();
    }

    if (!(((S_80096384_4 *)temp_s4)->unk_02 & 4)) {
        if (!(temp_a0 & 0x20)) {
            flags_page = (u16 *)0x80010000;
            flags = flags_page[0x1B8A];
            if (flags & 1) {
                ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = temp_v1_2 & 0xFFFE;
                if (temp_v1_2 & 0x200) {
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = temp_v1_2 & 0xFDFE;
                }

                temp_v0_2 = func_8009F868(flags);
                if (temp_v0_2 != 0) {
                    kind = temp_v0_2->unk_01 & 7;
                    temp_a1 = ((S_80096384_3 *)arg3)->unk_2A.u;
                    ASM_KEEP_NV(kind);   /* MATCH pin: retail basic-block layout depends on it */
                    kind &= 0xFF;
                    temp_a0 = kind << 9;
                    sign_tmp = temp_a1 & 0xFFF;
                    angle_target = temp_a0;
                    ASM_KEEP_NV(angle_target);   /* MATCH pin: retail delay-slot fill depends on it */
                    ((S_80096384_3 *)arg3)->unk_2A.u = sign_tmp;

                    if (sign_tmp != angle_target) {
                        normalized = temp_a1 & 0x800;
                        if (!normalized) {
                            normalized = temp_a1 & 0x7FF;
                        } else {
                            normalized = sign_tmp | 0xF800;
                        }
                        ((S_80096384_3 *)arg3)->unk_2A.u = normalized;

                        normalized = temp_a0 & 0x800;
                        if (!normalized) {
                            normalized = temp_a0 & 0x7FF;
                        } else {
                            normalized = temp_a0 | 0xF800;
                        }
                        temp_a0 = normalized;
                        sign_tmp = temp_a0 << 16;
                        signed_target = sign_tmp >> 16;
                        ASM_MEM_BARRIER();   /* MATCH pin: retail register colouring depends on it */
                        current_s = ((S_80096384_3 *)arg3)->unk_2A.s;
                        current_u = ((S_80096384_3 *)arg3)->unk_2A.u;
                        var_v0_3 = current_s - signed_target;
                        if (var_v0_3 < 0) {
                            var_v0_3 = 0 - var_v0_3;
                        }
                        if (var_v0_3 >= 0x801) {
                            ((S_80096384_3 *)arg3)->unk_2A.u = (u16)
                                ((temp_a0 & ~0xFFF) | (current_u & 0xFFF));
                        }
                        current_s = ((S_80096384_3 *)arg3)->unk_2A.s;
                        current_u = ((S_80096384_3 *)arg3)->unk_2A.u;
                        var_v0_4 = signed_target < current_s;
                        if (!var_v0_4) {
                            var_v0_4 = current_u + 0x200;
                        } else {
                            var_v0_4 = current_u - 0x200;
                        }
                        ((S_80096384_3 *)arg3)->unk_2A.u = var_v0_4;
                        func_8009F988(temp_a0, signed_target);
                        func_8009693C();
                    }

                    D_800E3544[0] = temp_v0_2->unk_01 & 0xF8;
                    temp_state = D_800E3544[0];
                    if (temp_state != 0x10) {
                        if (temp_state < 0x11) {
                            if (temp_state != 8) {
                                func_8009693C();
                            }
                            goto block_state_8;
                        }
                        if (temp_state != 0x18) {
                            if (temp_state != 0xD8) {
                                func_8009693C();
                            }
                            goto block_state_D8;
                        }
                        goto block_state_18;
                    }
                    goto block_state_10;
block_state_8:
                    func_80096C24(arg0, arg1, arg2, arg3);
                    func_80096990();
block_state_10:
                    func_800969B8(arg0, arg1, arg2, arg3);
                    func_80096990();
block_state_18:
                    func_800973F0(arg0, arg1, arg2, arg3);
                    func_8009693C();
block_state_D8:
                    D_800DD830[temp_v0_2->unk_00 & 0x7F]();
                    func_8009693C();
                }
            } else {
                D_800E3544[0] = 0;
                if (flags & 4) {
                    func_80040AA0(3);
                    func_80096990();
                }

                if ((func_80094EA4() << 16) != 0) {
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A4.as_s16 = 0;
                }

                if ((((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 & 0x200) &&
                    ((func_800A2C34(arg3) << 16) == 0) &&
                    !(((S_80096384_4 *)temp_s4)->unk_02 & 4) &&
                    ((func_800A4474(arg2->unk_24,
                        arg2->unk_25) << 16) != 0)) {
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 &= 0xFDFF;
                    func_8008CF6C(arg0, arg1, arg2, D_800245A8);
                    func_80096990();
                }

                if (((S_80096384_2 *)temp_s5)->unk_08.s & 0x80) {
                    ((S_80096384_3 *)arg3)->unk_8A = 2;
                    D_800E4940[0] = 2;
                    func_8008CF6C(arg0, arg1, arg2, D_8004F5F4);
                    D_80082EB0[0] = 0;
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_C8 = 0;
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_104 = 0;
                    func_80096990();
                }

                ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
                temp_a1_2 = (u8 *)arg0 + 0xA2;
                if (((S_80096384_2 *)temp_s5)->unk_08.s & 3) {
                    func_800A56E0(0x506, temp_a1_2);
                    func_80096990();
                }

                temp_v0_3 = func_8009074C(((Rec_func_8008ACDC_arg0 *)arg0)->unk_9E,
                    temp_a1_2, (u8 *)arg3 + 0x2A);
                if (temp_v0_3 != 0xFFF) {
                    ((S_80096384_3 *)arg3)->unk_2A.s = temp_v0_3;
                    if (!(((S_80096384_2 *)temp_s5)->unk_08.s & 0x10)) {
                        temp_v1_5 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2;
                        if (!(temp_v1_5 & 0x400)) {
                            ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = temp_v1_5 & 0xFFFE;
                            if (((S_80096384_3 *)arg3)->unk_1C & 0x400) {
                                ((S_80096384_3 *)arg3)->unk_2A.s =
                                    ((S_80096384_3 *)arg3)->unk_2A.u +
                                    (func_800A6D30() & 0xE00);
                            }
                            func_80096C24(arg0, arg1, arg2, arg3);
                            if (((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_u8 != 0x32) {
                                func_80096990();
                            }
                            goto block_78;
                        }
                    }
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_s16 = 0;
                }

block_78:
                tail_data_flags = ((S_80096384_2 *)temp_s5)->unk_08.u;
                if ((tail_data_flags & 0x30) == 0x30) {
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 &= 0xFFFE;
                    func_800969B8(arg0, arg1, arg2, arg3);
                    func_80096990();
                }

                temp_v1_6 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2;
                temp_v0_4 = temp_v1_6 & 0x40;
                if (temp_v0_4 != 0) {
                    temp_v0_4 = tail_data_flags & 0x40;
                    if (temp_v0_4 == 0) {
                        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = temp_v1_6 & 0xFFBF;
                        func_8009693C();
                    }
                    goto block_88;
                }
                temp_v0_4 = tail_data_flags & 0x40;
                if (temp_v0_4 == 0) {
                    goto block_87;
                }
                ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = temp_v1_6 & 0xFFFE;
                if ((func_800973F0(arg0, arg1, arg2, arg3) << 16) != 0) {
                    return;
                }
                goto block_87;
            }
        } else {
            goto block_state_10;
        }
        } else {
block_87:
        temp_v1_6 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2;
block_88:
        if (temp_v1_6 & 1) {
            ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = temp_v1_6 & 0xFFFE;
            arg2->unk_2C.as_pv = D_800DD274;
            func_8003DB94(arg2,
                *(void **)((u8 *)D_800DD274 +
                    ((((s32)(D_80083228[0] + ((S_80096384_3 *)arg3)->unk_2A.s +
                        0x100)) >> 7) & 0x1C)),
                0);
        }
    }
}
