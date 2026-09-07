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

s32 func_8003AD08();
void func_800419EC();
s32 func_80042900();
M2C_UNK func_80094E34();
s32 func_80098250();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_8009929C();
s32 func_8009955C();
s32 func_80099734();
M2C_UNK func_80099C58();
M2C_UNK func_8009BF7C();
M2C_UNK func_8009BFF8();
void *func_8009C31C();
void *func_8009C3EC();
void *func_8009C4A4();
void *func_8009C4F4();
void *func_8009C544();
void *func_8009C57C();
void *func_8009C644();
void *func_8009C6A4();
void *func_8009C6D0(s32, s32);
void *func_8009C908();
s32 func_8009CD58();
M2C_UNK func_800A2D68();
M2C_UNK func_800A56E0();
M2C_UNK func_800A5720();
M2C_UNK func_800B4C7C();
s16 func_800B5ED0();
M2C_UNK func_800C7DEC();
s32 func_800C82B8();
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern void *D_80083470[3];
extern M2C_UNK D_800E0D7B;
extern M2C_UNK D_800E0D92;
extern M2C_UNK D_800E0D9E;
extern M2C_UNK D_800E0DB8;
extern M2C_UNK D_800E0DD0;
extern M2C_UNK D_800E0DDD;
extern M2C_UNK D_800E0DEA;
extern M2C_UNK D_800E3648;
extern void *D_800E3D7C[3];

