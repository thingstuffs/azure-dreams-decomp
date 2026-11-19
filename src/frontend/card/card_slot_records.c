/* Copy card slot record fields and refresh the five displayed objects. */

#include "common.h"
#include "m2c_compat.h"
#include "engine/resource.h"
#include "frontend/card.h"
#include "frontend/libcard.h"

/*
 * Releases the node's card record handles, closes the card boot events and resumes the timer, then
 * requests scene dispatch state 3.
 */

void release_card_records_and_request_scene_state_three(CardSaveMenuBody *menu) {
    release_card_record_handles(NODE_HEADER(menu));
    card_boot_close_events_and_resume_timer();
    request_scene_dispatch_state(3);
}


/* Runs card_boot_refresh_slot_window on each of five stored object addresses. */
void card_boot_refresh_five_slot_objects(CardSaveMenuBody *menu) {
    s32 object_index;

    object_index = 0;
    do {
        ObjectNodeHeader *window = menu->slots[object_index];
        object_index++;
        card_boot_refresh_slot_window(window);
    } while (object_index < 5);
}
