#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"
#include "town/player/state.h"

/*
 * Reads and returns func_80019928 status, passing F_sbs22_pad36 to func_8001A418 for zero or
 * func_8001A490 otherwise.
 */
s32 dispatch_code_7_a_0_by_status(void *object, s32 entry_index) {
    s32 status;

    status = process_checked_entry(object, entry_index);
    if (status == 0) {
        set_script_flag_bit(F_sbs22_pad36);
    } else {
        clear_script_flag_bit(F_sbs22_pad36);
    }
    return status;
}
