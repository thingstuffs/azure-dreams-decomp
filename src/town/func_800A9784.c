#include "common.h"

extern void create_paired_offset_effects(void *first_ptr, void *second_ptr);

// Increase the step by four and accumulate up to 0x400, then trigger the completion handler.
void accumulate_effect_step(void *updateState, s32 unused1, s32 unused2, void *accumulatorState) {
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
        create_paired_offset_effects(updateState, updateState);
    }
}
