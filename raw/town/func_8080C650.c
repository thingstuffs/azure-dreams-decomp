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

s32 func_80034A1C();                /* extern */
void *func_800374FC();            /* extern */
M2C_UNK func_8003BC18();           /* extern */
M2C_UNK func_8003EA54();                      /* extern */
M2C_UNK func_80050BD8();                     /* extern */
M2C_UNK func_80050BFC();                     /* extern */
M2C_UNK func_80058F88();                     /* extern */
s32 func_8006A3A4();                             /* extern */
s32 func_8006A470();                             /* extern */
M2C_UNK func_8023FB18();                      /* extern */
M2C_UNK func_80245C10();             /* extern */
s16 func_8025E01C();                          /* extern */
s32 func_8052776C() __attribute__((noreturn));
s32 func_805278B0() __attribute__((noreturn));
s32 func_80527920() __attribute__((noreturn));
s32 func_80527A3C() __attribute__((noreturn));
s32 func_80527AD0() __attribute__((noreturn));
s32 func_80527AF8() __attribute__((noreturn));
s32 func_80527BB8() __attribute__((noreturn));
s32 func_80527C60() __attribute__((noreturn));
s32 func_80527CCC() __attribute__((noreturn));
s32 func_80527CD8() __attribute__((noreturn));
s32 func_80527D18() __attribute__((noreturn));
s32 func_80527D2C() __attribute__((noreturn));
extern s16 D_800133A0[5];
extern s16 D_800133A0_store[5] __asm__("D_800133A0");
extern M2C_UNK D_8003C558[3];
extern volatile s32 D_80084D5C;
extern volatile s32 D_80084D5C_store __asm__("D_80084D5C");
extern M2C_UNK D_8012F130[5];
extern M2C_UNK D_801328C8[3];
extern s32 D_801328E8[3];
extern s32 D_80132AE8[3];
extern s32 D_80132AEC[3];
extern s32 D_80132AF0[3];
extern s16 D_80132AF2[5];
extern u8 D_802430A8[12];
extern u8 D_80243200[12];
extern u8 D_802434B0[12];
extern u8 D_802892EC[12];
extern u8 D_80289334[12];
extern u8 D_8028937C[12];
extern u8 D_802893C4[12];
extern u8 D_8028940C[12];
extern u8 D_802894AC[12];
extern u8 D_80289454[12];
extern u8 D_8028950C[12];
extern u8 D_8028954C[12];
extern s32 D_8029070C[3];
extern u8 D_80529080[12];
extern s16 D_80530658[];
extern s16 D_80530666;
void func_8080C650(void *in0, void *in1, void *in2) {
    s16 *var_v1;
    register s32 temp_s1 ASM_REG("$17");
    s16 raw_s1;
    s32 temp_v0_4;
    s16 temp_v1;
    register s32 var_a0 ASM_REG("$4");
    register s32 temp_a0 ASM_REG("$4");
    s32 temp_a0_2;
    s32 temp_a1;
    register s32 temp_lo ASM_REG("$2");
    register s32 temp_v0_6 ASM_REG("$2");
    s32 temp_v1_4;
    register s32 var_s2 ASM_REG("$18");
    s32 var_s2_2;
    s32 var_v0_2;
    s32 tmpx;
    register s32 state4_v0 ASM_REG("$2");
    register s32 state4_a1 ASM_REG("$5");
    register s32 high_v0 ASM_REG("$2");
    register s32 abs_v0 ASM_REG("$2");
    register s32 abs_v1 ASM_REG("$3");
    s32 state6_v0;
    s32 state6_v1;
    register s32 state10_sin_v0 ASM_REG("$2");
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_5;
    u16 temp_v0_7;
    u16 temp_state108;
    u16 temp_v1_2;
    u16 temp_v1_3;
    void *temp_v0_3;
    register void *var_s0 ASM_REG("$16");
    register void *arg0 ASM_REG("$20") = in0;
    register void *arg1 ASM_REG("$19") = in1;
    register void *arg2 ASM_REG("$22") = in2;
    register s32 *global_s7 ASM_REG("$23");
    register s32 *global_s5 ASM_REG("$21");

    var_s2 = 0;
    var_s0 = NULL;
    ASM_KEEP_NV(arg0);
    ASM_KEEP_NV(arg1);
    ASM_KEEP_NV(arg2);
    raw_s1 = func_8025E01C(arg1);
    global_s7 = D_8012F130;
    ASM_KEEP_NV(global_s7);
    global_s5 = D_801328E8;
    temp_s1 = raw_s1;
    if (M2C_FIELD(arg0, s16 *, 0x68) < 0xFF) {
        var_s0 = M2C_FIELD(arg0, void **, 0xAC);
        if (M2C_FIELD(var_s0, s16 *, 0x36) == 0xFF) {
            M2C_FIELD(arg0, s16 *, 0x68) = 0xFF;
        }
    }
    func_80245C10(arg1);
    if (M2C_FIELD(arg1, s16 *, 0xA) >= temp_s1) {
        M2C_FIELD(arg1, s16 *, 0xA) = temp_s1;
    }
    func_8003EA54(arg2);
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x68);
    if (temp_v1 == 0xB) {
        goto block_state11;
    }
    {
        if (temp_v1 < 0xC) {
            if (temp_v1 != 4) {
                if (temp_v1 < 5) {
                    if (temp_v1 != 1) {
                        if (temp_v1 < 2) {
                            if (temp_v1 != 0) {
                                return func_80527D18();
                            }
                            goto block_state0;
                        }
                        if (temp_v1 != 2) {
                            if (temp_v1 != 3) {
                                return func_80527D18();
                            }
                            goto block_state3;
                        }
                        goto block_state2;
                    }
                    goto block_state1;
                }
                if (temp_v1 < 0xA) {
                    if (temp_v1 < 7) {
                        if (temp_v1 != 5) {
                            if (temp_v1 != 6) {
                                return func_80527D18();
                            }
                            goto block_state6;
                        }
                        goto block_state5;
                    }
                    goto block_state7;
                }
                goto block_state10;
            }
            goto block_state4;
        }
        if (temp_v1 >= 0xC) {
            if (temp_v1 != 0x104) {
                if (temp_v1 < 0x105) {
                    if (temp_v1 != 0x101) {
                        if (temp_v1 < 0x102) {
                            if (temp_v1 != 0xFF) {
                                if (temp_v1 != 0x100) {
                                    return func_80527D18();
                                }
                                goto block_140;
                            }
                            goto block_highff;
                        }
                        if (temp_v1 != 0x102) {
                            if (temp_v1 != 0x103) {
                                return func_80527D18();
                            }
                            goto block_144;
                        }
                        goto block_140;
                    }
                    goto block_144;
                }
                if (temp_v1 != 0x107) {
                    if (temp_v1 < 0x108) {
                        if (temp_v1 != 0x105) {
                            if (temp_v1 != 0x106) {
                                return func_80527D18();
                            }
                            goto block_high106;
                        }
                        goto block_high105;
                    }
                    if (temp_v1 != 0x108) {
                        if (temp_v1 != 0x109) {
                            return func_80527D18();
                        }
                        goto block_high109;
                    }
                    goto block_high108;
                }
                goto block_high107;
            }
            goto block_high104;
        }
block_state0:
                M2C_FIELD(arg1, s32 *, 0) = 0x03A00000;
                M2C_FIELD(arg1, s32 *, 4) = 0x01E00000;
                M2C_FIELD(arg1, s16 *, 0xA) = func_8025E01C(arg1);
                M2C_FIELD(arg0, u16 *, 0x6C) = 0x40U;
                M2C_FIELD(arg0, s8 *, 0x15) = 0;
                M2C_FIELD(arg0, s16 *, 0x68) = 1;
block_state1:
                if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
                    M2C_FIELD(arg1, s32 *, 0x10) = 0x80000;
                    var_s2 = (s32)D_802892EC;
                }
                if (M2C_FIELD(arg0, s32 *, 0xA8) & 1) {
                    temp_v0 = M2C_FIELD(arg0, u16 *, 0x6C) - 1;
                    M2C_FIELD(arg0, u16 *, 0x6C) = temp_v0;
                    if ((s16) temp_v0 >= 0) {
                        M2C_FIELD(arg1, s32 *, 0) = (s32) ((func_8006A3A4((s16) temp_v0 << 7) << 7) + 0x03A00000);
                    }
                }
                if (M2C_FIELD(arg1, s32 *, 4) > 0x0477FFFF) {
                    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 1);
                    M2C_FIELD(arg1, s32 *, 0xC) = 0x80000;
                    var_s2 = (s32)D_80289334;
                    ASM_KEEP(var_s2);
                    M2C_FIELD(arg0, s16 *, 0x68) = 2;
                    return func_80527D18();
                }
                goto block_160;
