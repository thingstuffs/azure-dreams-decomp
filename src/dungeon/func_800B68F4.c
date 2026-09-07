#include "common.h"

#ifndef NON_MATCHING
#undef ASM_KEEP
#define ASM_KEEP(v) __asm__ __volatile__("" : "=r"(v) : "0"(v))
#endif

extern void func_800BBDEC(void *arg0, void *arg1, void *arg2, s16 arg3);
extern s32 func_800BC064();

s32 func_800BC054(void *arg0, void *arg1, void *arg2) {
    void *base;
    register void *node ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    register s32 field1 ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */

    base = arg0;
    ASM_KEEP(base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_800BBDEC(base, arg1, arg2, *(s16 *)((s8 *)arg2 + 6));
    node = *(void **)((s8 *)base - 8);
    if (node == 0) {
        ASM_KEEP(node);   /* MATCH pin: retail register colouring depends on it */
        return 0;
    }
    base = (void *)((s8 *)node + 32);
    ASM_KEEP(base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    field1 = ((s32 *)node)[2];
    node = (void *)((s32 *)node)[3];
    ASM_KEEP(field1);   /* MATCH pin: retail basic-block layout depends on it */
    ASM_KEEP(node);   /* MATCH pin: retail register colouring depends on it */
    return func_800BC064();
}
