#include "town/player.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene.h"

s32 apply_record_value_when_enabled(Rec_func_800165F4_arg0 *entry, s32 entry_index) {
    if (get_town_state_count() != 0) {
        set_script_flag_bit(entry->unk_18);
    }
    return apply_selected_entry_values(entry, entry_index);
}
