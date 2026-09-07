/* cfail-repair: tf7-phase1-cache-v3 */
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

s32 func_800374F4();                         /* extern */
M2C_UNK func_800C9ED0();                         /* extern */
M2C_UNK func_800C9ED4();                         /* extern */
extern void (*D_800D65D8[])(void *, void *, M2C_UNK);

void func_800C9DB8(void *arg0, void *arg1, M2C_UNK arg2) {
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_a0_3;
    s32 temp_v0_4;
    s32 temp_v1_4;
    register s32 temp_a0_4 ASM_REG("$4");
    s32 temp_v1;
    s32 var_s1;
    register s32 var_s2 ASM_REG("$18");
    register s32 tail_value ASM_REG("$2");

    var_s2 = 0x10;
    ASM_KEEP(var_s2);
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    ASM_SCHED_BARRIER();
    var_s2 -= 1;
loop_1:
    var_s1 = 0;
    if (var_s2 > 0) {
        var_s1 = func_800374F4(3) & 0xFFFF;
        if (var_s1 == 1) {
            temp_v1 = func_800374F4(4) & 0xFFFF;
            if (temp_v1 == 0) {
                temp_a0 = M2C_FIELD(arg0, s16 *, 0x8C);
                var_s2 -= 1;
                if (M2C_FIELD(arg1, s16 *, 2) < (M2C_FIELD(arg0, s16 *, 0x84) + temp_a0)) {
                    var_s2 += 1;
                    ASM_KEEP(var_s2);
                    tail_value = 0x400;
                    ASM_TAILSLOT_PIN_TIED(tail_value);
                    func_800C9ED0(temp_a0);
                    return;
                }
                goto loop_1;
            }
            if (temp_v1 == var_s1) {
                temp_a0_2 = M2C_FIELD(arg0, s16 *, 0x8E);
                var_s2 -= 1;
                if (M2C_FIELD(arg1, s16 *, 6) < (M2C_FIELD(arg0, s16 *, 0x86) + temp_a0_2)) {
                    var_s2 += 1;
                    ASM_KEEP(var_s2);
                    M2C_FIELD(arg0, s16 *, 0x72) = 0;
                    func_800C9ED4(temp_a0_2);
                    return;
                }
                goto loop_1;
            }
            if (temp_v1 == 2) {
                temp_a0_3 = M2C_FIELD(arg1, s16 *, 2);
                var_s2 -= 1;
                if ((M2C_FIELD(arg0, s16 *, 0x84) - M2C_FIELD(arg0, s16 *, 0x8C)) < temp_a0_3) {
                    var_s2 += 1;
                    ASM_KEEP(var_s2);
                    tail_value = 0xC00;
                    ASM_TAILSLOT_PIN_TIED(tail_value);
                    func_800C9ED0(temp_a0_3);
                    return;
                }
                goto loop_1;
            }
            temp_v0_4 = M2C_FIELD(arg0, s16 *, 0x86);
            temp_v1_4 = M2C_FIELD(arg0, s16 *, 0x8E);
            temp_a0_4 = M2C_FIELD(arg1, s16 *, 6);
            ASM_KEEP(temp_a0_4);
            var_s2 -= 1;
            if ((temp_v0_4 - temp_v1_4) < temp_a0_4) {
                var_s2 += 1;
                ASM_KEEP(var_s2);
                M2C_FIELD(arg0, s16 *, 0x72) = 0x800;
                goto block_17;
            }
            goto loop_1;
        }
        /* Duplicate return node #18. Try simplifying control flow for better match */
        goto block_17;
    }
block_17:
    {
        register void *call_arg0 ASM_REG("$4") = arg0;
        register void (**table)(void *, void *, M2C_UNK) ASM_REG("$2") = D_800D65D8;

        ASM_KEEP(call_arg0);
        ASM_KEEP(table);
        table[var_s1](call_arg0, arg1, arg2);
    }
}

/* MECHANISM: Retail separates the one-time preheader decrement from the loop
   target; later decrements occupy branch-back delay slots. A pinned s2 counter,
   split loads and a0/v0 dispatch bases hold its ABI; tied LEAD28 pins preserve
   the two dead v0 tail values, with the middle halfword store as its jump slot. */
