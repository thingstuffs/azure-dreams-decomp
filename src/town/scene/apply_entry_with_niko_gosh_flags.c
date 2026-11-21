#include "script_symbols.h"
#include "town/player/state.h"
#include "town/scene/record_actions.h"

s32 apply_entry_with_niko_gosh_flags(Rec_func_800165F4_arg0 *entry, s32 entry_index) {
    if (get_script_flag_mask(F_05_niko_and_gosh) != 0) {
        write_script_flag_range(F_sbs34_pad16, 2, 2);
        set_script_flag_bit(entry->unk_18);
    }
    return apply_selected_entry_values(entry, entry_index);
}
