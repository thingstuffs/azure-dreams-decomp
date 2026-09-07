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
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
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
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern struct S_8003E2D8 D_80083160_init __asm__("D_80083160");
extern struct S_8003E2D8 D_80083160_alloc __asm__("D_80083160");
extern struct S_8003E2D8 D_80083160_link __asm__("D_80083160");
extern struct S_8003E2D8 D_80083160_final __asm__("D_80083160");
s32 func_80065420();
s32 func_80066460();
M2C_UNK func_80066640();
M2C_UNK func_80066708();
M2C_UNK func_80067F20();

typedef struct {
    M2C_UNK *p28;
    M2C_UNK *p2C;
    s16 p30;
    s16 p32;
    s16 p34;
    s16 pad36;
    M2C_UNK p38;
    M2C_UNK p3C;
    s16 p40;
    s16 p42;
    s16 pad44;
    s16 pad46;
    s16 p48;
    s16 p4A;
    s32 p4C;
    void *volatile p50;
    s32 *p54;
    s8 *volatile p58;
} LocalRecord;

typedef struct {
    s8 work[16];
    LocalRecord record;
} LocalFrame;

typedef struct {
    s16 value;
    s16 zero2;
    s16 zero4;
    s16 pad6;
} WorkCell;

struct PackedPair {
    s32 first;
    s32 second;
} __attribute__((packed));
typedef struct PackedPair PackedPair;

struct PackedWord {
    s32 value;
} __attribute__((packed));
typedef struct PackedWord PackedWord;

