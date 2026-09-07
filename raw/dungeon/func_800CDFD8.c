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
#define M2C_BREAK() 0
#define M2C_SYNC() 0
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
M2C_UNK func_800D3924();
M2C_UNK func_800D3AB8();
M2C_UNK func_800D3B28();
M2C_UNK func_800D3D40();
M2C_UNK func_800D3D90();
extern M2C_UNK D_8006CD30[];
extern u8 D_80083160[];

void func_800D3738(void *arg0, void *arg1_in, void *arg2_in, s16 arg3) {
    s32 temp_a0_2;
    register s32 temp_a1_3 ASM_REG("$5");
    register s32 temp_a1_4 ASM_REG("$3");
    register s32 temp_a1_5 ASM_REG("$5");
    s32 temp_v0_10;
    s16 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1_3;
    s32 temp_v1_4;
    register s32 *temp_v1_9 ASM_REG("$2");
    register s32 *temp_tail_addr ASM_REG("$3");
    register u32 temp_a0_4 ASM_REG("$4");
    register u32 temp_high_mask ASM_REG("$5");
    register u32 temp_tail_old ASM_REG("$3");
    register u32 temp_tail_table ASM_REG("$2");
    register s32 temp_tail_0 ASM_REG("$2");
    register s32 temp_tail_1 ASM_REG("$3");
    s32 temp_a1_2;
    register s32 temp_a2_2 ASM_REG("$6");
    s32 temp_c4;
    s32 temp_c6;
    s32 temp_c8;
    s32 temp_coord_y;
    s32 temp_coord_base;
    s32 temp_rotation_x;
    u32 temp_scale_x;
    u32 temp_scale_y;
    register s32 var_a1 ASM_REG("$5");
    register s32 var_a2 ASM_REG("$6");
    register s32 var_v1 ASM_REG("$3");
    register s32 var_v1_2 ASM_REG("$3");
    s32 temp_a2;
    register u16 temp_y_width ASM_REG("$4");
    u16 temp_v0_3;
    u16 temp_v0_4;
    register u32 temp_a0 ASM_REG("$4");
    register u32 temp_a0_3 ASM_REG("$4");
    u32 temp_a1;
    register u32 temp_a1_6 ASM_REG("$5");
    register u32 temp_x_total ASM_REG("$3");
    register u32 temp_y_total ASM_REG("$2");
    register u32 temp_bound ASM_REG("$2");
    register u32 temp_flags ASM_REG("$3");
    register u32 temp_any ASM_REG("$2");
    u32 temp_v0;
    u32 temp_v0_2;
    u8 temp_v0_5;
    u8 temp_v0_6;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_5;
    u8 temp_v1_6;
    u8 temp_v1_7;
    u8 temp_v1_8;
    void *temp_s0;
    u8 *temp_s1;
    register u8 *base ASM_REG("$9");
    register void *arg1 ASM_REG("$3");
    register u8 *page_scratch ASM_REG("$2");
    void *temp_s2;
    register void *temp_s4 ASM_REG("$20");
    register void *temp_s6 ASM_REG("$22");
    register void *var_s5 ASM_REG("$21");
    register void *arg2 ASM_REG("$19");
    register s16 arg3_s0 ASM_REG("$16");

    arg1 = arg1_in;
    arg2 = arg2_in;
    ASM_KEEP_NV(arg2);
    arg3_s0 = arg3;
    ASM_KEEP_NV(arg3_s0);
    {
    register u8 *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");
    register void *call_a2 ASM_REG("$6");
    register void *call_a3 ASM_REG("$7");
    register void *root ASM_REG("$8");
    call_a0 = (u8 *)0x1F800000;
    ASM_KEEP_NV(call_a0);
    call_a1 = call_a0;
    ASM_KEEP_NV(call_a1);
    call_a1 = (void *) ((u32) call_a1 | 0xB8);
    call_a2 = call_a0;
    ASM_KEEP_NV(call_a2);
    ASM_KEEP_MEMDEP_NV(call_a0, page_scratch, *(void **)D_80083160);
    temp_s1 = call_a0;
    ASM_KEEP_NV(temp_s1);
    root = *(void **)D_80083160;
    call_a2 = (void *) ((u32) call_a2 | 0x90);
    ASM_SCHED_BARRIER();
    M2C_FIELD(temp_s1, u32 *, 0xEC) = 0;
    M2C_FIELD(temp_s1, u16 *, 0x8C) = 0;
    M2C_FIELD(temp_s1, u16 *, 0x84) = 0;
    M2C_FIELD(temp_s1, u16 *, 0x7C) = 0;
    M2C_FIELD(temp_s1, u16 *, 0x74) = 0;
    M2C_FIELD(temp_s1, u32 *, 0x20) = root + 0xB0;
    temp_v0_3 = M2C_FIELD(arg1, u16 *, 2);
    ASM_SET(call_a3);
    call_a3 = call_a0;
    ASM_KEEP_NV(call_a3);
    M2C_FIELD(temp_s1, u16 *, 0) = temp_v0_3;
    ASM_KEEP_MEMDEP_NV(temp_s1, page_scratch, *(void **)D_80083160);
#ifdef NON_MATCHING
    base = D_80083160 - 0x3160;
#else
    ASM_SET(base);
#endif
    temp_v0_3 = M2C_FIELD(arg1, u16 *, 6);
    call_a3 = (void *) ((u32) call_a3 | 0x94);
    M2C_FIELD(temp_s1, u16 *, 2) = temp_v0_3;
    temp_v0_3 = M2C_FIELD(arg1, u16 *, 0xA);
    M2C_FIELD(temp_s1, u16 *, 4) = temp_v0_3;
    var_s5 = M2C_FIELD(root, void **, 0x8D0);
    M2C_FIELD(temp_s1, u32 *, 0xC0) = func_80065420((temp_s6 = base + 0x3160, call_a0), call_a1, call_a2, call_a3);
    }
    ASM_KEEP_NV(temp_s6);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x8000);
    temp_v0 = M2C_FIELD(temp_s1, u32 *, 0xC0);
    temp_s2 = &D_8006CD30;
    ASM_KEEP_NV(temp_s2);
    M2C_FIELD(temp_s2, s32 *, 0x1C) = (s32) (temp_v0 * 4);
    temp_v0 -= 0xA;
    ASM_KEEP_NV(temp_v0);
    temp_v0_2 = temp_v0 - arg3_s0;
    M2C_FIELD(temp_s1, u32 *, 0xC0) = temp_v0_2;
    if (temp_v0_2 < 0x1D6U) {
        temp_s0 = var_s5 + 7;
        func_800649A0();
        {
            register void *call_a0 ASM_REG("$4");
            register void *call_a1 ASM_REG("$5");
            register u16 temp_adjust ASM_REG("$2");
            ASM_SET(call_a0);
            call_a0 = temp_s1;
            ASM_KEEP_NV(call_a0);
        temp_adjust = M2C_FIELD(temp_s1, u16 *, 0xB8);
        call_a0 = (void *) ((u32) call_a0 | 0x100);
        ASM_KEEP_NV(call_a0);
        temp_adjust -= 0xA0;
        M2C_FIELD(temp_s1, u16 *, 0xB8) = temp_adjust;
        temp_adjust = M2C_FIELD(temp_s1, u16 *, 0xBA);
        temp_c4 = M2C_FIELD(temp_s6, s16 *, 0xC4);
        temp_c6 = M2C_FIELD(temp_s6, s16 *, 0xC6);
        temp_c8 = M2C_FIELD(temp_s6, s16 *, 0xC8);
        temp_adjust -= 0x78;
        M2C_FIELD(temp_s1, u16 *, 0xBA) = temp_adjust;
        M2C_FIELD(temp_s1, u32 *, 0x30) = (u32) temp_c4;
        M2C_FIELD(temp_s1, u32 *, 0x34) = (u32) temp_c6;
        M2C_FIELD(temp_s1, u32 *, 0x38) = (u32) temp_c8;
        temp_a2 = M2C_FIELD(temp_s1, u16 *, 0x34);
        M2C_FIELD(temp_s1, u16 *, 0x100) = (u16) M2C_FIELD(arg2, u16 *, 0x16);
        temp_coord_y = M2C_FIELD(arg2, u16 *, 0x1A);
        temp_coord_base = M2C_FIELD(temp_s6, u16 *, 0xB8);
        temp_coord_y -= temp_a2;
        temp_coord_base += temp_coord_y;
        M2C_FIELD(temp_s1, u16 *, 0x104) = (s16) temp_coord_base;
        temp_rotation_x = M2C_FIELD(arg2, u16 *, 0x18) - 0x100;
        temp_rotation_x += ((u16) M2C_FIELD(temp_s1, u32 *, 0x38) + 0x100) & 0x1FF;
        M2C_FIELD(temp_s1, u16 *, 0x102) = (s16) temp_rotation_x;
        temp_v0_3 = M2C_FIELD(arg2, u16 *, 0x20);
        ASM_SET(call_a1);
        call_a1 = temp_s1;
        ASM_KEEP_NV(call_a1);
        M2C_FIELD(temp_s1, u32 *, 0xE4) = (u32) temp_v0_3;
        ASM_SCHED_BARRIER();
        M2C_FIELD(temp_s1, u16 *, 0x108) = temp_v0_3;
        temp_v0_4 = M2C_FIELD(arg2, u16 *, 0x22);
        call_a1 = (void *) ((u32) call_a1 | 0xD0);
        M2C_FIELD(temp_s1, u32 *, 0xE8) = (u32) temp_v0_4;
        M2C_FIELD(temp_s1, u16 *, 0x10A) = temp_v0_4;
        func_80065820(call_a0, call_a1, temp_a2);
        }
        {
            register void *call_a0 ASM_REG("$4");
            register void *call_a1 ASM_REG("$5");
            ASM_SET(call_a0);
            call_a0 = temp_s1;
            ASM_KEEP_NV(call_a0);
            call_a0 = (void *) ((u32) call_a0 | 0xD0);
            ASM_SET(call_a1);
            call_a1 = temp_s1;
            ASM_KEEP_NV(call_a1);
            temp_scale_x = M2C_FIELD(arg2, u16 *, 0x1C);
            call_a1 = (void *) ((u32) call_a1 | 0x30);
            M2C_FIELD(temp_s1, u32 *, 0x30) = temp_scale_x;
            temp_scale_y = M2C_FIELD(arg2, u16 *, 0x1E);
            M2C_FIELD(temp_s1, u32 *, 0x38) = 0x1000;
            M2C_FIELD(temp_s1, u32 *, 0x34) = temp_scale_y;
            func_80064BC0(call_a0, call_a1);
        }
        {
            register void *call_a0 ASM_REG("$4");
            register void *call_a1 ASM_REG("$5");
            register void *call_a2 ASM_REG("$6");
            ASM_SET(call_a0);
            call_a0 = temp_s2;
            ASM_KEEP_NV(call_a0);
            ASM_SET(call_a1);
            call_a1 = temp_s1;
            ASM_KEEP_NV(call_a1);
            call_a1 = (void *) ((u32) call_a1 | 0xD0);
            ASM_SET(call_a2);
            call_a2 = temp_s1;
            ASM_KEEP_NV(call_a2);
            call_a2 = (void *) ((u32) call_a2 | 0x50);
            func_80064840(call_a0, call_a1, call_a2);
        }
        {
            register void *call_a0 ASM_REG("$4");
            ASM_SET(call_a0);
            call_a0 = temp_s1;
            ASM_KEEP_NV(call_a0);
            call_a0 = (void *) ((u32) call_a0 | 0x50);
            func_80064D80(call_a0);
        }
        {
            register void *call_a0 ASM_REG("$4");
            ASM_SET(call_a0);
            call_a0 = temp_s1;
            ASM_KEEP_NV(call_a0);
            call_a0 = (void *) ((u32) call_a0 | 0x50);
            func_80064CF0(call_a0);
        }
        temp_s4 = M2C_FIELD(arg2, void **, 8);
        temp_s2 = temp_s4 + 4;
        M2C_FIELD(temp_s1, u16 *, 0x24) = (u16) M2C_FIELD(arg2, u16 *, 0x14);
loop_top:
        if (!(M2C_FIELD(temp_s4, u8 *, 0) & 0x20)) {
            temp_v0_5 = M2C_FIELD(temp_s2, u8 *, 4);
            M2C_FIELD(temp_s1, u32 *, 8) = (u32) temp_v0_5;
            temp_v1 = M2C_FIELD(temp_s2, u8 *, 6);
            M2C_FIELD(temp_s1, u32 *, 0x10) = (u32) temp_v1;
            if (((temp_v0_5 + temp_v1) >= 0x100) || (M2C_FIELD(arg2, u16 *, 0x1A) != 0)) {
                M2C_FIELD(temp_s1, u32 *, 0x10) = temp_v1 - 1;
            }
            temp_v0_6 = M2C_FIELD(temp_s2, u8 *, 5);
            M2C_FIELD(temp_s1, u32 *, 0xC) = (u32) temp_v0_6;
            temp_v1_2 = M2C_FIELD(temp_s2, u8 *, 7);
            M2C_FIELD(temp_s1, u32 *, 0x14) = (u32) temp_v1_2;
            if (((temp_v0_6 + temp_v1_2) >= 0x100) || (M2C_FIELD(arg2, u16 *, 0x1A) != 0)) {
                M2C_FIELD(temp_s1, u32 *, 0x14) = temp_v1_2 - 1;
            }
            if ((M2C_FIELD(temp_s4, u8 *, 0) ^ M2C_FIELD(temp_s1, u16 *, 0x24)) & 1) {
                temp_a1 = M2C_FIELD(temp_s1, u32 *, 0x10);
                temp_v1_3 = (0 - (s8) M2C_FIELD(temp_s2, volatile u8 *, -2)) - M2C_FIELD(temp_s1, u16 *, 0x108);
                temp_v1_4 = temp_v1_3 + ((s32) ((s16) temp_v1_3 + ((u32) (temp_v1_3 << 0x10) >> 0x1F)) >> 1);
                temp_a1_2 = (s32) (temp_a1 + (temp_a1 >> 0x1F)) >> 1;
                M2C_FIELD(temp_s1, u16 *, 0x70) = temp_v1_4;
                M2C_FIELD(temp_s1, u16 *, 0x78) = (s16) (temp_v1_4 - ((u16) M2C_FIELD(temp_s1, u32 *, 0x10) + temp_a1_2));
                M2C_FIELD(temp_s1, u16 *, 0x80) = (s16) ((0 - (s8) M2C_FIELD(temp_s2, u8 *, -2)) - M2C_FIELD(temp_s1, u16 *, 0x108));
                M2C_FIELD(temp_s1, u16 *, 0x88) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x80) - (u16) M2C_FIELD(temp_s1, u32 *, 0x10));
                goto x_join;
            }
            temp_a1_3 = (s8) M2C_FIELD(temp_s2, volatile u8 *, -2) - M2C_FIELD(temp_s1, volatile u16 *, 0x108);
            temp_a0 = M2C_FIELD(temp_s1, volatile u32 *, 0x10);
            temp_a1_4 = (s16) temp_a1_3;
            temp_a1_4 = (s32) (temp_a1_4 + ((u32) (temp_a1_3 << 0x10) >> 0x1F)) >> 1;
            temp_a1_3 += temp_a1_4;
            M2C_FIELD(temp_s1, u16 *, 0x70) = temp_a1_3;
            temp_a1_3 += (u16) M2C_FIELD(temp_s1, u32 *, 0x10) + ((s32) (temp_a0 + (temp_a0 >> 0x1F)) >> 1);
            M2C_FIELD(temp_s1, u16 *, 0x78) = temp_a1_3;
            temp_v0_7 = (s8) M2C_FIELD(temp_s2, u8 *, -2) - M2C_FIELD(temp_s1, u16 *, 0x108);
            M2C_FIELD(temp_s1, u16 *, 0x80) = temp_v0_7;
            M2C_FIELD(temp_s1, u16 *, 0x88) = (s16) (temp_v0_7 + (u16) M2C_FIELD(temp_s1, u32 *, 0x10));
