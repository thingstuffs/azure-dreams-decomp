#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Forwards value to init_card_message_object with fixed arguments 8, 0, and 0. */
void func_8001C144(s32 value) {
    init_card_message_object(value, 8, 0, 0);
}
