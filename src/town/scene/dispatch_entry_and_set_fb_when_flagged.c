#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"
#include "town/player/state.h"

/*
 * When either F_sbs22_pad28 or F_sbs22_pad29 is set, processes Fp_far_kenkatyu, applies the signed
 * entry value, and returns one; otherwise calls func_80019928.
 */
s32 dispatch_entry_and_set_11_fb_when_flagged(void *context, s32 entry_index) {
    if ((get_script_flag_mask(F_sbs22_pad28) != 0) || (get_script_flag_mask(F_sbs22_pad29) != 0)) {
        clear_script_flag_bit(Fp_far_kenkatyu);
        pass_indexed_entry(context, entry_index);
        return 1;
    }
    return process_checked_entry(context, entry_index);
}
