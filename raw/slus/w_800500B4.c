#include "common.h"

/* first_pass warm draft: compiles, best score 106 @ 2.7.2 */
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

void func_800500B4(void *arg0, void *arg1) {
    register void *pArg1 ASM_REG("$10");
    register s32 var_t1 ASM_REG("$9");
    register u8 *var_addr_a4 ASM_REG("$8");
    register s32 temp_a1 ASM_REG("$5");
    s32 temp_a1_2;
    s32 temp_v1_3;
    u8 temp_a1_3;
    u8 temp_v1_2;
    u8 var_v0;
    void *temp_a0;
    void *temp_v1;
    void *var_a2;
    void *var_a3;
    s32 var_divres;

    pArg1 = arg1;
    temp_a1 = M2C_FIELD(pArg1, s32 *, 0x18);
    var_divres = (s32) ((M2C_FIELD(pArg1, s32 *, 0x1C) - temp_a1) * (M2C_FIELD(pArg1, s32 *, 0x14) << 4)) / (s32) M2C_FIELD(pArg1, s32 *, 0x10);
    var_divres = var_divres - 0x28;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), void **, 4), s16 *, 0xA) = (s16) ((temp_a1 << 4) + var_divres);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), void **, 4), u16 *, 0xA) = (u16) M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), void **, 4), u16 *, 0xA);
    temp_v1 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(M2C_FIELD(temp_v1, void **, 8), s16 *, 8) = (s16) (M2C_FIELD(M2C_FIELD(temp_v1, void **, 4), u16 *, 0xA) - 2);
    temp_a1_2 = M2C_FIELD(pArg1, s32 *, 0x1C);
    var_t1 = 0;
    var_a3 = arg0;
    var_a2 = pArg1;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a3, void **, 0x20), void **, 8), s16 *, 4) = (s16) (-(temp_a1_2 << 9) - ((s32) ((temp_a1_2 - M2C_FIELD(pArg1, s32 *, 0x18)) * -(M2C_FIELD(pArg1, s32 *, 0x14) << 9)) / (s32) M2C_FIELD(pArg1, s32 *, 0x10)));
    do {
        var_addr_a4 = (u8 *) ((s8 *) var_a2 + 0xA4);
        temp_a1_3 = *var_addr_a4;
        if (var_t1 == M2C_FIELD(pArg1, s32 *, 0x1C)) {
            var_v0 = temp_a1_3 + ((s32) (8 - temp_a1_3) / (s32) ((M2C_FIELD(pArg1, s32 *, 0x10) - M2C_FIELD(pArg1, s32 *, 0x14)) + 1));
        } else {
            var_v0 = temp_a1_3;
            if (var_v0 != 0) {
                var_v0 -= 1;
            }
        }
        *var_addr_a4 = var_v0;
        temp_v1_2 = M2C_FIELD(var_a2, u8 *, 0xA4);
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a3, void **, 4), s8 **, 4), s16 *, 8) = (s16) temp_v1_2;
        var_t1 += 1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a3, void **, 0x28), s8 **, 4), s16 *, 8) = (s16) (temp_v1_2 + 0x1E);
        *M2C_FIELD(M2C_FIELD(var_a3, void **, 0x28), s8 **, 4) = (M2C_FIELD(var_a2, u8 *, 0xA4) * 5) + 0x58;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a3, void **, 0x28), s8 **, 4), s8 *, 1) = (s8) ((M2C_FIELD(var_a2, u8 *, 0xA4) * 5) + 0x58);
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a3, void **, 0x28), s8 **, 4), s8 *, 2) = (s8) ((M2C_FIELD(var_a2, u8 *, 0xA4) * 5) + 0x58);
        *M2C_FIELD(M2C_FIELD(var_a3, void **, 4), s8 **, 4) = (M2C_FIELD(var_a2, u8 *, 0xA4) * 5) + 0x58;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a3, void **, 4), s8 **, 4), s8 *, 1) = (s8) ((M2C_FIELD(var_a2, u8 *, 0xA4) * 5) + 0x58);
        temp_a0 = M2C_FIELD(var_a3, void **, 4);
        var_a3 += 4;
        M2C_FIELD(M2C_FIELD(temp_a0, void **, 4), s8 *, 2) = (s8) ((M2C_FIELD(var_a2, u8 *, 0xA4) * 5) + 0x58);
        var_a2 += 1;
    } while (var_t1 < 6);
    temp_v1_3 = M2C_FIELD(pArg1, s32 *, 0x14);
    if (temp_v1_3 < M2C_FIELD(pArg1, s32 *, 0x10)) {
        M2C_FIELD(pArg1, s32 *, 0x14) = (s32) (temp_v1_3 + 1);
    }
}
