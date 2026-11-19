#include "common.h"
#include "frontend/libcard.h"
#include "slus.h"

/*
 * Clears the words referenced by the three-, four-, and ten-entry pointer tables, calling
 * noop_release_notification for the first three entries.
 */
void card_boot_clear_slot_words(CardSlotDetails *object) {
    s32 slot_index;

    for (slot_index = 0; slot_index < 3; slot_index++) {
        noop_release_notification(object->text_nodes[slot_index]->payload.word);
        object->text_nodes[slot_index]->payload.word = 0;
    }

    slot_index = 0;
    for (; slot_index < 4; slot_index++) {
        object->text_nodes[3 + slot_index]->payload.word = 0;
    }

    slot_index = 0;
    for (; slot_index < 0xA; slot_index++) {
        object->icon_nodes[slot_index]->payload.word = 0;
    }
}
