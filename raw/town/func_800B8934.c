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

s32 func_800439BC();
M2C_UNK func_800498EC();
s32 func_80049918();
s32 func_80049944();
M2C_UNK func_800B5264();
M2C_UNK func_800B53BC();
s32 func_800B6030();
extern u8 D_8006DE24[];

void func_800B6094(void *arg0, s32 arg1, s32 arg2) {
    register void *held_arg0 ASM_REG("$19") = arg0;
    register s32 held_arg1 ASM_REG("$21") = arg1;
    register s32 held_arg2 ASM_REG("$20") = arg2;
    register s32 first_zero ASM_REG("$6") = 0;
    M2C_UNK sp18[3];
    s32 *temp_s1_2;
    s32 temp_s0_2;
    register s32 temp_s2 ASM_REG("$18");
    register s32 branch_result ASM_REG("$2");
    void *temp_s0;
    register void *temp_s1 ASM_REG("$17");
    void *temp_v1;

    temp_s2 = (held_arg2 * 0x10) + 0xD8;
    temp_s1 = (void *) (held_arg2 * 4);
    ASM_KEEP(held_arg2);
    temp_s0 = (M2C_FIELD(held_arg0, u8 *, 0) * 0x14) + D_8006DE24;
    temp_s1 = (void *) ((s8 *)temp_s1 + (s32)held_arg1);
    func_800B5264(M2C_FIELD(temp_s1, s32 *, 0x20), M2C_FIELD(temp_s0, s32 *, 0), first_zero, 0x58, temp_s2);
    func_800B53BC(M2C_FIELD(temp_s1, s32 *, 0x2C), func_800B6030(M2C_FIELD(held_arg0, u8 *, 1), sp18), 0, 0xA0, temp_s2);
    ASM_KEEP(held_arg0);
    temp_s0_2 = func_80049944(M2C_FIELD(temp_s0, u8 *, 0x10));
    temp_s1_2 = M2C_FIELD(temp_s1, s32 **, 0x38);
    if (func_800439BC(M2C_FIELD(held_arg0, u8 *, 0)) != 0) {
        branch_result = func_800498EC(temp_s0_2);
    } else {
        branch_result = func_80049918(temp_s0_2);
    }
    temp_v1 = (held_arg2 * 4) + held_arg1;
    ASM_KEEP(branch_result);
    ASM_KEEP(held_arg1);
    ASM_KEEP(held_arg2);
    *temp_s1_2 = branch_result;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v1, void **, 0x38), void **, 4), s16 *, 8) = -0x30;
    temp_v1 = M2C_FIELD(temp_v1, void **, 0x38);
    branch_result = (held_arg2 * 0x10) + 0x67;
    temp_v1 = M2C_FIELD(temp_v1, void **, 4);
    M2C_FIELD(temp_v1, s16 *, 0xA) = (s16) branch_result;
}
