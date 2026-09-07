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
typedef u8 *(*FnPtr)(void *, s32, void *, void *, u8 *);
typedef struct { s32 w0, w1, w2, w3; } Blk16;
typedef struct { s32 w0, w1; } Blk8;
typedef struct { s32 a0,a1,a2,a3,a4,a5,a6,a7,a8,a9; } Blk40;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define D_FIELD(type_ptr, offset) (*(type_ptr)(D_80083160 + (offset)))
#define D_LITERAL(type_ptr, offset) (*(type_ptr)((u8 *)0x80083160 + (offset)))
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

void func_80024390() __attribute__((noreturn));
void func_8002443C() __attribute__((noreturn));
void func_800244B0() __attribute__((noreturn));
void func_80024638() __attribute__((noreturn));
void func_80024640() __attribute__((noreturn));
void func_80024690() __attribute__((noreturn));
void func_80024958() __attribute__((noreturn));
void func_80024AA0() __attribute__((noreturn));
M2C_UNK func_80064840();
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80064BC0();
M2C_UNK func_80064CF0();
M2C_UNK func_80064D80();
M2C_UNK func_800654B0();
M2C_UNK func_80065820();
M2C_UNK func_80067EF4();
extern M2C_UNK D_8006CD10[3];
extern u8 D_80083160[];

