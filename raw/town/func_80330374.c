#include "common.h"

typedef void (*TownCopyFn)(void *, void *, s32);
typedef void (*TownSetFn)(s32);

extern s32 func_8001AB20(s32, s32);
extern s8 D_80016000[];
extern s8 D_80016130[];
extern s8 D_80016158[];

s32 func_8001AB74(s32 arg0, s32 arg1, s32 arg2) {
    register s32 entry ASM_REG("$16");
    register s32 context ASM_REG("$21");
    register s32 count ASM_REG("$20");
    register s32 best_entry ASM_REG("$19");
    register s32 best_value ASM_REG("$18");
    register s32 index ASM_REG("$17");
    s32 value;
    void *object;
    void *dispatch;
    TownCopyFn copy_fn;
    TownSetFn set_fn;

    ASM_SCHED_BARRIER();
    entry = arg0;
    context = arg1;
    count = arg2;
    ASM_USE2(context, count);
    best_value = 0x7FFFFFFF;
    index = 0;
    best_entry = index;
    if (count > 0) {
        do {
            value = func_8001AB20(entry, context);
            if (value < best_value) {
                best_entry = entry;
                best_value = value;
            }
            index++;
            entry += 8;
        } while (index < count);
    }

    if (best_entry == 0) {
        object = *(void **)D_80016000;
        dispatch = *(void **)((s8 *)object + 0x20);
        copy_fn = *(TownCopyFn *)((s8 *)dispatch + 0x168);
        ASM_SCHED_BARRIER();
        copy_fn(D_80016130, D_80016158, 0x40);

        object = *(void **)D_80016000;
        dispatch = *(void **)((s8 *)object + 0x20);
        set_fn = *(TownSetFn *)((s8 *)dispatch + 0x174);
        set_fn(1);
    }
    return best_entry;
}

/* MECHANISM: guarded saved-register roles plus an entry scheduling boundary
   keep the 0x30-frame save block contiguous; joint liveness orders s5/s4 setup.
   A post-dispatch boundary preserves the first call's two load-delay nops. */
