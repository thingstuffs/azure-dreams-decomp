#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Passes value to init_card_message_object with fixed arguments 0x10, 0, 0. */
void func_8001C34C(s32 value) {
    init_card_message_object(value, 0x10, 0, 0);
}
