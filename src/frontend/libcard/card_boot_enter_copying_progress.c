#include "common.h"
#include "frontend/libcard/save_menu.h"

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"

/* Sets two state fields, initializes embedded data, and assigns the record pointer. */
void card_boot_enter_copying_progress(void *object_data) {
    CardSaveMenuBody *state = object_data;

    state->countdown = 1;
    card_boot_show_copying_progress(object_data - 0x20, object_data + 0x40);
    state->unk_40 = 1;
    ((ObjectNodeHeader *)object_data - 1)->update_callback = &card_boot_wait_before_copying_slot;
}
