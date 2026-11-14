#include "modules/town_ovl_5ff1d0.h"
#include "town/scene.h"
#include "town/player.h"

/*
 * Returns whether func_80017978 accepts the supplied inputs, skipping that call until
 * func_80018604 reaches 20.
 */
s32 process_entry_if_field_twenty_plus(s32 check_value, s32 check_data) {
    s32 check_passed;

    check_passed = 0;
    if (get_town_state_count() >= 0x14) {
        check_passed = process_checked_entry(check_value, check_data) != 0;
    }
    return check_passed;
}
