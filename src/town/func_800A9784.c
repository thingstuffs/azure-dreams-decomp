#include "common.h"

extern void func_800A6F48(void *arg0, void *arg1);

// Increase the step by four and accumulate up to 0x400, then trigger the completion handler.
void func_800A6EE4(void *updateState, s32 unused1, s32 unused2, void *accumulatorState) {
    u16 step;
    u16 accumulatedValue;

    step = *(u16 *) ((u8 *) updateState + 0x90) + 4;
    *(u16 *) ((u8 *) updateState + 0x90) = step;
    accumulatedValue = *(u16 *) ((u8 *) accumulatorState + 0x16) + step;
    *(u16 *) ((u8 *) accumulatorState + 0x16) = accumulatedValue;
    if (accumulatedValue >= 0x400) {
        accumulatedValue = 0x400;
        *(u16 *) ((u8 *) accumulatorState + 0x16) = accumulatedValue;
    }
    if (*(u16 *) ((u8 *) accumulatorState + 0x16) == 0x400) {
        func_800A6F48(updateState, updateState);
    }
}
