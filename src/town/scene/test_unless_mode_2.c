#include "common.h"

extern s32 func_800198D0();
extern s16 D_8001648C;
extern s32 scene_choice_index;

/* Returns whether func_800198D0 accepts D_8001648C, skipping the test when scene_choice_index is 2. */
s32 test_unless_2(void) {
    s32 check_passed;

    check_passed = 0;
    if (scene_choice_index != 2) {
        check_passed = func_800198D0(D_8001648C) != 0;
    }
    return check_passed;
}
