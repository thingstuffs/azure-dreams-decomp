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
    register s32 hard_zero ASM_REG("$0");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
#endif
    s32 index = 0;
#ifdef NON_MATCHING
    s32 offset = 0;
#else
    register s32 offset ASM_REG("$16") = hard_zero;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
#endif
    s32 result;

    ASM_KEEP(index);   /* MATCH pin: retail immediate-load split depends on it */
    result = func_80702714(*(u16 *)&D_80701DFC[offset]);
    if (result != 0) {
        offset += 4;
        ASM_KEEP(offset);   /* MATCH pin: retail delay-slot contents depend on it */
        index += 1;
        func_80702278();
    }
    func_807021C8(index);
}
