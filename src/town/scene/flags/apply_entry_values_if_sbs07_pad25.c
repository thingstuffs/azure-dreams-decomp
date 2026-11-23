#include "script_symbols.h"
#include "town/player/script_flags.h"
#include "town/scene/hooks.h"
#include "town/scene/record_actions.h"
#include "town/scene/state_data.h"
#include "town/scene.h"

s32 apply_entry_values_if_sbs07_pad25(TownObjectSet *row, s32 entry_index) {
    set_global_entry_pair(row, entry_index);
    if (get_script_flag_mask(F_sbs07_pad25) != 0) {
        return apply_selected_entry_values(row, entry_index);
    }
    if (get_script_flag_mask(scene_request_flag_id) == 0) {
        set_script_flag_bit(F_sbs07_pad26);
    }
    return 0;
}
