#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800287A4.h"
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

s32 func_80042900();                 /* extern */
s32 func_800A6D30(void); /* Retail RNG at 0x800A6D30 reads no argument registers, including $a3. */
M2C_UNK func_800CB82C();         

typedef struct S_8009D218_1_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_8009D218_1_pre;   /* the 0x18 bytes before arg0 in func_8009D218, addressed as arg0[-1] */


/* extern */

s32 func_8009D218(void *arg0, s32 arg1, Rec_D_800287A4 *arg2) {
    u8 *temp_v0;

    if (!(arg1 & 8) && (arg2 != NULL)) {
        if (arg1 & 1) {
            if (((func_80042900(arg0, 0x16) << 0x10) != 0) && (arg2->unk_13 >= 0)) {
                ASM_MEM_BARRIER(); /* MATCH: distinct barriers keep the first two success paths from cross-jump merging. */
                goto block_22;
            }
            goto block_17;
        }
        if (arg1 & 2) {
            if ((((func_80042900(arg0, 0x16) << 0x10) != 0) || ((func_80042900(arg0, 0x17) << 0x10) != 0)) && (arg2->unk_13 >= 0)) {
                ASM_SCHED_BARRIER(); /* MATCH: prevents merging this condition tail with the arg1 & 4 path. */
                goto block_22;
            }
            goto block_17;
        }
        if (!(arg1 & 4) || (((func_80042900(arg0, 0x16) << 0x10) == 0) && ((func_80042900(arg0, 0x15) << 0x10) == 0)) || (arg2->unk_13 < 0)) {
block_17:
            if (arg2 != NULL) {
                temp_v0 = ((Rec_D_800E3D7C *)arg0)->unk_50.at00_pu8.v;
                if (temp_v0 != NULL) {
                    if ((*temp_v0 == 3) && (arg2->unk_13 >= 0) && (func_800A6D30() & 3)) {
                        /* Duplicate return node #22. Try simplifying control flow for better match */
                        func_800CB82C(((S_8009D218_1_pre *)arg0)[-1].unk_00, arg0, arg2);
                        return 1;
                    }
                    /* Duplicate return node #25. Try simplifying control flow for better match */
                    return 0;
                }
                goto block_24;
            }
            /* Duplicate return node #25. Try simplifying control flow for better match */
            return 0;
        }
block_22:
        func_800CB82C(((S_8009D218_1_pre *)arg0)[-1].unk_00, arg0, arg2);
        return 1;
    }
block_24:
    return 0;
}

/* MECHANISM (byte-exact @ 2.7.2, dungeon overlay)
 * 1. IMPLICIT $a0 PASSTHROUGH: the first func_80042900 site is spelled
 *    func_80042900(arg0, 0x16) like the other three -- NOT m2c's one-arg
 *    func_80042900((void*)0x16). It sits in the ENTRY extended basic block, so
 *    cse still knows $a0 == arg0 and deletes the `move a0,s0` copy; retail's
 *    jal delay slot therefore carries `addiu a1,zero,0x16` (word 13) while the
 *    three later sites (all branch targets, cse reset) keep their `move a0,s0`.
 * 2. LEAD-22 SHAPE-C TAIL: func_8009D368 is declared VOID and the arm is spelled
 *    as two plain calls + a bare `return 1;` (never `return func_8009D368();`).
 *    Both callees are in config/sibcall_syms.dungeon.txt, so maspsx rewrites the
 *    shared-epilogue jal->j and relocates `addiu v0,zero,1` into the converted
 *    `j func_8009D368` delay slot (word 82) -- the func_800C7C24 spelling.
 * 3. ONE-SIDED ASM_MEM_BARRIER after the FIRST `return func_8009D34C();` arm
 *    defeats -O2 cross-jump merging of the two identical `j 8009d34c; nop` tail
 *    sites (words 21 and 39) so both survive; the arg1&4 arm's `bgez -> 7bec`
 *    keeps the two func_800CB82C/func_8009D368 tails legitimately merged.
 */
