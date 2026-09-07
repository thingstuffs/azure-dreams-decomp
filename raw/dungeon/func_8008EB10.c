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
extern s32 D_80082EB0[];
extern s32 D_800E3DF0[];
s16 func_8009402C(); /* extern */
s32 func_80094208();                         /* extern */
M2C_UNK func_80094E34();                      /* extern */
s32 func_800990FC();                          /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                    /* extern */
s32 func_8009929C();                    /* extern */
s32 func_80099734();                        /* extern */
M2C_UNK func_800997FC();                   /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800A5720();                         /* extern */
extern M2C_UNK D_800E05E1;
extern M2C_UNK D_800E05F0;
extern M2C_UNK D_800E0633;
extern M2C_UNK D_800E0726;
extern M2C_UNK D_800E0739;
extern M2C_UNK D_800E0747;
extern M2C_UNK D_800E0766;
extern M2C_UNK D_800E0769;
extern M2C_UNK D_800E077C;
extern M2C_UNK D_800E078A;

s32 func_80094270(void *arg0, M2C_UNK arg1, M2C_UNK arg2, void *arg3, s32 arg4) {
    s16 sp18;
    s16 sp1A;
    s16 temp_v0;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s2;
    s32 call_result;
    void *temp_v1;
    M2C_UNK *hdr;
    register M2C_UNK *hdr3 ASM_REG("$4");
    register s32 call_a0 ASM_REG("$4");

    M2C_FIELD(arg0, s16 *, 0x8A) = (s16) arg4;
    if (func_80094208(0) == 0) {
        if (M2C_FIELD((arg0 + (s16) arg4), u8 *, 0xFA) == 2) {
            func_800997FC(&D_800E0633);
            return 1;
        }
        temp_v1 = (void *) ((M2C_FIELD(arg0, s16 *, 0x8A) * 4) + (u32) arg0);
        if (M2C_FIELD(temp_v1, s32 *, 0xD0) == arg3) {
            call_a0 = (s32) arg0;
            if (!(M2C_FIELD(M2C_FIELD(temp_v1, void **, 0xAC), s32 *, 0x1C) & 0x20000)) {
                /* retail: a single shared "jal func_80099194(hdr,.)" call is
                 * reached from BOTH arms of the (s16)arg4 check below (hdr
                 * chosen per arm, computed BEFORE the call, not two separate
                 * calls); the "-3" applies UNIFORMLY to the result regardless
                 * of which arm ran (it is the delay-slot arg-setup for the
                 * NEXT, D_800E0739 call, not part of either arm). This ending
                 * then jumps into the SAME shared func_80099290(temp_a1,
                 * temp_a1) / func_800A5720 / func_800A56E0 / "return 1" tail
                 * the temp_v0 dispatch below also reaches (retail has only
                 * ONE physical "jal func_80099290" instance for all four
                 * endings). Previously spelled as fake externs
                 * func_80094364()/func_800944CC() whose "return" never
                 * actually escaped the function -- the real control flow
                 * always ends in "return 1". */
                temp_s2 = func_800990FC(call_a0);
                temp_a1 = func_80099194(&D_800E0726, temp_s2);
                if (M2C_FIELD(arg0, s16 *, 0x8A) != 0) {
                    hdr = &D_800E05F0;
                } else {
                    hdr = &D_800E05E1;
                }
                temp_a1 = func_80099194(hdr, temp_a1);
                call_result = func_80099194(&D_800E0739, temp_a1 - 3);
                ASM_SET(temp_a1);
                call_a0 = call_result;
                goto call_290;
            }
            func_80094E34();
            *D_80082EB0 = 0;
            func_8008DB0C(arg0, arg1, arg2, 0, 0);
            M2C_FIELD(arg0, s32 *, 0x60) = 0;
            goto return_zero;
        }
        temp_v0 = func_8009402C(arg0, arg1, arg2, &sp18, &sp1A, arg3);
        call_a0 = (s32) arg0;
        if (temp_v0 != 0) {
            temp_s2 = func_800990FC(call_a0);
            if (temp_v0 == 1) {
                register s32 temp_bits ASM_REG("$2");
                register s32 *table_base ASM_REG("$4");
                register u32 table_entry ASM_REG("$3");

                temp_bits = M2C_FIELD(arg3, u8 *, 3) & 0x1F;
                ASM_KEEP_NV(temp_bits);
                temp_s0 = temp_bits & 0xFF;
                temp_a1 = func_80099194(&D_800E0747, temp_s2);
                temp_a1 = func_8009929C(0xA, temp_a1);
                table_base = D_800E3DF0;
                table_entry = temp_s0;
                table_entry <<= 2;
                table_entry += (u32) table_base;
                ASM_KEEP_NV(table_base);
                ASM_KEEP_NV(table_entry);
                call_result = func_80099734(*(s32 *) table_entry, temp_a1);
                hdr3 = &D_800E0766;
                goto use_result;
            }
            if (temp_v0 == 2) {
                temp_a1 = func_80099194(&D_800E0769, temp_s2);
                if ((s16) arg4 != 0) {
                    hdr = &D_800E05F0;
                } else {
                    hdr = &D_800E05E1;
                }
                temp_a1 = func_80099194(hdr, temp_a1);
                hdr3 = &D_800E077C;
                temp_a1 -= 3;
                goto call3;
            }
            call_result = func_80099734(D_800E3DF0[M2C_FIELD(arg3, u8 *, 3) & 0x1F], temp_s2);
            hdr3 = &D_800E078A;
        use_result:
            temp_a1 = call_result;
        call3:
            /* one physical "jal func_80099194(hdr3,.)" call shared by all
             * three arms above (each pre-selects hdr3 and temp_a1, then
             * merges here). */
            ASM_KEEP_NV(hdr3);
            temp_a1 = func_80099194(hdr3, temp_a1);
            call_a0 = temp_a1;
        call_290:
            /* one physical "jal func_80099290(temp_a1,temp_a1)" call shared
             * by ALL FOUR endings (the single-arg I-block ending above jumps
             * straight here too), followed by the shared finish tail. */
            func_80099290(call_a0, temp_a1);
        finish:
            func_800A5720(temp_s2);
            func_800A56E0(0x506);
            return 1;
        }
        M2C_FIELD(arg0, s32 *, 0xC8) = 0;
        *D_80082EB0 = (s32) arg3;
        func_8008DB0C(arg0, arg1, arg2, sp18, (s32) sp1A);
        func_80094E34();
    return_zero:
        return 0;
    }
    return 1;
}
