#include "common.h"

extern int func_80033B2C(int);
extern int func_80033AE8(int);

/* Processes the first passing slot check among 3, 4, and 5, returning 1, 2, or 3, or 0 if none pass. */
int func_8004E0AC(void) {
    int slot_result = 0;
    if (func_80033B2C(3)) {
        func_80033AE8(3);
        slot_result = 1;
        goto out;
    }
    if (func_80033B2C(4)) {
        func_80033AE8(4);
        slot_result = 2;
        goto out;
    }
    if (func_80033B2C(5)) {
        func_80033AE8(5);
        slot_result = 3;
    }
out:
    return slot_result;
}
