#include "common.h"

extern s32 func_800198D0();
extern s16 D_800164BC;
extern s32 D_80019BB4;

/* Test D_800164BC with func_800198D0 unless D_80019BB4 is 6. */
s32 func_800181F0(void) {
    s32 check_passed;

    check_passed = 0;
    if (D_80019BB4 != 6) {
        check_passed = func_800198D0(D_800164BC) != 0;
    }
    return check_passed;
}