block_state2:
                if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
                    var_s2 = (s32)D_802893C4;
                }
                if (M2C_FIELD(arg1, s32 *, 4) > 0x048FFFFF) {
                    tmpx = 3;
                    var_s2 = (s32)D_8028937C;
                    ASM_KEEP(var_s2);
                    M2C_FIELD(arg1, s32 *, 0x10) = 0;
                    M2C_FIELD(arg0, s16 *, 0x68) = tmpx;
                    return func_80527D18();
                }
                goto block_160;
block_state3:
                if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
                    var_s2 = (s32)D_802893C4;
                }
                if (M2C_FIELD(arg1, s32 *, 0) > 0x03DFFFFF) {
                    M2C_FIELD(arg1, s32 *, 0x14) = -0x100000;
                    var_s2 = (s32)D_80289454;
                    ASM_KEEP(var_s2);
                    M2C_FIELD(arg0, s16 *, 0x68) = 4;
                    return func_80527D18();
                }
                goto block_160;
block_state4:
                temp_a0 = M2C_FIELD(arg1, s32 *, 0);
                state4_a1 = 0x48000;
                state4_v0 = M2C_FIELD(arg1, s32 *, 0x14) + state4_a1;
                M2C_FIELD(arg1, s32 *, 0x14) = state4_v0;
                if (temp_a0 > 0x041FFFFF) {
                    M2C_FIELD(arg1, s32 *, 0x14) = 0;
                    M2C_FIELD(arg1, s32 *, 0xC) = 0;
                    M2C_FIELD(arg0, s8 *, 0x15) = 1;
                    M2C_FIELD(arg0, s16 *, 0x68) = 5;
                    return func_80527D18();
                }
                goto block_160;
