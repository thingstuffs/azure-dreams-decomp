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

/* Value-preserving cse-equivalence launder for the first callback's 4th
 * argument: a block-scoped $a0-pinned temp with the empty "=r"/"0" tie
 * (expression form of ASM_REG+ASM_KEEP_NV). Port build folds to the plain
 * value. */
#ifdef NON_MATCHING
#define KEEP_A0_EXPR(v) (v)
#else
#define KEEP_A0_EXPR(v) ({ register void *t_ ASM_REG("$4") = (v); ASM_KEEP_NV(t_); t_; })
#endif

void func_80047738(void *, u8, s8);              /* extern */
void func_80047784(void *, u8, s32);             /* extern */
void func_800478B8(void *);                       /* extern */
s32 func_800644B8(s32);                            /* extern */
M2C_UNK func_800A020C(s32, void *);               /* extern */
s32 func_800A9E70(void *, void *, void *, void *); /* extern */
M2C_UNK func_800AA36C(void *, void *, void *, void *); /* extern */
s16 func_800BCB04(s32, s32, s16);                 /* extern */
void func_80170D94(void) __attribute__((noreturn));  /* extern */
void func_80170E3C(void) __attribute__((noreturn));  /* extern */
void func_80170EB8(void) __attribute__((noreturn));  /* extern */
void func_80170F54(void) __attribute__((noreturn));  /* extern */
void func_80171210(void) __attribute__((noreturn));  /* extern */
void func_80171320(void) __attribute__((noreturn));  /* extern */
void func_80171330(void) __attribute__((noreturn));  /* extern */
void func_801713D4(void) __attribute__((noreturn));  /* extern */
extern u8 D_8006CCF8[12];
extern s16 D_80083228[5];
extern u16 D_80083462[5];
extern M2C_UNK D_80171400[3];
extern u8 D_80175140[12];
extern u8 D_80175148[12];
extern u8 D_80175170[12];
extern u8 D_80175178[12];
extern void *D_80175198[3];

