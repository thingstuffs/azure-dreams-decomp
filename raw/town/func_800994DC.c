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

extern u8 D_800133A6;
extern s32 D_800FE508[4];
extern s32 D_800FE520[33];

void func_80096C3C(void) {
    register s32 c30000000 ASM_REG("$4");
    register s32 c065FFFFF ASM_REG("$5");
    register s32 cF0000000 ASM_REG("$7");
    register s32 c09EFFFFF ASM_REG("$8");
    register s32 *page ASM_REG("$2");
    register s32 *state ASM_REG("$6");
    register u8 *mode_page ASM_REG("$3");
    s32 *head;
    s32 temp_v0;
    s32 temp_v1;

    D_800FE508[0] = 0x025FFFFF;
    c065FFFFF = 0x065FFFFF;
    c09EFFFFF = 0x09EFFFFF;
    head = D_800FE508;
    head[2] = 0x01000000;
    head[1] = 0x1DA00000;
    head[3] = 0x1DA00000;
    ASM_SCHED_BARRIER();
#ifdef NON_MATCHING
    page = D_800FE520 + 1720;
#else
    page = (s32 *)0x80100000;
#endif
    ASM_KEEP(page);
    cF0000000 = 0xF0000000;
    state = page - 1720;
    page[-1720] = cF0000000;
    ASM_SCHED_BARRIER();
    temp_v0 = 0x0FE00000;
    temp_v1 = 0x04000000;
    state[1] = temp_v0;
    temp_v0 = 0x10200000;
    c30000000 = 0x30000000;
    state[4] = temp_v0;
    temp_v0 = 0x0F500000;
    state[9] = temp_v0;
    temp_v0 = 0x10B00000;
    state[12] = temp_v0;
    temp_v0 = 0x0F980000;
    state[3] = temp_v1;
    state[7] = temp_v1;
    temp_v1 = 0x05E80000;
    state[17] = temp_v0;
    temp_v0 = 0x10680000;
    state[20] = temp_v0;
    temp_v0 = 0x1A100000;
    state[2] = 0;
    state[5] = c30000000;
    state[6] = 0;
    state[8] = cF0000000;
    state[10] = 0;
    state[11] = c065FFFFF;
    state[13] = c30000000;
    state[14] = 0;
    state[15] = c065FFFFF;
    state[16] = cF0000000;
    ASM_KEEP(cF0000000);
    state[18] = temp_v1;
    state[19] = c065FFFFF;
    state[21] = c30000000;
    state[22] = temp_v1;
    state[23] = c065FFFFF;
    state[24] = temp_v0;
    state[25] = c30000000;
    ASM_KEEP(c30000000);
    state[26] = 0;
    state[27] = c09EFFFFF;
    ASM_KEEP(c065FFFFF);
    ASM_KEEP(c09EFFFFF);
#ifdef NON_MATCHING
    mode_page = &D_800133A6 - 0x33A6;
#else
    mode_page = (u8 *)0x80010000;
#endif
    ASM_KEEP(mode_page);
    if (mode_page[0x33A6] == 0xA) {
        state[29] = 0x05F00000;
        state[28] = cF0000000;
        state[30] = 0;
        state[31] = c09EFFFFF;
        state[32] = 0x80000000;
    } else {
        state[28] = 0x80000000;
    }
    ASM_KEEP(state);
}
