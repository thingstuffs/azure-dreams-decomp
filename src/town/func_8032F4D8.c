#include "common.h"

s32 func_8001ADE0();

/* Returns whether every entry in a zero-terminated list passes func_8001ADE0. */
s32 func_80019CD8(s16 *values) {
    s16 *valueCursor;
    s32 firstValue;
    u16 currentValue;

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    valueCursor = values;
    firstValue = *(u16 *)valueCursor;

    currentValue = firstValue;
    if (firstValue != 0) {
check_value:
        if (func_8001ADE0((s16)currentValue) != 0) {
            valueCursor++;
            currentValue = *(u16 *)valueCursor;
            ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            if (*valueCursor != 0) {
                goto check_value;
            }
        }
    }
    return *valueCursor == 0;
}
