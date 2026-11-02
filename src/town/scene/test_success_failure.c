#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Test 0xFC0 and process 0xFB5 on success or 0xFB7 and 0xFB8 on failure. */
s32 test_success_failure(void) {
    if (get_script_flag_mask(Fr_cheriru_scene03) != 0) {
        set_script_flag_bit(Fr_hospital_scene00);
        return 1;
    }

    clear_script_flag_bit(F_hos_first_cheriru);
    clear_script_flag_bit(F_hos_first_hush);
    return 0;
}
