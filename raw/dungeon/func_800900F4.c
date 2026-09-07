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

M2C_UNK func_80048A44(); /* extern */
M2C_UNK func_80094E34();                            /* extern */
M2C_UNK func_8009A21C();           /* extern */
M2C_UNK func_8009A3D0();           /* extern */
s32 func_8009B88C();   /* extern */
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80082EB0;
extern s16 D_80083228;
extern u8 D_800DD130;

s32 func_80095854(void *arg0_in, s32 arg1, void *arg2_in, s32 arg3_in) {
    s16 sp18;
    s16 sp1A;
    s16 sp1C;
    s16 sp1E;
    register void *arg0 ASM_REG("$16") = arg0_in;
    register void *arg2 ASM_REG("$18") = arg2_in;
    register s32 arg3 ASM_REG("$19") = arg3_in;
    register s32 var_s1 ASM_REG("$17");
    register s32 temp_cmp ASM_REG("$2");
    s32 temp_a2;
    s32 temp_shift;
    register s32 temp_s1 ASM_REG("$17");
    s8 temp_v0;
    void *temp_v1;

    var_s1 = 0;
    ASM_KEEP(arg0);
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);
    ASM_KEEP(var_s1);
    temp_v1 = M2C_FIELD(arg0, void **, 0x124);
    M2C_FIELD(arg0, s8 *, 0x9A) = 0x31;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    if (temp_v1 != NULL) {
        temp_cmp = M2C_FIELD(temp_v1, s8 *, 0x13);
        temp_cmp = temp_cmp > 0;
        ASM_KEEP(temp_cmp);
        var_s1 = temp_cmp;
    }
    func_80094E34();
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_800DD130;
    func_80048A44(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_800DD130), 0, 1);
    D_80082EB0 = arg3;
    temp_a2 = ((u16) M2C_FIELD(arg0, s16 *, 0x2A) >> 8) & 0xE;
    M2C_FIELD(arg0, s8 *, 0x72) = (s8) (M2C_FIELD(arg2, u8 *, 0x24) + *(temp_a2 + &D_8006CCD8));
    temp_v0 = M2C_FIELD(arg2, u8 *, 0x25) + *(temp_a2 + &D_8006CCE8);
    M2C_FIELD(arg0, s8 *, 0x73) = temp_v0;
    if ((func_8009B88C(0, M2C_FIELD(arg0, s8 *, 0x72), temp_v0, &sp18, &sp1A) << 0x10) != 0) {
        temp_cmp = var_s1 << 0x10;
        ASM_KEEP(temp_cmp);
        if (temp_cmp != 0) {
            func_8009A21C(sp18, sp1A, 0x8000);
            temp_s1 = func_8009B88C(0, M2C_FIELD(arg0, s8 *, 0x72), M2C_FIELD(arg0, s8 *, 0x73), &sp1C, &sp1E);
            ASM_KEEP(temp_s1);
            func_8009A3D0(sp18, sp1A, 0x8000);
            temp_shift = temp_s1 << 0x10;
            ASM_KEEP(temp_shift);
            ASM_CLOBBER("$17");
            if (temp_shift != 0) {
                M2C_FIELD(arg0, s8 *, 0x72) = (s8) (u8) sp1C;
                M2C_FIELD(arg0, s8 *, 0x73) = (s8) (u8) sp1E;
                return 1;
            }
            return 0;
        }
        M2C_FIELD(arg0, s8 *, 0x72) = (s8) (u8) sp18;
        M2C_FIELD(arg0, s8 *, 0x73) = (s8) (u8) sp1A;
        return 1;
    }
    return 0;
}
/* MECHANISM: Restored the dead ABI arg and pinned held roles for the exact s0/s2/s3/s1 prologue.
   Byte-typed globals removed fourfold index scaling; natural local-return CFG restored the tail.
   A split-scope s1 result plus post-shift s1 clobber preserved the v0 test and zero delay slot. */
