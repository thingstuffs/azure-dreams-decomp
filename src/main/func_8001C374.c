#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Forwards the target to init_card_message_object with fixed arguments 0x11, 0, and 0. */
void func_8001C374(s32 target) {
    init_card_message_object(target, 0x11, 0, 0);
}