block_state5:
                if (global_s5[0] == (s32)D_802430A8) {
                    M2C_FIELD(arg0, u16 *, 0x6C) = 7U;
                    global_s5[0] = (s32)D_80243200;
                    M2C_FIELD(arg0, s8 *, 0x15) = 0;
                    M2C_FIELD(arg0, s16 *, 0x68) = 6;
                    return func_80527D18();
                }
                goto block_160;
block_state6:
                M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (D_80132AE8[0] - M2C_FIELD(arg1, s32 *, 0)) >> 1);
                M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (D_80132AEC[0] - M2C_FIELD(arg1, s32 *, 4)) >> 1);
                state6_v0 = D_80132AF0[0] + D_8029070C[0];
                state6_v1 = M2C_FIELD(arg1, s32 *, 8) + 0x80000;
                state6_v0 -= state6_v1;
                M2C_FIELD(arg1, s32 *, 0x14) = state6_v0 >> 1;
                func_80245C10(arg1);
                global_s5[0] = (s32)D_80243200;
                temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x6C) - 1;
                M2C_FIELD(arg0, u16 *, 0x6C) = temp_v0_2;
                if ((temp_v0_2 << 0x10) <= 0) {
                    global_s5[0] = (s32)D_80243200;
                    M2C_FIELD(arg1, s32 *, 0x14) = 0;
                    M2C_FIELD(arg1, s32 *, 0x10) = 0;
                    M2C_FIELD(arg1, s32 *, 0xC) = 0;
                    M2C_FIELD(arg0, s16 *, 0x68) = 7;
                    return func_80527D18();
                }
                goto block_160;
block_state7:
                    M2C_FIELD(arg1, s32 *, 0) = (s32) D_80132AE8[0];
                    M2C_FIELD(arg1, s32 *, 4) = (s32) D_80132AEC[0];
                    M2C_FIELD(arg1, s32 *, 8) = (s32) (D_80132AF0[0] + D_8029070C[0] + 0xFFF80000);
                    if (global_s7[4] & 0x20) {
                        if (D_80132AF2[0] == 0) {
                            if (M2C_FIELD(arg0, s16 *, 0x68) == 9) {
                                tmpx = 0x100000;
                                var_s2 = (s32)D_8028950C;
                                ASM_KEEP(var_s2);
                                M2C_FIELD(var_s0, s32 *, 0) = tmpx;
                                return func_8052776C();
                            }
                            global_s5[0] = (s32)D_802434B0;
                            M2C_FIELD(arg1, s32 *, 0x14) = 0x100000;
                            return func_8052776C();
                        }
                        global_s5[0] = (s32)D_80243200;
                        if (M2C_FIELD(arg0, s16 *, 0x68) == 9) {
                            func_80058F88(0x700);
                        }
                        M2C_FIELD(var_s0, u16 *, 0x2A) = (u16)(M2C_FIELD(var_s0, u16 *, 0x2A) & ~4);
                        return func_80527CCC();
                    }
                    goto block_160;
