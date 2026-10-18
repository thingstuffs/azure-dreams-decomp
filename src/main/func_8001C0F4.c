#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Forwards value to init_card_message_object with fixed options (1, 0, 0). */
void func_8001C0F4(s32 value) {
    init_card_message_object(value, 1, 0, 0);
}
