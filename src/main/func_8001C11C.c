#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Forwards the target and value to init_card_message_object with both selectors set to 2. */
void func_8001C11C(s32 target, s32 value) {
    init_card_message_object(target, 2, 2, value);
}
