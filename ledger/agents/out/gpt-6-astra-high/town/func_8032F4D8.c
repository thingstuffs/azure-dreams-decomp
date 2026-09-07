#include "common.h"

s32 func_8001ADE0();

/* Returns whether every entry in a zero-terminated list passes func_8001ADE0. */
s32 func_80019CD8(s16 *values) {
    s16 *valueCursor;
    s32 firstValue;
    u16 currentValue;

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    valueCursor = values;
    firstValue = *(u16 *)valueCursor;

    currentValue = firstValue;
    if (firstValue != 0) {
check_value:
        if (func_8001ADE0((s16)currentValue) != 0) {
            valueCursor++;
            currentValue = *(u16 *)valueCursor;
            ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            if (*valueCursor != 0) {
                goto check_value;
            }
        }
    }
    return *valueCursor == 0;
}
