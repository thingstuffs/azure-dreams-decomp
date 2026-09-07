#include "common.h"

/* Checks slots 3-5 and initializes the first available slot, returning its result code. */
extern int func_80033B2C(int);
extern int func_80033AE8(int);

int func_8004E0AC(void) {
    int result = 0;
    if (func_80033B2C(3)) {
        func_80033AE8(3);
        result = 1;
        goto out;
    }
    if (func_80033B2C(4)) {
        func_80033AE8(4);
        result = 2;
        goto out;
    }
    if (func_80033B2C(5)) {
        func_80033AE8(5);
        result = 3;
    }
out:
    return result;
}
