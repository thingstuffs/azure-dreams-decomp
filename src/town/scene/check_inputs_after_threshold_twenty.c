#include "modules/town_ovl_5ff1d0.h"
#include "town/scene.h"
#include "town/player.h"

/*
 * Returns whether func_80017978 accepts the supplied inputs, skipping that call until
 * func_80018604 reaches 20.
 */
s32 check_inputs_after_threshold_twenty(s32 check_value, s32 check_data) {
    s32 check_passed;

    check_passed = 0;
    if (get_linked_record_field_2_d_60() >= 0x14) {
        check_passed = process_checked_entry(check_value, check_data) != 0;
    }
    return check_passed;
}
