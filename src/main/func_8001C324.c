#include "common.h"
#include "m2c_compat.h"

u8 *init_card_message_object();   /* extern */

/* Dispatches operation 0xf in mode 2 with the supplied target and value. */
void func_8001C324(M2C_UNK target, M2C_UNK value) {
    init_card_message_object(target, 0xf, 2, value);
}
