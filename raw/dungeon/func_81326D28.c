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

extern void *D_8016A868[];
s32 func_800A45D8();
s32 func_800A7234();
M2C_UNK func_800A7A7C();
s16 func_800BCB04();
void func_8016E63C(void) __attribute__((noreturn));
void func_8016E824(void) __attribute__((noreturn));
void func_8016E9E0(void) __attribute__((noreturn));
void func_8016EAF4(void) __attribute__((noreturn));
extern s32 D_800814A0;
extern u8 D_80174708;

void func_8016E528(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    u8 sp18[4];
    s32 temp_s0;
    s16 temp_s0_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_v0;
    s32 var_v1;
    s32 temp_a0;
    s32 temp_y;
    u16 temp_v0;
    s16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_a2;
    u32 temp_v1;
    void *temp_a1;
    u8 *table_base;

    if (M2C_FIELD(arg0, s16 *, 0x12) != 3) {
        goto block_4;
    }
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x1A);
    M2C_FIELD(arg0, u16 *, 0x1A) = (u16) (temp_v0 + 1);
    if ((s16) temp_v0 < 0x38) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x12) = 0;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFF7F);
    M2C_FIELD(arg0, u16 *, 0x1A) = 0U;
    M2C_FIELD(arg0, s32 *, 0x60) = 0x14900;
block_3:
block_4:
    if (M2C_FIELD(arg0, s16 *, 0x12) != 1) {
        goto block_28;
    }
    if (M2C_FIELD(arg0, s16 *, 0x14) != 0) {
        goto block_21;
    }
    M2C_FIELD(arg0, s16 *, 0x14) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x14) + 1);
    temp_a0 = M2C_FIELD(arg0, s8 *, 0x49);
    var_v1 = M2C_FIELD(arg1, s16 *, 0xE) - M2C_FIELD(arg0, s8 *, 0x48);
    temp_y = M2C_FIELD(arg1, s16 *, 0x12);
    if (var_v1 >= 0) {
        goto block_8;
    }
    var_v1 = 0 - var_v1;
block_8:
    var_v0 = temp_y - temp_a0;
    if (var_v0 >= 0) {
        goto block_10;
    }
    var_v0 = 0 - var_v0;
block_10:
    temp_v1 = var_v1 + var_v0;
    if (temp_v1 >= 5U) {
        goto block_20;
    }
    (void)jt_keep; goto *D_8016A868[(u32)(temp_v1)];
jt_c0:
    var_v0 = 4;
    goto jt_set_countdown;
jt_c1:
    var_v0 = 8;
    goto jt_set_countdown;
jt_c2:
    var_v0 = 0xC;
    goto jt_set_countdown;
jt_c3:
    var_v0 = 0xE;
    goto jt_set_countdown;
jt_c4:
block_20:
    var_v0 = 0x10;
jt_set_countdown:
    M2C_FIELD(arg0, u16 *, 0x1A) = var_v0;
block_21:
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x1A) - 1;
    M2C_FIELD(arg0, u16 *, 0x1A) = temp_v0_2;
    if ((s16) temp_v0_2 == 0) {
        goto block_23;
    }
    {
        s32 interp_target;
        s32 interp_current;
        interp_target = M2C_FIELD(arg1, s16 *, 0xE) << 6;
        interp_current = M2C_FIELD(arg1, s16 *, 2) - 0x20;
        M2C_FIELD(arg1, s16 *, 2) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 2) + (interp_target - interp_current) / (s16) temp_v0_2);
    }
    {
        s32 interp_target;
        s32 interp_current;
        interp_target = M2C_FIELD(arg1, s16 *, 0x12) << 6;
        interp_current = M2C_FIELD(arg1, s16 *, 6) - 0x20;
        M2C_FIELD(arg1, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 6) + (interp_target - interp_current) / (s16) M2C_FIELD(arg0, u16 *, 0x1A));
    }
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) + ((s32) (M2C_FIELD(arg1, s16 *, 0x16) - M2C_FIELD(arg1, s16 *, 0xA)) / (s16) M2C_FIELD(arg0, u16 *, 0x1A)));
block_23:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x1A) > 0) {
        goto block_26;
    }
    sp18[0] = M2C_FIELD(arg0, u8 *, 0x44);
    sp18[1] = M2C_FIELD(arg0, u8 *, 0x45);
    sp18[2] = M2C_FIELD(arg0, u8 *, 0x46);
    sp18[3] = M2C_FIELD(arg0, u8 *, 0x47);
    func_800A7A7C(M2C_FIELD(arg1, s16 *, 0xE), M2C_FIELD(arg1, s16 *, 0x12), M2C_FIELD(arg1, s16 *, 0x16), M2C_FIELD(arg2, s32 *, 8), sp18);
    func_8016E824();
    return;
block_26:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        goto block_3;
    }
block_27:
block_28:
    if (M2C_FIELD(arg0, s16 *, 0x12) != 2) {
        goto loop_33;
    }
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x54));
    M2C_FIELD(arg0, s32 *, 0x54) = (s32) (M2C_FIELD(arg0, s32 *, 0x54) + M2C_FIELD(arg0, s32 *, 0x60));
    temp_v0_3 = M2C_FIELD(arg2, u16 *, 0x1E) - 0xC8;
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_3;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_3;
    temp_a2 = M2C_FIELD(arg1, volatile u16 *, 0xA);
    temp_s0 = M2C_FIELD(arg1, s16 *, 0xA);
    if ((func_800BCB04((M2C_FIELD(arg0, s8 *, 0x48) << 6) & 0xFFC0, (M2C_FIELD(arg0, s8 *, 0x49) << 6) & 0xFFC0, (s16) (temp_a2 - 0x20)) - 7) >= temp_s0) {
        goto block_32;
    }
    M2C_FIELD(arg1, s16 *, 0xA) = func_800BCB04((M2C_FIELD(arg0, s8 *, 0x48) << 6) & 0xFFC0, (M2C_FIELD(arg0, s8 *, 0x49) << 6) & 0xFFC0, (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 0x20));
    M2C_FIELD(arg1, s16 *, 8) = 0;
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    D_800814A0 |= 0x8000;
    func_8016EAF4();
    return;
