#include "common.h"
#include "frontend/libcard/save_menu.h"
#include "frontend/libcard/message.h"
#include "m2c_compat.h"

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"
#include "main/data.h"

/* Set record pointers around an update of its base record. */
void card_boot_enter_insufficient_space_advice(void *record_part) {
    CardMenuCallbackPrefix *state = record_part;

    state->saved_callback = write_text_and_advance_selection;
    card_boot_show_insufficient_space_overwrite_advice(NODE_HEADER(record_part));
    ((ObjectNodeHeader *)record_part - 1)->update_callback = &D_800261F0;
}
