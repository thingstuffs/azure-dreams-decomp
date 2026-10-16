#include "common.h"

extern s32 D_800DCF60;

/* Sets the value stored in D_800DCF60. */
void dungeonSetContinuationValue(s32 value) {
    D_800DCF60 = value;
}
