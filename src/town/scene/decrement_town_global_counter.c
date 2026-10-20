#include "common.h"

extern u16 D_80017AA0[];

/* Decrements the first value in D_80017AA0. */
void decrement_town_global_counter(void) {
    D_80017AA0[0]--;
}
