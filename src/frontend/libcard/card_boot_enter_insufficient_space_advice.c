#include "common.h"
#include "frontend/libcard/save_menu.h"
#include "frontend/libcard/message.h"
#include "m2c_compat.h"

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"
#include "main/data.h"

/* Set record pointers around an update of its base record. */
void card_boot_enter_insufficient_space_advice(CardSaveMenuBody *record_part) {
    record_part->saved_callback = card_boot_update_save_slot_menu_input;
    card_boot_show_no_space_overwrite_notice(NODE_HEADER(record_part));
    NODE_HEADER(record_part)->update_callback = &D_800261F0;
}