void func_81904990(void *arg0, void *arg1, s32 *arg2, s32 arg3) {
    u16 arg3_copy;
    s32 sp30_0;
    M2C_UNK var_a1;
    s32 byte_b;
    register s32 sh16 ASM_REG("$2");
    s32 m256_t;
    u8 *cpv0;
    void *dpg;
    void *ca0;
    s32 ca1;
    void *ca2;
    void *ca3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 temp_v0_8;
    s16 temp_v0_9;
    u16 temp_tail_src;
    FnPtr temp_v0_10;
    u8 *blk;
    s32 *temp_v1;
    s32 *temp_v1_10;
    s32 *temp_v1_11;
    s32 *temp_v1_7;
    s32 *temp_v1_8;
    s32 *temp_v1_9;
    u8 *var_a0_2;
    u8 *var_s1;
    register u8 *var_t0 ASM_REG("$8");
    s32 temp_a0_2;
    s32 tA0;
    s32 tA1;
    s32 tA2;
    s32 tA3;
    s32 temp_a3;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_t3;
    s32 var_t4;
    u16 temp_v0;
    u16 temp_v0_2;
    u32 temp_s4_12;
    u16 temp_s4_16;
    u16 temp_v1_6;
    register u8 temp_a0 ASM_REG("$4");
    u8 temp_v1_4;
    u8 temp_v1_5;
    register u8 var_v0 ASM_REG("$2");
    u8 *temp_s0;
    void *temp_s4;
    u8 *temp_s5;
    void *var_a0;
    void *var_t2;
    M2C_UNK *d6;
    s32 nine;
    s32 tail_v0;
    s32 tail_v1;
    register s32 mask24 ASM_REG("$19");
    s32 mask_top;
    register u8 *scratch ASM_REG("$18");
    register void *base ASM_REG("$23");

    var_a0 = arg0;
    base = arg1;
    temp_s4 = M2C_FIELD(base, void **, -0x14);
    {
        void **q;
        q = (void **)D_80083160;
        ASM_CLOBBER("$2");
        sp30_0 = M2C_FIELD(base, s32 *, -0x18);
        dpg = *q;
    }
    temp_s5 = M2C_FIELD(temp_s4, void **, 8);
    scratch = (u8 *)0x1F800000;
    ASM_KEEP(scratch);
    M2C_FIELD(scratch, s32 *, 0x0EC) = NULL;
    M2C_FIELD(scratch, u16 *, 0x08C) = 0;
    M2C_FIELD(scratch, u16 *, 0x084) = 0;
    M2C_FIELD(scratch, u16 *, 0x07C) = 0;
    M2C_FIELD(scratch, u16 *, 0x074) = 0;
    var_s1 = M2C_FIELD(dpg, u8 **, 0x8D0);
    M2C_FIELD(scratch, s32 **, 0x020) = arg2;
    M2C_FIELD(scratch, s32 *, 0x0C0) = NULL;
    M2C_FIELD(scratch, u16 *, 0x0B8) = (s16) (M2C_FIELD(var_a0, u16 *, 0) - 0xA0);
    M2C_FIELD(scratch, u16 *, 0x0BA) = (u16) (M2C_FIELD(var_a0, u16 *, 2) - 0x78);
    arg3_copy = (u16) arg3;
    temp_a3 = arg3 << 0x10;
    var_a1 = 0;
    if (temp_a3 != 0) {
        func_80067EF4(var_s1, 0, 0, temp_a3);
        {
        s32 m24l = 0xFFFFFF;
        var_a1 = 0xFF000000;
        M2C_FIELD(var_s1, s32 *, 0) = (M2C_FIELD(var_s1, s32 *, 0) & 0xFF000000) | (*M2C_FIELD(scratch, s32 **, 0x020) & m24l);
        }
        temp_v1 = M2C_FIELD(scratch, s32 **, 0x020);
        var_a0 = (void *) ((s32) var_s1 & 0xFFFFFF);
        var_s1 += 12;
        *temp_v1 = (*temp_v1 & 0xFF000000) | (s32) var_a0;
    }
    nine = 9;
    ASM_KEEP_NV(nine);
    mask24 = 0xFFFFFF;
    mask_top = 0xFF000000;
    ASM_KEEP_NV(mask_top);
    d6 = D_8006CD10;
    M2C_FIELD(d6, s32 *, 0x1C) = (s32) D_FIELD(s32 *, 0xA0);
    func_800649A0((s32) var_a0, var_a1);
    {
        s32 d_c4;
        s32 d_c6;
        s32 d_c8;
        d_c4 = D_FIELD(s16 *, 0xC4);
        d_c6 = D_FIELD(s16 *, 0xC6);
        d_c8 = D_FIELD(s16 *, 0xC8);
        M2C_FIELD(scratch, s32 *, 0x030) = d_c4;
        M2C_FIELD(scratch, s32 *, 0x034) = d_c6;
        M2C_FIELD(scratch, s32 *, 0x038) = d_c8;
    }
    M2C_FIELD(scratch, u16 *, 0x100) = (u16) M2C_FIELD(temp_s4, u16 *, 0x16);
    M2C_FIELD(scratch, u16 *, 0x104) = (s16) (M2C_FIELD(temp_s4, u16 *, 0x1A) - (u16) M2C_FIELD(scratch, s32 *, 0x034));
    temp_v0 = (((u16) M2C_FIELD(scratch, s32 *, 0x038) + 0x100) & 0x1FF);
    m256_t = M2C_FIELD(temp_s4, u16 *, 0x18) - 0x100;
    M2C_FIELD(scratch, u16 *, 0x102) = temp_v0 + m256_t;
    temp_v0 = M2C_FIELD(temp_s4, u16 *, 0x20);
    M2C_FIELD(scratch, s32 *, 0x0E4) = (s32) temp_v0;
    M2C_FIELD(scratch, u16 *, 0x108) = temp_v0;
    temp_v0_2 = M2C_FIELD(temp_s4, u16 *, 0x22);
    M2C_FIELD(scratch, s32 *, 0x0E8) = (s32) temp_v0_2;
    M2C_FIELD(scratch, u16 *, 0x10A) = temp_v0_2;
    func_80065820((void *)0x1F800100, (void *)0x1F8000D0);
    {
        s32 e1c;
        s32 e1e;
        e1c = M2C_FIELD(temp_s4, u16 *, 0x1C);
        M2C_FIELD(scratch, s32 *, 0x030) = e1c;
        e1e = M2C_FIELD(temp_s4, u16 *, 0x1E);
        M2C_FIELD(scratch, s32 *, 0x038) = (s32)0x1000;
        M2C_FIELD(scratch, s32 *, 0x034) = e1e;
    }
    func_80064BC0((void *)0x1F8000D0, (void *)0x1F800030);
    func_80064840(d6, (void *)0x1F8000D0, (void *)0x1F800050);
    func_80064D80((void *)0x1F800050);
    func_80064CF0((void *)0x1F800050);
    temp_s0 = temp_s5 + 8;
    ASM_KEEP_NV(temp_s0);
    M2C_FIELD(scratch, u16 *, 0x024) = (u16) M2C_FIELD(temp_s4, u16 *, 0x14);
    if (!(M2C_FIELD(temp_s5, u8 *, 0) & 0x20)) {
        M2C_FIELD(scratch, s32 *, 0x008) = (s32) M2C_FIELD(temp_s0, u8 *, 0);
        M2C_FIELD(scratch, s32 *, 0x00C) = (s32) M2C_FIELD(temp_s0, u8 *, 1);
        M2C_FIELD(scratch, s32 *, 0x010) = (s32) M2C_FIELD(temp_s0, u8 *, 2);
        M2C_FIELD(scratch, s32 *, 0x014) = (s32) M2C_FIELD(temp_s0, u8 *, 3);
        if ((M2C_FIELD(temp_s5, u8 *, 0) ^ M2C_FIELD(scratch, u16 *, 0x024)) & 1) {
            byte_b = *(volatile u8 *)((s8 *)temp_s0 + -6);
            tail_v0 = (0 - (s32)(s8) byte_b) - M2C_FIELD(scratch, u16 *, 0x108);
            M2C_FIELD(scratch, u16 *, 0x080) = tail_v0;
            M2C_FIELD(scratch, u16 *, 0x070) = tail_v0;
            tail_v0 = tail_v0 - M2C_FIELD(scratch, u16 *, 0x010);
            ASM_TAILSLOT_PIN(tail_v0);
            func_8002443C((u16) M2C_FIELD(scratch, s32 *, 0x010));
            return;
        }
        byte_b = *(volatile u8 *)((s8 *)temp_s0 + -6);
        temp_v0_4 = (s32)(s8) byte_b - M2C_FIELD(scratch, u16 *, 0x108);
        M2C_FIELD(scratch, u16 *, 0x080) = temp_v0_4;
        M2C_FIELD(scratch, u16 *, 0x070) = temp_v0_4;
        temp_v0_5 = temp_v0_4 + (u16) M2C_FIELD(scratch, s32 *, 0x010);
        M2C_FIELD(scratch, u16 *, 0x088) = temp_v0_5;
        M2C_FIELD(scratch, u16 *, 0x078) = temp_v0_5;
        if ((M2C_FIELD(temp_s5, u8 *, 0) ^ M2C_FIELD(scratch, u16 *, 0x024)) & 2) {
            byte_b = *(volatile u8 *)((s8 *)temp_s0 + -5);
            tail_v0 = (0 - (s32)(s8) byte_b) - M2C_FIELD(scratch, u16 *, 0x10A);
            M2C_FIELD(scratch, u16 *, 0x07A) = tail_v0;
            M2C_FIELD(scratch, u16 *, 0x072) = tail_v0;
            tail_v0 = tail_v0 - M2C_FIELD(scratch, u16 *, 0x014);
            ASM_TAILSLOT_PIN(tail_v0);
            func_800244B0((u16) M2C_FIELD(scratch, s32 *, 0x014));
            return;
        }
        byte_b = *(volatile u8 *)((s8 *)temp_s0 + -5);
        temp_v0_7 = (s32)(s8) byte_b - M2C_FIELD(scratch, u16 *, 0x10A);
        M2C_FIELD(scratch, u16 *, 0x07A) = temp_v0_7;
        M2C_FIELD(scratch, u16 *, 0x072) = temp_v0_7;
        temp_v0_8 = temp_v0_7 + (u16) M2C_FIELD(scratch, s32 *, 0x014);
        M2C_FIELD(scratch, u16 *, 0x08A) = temp_v0_8;
        M2C_FIELD(scratch, u16 *, 0x082) = temp_v0_8;
        ASM_SCHED_BARRIER();
    func_800654B0(scratch + 0x70, scratch + 0x78, scratch + 0x80, scratch + 0x88, scratch + 0xF0, scratch + 0xF4, scratch + 0xF8, scratch + 0xFC, scratch + 0x90, scratch + 0x94);
        M2C_FIELD(var_s1, s16 *, 8) = (s16) (M2C_FIELD(scratch, u16 *, 0x0F0) + M2C_FIELD(scratch, u16 *, 0x0B8));
        M2C_FIELD(var_s1, s16 *, 0xA) = (s16) (M2C_FIELD(scratch, u16 *, 0x0F2) + M2C_FIELD(scratch, u16 *, 0x0BA));
        M2C_FIELD(var_s1, s16 *, 0x10) = (s16) (M2C_FIELD(scratch, u16 *, 0x0F4) + M2C_FIELD(scratch, u16 *, 0x0B8));
        M2C_FIELD(var_s1, s16 *, 0x12) = (s16) (M2C_FIELD(scratch, u16 *, 0x0F6) + M2C_FIELD(scratch, u16 *, 0x0BA));
        M2C_FIELD(var_s1, s16 *, 0x18) = (s16) (M2C_FIELD(scratch, u16 *, 0x0F8) + M2C_FIELD(scratch, u16 *, 0x0B8));
        M2C_FIELD(var_s1, s16 *, 0x1A) = (s16) (M2C_FIELD(scratch, u16 *, 0x0FA) + M2C_FIELD(scratch, u16 *, 0x0BA));
        M2C_FIELD(var_s1, s16 *, 0x20) = (s16) (M2C_FIELD(scratch, u16 *, 0x0FC) + M2C_FIELD(scratch, u16 *, 0x0B8));
        M2C_FIELD(var_s1, s16 *, 0x22) = (s16) (M2C_FIELD(scratch, u16 *, 0x0FE) + M2C_FIELD(scratch, u16 *, 0x0BA));
        M2C_FIELD(var_s1, s8 *, 3) = nine;
        ASM_USE2_NV(nine, nine);
        {
            s32 t10 = M2C_FIELD(scratch, s32 *, 0x010);
            s32 t08 = M2C_FIELD(scratch, s32 *, 0x008);
            t10 = t10 - 1;
            {
                s32 t08b = t10 + t08;
                temp_v1_2 = t08b;
            }
        }
        M2C_FIELD(scratch, s32 *, 0x010) = temp_v1_2;
        if (temp_v1_2 & 0x100) {
            M2C_FIELD(scratch, s32 *, 0x010) = temp_v1_2 - 1;
        }
        {
            s32 t14 = M2C_FIELD(scratch, s32 *, 0x014);
            s32 t0c = M2C_FIELD(scratch, s32 *, 0x00C);
            t14 = t14 - 1;
            {
                s32 t0cb = t14 + t0c;
                temp_v1_3 = t0cb;
            }
        }
        M2C_FIELD(scratch, s32 *, 0x014) = temp_v1_3;
        if (temp_v1_3 & 0x100) {
            M2C_FIELD(scratch, s32 *, 0x014) = temp_v1_3 - 1;
        }
        M2C_FIELD(scratch, s32 *, 0x014) <<= 8;
        M2C_FIELD(scratch, s32 *, 0x00C) <<= 8;
        temp_s4_12 = M2C_FIELD(temp_s4, u16 *, 0x12);
        if (temp_s4_12 != 0) {
            if (M2C_FIELD(scratch, u16 *, 0x024) & 0x100) {
                M2C_FIELD(var_s1, u16 *, 0xE) = temp_s4_12;
                func_80024640();
                return;
            }
            tail_v0 = temp_s4_12 + M2C_FIELD(temp_s0, u16 *, -2);
            ASM_TAILSLOT_PIN(tail_v0);
            func_80024638();
            return;
        }
        M2C_FIELD(var_s1, u16 *, 0xE) = (u16) M2C_FIELD(temp_s0, u16 *, -2);
        M2C_FIELD(var_s1, s16 *, 0xC) = (s16) ((u16) M2C_FIELD(scratch, s32 *, 0x00C) + (u16) M2C_FIELD(scratch, s32 *, 0x008));
        M2C_FIELD(var_s1, s16 *, 0x14) = (s16) ((u16) M2C_FIELD(scratch, s32 *, 0x00C) + (u16) M2C_FIELD(scratch, s32 *, 0x010));
        temp_s4_16 = M2C_FIELD(temp_s4, u16 *, 0x10);
        if (temp_s4_16 != 0) {
            temp_tail_src = M2C_FIELD(temp_s0, u16 *, -4) & 0xFF9F;
            tail_v0 = temp_s4_16 + temp_tail_src;
            ASM_TAILSLOT_PIN(tail_v0);
            func_80024690();
            return;
        }
        M2C_FIELD(var_s1, u16 *, 0x16) = (u16) M2C_FIELD(temp_s0, u16 *, -4);
        M2C_FIELD(var_s1, s16 *, 0x1C) = (s16) ((u16) M2C_FIELD(scratch, s32 *, 0x014) | (u16) M2C_FIELD(scratch, s32 *, 0x008));
        {
            register s32 h14 ASM_REG("$3");
            h14 = (u16) M2C_FIELD(scratch, s32 *, 0x014);
            M2C_FIELD(var_s1, s16 *, 0x24) = (s16) (h14 | (u16) M2C_FIELD(scratch, s32 *, 0x010));
        }
        if (M2C_FIELD(var_s1, s16 *, 0x20) < M2C_FIELD(var_s1, s16 *, 8)) {
            temp_v1_4 = (u8) M2C_FIELD(var_s1, s16 *, 0x24);
            M2C_FIELD(var_s1, u8 *, 0x24) = (u8) (temp_v1_4 + 0xFF);
            M2C_FIELD(var_s1, u8 *, 0x14) = temp_v1_4;
        }
        if (M2C_FIELD(var_s1, s16 *, 0xA) > M2C_FIELD(var_s1, s16 *, 0x22)) {
            temp_v1_5 = M2C_FIELD(var_s1, u8 *, 0x25);
            M2C_FIELD(var_s1, u8 *, 0x25) = (u8) (temp_v1_5 + 0xFF);
            M2C_FIELD(var_s1, u8 *, 0x1D) = temp_v1_5;
        }
        temp_a0 = M2C_FIELD(temp_s0, u8 *, -7);
        M2C_FIELD(temp_s4, u8 *, 0xF) = temp_a0;
        temp_v1_6 = M2C_FIELD(scratch, u16 *, 0x024);
        if (temp_v1_6 & 8) {
            var_v0 = temp_v1_6 & 4;
            if (var_v0 != 0) {
                var_v0 = temp_a0 | 2;
            } else {
                var_v0 = temp_a0 & 0xFD;
            }
            M2C_FIELD(temp_s4, u8 *, 0xF) = var_v0;
        }
        blk = var_s1;
        M2C_FIELD(var_s1, s32 *, 4) = (s32) M2C_FIELD(temp_s4, s32 *, 0xC);
        M2C_FIELD(base, u16 *, 0x62) = (u16) M2C_FIELD(var_s1, s16 *, 0xA);
        var_t0 = blk + 32;
        temp_v0_9 = (u16) M2C_FIELD(var_s1, s16 *, 0xA) + M2C_FIELD(base, u16 *, 0x64);
        M2C_FIELD(var_s1, s16 *, 0x22) = temp_v0_9;
        M2C_FIELD(var_s1, s16 *, 0x1A) = temp_v0_9;
        tA0 = (s32) var_s1 & mask24;
        M2C_FIELD(var_s1, s32 *, 0) = (M2C_FIELD(var_s1, s32 *, 0) & mask_top) | (*M2C_FIELD(scratch, s32 **, 0x020) & mask24);
        temp_v1_7 = M2C_FIELD(scratch, s32 **, 0x020);
        var_s1 += 40;
        *temp_v1_7 = (*temp_v1_7 & mask_top) | tA0;
        M2C_FIELD(var_s1, s8 *, 3) = nine;

        *(Blk40 *)var_s1 = *(Blk40 *)blk;
        var_t4 = 1;
        var_t3 = -0x30;
        var_t2 = base + 2;
        tA1 = (s32) var_s1 & mask24;
        M2C_FIELD(var_s1, u16 *, 8) = (u16) (M2C_FIELD(var_s1, u16 *, 8) + 0x40);
        M2C_FIELD(var_s1, u16 *, 0x10) = (u16) (M2C_FIELD(var_s1, u16 *, 0x10) + 0x40);
        M2C_FIELD(var_s1, u16 *, 0x18) = (u16) (M2C_FIELD(var_s1, u16 *, 0x18) + 0x40);
        M2C_FIELD(var_s1, u16 *, 0x20) = (u16) (M2C_FIELD(var_s1, u16 *, 0x20) + 0x40);
        M2C_FIELD(var_s1, s32 *, 0) = (M2C_FIELD(var_s1, s32 *, 0) & mask_top) | (*M2C_FIELD(scratch, s32 **, 0x020) & mask24);
        temp_v1_8 = M2C_FIELD(scratch, s32 **, 0x020);
        var_s1 += 40;
        var_t0 = var_s1 + 32;
        *temp_v1_8 = (*temp_v1_8 & mask_top) | tA1;
loop_33:
        M2C_FIELD(var_t0, s8 *, -0x1D) = nine;
        *(Blk40 *)var_s1 = *(Blk40 *)blk;
        M2C_FIELD(var_t0, s16 *, -0x16) = (s16) (M2C_FIELD(base, u16 *, 0x62) + M2C_FIELD(var_t2, u16 *, 0x62));
        M2C_FIELD(var_t0, s16 *, -0xE) = (s16) (M2C_FIELD(base, u16 *, 0x62) + M2C_FIELD(var_t2, u16 *, 0x62));
        M2C_FIELD(var_t0, s16 *, -6) = (s16) (M2C_FIELD(base, u16 *, 0x62) + M2C_FIELD(var_t2, u16 *, 0x64));
        M2C_FIELD(var_t0, s16 *, 2) = (s16) (M2C_FIELD(base, u16 *, 0x62) + M2C_FIELD(var_t2, u16 *, 0x64));
        temp_a0_2 = var_t4 * 0x10;
        if (var_t4 < 4) {
            tail_v0 = M2C_FIELD(var_t0, u8 *, -0x13);
            tail_v1 = M2C_FIELD(var_t0, u8 *, -0xB);
            tail_v0 = tail_v0 + temp_a0_2;
            M2C_FIELD(var_t0, u8 *, -0x13) = (u8) tail_v0;
            tail_v0 = M2C_FIELD(var_t0, u8 *, -3);
            tail_v1 = tail_v1 + temp_a0_2;
            M2C_FIELD(var_t0, u8 *, -0xB) = (u8) tail_v1;
            tail_v1 = M2C_FIELD(var_t0, u8 *, 5);
            tail_v0 = tail_v0 + temp_a0_2;
            tail_v1 = tail_v1 + temp_a0_2;
            ASM_KEEP(tail_v0);
            ASM_TAILSLOT_PIN(tail_v1);
            func_80024958();
            return;
        }
        tail_v0 = M2C_FIELD(var_t0, u8 *, -0x13);
        tail_v1 = M2C_FIELD(var_t0, u8 *, -0xB);
        tail_v0 = tail_v0 + var_t3;
        M2C_FIELD(var_t0, u8 *, -0x13) = (u8) tail_v0;
        tail_v0 = M2C_FIELD(var_t0, u8 *, -3);
        tail_v1 = tail_v1 + var_t3;
        M2C_FIELD(var_t0, u8 *, -0xB) = (u8) tail_v1;
        tail_v1 = M2C_FIELD(var_t0, u8 *, 5);
        tail_v0 = tail_v0 + var_t3;
        tail_v1 = tail_v1 + var_t3;
        M2C_FIELD(var_t0, u8 *, -3) = (u8) tail_v0;
        M2C_FIELD(var_t0, u8 *, 5) = (u8) tail_v1;
        var_t0 += 40;
        cpv0 = var_s1;
        ASM_KEEP(cpv0);
        tA2 = (s32) var_s1 & mask24;
        {
            register s32 sv ASM_REG("$2");
            sv = M2C_FIELD(var_s1, s32 *, 0);
            M2C_FIELD(var_s1, s32 *, 0) = (sv & mask_top) | (*M2C_FIELD(scratch, s32 **, 0x020) & mask24);
        }
        temp_v1_9 = M2C_FIELD(scratch, s32 **, 0x020);
        var_s1 += 40;
        *temp_v1_9 = (*temp_v1_9 & mask_top) | tA2;
        M2C_FIELD(var_t0, s8 *, -0x1D) = nine;
        *(Blk40 *)var_s1 = *(Blk40 *)cpv0;
        var_t3 += 0x10;
        var_t2 = (u8 *)var_t2 + 2;
        var_t4 += 1;
        tA3 = (s32) var_s1 & mask24;
        M2C_FIELD(var_t0, u16 *, -0x18) = (u16) (M2C_FIELD(var_t0, u16 *, -0x18) + 0x40);
        M2C_FIELD(var_t0, u16 *, -0x10) = (u16) (M2C_FIELD(var_t0, u16 *, -0x10) + 0x40);
        M2C_FIELD(var_t0, u16 *, -8) = (u16) (M2C_FIELD(var_t0, u16 *, -8) + 0x40);
        M2C_FIELD(var_t0, u16 *, 0) = (u16) (M2C_FIELD(var_t0, u16 *, 0) + 0x40);
        {
            register s32 sv ASM_REG("$2");
            sv = M2C_FIELD(var_s1, s32 *, 0);
            M2C_FIELD(var_s1, s32 *, 0) = (sv & mask_top) | (*M2C_FIELD(scratch, s32 **, 0x020) & mask24);
        }
        temp_v1_10 = M2C_FIELD(scratch, s32 **, 0x020);
        var_t0 += 40;
        *temp_v1_10 = (*temp_v1_10 & mask_top) | tA3;
        var_s1 += 40;
        if (var_t4 < 8) {
            goto loop_33;
        }
        func_80024AA0();
    }
    temp_v0_10 = M2C_FIELD(temp_s0, FnPtr *, 0);
    if (temp_v0_10 != NULL) {
        ca0 = base;
        ca2 = temp_s4;
        ca1 = sp30_0;
        ca3 = temp_s5;
        var_s1 = temp_v0_10(ca0, ca1, ca2, ca3, var_s1);
    }
    if ((s8) M2C_FIELD(temp_s5, u8 *, 0) >= 0) {
        temp_s0 += 12;
        temp_s5 += 12;
        ASM_KEEP(temp_s0);
        ASM_TAILSLOT_PIN(temp_s5);
        func_80024390();
        return;
    }
    sh16 = arg3_copy << 0x10;

    var_a0_2 = var_s1;
    if (sh16 != 0) {
        func_80067EF4(var_a0_2, 0, 1);
        M2C_FIELD(var_s1, s32 *, 0) = (M2C_FIELD(var_s1, s32 *, 0) & 0xFF000000) | (*M2C_FIELD(scratch, s32 **, 0x020) & 0xFFFFFF);
        temp_v1_11 = M2C_FIELD(scratch, s32 **, 0x020);
        var_a0_2 = (u8 *) ((s32) var_s1 & 0xFFFFFF);
        var_s1 += 12;
        *temp_v1_11 = (*temp_v1_11 & 0xFF000000) | (s32) var_a0_2;
    }
    func_80064A40((s32) var_a0_2);
    {
        u8 *tp = D_80083160;
        u64 raw = *(u64 *)tp;
        void *root = (void *)(u32)raw;
        M2C_FIELD(root, u8 **, 0x8D0) = var_s1;
    }
}
