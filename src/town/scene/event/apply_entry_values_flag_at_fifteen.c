#include "common.h"
#include "town/player.h"
#include "town/scene.h"
#include "town/scene/event.h"
#include "town/scene/flags.h"

/*
 * Sets the current entry script flag when the linked record field reaches 15, then applies the
 * selected entry values regardless of the threshold.
 */
void apply_entry_values_flag_at_fifteen(s32 request, s32 context) {
    if (get_town_state_count() >= 0xF) {
        set_current_entry_script_flag();
    }
    apply_selected_entry_values(request, context);
}
