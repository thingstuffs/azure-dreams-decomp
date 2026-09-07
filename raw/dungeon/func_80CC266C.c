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

void func_80047784(void *, u8, s32);
void *func_800A04F0(void *, u8, u8, s16);
s16 func_800A0818(u8, u8, u8, u8, s32 *);
s32 func_800A2C34(void *);
void func_800A9A0C(void *);
void func_80175E14(void *);
extern s16 D_80083228;
extern u8 D_80083460[];
extern u16 D_80083462;
extern u8 *D_800E3D7C;
extern u8 D_80176348[];

s32 func_80175E6C(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 sp18;
    s32 temp_a0;
    s32 var_s0;
    register s32 var_s1 ASM_REG("$17");
    s32 var_v0;
    void *temp_v0;
    void *temp_v0_2;
    register void *var_s2 ASM_REG("$18");
    register void *arg2p ASM_REG("$20");
    u8 *base;

    arg2p = arg2;
    ASM_KEEP_NV(arg2p);
    var_s2 = NULL;
    ASM_KEEP_NV(var_s2);
    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if ((D_80083462 & 0x2008) ||
        (var_s1 = (s32) var_s2, ((func_800A2C34(arg3) << 0x10) != 0))) {
        goto return_minus_1;
    }
    var_s0 = 0;
    goto after_minus_1;
return_minus_1:
    ASM_SCHED_BARRIER();
    var_v0 = -1;
    goto return_label;
after_minus_1:
loop_5:
    temp_v0 = func_800A04F0(arg3, M2C_FIELD(arg2p, u8 *, 0x24), M2C_FIELD(arg2p, u8 *, 0x25), (s16) (var_s0 << 9));
    if (temp_v0 != NULL) {
        if (temp_v0 == D_800E3D7C) {
            var_s1 = 1;
            goto block_12;
        }
        temp_a0 = M2C_FIELD(temp_v0, s32 *, 0x14);
        if (temp_a0 & 0x4000) {
            if (!(temp_a0 & 0x20000000)) {
                var_s2 = temp_v0;
            }
        }
        goto block_12;
    }
block_12:
    var_s0 += 1;
    if (var_s0 >= 8) {
        if ((var_s2 != NULL) && (var_s1 & 0xFFFF)) {
            base = D_80083460;
            ASM_KEEP(var_s1);
            M2C_FIELD(base, u16 *, 0xA) = (u16) (M2C_FIELD(base, u16 *, 0xA) + 1);
            M2C_FIELD(arg3, void **, 0x60) = var_s2;
            func_800A9A0C(var_s2);
            M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
            M2C_FIELD(arg0, s8 *, 0x9B) = 0;
            M2C_FIELD(arg0, s32 *, 0x8C) = 0;
            temp_v0_2 = M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), void **, -0x14);
            M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2p, u8 *, 0x24), M2C_FIELD(arg2p, u8 *, 0x25), M2C_FIELD(temp_v0_2, u8 *, 0x24), M2C_FIELD(temp_v0_2, u8 *, 0x25), &sp18);
            M2C_FIELD(arg2p, u8 **, 0x2C) = D_80176348;
            func_80047784(arg2p, D_80176348[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
            func_80175E14(arg3);
            var_v0 = 1;
            goto return_label;
        }
        var_v0 = 0;
        goto return_label;
    }
    goto loop_5;
return_label:
    return var_v0;
}
