#include "common.h"

/* Initializes two 64-entry s16 tables to constant values, iterating backwards. */
extern short D_800838D8[64];
extern short D_80083858[64];

void func_8003CAC4(void) {
    int i;

    for (i = 0x3F; i >= 0; i--) {
        D_80083858[i] = 0x500;
        D_800838D8[i] = 0x380;
    }
}
