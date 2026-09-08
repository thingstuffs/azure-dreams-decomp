#include "common.h"
#include "m2c_compat.h"

typedef struct S_80F90E88_0 {
    s32 unk_00;
    u8 pad_04[0x4];
    void * unk_08;
    u8 pad_0C[0x54];
    s32 unk_60;
    u8 pad_64[0x6C];
    u16 unk_D0;
} S_80F90E88_0;   /* global_base in func_80F90E88; pointer addresses record offset 0x8 */

typedef struct S_80F90E88_1 {
    s32 unk_00;
    s32 unk_04;
    union { u16 s; s16 u; } unk_08;   /* accessed as both */
    s16 unk_0A;
    s32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    s32 unk_14;
    s16 unk_18;
    s16 unk_1A;
    s32 unk_1C;
    s16 unk_20;
    s16 unk_22;
} S_80F90E88_1;   /* temp_s0 in func_80F90E88 */

typedef struct S_80F90E88_2 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_80F90E88_2;   /* temp_s4 + link_global in func_80F90E88 */

typedef struct S_80F90E88_3 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_80F90E88_3;   /* var_a0 in func_80F90E88 */

typedef struct S_80F90E88_4 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_80F90E88_4;   /* final_global in func_80F90E88 */

typedef struct S_80F90E88_5 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_80F90E88_5;   /* temp_a0_3 in func_80F90E88 */


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

typedef struct S_80F90E88_6 {
    void * unk_00;
} S_80F90E88_6;   /* global_base in func_80F90E88 */

typedef struct S_80F90E88_7 {
    u8 pad_00[0x8D0];
    s32 * unk_8D0;
} S_80F90E88_7;   /* ((S_80F90E88_6 *)global_base)->unk_00 in func_80F90E88 */


