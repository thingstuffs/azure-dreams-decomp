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

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern s32 D_80013630;
extern s32 D_80013634;
extern M2C_UNK D_8001363C;
extern M2C_UNK D_8009E038;
extern M2C_UNK D_8009E798;
extern M2C_UNK D_800DD7E0;
extern M2C_UNK D_800E296C;

void func_8009ED30(void) {
    void *temp_v0;

    if (!(D_800E296C & 0x80)) {
        temp_v0 = func_8003FC64(0x12);
        if (temp_v0 != NULL) {
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8009E038;
            func_8004491C(temp_v0, &D_8009E798);
            {
            u16 temp_a1;
            register void *temp_a0 ASM_REG("$4");
            register void *temp_a2 ASM_REG("$6");
            register s32 temp_a3 ASM_REG("$7");
            register void *temp_page ASM_REG("$2");
            register void *temp_v1 ASM_REG("$3");

            temp_a2 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_a2, s16 *, 0xA) = -1;
            temp_v1 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_v1, s16 *, 0x14) = 0xC;
            M2C_FIELD(temp_v1, M2C_UNK **, 8) = &D_800DD7E0;
            ASM_SCHED_BARRIER();
            temp_page = (void *) 0x80010000;
            M2C_FIELD(temp_v1, s16 *, 0x1E) = 0;
            M2C_FIELD(temp_v1, s16 *, 0x1C) = 0;
            temp_a1 = M2C_FIELD(temp_page, u16 *, 0x363C);
            temp_a0 = temp_v0 + 0x20;
            M2C_FIELD(temp_a0, u16 *, 0x1E) = temp_a1;
            temp_a1 = M2C_FIELD(temp_page, u16 *, 0x3638);
            M2C_FIELD(temp_a2, u16 *, 2) = temp_a1;
            M2C_FIELD(temp_a0, u16 *, 0x14) = temp_a1;
            M2C_FIELD(temp_a2, u16 *, 6) = M2C_FIELD(temp_page, u16 *, 0x363A);
            M2C_FIELD(temp_a0, u16 *, 0x16) = M2C_FIELD(temp_page, u16 *, 0x363A);
            M2C_FIELD(temp_a0, s16 *, 0x1A) = 0x10;
            M2C_FIELD(temp_a0, s16 *, 0x1C) = 8;
            temp_a3 = 0x808080;
            M2C_FIELD(temp_v1, s32 *, 0xC) = temp_a3;
            ASM_SCHED_BARRIER();
            temp_page = (void *) D_80013630;
            M2C_FIELD(temp_v1, s16 *, 0x18) = 0;
            M2C_FIELD(temp_v1, s16 *, 0x16) = 0;
            M2C_FIELD(temp_v1, s16 *, 0x18) = 0;
            M2C_FIELD(temp_v1, s16 *, 0x16) = 0;
            M2C_FIELD(temp_a0, s32 *, 4) = (s32) temp_page;
            M2C_FIELD(temp_a0, s32 *, 0xC) = (s32) temp_page;
            temp_page = (void *) D_80013634;
            M2C_FIELD(temp_a0, s16 *, 0x18) = 0;
            M2C_FIELD(temp_a0, s32 *, 8) = (s32) temp_page;
            M2C_FIELD(temp_a0, s32 *, 0x10) = (s32) temp_page;
            temp_v1 = (void *) D_800E296C;
            temp_page = (void *) 4;
            M2C_FIELD(temp_a0, s16 *, 0x1C) = (s16) (s32) temp_page;
            D_800E296C = (s32) temp_v1 | 0x80;
            }
        }
    }
}

/* MECHANISM: Direct D_800E296C RMW holds its page in s1, producing the 0x20 frame and retail save order.
   Post-call caller-register roles hold the 0x8001 page in v0, child/secondary/subobject in a2/v1/a0,
   and color in a3; reusing dead v0/v1 for the two globals, literal 4, and flag reload removes the tail nop. */
