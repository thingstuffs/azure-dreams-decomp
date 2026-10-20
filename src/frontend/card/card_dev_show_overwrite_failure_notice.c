#include "common.h"

#include "frontend/card/message_object.h"   /* extern */

/* Forwards value to init_card_message_object with fixed arguments 8, 0, and 0. */
void card_dev_show_overwrite_failure_notice(s32 value) {
    init_card_message_object(value, 8, 0, 0);
}
