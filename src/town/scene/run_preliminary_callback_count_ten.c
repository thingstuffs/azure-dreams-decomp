#include "common.h"
#include "town/player.h"
#include "town/scene/flags.h"

extern s32 apply_selected_entry_values(); /* Slot contract: loading images do not establish one callee contract. */

/* Run the preliminary callback at a count of ten or more, then dispatch the argument pair. */
void run_preliminary_callback_count_ten(s32 dispatch_value, s32 dispatch_option) {
    if (get_town_state_count() >= 10) {
        set_current_entry_script_flag();
    }
    apply_selected_entry_values(dispatch_value, dispatch_option);
}
