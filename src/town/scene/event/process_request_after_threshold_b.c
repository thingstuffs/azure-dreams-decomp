#include "common.h"
#include "town/player.h"
#include "town/scene/event.h"
#include "town/scene/flags.h"

extern s32 apply_selected_entry_values(); /* Slot contract: loading images do not establish one callee contract. */

/*
 * Sets the current entry script flag when the linked record field reaches 20, then applies the
 * selected entry values regardless of the threshold.
 */
void process_request_after_threshold_20(s32 request, s32 context) {
    if (get_linked_record_field_2_d_60() >= 0x14) {
        set_current_entry_script_flag();
    }
    apply_selected_entry_values(request, context);
}