void *func_8009C12C(void *arg0_in, void *arg1_in, s16 arg2, s16 arg3) {
    register void *arg0 ASM_REG("$20") = arg0_in;
    void *arg1 = arg1_in;
    s16 temp_v0;
    s16 temp_v0_5;
    s32 var_a2;
    register s16 var_s6 ASM_REG("$22");
    register s32 temp_a2 ASM_REG("$6");
    s32 temp_s0;
    s32 temp_s0_2;
    register s32 temp_s3 ASM_REG("$19");
    register s32 temp_s7 ASM_REG("$23");
    register s32 temp_v0_3 ASM_REG("$21");
    s32 temp_v0_6;
    s8 temp_s8;
    s32 temp_v1;
    s32 temp_v1_3;
    s32 temp_v1_7;
    register s32 temp_v1_5 ASM_REG("$3");
    s32 var_a3;
    register u32 bf_arg ASM_REG("$4");
    register s32 var_s0 ASM_REG("$16");
    register s32 var_s2 ASM_REG("$18");
    register s32 var_v0_2 ASM_REG("$2");
    register s32 var_v0_3 ASM_REG("$2");
    register s32 var_v0_4 ASM_REG("$2");
    register s32 var_v0_5 ASM_REG("$2");
    u16 *temp_v0_4;
    u16 temp_v1_2;
    u16 temp_v1_4;
    register u8 temp_v0_7 ASM_REG("$4");
    register void *temp_ptr ASM_REG("$3");
    register s16 *table_base ASM_REG("$5");
    register s16 *table_v0 ASM_REG("$2");
    register u16 table_raw ASM_REG("$12");
    register s32 table_a0 ASM_REG("$4");
    register s32 table_step ASM_REG("$9");
    register s32 table_a1 ASM_REG("$8");
    register s32 table_b0 ASM_REG("$10");
    register s32 table_x ASM_REG("$11");
    register s32 table_y ASM_REG("$5");
    register s32 hard_zero ASM_REG("$0");
    struct {
        volatile u16 arg2;
        u8 gap[6];
        u16 arg3;
    } homes;
    register void **var_v1 ASM_REG("$3");
    register void *temp_s1 ASM_REG("$17");
    void *var_a0;
    void *var_v0;

    var_s2 = 0;
#ifdef NON_MATCHING
    hard_zero = 0;
#endif
    ASM_KEEP(arg0);
    M2C_FIELD(arg0, s8 *, 0x73) = 0;
    ASM_KEEP(arg1);
    M2C_FIELD(arg0, s8 *, 0x72) = 0;
    ASM_KEEP(arg2);
    homes.arg2 = arg2;
    temp_s1 = M2C_FIELD(arg0, void **, 0x60);
    var_s6 = var_s2;
    homes.arg3 = arg3;
    if (temp_s1 == NULL) {
        register void *entry_page ASM_REG("$2");
        ASM_SCHED_BARRIER();
        entry_page = (void *)0x800E0000;
        var_v0 = NULL;
        ASM_KEEP(entry_page);
        if (arg0 == M2C_FIELD(entry_page, void **, 0x3D7C)) {
            temp_v0 = func_800B5ED0(M2C_FIELD(arg1, u8 *, 0x24), M2C_FIELD(arg1, u8 *, 0x25), arg2, M2C_FIELD(arg0, s16 *, 0x88));
            var_v0 = NULL;
            if (temp_v0 >= 0) {
                register s32 table_a0 ASM_REG("$4");
                register s32 table_v1 ASM_REG("$3");
                s32 built;
                temp_v0_3 = func_800990FC();
                built = func_8009929C(8, temp_v0_3);
                table_a0 = temp_v0 << 2;
                table_v1 = (s32)&D_800E3648;
                table_a0 += table_v1;
                built = func_8009955C(table_a0, built);
                built = func_80099194(&D_800E0D7B, built);
                func_80099290(built);
                func_800A5720(temp_v0_3);
                func_800A56E0(0x700);
                func_800A2D68(arg0, 8);
                func_800B4C7C(0x82, arg0, 8, 1);
                func_8009C908();
            }
        }
        return NULL;
    }
    temp_v0_3 = func_800990FC();
    var_s0 = temp_v0_3;
    temp_s8 = M2C_FIELD(arg0, s8 *, 0x13);
    temp_v0_7 = *(volatile u8 *)((s8 *)arg0 + 0x13);
    if (temp_s8 >= 0) {
        temp_ptr = M2C_FIELD(temp_s1, void **, -0x14);
        temp_v1_2 = M2C_FIELD(temp_ptr, u16 *, 0x14);
        if (!(M2C_FIELD(arg1, u16 *, 0x14) & temp_v1_2 & 0x8000) || ((temp_v0_7 == 0x23) && (M2C_FIELD(arg0, s16 *, 0xA6) != 0) && !(temp_v1_2 & 0x8000))) {
            var_s0 = func_8009929C(0xA, func_80099194(&D_800E0D92, func_80099734(arg0, temp_v0_3)));
            ASM_TAILSLOT_PIN_TIED(var_s0);
            return func_8009C31C();
        }
        temp_v1_3 = M2C_FIELD(arg0, s32 *, 0x14) & 0x4000;
        if ((temp_v1_3 != 0) || (var_s6 = -1, ((M2C_FIELD(temp_s1, s32 *, 0x14) & 0x4000) != 0))) {
            var_a0 = temp_s1;
            if (temp_v1_3 != 0) {
                var_a0 = arg0;
            }
            var_s0 = func_80099194(&D_800E0D9E, func_80099734(var_a0, var_s0));
            var_s6 = 1;
        }
        goto block_17;
    }
block_17:
    M2C_FIELD(temp_s1, s32 *, 0x14) = (s32) (M2C_FIELD(temp_s1, s32 *, 0x14) | 0x01000000);
    if (M2C_FIELD(arg0, s32 *, 0x14) & 0x04000000) {
        func_800B4C7C(3, temp_s1, -1, 0);
        if (M2C_FIELD(arg0, s8 *, 0x13) >= 0) {
            var_v0_5 = var_s6 << 16;
            ASM_KEEP(var_v0_5);
            var_s2 = var_v0_5 >> 16;
            if (var_s2 == 0) {
                var_s0 = func_80099194(&D_800E0DB8, func_80099734(temp_s1, var_s0));
            }
            var_v0 = NULL;
            if (var_s2 >= 0) {
                func_80099290(var_s0);
                func_800A5720(temp_v0_3);
                func_8009C908();
                return (void *)hard_zero;
            }
            return var_v0;
        }
        func_8009C908();
        return (void *)hard_zero;
    }
    temp_v0_4 = M2C_FIELD(arg0, u16 **, 0x4C);
    if ((temp_v0_4 != NULL) && (*temp_v0_4 == 0xF0D)) {
        M2C_FIELD(temp_s1, u16 *, 0x22) = M2C_FIELD(temp_s1, u8 *, 0x27);
        return func_8009C3EC();
    }
    M2C_FIELD(temp_s1, volatile u16 *, 0x22) = (u16) (M2C_FIELD(temp_s1, u8 *, 0x27) + func_80098250(temp_s1));
    ASM_SCHED_BARRIER();
    if ((func_80042900(temp_s1, 0xA) << 0x10) != 0) {
        M2C_FIELD(temp_s1, u16 *, 0x22) = (u16) ((s32) (M2C_FIELD(temp_s1, u16 *, 0x22) << 0x10) >> 0x11);
    }
    {
        s16 field_22 = M2C_FIELD(temp_s1, s16 *, 0x22);
        u16 field_22_u = M2C_FIELD(temp_s1, volatile u16 *, 0x22);
        if (field_22 == 0) {
            M2C_FIELD(temp_s1, u16 *, 0x22) = (u16) (field_22_u + 1);
        }
    }
    temp_s7 = func_8009CD58(arg0, 7, 1);
    temp_s3 = func_8009CD58(temp_s1, 7, 0);
    if (temp_s7 & 1) {
        if ((func_80042900(temp_s1, 0x13) << 0x10) != 0) {
            M2C_FIELD(arg0, u16 *, 0x20) = (u16) ((s32) (M2C_FIELD(arg0, u16 *, 0x20) << 0x10) >> 0x12);
            return func_8009C4A4();
        }
        if (temp_s3 & 4) {
            var_s2 += 1;
        }
        var_v0_2 = temp_s3 & 2;
        if (var_v0_2) {
            var_s2 -= 2;
            goto block_41;
        }
        goto block_42;
    }
block_41:
block_42:
    var_v0_2 = temp_s7 & 2;
    if (var_v0_2 != 0) {
        if ((func_80042900(temp_s1, 0x14) << 0x10) != 0) {
            M2C_FIELD(arg0, u16 *, 0x20) = (u16) ((s32) (M2C_FIELD(arg0, u16 *, 0x20) << 0x10) >> 0x12);
            return func_8009C4F4();
        }
        if (temp_s3 & 1) {
            var_s2 += 1;
        }
        var_v0_3 = temp_s3 & 4;
        if (var_v0_3) {
            var_s2 -= 2;
            goto block_50;
        }
        goto block_51;
    }
block_50:
block_51:
    var_v0_3 = temp_s7 & 4;
    if (var_v0_3 != 0) {
        if ((func_80042900(temp_s1, 0x12) << 0x10) != 0) {
            M2C_FIELD(arg0, u16 *, 0x20) = (u16) ((s32) (M2C_FIELD(arg0, u16 *, 0x20) << 0x10) >> 0x12);
            return func_8009C544();
        }
        var_v0_3 = temp_s3 & 2;
        if (var_v0_3) {
            var_s2 += 1;
        }
        var_v0_3 = temp_s3 & 1;
        if (var_v0_3) {
            var_s2 -= 2;
        }
        goto block_59;
    }
block_59:
    temp_v0_5 = (u16) M2C_FIELD(arg0, s16 *, 0x88) - M2C_FIELD(temp_s1, u16 *, 0x88);
    if (temp_v0_5 >= 0x20) {
        var_s2 -= 1;
        ASM_TAILSLOT_PIN_TIED(var_s2);
        return func_8009C57C();
    }
    var_v0_4 = temp_v0_5 < -0x1F;
    if (var_v0_4 == 0) {
        var_v0_4 = var_s2 << 0x10;
    } else {
        var_s2 += 1;
        var_v0_4 = var_s2 << 0x10;
    }
    {
        register s32 first_lhs ASM_REG("$3");
        register s32 first_product ASM_REG("$12");
        register u16 first_current ASM_REG("$2");
        register void *first_call_arg ASM_REG("$4");
        first_lhs = (s16)M2C_FIELD(arg0, u16 *, 0x20);
        ASM_KEEP(first_lhs);
        first_product = first_lhs * (var_v0_4 >> 0x10);
        first_call_arg = arg0;
        first_current = M2C_FIELD(arg0, volatile u16 *, 0x20);
        ASM_KEEP4(first_call_arg, first_current, first_product, first_lhs);
        first_lhs = first_product >> 3;
        ASM_KEEP(first_lhs);
        M2C_FIELD(arg0, u16 *, 0x20) = (u16)(first_current + first_lhs);
        temp_v0_6 = func_800C82B8(first_call_arg);
    }
    if (temp_v0_6 != 0) {
        register u16 second_current ASM_REG("$3");
        register s32 second_scaled ASM_REG("$2");
        register s32 second_product ASM_REG("$12");
        second_current = M2C_FIELD(arg0, u16 *, 0x20);
        ASM_KEEP(second_current);
        second_scaled = (s32)(second_current << 0x10) >> 0x13;
        ASM_KEEP(second_scaled);
        second_product = second_scaled * temp_v0_6;
        ASM_KEEP(second_product);
        M2C_FIELD(arg0, u16 *, 0x20) = (u16)(second_current + second_product);
    }
    if (M2C_FIELD(arg0, s32 *, 0x1C) & 0x01000000) {
        temp_v1 = (s32) ((s16) M2C_FIELD(temp_s1, u16 *, 0x22) - (s16) M2C_FIELD(arg0, u16 *, 0x20)) / 2;
        temp_v1_7 = (s32) ((s16) temp_v1 + ((u32) (temp_v1 << 0x10) >> 0x1F)) >> 1;
        M2C_FIELD(temp_s1, s16 *, 0x64) = (s16) (temp_v1 + temp_v1_7);
        return func_8009C644(temp_v1_7);
    }
    M2C_FIELD(temp_s1, volatile s16 *, 0x64) = (s16) ((s32) ((s16) M2C_FIELD(temp_s1, u16 *, 0x22) - (s16) M2C_FIELD(arg0, u16 *, 0x20)) / 2);
    if (M2C_FIELD(temp_s1, s16 *, 0x64) >= 0) {
        M2C_FIELD(temp_s1, s16 *, 0x64) = -1;
    }
    var_s2 = func_80042900(temp_s1, 0x1D);
    ASM_KEEP_NV(var_s2);
    var_v0_5 = var_s6 << 0x10;
    if (var_v0_5 == 0) {
        var_s0 = func_80099734(temp_s1, var_s0);
        if (M2C_FIELD(arg0, s32 *, 0x14) & 0x2000) {
            register void *c6a4_arg ASM_REG("$4") = &D_800E0DD0;
            ASM_TAILSLOT_PIN_TIED(c6a4_arg);
            return func_8009C6A4(c6a4_arg);
        }
        var_s0 = func_80099194(&D_800E0DDD, var_s0);
        if ((var_s2 << 0x10) != 0) {
            return func_8009C6D0(0, var_s0);
        }
        {
            register s32 ad08_a0 ASM_REG("$4") = 0 - M2C_FIELD(temp_s1, s16 *, 0x64);
            register s32 ad08_a1 ASM_REG("$5") = var_s0;
            ASM_USE2(ad08_a0, ad08_a1);
            var_s0 = func_8003AD08(ad08_a0, ad08_a1);
        }
        ASM_KEEP(var_s0);
        var_s0 = func_80099194(&D_800E0DEA, var_s0);
        ASM_KEEP(var_s6);
        var_v0_5 = var_s6 << 0x10;
        goto block_79;
    }
block_79:
    if (var_v0_5 >= 0) {
        func_80099290(var_s0);
        func_800A5720(temp_v0_3);
    }
    {
        register u16 late_arg3 ASM_REG("$12");
        register s32 late_signed ASM_REG("$2");
        register s32 late_one ASM_REG("$3");
        late_arg3 = *(volatile u16 *)&homes.arg3;
        ASM_KEEP(late_arg3);
        late_one = 1;
        ASM_KEEP(late_one);
        late_signed = (s16)late_arg3;
        ASM_KEEP(late_signed);
        if (late_signed == late_one) {
            func_800C7DEC(arg0, temp_s1);
        }
    }
    bf_arg = 0xDFFFFFFF;
    temp_ptr = (void *)0x800E0000;
    ASM_KEEP_DEP_NV(temp_ptr, bf_arg);
    temp_s0_2 = M2C_FIELD(temp_s1, s32 *, 0x1C) & bf_arg;
    temp_ptr = M2C_FIELD(temp_ptr, void **, 0x3D7C);
    M2C_FIELD(temp_s1, s32 *, 0x1C) = temp_s0_2;
    if (temp_s1 == temp_ptr) {
        func_8009BFF8(temp_s1, arg0);
    }
    var_v0_5 = var_s2 << 0x10;
    var_a2 = 0;
    if (var_v0_5 == 0) {
        var_v0_5 = 0 - (u16) M2C_FIELD(temp_s1, s16 *, 0x64);
        var_v0_5 <<= 0x10;
        ASM_KEEP(var_v0_5);
        var_a2 = var_v0_5 >> 0x10;
    }
    func_800B4C7C(3, temp_s1, var_a2, 0);
    var_s0 = 0x800E0000;
    ASM_KEEP(var_s0);
    var_v1 = (void **)0x80080000;
    if (temp_s1 == M2C_FIELD((void *)var_s0, void **, 0x3D7C)) {
        func_80094E34();
        var_v1 = (void **)0x80080000;
    }
    M2C_FIELD(temp_s1, void **, 0x60) = arg0;
    M2C_FIELD(arg0, void **, 0x60) = temp_s1;
    M2C_FIELD(var_v1, void **, 0x3470) = temp_s1 - 0x20;
    if (M2C_FIELD(arg0, s32 *, 0x1C) & 0x01000000) {
        register s32 bf_four ASM_REG("$5");
        func_800A56E0(0x700);
        bf_arg = M2C_FIELD(arg0, u16 *, 0x14);
        bf_four = 4;
        bf_arg &= 0x2000;
        bf_arg <<= 0x10;
        ASM_KEEP(bf_arg);
        bf_arg >>= 0x10;
        func_8009BF7C(bf_arg, bf_four);
    }
    func_800A56E0(0x601);
    if (!(M2C_FIELD(arg1, u16 *, 0x14) & 0x8000)) {
        func_800419EC(8, 0x10);
    }
    var_a3 = temp_s7 << 0x10;
    if (arg0 == M2C_FIELD((void *)var_s0, void **, 0x3D7C)) {
        if (M2C_FIELD(arg0, u8 *, 0xA8) != 0) {
            return temp_s1;
        }
    }
    var_a3 = temp_s7 << 0x10;
    ASM_KEEP(var_a3);
    var_a3 >>= 0x10;
    ASM_KEEP(var_a3);
    table_base = (s16 *)0x80070000;
    ASM_KEEP(table_base);
    table_raw = homes.arg2;
    ASM_KEEP(table_raw);
    table_base = (s16 *)((s32)table_base - 0x3328);
    ASM_KEEP(table_base);
    temp_v1_5 = (table_raw >> 9) & 7;
    temp_a2 = temp_v1_5 * 2;
    table_v0 = (s16 *)(temp_a2 + (s32)table_base);
    ASM_KEEP(table_v0);
    temp_v1_5 = (temp_v1_5 + 4) & 7;
    temp_v1_5 *= 2;
    table_base = (s16 *)(temp_v1_5 + (s32)table_base);
    ASM_KEEP(table_base);
    table_raw = homes.arg3;
    ASM_KEEP(table_raw);
    table_a0 = *table_v0;
    table_v0 = (s16 *)0x80070000;
    ASM_KEEP(table_v0);
    table_step = (s16)table_raw;
    ASM_KEEP(table_step);
    table_x = table_a0 * table_step;
    table_v0 = (s16 *)((s32)table_v0 - 0x3318);
    temp_a2 += (s32)table_v0;
    temp_v1_5 += (s32)table_v0;
    table_a1 = *table_base;
    table_y = M2C_FIELD(arg1, u8 *, 0x25);
    table_b0 = *(s16 *)temp_a2;
    table_v0 = (s16 *)M2C_FIELD(arg0, void **, 0x60);
    temp_v1_5 = *(s16 *)temp_v1_5;
    table_a1 <<= 5;
    table_a1 += 0x20;
    temp_v1_5 <<= 5;
    temp_v1_5 += 0x20;
    table_a0 = M2C_FIELD(arg1, u8 *, 0x24);
    temp_a2 = M2C_FIELD(table_v0, u16 *, 0x88) - 0x30;
    temp_a2 = (s16)temp_a2;
    table_v0 = (s16 *)(s32)M2C_FIELD(arg0, s16 *, 0x2A);
    table_a0 += table_x;
    table_a0 <<= 6;
    table_a0 += table_a1;
    table_a0 = (s16)table_a0;
    table_step = table_b0 * table_step;
    table_y += table_step;
    table_y <<= 6;
    table_y += temp_v1_5;
    table_y = (s16)table_y;
    func_80099C58(table_a0, table_y, temp_a2, var_a3, (s32)table_v0);
    ASM_SET(table_b0);
    return temp_s1;
}
