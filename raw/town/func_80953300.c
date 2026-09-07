#include "common.h"

extern s32 rand(void);
extern s16 D_80024308[];
extern s16 D_80113158;
extern s32 D_8011315C;

s32 func_80953300(void) {
    s32 counter;
    s32 value;
    s32 second;

    counter = 3;
    do {
        value = rand();
        D_80024308[counter] = (value % 5) + 3;
        counter--;
    } while (counter >= 0);

    counter = rand() & 3;
    do {
        second = rand() & 3;
    } while (counter == second);

    D_80024308[counter] = 1;
    D_80024308[second] = 2;
    D_80113158 = 0;
    D_8011315C = 0;
    return 0;
}

/* MECHANISM: 0x20-byte frame with counter/value/second source locals.
   Hold the D_80024308 base through the first loop and use a short loop-carried
   pointer implied by the descending indexed stores; keep the final stores direct. */
