#include "frontend/card/slot_details.h"
#include "frontend/card/save_slot.h"
#include "common.h"
#include "frontend/card.h"

/*
 * Builds selected-slot details for a nonzero cached card header, or the memory-task text for an
 * empty header.
 */
void select_memory_task_exit(CardDevSlotDetails *owner) {
    if (card_slot_header_cache[owner->selected_slot].fields.marker) {
        card_build_selected_slot_details(owner);
    } else {
        build_memory_task_text(owner);
    }
}
