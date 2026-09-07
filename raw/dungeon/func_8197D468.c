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

/* cfail-repair: tf7-phase1-cache-v3 */
extern u16 D_8008378A;
extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_800DED70[];
extern s32 D_800814A0;
void func_80025050(void) __attribute__((noreturn)); /* extern */
void *func_8003FD64();                 /* extern */
s32 func_80069EF8();                          /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80024BB8;
extern M2C_UNK D_800DE990;

void func_8197D468(void *arg0, void *arg1, void *arg2) {
    s16 temp_v1;
    s16 temp_v0_5;
    s32 var_s3;
    s32 temp_v0_7;
    s32 random_value_0;
    s32 velocity_0;
    s32 random_value_2;
    s32 velocity_2;
    u16 temp_v0_3;
    register u16 temp_v1_2 ASM_REG("$3");
    register s32 temp_a0_5 ASM_REG("$4");
    void *temp_a0_4;
    register void *temp_v0_4 ASM_REG("$2");
    void *temp_s0;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v0, u16 *, 0x52) = (u16) (M2C_FIELD(temp_v0, u16 *, 0x52) | 0x8000);
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        M2C_FIELD(arg2, s8 *, 4) = 0;
        M2C_FIELD(arg2, s8 *, 5) = 0;
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0x9FFF);
    }
    func_800478B8(arg2);
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x4C);
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state_0;
        }
        ASM_SCHED_BARRIER();
        func_80025050();
    }
    ASM_SCHED_BARRIER();
    if (temp_v1 == 2) {
        goto state_2;
    }
    ASM_MEM_BARRIER();
    func_80025050();

state_0:
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
        random_value_0 = func_80069EF8();
        velocity_0 = M2C_FIELD(arg1, s32 *, 0x14) + 0x1A000;
        velocity_0 += random_value_0 >> 1;
        M2C_FIELD(arg1, s32 *, 0x14) = velocity_0;
        if ((u8) M2C_FIELD(arg2, u8 *, 0xC) < 0x40) {
            M2C_FIELD(arg2, s32 *, 0xC) = (s32) ((s32) M2C_FIELD(arg2, s32 *, 0xC) + 0x40404);
        }
        if (M2C_FIELD(arg1, s32 *, 0x14) > 0) {
            M2C_FIELD(arg2, M2C_UNK **, 0) = &D_800DE990;
            temp_a0_4 = (void *) M2C_FIELD(&D_800DE990, void **, 4);
            ASM_KEEP(temp_a0_4);
            temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
            ASM_KEEP(temp_v1_2);
            M2C_FIELD(arg2, s8 *, 4) = 0;
            M2C_FIELD(arg2, s8 *, 5) = 0;
            M2C_FIELD(arg2, u16 *, 0x1E) = 0x400U;
            M2C_FIELD(arg2, u16 *, 0x1C) = 0x400U;
            M2C_FIELD(arg2, s16 *, 0x10) = 0;
            ASM_SCHED_BARRIER();
            M2C_FIELD(arg2, void **, 8) = temp_a0_4;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (temp_v1_2 | 2);
            M2C_FIELD(arg0, u16 *, 0x48) = (u16) ((func_80069EF8(temp_a0_4) & 3) + 4);
            M2C_FIELD(arg0, u16 *, 0x4C) = (u16) (M2C_FIELD(arg0, u16 *, 0x4C) + 1);
            func_80025050();
        }
        goto done;

state_1:
        M2C_FIELD(arg2, s32 *, 0xC) = 0x606060;
        M2C_FIELD(arg2, u16 *, 0x1C) = (u16) (M2C_FIELD(arg2, u16 *, 0x1C) + 0xC8);
        M2C_FIELD(arg2, u16 *, 0x1E) = (u16) (M2C_FIELD(arg2, u16 *, 0x1E) + 0xC8);
        temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x48) - 1;
        M2C_FIELD(arg0, u16 *, 0x48) = temp_v0_3;
        if ((temp_v0_3 << 0x10) <= 0) {
            M2C_FIELD(arg0, u16 *, 0x4C) = (u16) (M2C_FIELD(arg0, u16 *, 0x4C) + 1);
            func_80025050();
        }
        goto done;

