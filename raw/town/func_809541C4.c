#include "common.h"

typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80021298(void) __attribute__((noreturn));
extern void func_80047738(void *, u8, s8);
extern void func_80047784(void *, u8, s32);
extern u8 D_8006CCF8[];
extern s16 D_80083228[];

void func_800211C4(void *arg0, void *arg1, void *arg2) {
    u8 *var_v0;
    s32 base_v0;
    register s32 temp_s0 ASM_REG("$16");
    u8 *temp_v0;
    register s32 temp_v2 ASM_REG("$2");
    register u16 temp_v1 ASM_REG("$3");
    void *arg1_hold = arg1;

    temp_v1 = (M2C_FIELD(arg0, u16 *, 0x2A) + 0x2000) & 0xFFF;
    M2C_FIELD(arg0, u16 *, 0x2A) = temp_v1;
    temp_v2 = (s32)(D_80083228[0] + temp_v1 + 0x100) >> 9;
    temp_s0 = temp_v2 & 7;
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        func_80047784(arg2, *((u8 *)M2C_FIELD(arg2, s32 *, 0x2C) + temp_s0), 0);
    }
    if (M2C_FIELD(arg1_hold, s16 *, 0x20) == temp_s0) {
        var_v0 = (u8 *)0x80070000;
        goto page_check;
    }
    temp_v0 = (u8 *)M2C_FIELD(arg2, s32 *, 0x2C);
    if (temp_v0 != 0) {
        func_80047738(arg2, temp_v0[temp_s0], M2C_FIELD(arg2, s8 *, 4));
    }
    M2C_FIELD(arg1_hold, s16 *, 0x20) = temp_s0;
    var_v0 = (u8 *)0x80070000;
page_check:
    base_v0 = (s32)var_v0 - 0x3308;
    ASM_KEEP(base_v0);
    temp_v0 = (u8 *)(temp_s0 + base_v0);
    if (temp_v0[0] != 0) {
        register u32 temp_return ASM_REG("$2");
        temp_return = M2C_FIELD(arg2, u16 *, 0x14) | 1;
        ASM_TAILSLOT_PIN_TIED(temp_return);
        func_80021298();
    }
    M2C_FIELD(arg2, u16 *, 0x14) = (u16)(M2C_FIELD(arg2, u16 *, 0x14) & 0xFFFE);
}
