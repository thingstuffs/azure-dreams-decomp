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

extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_801588FC(void) __attribute__((noreturn));
extern u8 D_80083160[];

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80ADD000")
    __attribute__((section(".text.func_80ADD000"), aligned(4))) = {
    0x80159158, 0x80159320, 0x80159B54, 0x80159B54,
    0x80159B54, 0x80159B80, 0x80159B00, 0x80159B00,
    0x80159B00, 0x80159AAC, 0x80159AE4, 0x80159B80,
    0x80159B80, 0x80159B44, 0x8015B020, 0x8015B070,
    0x8015B0E4, 0x8015B158, 0x8015B1D0, 0x00000000,
    0x8015B29C, 0x8015B4CC, 0x8015B514, 0x8015B744,
    0x8015B7CC, 0x00000000, 0x8015B34C, 0x8015B344,
    0x8015B33C, 0x8015B354, 0x8015B2F8, 0x8015B2F0,
    0x8015B2E8, 0x00000001, 0x00010001, 0x00010000,
    0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000,
    0xFFFF0001,
};
__asm__(".globl func_80ADD000\n"
        ".size func_80ADD000, 644");
#define BODY_NAME func_80ADD0A4
#else
#define BODY_NAME func_80ADD000
#endif

s32 BODY_NAME(void *arg0, void *arg1) {
    register void *object ASM_REG("$19") = arg0;
    register void *input ASM_REG("$8") = arg1;
    void **global_slot = (void **)D_80083160;
    register void *ctx ASM_REG("$2") = *global_slot;
    register u32 low_mask ASM_REG("$18") = 0xFF0000;
    register u32 high_mask ASM_REG("$20");
    register u8 *scratch ASM_REG("$17");
    void *prim;
    u32 index;
    void *prim2;
    register void *node ASM_REG("$5");

    ASM_KEEP_NV(object);
    ASM_KEEP_NV(input);
    ASM_KEEP_NV(global_slot);
    ASM_KEEP_NV(low_mask);
    ASM_KEEP_DEP_NV(low_mask, ctx);
    low_mask |= 0xFFFF;
    ASM_KEEP_NV(ctx);
    ASM_KEEP_NV(low_mask);
    high_mask = 0xFF000000;
    ASM_KEEP_NV(high_mask);
    scratch = (u8 *)0x1F800000;
    ASM_KEEP_NV(scratch);
    FIELD(scratch, void *, 0x1C) = FIELD(ctx, void *, 0x8D0);
    FIELD(scratch, void *, 0x24) = (u8 *)ctx + 0xB0;
    ASM_SCHED_BARRIER();
    FIELD(scratch, u16, 4) = FIELD(input, u16, 2);
    prim = FIELD(scratch, void * volatile, 0x1C);
    FIELD(scratch, u16, 6) = FIELD(input, u16, 6);
    FIELD(scratch, u16, 8) = FIELD(input, u16, 0xA);
    FIELD(scratch, void *, 0x1C) = (u8 *)prim + 0xC;
    index = func_80065420(scratch + 4, (u8 *)prim + 8,
                          scratch + 0xD0, scratch + 0xD4);
    FIELD(scratch, u32, 0x100) = index;
    if (index < 0x1E0U) {
        FIELD(prim, s32, 4) = FIELD(object, s32, 8);
        FIELD(prim, u8, 3) = 2;
        {
            register u8 dead_read0 ASM_REG("$3");
            register u8 dead_read1 ASM_REG("$6");
            register u8 dead_read2 ASM_REG("$7");
            dead_read0 = FIELD(prim, volatile u8, 4);
            dead_read1 = FIELD(prim, volatile u8, 5);
            dead_read2 = FIELD(prim, volatile u8, 6);
        }
        FIELD(prim, u8, 7) = 0x6A;
        FIELD(prim, u32, 0) =
            (FIELD(prim, u32, 0) & high_mask) |
            (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                   FIELD(scratch, u32, 0x100) * 4) & low_mask);
        {
            register u32 *rmw_ptr ASM_REG("$7");
            rmw_ptr = (u32 *)((FIELD(scratch, u32, 0x100) << 2) +
                              (u32)FIELD(scratch, u32 *, 0x24));
            ASM_KEEP_NV(rmw_ptr);
            {
                register u32 rmw_value ASM_REG("$3");
                u32 prim_low;
                rmw_value = *rmw_ptr;
                prim_low = (u32)prim & low_mask;
                rmw_value &= high_mask;
                rmw_value |= prim_low;
                *rmw_ptr = rmw_value;
            }
        }
        prim2 = FIELD(scratch, void *, 0x1C);
        FIELD(scratch, void *, 0x1C) = (u8 *)prim2 + 0xC;
        func_80067F20(prim2, 0, 0,
                      func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
        FIELD(prim2, u32, 0) =
            (FIELD(prim2, u32, 0) & high_mask) |
            (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                   FIELD(scratch, u32, 0x100) * 4) & low_mask);
        FIELD(FIELD(scratch, u32 *, 0x24), u32,
              FIELD(scratch, u32, 0x100) * 4) =
            (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                   FIELD(scratch, u32, 0x100) * 4) & high_mask) |
            ((u32)prim2 & low_mask);
    }
    node = FIELD(object, void *, -8);
    if (node != NULL) {
        register void *tail_arg0 ASM_REG("$4");

        object = (u8 *)node + 0x20;
        input = FIELD(node, void *, 8);
        ASM_KEEP(object);
        ASM_KEEP(input);
        ASM_KEEP(scratch);
        ASM_KEEP(node);
        tail_arg0 = scratch + 4;
        ASM_TAILSLOT_PIN(tail_arg0);
        func_801588FC();
    }
    {
        register s32 hard_zero ASM_REG("$0");
        register s32 result ASM_REG("$2");

#ifdef NON_MATCHING
        hard_zero = 0;
#else
        ASM_SET(hard_zero);
#endif
        FIELD(*global_slot, void *, 0x8D0) = FIELD(scratch, void *, 0x1C);
        result = hard_zero;
        ASM_KEEP(result);
        return result;
    }
}
