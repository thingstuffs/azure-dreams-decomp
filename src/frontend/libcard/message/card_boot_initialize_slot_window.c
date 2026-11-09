#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"
#include "frontend/libcard/slot_list.h"


/* Store the window's slot and owner, link its frame node, and fill its display. */
void card_boot_initialize_slot_window(CardSlotWindow *window, s32 owner, s32 slot_index) {
    card_boot_set_slot_index_and_owner(window, owner, slot_index);
    card_boot_initialize_slot_window_frame(&window->frame, &window->frame_block, &window->frame_vector, slot_index);
    card_boot_populate_slot_window_display(window);
}
