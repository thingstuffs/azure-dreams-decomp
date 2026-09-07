#include "common.h"

typedef void (*Func)(void *, s32);
typedef void (*FinalFunc)(void *);

extern Func D_800E2934[];
extern void func_800DC724(void *);

void func_800DC8F8(u8 *arg0) {
    s32 i;
    Func *base;
    Func *func;
    Func callback;
    FinalFunc final_callback;

    i = 1;
    base = D_800E2934;
    func = base + 1;
    ASM_KEEP(base);
    do {
        register u8 *call_arg ASM_REG("$4") = arg0;

        ASM_KEEP(call_arg);
        callback = *func++;
        callback(call_arg, *(s32 *)(arg0 + 0x3C) + i * 0x10);
        i++;
    } while (i < 8);
    func_800DC724(arg0);
    final_callback = *(FinalFunc *)(arg0 + 0x4C);
    if (final_callback != 0) {
        final_callback(arg0);
    }
}

/* MECHANISM: A separately held D_800E2934 base forces retail's three-word base-plus-4 setup.
   arg0, the loop index, and callback cursor naturally occupy s2, s0, and s1.
   Keeping the a0 callback argument at the loop header fixes both argument-move delay slots. */