void func_80170BF8(void *arg0_, void *arg1_, void *arg2_) {
    u16 initial_flags = D_80083462[0];
    register void *actor ASM_REG("$17") = arg0_;
    register void *motion ASM_REG("$21") = arg1_;
    register void *object ASM_REG("$20") = arg2_;
    register s32 var_s6 ASM_REG("$22") = 0;
    register void *actor2 ASM_REG("$18") = actor;
#define arg0 actor
#define arg1 motion
#define arg2 object

    M2C_UNK (*temp_v0)(void *, void *, void *, void *);
    M2C_UNK (*temp_v1)(void *, void *, void *, void *);
    u8 *temp_v1_5;
    u8 *temp_v1_8;
    u8 *var_a1;
    u8 *var_a1_2;
    u8 *var_v0;
    s16 temp_a0_2;
    s16 temp_a0_3;
    s16 temp_a0_4;
    s16 temp_a0_5;
    s16 temp_v0_2;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 var_v0_3;
    s32 temp_a0;
    s16 temp_a1;
    s32 temp_v1_10;
    s32 temp_v1_3;
    s32 temp_v1_6;
    s32 temp_final;
    u32 address_1;
    register u32 page_base ASM_REG("$2");
    register u32 tail_value ASM_REG("$5");
    register u32 temp_dead ASM_REG("$2");
    u16 temp_v0_3;
    u16 temp_v1_2;
    u16 temp_v1_4;
    u16 temp_v1_7;
    u16 temp_v1_9;
    u16 var_v0_2;
    s32 temp_s3;
    s16 temp_s0;
    if (initial_flags & 0x2000) {
            temp_v1 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
        if (temp_v1 == &D_80171400) {
            temp_v1(arg0_, arg1_, arg2_, KEEP_A0_EXPR(arg0_));
            func_801713D4();
            return;
        }
        M2C_FIELD(arg0, u8 *, 0x71) = (u8) (M2C_FIELD(arg0, u8 *, 0x71) & 0x7F);
        func_801713D4();
        return;
    }
    ASM_KEEP_NV(actor);
    ASM_KEEP_NV(motion);
    ASM_KEEP_NV(object);
    temp_s0 = (s8) M2C_FIELD(arg0, u8 *, 0x6D);
    if (func_800A9E70(arg0, arg1, arg2, arg0) == 0) {
        temp_v0 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
        if (temp_v0 != NULL) {
            temp_v0(arg0, arg1, arg2, arg0);
        }
        ((void (*)(void *, void *, void *, void *))D_80175198[M2C_FIELD(arg0, u8 *, 0x9A)])(arg0, arg1, arg2, arg0);
        if ((s16) temp_s0 != (s8) M2C_FIELD(arg0, u8 *, 0x6D)) {
            func_800AA36C(arg0, arg1, arg2, arg0);
        }
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
        if (!(M2C_FIELD(arg0, s32 *, 0x1C) & 0x40000) && !(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + (M2C_FIELD(arg0, s8 *, 0x9D) * 0x14000));
            M2C_FIELD(arg0, u8 *, 0x9D) = (u8) (M2C_FIELD(arg0, u8 *, 0x9D) + 1);
            func_80170D94();
            return;
        }
        M2C_FIELD(arg0, s8 *, 0x9D) = 0;
        ASM_SCHED_BARRIER();
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + M2C_FIELD(arg1, s32 *, 0x14));
        temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
        if (!(temp_v1_2 & 0x8000)) {
            temp_s3 = ((s32) (D_80083228[0] + M2C_FIELD(actor2, s16 *, 0x2A) + 0x100) >> 9) & 7;
            temp_s0 = (s16) temp_s3;
            if (M2C_FIELD(arg0, s16 *, 0x94) != temp_s0) {
                func_80047738(arg2, *(M2C_FIELD(arg2, u8 **, 0x2C) + temp_s0), M2C_FIELD(arg2, s8 *, 4));
                M2C_FIELD(arg0, s16 *, 0x94) = temp_s3;
            }
            if (D_8006CCF8[temp_s0] != 0) {
                temp_dead = M2C_FIELD(arg2, u16 *, 0x14);
                temp_dead |= 1;
                ASM_TAILSLOT_PIN(temp_dead);
                func_80170E3C();
                return;
            }
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFFFE);
            if (M2C_FIELD(arg0, u8 *, 0x9A) != 8) {
                func_800A020C(M2C_FIELD(actor2, s32 *, 0x1C), arg2 + 0xC);
            }
            if (!(M2C_FIELD(actor2, s32 *, 0x1C) & 0x20)) {
                if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
                    func_800478B8(arg2);
                    page_base = 0xF7FF0000;
                    ASM_PAGEBASE_PIN(page_base);
                    func_80170EB8();
                    return;
                }
                goto block_28;
            }
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x7000);
            M2C_FIELD(actor2, s32 *, 0x1C) = (s32) (M2C_FIELD(actor2, s32 *, 0x1C) & 0xFFFBFFFF);
block_28:
            temp_v1_3 = M2C_FIELD(actor2, s32 *, 0x1C) & 0xF7FFFFFF;
            M2C_FIELD(actor2, s32 *, 0x1C) = temp_v1_3;
            if (temp_v1_3 & 0x40000) {
                if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
                    temp_v1_4 = M2C_FIELD(arg0, u16 *, 0x98);
                    if (temp_v1_4 & 0x8000) {
                        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (temp_v1_4 & 0x7FFF);
            temp_v1_5 = M2C_FIELD(arg2, u8 **, 0x2C);
                        var_a1 = D_80175148;
                        if (temp_v1_5 == D_80175148) {
                            tail_value = (u32) D_80175140;
                            ASM_TAILSLOT_PIN(tail_value);
                            func_80170F54();
                            return;
                        }
                        if (temp_v1_5 != D_80175140) {
                            var_a1 = D_80175170;
                            if (temp_v1_5 == D_80175170) {
                                tail_value = (u32) D_80175178;
                                ASM_TAILSLOT_PIN(tail_value);
                                func_80170F54();
                                return;
                            }
                            if (temp_v1_5 == D_80175178) {
                                goto block_39;
                            }
                            goto block_40;
                        }
block_39:
                        M2C_FIELD(arg2, u8 **, 0x2C) = var_a1;
                        address_1 = (u32) ((((s32) (D_80083228[0] + M2C_FIELD(actor2, s16 *, 0x2A) + 0x100) >> 9) & 7));
                        address_1 += (u32) var_a1;
                        func_80047784(arg2, *(u8 *) address_1, 0);
                        goto block_40;
                    }
block_40:
                        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
                        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x8000);
                        if (M2C_FIELD(arg2, u8 **, 0x2C) == D_80175140) {
                            M2C_FIELD(arg0, s16 *, 0xA8) = 0;
                        }
                    }
                    var_s6 = func_800644B8((M2C_FIELD(arg0, s16 *, 0xA8) << 0xC) / 20) >> 0xA;
                    M2C_FIELD(arg0, s16 *, 0xA8) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA8) + 1);
                    goto block_44;
                }
