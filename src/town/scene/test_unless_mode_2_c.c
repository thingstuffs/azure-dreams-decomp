#include "common.h"

extern s32 func_800198D0();
extern s16 D_800164BC;
extern s32 scene_choice_index;

/* Test D_800164BC with func_800198D0 unless D_80019BB4 is 6. */
s32 test_unless_6(void) {
    s32 check_passed;

    check_passed = 0;
    if (scene_choice_index != 6) {
        check_passed = func_800198D0(D_800164BC) != 0;
    }
    return check_passed;
}
