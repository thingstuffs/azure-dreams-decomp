#include "common.h"

typedef void (*TownCopyFn)(void *, void *, s32);
typedef void (*TownSetFn)(s32);

extern s32 func_8001AB20(s32, s32);
extern s8 D_80016000[];
extern s8 D_80016130[];
extern s8 D_80016158[];

s32 func_8001AB74(s32 arg0, s32 arg1, s32 arg2) {
    s32 entry;
    s32 context;
    s32 count;
    register s32 best_entry ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    s32 best_value;
    s32 index;
    s32 value;
    void *object;
    void *dispatch;
    TownCopyFn copy_fn;
    TownSetFn set_fn;

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    entry = arg0;
    context = arg1;
    count = arg2;
    ASM_USE2(context, count);   /* MATCH pin: retail immediate-load split depends on it */
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
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
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
