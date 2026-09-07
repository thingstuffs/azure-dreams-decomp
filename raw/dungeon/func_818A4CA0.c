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

void func_80024650(void) __attribute__((noreturn)); /* extern */
M2C_UNK func_8003DB94(); /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80024340;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DECF8;

s32 func_818A4CA0(void *arg0, void *arg1, s16 arg2, s16 arg3) {
    register s32 result ASM_REG("$2");
    s16 temp_s0_2;
    u16 temp_v1;
    s32 shifted_arg3;
    s32 temp_v0_2;
    s32 var_s0;
    void *callback;
    void *temp_s0;
    void *temp_s3;
    register void *temp_v0 ASM_REG("$18");

    temp_v0 = func_8003FC64(0x212);
    ASM_KEEP(temp_v0);
    if (temp_v0 != NULL) {
        callback = &D_80024340;
        ASM_KEEP(callback);
        M2C_FIELD(temp_v0, void **, 0x20) = arg0;
        arg0 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, void **, 0x10) = callback;
        M2C_FIELD(arg0, s16 *, 4) = arg2;
        M2C_FIELD(arg0, s16 *, 6) = (s16) (-6 - (rand() % 5));
        M2C_FIELD(arg0, u16 *, 8) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(arg0, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 6);
        M2C_FIELD(arg0, u16 *, 0xC) = (u16) (M2C_FIELD(arg1, u16 *, 0xA) + 0x20);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, s8 *, 0xE) = 0x60;
        M2C_FIELD(temp_s0, s8 *, 0xD) = 0x60;
        M2C_FIELD(temp_s0, s8 *, 0xC) = 0x60;
        M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7E07;
        M2C_FIELD(temp_s0, u16 *, 0x10) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x10) | 0x60);
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0x100);
        shifted_arg3 = (s32)arg3 << 0x10;
        func_8003DB94(temp_s0, &D_800DECF8, (s16) ((shifted_arg3 >> 0x10) % 5), shifted_arg3 >> 0x1F);
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
        func_8004491C(temp_v0, &D_80045340);
        temp_s3 = M2C_FIELD(temp_v0, void **, 8);
        temp_v0_2 = rand();
        var_s0 = temp_v0_2;
        if (temp_v0_2 < 0) {
            var_s0 = temp_v0_2 + 0xFFF;
        }
        temp_s0_2 = temp_v0_2 - ((var_s0 >> 0xC) << 0xC);
        M2C_FIELD(temp_s3, s16 *, 2) = (s16) (M2C_FIELD(arg0, u16 *, 8) + ((s32) (func_800644B8(temp_s0_2) * 2) >> 8));
        M2C_FIELD(temp_s3, s16 *, 6) = (s16) (M2C_FIELD(arg0, u16 *, 0xA) + ((s32) (func_80064584(temp_s0_2) * 2) >> 8));
        ASM_SCHED_BARRIER();
        temp_v1 = M2C_FIELD(arg0, u16 *, 0xC);
        ASM_KEEP(temp_v1);
        result = (s32)temp_v0;
        ASM_KEEP(result);
        M2C_FIELD(temp_s3, s16 *, 0xA) = (s16)temp_v1;
        func_80024650();
    }
    ASM_CLOBBER("$18");
    result = 0;
    ASM_KEEP(result);
    return result;
}

/* MECHANISM: Reuse arg0 as the +0x20 base and pin only the allocated object in s2,
   giving the retail 0x28 frame and saved-role order; split shifted arg3 drives a3/a2.
   Value fences place the callback low half and tail lhu/move, while noreturn LEAD 18
   plus the failure-only s2 clobber preserves the object tail return and literal zero. */
