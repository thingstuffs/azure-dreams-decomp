#include "common.h"

extern s16 D_800E3CCE;

/* Decrement the counter if it is nonzero. */
void decrement_event_counter(void) {
    if (D_800E3CCE != 0) {
        D_800E3CCE = (u16) D_800E3CCE - 1;
    }
}
