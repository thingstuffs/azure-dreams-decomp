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

M2C_UNK func_80064840();
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80064BC0();
M2C_UNK func_80064CF0();
M2C_UNK func_80064D80();
u32 func_80065420();
M2C_UNK func_800654B0();
M2C_UNK func_80065820();
M2C_UNK func_80170A78();
M2C_UNK func_80170B40();
M2C_UNK func_80170BAC();
M2C_UNK func_80170DF8();
M2C_UNK func_80170E48();
M2C_UNK func_80170F78();
extern M2C_UNK D_8006CD30[];
extern struct S_8003E2D8 D_80083160;

#ifdef __mips__
static const u32 split_prefix[] __asm__("func_80170800")
    __attribute__((section(".text.func_80170800"), aligned(4))) = {
    0x80171850, 0x80171A18,
    0x80172204, 0x80172204, 0x80172204, 0x80172230,
    0x801721B0, 0x801721B0, 0x801721B0, 0x8017215C,
    0x80172194, 0x80172230, 0x80172230, 0x801721F4,
    0x801738F8, 0x801738F0, 0x801738E8, 0x80173900,
    0x801738A8, 0x801738A0, 0x80173898,
    0x00000001, 0x00020002, 0x00010000, 0x0002FFFE,
    0x0000FFFF, 0xFFFEFFFE, 0xFFFF0000, 0xFFFE0002,
};
__asm__(".globl func_80170800\n"
        ".size func_80170800, 2008");
#define BODY_NAME func_80170874
#else
#define BODY_NAME func_80170800
#endif

#define scratch scratch_page

