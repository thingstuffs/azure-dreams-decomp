#include "common.h"
#include "frontend/libcard.h"
#include "frontend/libcard/slot_list.h"

/* Store the window's card slot index and owner. */
void card_boot_set_slot_index_and_owner(CardSlotWindow *window, s32 owner, s32 slot_index) {
    window->slot_index = slot_index;
    window->owner = owner;
}
