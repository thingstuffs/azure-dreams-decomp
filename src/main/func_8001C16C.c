#include "common.h"
#include "m2c_compat.h"

u8 *init_card_message_object();   /* extern */

/* Forwards a target and value to init_card_message_object with fixed parameters 4 and 2. */
void func_8001C16C(M2C_UNK target, M2C_UNK value) {
    init_card_message_object(target, 4, 2, value);
}