s32 func_80F90E88(void *arg0) {
    LocalFrame frame;
    register s32 var_s2 ASM_REG("$18");
    register s32 var_s3 ASM_REG("$19");
    register s32 mask_all ASM_REG("$22");
    s32 mask_high;
    s32 *temp_s0;
    s32 *temp_s0_2;
    register s32 temp_a0 ASM_REG("$4");
    register s32 temp_a0_2 ASM_REG("$4");
    register s32 temp_s4 ASM_REG("$20");
    s32 temp_s5;
    s32 temp_v0;
    s32 temp_v0_2;
    register s32 var_a0 ASM_REG("$4");
    register s32 var_s1 ASM_REG("$17");
    register s8 *global_base ASM_REG("$8");
    register u32 temp_s7 ASM_REG("$23");
    register void *temp_a0_3 ASM_REG("$4");
    register WorkCell *var_v0 ASM_REG("$2");
    register s32 initial_value ASM_REG("$3");
    register s32 negative_value ASM_REG("$4");
    register void *db_arg ASM_REG("$4");
    register u16 global_value ASM_REG("$2");
    register s32 copy0 ASM_REG("$2");
    register s32 copy1 ASM_REG("$3");
    register s8 *stack_base ASM_REG("$29");
    register s32 mask_low ASM_REG("$8");
    register s32 bound_s ASM_REG("$4");
    register u32 bound_u ASM_REG("$3");
    register s32 call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");
    register s32 *call_a2 ASM_REG("$6");
    register s32 compare_result ASM_REG("$2");
    register u32 shifted_bound ASM_REG("$2");
    register s32 average_s2 ASM_REG("$3");
    register s32 average_s3 ASM_REG("$2");
    register s32 average_result ASM_REG("$3");
    register u16 center_value ASM_REG("$2");
    register s32 final_mask ASM_REG("$5");
    register s32 link_global ASM_REG("$3");
    register s32 link_object ASM_REG("$2");
    register s32 final_global ASM_REG("$2");
    register s32 final_object ASM_REG("$3");

#define sp18 frame.work[0]
#define sp28 frame.record.p28
#define sp2C frame.record.p2C
#define sp30 frame.record.p30
#define sp32 frame.record.p32
#define sp34 frame.record.p34
#define sp38 frame.record.p38
#define sp3C frame.record.p3C
#define sp40 frame.record.p40
#define sp42 frame.record.p42
#define sp44 frame.record.pad44
#define sp46 frame.record.pad46
#define sp48 frame.record.p48
#define sp4A frame.record.p4A
#define sp4C frame.record.p4C
#define sp50 frame.record.p50
#define sp54 frame.record.p54
#define sp58 frame.record.p58

    global_base = &sp18;
    ASM_KEEP_NV(global_base);
    sp58 = global_base;
    global_base = (s8 *) &sp4C;
    ASM_KEEP_NV(global_base);
    mask_all = 0x00FFFFFF;
    sp54 = (s32 *) global_base;
loop_entry:
    global_base = (s8 *) arg0;
    ASM_KEEP_NV(global_base);
    sp4C = 8;
    initial_value = (u16) sp4C;
    var_s1 = 1;
    sp50 = global_base;
    global_base = sp58;
    ASM_KEEP_NV(global_base);
    negative_value = 0 - initial_value;
    ASM_CLOBBER("$2");
    var_v0 = (WorkCell *) (global_base + 8);
    ASM_KEEP4_NV(var_v0, initial_value, negative_value, var_s1);
    do {
        var_v0->value = initial_value;
        if (var_s1 != 0) {
            var_v0->value = negative_value;
        }
        var_v0->zero4 = 0;
        var_v0->zero2 = 0;
        ASM_SCHED_BARRIER();
        var_s1 -= 1;
        var_v0 -= 1;
    } while (var_s1 >= 0);
    db_arg = &sp28;
    ASM_KEEP_NV(db_arg);
    var_s3 &= 0xFFFF;
    var_s2 &= 0xFFFF;
    global_base = (s8 *) &D_80083160_init;
    ASM_KEEP_NV(global_base);
    global_value = M2C_FIELD(global_base, u16 *, 0xC8);
    ASM_KEEP_NV(global_value);
    global_base = sp58;
    ASM_KEEP_NV(global_base);
    var_s1 = 1;
    sp32 = 0;
    sp30 = 0;
    ASM_SCHED_BARRIER();
    sp28 = (M2C_UNK *) global_base;
    sp2C = (M2C_UNK *) global_base;
    global_base = (s8 *) sp50;
    ASM_KEEP_NV(global_base);
    sp34 = 0 - global_value;
    copy0 = ((PackedWord *) (global_base + 0xC))->value;
    copy1 = ((PackedWord *) (global_base + 0x10))->value;
#ifdef NON_MATCHING
    stack_base = (s8 *) &sp38 - 0x38;
#else
    ASM_UNDEF(stack_base);
#endif
    ((PackedWord *) (stack_base + 0x38))->value = copy0;
    ((PackedWord *) (stack_base + 0x3C))->value = copy1;
    ASM_SCHED_BARRIER();
    sp40 = 2;
    sp42 = 0;
    func_800DBA90(db_arg);
    var_s3 |= 0x75300000;
    mask_low = 0xFFFF0000;
    ASM_USE_NV(mask_low);
    var_s3 &= mask_low;
    var_s3 |= 0x7530;
    var_s2 |= 0x8AD00000;
    var_s2 &= mask_low;
    var_s2 |= 0x8AD0;
    do {
        call_a0 = var_s1 * 8;
        call_a1 = &sp48;
        global_base = sp58;
        ASM_KEEP_NV(global_base);
        call_a2 = sp54;
        ASM_USE2_NV(call_a0, call_a1);
        ASM_USE_NV(call_a2);
        call_a0 = (s32) global_base + call_a0;
        temp_s7 = func_80065420(call_a0, call_a1, call_a2, call_a2) - 4;
        ASM_KEEP_NV(temp_s7);
        compare_result = (s16) var_s2;
        ASM_KEEP_NV(compare_result);
        bound_s = sp48;
        bound_u = (u16) sp48;
        ASM_USE2_NV(bound_s, bound_u);
        compare_result = compare_result < bound_s;
        ASM_USE_NV(compare_result);
        if (compare_result) {
            mask_low = 0xFFFF0000;
            ASM_USE_NV(mask_low);
            var_s2 &= mask_low;
            var_s2 = bound_u | var_s2;
        }
        compare_result = (s16) var_s3;
        compare_result = bound_s < compare_result;
        ASM_USE_NV(compare_result);
        if (compare_result) {
            mask_low = 0xFFFF0000;
            ASM_USE_NV(mask_low);
            var_s3 &= mask_low;
            var_s3 = bound_u | var_s3;
        }
        compare_result = var_s2 >> 0x10;
        ASM_KEEP_NV(compare_result);
        bound_s = sp4A;
        bound_u = (u16) sp4A;
        ASM_USE2_NV(bound_s, bound_u);
        compare_result = compare_result < bound_s;
        ASM_USE_NV(compare_result);
        if (compare_result) {
            shifted_bound = bound_u << 0x10;
            ASM_USE_NV(shifted_bound);
            var_s2 &= 0xFFFF;
            var_s2 |= shifted_bound;
        }
        compare_result = var_s3 >> 0x10;
        compare_result = bound_s < compare_result;
        ASM_USE_NV(compare_result);
        if (compare_result) {
            shifted_bound = bound_u << 0x10;
            ASM_USE_NV(shifted_bound);
            var_s3 &= 0xFFFF;
            var_s3 |= shifted_bound;
        }
        var_s1 -= 1;
    } while (var_s1 >= 0);
    if (temp_s7 < 0x1E0U) {
        average_s2 = (s16) var_s2;
        average_s3 = (s16) var_s3;
        ASM_USE2_NV(average_s2, average_s3);
        average_result = average_s2 + average_s3;
        ASM_USE_NV(average_result);
        average_result >>= 1;
        sp4C = average_result;
        ASM_SCHED_BARRIER();
        var_s1 = 1;
        ASM_KEEP(var_s1);
        ASM_SET(var_s1);
        temp_s5 = var_s2 >> 0x10;
        ASM_USE(temp_s5);
        temp_s4 = temp_s7 * 4;
        ASM_KEEP_NV(temp_s7);
        ASM_USE2_NV(temp_s5, temp_s4);
        mask_high = 0xFF000000;
        ASM_SCHED_BARRIER();
loop_16:
        global_base = (s8 *) &D_80083160_alloc;
        ASM_KEEP_DEP_NV(global_base, mask_high);
        temp_s0 = M2C_FIELD(M2C_FIELD(global_base, void **, 0), s32 **, 0x8D0);
        M2C_FIELD(M2C_FIELD(global_base, void **, 0), s32 **, 0x8D0) = (s32 *) ((s8 *) temp_s0 + 0x24);
        if (var_s1 != 0) {
            global_base = (s8 *) sp50;
            ASM_KEEP_NV(global_base);
            temp_v0 = M2C_FIELD(global_base, s32 *, 0x58);
            M2C_FIELD(temp_s0, s32 *, 0x1C) = 0;
            M2C_FIELD(temp_s0, s32 *, 0x14) = 0;
            M2C_FIELD(temp_s0, s32 *, 0xC) = temp_v0;
            M2C_FIELD(temp_s0, s32 *, 4) = temp_v0;
            ASM_SCHED_BARRIER();
            center_value = (u16) sp4C;
            ASM_USE_NV(center_value);
            M2C_FIELD(temp_s0, s16 *, 0x20) = var_s2;
            M2C_FIELD(temp_s0, s16 *, 0x18) = var_s2;
            M2C_FIELD(temp_s0, u16 *, 0x10) = center_value;
            M2C_FIELD(temp_s0, u16 *, 8) = center_value;
            goto shared_setup;
        }
        {
            register s32 hard_zero ASM_REG("$0");
#ifdef NON_MATCHING
            hard_zero = 0;
#else
            ASM_UNDEF(hard_zero);
#endif
            M2C_FIELD(temp_s0, s32 *, 0xC) = hard_zero;
            M2C_FIELD(temp_s0, s32 *, 4) = hard_zero;
        }
        global_base = (s8 *) sp50;
        ASM_KEEP_NV(global_base);
        temp_v0_2 = M2C_FIELD(global_base, s32 *, 0x58);
        M2C_FIELD(temp_s0, s32 *, 0x1C) = temp_v0_2;
        M2C_FIELD(temp_s0, s32 *, 0x14) = temp_v0_2;
        ASM_SCHED_BARRIER();
        center_value = (u16) sp4C;
        ASM_USE_NV(center_value);
        M2C_FIELD(temp_s0, u16 *, 0x10) = (u16) var_s3;
        M2C_FIELD(temp_s0, s16 *, 8) = var_s3;
        M2C_FIELD(temp_s0, s16 *, 0x20) = center_value;
        M2C_FIELD(temp_s0, s16 *, 0x18) = center_value;
shared_setup:
        func_80066708(temp_s0);
        func_80066640(temp_s0, 1);
        M2C_FIELD(temp_s0, s16 *, 0x1A) = 0;
        M2C_FIELD(temp_s0, s16 *, 0xA) = 0;
        M2C_FIELD(temp_s0, s16 *, 0x22) = (s16) temp_s5;
        M2C_FIELD(temp_s0, s16 *, 0x12) = (s16) temp_s5;
        global_base = (s8 *) &D_80083160_link;
        ASM_KEEP_NV(global_base);
        link_global = (s32) M2C_FIELD(global_base, void **, 0);
        link_object = M2C_FIELD(temp_s0, s32 *, 0);
        ASM_USE2_NV(link_global, link_object);
        link_global = M2C_FIELD(temp_s4 + link_global, s32 *, 0xB0);
        link_object &= mask_high;
        link_global &= mask_all;
        link_object |= link_global;
        M2C_FIELD(temp_s0, s32 *, 0) = link_object;
        var_s1 -= 1;
        var_a0 = temp_s4 + (s32) M2C_FIELD(global_base, void **, 0);
        M2C_FIELD(var_a0, s32 *, 0xB0) = (s32) ((M2C_FIELD(var_a0, s32 *, 0xB0) & mask_high) | ((s32) temp_s0 & mask_all));
        if (var_s1 < 0) {
            temp_s0_2 = M2C_FIELD(M2C_FIELD(global_base, void **, 0), s32 **, 0x8D0);
            M2C_FIELD(M2C_FIELD(global_base, void **, 0), s32 **, 0x8D0) = (s32 *) ((s8 *) temp_s0_2 + 0xC);
            func_80067F20(temp_s0_2, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
            global_base = (s8 *) &D_80083160_final;
            ASM_KEEP_NV(global_base);
            temp_a0_2 = temp_s7 * 4;
            ASM_USE_NV(temp_a0_2);
            final_mask = 0xFF000000;
            ASM_USE_NV(final_mask);
            final_global = (s32) M2C_FIELD(global_base, void **, 0);
            final_object = *temp_s0_2;
            ASM_USE2_NV(final_global, final_object);
            final_global = temp_a0_2 + final_global;
            final_global = M2C_FIELD(final_global, s32 *, 0xB0);
            final_object &= final_mask;
            final_global &= mask_all;
            final_object |= final_global;
            *temp_s0_2 = final_object;
            final_global = (s32) M2C_FIELD(global_base, void **, 0);
            ASM_USE_NV(final_global);
            temp_a0_3 = (void *) (temp_a0_2 + final_global);
            ASM_USE_NV(temp_a0_3);
            M2C_FIELD(temp_a0_3, s32 *, 0xB0) = (s32) ((M2C_FIELD(temp_a0_3, s32 *, 0xB0) & final_mask) | ((s32) temp_s0_2 & mask_all));
            goto block_21;
        }
        goto loop_16;
    }
block_21:
    global_base = (s8 *) arg0;
    ASM_KEEP_NV(global_base);
    temp_a0 = M2C_FIELD(global_base, s32 *, -8);
    ASM_USE_NV(temp_a0);
    if (temp_a0 == 0) {
        goto return_zero;
    }
    arg0 = (void *) (temp_a0 + 0x20);
    goto loop_entry;
return_zero:
    {
        register s32 hard_zero ASM_REG("$0");
        register s32 result ASM_REG("$2");
#ifdef NON_MATCHING
        hard_zero = 0;
#else
        ASM_UNDEF(hard_zero);
#endif
        result = hard_zero;
        ASM_KEEP(result);
        return result;
    }
}
