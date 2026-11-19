#include "common.h"
#include "frontend/libcard/interfaces.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"


/* Initializes object data and assigns the card_boot_handle_slot_selection_input record pointer. */
void card_boot_resume_menu_after_slot_refresh(CardSlotMenuState *menu) {
    card_boot_refresh_five_slot_selection(menu);
    (NODE_HEADER(menu))->update_callback = card_boot_handle_slot_selection_input;
}
