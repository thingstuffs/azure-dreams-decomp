#include "common.h"
#include "town/player.h"
#include "town/scene.h"
#include "town/scene/flags.h"

/*
 * Sets the current entry script flag when the linked record field reaches 25, then applies the
 * selected entry values regardless of the threshold.
 */
void apply_values_marking_at_count_threshold(s32 request, s32 context) {
    if (get_town_state_count() >= 0x19) {
        set_current_entry_script_flag();
    }
    apply_selected_entry_values(request, context);
}