state_2:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
            M2C_FIELD(arg2, M2C_UNK **, 0) = &D_800DE990;
            temp_v0_4 = (void *) M2C_FIELD(&D_800DE990, void **, 4);
            ASM_KEEP(temp_v0_4);
            M2C_FIELD(arg2, s8 *, 4) = 0;
            M2C_FIELD(arg2, s8 *, 5) = 0;
            M2C_FIELD(arg2, void **, 8) = temp_v0_4;
        }
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
        random_value_2 = func_80069EF8();
        velocity_2 = M2C_FIELD(arg1, s32 *, 0x14) + 0x1C000;
        velocity_2 += random_value_2 >> 1;
        M2C_FIELD(arg1, s32 *, 0x14) = velocity_2;
        if ((u8) M2C_FIELD(arg2, u8 *, 0xC) < 0x80) {
            M2C_FIELD(arg2, s32 *, 0xC) = (s32) ((s32) M2C_FIELD(arg2, s32 *, 0xC) + 0x40404);
        }
        temp_v0_5 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (D_8008378A - 0x80));
        if (M2C_FIELD(arg1, s16 *, 0xA) >= (temp_v0_5 - 0x20)) {
            var_s3 = 4;
            do {
                temp_v0_2 = func_8003FD64(0x312, D_80083498);
                if (temp_v0_2 != NULL) {
                    M2C_FIELD(temp_v0_2, M2C_UNK **, 0x10) = &D_80024BB8;
                    func_8004491C(temp_v0_2, D_80045340);
                    temp_s0 = M2C_FIELD(temp_v0_2, void **, 0xC);
                    M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA));
                    M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA));
                    M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA));
                    M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s32 *, 0xC) = (s32) (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA);
                    M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s32 *, 0x10) = (s32) (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xA);
                    M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s32 *, 0x14) = (s32) (0 - ((func_80069EF8() & 0x3FF) << 8));
                    temp_a0_5 = 0xC00000;
                    ASM_KEEP(temp_a0_5);
                    M2C_FIELD(temp_s0, s16 *, 0x1E) = 0xC00;
                    M2C_FIELD(temp_s0, s16 *, 0x1C) = 0xC00;
                    M2C_FIELD(temp_s0, s16 *, 0x10) = 0x20;
                    M2C_FIELD(temp_s0, u8 **, 0) = D_800DED70;
                    M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
                    temp_v0_7 = M2C_FIELD(D_800DED70, s32 *, 4);
                    ASM_KEEP(temp_v0_7);
                    temp_a0_5 |= 0x6060;
                    ASM_KEEP(temp_a0_5);
                    M2C_FIELD(temp_s0, s8 *, 4) = 0;
                    M2C_FIELD(temp_s0, s8 *, 5) = 0;
                    M2C_FIELD(temp_s0, s32 *, 0xC) = temp_a0_5;
                    M2C_FIELD(temp_s0, s32 *, 8) = temp_v0_7;
                    temp_v0_4 = M2C_FIELD(arg0, void **, 0);
                    ASM_KEEP(temp_v0_4);
                    ASM_SCHED_BARRIER();
                    M2C_FIELD(temp_v0_2, void **, 0x20) = temp_v0_4;
                    temp_v0_4 = temp_v0_2 + 0x20;
                    ASM_KEEP(temp_v0_4);
                    M2C_FIELD(temp_v0_4, s16 *, 0x4C) = 0;
                }
                var_s3 -= 1;
            } while (var_s3 >= 0);
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            D_800814A0 |= 0x8000;
        }
done:
    return;
}
