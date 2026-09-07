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
M2C_UNK func_8008F05C(); /* extern */
M2C_UNK func_8008F3C0();              /* extern */
M2C_UNK func_8008F3C8();           /* extern */
M2C_UNK func_8008F3FC();                 /* extern */
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

void func_8008EAC8(void *arg0, void *arg1, void *arg2, void *arg3) {
    s8 *held_D_80083160 = D_80083160;
    u8 *held_D_80083460;
    s16 temp_v0_3;
    s16 temp_v1;
    s16 var_v0_2;
    register s32 temp_a0 ASM_REG("$4");
    s32 temp_code;
    s32 temp_v0_4;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0_3;
    u16 temp_a1;
    u16 temp_v1_4;
    register s32 temp_v1_5 ASM_REG("$3");
    u16 temp_v1_6;
    u16 temp_v1_8;
    u16 var_v0;
    u16 var_v0_4;
    u32 temp_v1_7;
    u8 temp_a0_2;
    u8 temp_a1_2;
    u8 temp_a1_3;
    u8 temp_a1_4;
    u8 temp_a1_5;
    register s32 temp_angle ASM_REG("$2");
    register void *code8_a0 ASM_REG("$4");
    s32 tail_data_flags;
    void *temp_v0;
    void *temp_v0_2;

    if (M2C_FIELD(arg0, u8 *, 0x9A) != 0xE) {
        if (M2C_FIELD(arg0, u16 *, 0xA2) & 0x100) {
            func_8008D94C();
            func_8008F3FC();
            return;
        }
        goto block_5;
    }
block_5:
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
    if (!(M2C_FIELD(arg3, s32 *, 0x14) & 0x100000)) {
        func_800A4300(arg2, arg3);
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    }
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
    held_D_80083460 = (u8 *) &D_80083460;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(held_D_80083460, u16 *, 2) = (u16) (M2C_FIELD(held_D_80083460, u16 *, 2) & 0xFF7F);
    temp_v1 = M2C_FIELD(arg3, s16 *, 0x64);
    if ((temp_v1 < 0) || (M2C_FIELD(arg0, u16 *, 0x10C) & 1)) {
        func_8008CAA0(arg0, arg1, arg2, arg3);
        func_8008F3FC();
        return;
    }
    if (temp_v1 > 0) {
        func_8008CBA0(arg0, arg1, arg2, arg3);
    }
    temp_v1_2 = M2C_FIELD(arg3, s32 *, 0x14);
    if (temp_v1_2 & 0x20000) {
        M2C_FIELD(arg3, s32 *, 0x14) = (s32) (temp_v1_2 & 0xFFFDFFFF);
    }
    if (!(M2C_FIELD(arg0, u16 *, 0xA2) & 0x10)) {
        func_8008C468(arg0, arg1, arg2, arg3);
        func_8008F3FC();
        return;
    }
    temp_v1_3 = M2C_FIELD(arg3, s32 *, 0x1C);
    if (temp_v1_3 & 0x200) {
        func_80090200(arg0, arg1, arg2, arg3);
        func_8008F3FC();
        return;
    }
    if (!(temp_v1_3 & 0x100000)) {
        register void *call_arg ASM_REG("$4") = arg2;
        ASM_KEEP(call_arg);
        {
            void *callback = &D_8008ACDC;
            ASM_KEEP(callback);
            {
                void *data = &D_800DCFB0;
                ASM_KEEP(data);
                M2C_FIELD(arg0, void **, 0x8C) = callback;
                func_8008F3C8(call_arg, data);
            }
        }
        return;
    }
    if ((M2C_FIELD(arg0, s32 *, 0x124) != 0) && (((func_800A1C58(arg3) << 0x10) == 0) || (func_8008D1D0(arg0, arg1, arg2, arg3) == 0))) {
        if (!(M2C_FIELD(held_D_80083460, u16 *, 2) & 4)) {
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x20) {
                ASM_SCHED_BARRIER();
                if (!(D_80013714 & 1) && (M2C_FIELD(held_D_80083160, u32 *, 8) & 0x80)) {
                    M2C_FIELD(arg3, s16 *, 0x8A) = 2;
                    D_800E4940 = 2;
                    func_8008CF6C(arg0, arg1, arg2, &D_8004F5F4);
                    D_80082EB0 = 0;
                    M2C_FIELD(arg0, s32 *, 0xC8) = 0;
                    M2C_FIELD(arg0, s32 *, 0x104) = 0;
                    func_8008F3FC();
                    return;
                }
                goto code_10;
            }
            ASM_SCHED_BARRIER();
            if (D_80013714_second & 1) {
                temp_v1_4 = M2C_FIELD(arg0, u16 *, 0xA2);
                M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (temp_v1_4 & 0xFFFE);
                if (temp_v1_4 & 0x200) {
                    M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (temp_v1_4 & 0xFDFE);
                }
                temp_v0 = func_8009F868();
                if (temp_v0 != NULL) {
                    temp_angle = M2C_FIELD(temp_v0, u8 *, 1) & 7;
                    temp_a1 = M2C_FIELD(arg3, u16 *, 0x2A);
                    ASM_KEEP(temp_angle);
                    temp_angle = (u8) temp_angle;
                    ASM_KEEP(temp_angle);
                    temp_a0 = temp_angle << 9;
                    ASM_KEEP(temp_a0);
                    temp_v1_5 = temp_a1 & 0xFFF;
                    ASM_KEEP(temp_v1_5);
                    temp_angle = temp_a0;
                    ASM_KEEP(temp_angle);
                    M2C_FIELD(arg3, u16 *, 0x2A) = temp_v1_5;
                    if (temp_v1_5 != temp_angle) {
                        register s32 signed_target ASM_REG("$5");
                        register s32 diff ASM_REG("$2");
                        {
                            register s32 normalized ASM_REG("$2");
                            if (temp_a1 & 0x800) {
                                normalized = temp_v1_5 | 0xF800;
                            } else {
                                normalized = temp_a1 & 0x7FF;
                            }
                            M2C_FIELD(arg3, u16 *, 0x2A) = normalized;
                        }
                        {
                            register s32 normalized_target ASM_REG("$2");
                            if (temp_a0 & 0x800) {
                                normalized_target = temp_a0 | 0xF800;
                            } else {
                                normalized_target = temp_a0 & 0x7FF;
                            }
                            temp_a0 = normalized_target;
                            ASM_KEEP(temp_a0);
                        }
                        temp_v1_5 = (u32) temp_a0 << 16;
                        ASM_KEEP(temp_v1_5);
                        signed_target = temp_v1_5 >> 16;
                        ASM_KEEP(signed_target);
                        ASM_MEM_BARRIER();
                        diff = M2C_FIELD(arg3, s16 *, 0x2A);
                        temp_v1_5 = M2C_FIELD(arg3, u16 *, 0x2A);
                        diff -= signed_target;
                        if (diff < 0) {
                            diff = 0 - diff;
                        }
                        if (diff >= 0x801) {
                            M2C_FIELD(arg3, u16 *, 0x2A) = (u16) ((temp_a0 & ~0xFFF) | (temp_v1_5 & 0xFFF));
                        }
                        {
                            register s32 step ASM_REG("$2");
                            ASM_MEM_BARRIER();
                            step = M2C_FIELD(arg3, s16 *, 0x2A);
                            temp_v1_5 = M2C_FIELD(arg3, u16 *, 0x2A);
                            step = signed_target < step;
                            if (step) {
                                step = temp_v1_5 - 0x200;
                            } else {
                                step = temp_v1_5 + 0x200;
                            }
                            M2C_FIELD(arg3, u16 *, 0x2A) = step;
                        }
                        func_8009F988(temp_a0);
                        func_8008F3C0(arg2);
                        return;
                    }
                    *(volatile s8 *) &D_800E3544 = (s8) (M2C_FIELD(temp_v0, u8 *, 1) & 0xF8);
                    temp_code = *(u8 *) &D_800E3544;
                    if (temp_code == 0x70) goto code_70;
                    if (temp_code >= 0x71) goto code_high;
                    if (temp_code == 0x30) goto code_30;
                    if (temp_code >= 0x31) goto code_mid;
                    if (temp_code == 0x10) goto code_10;
                    if (temp_code >= 0x11) goto code_low_mid;
                    code8_a0 = arg0;
                    if (temp_code == 8) goto code_8;
                    func_8008F3FC();
                    return;
code_low_mid:
                    if (temp_code == 0x28) goto code_28;
                    func_8008F3FC();
                    return;
code_mid:
                    if (temp_code == 0x50) goto code_50;
                    if (temp_code >= 0x51) goto code_mid_high;
                    if (temp_code == 0x48) goto code_48;
                    func_8008F3FC();
                    return;
code_mid_high:
                    if (temp_code == 0x68) goto code_68;
                    func_8008F3FC();
                    return;
code_high:
                    if (temp_code == 0x90) goto code_90;
                    if (temp_code >= 0x91) goto code_top;
                    if (temp_code == 0x80) goto code_80;
                    if (temp_code >= 0x81) goto code_high_mid;
                    if (temp_code == 0x78) goto code_78;
                    func_8008F3FC();
                    return;
code_high_mid:
                    if (temp_code == 0x88) goto code_88;
                    func_8008F3FC();
                    return;
code_top:
                    if (temp_code == 0xA0) goto code_A0;
                    if (temp_code >= 0xA1) goto code_top_high;
                    if (temp_code == 0x98) goto code_98;
                    func_8008F3FC();
                    return;
code_top_high:
                    if (temp_code == 0xD8) goto code_D8;
                    func_8008F3FC();
                    return;
code_10:
                    func_8008C7B4(arg0, arg1, arg2, arg3);
                    func_8008F3FC();
                    ASM_SCHED_BARRIER();
                    return;
code_48:
                    if (func_80095538(arg0, M2C_FIELD(temp_v0, u8 *, 0) & 0x1F, M2C_FIELD(temp_v0, u8 *, 2) & 0x1F) >= 0) {
                        func_8009FAAC();
                        func_8008F3FC();
                        return;
                    }
                    func_8009F988();
                    func_8008F3FC();
                    return;
code_50:
                    temp_a0_2 = M2C_FIELD(temp_v0, u8 *, 0);
                    temp_v0 = (void *) ((u32) (temp_a0_2 & 0x60) >> 5);
                    temp_v0_2 = func_8009FADC(temp_a0_2 & 0x1F, temp_a1);
                    if (func_80098920(M2C_FIELD(((((u32) temp_v0) * 4) + arg0), s32 *, 0xAC), temp_v0_2, 0x15, 0) < 0) {
                        func_8009F988();
                        func_8008F3FC();
                    }
                    return;
code_68:
                    temp_v0_2 = func_8009FADC(M2C_FIELD(temp_v0, u8 *, 0) & 0x1F, temp_a1);
                    {
                        register void *call0 ASM_REG("$4") = arg0;
                        register void *call1 ASM_REG("$5") = arg1;
                        register void *call2 ASM_REG("$6") = arg2;
                        register void *call3 ASM_REG("$2") = temp_v0_2;
                        register u32 mode ASM_REG("$3");
                        ASM_KEEP(call0);
                        ASM_KEEP(call1);
                        ASM_KEEP(call2);
                        ASM_SCHED_BARRIER();
                        mode = M2C_FIELD(temp_v0, u8 *, 0);
                        ASM_KEEP(mode);
                        ASM_KEEP(call3);
                        mode &= 0x60;
                        ASM_KEEP(mode);
                        mode >>= 5;
                        ASM_TAILSLOT_PIN(mode);
                        func_8008F05C(call0, call1, call2, call3);
                    }
                    return;
code_88:
                    temp_v1_7 = (u32) (M2C_FIELD(temp_v0, u8 *, 0) & 0x60) >> 5;
                    temp_v0_4 = M2C_FIELD(((temp_v1_7 * 4) + arg0), s32 *, 0xD0);
                    func_80094270(arg0, arg1, arg2, temp_v0_4, temp_v1_7);
                    func_8008F3FC();
                    return;
code_70:
                    temp_a1_5 = M2C_FIELD(temp_v0, u8 *, 0);
                    func_80094548((u32) (temp_a1_5 & 0x60) >> 5, temp_a1_5 & 7);
                    func_8008F3FC();
                    return;
code_78:
                    temp_a1_2 = M2C_FIELD(temp_v0, u8 *, 0);
                    func_8009458C((u32) (temp_a1_2 & 0x60) >> 5, temp_a1_2 & 0x1F);
                    func_8008F3FC();
                    return;
code_80:
                    temp_a1_3 = M2C_FIELD(temp_v0, u8 *, 0);
                    func_800945C4((u32) (temp_a1_3 & 0x60) >> 5, temp_a1_3 & 0x1F);
                    func_8008F3FC();
                    return;
code_90:
                    temp_a1_4 = M2C_FIELD(temp_v0, u8 *, 0);
                    func_8009456C((u32) (temp_a1_4 & 0x60) >> 5, temp_a1_4 & 7);
                    func_8008F3FC();
                    return;
code_98:
                    temp_v0_2 = func_8009FADC(M2C_FIELD(temp_v0, u8 *, 0) & 0x1F, temp_a1);
                    if (M2C_FIELD(temp_v0_2, u8 *, 3) & 0x20) {
                        func_800956B8(arg0, arg1, arg2, temp_v0_2);
                        func_8008F3FC();
                        return;
                    }
                    func_80095854(arg0, arg1, arg2, temp_v0_2);
                    func_8008F3FC();
                    return;
code_A0:
                    func_8002534C(arg0, arg1, arg2, arg3);
                    func_8008F3FC();
                    return;
code_D8:
                    D_800DD830[M2C_FIELD(temp_v0, u8 *, 0) & 0x7F](temp_a0, temp_a1);
                    func_8008F3FC();
                    return;
                }
            } else {
                s32 flag_200;

                flag_200 = M2C_FIELD(arg0, u16 *, 0xA2) & 0x200;
                M2C_FIELD(&D_800E3544, s8 *, 0) = 0;
                if (flag_200 && ((func_800A2C34(arg3) << 0x10) == 0) && !(M2C_FIELD(held_D_80083460, u16 *, 2) & 4)) {
                    M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (M2C_FIELD(arg0, u16 *, 0xA2) & 0xFDFF);
                    if ((func_800A4474(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25)) << 0x10) != 0) {
                        func_8008CF6C(arg0, arg1, arg2, &D_800245A8);
                        func_8008F3FC();
                        ASM_SCHED_BARRIER();
                        return;
                    }
                }
                if (M2C_FIELD(held_D_80083160, u32 *, 8) & 0x80) {
                    func_8008CF6C(arg0, arg1, arg2, &D_80050CAC);
                    func_8008F3FC();
                    return;
                }
                if ((M2C_FIELD(held_D_80083160, u32 *, 8) & 0x10) || !(M2C_FIELD(held_D_80083160, u32 *, 8) & 3) || (func_8008D024(arg0, arg1, arg2, (((u32) M2C_FIELD(held_D_80083160, u32 *, 8) >> 1) ^ 1) & 1, 0) == 0)) {
                    temp_v0_3 = func_8009074C(M2C_FIELD(arg0, s16 *, 0x9E), arg0 + 0xA2, arg3 + 0x2A);
                    if (temp_v0_3 != 0xFFF) {
                        M2C_FIELD(arg3, u16 *, 0x2A) = (u16) temp_v0_3;
                        if (!(M2C_FIELD(held_D_80083160, u32 *, 8) & 0x10)) {
                            temp_v1_8 = M2C_FIELD(arg0, u16 *, 0xA2);
                            if (!(temp_v1_8 & 0x400)) {
                                M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (temp_v1_8 & 0xFFFE);
                                code8_a0 = arg0;
                                if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x400) {
                                    M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (M2C_FIELD(arg3, u16 *, 0x2A) + (func_800A6D30(code8_a0) & 0xE00));
                                    ASM_SCHED_BARRIER();
                                    code8_a0 = arg0;
                                }
code_8:
                                func_8008C13C(code8_a0, arg1, arg2, arg3);
                                func_8008F3FC();
                                return;
                            }
                        }
                    }
                    tail_data_flags = M2C_FIELD(held_D_80083160, u32 *, 8);
                    if ((tail_data_flags & 0x30) == 0x30) {
                        M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (M2C_FIELD(arg0, u16 *, 0xA2) & 0xFFFE);
                        func_8008C7B4(arg0, arg1, arg2, arg3);
                        func_8008F3FC();
                        return;
                    }
                    {
                        register s32 flag40 ASM_REG("$2");

                        temp_v1_6 = M2C_FIELD(arg0, u16 *, 0xA2);
                        flag40 = temp_v1_6 & 0x40;
                        ASM_KEEP_NV(flag40);
                        if (flag40) {
                            flag40 = tail_data_flags & 0x40;
                            ASM_KEEP_NV(flag40);
                            if (flag40 == 0) {
                                register void *tail_a0 ASM_REG("$4") = arg2;
                                register void *tail_a1 ASM_REG("$5") = arg1;

                                ASM_KEEP(tail_a0);
                                ASM_SET(tail_a0);
                                ASM_SET(tail_a1);
                                M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (temp_v1_6 & 0xFFBF);
                                func_8008F3C0(tail_a0, tail_a1);
                                return;
                            }
                            goto block_153;
                        }
                        flag40 = tail_data_flags & 0x40;
                        ASM_KEEP_NV(flag40);
                        temp_v0_4 = flag40;
                    }
                    if (temp_v0_4 != 0) {
                        if (!(tail_data_flags & 0x20)) {
code_28:
                            func_8008F6EC(arg0, arg1, arg2, arg3);
                            func_8008F3FC();
                            return;
                        }
code_30:
                        M2C_FIELD(arg0, s16 *, 0x96) = 6;
                        func_8008FA14(arg0, arg1, arg2, arg3);
                        func_8008F3FC();
                        return;
                    }
                    goto block_153;
                }
            }
        } else {
block_153:
            M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD0B8;
            func_80048A44(arg2, D_800DD0B8[((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
        }
    }
}
