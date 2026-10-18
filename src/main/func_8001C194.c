#include "common.h"
#include "m2c_compat.h"

u8 *init_card_message_object();   /* extern */

/* Dispatch operation 5 for the target with one value. */
void func_8001C194(M2C_UNK target, M2C_UNK value) {
    init_card_message_object(target, 5, 1, value);
}
