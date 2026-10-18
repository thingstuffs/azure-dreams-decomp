#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Calls init_card_message_object with the target and fixed arguments (13, 0, 0). */
void func_8001C2AC(s32 target) {
    init_card_message_object(target, 0xd, 0, 0);
}
