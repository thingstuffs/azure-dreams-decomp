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
    register s32 hard_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#endif
    s32 index = 0;
#ifdef NON_MATCHING
    s32 offset = 0;
#else
    register s32 offset ASM_REG("$16") = hard_zero;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
#endif
    s32 result;

    ASM_KEEP(index);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    result = func_80702714(*(u16 *)&D_80701DFC[offset]);
    if (result != 0) {
        offset += 4;
        ASM_KEEP(offset);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        index += 1;
        func_80702278();
    }
    func_807021C8(index);
}
