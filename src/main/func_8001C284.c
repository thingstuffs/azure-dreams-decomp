#include "common.h"
#include "m2c_compat.h"

u8 *init_card_message_object();   /* extern */

/* Forwards the input to init_card_message_object with arguments 0xC, 0, and 0. */
void func_8001C284(M2C_UNK input) {
    init_card_message_object(input, 0xc, 0, 0);
}