block_44:
                if (!(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
                    temp_v0_2 = (s16) (func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(actor2, u16 *, 0x88) - 0x20)) - M2C_FIELD(actor2, u16 *, 0x88));
                    temp_v1_9 = (u16) M2C_FIELD(arg0, s16 *, 0x92);
                    if (M2C_FIELD(arg0, s16 *, 0x92) > (temp_v0_2 - 0x20)) {
                        M2C_FIELD(arg0, s16 *, 0x92) = (s16) (temp_v1_9 - 8);
                        func_80171330();
                        return;
                    }
                    ASM_SCHED_BARRIER();
                    if (M2C_FIELD(arg0, s16 *, 0x92) < (temp_v0_2 - 0x2A)) {
                        M2C_FIELD(arg0, s16 *, 0x92) = (s16) (temp_v1_9 + 8);
                        func_80171330();
                        return;
                    }
                    goto block_82;
                }
                goto block_82;
            }
            temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x98);
            M2C_FIELD(arg0, s16 *, 0xA8) = 0;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (temp_v0_3 & 0x7FFF);
            if (!(temp_v0_3 & 8)) {
                temp_a0 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(actor2, u16 *, 0x88) - 0x20));
                temp_v0_4 = (s16) temp_a0;
                temp_a0_3 = M2C_FIELD(actor2, s16 *, 0x88);
                temp_a0 = (s32) temp_v0_4 - temp_a0_3;
                if (temp_a0 < M2C_FIELD(arg0, s16 *, 0x92)) {
                    M2C_FIELD(arg0, s16 *, 0x92) = temp_a0;
                    M2C_FIELD(arg0, s8 *, 0x9D) = 0;
                    M2C_FIELD(arg1, s32 *, 0x14) = 0;
                    M2C_FIELD(actor2, s32 *, 0x1C) = M2C_FIELD(actor2, s32 *, 0x1C) | 0x08000000;
                    func_80171330();
                    return;
                }
            }
            goto block_82;
        }
        M2C_FIELD(arg2, u16 *, 0x14) = (temp_v1_2 & 0x800) ? (temp_v1_2 & 0x8FFF) : (temp_v1_2 | 0x7000);
        temp_v1_6 = M2C_FIELD(actor2, s32 *, 0x1C) & 0xF7FFFFFF;
        M2C_FIELD(actor2, s32 *, 0x1C) = temp_v1_6;
        if (!(temp_v1_6 & 0x40000)) {
            M2C_FIELD(arg0, s16 *, 0xA8) = 0;
            M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x92) - var_s6);
            var_s6 = 0;
            if (!(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
                temp_a0 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(actor2, u16 *, 0x88) - 0x20));
                temp_v0_5 = (s16) temp_a0;
                temp_a0_4 = M2C_FIELD(actor2, s16 *, 0x88);
                temp_a0 = (s32) temp_v0_5 - temp_a0_4;
                if (temp_a0 < M2C_FIELD(arg0, s16 *, 0x92)) {
                    M2C_FIELD(arg0, s16 *, 0x92) = temp_a0;
                    M2C_FIELD(arg0, s8 *, 0x9D) = 0;
                    M2C_FIELD(arg1, s32 *, 0x14) = 0;
                    M2C_FIELD(actor2, s32 *, 0x1C) = M2C_FIELD(actor2, s32 *, 0x1C) | 0x08000000;
                    func_80171320();
                    return;
                }
            }
            goto block_81;
        }
        if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
            temp_v1_7 = M2C_FIELD(arg0, u16 *, 0x98);
            if (temp_v1_7 & 0x8000) {
                M2C_FIELD(arg0, u16 *, 0x98) = (u16) (temp_v1_7 & 0x7FFF);
                        temp_v1_8 = M2C_FIELD(arg2, u8 **, 0x2C);
                var_a1_2 = D_80175148;
                if (temp_v1_8 == D_80175148) {
                    tail_value = (u32) D_80175140;
                    ASM_TAILSLOT_PIN(tail_value);
                    func_80171210();
                    return;
                }
                if (temp_v1_8 != D_80175140) {
                    var_a1_2 = D_80175170;
                    if (temp_v1_8 == D_80175170) {
                        tail_value = (u32) D_80175178;
                        ASM_TAILSLOT_PIN(tail_value);
                        func_80171210();
                        return;
                    }
                    if (temp_v1_8 == D_80175178) {
                        goto block_72;
                    }
                    goto block_73;
                }
block_72:
                M2C_FIELD(arg2, u8 **, 0x2C) = var_a1_2;
                address_1 = (u32) ((((s32) (D_80083228[0] + M2C_FIELD(actor2, s16 *, 0x2A) + 0x100) >> 9) & 7));
                address_1 += (u32) var_a1_2;
                func_80047784(arg2, *(u8 *) address_1, 0);
                goto block_73;
            }
