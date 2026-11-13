#include "common.h"
#include "frontend/libcard.h"
#include "slus.h"

/*
 * Clears the words referenced by the three-, four-, and ten-entry pointer tables, calling
 * noop_release_notification for the first three entries.
 */
void card_boot_clear_slot_words(void *object) {
    s32 slot_index;
    void *four_slot_base;
    void *ten_slot_base;

    for (slot_index = 0; slot_index < 3; slot_index++) {
        noop_release_notification(((CardSlotDetails *)((u8 *)object + slot_index * 4))->text_nodes[0]->payload.word);
        ((CardSlotDetails *)((u8 *)object + slot_index * 4))->text_nodes[0]->payload.word = 0;
    }

    slot_index = 0;
    four_slot_base = object;
    for (; slot_index < 4; slot_index++) {
        ((CardSlotDetails *)four_slot_base)->text_nodes[3]->payload.word = 0;
        four_slot_base = (u8 *) four_slot_base + 4;
    }

    slot_index = 0;
    ten_slot_base = object;
    for (; slot_index < 0xA; slot_index++) {
        ((CardSlotDetails *)ten_slot_base)->icon_nodes[0]->payload.word = 0;
        ten_slot_base = (u8 *) ten_slot_base + 4;
    }
}
