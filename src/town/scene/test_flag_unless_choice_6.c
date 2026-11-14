#include "common.h"
#include "town/scene/choice_data.h"
#include "town/scene.h"
#include "town/player/state.h"

extern s16 D_800164BC;

/* Returns whether func_800198D0 accepts D_800164BC, skipping the test when scene_choice_index is 6. */
s32 test_flag_unless_choice_6(void) {
    s32 check_passed;

    check_passed = 0;
    if (scene_choice_index != 6) {
        check_passed = get_script_flag_mask(D_800164BC) != 0;
    }
    return check_passed;
}
