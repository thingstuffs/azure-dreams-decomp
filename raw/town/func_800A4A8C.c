#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004491C();
extern void func_800A22AC(void);
extern M2C_UNK D_80046398;
extern M2C_UNK D_800A22D0;

s32 func_800A21EC(void *arg0, void *arg1, void *arg2) {
    M2C_FIELD(arg2, s32 *, 0) = 0;
    M2C_FIELD(arg2, s8 *, 4) = 0;
    M2C_FIELD(arg2, s8 *, 5) = 0;
    func_8004491C(arg0 - 0x20, &D_80046398);
    M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s32 *, 0);
    M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s32 *, 4);
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s32 *, 8);
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_800A22D0;
    if (M2C_FIELD(arg0, s16 *, 0x20) == 0) {
        register s32 dead ASM_REG("$2");
        dead = 1;
        M2C_FIELD(arg2, s32 *, 8) = dead;
        dead = (u16) M2C_FIELD(arg1, u16 *, 2);
        ASM_KEEP(dead);
        func_800A22AC();
        return dead + 0x90;
    }
    {
        register s32 flags ASM_REG("$2") = (u16) M2C_FIELD(arg2, u16 *, 0x14);
        register s32 one ASM_REG("$3") = 1;
        M2C_FIELD(arg2, s32 *, 8) = one;
        ASM_KEEP(one);
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (flags | 1);
        M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) - 0x90);
        M2C_FIELD(arg2, s16 *, 0x1A) = 0;
    }
}
