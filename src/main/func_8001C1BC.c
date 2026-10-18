#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Dispatch operation 6 in mode 2 with the supplied target and value. */
void func_8001C1BC(s32 target, s32 value) {
    init_card_message_object(target, 6, 2, value);
}
