#include "common.h"

s32 func_800198D0();                             /* extern */
extern s16 D_80016480;
extern s32 D_80019BB4;

/* Test D_80016480 with func_800198D0 unless D_80019BB4 is 1. */
s32 func_80477130(void) {
    s32 check_passed;

    check_passed = 0;
    if (D_80019BB4 != 1) {
        check_passed = func_800198D0(D_80016480) != 0;
    }
    return check_passed;
}
