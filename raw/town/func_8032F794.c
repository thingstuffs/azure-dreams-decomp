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
typedef s32 (*M2C_CALLBACK)(void *, s32);

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80019EA8();
s32 func_80019FC8() __attribute__((noreturn));
s32 func_8001ADE0();
extern M2C_UNK D_8001C378[];

s32 func_80019F94(void *arg0) {
    register void *held_arg0 ASM_REG("$18");
    M2C_UNK *global;
    register s32 temp_s0 ASM_REG("$16");
    register s32 temp_s1 ASM_REG("$17");
    register s32 base_value ASM_REG("$2");

    ASM_SCHED_BARRIER();
    held_arg0 = arg0;
    func_80019EA8(M2C_FIELD(held_arg0, s32 *, 0x14), M2C_FIELD(held_arg0, s16 *, 0x1A));
    global = (M2C_UNK *)0x80020000;
loop_1:
    global[-3874] = 0;
    ASM_SCHED_BARRIER();
    temp_s1 = 0;
    ASM_KEEP(temp_s1);
    temp_s0 = temp_s1 * 0x10;
    if ((func_8001ADE0(M2C_FIELD((temp_s0 + M2C_FIELD(held_arg0, s32 *, 0x10)), s16 *, 0xC)) != 0) || (M2C_FIELD((M2C_UNK8 *)(temp_s0 + (base_value = M2C_FIELD(held_arg0, s32 *, 0x10))), M2C_CALLBACK *, 0)(held_arg0, temp_s1) != 0)) {
        temp_s1++;
        ASM_TAILSLOT_PIN_TIED(temp_s1);
        return func_80019FC8();
    }
    if (global[-3874] == 0) {
        return temp_s1;
    }
    goto loop_1;
}
