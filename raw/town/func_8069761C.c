#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

#ifdef NON_MATCHING
#define LOCAL_ASM_REG(reg)
#define LOCAL_ASM_KEEP(var) ((void)0)
#else
#define LOCAL_ASM_REG(reg) asm(reg)
#define LOCAL_ASM_KEEP(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

M2C_UNK func_800165C4();
extern void *D_80016000;
extern M2C_UNK D_80018AE8;
extern s32 D_80018BE8;

void func_8069761C(void) {
    register s32 zero LOCAL_ASM_REG("$4");

    func_800165C4(&D_80018AE8);

    zero = 0;
    LOCAL_ASM_KEEP(zero);
    D_80018BE8 = M2C_FIELD(M2C_FIELD(D_80016000, void **, 0x20), s32 (**)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *), 0x68)(zero, zero, 2, &D_80018AE8);
}