block_state10:
                state10_sin_v0 = (s32) (((s32) M2C_FIELD(var_s0, s32 *, 0) >> 0xC) * func_8006A3A4(M2C_FIELD(var_s0, s16 *, 0x2C)));
                M2C_FIELD(arg1, s32 *, 0xC) = state10_sin_v0;
                temp_lo = ((s32) (0 - M2C_FIELD(var_s0, s32 *, 0)) >> 0xC) * func_8006A470(M2C_FIELD(var_s0, s16 *, 0x2C));
                M2C_FIELD(arg1, s32 *, 0x10) = temp_lo;
                if (temp_lo > -0x40000) {
                    M2C_FIELD(arg1, s32 *, 0x10) = -0x40000;
                }
                M2C_FIELD(var_s0, s16 *, 0x2C) = (s16) ((u16) M2C_FIELD(var_s0, s16 *, 0x2C) - ((s32) (M2C_FIELD(var_s0, u16 *, 0x2E) << 0x10) >> 0x14));
                if (M2C_FIELD(arg1, s32 *, 8) > 0) {
                    temp_v1_2 = M2C_FIELD(var_s0, u16 *, 0x2A);
                    if (!(temp_v1_2 & 4)) {
                        M2C_FIELD(var_s0, u16 *, 0x2A) = (u16) (temp_v1_2 | 4);
                        func_80058F88(0x701);
                    }
                    temp_a0_2 = M2C_FIELD(arg1, s32 *, 0);
                    M2C_FIELD(arg1, s32 *, 8) = 0x200000;
                    if (temp_a0_2 <= 0x041FFFFF) {
                        if (temp_a0_2 > 0x03BFFFFF) {
                            var_v0_2 = 0x03B80000;
                            goto block_98;
                        }
                        if (temp_a0_2 > 0x03800000) {
                            goto block_99;
                        }
                        M2C_FIELD(arg1, s32 *, 0) = 0x03880000;
                        return func_805278B0(temp_a0_2);
                    }
                    if (temp_a0_2 > 0x04BFFFFF) {
                        var_v0_2 = 0x04B80000;
                        goto block_98;
                    }
                    if (temp_a0_2 > 0x04800000) {
                        goto block_99;
                    }
                    var_v0_2 = 0x04880000;
block_98:
                    M2C_FIELD(arg1, s32 *, 0) = var_v0_2;
block_99:
                    M2C_FIELD(var_s0, s16 *, 0x2C) = (s16) ((s32) (0 - M2C_FIELD(var_s0, s16 *, 0x2C)) >> 1);
                    goto block_100;
                }
