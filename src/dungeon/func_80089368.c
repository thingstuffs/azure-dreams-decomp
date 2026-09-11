#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_8002534C(); /* extern */
M2C_UNK func_80048A44(); /* extern */
M2C_UNK func_8008C13C(); /* extern */
M2C_UNK func_8008C468(); /* extern */
M2C_UNK func_8008C7B4(); /* extern */
M2C_UNK func_8008CAA0(); /* extern */
M2C_UNK func_8008CBA0(); /* extern */
M2C_UNK func_8008CF6C(); /* extern */
s32 func_8008D024(); /* extern */
s32 func_8008D1D0();  /* extern */
M2C_UNK func_8008D94C();                            /* extern */
M2C_UNK func_8008F6EC(); /* extern */
M2C_UNK func_8008FA14(); /* extern */
M2C_UNK func_80090200(); /* extern */
s16 func_8009074C();             /* extern */
M2C_UNK func_80094270(void *, void *, void *, s32, u32); /* extern */
M2C_UNK func_80094548();                    /* extern */
M2C_UNK func_8009456C();                    /* extern */
M2C_UNK func_8009458C();                    /* extern */
M2C_UNK func_800945C4();                    /* extern */
s16 func_80095538();                /* extern */
M2C_UNK func_800956B8(); /* extern */
M2C_UNK func_80095854(); /* extern */
s32 func_80098920();   /* extern */
void *func_8009F868();                        /* extern */
M2C_UNK func_8009F988();                    /* extern */
M2C_UNK func_8009FAAC();                            /* extern */
void *func_8009FADC();                      /* extern */
s32 func_800A1C58();                  /* extern */
M2C_UNK func_800A2B04();              /* extern */
s32 func_800A2C34();                          /* extern */
M2C_UNK func_800A4300();              /* extern */
s32 func_800A4474();                          /* extern */
s32 func_800A6D30();                          /* extern */
extern u16 D_80013714;
extern u16 D_80013714_second __asm__("D_80013714");
extern M2C_UNK D_800245A8;
extern M2C_UNK D_8004F5F4;
extern M2C_UNK D_80050CAC;
extern s32 D_80082EB0;
extern s8 D_80083160[];
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8008ACDC;
extern M2C_UNK D_800DCFB0;
extern u8 D_800DD0B8[];
extern M2C_UNK (*D_800DD830[])(s32, u16);
extern M2C_UNK D_800E3544;
extern s32 D_800E4940;



typedef struct S_8008EAC8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x24];
    s16 unk_8A;
} S_8008EAC8_1;   /* arg3 in func_8008EAC8 */



typedef struct S_8008EAC8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8008EAC8_4;   /* held_D_80083460 in func_8008EAC8 */

typedef struct S_8008EAC8_5 {
    u8 pad_00[0x8];
    u32 unk_08;
} S_8008EAC8_5;   /* held_D_80083160 in func_8008EAC8 */

typedef struct S_8008EAC8_6 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_8008EAC8_6;   /* temp_v0 in func_8008EAC8 */

typedef struct S_8008EAC8_7 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8008EAC8_7;   /* ((((u32) temp_v0) * 4) + arg0) in func_8008EAC8 */

typedef struct S_8008EAC8_8 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_8008EAC8_8;   /* ((temp_v1_7 * 4) + arg0) in func_8008EAC8 */

typedef struct S_8008EAC8_9 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_8008EAC8_9;   /* temp_v0_2 in func_8008EAC8 */

typedef struct S_8008EAC8_10 {
    s8 unk_00;
} S_8008EAC8_10;   /* &D_800E3544 in func_8008EAC8 */

