#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Forwards value to init_card_message_object with fixed arguments 10, 0, and 0. */
void card_dev_show_insufficient_space_card_advice(s32 value) {
    init_card_message_object(value, 0xa, 0, 0);
}
