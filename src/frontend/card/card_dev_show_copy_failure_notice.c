#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Passes value to init_card_message_object with fixed arguments 0x10, 0, 0. */
void card_dev_show_copy_failure_notice(s32 value) {
    init_card_message_object(value, 0x10, 0, 0);
}
