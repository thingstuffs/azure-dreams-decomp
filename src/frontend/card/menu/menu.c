#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "frontend/card/menu.h"
#include "main/data.h"

/* Decrement the record's counter and replace its pointer when the counter becomes negative. */
void decrement_card_menu_countdown(CardChooserBody *record_data) {
    s32 counter;

    counter = record_data->format_countdown - 1;
    record_data->format_countdown = counter;
    if (counter < 0) {
        NODE_HEADER(record_data)->update_callback = card_boot_poll_status_and_select_context;
    }
}
