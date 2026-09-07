/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8008ACDC_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
    u16 unk_A4;
    u8 pad_A6[0x22];
    s32 unk_C8;
    u8 pad_CC[0x38];
    s32 unk_104;
    u8 pad_108[0x4];
    u16 unk_10C;
} S_8008ACDC_0;   /* arg0 in func_8008ACDC */

typedef struct S_8008ACDC_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8008ACDC_1;   /* arg2 in func_8008ACDC */

typedef struct S_8008ACDC_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_8008ACDC_2;   /* arg1 in func_8008ACDC */

typedef struct S_8008ACDC_3 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8008ACDC_3;   /* status in func_8008ACDC */

typedef struct S_8008ACDC_4 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x24];
    s16 unk_8A;
} S_8008ACDC_4;   /* arg3 in func_8008ACDC */

typedef struct S_8008ACDC_5 {
    u8 pad_00[0x8];
    u32 unk_08;
} S_8008ACDC_5;   /* data in func_8008ACDC */

typedef struct S_8008ACDC_6 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_8008ACDC_6;   /* temp_v0 in func_8008ACDC */

typedef struct S_8008ACDC_7 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8008ACDC_7;   /* (void *) case50_bits in func_8008ACDC */

typedef struct S_8008ACDC_8 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_8008ACDC_8;   /* (void *) case88_index in func_8008ACDC */

typedef struct S_8008ACDC_9 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_8008ACDC_9;   /* temp_v0_2 in func_8008ACDC */


