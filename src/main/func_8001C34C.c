#include "common.h"
#include "m2c_compat.h"

u8 *init_card_message_object();   /* extern */

/* Passes value to init_card_message_object with fixed arguments 0x10, 0, 0. */
void func_8001C34C(M2C_UNK value) {
    init_card_message_object(value, 0x10, 0, 0);
}