s32 func_80F90E88(void *arg0) {
    LocalFrame frame;
    register s32 var_s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 var_s3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 mask_all ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 mask_high;
    s32 *temp_s0;
    s32 *temp_s0_2;
    s32 temp_a0;
    s32 temp_a0_2;
    register s32 temp_s4 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 temp_s5;
    s32 temp_v0;
    s32 temp_v0_2;
    register s32 var_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 var_s1;
    register s8 *global_base ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register u32 temp_s7 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register S_80F90E88_5 *temp_a0_3 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register WorkCell *var_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 initial_value;
    s32 negative_value;
    void *db_arg;
    u16 global_value;
    s32 copy0;
    s32 copy1;
    register s8 *stack_base ASM_REG("$29");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 mask_low ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 bound_s;
    register u32 bound_u ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 call_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *call_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 *call_a2;
    s32 compare_result;
    u32 shifted_bound;
    register s32 average_s2 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 average_s3;
    s32 average_result;
    u16 center_value;
    s32 final_mask;
    s32 link_global;
    s32 link_object;
    register s32 final_global ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 final_object;

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
    sp58 = global_base;
    global_base = (s8 *) &sp4C;
    mask_all = 0x00FFFFFF;
    sp54 = (s32 *) global_base;
loop_entry:
    global_base = (s8 *) arg0;
    sp4C = 8;
    initial_value = (u16) sp4C;
    var_s1 = 1;
    sp50 = global_base;
    global_base = sp58;
    ASM_KEEP_NV(global_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    negative_value = 0 - initial_value;
    ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    var_v0 = (WorkCell *) (global_base + 8);
    do {
        var_v0->value = initial_value;
        if (var_s1 != 0) {
            var_v0->value = negative_value;
        }
        var_v0->zero4 = 0;
        var_v0->zero2 = 0;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        var_s1 -= 1;
        var_v0 -= 1;
    } while (var_s1 >= 0);
    db_arg = &sp28;
    ASM_KEEP_NV(db_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_s3 &= 0xFFFF;
    var_s2 &= 0xFFFF;
    global_base = (s8 *) &D_80083160_init;
    ASM_KEEP_NV(global_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    global_value = ((S_80F90E88_0 *)((u8 *)global_base - 0x8))->unk_D0;
    global_base = sp58;
    ASM_KEEP_NV(global_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_s1 = 1;
    sp32 = 0;
    sp30 = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    sp28 = (M2C_UNK *) global_base;
    sp2C = (M2C_UNK *) global_base;
    global_base = (s8 *) sp50;
    sp34 = 0 - global_value;
    copy0 = ((PackedWord *) (global_base + 0xC))->value;
    copy1 = ((PackedWord *) (global_base + 0x10))->value;
#ifdef NON_MATCHING
    stack_base = (s8 *) &sp38 - 0x38;
#else
#endif
    ((PackedWord *) (stack_base + 0x38))->value = copy0;
    ((PackedWord *) (stack_base + 0x3C))->value = copy1;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    sp40 = 2;
    sp42 = 0;
    func_800DBA90(db_arg);
    var_s3 |= 0x75300000;
    mask_low = 0xFFFF0000;
    var_s3 &= mask_low;
    var_s3 |= 0x7530;
    var_s2 |= 0x8AD00000;
    var_s2 &= mask_low;
    var_s2 |= 0x8AD0;
    do {
        call_a0 = var_s1 * 8;
        call_a1 = &sp48;
        global_base = sp58;
        ASM_KEEP_NV(global_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        call_a2 = sp54;
        ASM_USE_NV(call_a2);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        call_a0 = (s32) global_base + call_a0;
        temp_s7 = func_80065420(call_a0, call_a1, call_a2, call_a2) - 4;
        ASM_KEEP_NV(temp_s7);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        compare_result = (s16) var_s2;
        bound_s = sp48;
        bound_u = (u16) sp48;
        compare_result = compare_result < bound_s;
        if (compare_result) {
            mask_low = 0xFFFF0000;
            var_s2 &= mask_low;
            var_s2 = bound_u | var_s2;
        }
        compare_result = (s16) var_s3;
        compare_result = bound_s < compare_result;
        if (compare_result) {
            mask_low = 0xFFFF0000;
            var_s3 &= mask_low;
            var_s3 = bound_u | var_s3;
        }
        compare_result = var_s2 >> 0x10;
        bound_s = sp4A;
        bound_u = (u16) sp4A;
        compare_result = compare_result < bound_s;
        if (compare_result) {
            shifted_bound = bound_u << 0x10;
            var_s2 &= 0xFFFF;
            var_s2 |= shifted_bound;
        }
        compare_result = var_s3 >> 0x10;
        compare_result = bound_s < compare_result;
        if (compare_result) {
            shifted_bound = bound_u << 0x10;
            var_s3 &= 0xFFFF;
            var_s3 |= shifted_bound;
        }
        var_s1 -= 1;
    } while (var_s1 >= 0);
    if (temp_s7 < 0x1E0U) {
        average_s2 = (s16) var_s2;
        average_s3 = (s16) var_s3;
        average_result = average_s2 + average_s3;
        average_result >>= 1;
        sp4C = average_result;
        var_s1 = 1;
        temp_s5 = var_s2 >> 0x10;
        ASM_USE(temp_s5);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        temp_s4 = temp_s7 * 4;
        mask_high = 0xFF000000;
loop_16:
        global_base = (s8 *) &D_80083160_alloc;
        ASM_KEEP_DEP_NV(global_base, mask_high);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        temp_s0 = ((S_80F90E88_7 *)(((S_80F90E88_6 *)global_base)->unk_00))->unk_8D0;
        ((S_80F90E88_7 *)(((S_80F90E88_6 *)global_base)->unk_00))->unk_8D0 = (s32 *) ((s8 *) temp_s0 + 0x24);
        if (var_s1 != 0) {
            global_base = (s8 *) sp50;
            temp_v0 = ((S_80F90E88_0 *)((u8 *)global_base - 0x8))->unk_60;
            ((S_80F90E88_1 *)temp_s0)->unk_1C = 0;
            ((S_80F90E88_1 *)temp_s0)->unk_14 = 0;
            ((S_80F90E88_1 *)temp_s0)->unk_0C = temp_v0;
            ((S_80F90E88_1 *)temp_s0)->unk_04 = temp_v0;
            center_value = (u16) sp4C;
            ((S_80F90E88_1 *)temp_s0)->unk_20 = var_s2;
            ((S_80F90E88_1 *)temp_s0)->unk_18 = var_s2;
            ((S_80F90E88_1 *)temp_s0)->unk_10 = center_value;
            ((S_80F90E88_1 *)temp_s0)->unk_08.s = center_value;
            goto shared_setup;
        }
        {
            register s32 hard_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
            hard_zero = 0;
#else
#endif
            ((S_80F90E88_1 *)temp_s0)->unk_0C = hard_zero;
            ((S_80F90E88_1 *)temp_s0)->unk_04 = hard_zero;
        }
        global_base = (s8 *) sp50;
        temp_v0_2 = ((S_80F90E88_0 *)((u8 *)global_base - 0x8))->unk_60;
        ((S_80F90E88_1 *)temp_s0)->unk_1C = temp_v0_2;
        ((S_80F90E88_1 *)temp_s0)->unk_14 = temp_v0_2;
        center_value = (u16) sp4C;
        ((S_80F90E88_1 *)temp_s0)->unk_10 = (u16) var_s3;
        ((S_80F90E88_1 *)temp_s0)->unk_08.u = var_s3;
        ((S_80F90E88_1 *)temp_s0)->unk_20 = center_value;
        ((S_80F90E88_1 *)temp_s0)->unk_18 = center_value;
shared_setup:
        func_80066708(temp_s0);
        func_80066640(temp_s0, 1);
        ((S_80F90E88_1 *)temp_s0)->unk_1A = 0;
        ((S_80F90E88_1 *)temp_s0)->unk_0A = 0;
        ((S_80F90E88_1 *)temp_s0)->unk_22 = (s16) temp_s5;
        ((S_80F90E88_1 *)temp_s0)->unk_12 = (s16) temp_s5;
        global_base = (s8 *) &D_80083160_link;
        ASM_KEEP_NV(global_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        link_global = (s32) ((S_80F90E88_0 *)((u8 *)global_base - 0x8))->unk_08;
        link_object = ((S_80F90E88_1 *)temp_s0)->unk_00;
        link_global = ((S_80F90E88_2 *)(temp_s4 + link_global))->unk_B0;
        link_object &= mask_high;
        link_global &= mask_all;
        link_object |= link_global;
        ((S_80F90E88_1 *)temp_s0)->unk_00 = link_object;
        var_s1 -= 1;
        var_a0 = temp_s4 + (s32) ((S_80F90E88_0 *)((u8 *)global_base - 0x8))->unk_08;
        ((S_80F90E88_3 *)var_a0)->unk_B0 = (s32) ((((S_80F90E88_3 *)var_a0)->unk_B0 & mask_high) | ((s32) temp_s0 & mask_all));
        if (var_s1 < 0) {
            temp_s0_2 = ((S_80F90E88_7 *)(((S_80F90E88_6 *)global_base)->unk_00))->unk_8D0;
            ((S_80F90E88_7 *)(((S_80F90E88_6 *)global_base)->unk_00))->unk_8D0 = (s32 *) ((s8 *) temp_s0_2 + 0xC);
            func_80067F20(temp_s0_2, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
            global_base = (s8 *) &D_80083160_final;
            ASM_KEEP_NV(global_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            temp_a0_2 = temp_s7 * 4;
            final_mask = 0xFF000000;
            final_global = (s32) ((S_80F90E88_0 *)((u8 *)global_base - 0x8))->unk_08;
            final_object = *temp_s0_2;
            final_global = temp_a0_2 + final_global;
            final_global = ((S_80F90E88_4 *)final_global)->unk_B0;
            final_object &= final_mask;
            final_global &= mask_all;
            final_object |= final_global;
            *temp_s0_2 = final_object;
            final_global = (s32) ((S_80F90E88_0 *)((u8 *)global_base - 0x8))->unk_08;
            temp_a0_3 = (void *) (temp_a0_2 + final_global);
            temp_a0_3->unk_B0 = (s32) ((temp_a0_3->unk_B0 & final_mask) | ((s32) temp_s0_2 & mask_all));
            goto block_21;
        }
        goto loop_16;
    }
block_21:
    global_base = (s8 *) arg0;
    ASM_KEEP_NV(global_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_a0 = ((S_80F90E88_0 *)((u8 *)global_base - 0x8))->unk_00;
    if (temp_a0 == 0) {
        goto return_zero;
    }
    arg0 = (void *) (temp_a0 + 0x20);
    goto loop_entry;
return_zero:
    {
        register s32 hard_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        hard_zero = 0;
#else
#endif
        result = hard_zero;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        return result;
    }
}