block_73:
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
                M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x8000);
                if (M2C_FIELD(arg2, u8 **, 0x2C) == D_80175140) {
                    M2C_FIELD(arg0, s16 *, 0xA8) = 0;
                }
            }
            var_s6 = func_800644B8((M2C_FIELD(arg0, s16 *, 0xA8) << 0xC) / 20) >> 0xA;
            M2C_FIELD(arg0, s16 *, 0xA8) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA8) + 1);
            goto block_77;
        }
block_77:
        if (!(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
            temp_v0_6 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(actor2, u16 *, 0x88) - 0x20)) - M2C_FIELD(actor2, u16 *, 0x88);
            temp_a0_5 = M2C_FIELD(arg0, s16 *, 0x92);
            if (temp_a0_5 > (temp_v0_6 - 0x20)) {
                temp_v1_9 = (u16) M2C_FIELD(arg0, s16 *, 0x92);
                M2C_FIELD(arg0, s16 *, 0x92) = (s16) (temp_v1_9 - 8);
            } else if (temp_a0_5 < (temp_v0_6 - 0x2A)) {
                temp_v1_9 = (u16) M2C_FIELD(arg0, s16 *, 0x92);
                M2C_FIELD(arg0, s16 *, 0x92) = (s16) (temp_v1_9 + 8);
            }
        }
block_81:
        M2C_FIELD(arg0, s16 *, 0xA8) = 0;
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0x7FFF);
block_82:
        temp_v1_10 = M2C_FIELD(actor2, s32 *, 0x1C);
        if (temp_v1_10 & 0x40000000) {
            M2C_FIELD(actor2, s32 *, 0x1C) = (s32) (temp_v1_10 & 0xBFFFFFFF);
            temp_v0_7 = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(actor2, u16 *, 0x88) - 0x20));
            if (temp_v0_7 < 0x200) {
                M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x92) + (M2C_FIELD(actor2, u16 *, 0x88) - temp_v0_7));
                M2C_FIELD(actor2, u16 *, 0x88) = (u16) temp_v0_7;
            }
        }
        temp_final = (s32) (M2C_FIELD(actor2, u16 *, 0x88) + (u16) M2C_FIELD(arg0, s16 *, 0x92) + var_s6);
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) temp_final;
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x40);
    }
}
