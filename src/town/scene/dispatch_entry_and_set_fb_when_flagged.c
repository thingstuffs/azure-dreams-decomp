#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"

s32 dispatch_entry_and_set_11_fb_when_flagged(s32 context, s32 entry_index) {
    if ((func_8001A510(F_sbs22_pad28) != 0) || (func_8001A510(F_sbs22_pad29) != 0)) {
        func_8001A490(Fp_far_kenkatyu);
        apply_signed_value_to_indexed_entry(context, entry_index);
        return 1;
    }
    func_80019928(context, entry_index);
}
