#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Pass the target to init_card_message_object with code 0x13 and zero options. */
void func_8001C3C4(s32 target) {
    init_card_message_object(target, 0x13, 0, 0);
}
