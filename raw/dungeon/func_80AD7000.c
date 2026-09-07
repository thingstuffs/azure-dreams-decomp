/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_8015E8FC(void) __attribute__((noreturn));
extern u8 D_80083160[];

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

#ifdef __mips__
static const u32 prefix_words[] __asm__("func_80AD7000")
    __attribute__((section(".text.func_80AD7000"), aligned(4))) = {
    0x8015F158, 0x8015F320, 0x8015FB54, 0x8015FB54,
    0x8015FB54, 0x8015FB80, 0x8015FB00, 0x8015FB00,
    0x8015FB00, 0x8015FAAC, 0x8015FAE4, 0x8015FB80,
    0x8015FB80, 0x8015FB44, 0x80161020, 0x80161070,
    0x801610E4, 0x80161158, 0x801611D0, 0x00000000,
    0x8016129C, 0x801614CC, 0x80161514, 0x80161744,
    0x801617CC, 0x00000000, 0x8016134C, 0x80161344,
    0x8016133C, 0x80161354, 0x801612F8, 0x801612F0,
    0x801612E8, 0x00000001, 0x00010001, 0x00010000,
    0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000,
    0xFFFF0001,
};
__asm__(".globl func_80AD7000\n"
        ".size func_80AD7000, 644");
#define BODY_NAME func_80AD70A4
#else
#define BODY_NAME func_80AD7000
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
        func_8015E8FC();
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
