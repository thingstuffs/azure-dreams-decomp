#include "script_symbols.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/scene/record_actions.h"
#include "town/scene/entry_requests.h"
#include "town/scene/flags.h"

/* Update the context flag and dispatch the selected entry according to active flags. */
s32 dispatch_entry_for_active_flags(TownObjectSet *entry, s32 entry_index) {
    if (get_script_flag_mask(F_s34_sero_quickstart) != 0) {
        set_script_flag_bit(entry->entry_flag);
        return process_checked_entry(entry, entry_index);
    }
    if (get_script_flag_mask(F_s34_sero_start) != 0) {
        set_script_flag_bit(entry->entry_flag);
    }
    return apply_selected_entry_values(entry, entry_index);
}
