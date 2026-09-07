#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct Position {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
} Position;

extern void func_800C170C(s32 arg0);
extern s32 func_800C2124(void);
extern void func_800C2290(void);
extern Position D_80083780;

s32 func_800C21F8(void *arg0) {
    register s32 temp_a0 ASM_REG("$4");
    register s32 temp_v0 ASM_REG("$2");
    register s32 temp_v1 ASM_REG("$3");

    temp_v0 = M2C_FIELD(arg0, s16 *, 4);
    temp_v1 = D_80083780.x;
    temp_a0 = D_80083780.y;
    ASM_KEEP(temp_v0);
    ASM_KEEP(temp_v1);
    ASM_KEEP(temp_a0);
    temp_v0 -= temp_v1;
    if (temp_v0 < 0) {
        temp_v0 = 0 - temp_v0;
    }
    ASM_KEEP(temp_v0);
    temp_v1 = M2C_FIELD(arg0, s16 *, 6);
    temp_v0 = (s32)((u32)temp_v0 << 16);
    temp_v1 -= temp_a0;
    temp_a0 = temp_v1;
    if (temp_v1 < 0) {
        temp_a0 = 0 - temp_a0;
    }
    ASM_KEEP(temp_v1);
    ASM_KEEP(temp_a0);
    if ((M2C_FIELD(arg0, s16 *, 0xC) < (temp_v0 >> 16)) ||
        ((s16)temp_a0 > M2C_FIELD(arg0, s16 *, 0xE))) {
        func_800C170C(temp_a0);
        M2C_FIELD(arg0, void (**)(void), 0) = (void (*)(void))func_800C2124;
        ASM_SCHED_BARRIER();
        func_800C2290();
        return 1;
    }
    return 0;
}

/* MECHANISM: A 24-byte frame and s0-held object preserve the delta live ranges.
   Spelling the second test as temp_a0 > field makes EXPAND issue sll before lh,
   closing the reorder; cdk-G0 supplies the split global base and sibcall tail. */
