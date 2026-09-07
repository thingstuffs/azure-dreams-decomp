#include "common.h"

/* Tries three slot checks (args 3,4,5) via func_80033B2C; on first success calls
 * func_80033AE8 with that arg and returns 1/2/3; if none succeed returns 0. */
extern int func_80033B2C(int);
extern int func_80033AE8(int);

int func_8004E0AC(void) {
    int ret = 0;
    if (func_80033B2C(3)) {
        func_80033AE8(3);
        ret = 1;
        goto out;
    }
    if (func_80033B2C(4)) {
        func_80033AE8(4);
        ret = 2;
        goto out;
    }
    if (func_80033B2C(5)) {
        func_80033AE8(5);
        ret = 3;
    }
out:
    return ret;
}
