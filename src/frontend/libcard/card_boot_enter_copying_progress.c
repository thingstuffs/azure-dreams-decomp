#include "common.h"
#include "frontend/libcard/save_menu.h"

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"

/* Sets two state fields, initializes embedded data, and assigns the record pointer. */
void card_boot_enter_copying_progress(CardSlotMenuState *object_data) {
    object_data->countdown = 1;
    card_boot_show_copying_progress(NODE_HEADER(object_data), &object_data->unk_40);
    object_data->unk_40 = 1;
    NODE_HEADER(object_data)->update_callback = &card_boot_wait_before_copying_slot;
}
