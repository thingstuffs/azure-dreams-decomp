#include "common.h"

extern u16 D_80083460[];
extern s8 D_800DCF4F;

/* Clear D_800DCF4F and decrement the sixth counter in D_80083460. */
void func_800A2AE4(void) {
    u16 *counters = (u16 *) &D_80083460;

    D_800DCF4F = 0;
    counters[5]--;
}