block_32:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        goto block_27;
    }
loop_33:
    if (M2C_FIELD(arg0, s16 *, 0x12) != 0) {
        goto block_49;
    }
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x4C));
    M2C_FIELD(arg0, s32 *, 0x4C) = (s32) (M2C_FIELD(arg0, s32 *, 0x4C) + M2C_FIELD(arg0, s32 *, 0x58));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x50));
    table_base = &D_80174708;
    M2C_FIELD(arg0, s32 *, 0x50) = (s32) (M2C_FIELD(arg0, s32 *, 0x50) + M2C_FIELD(arg0, s32 *, 0x5C));
    temp_a1 = (M2C_FIELD(arg0, s16 *, 0x18) * 4) + table_base;
    var_v1 = M2C_FIELD(arg0, s8 *, 0x48) + M2C_FIELD(temp_a1, s16 *, 0);
    var_a0 = M2C_FIELD(arg1, s16 *, 2);
    if (var_a0 >= 0) {
        goto block_36;
    }
    var_a0 += 0x3F;
block_36:
    if (var_v1 != (var_a0 >> 6)) {
        goto block_45;
    }
    var_v1 = M2C_FIELD(arg0, s8 *, 0x49) + M2C_FIELD(temp_a1, s16 *, 2);
    var_a0_2 = M2C_FIELD(arg1, s16 *, 6);
    if (var_a0_2 >= 0) {
        goto block_39;
    }
    var_a0_2 += 0x3F;
block_39:
    if (var_v1 != (var_a0_2 >> 6)) {
        goto block_45;
    }
    if ((func_800A45D8((u16) M2C_FIELD(arg1, s16 *, 2), (u16) M2C_FIELD(arg1, s16 *, 6), M2C_FIELD(arg1, s16 *, 0xA)) << 0x10) != 0) {
        goto block_42;
    }
    if (func_800BCB04((u16) M2C_FIELD(arg1, s16 *, 2), (u16) M2C_FIELD(arg1, s16 *, 6), M2C_FIELD(arg1, s16 *, 0xA)) < 0x200) {
        goto block_44;
    }
block_42:
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) - M2C_FIELD(arg0, s32 *, 0x4C));
    M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    M2C_FIELD(arg0, s32 *, 0x58) = 0;
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) - M2C_FIELD(arg0, s32 *, 0x50));
    M2C_FIELD(arg0, s32 *, 0x50) = 0;
    M2C_FIELD(arg0, s32 *, 0x5C) = 0;
    func_8016E9E0();
    return;
block_44:
    M2C_FIELD(arg0, s8 *, 0x48) = (s8) ((u8) M2C_FIELD(arg0, s8 *, 0x48) + *((M2C_FIELD(arg0, s16 *, 0x18) * 4) + table_base));
    M2C_FIELD(arg0, s8 *, 0x49) = (s8) ((u8) M2C_FIELD(arg0, s8 *, 0x49) + M2C_FIELD(((M2C_FIELD(arg0, s16 *, 0x18) * 4) + table_base), u8 *, 2));
    M2C_FIELD(arg2, s16 *, 6) = 0;
block_45:
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x54));
    M2C_FIELD(arg0, s32 *, 0x54) = (s32) (M2C_FIELD(arg0, s32 *, 0x54) + M2C_FIELD(arg0, s32 *, 0x60));
    temp_s0_2 = M2C_FIELD(arg1, s16 *, 0xA);
    if ((func_800BCB04(((M2C_FIELD(arg0, s8 *, 0x48) << 6) + 0x20) & 0xFFE0, ((M2C_FIELD(arg0, s8 *, 0x49) << 6) + 0x20) & 0xFFE0, temp_s0_2) - 0x10) >= temp_s0_2) {
        goto block_48;
    }
    M2C_FIELD(arg1, s16 *, 0xA) = func_800BCB04(((M2C_FIELD(arg0, s8 *, 0x48) << 6) + 0x20) & 0xFFE0, ((M2C_FIELD(arg0, s8 *, 0x49) << 6) + 0x20) & 0xFFE0, M2C_FIELD(arg1, s16 *, 0xA));
    M2C_FIELD(arg1, s16 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0x5C) = 0;
    M2C_FIELD(arg0, s32 *, 0x50) = 0;
    M2C_FIELD(arg0, s32 *, 0x58) = 0;
    M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    M2C_FIELD(arg0, s16 *, 0x12) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x12) + 1);
    if ((func_800A7234(M2C_FIELD(arg0, s8 *, 0x48), M2C_FIELD(arg0, s8 *, 0x49), (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 0x20), arg1 + 0xE, arg1 + 0x12, arg1 + 0x16) << 0x10) != 0) {
        goto block_48;
    }
    M2C_FIELD(arg0, s16 *, 0x12) = 2;
    M2C_FIELD(arg0, s32 *, 0x54) = 0xFFF80000;
block_48:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        goto loop_33;
    }
block_49:
    return;
}
