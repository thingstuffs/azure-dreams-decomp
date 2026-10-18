#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Forward the context and value with fixed arguments 0x12 and 1. */
void func_8001C39C(s32 context, s32 value) {
    init_card_message_object(context, 0x12, 1, value);
}