block_100:
                if (M2C_FIELD(arg1, s32 *, 4) <= 0x01E00000) {
                    func_80058F88(0x1700);
                    func_80058F88(0x1701);
                    if (D_80530658[M2C_FIELD(var_s0, s16 *, 0x34)] == 8) {
                        var_s2 = 1;
                        global_s5 = (s32 *)0x1000;
                        M2C_FIELD(arg0, s32 *, 0xA8) = (s32) (M2C_FIELD(arg0, s32 *, 0xA8) | 1);
                        {
                            ASM_KEEP(var_s2);
                            temp_v0_3 = func_800374FC(0x136, D_801328C8);
                            if (temp_v0_3 != NULL) {
                                var_s0 = M2C_FIELD(temp_v0_3, void **, 0xC);
                                func_8003BC18(temp_v0_3, D_8003C558);
                                M2C_FIELD(var_s0, s32 *, 0xC) = 0x808080;
                                M2C_FIELD(var_s0, s16 *, 0x1E) = (s16)(s32)global_s5;
                                M2C_FIELD(var_s0, s16 *, 0x1C) = (s16)(s32)global_s5;
                                M2C_FIELD(temp_v0_3, s16 *, 0x22) = 0x78;
                                M2C_FIELD(temp_v0_3, void **, 0x24) = arg1;
                                M2C_FIELD(temp_v0_3, s32 *, 0x10) = (s32)D_80529080;
                                func_80034A1C(var_s0, D_8028954C, (s16)(var_s2 * 4));
                            }
                            var_s2 -= 1;
                            if (var_s2 >= 0) {
                                return func_80527920();
                            }
                            goto block_after;
                        }
                    }
                    M2C_FIELD(arg0, s32 *, 0xA8) = (s32) (M2C_FIELD(arg0, s32 *, 0xA8) & ~1);
block_after:
                    ASM_KEEP(arg0);
                    var_s2 = (s32)D_802894AC;
                    M2C_FIELD(arg1, s32 *, 0x14) = 0;
                    M2C_FIELD(arg1, s32 *, 0x10) = 0;
                    M2C_FIELD(arg1, s32 *, 0xC) = 0;
                    M2C_FIELD(arg0, u16 *, 0x6C) = 0x14U;
                    ASM_KEEP(var_s2);
                    M2C_FIELD(arg0, s16 *, 0x68) = 0xB;
                    return func_80527D18();
                }
                goto block_160;
block_state11:
        temp_v1_3 = M2C_FIELD(arg2, u16 *, 0x14);
        if ((temp_v1_3 & 0x6000) && ((s16) M2C_FIELD(arg0, u16 *, 0x6C) > 0)) {
            var_s2 = (s32)D_802892EC;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (temp_v1_3 | 0x800);
        }
        temp_v1_4 = M2C_FIELD(arg1, s32 *, 0);
        temp_v0_6 = 0x03A00000;
        if (temp_v1_4 > temp_v0_6) {
            temp_v0_6 = M2C_FIELD(arg2, u16 *, 0x14) & 0xFFFE;
            ASM_TAILSLOT_PIN_TIED(temp_v0_6);
            return func_80527A3C();
        }
        ASM_SCHED_BARRIER();
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 1);
        temp_v0_6 = M2C_FIELD(arg1, s32 *, 4);
        M2C_FIELD(arg1, s32 *, 4) = (s32) (((s32) (0x01E00000 - temp_v0_6) >> 1) + temp_v0_6);
        temp_v0_7 = M2C_FIELD(arg0, u16 *, 0x6C) - 1;
        M2C_FIELD(arg0, u16 *, 0x6C) = temp_v0_7;
        if ((temp_v0_7 << 0x10) == 0) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
            temp_v1_4 = M2C_FIELD(arg1, s32 *, 0);
            if (temp_v1_4 > 0x03A80000) {
                M2C_FIELD(arg1, s32 *, 0xC) = -0x80000;
                return func_80527AD0();
            }
            ASM_SCHED_BARRIER();
            if (temp_v1_4 <= 0x0397FFFF) {
                M2C_FIELD(arg1, s32 *, 0xC) = 0x80000;
                return func_80527AD0();
            }
            var_s2 = (s32)D_8028937C;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg1, s32 *, 0) = 0x03A00000;
            goto block_124;
        }
block_124:
        if ((u32) (M2C_FIELD(arg1, s32 *, 0) + 0xFC440000) <= 0xC80000U) {
            M2C_FIELD(arg1, s32 *, 8) = 0;
            return func_80527AF8();
        }
        M2C_FIELD(arg1, s32 *, 8) = 0x200000;
        ASM_KEEP_NV(arg1);
        abs_v1 = 0xFC600000;
        abs_v0 = M2C_FIELD(arg1, s32 *, 0) + abs_v1;
        if (abs_v0 < 0) {
            abs_v0 = 0 - abs_v0;
        }
        ASM_SCHED_BARRIER();
        if (abs_v0 <= 0x80000) {
            abs_v0 = (s32) (s16) M2C_FIELD(arg0, u16 *, 0x6C);
            if (abs_v0 < 0) {
                M2C_FIELD(var_s0, u16 *, 0x2A) = (u16) (M2C_FIELD(var_s0, u16 *, 0x2A) | 2);
                M2C_FIELD(arg1, s32 *, 0x14) = 0;
                M2C_FIELD(arg1, s32 *, 0x10) = 0;
                M2C_FIELD(arg1, s32 *, 0xC) = 0;
                M2C_FIELD(arg0, s16 *, 0x68) = 0;
                return func_80527D18();
            }
        }
        goto block_160;
