#include "common.h"

extern u8 D_80080EA8[];
extern u8 D_800CF828[];
extern void *D_800CF838[];

/* Return the slot whose mapped pointer matches D_80080EA8, or -1. */
s32 func_8008B3AC(void) {
    s32 slot_index;

    for (slot_index = 0; slot_index < 15; slot_index++) {
        if (D_800CF838[D_800CF828[slot_index]] == D_80080EA8) {
            return slot_index;
        }
    }

    return -1;
}
