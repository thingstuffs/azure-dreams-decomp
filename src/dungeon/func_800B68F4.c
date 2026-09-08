#include "common.h"

#ifndef NON_MATCHING
#undef ASM_KEEP
#define ASM_KEEP(v) __asm__ __volatile__("" : "=r"(v) : "0"(v))
#endif

extern void func_800BBDEC(void *arg0, void *arg1, void *arg2, s16 arg3);
extern s32 func_800BC064();

s32 func_800BC054(void *arg0, void *arg1, void *arg2) {
    void *base;
    register void *node ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 field1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    base = arg0;
    ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_800BBDEC(base, arg1, arg2, *(s16 *)((s8 *)arg2 + 6));
    node = *(void **)((s8 *)base - 8);
    if (node == 0) {
        ASM_KEEP(node);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        return 0;
    }
    base = (void *)((s8 *)node + 32);
    ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    field1 = ((s32 *)node)[2];
    node = (void *)((s32 *)node)[3];
    ASM_KEEP(field1);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(node);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    return func_800BC064();
}
