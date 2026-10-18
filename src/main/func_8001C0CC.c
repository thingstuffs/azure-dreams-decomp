#include "common.h"
#include "m2c_compat.h"

u8 *init_card_message_object();   /* extern */

/* Forward the target and value to init_card_message_object with selectors 0 and 1. */
void func_8001C0CC(M2C_UNK target, M2C_UNK value) {
    init_card_message_object(target, 0, 1, value);
}