block_highff:
        var_a0 = 0;
        var_s2 = 7;
        var_v1 = &D_80530658[7];
        do {
            temp_v0_4 = *var_v1;
            var_v1 -= 1;
            var_s2 -= 1;
            var_a0 += temp_v0_4;
        } while (var_s2 >= 0);
        if ((D_800133A0[0] < var_a0) || (var_a0 == 0x40)) {
            D_800133A0_store[0] = var_a0;
            func_80050BFC(0x5DA);
            return func_80527BB8();
        }
        func_80050BD8(0x5DA);
        var_s2 = (s32)D_802892EC;
        M2C_FIELD(arg1, s32 *, 0x10) = 0x80000;
        M2C_FIELD(arg0, u16 *, 0x6C) = 0x1EU;
        M2C_FIELD(arg0, s16 *, 0x68) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x68) + 1);
block_140:
        temp_v0_5 = M2C_FIELD(arg0, u16 *, 0x6C) - 1;
        M2C_FIELD(arg0, u16 *, 0x6C) = temp_v0_5;
        if ((temp_v0_5 << 0x10) <= 0) {
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0x14) = -0x100000;
            return func_80527CCC();
        }
        goto block_160;
block_144:
        high_v0 = M2C_FIELD(arg1, s32 *, 0x14) + 0x20000;
        M2C_FIELD(arg1, s32 *, 0x14) = high_v0;
        if (M2C_FIELD(arg1, s32 *, 8) > 0x1FFFFF) {
            M2C_FIELD(arg1, s32 *, 8) = 0x200000;
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            return func_80527CCC();
        }
        goto block_160;
block_high104:
        var_s2 = (s32)D_80289334;
        raw_s1 = temp_v1 + 1;
        ASM_KEEP(var_s2);
        ASM_TAILSLOT_PIN_TIED(raw_s1);
        return func_80527C60();
block_high105:
        var_s2 = (s32)D_8028937C;
        raw_s1 = temp_v1 + 1;
        ASM_KEEP(var_s2);
        ASM_TAILSLOT_PIN_TIED(raw_s1);
        return func_80527C60();
block_high106:
        var_s2 = (s32)D_802893C4;
        raw_s1 = temp_v1 + 1;
        ASM_KEEP(var_s2);
        M2C_FIELD(arg0, s16 *, 0x68) = raw_s1;
        return func_80527D18();
block_high107:
        var_a0 = 0xC0C0C0;
        M2C_FIELD(arg1, s32 *, 0x10) = -0x80000;
        temp_v1_3 = M2C_FIELD(arg2, u16 *, 0x14);
        M2C_FIELD(arg2, s16 *, 0x10) = 0x60;
        M2C_FIELD(arg2, s32 *, 0xC) = var_a0;
        temp_v1_3 |= 0xC;
        M2C_FIELD(arg2, u16 *, 0x14) = temp_v1_3;
        temp_v0_6 = (u16) M2C_FIELD(arg0, u16 *, 0x68);
        ASM_KEEP(temp_v0_6);
        var_s2 = (s32)D_8028940C;
        ASM_KEEP(var_s2);
        temp_v0_6 += 1;
        ASM_TAILSLOT_PIN_TIED(temp_v0_6);
        return func_80527CD8(var_a0);
block_high108:
        M2C_FIELD(arg2, s32 *, 0xC) = (s32) (M2C_FIELD(arg2, s32 *, 0xC) + 0xFFF7F7F8);
        if (M2C_FIELD(arg2, u8 *, 0xC) < 0x11U) {
            temp_state108 = M2C_FIELD(arg0, u16 *, 0x68);
            M2C_FIELD(arg0, s16 *, 0x68) = (s16) (temp_state108 + 1);
            return func_80527D18();
        }
        goto block_160;
block_high109:
        func_8023FB18(arg0);
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_80084D5C_store = D_80084D5C | 0x8000;
        return func_80527D2C();
    }
block_160:
    if (var_s2 != 0) {
        func_80034A1C(arg2, var_s2, 0);
    }
}
