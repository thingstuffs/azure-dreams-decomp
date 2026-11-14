#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/player/state.h"

/*
 * When F_sbs22_pad29 is set, clears D_8001B208 and returns func_80019928; otherwise applies the
 * signed indexed value and returns one.
 */
s32 dispatch_entry_by_799_flag(void *context, s32 entryIndex) {
    s32 result;

    if (get_script_flag_mask(F_sbs22_pad29) != 0) {
        D_8001B208 = 0;
        result = process_checked_entry(context, entryIndex);
    } else {
        set_flag_from_indexed_entry(context, entryIndex);
        result = 1;
    }
    return result;
}
