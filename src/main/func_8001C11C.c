#include "common.h"
#include "m2c_compat.h"

u8 *init_card_message_object();   /* extern */

/* Forwards the target and value to init_card_message_object with both selectors set to 2. */
void func_8001C11C(M2C_UNK target, M2C_UNK value) {
    init_card_message_object(target, 2, 2, value);
}
