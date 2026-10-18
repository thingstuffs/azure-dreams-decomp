#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Forward the target and value to init_card_message_object with selectors 0 and 1. */
void func_8001C0CC(s32 target, s32 value) {
    init_card_message_object(target, 0, 1, value);
}
