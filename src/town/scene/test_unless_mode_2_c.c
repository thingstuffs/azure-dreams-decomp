#include "common.h"

extern s32 func_800198D0();
extern s16 D_800164BC;
extern s32 scene_choice_index;

/* Returns whether func_800198D0 accepts D_800164BC, skipping the test when scene_choice_index is 6. */
s32 test_unless_6(void) {
    s32 check_passed;

    check_passed = 0;
    if (scene_choice_index != 6) {
        check_passed = func_800198D0(D_800164BC) != 0;
    }
    return check_passed;
}
