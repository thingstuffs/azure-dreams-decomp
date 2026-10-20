#include "common.h"

extern s32 func_800198D0();
extern s16 D_8001648C;
extern s32 D_80019BB4;

/* Test D_8001648C with func_800198D0 unless D_80019BB4 is 2. */
s32 test_unless_2(void) {
    s32 check_passed;

    check_passed = 0;
    if (D_80019BB4 != 2) {
        check_passed = func_800198D0(D_8001648C) != 0;
    }
    return check_passed;
}
