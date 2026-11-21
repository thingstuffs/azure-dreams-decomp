#include "script_symbols.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"

s32 apply_conditional_record_value(Rec_func_800165F4_arg0 *entry, s32 entry_index) {
    if (get_script_flag_mask(F_sb34_00) != 0) {
        set_script_flag_bit(entry->unk_18);
    }
    return apply_selected_entry_values(entry, entry_index);
}
