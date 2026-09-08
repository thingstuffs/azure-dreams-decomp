#include "common.h"

extern short D_800838D8[64];
extern short D_80083858[64];

/* Initializes the two 64-entry tables to 0x500 and 0x380. */
void func_8003CAC4(void) {
    int entry_index;

    for (entry_index = 0x3F; entry_index >= 0; entry_index--) {
        D_80083858[entry_index] = 0x500;
        D_800838D8[entry_index] = 0x380;
    }
}
