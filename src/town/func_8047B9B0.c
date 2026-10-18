#include "common.h"

extern s32 func_800198D0();
extern s16 D_80016498;
extern s32 D_80019BB4;

/* Test D_80016498 with func_800198D0 unless D_80019BB4 is 3. */
s32 test_unless_3(void) {
    s32 check_passed;

    check_passed = 0;
    if (D_80019BB4 != 3) {
        check_passed = func_800198D0(D_80016498) != 0;
    }
    return check_passed;
}
