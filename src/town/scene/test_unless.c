#include "common.h"
#include "town/scene.h"

s32 func_800198D0(s32 flagIndex);                             /* extern */
extern s16 D_80016480;
extern s32 scene_choice_index;

/* Returns whether func_800198D0 accepts D_80016480, skipping the test when scene_choice_index is 1. */
s32 test_unless_1(void) {
    s32 check_passed;

    check_passed = 0;
    if (scene_choice_index != 1) {
        check_passed = func_800198D0(D_80016480) != 0;
    }
    return check_passed;
}
