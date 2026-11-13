#include "common.h"
#include "frontend/libcard.h"
#include "frontend/libcard/slot_list.h"
#include "slus.h"

/* Release and clear the text of display slots 1-3, then clear slot 4's text. */
void card_boot_release_slot_window_texts(CardSlotWindow *window) {
    s32 slotIndex;

    for (slotIndex = 0; slotIndex < 3; slotIndex++) {
        noop_release_notification(window->pointers[slotIndex + 1]->unk_00);
        window->pointers[slotIndex + 1]->unk_00 = 0;
    }
    window->pointers[4]->unk_00 = 0;
}
