#include "common.h"
#include "m2c_compat.h"

u8 *init_card_message_object();   /* extern */

/* Forwards value to init_card_message_object with fixed arguments 3, 0, and 0. */
void func_8001C2D4(M2C_UNK value) {
    init_card_message_object(value, 3, 0, 0);
}
