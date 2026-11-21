#include "script_symbols.h"
#include "town/player/script_flags.h"

#include "town/scene/record_actions.h"

s32 set_entry_flag_and_apply_values(Rec_func_800165F4_arg0 *row, s32 entry_index) {
    set_script_flag_bit(row->unk_18);
    clear_script_flag_bit(F_sbs07_pad21);
    return apply_selected_entry_values(row, entry_index);
}
