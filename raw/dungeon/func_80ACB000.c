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

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))
#define SPAD_U16(off) (*(u16 *)(scratch + (off)))
#define SPAD_U32(off) (*(u32 *)(scratch + (off)))

extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_8016A8FC(void) __attribute__((noreturn));
extern void *D_80083160;

#ifdef __mips__
/* The row starts with a typed constant/jump table; the routine follows it. */
static const u32 func_80ACB000_table[41]
    __asm__("func_80ACB000")
    __attribute__((section(".text.func_80ACB000"), aligned(4))) = {
    0x8016B158U, 0x8016B320U, 0x8016BB54U, 0x8016BB54U,
    0x8016BB54U, 0x8016BB80U, 0x8016BB00U, 0x8016BB00U,
    0x8016BB00U, 0x8016BAACU, 0x8016BAE4U, 0x8016BB80U,
    0x8016BB80U, 0x8016BB44U, 0x8016D020U, 0x8016D070U,
    0x8016D0E4U, 0x8016D158U, 0x8016D1D0U, 0x00000000U,
    0x8016D29CU, 0x8016D4CCU, 0x8016D514U, 0x8016D744U,
    0x8016D7CCU, 0x00000000U, 0x8016D34CU, 0x8016D344U,
    0x8016D33CU, 0x8016D354U, 0x8016D2F8U, 0x8016D2F0U,
    0x8016D2E8U, 0x00000001U, 0x00010001U, 0x00010000U,
    0x0001FFFFU, 0x0000FFFFU, 0xFFFFFFFFU, 0xFFFF0000U,
    0xFFFF0001U,
};
__asm__(".globl func_80ACB000\n"
        ".type func_80ACB000,@function\n"
        ".size func_80ACB000, 644");
#define BODY_NAME composite_body_80ACB000
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_80ACB000")))
#else
#define BODY_NAME func_80ACB000
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE s32 BODY_NAME(void *arg0_in, void *arg1_in) BODY_ATTR;
BODY_STORAGE s32 BODY_NAME(void *arg0_in, void *arg1_in)
{
    u32 initial_cursor;
    u32 final_cursor;
    u32 temp_v0;
    void *final_base;
    void *temp_s0;
    void *temp_s0_2;
    void *next;
    register void *arg0_reg ASM_REG("$19") = arg0_in;
    register void *arg1_reg = arg1_in;
    register void **global ASM_REG("$21") = &D_80083160;
    register u32 low_mask ASM_REG("$18") = 0x00FFFFFFU;
    void *base = FIELD(&D_80083160, void *, 0);
    register u32 high_mask ASM_REG("$20") = 0xFF000000U;
    register u8 *scratch ASM_REG("$17") = (u8 *)0x1F800000;
    register s32 result ASM_REG("$2");

    ASM_KEEP(arg0_reg);
    ASM_KEEP(arg1_reg);
    ASM_KEEP(global);
    ASM_KEEP(high_mask);

    initial_cursor = FIELD(base, u32, 0x8D0);
    SPAD_U32(0x24) = (u32)base + 0xB0;
    FIELD(scratch, volatile u32, 0x1C) = initial_cursor;
    ASM_KEEP(scratch);
    SPAD_U16(4) = FIELD(arg1_reg, u16, 2);
    temp_s0 = (void *)FIELD(scratch, volatile u32, 0x1C);
    SPAD_U16(6) = FIELD(arg1_reg, u16, 6);
    SPAD_U16(8) = FIELD(arg1_reg, u16, 0xA);
    SPAD_U32(0x1C) = (u32)temp_s0 + 0xC;

    temp_v0 = func_80065420(scratch + 4, (u8 *)temp_s0 + 8,
                            scratch + 0xD0, scratch + 0xD4);
    ASM_KEEP(scratch);
    SPAD_U32(0x100) = temp_v0;
    if (temp_v0 < 0x1E0U) {
        register s32 call_zero ASM_REG("$4") = 0;
        register s32 call_one ASM_REG("$5") = 1;
        register u32 copied_word ASM_REG("$3") = FIELD(arg0_reg, u32, 8);
        register u32 marker ASM_REG("$2");
        ASM_KEEP(call_zero);
        ASM_KEEP(call_one);
        ASM_KEEP(copied_word);
        marker = 2;
        FIELD(temp_s0, u8, 3) = marker;
        marker = 0x6A;
        ASM_KEEP(marker);
        FIELD(temp_s0, u32, 4) = copied_word;
        {
            register u32 red ASM_REG("$3") = FIELD(temp_s0, volatile u8, 4);
            register u32 green ASM_REG("$6") = FIELD(temp_s0, volatile u8, 5);
            register u32 blue ASM_REG("$7") = FIELD(temp_s0, volatile u8, 6);
            ASM_KEEP(red);
            ASM_KEEP(green);
            ASM_KEEP(blue);
        }
        FIELD(temp_s0, u8, 7) = marker;
        FIELD(temp_s0, u32, 0) =
            (FIELD(temp_s0, u32, 0) & high_mask) |
            (*(u32 *)(SPAD_U32(0x24) + SPAD_U32(0x100) * 4) & low_mask);
        {
            register u32 *temp_a3 ASM_REG("$7");
            register u32 packed_word ASM_REG("$3");
            u32 low_bits;

            temp_a3 = (u32 *)(SPAD_U32(0x100) << 2);
            temp_a3 = (u32 *)((u32)temp_a3 + SPAD_U32(0x24));
            packed_word = *temp_a3;
            low_bits = (u32)temp_s0 & low_mask;
            packed_word &= high_mask;
            packed_word |= low_bits;
            *temp_a3 = packed_word;
        }

        temp_s0_2 = (void *)SPAD_U32(0x1C);
        SPAD_U32(0x1C) = (u32)temp_s0_2 + 0xC;
        func_80067F20(temp_s0_2, 0, 0,
                      func_80066460(call_zero, call_one, call_zero, call_zero) & 0xFFFF, 0);
        FIELD(temp_s0_2, u32, 0) =
            (FIELD(temp_s0_2, u32, 0) & high_mask) |
            (*(u32 *)(SPAD_U32(0x24) + SPAD_U32(0x100) * 4) & low_mask);
        {
            register u32 *temp_v1 ASM_REG("$3");

            temp_v1 = (u32 *)(SPAD_U32(0x100) << 2);
            temp_v1 = (u32 *)((u32)temp_v1 + SPAD_U32(0x24));
            *temp_v1 = (*temp_v1 & high_mask) | ((u32)temp_s0_2 & low_mask);
        }
    }

    next = FIELD(arg0_reg, void *, -8);
    if (next != 0) {
        register void *call_a0 ASM_REG("$4") = scratch + 4;

        arg0_reg = (u8 *)next + 0x20;
        arg1_reg = FIELD(next, void *, 8);
        ASM_KEEP(arg0_reg);
        ASM_KEEP(arg1_reg);
        ASM_TAILSLOT_PIN(call_a0);
        func_8016A8FC();
    }
    ASM_SCHED_BARRIER();
    final_base = *global;
    final_cursor = SPAD_U32(0x1C);
    ASM_SCHED_BARRIER();
    result = 0;
    ASM_KEEP(result);
    FIELD(final_base, u32, 0x8D0) = final_cursor;
    return result;
}
