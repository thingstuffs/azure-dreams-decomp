#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"

s32 dispatch_entry_by_799_flag(s32 context, s32 entryIndex) {
    s32 result;

    if (func_8001A510(F_sbs22_pad29) != 0) {
        D_8001B208 = 0;
        result = func_80019928(context, entryIndex);
    } else {
        apply_signed_value_to_indexed_entry(context, entryIndex);
        result = 1;
    }
    return result;
}
