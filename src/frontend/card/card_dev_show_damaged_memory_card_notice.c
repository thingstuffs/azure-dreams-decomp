#include "common.h"

#include "frontend/card/message_object.h"   /* extern */

/* Forwards value to init_card_message_object with fixed arguments 3, 0, and 0. */
void card_dev_show_damaged_memory_card_notice(s32 value) {
    init_card_message_object(value, 3, 0, 0);
}
