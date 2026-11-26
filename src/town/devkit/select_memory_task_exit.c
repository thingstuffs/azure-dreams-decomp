#include "frontend/card/slot_details.h"
#include "town/devkit/memory_task.h"
#include "frontend/card/save_slot.h"
#include "town/devkit.h"
#include "frontend/card.h"






/* Select the exit or fallback path using the indexed table entry. */
void select_memory_task_exit(CardDevSlotDetails *object) {
    if (card_slot_header_cache[object->selected_slot].fields.marker != 0) {
        card_build_selected_slot_details(object);
    } else {
        build_memory_task_text(object);
    }
}
