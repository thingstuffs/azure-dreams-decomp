#include "modules/town_ovl_3ef1c8.h"

s32 dispatch_entry_by_798_and_799_flags(s32 context, s32 entry_index) {
    if ((func_8001A510(0x798) != 0) || (func_8001A510(0x799) != 0)) {
        apply_signed_value_to_indexed_entry(context, entry_index);
        return 1;
    }
    return func_80019928(context, entry_index);
}