x_join:
            if ((M2C_FIELD(temp_s4, u8 *, 0) ^ M2C_FIELD(temp_s1, u16 *, 0x24)) & 2) {
                temp_v0_10 = (0 - (s8) M2C_FIELD(temp_s2, volatile u8 *, -1)) - M2C_FIELD(temp_s1, volatile u16 *, 0x10A);
                temp_y_width = M2C_FIELD(temp_s1, volatile u16 *, 0x14);
                M2C_FIELD(temp_s1, volatile u16 *, 0x7A) = temp_v0_10;
                M2C_FIELD(temp_s1, volatile u16 *, 0x72) = temp_v0_10;
                ASM_MEM_BARRIER();
                temp_v0_10 -= temp_y_width;
                goto y_join;
            }
            temp_v0_10 = (s8) M2C_FIELD(temp_s2, volatile u8 *, -1) - M2C_FIELD(temp_s1, volatile u16 *, 0x10A);
            temp_y_width = M2C_FIELD(temp_s1, volatile u16 *, 0x14);
            M2C_FIELD(temp_s1, volatile u16 *, 0x7A) = temp_v0_10;
            M2C_FIELD(temp_s1, volatile u16 *, 0x72) = temp_v0_10;
            ASM_KEEP_NV(temp_v0_10);
            temp_v0_10 = temp_y_width + temp_v0_10;