void BODY_NAME(void *arg0, void *arg1, void *arg2, s16 arg3) {
    s32 temp_a0;
    register s32 temp_a3;
    register s32 temp_c4;
    register s32 temp_c6;
    s16 temp_v0_10;
    s16 temp_v0_11;
    s16 temp_v0_5;
    s16 temp_v0_7;
    s16 temp_v0_8;
    s16 temp_v0_9;
    s32 temp_a1;
    s32 temp_a2_2;
    s32 *temp_v1_9;
    s32 var_a1;
    s32 var_a2;
    s32 var_v1;
    s32 var_v1_2;
    u32 temp_a2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    register u16 temp_v1_5;
    u32 temp_v0;
    u32 temp_v0_2;
    u32 temp_v0_6;
    u32 temp_scaled;
    register u32 coord_addend;
    register u32 temp_v1 ASM_REG("$3");
    register u32 temp_v1_2 ASM_REG("$3");
    register u32 adjust_value ASM_REG("$2");
    register u32 mask_value;
    u32 temp_a0_3;
    register u8 temp_a0_2 ASM_REG("$4");
    u8 temp_v1_3;
    u8 temp_v1_4;
    register u8 var_v0 ASM_REG("$2");
    void *(*temp_v0_12)(void *, void *, void *, void *, void *);
    void *temp_s0;
    void *temp_s3;
    register void *temp_s7 ASM_REG("$23");
    register u32 mask;
    register void *initial_ptr ASM_REG("$3");
    register u32 page_color;
    void *var_s2;
    register void *p_arg0 ASM_REG("$21") = arg0;
    register void *p_arg1 = arg1;
    register void *p_arg2 ASM_REG("$20") = arg2;
    register s16 p_arg3 ASM_REG("$16") = arg3;
    register u8 *call_a0 ASM_REG("$4") = (u8 *)0x1F800004;
    register u8 *call_a1 ASM_REG("$5") = (u8 *)0x1F8000F8;
    register u8 *scratch_seed ASM_REG("$6") = (u8 *)0x1F800000;
    register u8 *page_base ASM_REG("$8") = (u8 *)0x80080000;
    register u8 *scratch_page;
    register u8 *call_a3;
    ASM_KEEP_MEMDEP_NV(p_arg1, page_color, M2C_FIELD(&D_80083160, void **, 0));
    scratch_page = (u8 *)0x1F800000;
    ASM_KEEP_NV(scratch_seed);
    ASM_KEEP_NV(p_arg0);
    ASM_KEEP_NV(p_arg2);
    ASM_KEEP_NV(p_arg3);
#define arg0 p_arg0
#define arg1 p_arg1
#define arg2 p_arg2
#define arg3 p_arg3

    scratch_seed = (u8 *)((u32)scratch_seed | 0xD0);
    initial_ptr = M2C_FIELD(&D_80083160, void **, 0);
    M2C_FIELD(scratch, u32 *, 0x90) = 0;
    M2C_FIELD(scratch, u16 *, 0xCC) = 0;
    M2C_FIELD(scratch, u16 *, 0xC4) = 0;
    M2C_FIELD(scratch, u16 *, 0xBC) = 0;
    M2C_FIELD(scratch, u16 *, 0xB4) = 0;
    M2C_FIELD(scratch, u32 *, 0x24) = initial_ptr + 0xB0;
    M2C_FIELD(scratch, u16 *, 4) = M2C_FIELD(arg1, u16 *, 2);
    call_a3 = scratch_page;
    ASM_KEEP_MEMDEP_NV(scratch_page, page_color, M2C_FIELD(&D_80083160, void **, 0));
    ASM_SET(page_base);
    ASM_KEEP_NV(call_a3);
    M2C_FIELD(scratch, u16 *, 6) = M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(scratch, u16 *, 8) = M2C_FIELD(arg1, u16 *, 0xA);
    call_a3 = (u8 *)((u32)call_a3 | 0xD4);
    var_s2 = M2C_FIELD(initial_ptr, void **, 0x8D0);
    temp_s7 = (void *)(page_base + 0x3160);
    M2C_FIELD(scratch, u32 *, 0x100) = func_80065420(call_a0, call_a1, scratch_seed, call_a3);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16)(M2C_FIELD(arg2, u16 *, 0x14) | 0x8000);
    temp_v0 = M2C_FIELD(scratch, u32 *, 0x100);
    temp_scaled = temp_v0 * 4;
    temp_v0 -= 0xA;
    temp_v0_2 = temp_v0 - arg3;
    temp_s3 = &D_8006CD30;
    M2C_FIELD(temp_s3, s32 *, 0x1C) = (s32)temp_scaled;
    M2C_FIELD(scratch, u32 *, 0x100) = temp_v0_2;
    if (temp_v0_2 < 0x1D6U) {
        mask = 0x00FF0000;
        func_800649A0();
        ASM_KEEP_NV(mask);
        call_a0 = scratch_page;
        ASM_KEEP_NV(call_a0);
        call_a0 = (u8 *)((u32)call_a0 | 0xA4);
        adjust_value = M2C_FIELD(scratch, u16 *, 0xF8);
        call_a1 = scratch_page;
        adjust_value -= 0xA0;
        ASM_KEEP_NV(adjust_value);
        M2C_FIELD(scratch, u16 *, 0xF8) = adjust_value;
        adjust_value = M2C_FIELD(scratch, u16 *, 0xFA);
        temp_c4 = M2C_FIELD(temp_s7, s16 *, 0xC4);
        ASM_KEEP_DEP_NV(temp_c4, adjust_value);
        temp_c6 = M2C_FIELD(temp_s7, s16 *, 0xC6);
        temp_a3 = M2C_FIELD(temp_s7, s16 *, 0xC8);
        adjust_value -= 0x78;
        ASM_KEEP_NV(adjust_value);
        M2C_FIELD(scratch, u16 *, 0xFA) = adjust_value;
        ASM_SCHED_BARRIER();
        M2C_FIELD(scratch, u32 *, 0x34) = temp_c4;
        M2C_FIELD(scratch, u32 *, 0x38) = temp_c6;
        M2C_FIELD(scratch, u32 *, 0x3C) = temp_a3;
        ASM_SCHED_BARRIER();
        ASM_CLOBBER("$6");
        temp_v0_3 = M2C_FIELD(arg2, u16 *, 0x16);
        temp_a2 = M2C_FIELD(scratch, u16 *, 0x38);
        call_a1 = (u8 *)((u32)call_a1 | 0x74);
        ASM_KEEP_NV(call_a1);
        M2C_FIELD(scratch, u16 *, 0xA4) = temp_v0_3;
        coord_addend = M2C_FIELD(arg2, u16 *, 0x1A);
        ASM_KEEP_NV(coord_addend);
        mask_value = M2C_FIELD(temp_s7, u16 *, 0xB8);
        ASM_KEEP_NV(mask_value);
        coord_addend -= temp_a2;
        mask_value += coord_addend;
        M2C_FIELD(scratch, u16 *, 0xA8) = mask_value;
        coord_addend = M2C_FIELD(arg2, u16 *, 0x18);
        ASM_KEEP_NV(coord_addend);
        mask_value = M2C_FIELD(scratch, u16 *, 0x3C);
        ASM_KEEP_NV(mask_value);
        coord_addend -= 0x100;
        mask_value = (mask_value + 0x100) & 0x1FF;
        coord_addend += mask_value;
        M2C_FIELD(scratch, u16 *, 0xA6) = coord_addend;
        temp_v0_3 = M2C_FIELD(arg2, u16 *, 0x20);
        M2C_FIELD(scratch, u32 *, 0x88) = temp_v0_3;
        M2C_FIELD(scratch, u16 *, 0xAC) = temp_v0_3;
        mask_value = M2C_FIELD(arg2, u16 *, 0x22);
        ASM_KEEP_DEP_NV(mask, mask_value);
        mask |= 0xFFFF;
        ASM_KEEP_NV(mask);
        M2C_FIELD(scratch, u32 *, 0x8C) = mask_value;
        M2C_FIELD(scratch, u16 *, 0xAE) = mask_value;
        func_80065820(call_a0, call_a1, temp_a2, temp_a3);
        call_a0 = scratch_page;
        ASM_KEEP_NV(call_a0);
        call_a0 = (u8 *)((u32)call_a0 | 0x74);
        call_a1 = scratch_page;
        ASM_KEEP_NV(call_a1);
        call_a1 = (u8 *)((u32)call_a1 | 0x34);
        M2C_FIELD(scratch, u32 *, 0x34) = M2C_FIELD(arg2, u16 *, 0x1C);
        temp_v0_4 = M2C_FIELD(arg2, u16 *, 0x1E);
        M2C_FIELD(scratch, u32 *, 0x3C) = 0x1000;
        M2C_FIELD(scratch, u32 *, 0x38) = temp_v0_4;
        func_80064BC0(call_a0, call_a1);
        call_a0 = temp_s3;
        ASM_KEEP_NV(call_a0);
        call_a1 = scratch_page;
        ASM_KEEP_NV(call_a1);
        call_a1 = (u8 *)((u32)call_a1 | 0x74);
        scratch_seed = scratch_page;
        ASM_KEEP_NV(scratch_seed);
        scratch_seed = (u8 *)((u32)scratch_seed | 0x54);
        func_80064840(call_a0, call_a1, scratch_seed);
        call_a0 = scratch_page;
        ASM_KEEP_NV(call_a0);
        call_a0 = (u8 *)((u32)call_a0 | 0x54);
        func_80064D80(call_a0);
        call_a0 = scratch_page;
        ASM_KEEP_NV(call_a0);
        call_a0 = (u8 *)((u32)call_a0 | 0x54);
        func_80064CF0(call_a0);
        temp_s3 = M2C_FIELD(arg2, void **, 8);
        temp_s0 = temp_s3 + 8;
        M2C_FIELD(scratch, u16 *, 0x28) = M2C_FIELD(arg2, u16 *, 0x14);
loop_80170A78:
        if (!(M2C_FIELD(temp_s3, u8 *, 0) & 0x20)) {
            M2C_FIELD(scratch, u32 *, 0xC) = M2C_FIELD(temp_s0, u8 *, 0);
            M2C_FIELD(scratch, u32 *, 0x10) = M2C_FIELD(temp_s0, u8 *, 1);
            M2C_FIELD(scratch, u32 *, 0x14) = M2C_FIELD(temp_s0, u8 *, 2);
            M2C_FIELD(scratch, u32 *, 0x18) = M2C_FIELD(temp_s0, u8 *, 3);
            if ((M2C_FIELD(temp_s3, u8 *, 0) ^ M2C_FIELD(scratch, u16 *, 0x28)) & 1) {
                temp_v0_5 = (0 - ((s32)(0 - M2C_FIELD(arg0, s16 *, 0x4E)) / 2)) - M2C_FIELD(scratch, u16 *, 0xAC);
                M2C_FIELD(scratch, u16 *, 0xC0) = temp_v0_5;
                M2C_FIELD(scratch, u16 *, 0xB0) = temp_v0_5;
                temp_v0_8 = temp_v0_5 - M2C_FIELD(arg0, u16 *, 0x4E);
                goto block_80170B40;
            }
            temp_v0_6 = 0 - M2C_FIELD(arg0, s16 *, 0x4E);
            temp_v0_7 = ((s32)(temp_v0_6 + (temp_v0_6 >> 0x1F)) >> 1) - M2C_FIELD(scratch, u16 *, 0xAC);
            M2C_FIELD(scratch, u16 *, 0xC0) = temp_v0_7;
            M2C_FIELD(scratch, u16 *, 0xB0) = temp_v0_7;
            coord_addend = (u16)M2C_FIELD(arg0, s16 *, 0x4E);
            ASM_KEEP_NV(coord_addend);
            temp_v0_8 = temp_v0_7 + coord_addend;
block_80170B40:
            M2C_FIELD(scratch, u16 *, 0xC8) = temp_v0_8;
            M2C_FIELD(scratch, u16 *, 0xB8) = temp_v0_8;
            if ((M2C_FIELD(temp_s3, u8 *, 0) ^ M2C_FIELD(scratch, u16 *, 0x28)) & 2) {
                temp_v0_9 = M2C_FIELD(arg0, u16 *, 0x50) - M2C_FIELD(scratch, u16 *, 0xAE);
                M2C_FIELD(scratch, u16 *, 0xBA) = temp_v0_9;
                M2C_FIELD(scratch, u16 *, 0xB2) = temp_v0_9;
                temp_v0_11 = temp_v0_9 - M2C_FIELD(arg0, u16 *, 0x50);
                goto block_80170BAC;
            }
            temp_v0_10 = (0 - M2C_FIELD(arg0, u16 *, 0x50)) - M2C_FIELD(scratch, u16 *, 0xAE);
            M2C_FIELD(scratch, u16 *, 0xBA) = temp_v0_10;
            M2C_FIELD(scratch, u16 *, 0xB2) = temp_v0_10;
            coord_addend = M2C_FIELD(arg0, u16 *, 0x50);
            ASM_KEEP_NV(coord_addend);
            temp_v0_11 = temp_v0_10 + coord_addend;
block_80170BAC:
            M2C_FIELD(scratch, u16 *, 0xCA) = temp_v0_11;
            M2C_FIELD(scratch, u16 *, 0xC2) = temp_v0_11;
            ASM_SCHED_BARRIER();
            func_800654B0(scratch + 0xB0, scratch + 0xB8, scratch + 0xC0, scratch + 0xC8, scratch + 0x94, scratch + 0x98, scratch + 0x9C, scratch + 0xA0, scratch + 0xD0, scratch + 0xD4);
            M2C_FIELD(var_s2, u16 *, 8) = M2C_FIELD(scratch, u16 *, 0x94) + M2C_FIELD(scratch, u16 *, 0xF8);
            M2C_FIELD(var_s2, u16 *, 0xA) = M2C_FIELD(scratch, u16 *, 0x96) + M2C_FIELD(scratch, u16 *, 0xFA);
            M2C_FIELD(var_s2, u16 *, 0x10) = M2C_FIELD(scratch, u16 *, 0x98) + M2C_FIELD(scratch, u16 *, 0xF8);
            M2C_FIELD(var_s2, u16 *, 0x12) = M2C_FIELD(scratch, u16 *, 0x9A) + M2C_FIELD(scratch, u16 *, 0xFA);
            M2C_FIELD(var_s2, u16 *, 0x18) = M2C_FIELD(scratch, u16 *, 0x9C) + M2C_FIELD(scratch, u16 *, 0xF8);
            M2C_FIELD(var_s2, u16 *, 0x1A) = M2C_FIELD(scratch, u16 *, 0x9E) + M2C_FIELD(scratch, u16 *, 0xFA);
            var_a2 = 0;
            M2C_FIELD(var_s2, u16 *, 0x20) = M2C_FIELD(scratch, u16 *, 0xA0) + M2C_FIELD(scratch, u16 *, 0xF8);
            temp_a0 = M2C_FIELD(scratch, u16 *, 0xA2) + M2C_FIELD(scratch, u16 *, 0xFA);
            M2C_FIELD(var_s2, s16 *, 0x22) = temp_a0;
            if ((u32)((M2C_FIELD(var_s2, u16 *, 8) + 0x20) & 0xFFFF) < 0x181U) {
                u32 bound = (u32)((M2C_FIELD(var_s2, u16 *, 0xA) + 0x20) & 0xFFFF);
                var_a2 = bound < 0x121U;
            }
            var_v1 = 0;
            if ((u32)((M2C_FIELD(var_s2, u16 *, 0x10) + 0x20) & 0xFFFF) < 0x181U) {
                u32 bound = (u32)((M2C_FIELD(var_s2, u16 *, 0x12) + 0x20) & 0xFFFF);
                var_v1 = bound < 0x121U;
            }
            var_a1 = 0;
            temp_a2_2 = var_a2 | var_v1;
            if ((u32)((M2C_FIELD(var_s2, u16 *, 0x18) + 0x20) & 0xFFFF) < 0x181U) {
                u32 bound = (u32)((M2C_FIELD(var_s2, u16 *, 0x1A) + 0x20) & 0xFFFF);
                var_a1 = bound < 0x121U;
            }
            var_v1_2 = 0;
            temp_a1 = temp_a2_2 | var_a1;
            if ((u32)((M2C_FIELD(var_s2, u16 *, 0x20) + 0x20) & 0xFFFF) < 0x181U) {
                u32 bound = (u32)((temp_a0 + 0x20) & 0xFFFF);
                var_v1_2 = bound < 0x121U;
            }
            if ((temp_a1 | var_v1_2) != 0) {
                M2C_FIELD(var_s2, s8 *, 3) = 9;
                M2C_FIELD(arg2, u16 *, 0x14) = (u16)(M2C_FIELD(arg2, u16 *, 0x14) & 0x7FFF);
                {
                    register u32 count ASM_REG("$2") = M2C_FIELD(scratch, u32 *, 0x14);
                    temp_v1 = M2C_FIELD(scratch, u32 *, 0xC);
                    count -= 1;
                    ASM_KEEP_NV(count);
                    temp_v1 = count + temp_v1;
                }
                M2C_FIELD(scratch, u32 *, 0x14) = temp_v1;
                if (temp_v1 & 0x100) {
                    register u32 adjusted ASM_REG("$2") = temp_v1 - 1;
                    ASM_KEEP_NV(adjusted);
                    M2C_FIELD(scratch, u32 *, 0x14) = adjusted;
                }
                {
                    register u32 count ASM_REG("$2") = M2C_FIELD(scratch, u32 *, 0x18);
                    temp_v1_2 = M2C_FIELD(scratch, u32 *, 0x10);
                    count -= 1;
                    ASM_KEEP_NV(count);
                    temp_v1_2 = count + temp_v1_2;
                }
                M2C_FIELD(scratch, u32 *, 0x18) = temp_v1_2;
                if (temp_v1_2 & 0x100) {
                    register u32 adjusted ASM_REG("$2") = temp_v1_2 - 1;
                    ASM_KEEP_NV(adjusted);
                    M2C_FIELD(scratch, u32 *, 0x18) = adjusted;
                }
                M2C_FIELD(scratch, u32 *, 0x18) <<= 8;
                M2C_FIELD(scratch, u32 *, 0x10) <<= 8;
                if (M2C_FIELD(scratch, u16 *, 0x28) & 0x100) {
                    M2C_FIELD(var_s2, s16 *, 0xE) = M2C_FIELD(arg2, u16 *, 0x12);
                    goto block_80170DF8;
                }
                M2C_FIELD(var_s2, s16 *, 0xE) = (s16)(M2C_FIELD(arg2, u16 *, 0x12) + M2C_FIELD(temp_s0, u16 *, -2));
block_80170DF8:
                M2C_FIELD(var_s2, s16 *, 0xC) = (s16)((u16)M2C_FIELD(scratch, u32 *, 0x10) + (u16)M2C_FIELD(scratch, u32 *, 0xC));
                M2C_FIELD(var_s2, s16 *, 0x14) = (s16)((u16)M2C_FIELD(scratch, u32 *, 0x10) + (u16)M2C_FIELD(scratch, u32 *, 0x14));
                if (M2C_FIELD(arg2, u16 *, 0x10) != 0) {
                    temp_v0_3 = (M2C_FIELD(temp_s0, u16 *, -4) & 0xFF9F) + M2C_FIELD(arg2, u16 *, 0x10);
                    goto block_80170E48;
                }
                temp_v0_3 = M2C_FIELD(temp_s0, u16 *, -4);
block_80170E48:
                M2C_FIELD(var_s2, u16 *, 0x16) = temp_v0_3;
                M2C_FIELD(var_s2, s16 *, 0x1C) = (s16)((u16)M2C_FIELD(scratch, u32 *, 0x18) | (u16)M2C_FIELD(scratch, u32 *, 0xC));
                temp_v1 = (u16)M2C_FIELD(scratch, u32 *, 0x18);
                temp_v1 |= (u16)M2C_FIELD(scratch, u32 *, 0x14);
                M2C_FIELD(var_s2, s16 *, 0x24) = temp_v1;
                if ((s16)M2C_FIELD(var_s2, u16 *, 0x20) < (s16)M2C_FIELD(var_s2, u16 *, 8)) {
                    temp_v1_3 = M2C_FIELD(var_s2, u8 *, 0x24);
                    M2C_FIELD(var_s2, u8 *, 0x24) = (u8)(temp_v1_3 + 0xFF);
                    M2C_FIELD(var_s2, u8 *, 0x14) = temp_v1_3;
                }
                if ((s16)M2C_FIELD(var_s2, u16 *, 0xA) > M2C_FIELD(var_s2, s16 *, 0x22)) {
                    temp_v1_4 = M2C_FIELD(var_s2, u8 *, 0x25);
                    M2C_FIELD(var_s2, u8 *, 0x25) = (u8)(temp_v1_4 + 0xFF);
                    M2C_FIELD(var_s2, u8 *, 0x1D) = temp_v1_4;
                }
                temp_a0_2 = M2C_FIELD(temp_s0, u8 *, -7);
                M2C_FIELD(arg2, u8 *, 0xF) = temp_a0_2;
                temp_v1_5 = M2C_FIELD(scratch, u16 *, 0x28);
                if (temp_v1_5 & 8) {
                    var_v0 = temp_v1_5 & 4;
                    if (var_v0) {
                        var_v0 = temp_a0_2 | 2;
                    } else {
                        var_v0 = temp_a0_2 & 0xFD;
                    }
                    M2C_FIELD(arg2, u8 *, 0xF) = var_v0;
                }
                M2C_FIELD(var_s2, s32 *, 4) = (s32)M2C_FIELD(arg2, s32 *, 0xC);
                temp_a0_3 = (u32)var_s2 & mask;
                M2C_FIELD(var_s2, s32 *, 0) = (s32)((M2C_FIELD(var_s2, s32 *, 0) & 0xFF000000) | (*((u32 *)((M2C_FIELD(scratch, u32 *, 0x100) * 4) + M2C_FIELD(scratch, u32 *, 0x24))) & mask));
                temp_v1_9 = (s32 *)((M2C_FIELD(scratch, u32 *, 0x100) * 4) + M2C_FIELD(scratch, u32 *, 0x24));
                var_s2 += 0x28;
                *temp_v1_9 = (*temp_v1_9 & 0xFF000000) | temp_a0_3;
                goto block_39;
            }
            goto block_39;
        }
        temp_v0_12 = (void *(*)(void *, void *, void *, void *, void *))M2C_FIELD(temp_s0, void **, 0);
        if (temp_v0_12 != NULL) {
            var_s2 = temp_v0_12(arg0, arg1, arg2, temp_s3, var_s2);
        }
block_39:
        if ((s8)M2C_FIELD(temp_s3, u8 *, 0) >= 0) {
            temp_s0 += 0xC;
            temp_s3 += 0xC;
            goto loop_80170A78;
        }
        func_80064A40();
    }
    M2C_FIELD(M2C_FIELD(temp_s7, void **, 0), void **, 0x8D0) = var_s2;
}

#undef arg0
#undef arg1
#undef arg2
#undef arg3
#undef scratch
