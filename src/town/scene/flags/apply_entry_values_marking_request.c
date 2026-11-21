#include "script_symbols.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene/state_data.h"

s32 apply_entry_values_marking_request(Rec_func_800165F4_arg0 *row, s32 entry_index) {
    if (get_script_flag_mask(scene_request_flag_id) == 0) {
        set_script_flag_bit(F_sbs07_pad26);
    }
    return apply_selected_entry_values(row, entry_index);
}