y_join:
            M2C_FIELD(temp_s1, u16 *, 0x8A) = temp_v0_10;
            M2C_FIELD(temp_s1, u16 *, 0x82) = temp_v0_10;
            ASM_SCHED_BARRIER();
            func_800654B0(temp_s1 + 0x70, temp_s1 + 0x78, temp_s1 + 0x80, temp_s1 + 0x88, temp_s1 + 0xF0, temp_s1 + 0xF4, temp_s1 + 0xF8, temp_s1 + 0xFC, temp_s1 + 0x90, temp_s1 + 0x94);
            M2C_FIELD(temp_s0, u16 *, 1) = (u16) (M2C_FIELD(temp_s1, u16 *, 0xF0) + M2C_FIELD(temp_s1, u16 *, 0xB8));
            M2C_FIELD(temp_s0, u16 *, 3) = (u16) (M2C_FIELD(temp_s1, u16 *, 0xF2) + M2C_FIELD(temp_s1, u16 *, 0xBA));
            M2C_FIELD(temp_s0, u16 *, 0xD) = (u16) (M2C_FIELD(temp_s1, u16 *, 0xF4) + M2C_FIELD(temp_s1, u16 *, 0xB8));
            M2C_FIELD(temp_s0, u16 *, 0xF) = (u16) (M2C_FIELD(temp_s1, u16 *, 0xF6) + M2C_FIELD(temp_s1, u16 *, 0xBA));
            M2C_FIELD(temp_s0, u16 *, 0x19) = (u16) (M2C_FIELD(temp_s1, u16 *, 0xF8) + M2C_FIELD(temp_s1, u16 *, 0xB8));
            M2C_FIELD(temp_s0, u16 *, 0x1B) = (u16) (M2C_FIELD(temp_s1, u16 *, 0xFA) + M2C_FIELD(temp_s1, u16 *, 0xBA));
            var_a2 = 0;
            M2C_FIELD(temp_s0, u16 *, 0x25) = (u16) (M2C_FIELD(temp_s1, u16 *, 0xFC) + M2C_FIELD(temp_s1, u16 *, 0xB8));
            temp_a0_2 = M2C_FIELD(temp_s1, u16 *, 0xFE) + M2C_FIELD(temp_s1, u16 *, 0xBA);
            M2C_FIELD(temp_s0, s16 *, 0x27) = temp_a0_2;
            if ((u32) ((M2C_FIELD(temp_s0, u16 *, 1) + 0x20) & 0xFFFF) < 0x181U) {
                temp_bound = (M2C_FIELD(temp_s0, u16 *, 3) + 0x20) & 0xFFFF;
                ASM_KEEP_NV(temp_bound);
                var_a2 = temp_bound < 0x121U;
            }
            var_v1 = 0;
            if ((u32) ((M2C_FIELD(temp_s0, u16 *, 0xD) + 0x20) & 0xFFFF) < 0x181U) {
                temp_bound = (M2C_FIELD(temp_s0, u16 *, 0xF) + 0x20) & 0xFFFF;
                ASM_KEEP_NV(temp_bound);
                var_v1 = temp_bound < 0x121U;
            }
            var_a1 = 0;
            temp_a2_2 = var_a2 | var_v1;
            if ((u32) ((M2C_FIELD(temp_s0, u16 *, 0x19) + 0x20) & 0xFFFF) < 0x181U) {
                temp_bound = (M2C_FIELD(temp_s0, u16 *, 0x1B) + 0x20) & 0xFFFF;
                ASM_KEEP_NV(temp_bound);
                var_a1 = temp_bound < 0x121U;
            }
            var_v1_2 = 0;
            ASM_KEEP_NV(var_v1_2);
            temp_a1_5 = temp_a2_2 | var_a1;
            if ((u32) ((M2C_FIELD(temp_s0, u16 *, 0x25) + 0x20) & 0xFFFF) < 0x181U) {
                temp_bound = (temp_a0_2 + 0x20) & 0xFFFF;
                ASM_KEEP_NV(temp_bound);
                var_v1_2 = temp_bound < 0x121U;
            }
            temp_any = temp_a1_5 | var_v1_2;
            if (temp_any != 0) {
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0x7FFF);
                temp_x_total = M2C_FIELD(temp_s1, volatile u32 *, 0x10);
                temp_a0_3 = M2C_FIELD(temp_s1, volatile u32 *, 8);
                temp_y_total = M2C_FIELD(temp_s1, volatile u32 *, 0x14);
                temp_a1_6 = M2C_FIELD(temp_s1, volatile u32 *, 0xC);
                temp_x_total += temp_a0_3;
                temp_y_total += temp_a1_6;
                temp_y_total <<= 8;
                M2C_FIELD(temp_s1, u32 *, 0x14) = temp_y_total;
                temp_y_total = temp_a1_6;
                ASM_KEEP_NV(temp_y_total);
                M2C_FIELD(temp_s1, u32 *, 0x10) = temp_x_total;
                temp_flags = M2C_FIELD(temp_s1, u16 *, 0x24);
                temp_y_total <<= 8;
                M2C_FIELD(temp_s1, u32 *, 0xC) = temp_y_total;
                if (temp_flags & 0x100) {
                    M2C_FIELD(temp_s0, s16 *, 7) = (s16) M2C_FIELD(arg2, u16 *, 0x12);
                } else {
                    M2C_FIELD(temp_s0, s16 *, 7) = (s16) (M2C_FIELD(arg2, u16 *, 0x12) + M2C_FIELD(temp_s2, u16 *, 2));
                }
                M2C_FIELD(temp_s0, s16 *, 5) = (s16) ((u16) M2C_FIELD(temp_s1, u32 *, 0xC) + (u16) M2C_FIELD(temp_s1, u32 *, 8));
                M2C_FIELD(temp_s0, s16 *, 0x11) = (s16) ((u16) M2C_FIELD(temp_s1, u32 *, 0xC) + (u16) M2C_FIELD(temp_s1, u32 *, 0x10));
                if (M2C_FIELD(arg2, u16 *, 0x10) != 0) {
                    M2C_FIELD(temp_s0, u16 *, 0x13) = (u16) (M2C_FIELD(arg2, u16 *, 0x10) + (M2C_FIELD(temp_s2, u16 *, 0) & 0xFF9F));
                } else {
                    M2C_FIELD(temp_s0, u16 *, 0x13) = (u16) M2C_FIELD(temp_s2, u16 *, 0);
                }
                M2C_FIELD(temp_s0, s16 *, 0x1D) = (s16) ((u16) M2C_FIELD(temp_s1, u32 *, 0x14) | (u16) M2C_FIELD(temp_s1, u32 *, 8));
                M2C_FIELD(temp_s0, s16 *, 0x29) = (s16) ((u16) M2C_FIELD(temp_s1, u32 *, 0x14) | (u16) M2C_FIELD(temp_s1, u32 *, 0x10));
                temp_v0_8 = (s16) M2C_FIELD(temp_s1, volatile u16 *, 0x50);
                ASM_KEEP_NV(temp_v0_8);
                if (temp_v0_8 >= 0x1800) {
                    temp_v1_5 = (u8) M2C_FIELD(temp_s0, s16 *, 0x29);
                    M2C_FIELD(temp_s0, u8 *, 0x29) = (u8) (temp_v1_5 + 0xFF);
                    M2C_FIELD(temp_s0, u8 *, 0x11) = temp_v1_5;
                }
                temp_v0_9 = (s16) M2C_FIELD(temp_s1, volatile u16 *, 0x58);
                ASM_KEEP_NV(temp_v0_9);
                if (temp_v0_9 >= 0x1800) {
                    temp_v1_6 = M2C_FIELD(temp_s0, u8 *, 0x2A);
                    M2C_FIELD(temp_s0, u8 *, 0x2A) = (u8) (temp_v1_6 + 0xFF);
                    M2C_FIELD(temp_s0, u8 *, 0x1E) = temp_v1_6;
                }
                if ((s16) M2C_FIELD(temp_s0, u16 *, 1) > (s16) M2C_FIELD(temp_s0, u16 *, 0x25)) {
                    temp_v1_7 = (u8) M2C_FIELD(temp_s0, s16 *, 0x29);
                    M2C_FIELD(temp_s0, u8 *, 0x29) = (u8) (temp_v1_7 + 0xFF);
                    M2C_FIELD(temp_s0, u8 *, 0x11) = temp_v1_7;
                }
                if ((s16) M2C_FIELD(temp_s0, u16 *, 3) > M2C_FIELD(temp_s0, s16 *, 0x27)) {
                    temp_v1_8 = M2C_FIELD(temp_s0, u8 *, 0x2A);
                    M2C_FIELD(temp_s0, u8 *, 0x2A) = (u8) (temp_v1_8 + 0xFF);
                    M2C_FIELD(temp_s0, u8 *, 0x1E) = temp_v1_8;
                }
                M2C_FIELD(temp_s0, s32 *, -3) = 0;
                M2C_FIELD(temp_s0, s32 *, 9) = 0;
                temp_tail_0 = M2C_FIELD(arg2, volatile s32 *, 0xC);
                ASM_KEEP_NV(temp_tail_0);
                M2C_FIELD(temp_s0, s32 *, 0x15) = temp_tail_0;
                temp_tail_1 = M2C_FIELD(arg2, volatile s32 *, 0xC);
                M2C_FIELD(temp_s0, s8 *, -4) = 0xC;
                M2C_FIELD(temp_s0, s8 *, 0) = 0x3C;
                M2C_FIELD(temp_s0, s32 *, 0x21) = temp_tail_1;
                if ((M2C_FIELD(temp_s1, u32 *, 0x24) & 0xC) == 0xC) {
                    M2C_FIELD(temp_s0, s8 *, 0) = 0x3E;
                }
                temp_a0_4 = 0xFFFFFF;
                ASM_KEEP_NV(temp_a0_4);
                temp_s0 += 0x34;
                temp_high_mask = 0xFF000000;
                ASM_KEEP_NV(temp_high_mask);
                temp_v1_9 = (M2C_FIELD(temp_s1, u32 *, 0xC0) * 4) + M2C_FIELD(temp_s1, u32 *, 0x20);
                ASM_KEEP_NV(temp_v1_9);
                ASM_SCHED_BARRIER();
                temp_tail_old = M2C_FIELD(var_s5, u32 *, 0);
                temp_tail_table = *temp_v1_9;
                temp_tail_old = (temp_tail_old & temp_high_mask) | (temp_tail_table & temp_a0_4);
                temp_a0_4 = (u32) var_s5 & temp_a0_4;
                ASM_KEEP_NV(temp_a0_4);
                M2C_FIELD(var_s5, u32 *, 0) = temp_tail_old;
                temp_tail_addr = (M2C_FIELD(temp_s1, u32 *, 0xC0) * 4) + M2C_FIELD(temp_s1, u32 *, 0x20);
                ASM_KEEP_NV(temp_tail_addr);
                var_s5 += 0x34;
                *temp_tail_addr = (*temp_tail_addr & temp_high_mask) | temp_a0_4;
                goto block_40;
            }
            goto block_40;
        }
block_40:
        if ((s8) M2C_FIELD(temp_s4, u8 *, 0) >= 0) {
            temp_s2 += 0xC;
            temp_s4 += 0xC;
            goto loop_top;
        }
        func_80064A40();
        M2C_FIELD(M2C_FIELD(temp_s6, void **, 0), void **, 0x8D0) = var_s5;
        return;
    }
    M2C_FIELD(M2C_FIELD(temp_s6, void **, 0), void **, 0x8D0) = var_s5;
}
