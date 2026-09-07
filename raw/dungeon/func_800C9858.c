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
s32 func_80065420();
M2C_UNK func_800654B0();
M2C_UNK func_80065820();
u16 func_80065F90();
M2C_UNK func_8006658C();
M2C_UNK func_800CF270();
M2C_UNK func_800CF31C();
M2C_UNK func_800CF390();
M2C_UNK func_800CF5C4();
M2C_UNK func_800CF5D8();
M2C_UNK func_800CF75C();
M2C_UNK func_800CF764();
M2C_UNK func_800CF7B4();
extern s32 D_8006CD30[];
extern s8 D_80083160[];

void func_800CEFB8(void *unused, void *arg1, void *arg2, s16 arg3, s32 arg4) {
    s32 temp_c4;
    s32 temp_c6;
    s32 temp_c8;
    s16 temp_v0_10;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 temp_v0_8;
    s16 temp_v0_9;
    s32 var_v1;
    s32 temp_a0;
    register s32 temp_a1_2 ASM_REG("$5");
    s32 arg4_copy;
    s32 temp_v0;
    s32 a3x;
    s32 temp_v0_2;
    register s32 range_v0 ASM_REG("$2");
    register s32 range_v1 ASM_REG("$3");
    s32 var_a0;
    s32 var_a1;
    s32 var_v1_2;
    s32 var_v1_3;
    u16 temp_f2;
    u16 call_f2;
    u16 call_ba;
    u16 call_f0;
    u16 call_b8;
    u16 second_coord;
    s32 first_result;
    s32 second_result;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v1_5;
    register u16 temp_10e ASM_REG("$2");
    s32 continuation_flag;
    register s32 continuation_v0 ASM_REG("$2");
    register u8 temp_a0_2 ASM_REG("$4");
    u8 temp_v1_3;
    u8 temp_v1_4;
    register u8 var_v0 ASM_REG("$2");
    void *temp_a1_3;
    register void *global_base ASM_REG("$3");
    register u8 *global_page ASM_REG("$8") = (u8 *)0x80080000;
    register u8 *scratch_base ASM_REG("$4");
    register u8 *first_a1 ASM_REG("$5");
    register u8 *first_a2 ASM_REG("$6");
    register u8 *second_a0 ASM_REG("$4");
    register u8 *second_a3 ASM_REG("$7");
    void *temp_s0;
    void *temp_s1;
    register void *temp_s4 ASM_REG("$20");
    void *temp_s7;
    register void *s7_partner ASM_REG("$23");
    s32 *coeff_base;
    void *var_s3;
    register void *arg2_hold ASM_REG("$21") = arg2;
    register s16 arg3_hold ASM_REG("$17") = arg3;
    register s16 color_a3 ASM_REG("$7") = arg3;
    s32 arg4_hold = arg4;
    register u32 page_color;
    u8 *scratch;
    scratch_base = (u8 *)0x1F800000;
    first_a1 = scratch_base;
    first_a1 = (u8 *)((u32)first_a1 | 0xB8);
    first_a2 = scratch_base;
    ASM_KEEP_MEM_NV(first_a1, *(u8 **)D_80083160);
    scratch = scratch_base;
    ASM_KEEP_NV(arg4_hold);
    global_base = *(void **)D_80083160;
    ASM_KEEP_DEP_NV(first_a2, global_base);
    first_a2 = (u8 *)((u32)first_a2 | 0x90);
    ASM_KEEP_NV(arg3_hold);

#define SP8(off) M2C_FIELD(scratch, u8 *, (off))
#define SPS8(off) M2C_FIELD(scratch, s8 *, (off))
#define SP16(off) M2C_FIELD(scratch, u16 *, (off))
#define SPS16(off) M2C_FIELD(scratch, s16 *, (off))
#define SP32(off) M2C_FIELD(scratch, s32 *, (off))
#define SPA(off) ((void *)(scratch + (off)))

    SP32(0xEC) = 0;
    SP16(0x8C) = 0;
    SP16(0x84) = 0;
    SP16(0x7C) = 0;
    SP16(0x74) = 0;
    SP32(0x20) = global_base + 0xB0;
    var_s3 = M2C_FIELD(global_base, void **, 0x8D0);
    M2C_FIELD(arg2_hold, u16 *, 0x14) = (u16) (M2C_FIELD(arg2_hold, u16 *, 0x14) | 0x8000);
    ASM_KEEP_MEMDEP(arg2_hold, page_color, *(u8 **)D_80083160);
    ASM_SET(global_page);
    ASM_KEEP(color_a3);
    SP16(0x00) = (u16) M2C_FIELD(arg1, u16 *, 2);
    SP16(0x02) = (u16) M2C_FIELD(arg1, u16 *, 6);
    temp_s7 = global_page + 0x3160;
    s7_partner = temp_s7;
    ASM_KEEP_NV(s7_partner);
    SP16(0x04) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
    first_result = func_80065420(scratch_base,
                                 first_a1,
                                 first_a2,
                                 (void *)0x1F800094);
    ASM_KEEP_NV(scratch);
    second_a0 = scratch;
    ASM_KEEP_NV(second_a0);
    first_a1 = second_a0;
    ASM_KEEP_NV(first_a1);
    first_a1 = (u8 *)((u32)first_a1 | 0xF0);
    first_a2 = second_a0;
    SP32(0xC0) = first_result;
    second_coord = M2C_FIELD(arg1, u16 *, 0xE);
    ASM_KEEP_DEP_NV(first_a2, second_coord);
    first_a2 = (u8 *)((u32)first_a2 | 0x90);
    SP16(0x00) = second_coord;
    second_coord = M2C_FIELD(arg1, u16 *, 0x12);
    ASM_KEEP_DEP_NV(second_a0, second_coord);
    second_a3 = second_a0;
    ASM_KEEP_NV(second_a3);
    SP16(0x02) = second_coord;
    second_coord = M2C_FIELD(arg1, u16 *, 0x16);
    second_a3 = (u8 *)((u32)second_a3 | 0x94);
    SP16(0x04) = second_coord;
    second_result = func_80065420(second_a0, first_a1, first_a2, second_a3);
    call_f2 = SP16(0xF2);
    call_ba = SP16(0xBA);
    call_f0 = SP16(0xF0);
    call_b8 = SP16(0xB8);
    SP32(0xC0) = (s32)(SP32(0xC0) + second_result) >> 1;
    SP16(0x10E) = func_80065F90((s16)call_f2 - (s16)call_ba,
                                (s16)call_f0 - (s16)call_b8,
                                (s16)call_f0);
    {
        register u8 *coeff_page ASM_REG("$3") = (u8 *)0x80070000;
        ASM_KEEP_NV(coeff_page);
        coeff_base = (s32 *)(coeff_page - 0x32D0);
    }
    a3x = arg3_hold;
    ASM_SCHED_BARRIER();
    temp_v0 = SP32(0xC0);
    M2C_FIELD(coeff_base, s32 *, 0x1C) = (s32) (temp_v0 * 4);
    temp_v0_2 = temp_v0 - a3x;
    SP32(0xC0) = temp_v0_2;
    if ((u32) temp_v0_2 < 0x1E0U) {
        arg4_copy = arg4_hold;
        ASM_KEEP(arg4_copy);
        func_800649A0();
        range_v0 = M2C_FIELD(scratch, volatile u16 *, 0xB8);
        range_v1 = M2C_FIELD(scratch, volatile u16 *, 0xBA);
        range_v0 -= 0xA0;
        M2C_FIELD(scratch, volatile u16 *, 0xB8) = range_v0;
        range_v0 = M2C_FIELD(scratch, volatile u16 *, 0xF0);
        range_v1 -= 0x78;
        M2C_FIELD(scratch, volatile u16 *, 0xBA) = range_v1;
        range_v0 -= 0xA0;
        M2C_FIELD(scratch, volatile u16 *, 0xF0) = range_v0;
        range_v0 = M2C_FIELD(scratch, volatile u16 *, 0xF2);
        temp_c4 = M2C_FIELD(temp_s7, s16 *, 0xC4);
        temp_c6 = M2C_FIELD(temp_s7, s16 *, 0xC6);
        temp_c8 = M2C_FIELD(temp_s7, s16 *, 0xC8);
        range_v0 -= 0x78;
        M2C_FIELD(scratch, volatile u16 *, 0xF2) = range_v0;
        SP32(0x30) = temp_c4;
        SP32(0x34) = temp_c6;
        SP32(0x38) = temp_c8;
        SP16(0x100) = (u16) M2C_FIELD(arg2_hold, u16 *, 0x16);
        var_v1 = (M2C_FIELD(arg2_hold, u16 *, 0x1A) - temp_c6) + M2C_FIELD(temp_s7, s16 *, 0xB8);
        if (((u32)arg4_hold << 0x10) == 0) {
            ASM_KEEP(arg4_hold);
            temp_10e = SP16(0x10E);
            var_v1 += (s16)temp_10e;
        }
        {
            register void *call_a0 ASM_REG("$4");
            register u8 *call_a1 ASM_REG("$5");
            s32 f18;
            call_a0 = (void *)0x1F800100;
            SP16(0x104) = var_v1;
            f18 = M2C_FIELD(arg2_hold, u16 *, 0x18);
            SP16(0x102) = (s16) ((((u16) SP32(0x38) + 0x100) & 0x1FF) + (s16) (f18 - 0x100));
            call_a1 = (u8 *)0x1F800000;
            ASM_KEEP(call_a1);
            temp_v0_3 = M2C_FIELD(arg2_hold, u16 *, 0x20);
            call_a1 = (u8 *)((u32)call_a1 | 0xD0);
            SP32(0xE4) = (s32) temp_v0_3;
            SP16(0x108) = temp_v0_3;
            temp_v0_4 = M2C_FIELD(arg2_hold, u16 *, 0x22);
            temp_s0 = var_s3 + 4;
            SP32(0xE8) = (s32) temp_v0_4;
            SP16(0x10A) = temp_v0_4;
            func_80065820(call_a0, call_a1);
        }
        {
            s32 bc_field1c;
            s32 bc_field1e;
            s32 bc_scale;
            bc_field1c = M2C_FIELD(arg2_hold, u16 *, 0x1C);
            SP32(0x30) = bc_field1c;
            bc_field1e = M2C_FIELD(arg2_hold, u16 *, 0x1E);
            bc_scale = 0x1000;
            SP32(0x38) = bc_scale;
            SP32(0x34) = bc_field1e;
            func_80064BC0((void *)0x1F8000D0, (void *)0x1F800030);
        }
        func_80064840(coeff_base, (void *)0x1F8000D0, (void *)0x1F800050);
        func_80064D80((void *)0x1F800050);
        func_80064CF0((void *)0x1F800050);
        temp_s4 = M2C_FIELD(arg2_hold, void **, 8);
        temp_s1 = temp_s4 + 1;
        SP16(0x24) = (u16) M2C_FIELD(arg2_hold, u16 *, 0x14);
entry_loop:
        if (!(M2C_FIELD(temp_s4, u8 *, 0) & 0x20)) {
            SP32(0x08) = (s32) M2C_FIELD(temp_s1, u8 *, 7);
            SP32(0x0C) = (s32) M2C_FIELD(temp_s1, u8 *, 8);
            SP32(0x10) = (s32) M2C_FIELD(temp_s1, u8 *, 9);
            SP32(0x14) = (s32) M2C_FIELD(temp_s1, u8 *, 0xA);
            {
                s16 val_v0;
                u16 axis_adjust;
                s32 axis_extent;
                if ((M2C_FIELD(temp_s4, u8 *, 0) ^ SP16(0x24)) & 1) {
                    val_v0 = (s8) M2C_FIELD(temp_s1, volatile u8 *, 1);
                    axis_adjust = M2C_FIELD(scratch, volatile u16 *, 0x108);
                    axis_extent = (u16) SP32(0x10);
                    val_v0 = -val_v0 - axis_adjust;
                    SP16(0x80) = val_v0;
                    SP16(0x70) = val_v0;
                    ASM_SCHED_BARRIER();
                    val_v0 -= axis_extent;
                    goto axis_x_join;
                }
                val_v0 = (s8) M2C_FIELD(temp_s1, volatile u8 *, 1);
                axis_adjust = M2C_FIELD(scratch, volatile u16 *, 0x108);
                axis_extent = (u16) SP32(0x10);
                val_v0 -= axis_adjust;
                SP16(0x80) = val_v0;
                SP16(0x70) = val_v0;
                ASM_SCHED_BARRIER();
                val_v0 += axis_extent;
axis_x_join:
                SP16(0x88) = val_v0;
                SP16(0x78) = val_v0;
            }
            {
                s16 val_v0;
                u16 axis_adjust;
                s32 axis_extent;
                if ((M2C_FIELD(temp_s4, u8 *, 0) ^ SP16(0x24)) & 2) {
                    val_v0 = (s8) M2C_FIELD(temp_s1, volatile u8 *, 2);
                    axis_adjust = M2C_FIELD(scratch, volatile u16 *, 0x10A);
                    axis_extent = (u16) SP32(0x14);
                    val_v0 = -val_v0 - axis_adjust;
                    SP16(0x7A) = val_v0;
                    SP16(0x72) = val_v0;
                    ASM_SCHED_BARRIER();
                    val_v0 -= axis_extent;
                    goto axis_y_join;
                }
                val_v0 = (s8) M2C_FIELD(temp_s1, volatile u8 *, 2);
                axis_adjust = M2C_FIELD(scratch, volatile u16 *, 0x10A);
                axis_extent = (u16) SP32(0x14);
                val_v0 -= axis_adjust;
                SP16(0x7A) = val_v0;
                SP16(0x72) = val_v0;
                ASM_SCHED_BARRIER();
                val_v0 += axis_extent;
axis_y_join:
                SP16(0x8A) = val_v0;
                SP16(0x82) = val_v0;
                ASM_SCHED_BARRIER();
            }
            func_800654B0(SPA(0x70), SPA(0x78), SPA(0x80), SPA(0x88),
                         var_s3 + 8, var_s3 + 0x10, var_s3 + 0x18,
                         var_s3 + 0x20, SPA(0x90), SPA(0x94));
            if (((u32)arg4_copy << 0x10) != 0) {
                if ((SP16(0xBA) << 0x10) < (SP16(0xF2) << 0x10)) {
                    M2C_FIELD(temp_s0, u16 *, 4) = (u16) (M2C_FIELD(temp_s0, u16 *, 4) + SP16(0xB8));
                    M2C_FIELD(temp_s0, u16 *, 0xC) = (u16) (M2C_FIELD(temp_s0, u16 *, 0xC) + SP16(0xB8));
                    M2C_FIELD(temp_s0, u16 *, 6) = (u16) (M2C_FIELD(temp_s0, u16 *, 6) + SP16(0xBA));
                    M2C_FIELD(temp_s0, u16 *, 0xE) = (u16) (M2C_FIELD(temp_s0, u16 *, 0xE) + SP16(0xBA));
                    M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) + SP16(0xF0));
                    M2C_FIELD(temp_s0, u16 *, 0x1C) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x1C) + SP16(0xF0));
                    M2C_FIELD(temp_s0, u16 *, 0x16) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x16) + SP16(0xF2));
                    func_800CF5C4();
                    return;
                }
                M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) + SP16(0xB8));
                M2C_FIELD(temp_s0, u16 *, 0x1C) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x1C) + SP16(0xB8));
                M2C_FIELD(temp_s0, u16 *, 0x16) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x16) + SP16(0xBA));
                M2C_FIELD(temp_s0, u16 *, 0x1E) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x1E) + SP16(0xBA));
                M2C_FIELD(temp_s0, u16 *, 4) = (u16) (M2C_FIELD(temp_s0, u16 *, 4) + SP16(0xF0));
                M2C_FIELD(temp_s0, u16 *, 0xC) = (u16) (M2C_FIELD(temp_s0, u16 *, 0xC) + SP16(0xF0));
                M2C_FIELD(temp_s0, u16 *, 6) = (u16) (M2C_FIELD(temp_s0, u16 *, 6) + SP16(0xF2));
                M2C_FIELD(temp_s0, u16 *, 0xE) = (u16) (M2C_FIELD(temp_s0, u16 *, 0xE) + SP16(0xF2));
                func_800CF5D8();
                return;
            }
            M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) + SP16(0xB8));
            M2C_FIELD(temp_s0, u16 *, 0x16) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x16) + SP16(0xBA));
            M2C_FIELD(temp_s0, u16 *, 0xC) = (u16) (M2C_FIELD(temp_s0, u16 *, 0xC) + SP16(0xF0));
            M2C_FIELD(temp_s0, u16 *, 0xE) = (u16) (M2C_FIELD(temp_s0, u16 *, 0xE) + SP16(0xF2));
            M2C_FIELD(temp_s0, u16 *, 4) = (u16) (M2C_FIELD(temp_s0, u16 *, 4) + SP16(0xB8));
            M2C_FIELD(temp_s0, u16 *, 6) = (u16) (M2C_FIELD(temp_s0, u16 *, 6) + SP16(0xBA));
            M2C_FIELD(temp_s0, u16 *, 0x1C) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x1C) + SP16(0xF0));
            M2C_FIELD(temp_s0, u16 *, 0x1E) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x1E) + SP16(0xF2));
            ASM_SCHED_BARRIER();
            var_a1 = 0;
            if ((u32) ((M2C_FIELD(temp_s0, u16 *, 4) + 0x20) & 0xFFFF) < 0x181U) {
                range_v0 = (M2C_FIELD(temp_s0, u16 *, 6) + 0x20) & 0xFFFF;
                var_a1 = (u32) range_v0 < 0x121U;
            }
            var_v1_2 = 0;
            if ((u32) ((M2C_FIELD(temp_s0, u16 *, 0xC) + 0x20) & 0xFFFF) < 0x181U) {
                range_v0 = (M2C_FIELD(temp_s0, u16 *, 0xE) + 0x20) & 0xFFFF;
                var_v1_2 = (u32) range_v0 < 0x121U;
            }
            var_a0 = 0;
            temp_a1_2 = var_a1 | var_v1_2;
            if ((u32) ((M2C_FIELD(temp_s0, u16 *, 0x14) + 0x20) & 0xFFFF) < 0x181U) {
                range_v0 = (M2C_FIELD(temp_s0, u16 *, 0x16) + 0x20) & 0xFFFF;
                var_a0 = (u32) range_v0 < 0x121U;
            }
            var_v1_3 = 0;
            temp_a0 = temp_a1_2 | var_a0;
            if ((u32) ((M2C_FIELD(temp_s0, u16 *, 0x1C) + 0x20) & 0xFFFF) < 0x181U) {
                range_v0 = (M2C_FIELD(temp_s0, u16 *, 0x1E) + 0x20) & 0xFFFF;
                var_v1_3 = (u32) range_v0 < 0x121U;
            }
            range_v0 = temp_a0 | var_v1_3;
            if (range_v0 != 0) {
                M2C_FIELD(temp_s0, s8 *, -1) = 9;
                M2C_FIELD(arg2_hold, u16 *, 0x14) = (u16) (M2C_FIELD(arg2_hold, u16 *, 0x14) & 0x7FFF);
                range_v0 = SP32(0x10);
                range_v1 = SP32(0x08);
                range_v0 -= 1;
                range_v1 = range_v0 + range_v1;
                SP32(0x10) = range_v1;
                if (range_v1 & 0x100) {
                    range_v0 = range_v1 - 1;
                    SP32(0x10) = range_v0;
                }
                range_v0 = SP32(0x14);
                range_v1 = SP32(0x0C);
                range_v0 -= 1;
                range_v1 = range_v0 + range_v1;
                SP32(0x14) = range_v1;
                if (range_v1 & 0x100) {
                    range_v0 = range_v1 - 1;
                    SP32(0x14) = range_v0;
                }
                SP32(0x14) <<= 8;
                SP32(0x0C) <<= 8;
                continuation_flag = M2C_FIELD(arg2_hold, u16 *, 0x12);
                if (continuation_flag != 0) {
                    if (SP16(0x24) & 0x100) {
                        M2C_FIELD(temp_s0, u16 *, 0xA) = continuation_flag;
                        func_800CF764(temp_a0, temp_a1_2);
                        return;
                    }
                    continuation_v0 = M2C_FIELD(temp_s1, u16 *, 5);
                    continuation_v0 = continuation_flag + continuation_v0;
                    ASM_TAILSLOT_PIN(continuation_v0);
                    func_800CF75C(temp_a0, temp_a1_2);
                    return;
                }
                M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) M2C_FIELD(temp_s1, u16 *, 5);
                M2C_FIELD(temp_s0, s16 *, 8) = (s16) ((u16) SP32(0x0C) + (u16) SP32(0x08));
                M2C_FIELD(temp_s0, s16 *, 0x10) = (s16) ((u16) SP32(0x0C) + (u16) SP32(0x10));
                continuation_flag = M2C_FIELD(arg2_hold, u16 *, 0x10);
                if (continuation_flag != 0) {
                    continuation_v0 = M2C_FIELD(temp_s1, u16 *, 3);
                    continuation_v0 &= 0xFF9F;
                    continuation_v0 = continuation_flag + continuation_v0;
                    ASM_TAILSLOT_PIN(continuation_v0);
                    func_800CF7B4(temp_a0, temp_a1_2);
                    return;
                }
                M2C_FIELD(temp_s0, u16 *, 0x12) = (u16) M2C_FIELD(temp_s1, u16 *, 3);
                {
                    s32 field_4;
                    register u16 packed_y ASM_REG("$3");
                    register u16 pack_a0 ASM_REG("$4");
                    M2C_FIELD(temp_s0, s16 *, 0x18) = (s16) (SP16(0x14) | SP16(0x08));
                    field_4 = M2C_FIELD(temp_s0, s16 *, 4);
                    packed_y = SP16(0x14);
                    pack_a0 = SP16(0x10);
                    packed_y |= pack_a0;
                    M2C_FIELD(temp_s0, s16 *, 0x20) = (s16) packed_y;
                    if (M2C_FIELD(temp_s0, s16 *, 0x1C) < field_4) {
                        temp_v1_3 = M2C_FIELD(temp_s0, u8 *, 0x20);
                        M2C_FIELD(temp_s0, u8 *, 0x20) = (u8) (temp_v1_3 + 0xFF);
                        M2C_FIELD(temp_s0, u8 *, 0x10) = temp_v1_3;
                    }
                }
                if ((s16) M2C_FIELD(temp_s0, u16 *, 6) > (s16) M2C_FIELD(temp_s0, u16 *, 0x1E)) {
                    temp_v1_4 = M2C_FIELD(temp_s0, u8 *, 0x21);
                    M2C_FIELD(temp_s0, u8 *, 0x21) = (u8) (temp_v1_4 + 0xFF);
                    M2C_FIELD(temp_s0, u8 *, 0x19) = temp_v1_4;
                }
                temp_a0_2 = M2C_FIELD(temp_s1, u8 *, 0);
                M2C_FIELD(arg2_hold, u8 *, 0xF) = temp_a0_2;
                temp_v1_5 = SP16(0x24);
                if (temp_v1_5 & 8) {
                    if (temp_v1_5 & 4) {
                        var_v0 = temp_a0_2 | 2;
                    } else {
                        var_v0 = temp_a0_2 & 0xFD;
                    }
                    M2C_FIELD(arg2_hold, u8 *, 0xF) = var_v0;
                }
                temp_a1_3 = var_s3;
                var_s3 += 0x28;
                M2C_FIELD(temp_s0, s32 *, 0) = (s32) M2C_FIELD(arg2_hold, s32 *, 0xC);
                temp_s0 += 0x28;
                func_8006658C(SP32(0x20) + (SP32(0xC0) * 4), temp_a1_3);
                goto block_47;
            }
            goto block_47;
        }
block_47:
        if ((s8) M2C_FIELD(temp_s4, u8 *, 0) >= 0) {
            temp_s1 += 0xC;
            temp_s4 += 0xC;
            goto entry_loop;
        }
        func_80064A40();
        M2C_FIELD(M2C_FIELD(temp_s7, void **, 0), void **, 0x8D0) = var_s3;
        return;
    }
    M2C_FIELD(M2C_FIELD(temp_s7, void **, 0), void **, 0x8D0) = var_s3;
}
