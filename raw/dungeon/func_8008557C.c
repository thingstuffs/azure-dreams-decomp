/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */


/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)

#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

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
    register s32 kind ASM_REG("$2");
    s32 angle_target;
    s32 normalized;
    register s32 sign_tmp ASM_REG("$3");
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
    register u16 *flags_page ASM_REG("$4");
    s32 flags;
    register u32 temp_v1_6 ASM_REG("$3");
    s32 case88_index;
    register void *case88_value ASM_REG("$7");
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
    register void *arg2 ASM_REG("$20");
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
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9A);
    if (temp_v1 != 0xE) {
        if (temp_v1 != 0x17) {
            if (M2C_FIELD(arg0, u16 *, 0xA2) & 0x100) {
                func_8008D94C(arg0);
                goto epilogue;
            }
            M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
            M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (M2C_FIELD(arg0, u16 *, 0xA2) & 0xFEFF);
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
            M2C_FIELD(arg0, s8 *, 0x9B) = 0;
            M2C_FIELD(arg0, u16 *, 0xA4) = 0U;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            goto block_6;
        }
block_6:
        M2C_FIELD(arg0, s16 *, 0x96) = 0;
        func_800A4300(arg2, arg3);
        goto block_7;
    }
block_7:
    status = D_80083460;
    M2C_FIELD(status, u16 *, 2) = (u16) (M2C_FIELD(status, u16 *, 2) & 0xFF7F);
    temp_v1_2 = M2C_FIELD(arg3, s16 *, 0x64);
    if ((temp_v1_2 < 0) || (M2C_FIELD(arg0, u16 *, 0x10C) & 1)) {
        func_8008CAA0(arg0, arg1, arg2, arg3);
        goto epilogue;
    }
    if (temp_v1_2 > 0) {
        func_8008CBA0(arg0, arg1, arg2, arg3);
    }
    if (M2C_FIELD(arg3, s32 *, 0x14) & 0x20000) {
        func_80091B5C(arg0, arg1, arg2, arg3);
        goto epilogue;
    }
    if (!(M2C_FIELD(arg0, u16 *, 0xA2) & 0x10)) {
        func_8008C468(arg0, arg1, arg2, arg3);
        goto epilogue;
    }
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x200) {
        func_80090200(arg0, arg1, arg2, arg3);
        goto epilogue;
    }
    if (((func_800A1C58(arg3) << 0x10) == 0) || (func_8008D1D0(arg0, arg1, arg2, arg3) == 0)) {
        temp_v1_3 = M2C_FIELD(arg0, u16 *, 0xA2);
        if (temp_v1_3 & 0x80) {
            func_8008D7D0(arg0, arg1, arg2, arg3);
            goto epilogue;
        }
        if (!(M2C_FIELD(status, u16 *, 2) & 4)) {
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x20) {
                ASM_SCHED_BARRIER();
                if (!(D_80013714 & 1) && (M2C_FIELD(data, u32 *, 8) & 0x80)) {
                    M2C_FIELD(arg3, s16 *, 0x8A) = 2;
                    D_800E4940 = 2;
                    func_8008CF6C(arg0, arg1, arg2, &D_8004F5F4);
                    D_80082EB0 = 0;
                    M2C_FIELD(arg0, s32 *, 0xC8) = 0;
                    M2C_FIELD(arg0, s32 *, 0x104) = 0;
                    goto epilogue;
                }
                goto call_C7B4;
            }
            ASM_SCHED_BARRIER();
            flags_page = (u16 *) 0x80010000;
            ASM_KEEP_NV(flags_page);
            flags = flags_page[0x1B8A];
            if (flags & 1) {
                M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (temp_v1_3 & 0xFFFE);
                if (temp_v1_3 & 0x200) {
                    M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (temp_v1_3 & 0xFDFE);
                }
                temp_v0 = func_8009F868(flags);
                if (temp_v0 != NULL) {
                    kind = M2C_FIELD(temp_v0, u8 *, 1) & 7;
                    temp_a1 = M2C_FIELD(arg3, u16 *, 0x2A);
                    ASM_KEEP_NV(kind);
                    kind &= 0xFF;
                    temp_a0 = kind << 9;
                    ASM_KEEP_NV(temp_a0);
                    sign_tmp = temp_a1 & 0xFFF;
                    ASM_KEEP_NV(sign_tmp);
                    angle_target = temp_a0;
                    ASM_KEEP_NV(angle_target);
                    M2C_FIELD(arg3, u16 *, 0x2A) = sign_tmp;
                    if (sign_tmp != angle_target) {
                        normalized = temp_a1 & 0x800;
                        if (!normalized) {
                            normalized = temp_a1 & 0x7FF;
                        } else {
                            normalized = sign_tmp | 0xF800;
                        }
                        M2C_FIELD(arg3, u16 *, 0x2A) = normalized;
                        normalized = temp_a0 & 0x800;
                        if (!normalized) {
                            normalized = temp_a0 & 0x7FF;
                        } else {
                            normalized = temp_a0 | 0xF800;
                        }
                        temp_a0 = normalized;
                        ASM_KEEP_NV(temp_a0);
                        sign_tmp = temp_a0 << 16;
                        ASM_KEEP_NV(sign_tmp);
                        signed_target = sign_tmp >> 16;
                        ASM_MEM_BARRIER();
                        current_s = M2C_FIELD(arg3, s16 *, 0x2A);
                        current_u = M2C_FIELD(arg3, u16 *, 0x2A);
                        var_v0_3 = current_s - signed_target;
                        if (var_v0_3 < 0) {
                            var_v0_3 = 0 - var_v0_3;
                        }
                        if (var_v0_3 >= 0x801) {
                            M2C_FIELD(arg3, u16 *, 0x2A) = (u16) ((temp_a0 & ~0xFFF) | (current_u & 0xFFF));
                        }
                        ASM_MEM_BARRIER();
                        current_s = M2C_FIELD(arg3, s16 *, 0x2A);
                        ASM_KEEP_NV(current_s);
                        current_u = M2C_FIELD(arg3, u16 *, 0x2A);
                        ASM_KEEP_NV(current_u);
                        var_v0_4 = signed_target < current_s;
                        if (!var_v0_4) {
                            var_v0_4 = current_u + 0x200;
                        } else {
                            var_v0_4 = current_u - 0x200;
                        }
                        M2C_FIELD(arg3, u16 *, 0x2A) = var_v0_4;
                        func_8009F988(temp_a0, signed_target);
                        func_8008B7A0();
                        return;
                    }
                    D_800E3544 = (u8) (M2C_FIELD(temp_v0, u8 *, 1) & 0xF8);
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
                        ASM_MEM_BARRIER();
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
                        if ((s16) func_80095538(arg0, M2C_FIELD(temp_v0, u8 *, 0) & 0x1F, M2C_FIELD(temp_v0, u8 *, 2) & 0x1F) < 0) {
                            goto call_F988;
                        }
                        func_8009FAAC();
                        goto epilogue;
                    case 0x50: {
                        u8 case50_byte;
                        s32 case50_bits;
                        s32 case50_kind;
                        register void *case50_value ASM_REG("$5");

                        case50_byte = M2C_FIELD(temp_v0, u8 *, 0);
                        case50_bits = case50_byte & 0x60;
                        temp_v0 = (void *) ((u32) case50_bits >> 5);
                        ASM_KEEP(case50_bits);
                        case50_value = func_8009FADC(case50_byte & 0x1F, temp_a1);
                        ASM_KEEP_NV(case50_value);
                        case50_kind = 0x15;
                        ASM_KEEP_NV(case50_kind);
                        case50_bits = (s32) temp_v0 << 2;
                        ASM_KEEP_NV(case50_bits);
                        case50_bits = case50_bits + (s32) arg0;
                        ASM_KEEP_NV(case50_bits);
                        if (func_80098920(M2C_FIELD((void *) case50_bits, s32 *, 0xAC), case50_value, case50_kind, 0) >= 0) {
                            goto epilogue;
                        }
                    }
call_F988:
                        func_8009F988();
                        goto epilogue;
                    case 0x58:
                        func_80098CF8(arg0, arg1, arg2, func_8009FADC(M2C_FIELD(temp_v0, u8 *, 0) & 0x1F, temp_a1));
                        goto epilogue;
                    case 0x68:
                        case68_value = func_8009FADC(M2C_FIELD(temp_v0, u8 *, 0) & 0x1F, temp_a1);
                        case_call_a0 = arg0;
                        ASM_KEEP_NV(case_call_a0);
                        case_call_a1 = arg1;
                        ASM_KEEP_NV(case_call_a1);
                        case_call_a2 = arg2;
                        ASM_KEEP_NV(case_call_a2);
                        temp_v1_6 = M2C_FIELD(temp_v0, u8 *, 0);
                        case88_value = case68_value;
                        temp_v1_6 &= 0x60;
                        temp_v1_6 >>= 5;
                        goto call_94270;
                    case 0x88:
                        case_call_a0 = arg0;
                        ASM_KEEP_NV(case_call_a0);
                        temp_v1_6 = (u32) (M2C_FIELD(temp_v0, u8 *, 0) & 0x60) >> 5;
                        case_call_a1 = arg1;
                        ASM_KEEP_NV(temp_v1_6);
                        case88_index = temp_v1_6 << 2;
                        case88_index = case88_index + (s32) case_call_a0;
                        case88_value = (void *) M2C_FIELD((void *) case88_index, s32 *, 0xD0);
                        ASM_KEEP(case88_value);
                        case_call_a2 = arg2;
                        ASM_KEEP_NV(case_call_a2);
call_94270:
                        func_80094270(case_call_a0, case_call_a1, case_call_a2, case88_value, temp_v1_6);
                        goto epilogue;
                    case 0x70:
                        temp_a1_2 = M2C_FIELD(temp_v0, u8 *, 0);
                        func_80094548((u32) (temp_a1_2 & 0x60) >> 5, temp_a1_2 & 7);
                        goto epilogue;
                    case 0x78:
                        temp_a1_5 = M2C_FIELD(temp_v0, u8 *, 0);
                        func_8009458C((u32) (temp_a1_5 & 0x60) >> 5, temp_a1_5 & 0x1F);
                        goto epilogue;
                    case 0x80:
                        temp_a1_3 = M2C_FIELD(temp_v0, u8 *, 0);
                        func_800945C4((u32) (temp_a1_3 & 0x60) >> 5, temp_a1_3 & 0x1F);
                        goto epilogue;
                    case 0x90:
                        temp_a1_4 = M2C_FIELD(temp_v0, u8 *, 0);
                        func_8009456C((u32) (temp_a1_4 & 0x60) >> 5, temp_a1_4 & 7);
                        goto epilogue;
                    case 0x98:
                        temp_v0_2 = func_8009FADC(M2C_FIELD(temp_v0, u8 *, 0) & 0x1F, temp_a1);
                        if (M2C_FIELD(temp_v0_2, u8 *, 3) & 0x20) {
                            func_800956B8(arg0, arg1, arg2, temp_v0_2);
                        } else {
                            func_80095854(arg0, arg1, arg2, temp_v0_2);
                        }
                        goto epilogue;
                    case 0xA0:
                        func_8002534C(arg0, arg1, arg2, arg3);
                        goto epilogue;
                    case 0xC8:
                        M2C_FIELD(arg0, s16 *, 0x96) = (s16) (M2C_FIELD(temp_v0, u8 *, 0) & 0x7F);
                        func_8008D368(arg0, arg1, arg2, &D_800DD148, 2);
                        goto epilogue;
                    case 0xD8:
                        D_800DD830[M2C_FIELD(temp_v0, u8 *, 0) & 0x7F]();
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
                        M2C_FIELD(arg0, u16 *, 0xA4) = 0U;
                    }
                    if ((M2C_FIELD(arg0, u16 *, 0xA2) & 0x200) && ((func_800A2C34(arg3) << 0x10) == 0) && !(M2C_FIELD(status, u16 *, 2) & 4)) {
                        M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (M2C_FIELD(arg0, u16 *, 0xA2) & 0xFDFF);
                        if ((func_800A4474(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25)) << 0x10) != 0) {
                            func_8008CF6C(arg0, arg1, arg2, &D_800245A8);
                            ASM_MEM_BARRIER();
                            goto epilogue;
                        }
                    }
                    if (M2C_FIELD(data, u32 *, 8) & 0x80) {
                        func_8008CF6C(arg0, arg1, arg2, &D_80050CAC);
                        goto epilogue;
                    }
                    if ((M2C_FIELD(data, u32 *, 8) & 0x10) || !(M2C_FIELD(data, u32 *, 8) & 3) || (func_8008D024(arg0, arg1, arg2, (((u32) M2C_FIELD(data, u32 *, 8) >> 1) ^ 1) & 1, 0) == 0)) {
                        temp_v0_3 = func_8009074C(M2C_FIELD(arg0, s16 *, 0x9E), arg0 + 0xA2, arg3 + 0x2A);
                        if (temp_v0_3 != 0xFFF) {
                            M2C_FIELD(arg3, u16 *, 0x2A) = (u16) temp_v0_3;
                            if (!(M2C_FIELD(data, u32 *, 8) & 0x10)) {
                                temp_v1_7 = M2C_FIELD(arg0, u16 *, 0xA2);
                                if (!(temp_v1_7 & 0x400)) {
                                    M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (temp_v1_7 & 0xFFFE);
                                    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x400) {
                                        M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (M2C_FIELD(arg3, u16 *, 0x2A) + (func_800A6D30() & 0xE00));
                                    }
                                    func_8008B9FC(arg0, arg1, arg2, arg3);
                                    if (M2C_FIELD(arg0, u8 *, 0x9A) != 0xE) {
                                        goto epilogue;
                                    }
                                    goto block_163;
                                }
                            }
                            M2C_FIELD(arg0, s16 *, 0x96) = 0;
                            goto block_163;
                        }
block_163:
                        tail_data_flags = M2C_FIELD(data, u32 *, 8);
                        if ((tail_data_flags & 0x30) == 0x30) {
                            M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (M2C_FIELD(arg0, u16 *, 0xA2) & 0xFFFE);
                            func_8008C7B4(arg0, arg1, arg2, arg3);
                            goto epilogue;
                        }
                        temp_v1_8 = M2C_FIELD(arg0, u16 *, 0xA2);
                        current_s = temp_v1_8 & 0x40;
                        if (current_s != 0) {
                            current_s = tail_data_flags & 0x40;
                            if (current_s == 0) {
                                M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (temp_v1_8 & 0xFFBF);
                            }
                            goto block_176;
                        }
                        current_s = tail_data_flags & 0x40;
                        if (current_s != 0) {
                            M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (temp_v1_8 & 0xFFFE);
                            if (!(M2C_FIELD(data, u32 *, 8) & 0x20)) {
                                if ((func_8008C8BC(arg0, arg1, arg2, arg3) << 0x10) != 0) {
                                    func_8008B7F8();
                                }
                            } else if (func_8008C5C4(arg0, arg1, arg2, arg3) == 0) {
                                goto block_176;
                            }
                        } else {
block_176:
                            ASM_MEM_BARRIER();
                            if (D_80013714 & 9) {
                                M2C_FIELD(arg0, u16 *, 0xA4) = 0U;
                            }
                            if (M2C_FIELD(arg0, u8 *, 0x9A) == 0xE) {
                                temp_v0_5 = M2C_FIELD(arg0, u16 *, 0xA4) + 1;
                                M2C_FIELD(arg0, u16 *, 0xA4) = temp_v0_5;
                                if ((s16) temp_v0_5 >= 0x3D) {
                                    M2C_FIELD(arg0, u16 *, 0xA4) = 0x3CU;
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
            temp_v1_9 = M2C_FIELD(arg0, u16 *, 0xA2);
            if (temp_v1_9 & 1) {
                M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (temp_v1_9 & 0xFFFE);
                M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD058;
                func_80048A44(arg2, D_800DD058[((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
            }
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
                M2C_FIELD(arg2, u8 **, 0x2C) = D_800DCFB0;
                func_80048A44(arg2, D_800DCFB0[((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
            }
        }
    }
epilogue:
    return;
}
