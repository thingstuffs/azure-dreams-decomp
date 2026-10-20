#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Forwards value to init_card_message_object with fixed options (1, 0, 0). */
void card_dev_show_no_memory_card_notice(s32 value) {
    init_card_message_object(value, 1, 0, 0);
}