void func_8008EAC8(void *arg0, void *arg1, void *arg2, void *arg3) {
    s8 *held_D_80083160 = D_80083160;
    u8 *held_D_80083460;
    s16 temp_v0_3;
    s16 temp_v1;
    s16 var_v0_2;
    s32 temp_a0;
    s32 temp_code;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0_3;
    u16 temp_a1;
    u16 temp_v1_4;
    s32 temp_v1_5;
    u16 temp_v1_6;
    u16 temp_v1_8;
    u16 var_v0;
    u16 var_v0_4;
    u32 temp_v1_7; /* MATCH: both arms merge the fifth argument in v1. */
    u8 temp_a0_2;
    u8 temp_a1_2;
    u8 temp_a1_3;
    u8 temp_a1_4;
    u8 temp_a1_5;
    s32 temp_angle;
    void *code8_a0;
    void *call0; /* MATCH: both arms prepare a0 before the shared call. */
    void *call1; /* MATCH: both arms prepare a1 before the shared call. */
    void *call2; /* MATCH: both arms prepare a2 before the shared call. */
    register s32 temp_v0_4 ASM_REG("$7"); /* MATCH: merge the fourth argument in a3. */
    s32 tail_data_flags;
    void *call_arg;
    register u8 *data ASM_REG("$5"); /* MATCH: shared tail receives its data pointer in a1. */
    void *temp_v0;
    void *temp_v0_2;

    if (((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_u8 != 0xE) {
        if (((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 & 0x100) {
            func_8008D94C(arg0, arg1, arg2, arg3);
            return;
        }
        goto block_5;
    }
block_5:
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_u8 = 0xEU;
    if (!(((S_8008EAC8_1 *)arg3)->unk_14 & 0x100000)) {
        func_800A4300(arg2, arg3);
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    }
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xF7FF);
    held_D_80083460 = (u8 *) &D_80083460;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_s8 = 0;
    ((S_8008EAC8_4 *)held_D_80083460)->unk_02 = (u16) (((S_8008EAC8_4 *)held_D_80083460)->unk_02 & 0xFF7F);
    temp_v1 = ((S_8008EAC8_1 *)arg3)->unk_64;
    if ((temp_v1 < 0) || (((Rec_func_8008ACDC_arg0 *)arg0)->unk_10C & 1)) {
        func_8008CAA0(arg0, arg1, arg2, arg3);
        return;
    }
    if (temp_v1 > 0) {
        func_8008CBA0(arg0, arg1, arg2, arg3);
    }
    temp_v1_2 = ((S_8008EAC8_1 *)arg3)->unk_14;
    if (temp_v1_2 & 0x20000) {
        ((S_8008EAC8_1 *)arg3)->unk_14 = (s32) (temp_v1_2 & 0xFFFDFFFF);
    }
    if (!(((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 & 0x10)) {
        func_8008C468(arg0, arg1, arg2, arg3);
        return;
    }
    temp_v1_3 = ((S_8008EAC8_1 *)arg3)->unk_1C;
    if (temp_v1_3 & 0x200) {
        func_80090200(arg0, arg1, arg2, arg3);
        return;
    }
    if (!(temp_v1_3 & 0x100000)) {
        call_arg = arg2;
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        {
            void *callback = &D_8008ACDC;
            {
                do {
                    data = (u8 *) &D_800DCFB0;
                } while (0);
                   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8C.as_pv = callback;
                goto block_154;
            }
        }
        return;
    }
    if ((((Rec_func_8008ACDC_arg0 *)arg0)->unk_124 != 0) && (((func_800A1C58(arg3) << 0x10) == 0) || (func_8008D1D0(arg0, arg1, arg2, arg3) == 0))) {
        if (!(((S_8008EAC8_4 *)held_D_80083460)->unk_02 & 4)) {
            if (((S_8008EAC8_1 *)arg3)->unk_1C & 0x20) {
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                if (!(D_80013714 & 1) && (((S_8008EAC8_5 *)held_D_80083160)->unk_08 & 0x80)) {
                    ((S_8008EAC8_1 *)arg3)->unk_8A = 2;
                    D_800E4940 = 2;
                    func_8008CF6C(arg0, arg1, arg2, &D_8004F5F4);
                    D_80082EB0 = 0;
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_C8 = 0;
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_104 = 0;
                    return;
                }
                goto code_10;
            }
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            if (D_80013714_second & 1) {
                temp_v1_4 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2;
                ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = (u16) (temp_v1_4 & 0xFFFE);
                if (temp_v1_4 & 0x200) {
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = (u16) (temp_v1_4 & 0xFDFE);
                }
                temp_v0 = func_8009F868();
                if (temp_v0 != NULL) {
                    temp_angle = ((S_8008EAC8_6 *)temp_v0)->unk_01 & 7;
                    temp_a1 = ((S_8008EAC8_1 *)arg3)->unk_2A.u;
                    ASM_KEEP(temp_angle);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                    temp_angle = (u8) temp_angle;
                    temp_a0 = temp_angle << 9;
                    temp_v1_5 = temp_a1 & 0xFFF;
                    temp_angle = temp_a0;
                    ASM_KEEP(temp_angle);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                    ((S_8008EAC8_1 *)arg3)->unk_2A.u = temp_v1_5;
                    if (temp_v1_5 != temp_angle) {
                        s32 signed_target;
                        s32 diff;
                        {
                            s32 normalized;
                            if (temp_a1 & 0x800) {
                                normalized = temp_v1_5 | 0xF800;
                            } else {
                                normalized = temp_a1 & 0x7FF;
                            }
                            ((S_8008EAC8_1 *)arg3)->unk_2A.u = normalized;
                        }
                        {
                            register s32 normalized_target ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
                            if (temp_a0 & 0x800) {
                                normalized_target = temp_a0 | 0xF800;
                            } else {
                                normalized_target = temp_a0 & 0x7FF;
                            }
                            temp_a0 = normalized_target;
                        }
                        temp_v1_5 = (u32) temp_a0 << 16;
                        signed_target = temp_v1_5 >> 16;
                        diff = ((S_8008EAC8_1 *)arg3)->unk_2A.s;
                        temp_v1_5 = ((S_8008EAC8_1 *)arg3)->unk_2A.u;
                        diff -= signed_target;
                        if (diff < 0) {
                            diff = 0 - diff;
                        }
                        if (diff >= 0x801) {
                            ((S_8008EAC8_1 *)arg3)->unk_2A.u = (u16) ((temp_a0 & ~0xFFF) | (temp_v1_5 & 0xFFF));
                        }
                        {
                            s32 step;
                            step = ((S_8008EAC8_1 *)arg3)->unk_2A.s;
                            temp_v1_5 = ((S_8008EAC8_1 *)arg3)->unk_2A.u;
                            step = signed_target < step;
                            if (step) {
                                step = temp_v1_5 - 0x200;
                            } else {
                                step = temp_v1_5 + 0x200;
                            }
                            ((S_8008EAC8_1 *)arg3)->unk_2A.u = step;
                        }
                        func_8009F988(temp_a0);
                        goto block_153;
                    }
                    *(volatile s8 *) &D_800E3544 = (s8) (((S_8008EAC8_6 *)temp_v0)->unk_01 & 0xF8);
                    temp_code = *(u8 *) &D_800E3544;
                    if (temp_code == 0x70) goto code_70;
                    if (temp_code >= 0x71) goto code_high;
                    if (temp_code == 0x30) goto code_30;
                    if (temp_code >= 0x31) goto code_mid;
                    if (temp_code == 0x10) goto code_10;
                    if (temp_code >= 0x11) goto code_low_mid;
                    code8_a0 = arg0;
                    if (temp_code == 8) goto code_8;
                    return;
code_low_mid:
                    if (temp_code == 0x28) goto code_28;
                    return;
code_mid:
                    if (temp_code == 0x50) goto code_50;
                    if (temp_code >= 0x51) goto code_mid_high;
                    if (temp_code == 0x48) goto code_48;
                    return;
code_mid_high:
                    if (temp_code == 0x68) goto code_68;
                    return;
code_high:
                    if (temp_code == 0x90) goto code_90;
                    if (temp_code >= 0x91) goto code_top;
                    if (temp_code == 0x80) goto code_80;
                    if (temp_code >= 0x81) goto code_high_mid;
                    if (temp_code == 0x78) goto code_78;
                    return;
code_high_mid:
                    if (temp_code == 0x88) goto code_88;
                    return;
code_top:
                    if (temp_code == 0xA0) goto code_A0;
                    if (temp_code >= 0xA1) goto code_top_high;
                    if (temp_code == 0x98) goto code_98;
                    return;
code_top_high:
                    if (temp_code == 0xD8) goto code_D8;
                    return;
code_10:
                    func_8008C7B4(arg0, arg1, arg2, arg3);
                    return;
                       /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                    return;
code_48:
                    if (func_80095538(arg0, ((S_8008EAC8_6 *)temp_v0)->unk_00 & 0x1F, ((S_8008EAC8_6 *)temp_v0)->unk_02 & 0x1F) >= 0) {
                        func_8009FAAC();
                        return;
                    }
                    func_8009F988();
                    return;
code_50:
                    temp_a0_2 = ((S_8008EAC8_6 *)temp_v0)->unk_00;
                    temp_v0 = (void *) ((u32) (temp_a0_2 & 0x60) >> 5);
                    temp_v0_2 = func_8009FADC(temp_a0_2 & 0x1F, temp_a1);
                    if (func_80098920(((S_8008EAC8_7 *)(((((u32) temp_v0) * 4) + arg0)))->unk_AC, temp_v0_2, 0x15, 0) < 0) {
                        func_8009F988();
                        return;
                    }
                    return;
code_68:
                    temp_v0_2 = func_8009FADC(((S_8008EAC8_6 *)temp_v0)->unk_00 & 0x1F, temp_a1);
                    {
                        void *call3 = temp_v0_2; /* MATCH: retain the returned pointer in v0 until argument setup. */
                        call0 = arg0;
                        call1 = arg1;
                        call2 = arg2;
                         /* MATCH: prepare argument registers before loading the mode. */
                        temp_v1_7 = (u32) (((S_8008EAC8_6 *)temp_v0)->unk_00 & 0x60) >> 5;
                        temp_v0_4 = (s32) call3;
                        goto block_94270;
                    }
code_88:
                    call0 = arg0;
                    temp_v1_7 = ((S_8008EAC8_6 *)temp_v0)->unk_00;
                     /* MATCH: load the mode before preparing a1. */
                    call1 = arg1;
                    temp_v1_7 &= 0x60;
                    temp_v1_7 >>= 5;
                    temp_v0_4 = ((S_8008EAC8_8 *)(((temp_v1_7 * 4) + call0)))->unk_D0;
                    ASM_SCHED_BARRIER(); /* MATCH: prepare a2 after loading the fourth argument. */
                    call2 = arg2;
block_94270:
                    func_80094270(call0, call1, call2, temp_v0_4, temp_v1_7);
                    return;
code_70:
                    temp_a1_5 = ((S_8008EAC8_6 *)temp_v0)->unk_00;
                    func_80094548((u32) (temp_a1_5 & 0x60) >> 5, temp_a1_5 & 7);
                    return;
code_78:
                    temp_a1_2 = ((S_8008EAC8_6 *)temp_v0)->unk_00;
                    func_8009458C((u32) (temp_a1_2 & 0x60) >> 5, temp_a1_2 & 0x1F);
                    return;
code_80:
                    temp_a1_3 = ((S_8008EAC8_6 *)temp_v0)->unk_00;
                    func_800945C4((u32) (temp_a1_3 & 0x60) >> 5, temp_a1_3 & 0x1F);
                    return;
code_90:
                    temp_a1_4 = ((S_8008EAC8_6 *)temp_v0)->unk_00;
                    func_8009456C((u32) (temp_a1_4 & 0x60) >> 5, temp_a1_4 & 7);
                    return;
code_98:
                    temp_v0_2 = func_8009FADC(((S_8008EAC8_6 *)temp_v0)->unk_00 & 0x1F, temp_a1);
                    if (((S_8008EAC8_9 *)temp_v0_2)->unk_03 & 0x20) {
                        func_800956B8(arg0, arg1, arg2, temp_v0_2);
                        return;
                    }
                    func_80095854(arg0, arg1, arg2, temp_v0_2);
                    return;
code_A0:
                    func_8002534C(arg0, arg1, arg2, arg3);
                    return;
code_D8:
                    D_800DD830[((S_8008EAC8_6 *)temp_v0)->unk_00 & 0x7F](temp_a0, temp_a1);
                    return;
                }
            } else {
                s32 flag_200;

                flag_200 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 & 0x200;
                ((S_8008EAC8_10 *)(&D_800E3544))->unk_00 = 0;
                if (flag_200 && ((func_800A2C34(arg3) << 0x10) == 0) && !(((S_8008EAC8_4 *)held_D_80083460)->unk_02 & 4)) {
                    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = (u16) (((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 & 0xFDFF);
                    if ((func_800A4474(((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25) << 0x10) != 0) {
                        func_8008CF6C(arg0, arg1, arg2, &D_800245A8);
                        return;
                           /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                        return;
                    }
                }
                if (((S_8008EAC8_5 *)held_D_80083160)->unk_08 & 0x80) {
                    func_8008CF6C(arg0, arg1, arg2, &D_80050CAC);
                    return;
                }
                if ((((S_8008EAC8_5 *)held_D_80083160)->unk_08 & 0x10) || !(((S_8008EAC8_5 *)held_D_80083160)->unk_08 & 3) || (func_8008D024(arg0, arg1, arg2, (((u32) ((S_8008EAC8_5 *)held_D_80083160)->unk_08 >> 1) ^ 1) & 1, 0) == 0)) {
                    temp_v0_3 = func_8009074C(((Rec_func_8008ACDC_arg0 *)arg0)->unk_9E, arg0 + 0xA2, arg3 + 0x2A);
                    if (temp_v0_3 != 0xFFF) {
                        ((S_8008EAC8_1 *)arg3)->unk_2A.u = (u16) temp_v0_3;
                        if (!(((S_8008EAC8_5 *)held_D_80083160)->unk_08 & 0x10)) {
                            temp_v1_8 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2;
                            if (!(temp_v1_8 & 0x400)) {
                                ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = (u16) (temp_v1_8 & 0xFFFE);
                                code8_a0 = arg0;
                                if (((S_8008EAC8_1 *)arg3)->unk_1C & 0x400) {
                                    ((S_8008EAC8_1 *)arg3)->unk_2A.u = (u16) (((S_8008EAC8_1 *)arg3)->unk_2A.u + (func_800A6D30(code8_a0) & 0xE00));
                                    do {
                                        code8_a0 = arg0;
                                    } while (0);
                                }
code_8:
                                func_8008C13C(code8_a0, arg1, arg2, arg3);
                                return;
                            }
                        }
                    }
                    tail_data_flags = ((S_8008EAC8_5 *)held_D_80083160)->unk_08;
                    if ((tail_data_flags & 0x30) == 0x30) {
                        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = (u16) (((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 & 0xFFFE);
                        func_8008C7B4(arg0, arg1, arg2, arg3);
                        return;
                    }
                    {
                        s32 flag40;   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */

                        temp_v1_6 = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2;
                        flag40 = temp_v1_6 & 0x40;
                        if (flag40) {
                            flag40 = tail_data_flags & 0x40;
                            if (flag40 == 0) {
                                void *tail_a0 = arg2;
                                void *tail_a1 = arg1;

                                   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                                ASM_SET(tail_a1);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                                ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = (u16) (temp_v1_6 & 0xFFBF);
                                goto block_153;
                            }
                            goto block_153;
                        }
                        flag40 = tail_data_flags & 0x40;
                        ASM_KEEP_NV(flag40);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        temp_v0_4 = flag40;
                    }
                    if (temp_v0_4 != 0) {
                        if (!(tail_data_flags & 0x20)) {
code_28:
                            func_8008F6EC(arg0, arg1, arg2, arg3);
                            return;
                        }
code_30:
                        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_s16 = 6;
                        func_8008FA14(arg0, arg1, arg2, arg3);
                        return;
                    }
                    goto block_153;
                }
            }
        } else {
block_153:
            call_arg = arg2;
            data = D_800DD0B8;
block_154:
            (*(u8 **)((u8 *)call_arg + (0x2C))) = data;
            func_80048A44(call_arg, *((u8 *) (((s32) (D_80083228 + (s16) ((S_8008EAC8_1 *)arg3)->unk_2A.u + 0x100) >> 9) & 7) + (u32) data), 0, 1);
        }
    }
}
