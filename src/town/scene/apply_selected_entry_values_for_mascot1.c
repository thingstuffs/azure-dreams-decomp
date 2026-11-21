#include "script_symbols.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"
#include "town/scene/record_actions.h"

s32 apply_selected_entry_values_for_mascot1(Rec_func_800165F4_arg0 *entry, s32 entry_index) {
    if (get_script_flag_mask(F_set_mascot1) != 0) {
        set_current_entry_script_flag();
    }
    return apply_selected_entry_values(entry, entry_index);
}
