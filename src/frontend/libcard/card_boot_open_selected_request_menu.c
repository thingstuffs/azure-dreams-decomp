#include "common.h"
#include "frontend/libcard/card_chooser.h"
#include "m2c_compat.h"

#include "frontend/libcard.h"
#include "frontend/libcard/interfaces.h"
/* Updates the record using its current mode and stored value. */
void card_boot_open_selected_request_menu(CardChooserBody *record) {
    s32 mode;

    card_boot_destroy_card_chooser((u8 *)record - 0x20);
    mode = record->mode;
    if (mode == 0) {
        card_boot_create_slot_selection_menu(record->request, 0);
        return;
    } else {
        card_boot_create_save_slot_menu(record->request, mode);
    }
}
