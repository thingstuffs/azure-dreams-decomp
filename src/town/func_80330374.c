#include "common.h"
#include "shared/record_ptrs.h"

typedef void (*TownCopyFn)(void *, void *, s32);
typedef void (*TownSetFn)(s32);

extern s32 func_8001AB20(s32, s32);
extern s8 D_80016130[];
extern s8 D_80016158[];

/* Returns the lowest-valued entry and reports a player.c assertion if none is selected. */
s32 func_8001AB74(s32 entries, s32 eval_context, s32 entry_count) {
    s32 best_entry;
    s32 best_value;
    s32 index;
    s32 value;
    void *object;
    void *dispatch;
    TownCopyFn report_assert;
    TownSetFn set_fn;

    best_value = 0x7FFFFFFF;
    best_entry = 0;
    for (index = 0; index < entry_count; index++) {
        value = func_8001AB20(entries, eval_context);
        if (value < best_value) {
            best_entry = entries;
            best_value = value;
        }
        entries += 8;
    }

    if (best_entry == 0) {
        object = *(void **)((s8 *)(&D_80016000));
        dispatch = *(void **)((s8 *)object + 0x20);
        report_assert = *(TownCopyFn *)((s8 *)dispatch + 0x168);
        report_assert(D_80016130, D_80016158, 0x40);

        object = *(void **)((s8 *)(&D_80016000));
        dispatch = *(void **)((s8 *)object + 0x20);
        set_fn = *(TownSetFn *)((s8 *)dispatch + 0x174);
        set_fn(1);
    }
    return best_entry;
}
