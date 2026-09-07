#include "common.h"

extern u8 D_80701DFC[];
extern void func_807021C8(s32 index);
extern void func_80702278(void);
#if 0
extern void func_80702278(void) __attribute__((noreturn));
#endif
extern s32 func_80702714(u16 value);

void func_80702260(void) {
#ifndef NON_MATCHING
    register s32 hard_zero ASM_REG("$0");
#endif
    register s32 index ASM_REG("$17") = 0;
#ifdef NON_MATCHING
    register s32 offset ASM_REG("$16") = 0;
#else
    register s32 offset ASM_REG("$16") = hard_zero;
#endif
    s32 result;

    ASM_KEEP(index);
    ASM_KEEP(offset);
    result = func_80702714(*(u16 *)&D_80701DFC[offset]);
    if (result != 0) {
        offset += 4;
        ASM_KEEP(offset);
        index += 1;
        func_80702278();
    }
    func_807021C8(index);
}
