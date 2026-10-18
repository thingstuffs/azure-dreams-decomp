#include "common.h"
#include "m2c_compat.h"

u8 *init_card_message_object();   /* extern */

/* Calls init_card_message_object for the target with fixed arguments 9, 0, and 0. */
void func_8001C20C(M2C_UNK target) {
    init_card_message_object(target, 9, 0, 0);
}