M2C_UNK func_8002534C(); /* extern */
void func_80040AA0();                     /* extern */
void func_80048A44(); /* extern */
M2C_UNK func_8008B330(); /* extern */
M2C_UNK func_8008B730();                 /* extern */
M2C_UNK func_8008B7A0();                            /* extern */
M2C_UNK func_8008B7F8();                            /* extern */
M2C_UNK func_8008B848();                 /* extern */
M2C_UNK func_8008B9FC(); /* extern */
M2C_UNK func_8008C468(); /* extern */
M2C_UNK func_8008C514(); /* extern */
s32 func_8008C5C4();  /* extern */
M2C_UNK func_8008C7B4(); /* extern */
s32 func_8008C8BC();  /* extern */
M2C_UNK func_8008CAA0(); /* extern */
M2C_UNK func_8008CBA0(); /* extern */
M2C_UNK func_8008CCB0(); /* extern */
M2C_UNK func_8008CF6C(); /* extern */
s32 func_8008D024(); /* extern */
s32 func_8008D1D0();  /* extern */
M2C_UNK func_8008D368(); /* extern */
M2C_UNK func_8008D7D0(); /* extern */
M2C_UNK func_8008D94C();                      /* extern */
M2C_UNK func_80090200(); /* extern */
s16 func_8009074C();             /* extern */
M2C_UNK func_80091B5C(); /* extern */
M2C_UNK func_80094270(); /* extern */
M2C_UNK func_80094548();                    /* extern */
M2C_UNK func_8009456C();                    /* extern */
M2C_UNK func_8009458C();                    /* extern */
M2C_UNK func_800945C4();                    /* extern */
s32 func_80094EA4();                             /* extern */
s32 func_80095538();                /* extern */
M2C_UNK func_800956B8(); /* extern */
M2C_UNK func_80095854(); /* extern */
s32 func_80098920();   /* extern */
M2C_UNK func_80098CF8(); /* extern */
void *func_8009F868();                           /* extern */
M2C_UNK func_8009F988();                    /* extern */
M2C_UNK func_8009FAAC();                            /* extern */
void *func_8009FADC();                      /* extern */
s32 func_800A1C58();                  /* extern */
M2C_UNK func_800A2B04();              /* extern */
s32 func_800A2C34();                          /* extern */
M2C_UNK func_800A4300();              /* extern */
s32 func_800A4474();                          /* extern */
s32 func_800A6D30(void);                      /* extern */
extern u16 D_80013714;
extern M2C_UNK D_800245A8;
extern M2C_UNK D_8004F5F4;
extern M2C_UNK D_80050CAC;
extern s32 D_80082EB0;
extern u8 D_80083160[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u8 D_800DCFB0[8];
extern u8 D_800DD058[];
extern M2C_UNK D_800DD148;
extern void (*D_800DD830[])(void);
extern u8 D_800E3544;
extern s8 D_800E3CD0[9];
extern s32 D_800E4940;

void func_8008ACDC(void *arg0, void *arg1_raw, void *arg2_raw, void *arg3_raw) {
    s16 temp_v0_3;
    s16 temp_v1_2;
    s16 var_v0_2;
    s32 temp_a0;
    s32 kind;
    s32 angle_target;
    s32 normalized;
    register s32 sign_tmp ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 signed_target;
    s32 current_s;
    u32 current_u;
    s32 temp_v0_4;
    s32 var_v0_3;
    u16 temp_a1;
    u16 temp_v0_5;
    u16 temp_v1_3;
    u16 temp_v1_5;
    u16 temp_v1_7;
    u16 temp_v1_8;
    u16 temp_v1_9;
    u16 var_v0;
    s32 var_v0_4;
    u16 *flags_page;
    s32 flags;
    register u32 temp_v1_6 ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 case88_index;
    register void *case88_value ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
    void *case68_value;
    u8 temp_a0_2;
    u8 temp_a1_2;
    u8 temp_a1_3;
    u8 temp_a1_4;
    u8 temp_a1_5;
    u8 temp_v1;
    void *temp_v0;
    void *temp_v0_2;
    void *arg1;
    register void *arg2 ASM_REG("$20");   /* MATCH pin: retail keeps a computation the compiler would drop */
    void *arg3;
    void *case_arg0;
    void *case_call_a0;
    void *case_call_a1;
    void *case_call_a2;
    u32 tail_data_flags;
    u8 *data;
    u8 *status;

    arg1 = arg1_raw;
    arg2 = arg2_raw;
    arg3 = arg3_raw;
    data = D_80083160;
    temp_v1 = ((S_8008ACDC_0 *)arg0)->unk_9A;
    if (temp_v1 != 0xE) {
        if (temp_v1 != 0x17) {
            if (((S_8008ACDC_0 *)arg0)->unk_A2 & 0x100) {
                func_8008D94C(arg0);
                goto epilogue;
            }
            ((S_8008ACDC_0 *)arg0)->unk_9A = 0xEU;
            ((S_8008ACDC_0 *)arg0)->unk_A2 = (u16) (((S_8008ACDC_0 *)arg0)->unk_A2 & 0xFEFF);
            ((S_8008ACDC_1 *)arg2)->unk_14 = (u16) (((S_8008ACDC_1 *)arg2)->unk_14 & 0xF7FF);
            ((S_8008ACDC_0 *)arg0)->unk_9B = 0;
            ((S_8008ACDC_0 *)arg0)->unk_A4 = 0U;
            ((S_8008ACDC_2 *)arg1)->unk_10 = 0;
            ((S_8008ACDC_2 *)arg1)->unk_0C = 0;
            func_800A2B04(arg1, ((S_8008ACDC_1 *)arg2)->unk_24, ((S_8008ACDC_1 *)arg2)->unk_25);
            goto block_6;
        }
block_6:
        ((S_8008ACDC_0 *)arg0)->unk_96 = 0;
        func_800A4300(arg2, arg3);
        goto block_7;
    }
block_7:
    status = D_80083460;
    ((S_8008ACDC_3 *)status)->unk_02 = (u16) (((S_8008ACDC_3 *)status)->unk_02 & 0xFF7F);
    temp_v1_2 = ((S_8008ACDC_4 *)arg3)->unk_64;
    if ((temp_v1_2 < 0) || (((S_8008ACDC_0 *)arg0)->unk_10C & 1)) {
        func_8008CAA0(arg0, arg1, arg2, arg3);
        goto epilogue;
    }
    if (temp_v1_2 > 0) {
        func_8008CBA0(arg0, arg1, arg2, arg3);
    }
    if (((S_8008ACDC_4 *)arg3)->unk_14 & 0x20000) {
        func_80091B5C(arg0, arg1, arg2, arg3);
        goto epilogue;
    }
    if (!(((S_8008ACDC_0 *)arg0)->unk_A2 & 0x10)) {
        func_8008C468(arg0, arg1, arg2, arg3);
        goto epilogue;
    }
    if (((S_8008ACDC_4 *)arg3)->unk_1C & 0x200) {
        func_80090200(arg0, arg1, arg2, arg3);
        goto epilogue;
    }
    if (((func_800A1C58(arg3) << 0x10) == 0) || (func_8008D1D0(arg0, arg1, arg2, arg3) == 0)) {
        temp_v1_3 = ((S_8008ACDC_0 *)arg0)->unk_A2;
        if (temp_v1_3 & 0x80) {
            func_8008D7D0(arg0, arg1, arg2, arg3);
            goto epilogue;
        }
        if (!(((S_8008ACDC_3 *)status)->unk_02 & 4)) {
            if (((S_8008ACDC_4 *)arg3)->unk_1C & 0x20) {
                ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
                if (!(D_80013714 & 1) && (((S_8008ACDC_5 *)data)->unk_08 & 0x80)) {
                    ((S_8008ACDC_4 *)arg3)->unk_8A = 2;
                    D_800E4940 = 2;
                    func_8008CF6C(arg0, arg1, arg2, &D_8004F5F4);
                    D_80082EB0 = 0;
                    ((S_8008ACDC_0 *)arg0)->unk_C8 = 0;
                    ((S_8008ACDC_0 *)arg0)->unk_104 = 0;
                    goto epilogue;
                }
                goto call_C7B4;
            }
            flags_page = (u16 *) 0x80010000;
            flags = flags_page[0x1B8A];
            if (flags & 1) {
                ((S_8008ACDC_0 *)arg0)->unk_A2 = (u16) (temp_v1_3 & 0xFFFE);
                if (temp_v1_3 & 0x200) {
                    ((S_8008ACDC_0 *)arg0)->unk_A2 = (u16) (temp_v1_3 & 0xFDFE);
                }
                temp_v0 = func_8009F868(flags);
                if (temp_v0 != NULL) {
                    kind = ((S_8008ACDC_6 *)temp_v0)->unk_01 & 7;
                    temp_a1 = ((S_8008ACDC_4 *)arg3)->unk_2A.s;
                    ASM_KEEP_NV(kind);   /* MATCH pin: retail basic-block layout depends on it */
                    kind &= 0xFF;
                    temp_a0 = kind << 9;
                    sign_tmp = temp_a1 & 0xFFF;
                    angle_target = temp_a0;
                    ASM_KEEP_NV(angle_target);   /* MATCH pin: retail delay-slot fill depends on it */
                    ((S_8008ACDC_4 *)arg3)->unk_2A.s = sign_tmp;
                    if (sign_tmp != angle_target) {
                        normalized = temp_a1 & 0x800;
                        if (!normalized) {
                            normalized = temp_a1 & 0x7FF;
                        } else {
                            normalized = sign_tmp | 0xF800;
                        }
                        ((S_8008ACDC_4 *)arg3)->unk_2A.s = normalized;
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
                        current_s = ((S_8008ACDC_4 *)arg3)->unk_2A.u;
                        current_u = ((S_8008ACDC_4 *)arg3)->unk_2A.s;
                        var_v0_3 = current_s - signed_target;
                        if (var_v0_3 < 0) {
                            var_v0_3 = 0 - var_v0_3;
                        }
                        if (var_v0_3 >= 0x801) {
                            ((S_8008ACDC_4 *)arg3)->unk_2A.s = (u16) ((temp_a0 & ~0xFFF) | (current_u & 0xFFF));
                        }
                        current_s = ((S_8008ACDC_4 *)arg3)->unk_2A.u;
                        current_u = ((S_8008ACDC_4 *)arg3)->unk_2A.s;
                        var_v0_4 = signed_target < current_s;
                        if (!var_v0_4) {
                            var_v0_4 = current_u + 0x200;
                        } else {
                            var_v0_4 = current_u - 0x200;
                        }
                        ((S_8008ACDC_4 *)arg3)->unk_2A.s = var_v0_4;
                        func_8009F988(temp_a0, signed_target);
                        func_8008B7A0();
                        return;
                    }
                    D_800E3544 = (u8) (((S_8008ACDC_6 *)temp_v0)->unk_01 & 0xF8);
                    switch (D_800E3544) {
                    default:
                        goto epilogue;
                    case 0x08:
                    case 0xE0:
                    case 0xE8:
                    case 0xF0:
                    case 0xF8:
                        case_arg0 = arg0;
                        func_8008B9FC(case_arg0, arg1, arg2, arg3);
                        goto epilogue;
                    case 0x10:
call_C7B4:
                        func_8008C7B4(arg0, arg1, arg2, arg3);
                        goto epilogue;
                    case 0x18:
                        func_8008C8BC(arg0, arg1, arg2, arg3);
                        goto epilogue;
                    case 0x20:
                        func_8008C5C4(arg0, arg1, arg2, arg3);
                        goto epilogue;
                    case 0x30:
                        func_8008C514(arg0, arg1, arg2, arg3);
                        goto epilogue;
                    case 0x48:
                        if ((s16) func_80095538(arg0, ((S_8008ACDC_6 *)temp_v0)->unk_00 & 0x1F, ((S_8008ACDC_6 *)temp_v0)->unk_02 & 0x1F) < 0) {
                            goto call_F988;
                        }
                        func_8009FAAC();
                        goto epilogue;
                    case 0x50: {
                        u8 case50_byte;
                        s32 case50_bits;
                        s32 case50_kind;
                        register void *case50_value ASM_REG("$5");   /* MATCH pin: retail keeps a computation the compiler would drop */

                        case50_byte = ((S_8008ACDC_6 *)temp_v0)->unk_00;
                        case50_bits = case50_byte & 0x60;
                        temp_v0 = (void *) ((u32) case50_bits >> 5);
                        case50_value = func_8009FADC(case50_byte & 0x1F, temp_a1);
                        case50_kind = 0x15;
                        ASM_KEEP_NV(case50_kind);   /* MATCH pin: retail schedule: same instructions, different order without it */
                        case50_bits = (s32) temp_v0 << 2;
                        case50_bits = case50_bits + (s32) arg0;
                        if (func_80098920(((S_8008ACDC_7 *)((void *) case50_bits))->unk_AC, case50_value, case50_kind, 0) >= 0) {
                            goto epilogue;
                        }
                    }
call_F988:
                        func_8009F988();
                        goto epilogue;
                    case 0x58:
                        func_80098CF8(arg0, arg1, arg2, func_8009FADC(((S_8008ACDC_6 *)temp_v0)->unk_00 & 0x1F, temp_a1));
                        goto epilogue;
                    case 0x68:
                        case68_value = func_8009FADC(((S_8008ACDC_6 *)temp_v0)->unk_00 & 0x1F, temp_a1);
                        case_call_a0 = arg0;
                        case_call_a1 = arg1;
                        case_call_a2 = arg2;
                        temp_v1_6 = ((S_8008ACDC_6 *)temp_v0)->unk_00;
                        case88_value = case68_value;
                        temp_v1_6 &= 0x60;
                        temp_v1_6 >>= 5;
                        goto call_94270;
                    case 0x88:
                        case_call_a0 = arg0;
                        temp_v1_6 = (u32) (((S_8008ACDC_6 *)temp_v0)->unk_00 & 0x60) >> 5;
                        case_call_a1 = arg1;
                        case88_index = temp_v1_6 << 2;
                        case88_index = case88_index + (s32) case_call_a0;
                        case88_value = (void *) ((S_8008ACDC_8 *)((void *) case88_index))->unk_D0;
                        ASM_KEEP(case88_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
                        case_call_a2 = arg2;
call_94270:
                        func_80094270(case_call_a0, case_call_a1, case_call_a2, case88_value, temp_v1_6);
                        goto epilogue;
                    case 0x70:
                        temp_a1_2 = ((S_8008ACDC_6 *)temp_v0)->unk_00;
                        func_80094548((u32) (temp_a1_2 & 0x60) >> 5, temp_a1_2 & 7);
                        goto epilogue;
                    case 0x78:
                        temp_a1_5 = ((S_8008ACDC_6 *)temp_v0)->unk_00;
                        func_8009458C((u32) (temp_a1_5 & 0x60) >> 5, temp_a1_5 & 0x1F);
                        goto epilogue;
                    case 0x80:
                        temp_a1_3 = ((S_8008ACDC_6 *)temp_v0)->unk_00;
                        func_800945C4((u32) (temp_a1_3 & 0x60) >> 5, temp_a1_3 & 0x1F);
                        goto epilogue;
                    case 0x90:
                        temp_a1_4 = ((S_8008ACDC_6 *)temp_v0)->unk_00;
                        func_8009456C((u32) (temp_a1_4 & 0x60) >> 5, temp_a1_4 & 7);
                        goto epilogue;
                    case 0x98:
                        temp_v0_2 = func_8009FADC(((S_8008ACDC_6 *)temp_v0)->unk_00 & 0x1F, temp_a1);
                        if (((S_8008ACDC_9 *)temp_v0_2)->unk_03 & 0x20) {
                            func_800956B8(arg0, arg1, arg2, temp_v0_2);
                        } else {
                            func_80095854(arg0, arg1, arg2, temp_v0_2);
                        }
                        goto epilogue;
                    case 0xA0:
                        func_8002534C(arg0, arg1, arg2, arg3);
                        goto epilogue;
                    case 0xC8:
                        ((S_8008ACDC_0 *)arg0)->unk_96 = (s16) (((S_8008ACDC_6 *)temp_v0)->unk_00 & 0x7F);
                        func_8008D368(arg0, arg1, arg2, &D_800DD148, 2);
                        goto epilogue;
                    case 0xD8:
                        D_800DD830[((S_8008ACDC_6 *)temp_v0)->unk_00 & 0x7F]();
                        goto epilogue;
                    }
                }
            } else {
                D_800E3544 = 0;
                if (flags & 4) {
                    if ((*(u8 *)D_800E3CD0) == 0) {
                        (*(s8 *)D_800E3CD0) = 1;
                        func_80040AA0(3);
                        goto epilogue;
                    }
                } else {
                    if ((func_80094EA4(flags) << 0x10) != 0) {
                        ((S_8008ACDC_0 *)arg0)->unk_A4 = 0U;
                    }
                    if ((((S_8008ACDC_0 *)arg0)->unk_A2 & 0x200) && ((func_800A2C34(arg3) << 0x10) == 0) && !(((S_8008ACDC_3 *)status)->unk_02 & 4)) {
                        ((S_8008ACDC_0 *)arg0)->unk_A2 = (u16) (((S_8008ACDC_0 *)arg0)->unk_A2 & 0xFDFF);
                        if ((func_800A4474(((S_8008ACDC_1 *)arg2)->unk_24, ((S_8008ACDC_1 *)arg2)->unk_25) << 0x10) != 0) {
                            func_8008CF6C(arg0, arg1, arg2, &D_800245A8);
                            goto epilogue;
                        }
                    }
                    if (((S_8008ACDC_5 *)data)->unk_08 & 0x80) {
                        func_8008CF6C(arg0, arg1, arg2, &D_80050CAC);
                        goto epilogue;
                    }
                    if ((((S_8008ACDC_5 *)data)->unk_08 & 0x10) || !(((S_8008ACDC_5 *)data)->unk_08 & 3) || (func_8008D024(arg0, arg1, arg2, (((u32) ((S_8008ACDC_5 *)data)->unk_08 >> 1) ^ 1) & 1, 0) == 0)) {
                        temp_v0_3 = func_8009074C(((S_8008ACDC_0 *)arg0)->unk_9E, arg0 + 0xA2, arg3 + 0x2A);
                        if (temp_v0_3 != 0xFFF) {
                            ((S_8008ACDC_4 *)arg3)->unk_2A.s = (u16) temp_v0_3;
                            if (!(((S_8008ACDC_5 *)data)->unk_08 & 0x10)) {
                                temp_v1_7 = ((S_8008ACDC_0 *)arg0)->unk_A2;
                                if (!(temp_v1_7 & 0x400)) {
                                    ((S_8008ACDC_0 *)arg0)->unk_A2 = (u16) (temp_v1_7 & 0xFFFE);
                                    if (((S_8008ACDC_4 *)arg3)->unk_1C & 0x400) {
                                        ((S_8008ACDC_4 *)arg3)->unk_2A.s = (u16) (((S_8008ACDC_4 *)arg3)->unk_2A.s + (func_800A6D30() & 0xE00));
                                    }
                                    func_8008B9FC(arg0, arg1, arg2, arg3);
                                    if (((S_8008ACDC_0 *)arg0)->unk_9A != 0xE) {
                                        goto epilogue;
                                    }
                                    goto block_163;
                                }
                            }
                            ((S_8008ACDC_0 *)arg0)->unk_96 = 0;
                            goto block_163;
                        }
block_163:
                        tail_data_flags = ((S_8008ACDC_5 *)data)->unk_08;
                        if ((tail_data_flags & 0x30) == 0x30) {
                            ((S_8008ACDC_0 *)arg0)->unk_A2 = (u16) (((S_8008ACDC_0 *)arg0)->unk_A2 & 0xFFFE);
                            func_8008C7B4(arg0, arg1, arg2, arg3);
                            goto epilogue;
                        }
                        temp_v1_8 = ((S_8008ACDC_0 *)arg0)->unk_A2;
                        current_s = temp_v1_8 & 0x40;
                        if (current_s != 0) {
                            current_s = tail_data_flags & 0x40;
                            if (current_s == 0) {
                                ((S_8008ACDC_0 *)arg0)->unk_A2 = (u16) (temp_v1_8 & 0xFFBF);
                            }
                            goto block_176;
                        }
                        current_s = tail_data_flags & 0x40;
                        if (current_s != 0) {
                            (*(u16 *)((u8 *)arg0 + 0xA2)) = (u16) (temp_v1_8 & 0xFFFE);
                            if (!(((S_8008ACDC_5 *)data)->unk_08 & 0x20)) {
                                if ((func_8008C8BC(arg0, arg1, arg2, arg3) << 0x10) != 0) {
                                    func_8008B7F8();
                                }
                            } else if (func_8008C5C4(arg0, arg1, arg2, arg3) == 0) {
                                goto block_176;
                            }
                        } else {
block_176:
                            ASM_MEM_BARRIER();   /* MATCH pin: retail register colouring depends on it */
                            if (D_80013714 & 9) {
                                ((S_8008ACDC_0 *)arg0)->unk_A4 = 0U;
                            }
                            if (((S_8008ACDC_0 *)arg0)->unk_9A == 0xE) {
                                temp_v0_5 = ((S_8008ACDC_0 *)arg0)->unk_A4 + 1;
                                ((S_8008ACDC_0 *)arg0)->unk_A4 = temp_v0_5;
                                if ((s16) temp_v0_5 >= 0x3D) {
                                    ((S_8008ACDC_0 *)arg0)->unk_A4 = 0x3CU;
                                    func_8008CCB0(arg0, arg1, arg2, arg3);
                                    goto epilogue;
                                }
                            }
                            goto block_182;
                        }
                    }
                }
            }
        } else {
block_182:
            temp_v1_9 = ((S_8008ACDC_0 *)arg0)->unk_A2;
            if (temp_v1_9 & 1) {
                ((S_8008ACDC_0 *)arg0)->unk_A2 = (u16) (temp_v1_9 & 0xFFFE);
                (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD058;
                func_80048A44(arg2, D_800DD058[((s32) (D_80083228 + (s16) ((S_8008ACDC_4 *)arg3)->unk_2A.s + 0x100) >> 9) & 7], 0, 1);
            }
            if (((S_8008ACDC_1 *)arg2)->unk_14 & 0xE000) {
                (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DCFB0;
                func_80048A44(arg2, D_800DCFB0[((s32) (D_80083228 + (s16) ((S_8008ACDC_4 *)arg3)->unk_2A.s + 0x100) >> 9) & 7], 0, 1);
            }
        }
    }
epilogue:
    return;
}
