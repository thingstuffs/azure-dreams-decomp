#include "common.h"
#include "town/scene/choice_data.h"
#include "town/player/state.h"

extern s16 D_80016498;

/* Returns whether func_800198D0 accepts D_80016498, skipping the test when scene_choice_index is 3. */
s32 test_unless_3(void) {
    s32 check_passed;

    check_passed = 0;
    if (scene_choice_index != 3) {
        check_passed = get_script_flag_mask(D_80016498) != 0;
    }
    return check_passed;
}
