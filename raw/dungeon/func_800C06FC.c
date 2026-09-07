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

typedef struct CounterBlock {
    u8 pad[0xA];
    u16 count;
} CounterBlock;

M2C_UNK func_8003DB94();        /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_80045C34;
extern CounterBlock D_80083460;
extern M2C_UNK D_800C5D80;

void func_800C5E5C(s16 arg0, s16 arg1, s16 arg2, s32 arg3, s16 arg4) {
    M2C_UNK var_a0;
    s32 var_s2;
    s32 var_s3;
    s32 var_s5;
    void *temp_s0;
    CounterBlock *temp_s4;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    register u16 temp_flags ASM_REG("$3");

    if (arg4 != 0) {
        func_800A56E0(0x816);
    }
    var_s2 = 0xB;
    var_s5 = 0x20;
    temp_s4 = &D_80083460;
    var_s3 = 0xFFFA0000;
    do {
        var_a0 = 0x12;
        if (var_s2 != 0) {
            var_a0 = 0x212;
        }
        temp_v0 = func_8003FC64(var_a0);
        if (temp_v0 != NULL) {
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800C5D80;
            func_8004491C(temp_v0, &D_80045C34);
            temp_v0_2 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_v0_2, s16 *, 2) = arg0;
            M2C_FIELD(temp_v0_2, s16 *, 6) = arg1;
            M2C_FIELD(temp_v0_2, s16 *, 0xA) = arg2;
            M2C_FIELD(temp_v0_2, s32 *, 0x14) = var_s3;
            temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
            func_8003DB94(temp_s0, arg3, 0);
            temp_flags = M2C_FIELD(temp_s0, u16 *, 0x14);
            {
                register s32 temp_color ASM_REG("$2");
                temp_color = 0x808080;
                M2C_FIELD(temp_s0, s32 *, 0xC) = temp_color;
                ASM_KEEP(temp_color);
            }
            {
                register s32 temp_1000 ASM_REG("$2");
                temp_1000 = 0x1000;
                M2C_FIELD(temp_s0, s16 *, 0x1E) = temp_1000;
                M2C_FIELD(temp_s0, s16 *, 0x1C) = temp_1000;
                ASM_KEEP(temp_1000);
            }
            temp_v0_3 = temp_v0 + 0x20;
            M2C_FIELD(temp_s0, s16 *, 0x10) = var_s5;
            temp_flags |= 0xC;
            M2C_FIELD(temp_s0, u16 *, 0x14) = temp_flags;
            ASM_KEEP(temp_flags);
            M2C_FIELD(temp_v0_3, s16 *, 0x10) = var_s5;
            M2C_FIELD(temp_v0_3, s16 *, 0xC) = var_s2;
            if (var_s2 == 0) {
                temp_s4->count = (u16) (temp_s4->count + 1);
            }
        }
        var_s3 += 0x8000;
        var_s2 -= 1;
    } while (var_s2 >= 0);
}

/* MECHANISM: An s32 loop counter removes the duplicate sign-extension live range and yields the retail 0x38 frame.
   A held CounterBlock base plus scoped v0/v1 locals reproduces the full-address and post-call register roles.
   Updating var_s3 before var_s2 places the 0x8000 materialization before the loop decrement. */
