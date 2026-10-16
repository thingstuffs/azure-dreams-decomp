#include "common.h"

extern u16 D_80017AA0[];

/* Decrements the first value in D_80017AA0. */
void decrementTownGlobalCounter(void) {
    D_80017AA0[0]--;
}
