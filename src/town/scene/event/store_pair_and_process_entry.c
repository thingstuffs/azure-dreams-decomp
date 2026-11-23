#include "script_symbols.h"
#include "town/player/script_flags.h"
#include "town/scene/entry_requests.h"
#include "town/scene/hooks.h"
#include "town/scene/state_data.h"
#include "town/scene.h"

s32 store_pair_and_process_entry(TownObjectSet *row, s32 entry_index) {
    if (get_script_flag_mask(F_sbs07_pad21) != 0) {
        if (get_script_flag_mask(scene_request_flag_id) == 0) {
            clear_script_flag_bit(F_sbs07_pad21);
        }
    }
    set_global_entry_pair(row, entry_index);
    return process_checked_entry(row, entry_index);
}
