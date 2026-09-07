#include "common.h"

extern int func_80033B2C(int);
extern int func_80033AE8(int);

/* Handles the first passing slot check (3, 4, 5) and returns 1, 2, or 3, or 0 if none pass. */
int func_8004E0AC(void) {
    int slotResult = 0;
    if (func_80033B2C(3)) {
        func_80033AE8(3);
        slotResult = 1;
        goto out;
    }
    if (func_80033B2C(4)) {
        func_80033AE8(4);
        slotResult = 2;
        goto out;
    }
    if (func_80033B2C(5)) {
        func_80033AE8(5);
        slotResult = 3;
    }
out:
    return slotResult;
}
