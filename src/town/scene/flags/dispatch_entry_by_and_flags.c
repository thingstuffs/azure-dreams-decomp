#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene/flags.h"

/*
 * Applies the signed indexed value and returns one when either F_sbs22_pad28 or F_sbs22_pad29 is
 * set; otherwise returns func_80019928.
 */
s32 dispatch_entry_by_798_and_799_flags(void *context, s32 entry_index) {
    if ((func_8001A510(F_sbs22_pad28) != 0) || (func_8001A510(F_sbs22_pad29) != 0)) {
        apply_signed_value_to_indexed_entry(context, entry_index);
        return 1;
    }
    return func_80019928(context, entry_index);
}
