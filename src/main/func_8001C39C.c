#include "common.h"
#include "m2c_compat.h"

u8 *init_card_message_object();   /* extern */

/* Forward the context and value with fixed arguments 0x12 and 1. */
void func_8001C39C(M2C_UNK context, M2C_UNK value) {
    init_card_message_object(context, 0x12, 1, value);
}
