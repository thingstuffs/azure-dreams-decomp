#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene/flags.h"
#include "town/player/state.h"

/*
 * Applies the signed indexed value and returns one when either F_sbs22_pad28 or F_sbs22_pad29 is
 * set; otherwise returns func_80019928.
 */
s32 dispatch_entry_by_798_and_799_flags(void *context, s32 entry_index) {
    if ((get_script_flag_mask(F_sbs22_pad28) != 0) || (get_script_flag_mask(F_sbs22_pad29) != 0)) {
        pass_indexed_entry(context, entry_index);
        return 1;
    }
    return process_checked_entry(context, entry_index);
}
