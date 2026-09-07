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

M2C_UNK func_80033CD8();           /* extern */
s32 func_8004A658();                          /* extern */
void *func_8009C390(); /* extern */
void func_800A8200(void) __attribute__((noreturn)); /* extern */
M2C_UNK func_800A8248();         /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006E240;
extern M2C_UNK D_800A8248;

void func_800A8184(s32 arg0, s32 arg1) {
    s32 temp_s3;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    register s32 held_arg1 ASM_REG("$18") = arg1;

    temp_v0 = func_8009C390(0, 0, &D_800A8248, 0);
    temp_s0 = temp_v0 + 0x20;
    if (temp_v0 != NULL) {
        temp_s3 = M2C_FIELD(temp_v0, s32 *, 8);
        temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, u8 *, 0x4C) = arg0;
        M2C_FIELD(temp_s0, u8 *, 0x4D) = held_arg1;
        if ((held_arg1 & 0xFF) == 0x12) {
            register u8 *dispatch_result ASM_REG("$2");

            dispatch_result = (u8 *)0x80070000;
            ASM_KEEP(dispatch_result);
            dispatch_result -= 0x1DC0;
            ASM_TAILSLOT_PIN(dispatch_result);
            func_800A8200();
            return;
        }
        M2C_FIELD(temp_s1, s32 *, 8) = func_8004A658(M2C_FIELD(temp_s0, u8 *, 0x4D), M2C_FIELD(temp_s0, u8 *, 0x4C));
        ASM_SCHED_BARRIER();
        func_80033CD8(temp_s0, &D_80045340);
        func_800A8248(temp_s0, temp_s3, temp_s1);
    }
    ASM_KEEP(held_arg1);
}
/* MECHANISM: The 0x28 frame and held s4/s2/s3/s1/s0 roles preserve the exact prologue and ABI lifetimes.
   A zero-word scheduling fence after the result store prevents delay-slot theft, keeping sw v0,8(s1)
   before call setup and allowing the D_80045340 low half to fill the following jal delay slot. */
