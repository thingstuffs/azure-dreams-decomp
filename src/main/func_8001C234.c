#include "common.h"
#include "m2c_compat.h"

u8 *init_card_message_object();   /* extern */

/* Forwards value to init_card_message_object with fixed arguments 10, 0, and 0. */
void func_8001C234(M2C_UNK value) {
    init_card_message_object(value, 0xa, 0, 0);
}
